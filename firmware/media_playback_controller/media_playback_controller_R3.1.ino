/*
 * media_playback_controller.ino
 * NaoDec Media Playback Controller — ESP32-S3-DevKitC-1 OSC operator panel
 *
 * Inputs:  rotary encoder (volume) + Play/Pause/Stop buttons.
 * Output:  OSC-over-UDP to a Max/MSP patch. No audio, video, or LED data/power
 *          passes through this board — see NaoDec_Media_Playback_Controller_
 *          Build_and_Max_Setup.md for the full hardware and network spec.
 *
 * Network: wired Ethernet is primary — U2, a WIZnet W5500 Lite SPI module
 * (hardware Rev 3.0, SPI on GPIO13-18), DHCP only. The router reserves
 * 192.168.50.114 keyed to the Ethernet MAC.
 *
 * Wi-Fi fallback (Rev 3.1): if the Ethernet link drops and stays down, and
 * Wi-Fi credentials have been stored, the controller brings up a Wi-Fi station
 * and keeps sending OSC over it. Ethernet always wins — the moment the cable
 * link + DHCP lease return, Wi-Fi is shut back off. Provision credentials over
 * USB serial with SETWIFI (they live in NVS, never in this file); RESETWIFI
 * clears them; STATUS prints the active interface plus link/IP/MAC/volume/
 * uptime state. With no credentials stored the board behaves exactly like
 * Rev 3.0 — wired only, nothing to provision.
 *
 * The board is safe to boot with the cable unplugged (LED blinks until a link
 * comes up on either interface).
 *
 * Requires the esp32 Arduino core >= 3.0.0 (W5500 support lives in the core's
 * ETH.h; WiFi.h is also part of the core). No third-party libraries.
 */

#include <ETH.h>
#include <WiFi.h>
#include <Network.h>
#include <NetworkUdp.h>
#include <ESPmDNS.h>
#include <Preferences.h>

// ── Firmware ──────────────────────────────────────────────────────────────────
// major tracks the schematic revision this firmware targets (Rev 3.x hardware);
// minor bumps for firmware feature releases on that hardware (3.1 = Wi-Fi
// fallback); the patch digit is for firmware-only fixes.
#define FW_VERSION "3.1.0"

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
#define LED_BLINK_MS          250   // ~2 Hz (no-network blink)
#define LED_WIFI_PERIOD_MS   2000   // Wi-Fi fallback: one off-blip per this period
#define LED_WIFI_BLIP_MS      150   // ...off for this long within the period (mostly-on)
#define ENCODER_REVERSED        0   // 1 if clockwise decreases volume (Build doc Section 9 troubleshooting: swap A/B wiring, or flip this instead)
#define ENCODER_STEPS_PER_DETENT 4  // quarter-steps per physical click; standard EC11/KY-040 = 4, some variants = 2 (set here if FUNC-05 shows half the expected step)

// Wi-Fi fallback timing. Only arm the fallback after Ethernet has been down
// this long, so a brief cable/link glitch or a normal boot-time DHCP wait does
// not thrash the radio. WIFI_RETRY_MS mirrors the FW 1.x reconnect cadence:
// longer than one associate+DHCP cycle, so a retry can't abort an attempt in
// progress.
#define ETH_FALLBACK_MS     15000
#define WIFI_RETRY_MS       15000

// ── Globals ───────────────────────────────────────────────────────────────────
NetworkUDP  udp;
Preferences prefs;

int           volume            = 50;   // 0..100, persisted in NVS
bool          volumeDirty        = false;
unsigned long lastVolumeChangeMs = 0;

bool          ledState        = false;
unsigned long lastLedToggleMs = 0;

// ── Wi-Fi fallback state ────────────────────────────────────────────────────
// Credentials live in NVS (SETWIFI), never in this file. hasWifiCreds gates the
// whole fallback path — with no credentials the controller is wired-only, i.e.
// identical to Rev 3.0. wifiActive means the radio is currently switched on as
// the fallback; ethGotIpMs stamps the last time Ethernet lost its lease so the
// fallback only arms after ETH has been down for ETH_FALLBACK_MS.
String        wifiSsid;
String        wifiPass;
bool          hasWifiCreds     = false;
bool          wifiActive       = false;   // radio on as fallback
volatile bool wifiHasIp        = false;   // set/cleared from network events
unsigned long ethDownSinceMs   = 0;       // millis() when ETH last went link-down / lost IP (0 = ETH is up)
unsigned long lastWifiTryMs    = 0;

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

// ── Network (Ethernet primary, Wi-Fi fallback) ─────────────────────────────────
// esp_netif owns DHCP on both interfaces, including re-acquiring a lease when a
// link comes back. The events below are for serial logging and for tracking the
// Wi-Fi lease flag; the status LED and the OSC guards poll networkReady(), and
// all radio on/off switching happens in manageWifiFallback() (loop context) so
// no mode changes run inside an event callback.
//
// Only one interface ever carries traffic at a time: Ethernet is primary, and
// manageWifiFallback() shuts the Wi-Fi radio off the moment ETH has a lease, so
// the OSC senders never face an ambiguous default route.
bool networkReady() {
  return ETH.hasIP() || wifiHasIp;  // a usable link + lease on either interface
}

const char* activeInterface() {
  if (ETH.hasIP()) return "Ethernet";
  if (wifiHasIp)   return "Wi-Fi fallback";
  return "none";
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
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      wifiHasIp = true;
      Serial.printf("[WIFI] DHCP lease: %s (RSSI %d dBm)\n",
                    WiFi.localIP().toString().c_str(), (int)WiFi.RSSI());
      break;
    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
      wifiHasIp = false;
      Serial.println("[WIFI] Lost IP");
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      wifiHasIp = false;
      Serial.println("[WIFI] Disconnected");
      break;
    default:
      break;
  }
}

// Load stored credentials (if any) from the shared "playback" NVS namespace.
// Called at boot and after SETWIFI/RESETWIFI so hasWifiCreds stays current.
void loadWifiCreds() {
  wifiSsid = prefs.getString("wifi_ssid", "");
  wifiPass = prefs.getString("wifi_pass", "");
  hasWifiCreds = wifiSsid.length() > 0;
}

void stopWifiFallback(const char* reason) {
  if (!wifiActive) return;
  Serial.printf("[WIFI] %s — disabling Wi-Fi fallback\n", reason);
  WiFi.disconnect(true /*wifioff*/, false /*eraseap*/);
  WiFi.mode(WIFI_OFF);
  wifiActive = false;
  wifiHasIp  = false;
}

void startWifiFallback() {
  Serial.printf("[WIFI] Ethernet down > %lus — starting Wi-Fi fallback to SSID \"%s\"\n",
                (unsigned long)(ETH_FALLBACK_MS / 1000), wifiSsid.c_str());
  WiFi.persistent(false);        // we own the credentials in our own NVS keys
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(HOSTNAME);    // keep naodec-playback(.local) on the radio too
  WiFi.begin(wifiSsid.c_str(), wifiPass.c_str());
  wifiActive    = true;
  lastWifiTryMs = millis();
}

// Ethernet-primary failover. Ethernet always wins: whenever it holds a lease the
// radio is forced off. Only once Ethernet has been down continuously for
// ETH_FALLBACK_MS (and credentials exist) does the radio come up; while it is up
// but not yet associated, re-begin() every WIFI_RETRY_MS. Non-blocking — buttons
// and the encoder keep running throughout.
void manageWifiFallback() {
  unsigned long now = millis();

  if (ETH.hasIP()) {                 // Ethernet primary and healthy
    ethDownSinceMs = 0;
    stopWifiFallback("Ethernet restored");
    return;
  }

  // Ethernet is down. Track how long, whether or not credentials exist yet, so
  // that provisioning with SETWIFI after the cable has already been out engages
  // the fallback right away instead of restarting the grace window.
  if (ethDownSinceMs == 0) ethDownSinceMs = now;
  if (!hasWifiCreds) return;         // wired-only build — identical to Rev 3.0
  if (now - ethDownSinceMs < ETH_FALLBACK_MS) return;        // still in grace window

  if (!wifiActive) {
    startWifiFallback();
  } else if (!wifiHasIp && (now - lastWifiTryMs >= WIFI_RETRY_MS)) {
    Serial.println("[WIFI] Still not associated — retrying");
    WiFi.begin(wifiSsid.c_str(), wifiPass.c_str());
    lastWifiTryMs = now;
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
// Solid            = Ethernet link up with a DHCP lease (normal operation).
// Mostly-on, brief
//   off-blip / 2 s = running on Wi-Fi fallback (panel works, wired link needs
//                    attention).
// ~2 Hz blink      = no network on either interface.
// Off              = no power (or firmware fault).
void updateStatusLed() {
  if (ETH.hasIP()) {                        // Ethernet primary: solid on
    digitalWrite(PIN_STATUS_LED, HIGH);
    ledState = true;
    return;
  }
  if (wifiHasIp) {                          // Wi-Fi fallback: mostly-on, short off-blip
    unsigned long phase = millis() % LED_WIFI_PERIOD_MS;
    bool on = phase >= LED_WIFI_BLIP_MS;    // off only for the first blip of each period
    digitalWrite(PIN_STATUS_LED, on ? HIGH : LOW);
    ledState = on;
    return;
  }
  if (millis() - lastLedToggleMs >= LED_BLINK_MS) {   // no network: ~2 Hz blink
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
  Serial.printf("[STATUS] IP (ETH):   %s\n", ETH.localIP().toString().c_str());
  Serial.printf("[STATUS] MAC (ETH):  %s  <- key the router DHCP reservation to this\n",
                ETH.macAddress().c_str());
  Serial.printf("[STATUS] Active if:  %s\n", activeInterface());
  // Wi-Fi fallback block. The Wi-Fi MAC differs from the Ethernet MAC — if you
  // want the fallback to land on a fixed address too, add a second router
  // reservation (e.g. 192.168.50.115) keyed to this MAC.
  if (hasWifiCreds) {
    Serial.printf("[STATUS] Wi-Fi SSID: %s (password: set)\n", wifiSsid.c_str());
    Serial.printf("[STATUS] MAC (WiFi): %s\n", WiFi.macAddress().c_str());
    if (wifiHasIp) {
      Serial.printf("[STATUS] IP (WiFi):  %s (RSSI %d dBm)\n",
                    WiFi.localIP().toString().c_str(), (int)WiFi.RSSI());
    }
  } else {
    Serial.println("[STATUS] Wi-Fi SSID: (none stored — wired-only; SETWIFI to enable fallback)");
  }
  Serial.printf("[STATUS] Hostname:   %s (.local)\n", HOSTNAME);
  Serial.printf("[STATUS] OSC target: %s:%d\n", MAX_HOST, OSC_PORT);
  Serial.printf("[STATUS] Volume:     %d\n", volume);
  Serial.printf("[STATUS] Uptime:     %lu s\n", millis() / 1000);
  Serial.println("[STATUS] ----------------------------");
}

void handleSerialCommand(const char* cmd) {
  while (*cmd == ' ') cmd++;  // ltrim

  if (strncmp(cmd, "SETWIFI ", 8) == 0) {
    // SETWIFI <ssid> <password> — split at the FIRST space, so the password may
    // contain spaces but the SSID may not. Credentials go to NVS, never echoed
    // back and never committed to this file.
    const char* args = cmd + 8;
    while (*args == ' ') args++;             // tolerate extra spaces before the SSID
    const char* sep = strchr(args, ' ');
    if (sep == nullptr || sep == args) {
      Serial.println("[WARN] Usage: SETWIFI <ssid> <password>  (SSID must not contain spaces)");
      return;
    }
    String ssid = String(args).substring(0, sep - args);
    String pass = String(sep + 1);          // everything after the first space, verbatim
    if (pass.length() == 0) {
      Serial.println("[WARN] Usage: SETWIFI <ssid> <password>  (password missing)");
      return;
    }
    prefs.putString("wifi_ssid", ssid);
    prefs.putString("wifi_pass", pass);
    loadWifiCreds();
    Serial.printf("[WIFI] Stored SSID \"%s\" (password: set). Fallback %s.\n",
                  wifiSsid.c_str(),
                  ETH.hasIP() ? "will engage if Ethernet drops"
                              : "will engage shortly (Ethernet is down)");
  } else if (strcmp(cmd, "RESETWIFI") == 0) {
    prefs.remove("wifi_ssid");
    prefs.remove("wifi_pass");
    loadWifiCreds();
    stopWifiFallback("Credentials cleared");
    Serial.println("[WIFI] Cleared stored credentials — controller is now wired-only.");
  } else if (strcmp(cmd, "STATUS") == 0) {
    printStatus();
  } else if (strlen(cmd) > 0) {
    Serial.printf("[WARN] Unknown command: %s\n", cmd);
  }
}

void checkSerial() {
  static char buf[128];  // room for "SETWIFI " + 32-char SSID + space + 63-char WPA key
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
  Serial.printf("[BOOT] Firmware version %s (hardware Rev 3.0, W5500 Ethernet + Wi-Fi fallback)\n", FW_VERSION);
  Serial.println("[BOOT] Serial commands: STATUS, SETWIFI <ssid> <password>, RESETWIFI");

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

  loadWifiCreds();
  if (hasWifiCreds) {
    Serial.printf("[WIFI] Fallback armed for SSID \"%s\" (used only if Ethernet is down)\n",
                  wifiSsid.c_str());
  } else {
    Serial.println("[WIFI] No credentials stored — wired-only. SETWIFI to enable fallback.");
  }

  Network.onEvent(onNetworkEvent);
  WiFi.mode(WIFI_OFF);        // radio stays off until manageWifiFallback() needs it
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
  manageWifiFallback();
  updateStatusLed();
  updateButtons();
  updateEncoder();
  saveVolumeIfIdle();
}
