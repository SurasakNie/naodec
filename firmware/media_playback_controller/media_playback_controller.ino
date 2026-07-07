/*
 * media_playback_controller.ino
 * NaoDec Media Playback Controller — ESP32-S3-DevKitC-1 OSC operator panel
 *
 * Inputs:  rotary encoder (volume) + Play/Pause/Stop buttons.
 * Output:  OSC-over-UDP to a Max/MSP patch. No audio, video, or LED data/power
 *          passes through this board — see NaoDec_Media_Playback_Controller_
 *          Build_and_Max_Setup.md for the full hardware and network spec.
 *
 * Wi-Fi provisioning: WiFiManager captive portal ("NaoDecPlayback-Setup"), so
 * no SSID/password is ever hardcoded in this file. Type RESETWIFI in the
 * Serial Monitor to clear saved credentials and re-open the portal, or STATUS
 * to print current Wi-Fi/volume/uptime state.
 *
 * New library required: "WiFiManager" by tzapu (Arduino Library Manager)
 */

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <WiFiManager.h>
#include <Preferences.h>

// ── Firmware ──────────────────────────────────────────────────────────────────
#define FW_VERSION "1.0.0"

// ── Hardware (see Build doc Section 3 — Pin Connections) ────────────────────
#define PIN_ENC_A       7
#define PIN_ENC_B       8
#define PIN_BTN_PLAY    9
#define PIN_BTN_PAUSE  10
#define PIN_BTN_STOP   11
#define PIN_STATUS_LED 12

// ── Network (see Build doc Section 6/8 — not secrets, already public there) ─
#define MAX_HOST   "192.168.50.2"
#define OSC_PORT   9000
#define HOSTNAME   "naodec-playback"   // -> naodec-playback.local

// ── Tuning ────────────────────────────────────────────────────────────────────
#define DEBOUNCE_MS            30
#define VOLUME_STEP             2   // percentage points per detent
#define VOLUME_SAVE_IDLE_MS  2000
#define LED_BLINK_MS          250   // ~2 Hz
#define RECONNECT_INTERVAL_MS 5000
#define ENCODER_REVERSED        0   // 1 if clockwise decreases volume (Build doc Section 9 troubleshooting: swap A/B wiring, or flip this instead)

// ── Globals ───────────────────────────────────────────────────────────────────
WiFiUDP     udp;
Preferences prefs;

int           volume            = 50;   // 0..100, persisted in NVS
bool          volumeDirty        = false;
unsigned long lastVolumeChangeMs = 0;

bool          resetWifiRequested   = false;  // set by RESETWIFI, handled in loop()
unsigned long lastReconnectAttempt = 0;

bool          ledState        = false;
unsigned long lastLedToggleMs = 0;

// ── Quadrature encoder (quarter-step Gray-code table, ISR-driven) ───────────
// Indexed by (prevState<<2 | currState), state = (A<<1)|B. 0 = invalid/bounce
// transition (ignored); +-1 = a valid quarter step. Four valid quarter steps
// accumulate into one full detent — this rejects single-bit contact bounce
// from either the NEBDS-01 (Schmitt-clean) or the optional KY-040 (bouncy)
// encoder per Build doc Section 3, with no separate "KY-040 mode" needed.
static const int8_t QUAD_TABLE[16] = {
   0, -1,  1,  0,
   1,  0,  0, -1,
  -1,  0,  0,  1,
   0,  1, -1,  0
};

volatile int8_t encoderAccum   = 0;
volatile int8_t encoderDetents = 0;
volatile uint8_t encoderPrevState = 0;

void IRAM_ATTR onEncoderChange() {
  uint8_t a = digitalRead(PIN_ENC_A);
  uint8_t b = digitalRead(PIN_ENC_B);
  uint8_t state = (a << 1) | b;
  int8_t delta = QUAD_TABLE[(encoderPrevState << 2) | state];
  encoderPrevState = state;
  if (delta == 0) return;
  encoderAccum += delta;
  if (encoderAccum >= 4) {
    encoderDetents++;
    encoderAccum = 0;
  } else if (encoderAccum <= -4) {
    encoderDetents--;
    encoderAccum = 0;
  }
}

// ── Debounced buttons ─────────────────────────────────────────────────────────
struct DebouncedButton {
  uint8_t       pin;
  uint8_t       stableState;
  uint8_t       lastRawState;
  unsigned long lastChangeMs;

  void begin(uint8_t p) {
    pin          = p;
    stableState  = HIGH;  // idle = released (active-low, pulled high)
    lastRawState = HIGH;
    lastChangeMs = 0;
  }

  // Returns true exactly once, on the debounced falling (press) edge.
  bool pressedEdge() {
    uint8_t raw = digitalRead(pin);
    if (raw != lastRawState) {
      lastRawState = raw;
      lastChangeMs = millis();
    }
    if ((millis() - lastChangeMs) >= DEBOUNCE_MS && raw != stableState) {
      stableState = raw;
      return stableState == LOW;
    }
    return false;
  }
};

DebouncedButton btnPlay, btnPause, btnStop;

// ── OSC sender ────────────────────────────────────────────────────────────────
// Minimal hand-rolled OSC-over-UDP packet builder — only two message shapes
// are ever needed (int argument, float argument), so no OSC library dependency.
size_t appendOscString(uint8_t* buf, size_t offset, const char* str) {
  size_t len = strlen(str);
  memcpy(buf + offset, str, len);
  offset += len;
  size_t padded    = ((len / 4) + 1) * 4;  // always >=1 null, total a multiple of 4
  size_t nullCount = padded - len;
  memset(buf + offset, 0, nullCount);
  return offset + nullCount;
}

void appendBigEndianU32(uint8_t* buf, size_t offset, uint32_t v) {
  buf[offset + 0] = (v >> 24) & 0xFF;
  buf[offset + 1] = (v >> 16) & 0xFF;
  buf[offset + 2] = (v >> 8) & 0xFF;
  buf[offset + 3] = v & 0xFF;
}

void sendOscInt(const char* address, int32_t value) {
  uint8_t buf[64];
  size_t offset = appendOscString(buf, 0, address);
  offset = appendOscString(buf, offset, ",i");
  appendBigEndianU32(buf, offset, (uint32_t)value);
  offset += 4;
  udp.beginPacket(MAX_HOST, OSC_PORT);
  udp.write(buf, offset);
  udp.endPacket();
}

void sendOscFloat(const char* address, float value) {
  uint8_t buf[64];
  size_t offset = appendOscString(buf, 0, address);
  offset = appendOscString(buf, offset, ",f");
  uint32_t bits;
  memcpy(&bits, &value, sizeof(bits));
  appendBigEndianU32(buf, offset, bits);
  offset += 4;
  udp.beginPacket(MAX_HOST, OSC_PORT);
  udp.write(buf, offset);
  udp.endPacket();
}

// ── Volume ────────────────────────────────────────────────────────────────────
void applyVolumeDelta(int detents) {
  int newVolume = volume + detents * VOLUME_STEP;
  if (newVolume < 0) newVolume = 0;
  if (newVolume > 100) newVolume = 100;
  if (newVolume == volume) return;

  volume = newVolume;
  float normalized = volume / 100.0f;
  sendOscFloat("/volume", normalized);
  Serial.printf("[ENC]  volume=%d -> /volume %.2f\n", volume, normalized);

  volumeDirty        = true;
  lastVolumeChangeMs = millis();
}

void saveVolumeIfIdle() {
  if (!volumeDirty) return;
  if (millis() - lastVolumeChangeMs < VOLUME_SAVE_IDLE_MS) return;
  prefs.putUInt("volume", volume);
  volumeDirty = false;
  Serial.printf("[VOL]  Saved volume: %d\n", volume);
}

// ── Status LED ────────────────────────────────────────────────────────────────
void updateStatusLed() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(PIN_STATUS_LED, HIGH);
    ledState = true;
    return;
  }
  if (millis() - lastLedToggleMs >= LED_BLINK_MS) {
    ledState = !ledState;
    digitalWrite(PIN_STATUS_LED, ledState ? HIGH : LOW);
    lastLedToggleMs = millis();
  }
}

// ── Wi-Fi ─────────────────────────────────────────────────────────────────────
void maintainWifi() {
  if (WiFi.status() == WL_CONNECTED) return;
  if (millis() - lastReconnectAttempt < RECONNECT_INTERVAL_MS) return;
  lastReconnectAttempt = millis();
  Serial.println("[WIFI] Disconnected, attempting reconnect...");
  WiFi.reconnect();
}

// ── Buttons ───────────────────────────────────────────────────────────────────
void updateButtons() {
  if (btnPlay.pressedEdge()) {
    sendOscInt("/transport/play", 1);
    Serial.println("[BTN]  Play -> /transport/play 1");
  }
  if (btnPause.pressedEdge()) {
    sendOscInt("/transport/pause", 1);
    Serial.println("[BTN]  Pause -> /transport/pause 1");
  }
  if (btnStop.pressedEdge()) {
    sendOscInt("/transport/stop", 1);
    Serial.println("[BTN]  Stop -> /transport/stop 1");
  }
}

// ── Encoder ───────────────────────────────────────────────────────────────────
void updateEncoder() {
  noInterrupts();
  int8_t detents = encoderDetents;
  encoderDetents = 0;
  interrupts();
  if (ENCODER_REVERSED) detents = -detents;
  if (detents != 0) applyVolumeDelta(detents);
}

// ── Serial input (USB) ────────────────────────────────────────────────────────
void printStatus() {
  Serial.println("[STATUS] ----------------------------");
  Serial.printf("[STATUS] Wi-Fi:      %s\n", WiFi.status() == WL_CONNECTED ? "connected" : "disconnected");
  Serial.printf("[STATUS] IP address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("[STATUS] Volume:     %d\n", volume);
  Serial.printf("[STATUS] Uptime:     %lu s\n", millis() / 1000);
  Serial.println("[STATUS] ----------------------------");
}

void handleSerialCommand(const char* cmd) {
  while (*cmd == ' ') cmd++;  // ltrim

  if (strncmp(cmd, "RESETWIFI", 9) == 0) {
    Serial.println("[WIFI] Reset requested — clearing credentials, restarting...");
    resetWifiRequested = true;  // handled safely in loop(), not inside a callback
  } else if (strncmp(cmd, "STATUS", 6) == 0) {
    printStatus();
  } else if (strlen(cmd) > 0) {
    Serial.printf("[WARN] Unknown command: %s\n", cmd);
  }
}

void checkSerial() {
  static char buf[32];
  static int  idx = 0;
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      if (idx > 0) {
        buf[idx] = '\0';
        handleSerialCommand(buf);
        idx = 0;
      }
    } else if (idx < (int)sizeof(buf) - 1) {
      buf[idx++] = c;
    }
  }
}

// ── setup ─────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(100);  // let USB CDC enumerate before the first log line
  Serial.println();
  Serial.println("[BOOT] NaoDec Media Playback Controller starting...");
  Serial.printf("[BOOT] Firmware version %s\n", FW_VERSION);
  Serial.println("[BOOT] Serial commands: RESETWIFI  |  STATUS");

  // Safe boot state first: LED off, no OSC sent, before any control logic runs.
  pinMode(PIN_STATUS_LED, OUTPUT);
  digitalWrite(PIN_STATUS_LED, LOW);

  pinMode(PIN_BTN_PLAY, INPUT_PULLUP);
  pinMode(PIN_BTN_PAUSE, INPUT_PULLUP);
  pinMode(PIN_BTN_STOP, INPUT_PULLUP);
  btnPlay.begin(PIN_BTN_PLAY);
  btnPause.begin(PIN_BTN_PAUSE);
  btnStop.begin(PIN_BTN_STOP);

  pinMode(PIN_ENC_A, INPUT);
  pinMode(PIN_ENC_B, INPUT);
  encoderPrevState = (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_A), onEncoderChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_B), onEncoderChange, CHANGE);

  prefs.begin("playback", false);
  volume = prefs.getUInt("volume", 50);
  Serial.printf("[VOL]  Loaded volume: %d\n", volume);
  // Not sent on boot: Max keeps its own gain until the operator turns the
  // knob, matching the "no commands sent on boot" rule for Play/Pause/Stop.

  WiFiManager wm;
  wm.setHostname(HOSTNAME);
  if (!wm.autoConnect("NaoDecPlayback-Setup")) {
    Serial.println("[ERROR] WiFiManager failed to connect, restarting...");
    ESP.restart();
  }
  Serial.printf("[WIFI] Connected. IP: %s\n", WiFi.localIP().toString().c_str());

  if (MDNS.begin(HOSTNAME)) {
    Serial.printf("[mDNS] %s.local ready\n", HOSTNAME);
  }

  udp.begin(0);  // ephemeral local port; this device only ever sends OSC
  Serial.printf("[OSC]  Sending to %s:%d\n", MAX_HOST, OSC_PORT);

  Serial.println("[BOOT] Ready.");
}

// ── loop ──────────────────────────────────────────────────────────────────────
void loop() {
  checkSerial();

  // Deferred Wi-Fi reset — executed here rather than inside the serial
  // callback to avoid restarting while the network stack is mid-operation.
  if (resetWifiRequested) {
    Serial.println("[WIFI] Clearing saved credentials...");
    digitalWrite(PIN_STATUS_LED, LOW);
    WiFiManager wm;
    wm.resetSettings();
    delay(200);
    ESP.restart();
  }

  maintainWifi();
  updateStatusLed();
  updateButtons();
  updateEncoder();
  saveVolumeIfIdle();
}
