/*
 * media_playback_controller.ino
 * NaoDec Media Playback Controller — ESP32-S3-DevKitC-1 OSC operator panel
 *
 * Inputs:  rotary encoder (volume) + Play/Pause/Stop buttons.
 * Output:  OSC-over-UDP to a Max/MSP patch. No audio, video, or LED data/power
 *          passes through this board — see NaoDec_Media_Playback_Controller_
 *          Build_and_Max_Setup.md for the full hardware and network spec.
 *
 * Network: wired Ethernet via U2, a WIZnet W5500 Lite SPI module (hardware
 * Rev 3.0, SPI on GPIO13-18). DHCP only — the router reserves 192.168.50.114
 * keyed to the Ethernet MAC; type STATUS in the Serial Monitor to read that
 * MAC plus link/IP/volume/uptime state. Nothing to provision, and the board
 * is safe to boot with the cable unplugged (LED blinks until link + lease).
 *
 * Requires the esp32 Arduino core >= 3.0.0 (W5500 support lives in the
 * core's ETH.h). No third-party libraries.
 */

#include <ETH.h>
#include <Network.h>
#include <NetworkUdp.h>
#include <ESPmDNS.h>
#include <Preferences.h>

// ── Firmware ──────────────────────────────────────────────────────────────────
// major.minor tracks the schematic revision this firmware targets (Rev 3.0);
// the patch digit is for firmware-only fixes on that hardware.
#define FW_VERSION "3.0.0"

// ── Hardware (see Build doc Section 3 — Pin Connections) ────────────────────
#define PIN_ENC_A       7
#define PIN_ENC_B       8
#define PIN_BTN_PLAY    9
#define PIN_BTN_PAUSE  10
#define PIN_BTN_STOP   11
#define PIN_STATUS_LED 12

// ── Ethernet (Rev 3.0 — U2 W5500 Lite on SPI, see schematic wire schedule) ──
#define PIN_ETH_SCLK   13
#define PIN_ETH_MOSI   14
#define PIN_ETH_MISO   15
#define PIN_ETH_CS     16
#define PIN_ETH_INT    17   // W5500 INTn. If a bench build leaves INT unwired, irq=-1 (polled) needs core >= 3.1.
#define PIN_ETH_RST    18   // the esp_eth driver pulses this itself (phy reset_gpio_num) — no manual reset code
#define ETH_PHY_ADDR_W5500  1
#define ETH_SPI_HOST_W5500  SPI2_HOST
#define ETH_SPI_MHZ_W5500   20  // GPIO-matrix SPI is good to ~26 MHz; drop to 10-16 if a jumper-wired module misbehaves

// ── Network (see Build doc Section 6/8 — not secrets, already public there) ─
#define MAX_HOST   "192.168.50.2"
#define OSC_PORT   9000
#define HOSTNAME   "naodec-playback"   // -> naodec-playback.local

// ── Tuning ────────────────────────────────────────────────────────────────────
#define DEBOUNCE_MS            30
#define VOLUME_STEP             2   // percentage points per detent
#define VOLUME_SAVE_IDLE_MS  2000
#define LED_BLINK_MS          250   // ~2 Hz
#define ENCODER_REVERSED        0   // 1 if clockwise decreases volume (Build doc Section 9 troubleshooting: swap A/B wiring, or flip this instead)
#define ENCODER_STEPS_PER_DETENT 4  // quarter-steps per physical click; standard EC11/KY-040 = 4, some variants = 2 (set here if FUNC-05 shows half the expected step)

// ── Globals ───────────────────────────────────────────────────────────────────
NetworkUDP  udp;
Preferences prefs;

int           volume            = 50;   // 0..100, persisted in NVS
bool          volumeDirty        = false;
unsigned long lastVolumeChangeMs = 0;

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

volatile int8_t  encoderAccum   = 0;
volatile int16_t encoderDetents = 0;  // int16 headroom so a fast spin between loop() passes can't wrap
volatile uint8_t encoderPrevState = 0;

void IRAM_ATTR onEncoderChange() {
  uint8_t a = digitalRead(PIN_ENC_A);
  uint8_t b = digitalRead(PIN_ENC_B);
  uint8_t state = (a << 1) | b;
  int8_t delta = QUAD_TABLE[(encoderPrevState << 2) | state];
  encoderPrevState = state;
  if (delta == 0) return;
  encoderAccum += delta;
  if (encoderAccum >= ENCODER_STEPS_PER_DETENT) {
    encoderDetents++;
    encoderAccum = 0;
  } else if (encoderAccum <= -ENCODER_STEPS_PER_DETENT) {
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
    // Sample the actual pin so a button held (or a harness shorted) at boot is
    // treated as the resting state — no phantom press edge on power-up (FUNC-08).
    // Call after pinMode(p, INPUT_PULLUP).
    stableState  = digitalRead(p);
    lastRawState = stableState;
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

// ── Ethernet (W5500) ──────────────────────────────────────────────────────────
// esp_netif owns DHCP, including re-acquiring the lease when the link comes
// back — there is no reconnect logic to run in loop(). The events below are
// for serial logging (and hostname latching) only; the status LED and the
// OSC guards poll networkReady() instead of tracking event state.
bool networkReady() {
  return ETH.hasIP();  // link up AND a DHCP lease in hand
}

void onNetworkEvent(arduino_event_id_t event) {
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      ETH.setHostname(HOSTNAME);  // some core versions only latch the hostname here
      Serial.println("[ETH]  Started");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      Serial.println("[ETH]  Link up");
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      Serial.printf("[ETH]  DHCP lease: %s (expect 192.168.50.114 if the router reservation is set)\n",
                    ETH.localIP().toString().c_str());
      break;
    case ARDUINO_EVENT_ETH_LOST_IP:
      Serial.println("[ETH]  Lost IP");
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      Serial.println("[ETH]  Link down");
      break;
    default:
      break;
  }
}

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
  if (!networkReady()) return;  // offline: drop the send instead of spamming lwIP route errors
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
  if (!networkReady()) return;  // offline: drop the send instead of spamming lwIP route errors
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
// Solid = Ethernet link up with a DHCP lease; ~2 Hz blink = no link / no
// lease; off = no power (or firmware fault). Matches Build doc Section 3.
void updateStatusLed() {
  if (networkReady()) {
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
  int16_t detents = encoderDetents;
  encoderDetents = 0;
  interrupts();
  if (ENCODER_REVERSED) detents = -detents;
  if (detents != 0) applyVolumeDelta(detents);
}

// ── Serial input (USB) ────────────────────────────────────────────────────────
void printStatus() {
  Serial.println("[STATUS] ----------------------------");
  Serial.printf("[STATUS] Firmware:   %s\n", FW_VERSION);
  if (ETH.linkUp()) {
    Serial.printf("[STATUS] Link:       up, %d Mbps %s-duplex\n",
                  (int)ETH.linkSpeed(), ETH.fullDuplex() ? "full" : "half");
  } else {
    Serial.println("[STATUS] Link:       down (check the Cat6 cable and router LAN port)");
  }
  Serial.printf("[STATUS] IP address: %s\n", ETH.localIP().toString().c_str());
  Serial.printf("[STATUS] MAC (ETH):  %s  <- key the router DHCP reservation to this\n",
                ETH.macAddress().c_str());
  Serial.printf("[STATUS] Hostname:   %s (.local)\n", HOSTNAME);
  Serial.printf("[STATUS] OSC target: %s:%d\n", MAX_HOST, OSC_PORT);
  Serial.printf("[STATUS] Volume:     %d\n", volume);
  Serial.printf("[STATUS] Uptime:     %lu s\n", millis() / 1000);
  Serial.println("[STATUS] ----------------------------");
}

void handleSerialCommand(const char* cmd) {
  while (*cmd == ' ') cmd++;  // ltrim

  if (strcmp(cmd, "RESETWIFI") == 0) {
    // Courtesy stub for FW 1.x muscle memory.
    Serial.println("[INFO] RESETWIFI was removed in FW 3.x — Rev 3.0 is wired Ethernet; nothing to provision.");
  } else if (strcmp(cmd, "STATUS") == 0) {
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
  Serial.printf("[BOOT] Firmware version %s (hardware Rev 3.0, W5500 Ethernet)\n", FW_VERSION);
  Serial.println("[BOOT] Serial commands: STATUS");

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

  Network.onEvent(onNetworkEvent);
  ETH.setHostname(HOSTNAME);  // belt; ETH_START latches it again (suspenders)

  bool ethOk = ETH.begin(ETH_PHY_W5500, ETH_PHY_ADDR_W5500, PIN_ETH_CS, PIN_ETH_INT,
                         PIN_ETH_RST, ETH_SPI_HOST_W5500, PIN_ETH_SCLK, PIN_ETH_MISO,
                         PIN_ETH_MOSI, ETH_SPI_MHZ_W5500);
  if (!ethOk) {
    // Driver/SPI fault (wiring, W5500 3.3 V power) — unlike a missing cable,
    // this can't self-heal from loop(), so blink visibly and retry from a
    // clean boot. A genuine fault shows up as a loggable ~10 s boot loop.
    Serial.println("[ERROR] W5500 init failed — check SPI wiring and 3.3 V power. Restarting in 10 s...");
    for (int i = 0; i < 10000 / LED_BLINK_MS; i++) {
      digitalWrite(PIN_STATUS_LED, (i & 1) ? HIGH : LOW);
      delay(LED_BLINK_MS);
    }
    ESP.restart();
  }
  // begin() does not wait for a cable: fall through to loop(), where the LED
  // blinks until link + DHCP lease arrive (safe to boot unplugged).
  Serial.printf("[ETH]  MAC %s — waiting for link/DHCP (LED blinks until ready)\n",
                ETH.macAddress().c_str());

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
  updateStatusLed();
  updateButtons();
  updateEncoder();
  saveVolumeIfIdle();
}
