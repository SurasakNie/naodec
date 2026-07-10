/*
 * aroma_controller_web.ino
 * Waveshare ESP32-S3-Relay-6CH — 4x JY-M27AO Atomizer Controller
 *
 * Control channels: HTTP GET / serves the web UI, browser sends via WebSocket
 *                   on port 81, Max MSP sends via UDP on port 4210.
 * All three entry points funnel into handleCommand() — one code path.
 *
 * Wi-Fi reset: type RESETWIFI in Serial Monitor (USB), or use the
 *              "Change WiFi Network" button in the web UI.
 *
 * New library required: "WebSockets" by Markus Sattler (Arduino Library Manager)
 */

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <WiFiManager.h>
#include <Adafruit_NeoPixel.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

// ── Hardware ──────────────────────────────────────────────────────────────────
#define RELAY_CH1     1
#define RELAY_CH2     2
#define RELAY_CH3    41
#define RELAY_CH4    42
#define LED_PIN      38
#define LED_COUNT     1

// ── Network ───────────────────────────────────────────────────────────────────
#define UDP_PORT   4210   // Max MSP — unchanged
#define HTTP_PORT    80
#define WS_PORT      81
#define HOSTNAME "aroma"  // resolves as aroma.local via mDNS

// ── Duration clamp (ms) ───────────────────────────────────────────────────────
#define DUR_MIN   1000
#define DUR_MAX  30000

// ── Globals ───────────────────────────────────────────────────────────────────
Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
WiFiUDP           udp;
WebServer         httpServer(HTTP_PORT);
WebSocketsServer  wsServer(WS_PORT);

static const int RELAY_PINS[4] = { RELAY_CH1, RELAY_CH2, RELAY_CH3, RELAY_CH4 };

int           activeChannel      = 0;
unsigned long scentStartMs       = 0;
unsigned long scentDurationMs    = 0;
bool          resetWifiRequested = false;  // set by RESETWIFI command, handled in loop()

// ── Embedded Web UI (PROGMEM) ─────────────────────────────────────────────────
static const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Aroma Controller</title>
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: #0f172a;
      color: #f1f5f9;
      font-family: Verdana, Geneva, Tahoma, sans-serif;
      min-height: 100vh;
      display: flex;
      align-items: flex-start;
      justify-content: center;
      padding: 16px;
    }

    @media (min-width: 600px) {
      body { align-items: center; padding: 32px 24px; }
    }

    .card {
      width: 100%;
      max-width: 480px;
      background: #1e293b;
      border-radius: 14px;
      padding: 22px 18px;
      border: 1px solid #334155;
    }

    @media (min-width: 600px) {
      .card { border-radius: 18px; padding: 32px 28px; }
    }

    .header {
      display: flex;
      align-items: center;
      justify-content: space-between;
      margin-bottom: 26px;
    }

    h1 {
      font-size: 0.9375rem;
      font-weight: 700;
      color: #f1f5f9;
      letter-spacing: 0.01em;
    }

    @media (min-width: 600px) {
      h1 { font-size: 1.0625rem; }
    }

    .ws-status {
      display: flex;
      align-items: center;
      gap: 6px;
      font-size: 0.625rem;
      color: #64748b;
    }

    .ws-dot {
      width: 7px;
      height: 7px;
      border-radius: 50%;
      background: #EF3340;
      transition: background 0.3s;
      flex-shrink: 0;
    }
    .ws-dot.on { background: #22c55e; }

    .section { margin-bottom: 20px; }

    .section-label {
      font-size: 0.5625rem;
      font-weight: 700;
      color: #64748b;
      text-transform: uppercase;
      letter-spacing: 0.09em;
      margin-bottom: 9px;
    }

    @media (min-width: 600px) {
      .section-label { font-size: 0.625rem; }
    }

    .ch-row {
      display: grid;
      grid-template-columns: repeat(4, 1fr);
      gap: 8px;
    }

    .ch-btn {
      padding: 0 6px;
      height: 48px;
      border-radius: 8px;
      border: 2px solid;
      background: transparent;
      font-family: Verdana, Geneva, Tahoma, sans-serif;
      font-size: 0.6875rem;
      font-weight: 700;
      cursor: pointer;
      transition: background 0.12s, color 0.12s;
      color: #94a3b8;
    }

    @media (min-width: 600px) {
      .ch-btn { height: 52px; font-size: 0.75rem; }
    }

    .ch-btn[data-ch="1"] { border-color: #10b981; }
    .ch-btn[data-ch="2"] { border-color: #3b82f6; }
    .ch-btn[data-ch="3"] { border-color: #ef4444; }
    .ch-btn[data-ch="4"] { border-color: #eab308; }

    .ch-btn[data-ch="1"].active { background: #10b981; color: #fff; }
    .ch-btn[data-ch="2"].active { background: #3b82f6; color: #fff; }
    .ch-btn[data-ch="3"].active { background: #ef4444; color: #fff; }
    .ch-btn[data-ch="4"].active { background: #eab308; color: #0f172a; }

    .dur-row {
      display: grid;
      grid-template-columns: repeat(5, 1fr);
      gap: 8px;
    }

    .dur-btn {
      height: 44px;
      border-radius: 6px;
      border: 1px solid #334155;
      background: transparent;
      font-family: Verdana, Geneva, Tahoma, sans-serif;
      font-size: 0.75rem;
      font-weight: 700;
      color: #64748b;
      cursor: pointer;
      transition: background 0.12s, color 0.12s, border-color 0.12s;
      text-align: center;
    }

    @media (min-width: 600px) {
      .dur-btn { height: 48px; font-size: 0.8125rem; }
    }

    .dur-btn.active {
      background: #334155;
      color: #f1f5f9;
      border-color: #475569;
    }

    .send-btn {
      width: 100%;
      height: 54px;
      border-radius: 8px;
      border: none;
      background: #334155;
      color: #f1f5f9;
      font-family: Verdana, Geneva, Tahoma, sans-serif;
      font-size: 0.9375rem;
      font-weight: 700;
      cursor: pointer;
      letter-spacing: 0.03em;
      transition: background 0.12s;
      margin-bottom: 10px;
    }

    @media (min-width: 600px) {
      .send-btn { height: 58px; font-size: 1rem; }
    }

    .send-btn:hover  { background: #475569; }
    .send-btn:active { transform: scale(0.99); }

    /* PANTONE Red 032 C */
    .stop-btn {
      width: 100%;
      height: 62px;
      border-radius: 8px;
      border: none;
      background: #EF3340;
      color: #ffffff;
      font-family: Verdana, Geneva, Tahoma, sans-serif;
      font-size: 1rem;
      font-weight: 700;
      cursor: pointer;
      letter-spacing: 0.18em;
      transition: background 0.12s;
    }

    @media (min-width: 600px) {
      .stop-btn { height: 68px; font-size: 1.0625rem; }
    }

    .stop-btn:hover  { background: #cc2b35; }
    .stop-btn:active { transform: scale(0.99); }

    .wifi-btn {
      display: block;
      width: 100%;
      margin-top: 10px;
      padding: 10px;
      border-radius: 6px;
      border: 1px solid #334155;
      background: transparent;
      color: #475569;
      font-family: Verdana, Geneva, Tahoma, sans-serif;
      font-size: 0.5625rem;
      cursor: pointer;
      transition: color 0.12s, border-color 0.12s;
      letter-spacing: 0.04em;
    }

    .wifi-btn:hover { color: #94a3b8; border-color: #475569; }
  </style>
</head>
<body>

<div class="card">

  <div class="header">
    <h1>Aroma Controller</h1>
    <div class="ws-status">
      <span class="ws-dot" id="wsDot"></span>
      <span id="wsText">disconnected</span>
    </div>
  </div>

  <div class="section">
    <div class="section-label">Scent Channel</div>
    <div class="ch-row">
      <button class="ch-btn active" data-ch="1">Green</button>
      <button class="ch-btn"        data-ch="2">Blue</button>
      <button class="ch-btn"        data-ch="3">Red</button>
      <button class="ch-btn"        data-ch="4">Yellow</button>
    </div>
  </div>

  <div class="section">
    <div class="section-label">Set Duration of scent dispersal</div>
    <div class="dur-row">
      <button class="dur-btn active" data-d="1">1</button>
      <button class="dur-btn"        data-d="2">2</button>
      <button class="dur-btn"        data-d="3">3</button>
      <button class="dur-btn"        data-d="4">4</button>
      <button class="dur-btn"        data-d="5">5</button>
      <button class="dur-btn"        data-d="6">6</button>
      <button class="dur-btn"        data-d="7">7</button>
      <button class="dur-btn"        data-d="8">8</button>
      <button class="dur-btn"        data-d="9">9</button>
      <button class="dur-btn"        data-d="10">10</button>
    </div>
  </div>

  <div class="section" style="margin-bottom:0">
    <button class="send-btn" id="sendBtn" onclick="sendScent()">SCENT 1&nbsp;&nbsp;&nbsp;1 sec</button>
    <button class="stop-btn" onclick="sendStop()">STOP</button>
    <button class="wifi-btn" onclick="resetWifi()">Change WiFi Network</button>
  </div>

</div>

<script>
  var ch = 1, dur = 1;
  var ws = null, reconnTimer = null;

  function connect() {
    ws = new WebSocket('ws://' + window.location.hostname + ':81');
    ws.onopen  = function() { setConn(true); };
    ws.onclose = function() {
      setConn(false);
      clearTimeout(reconnTimer);
      reconnTimer = setTimeout(connect, 2000);
    };
    ws.onerror = function() { ws.close(); };
  }

  function setConn(ok) {
    document.getElementById('wsDot').className = 'ws-dot' + (ok ? ' on' : '');
    document.getElementById('wsText').textContent = ok ? 'connected' : 'disconnected';
  }

  function sendScent() {
    if (ws && ws.readyState === 1) ws.send('SCENT ' + ch + ' ' + (dur * 1000));
  }

  function sendStop() {
    if (ws && ws.readyState === 1) ws.send('STOP');
  }

  function resetWifi() {
    if (!confirm('Clear saved WiFi and restart device?\nThe device will create a setup hotspot named "AromaController-Setup".')) return;
    if (ws && ws.readyState === 1) ws.send('RESETWIFI');
  }

  function updateLabel() {
    document.getElementById('sendBtn').innerHTML =
      'SCENT ' + ch + '&nbsp;&nbsp;&nbsp;' + dur + ' sec';
  }

  document.querySelectorAll('.ch-btn').forEach(function(b) {
    b.addEventListener('click', function() {
      document.querySelectorAll('.ch-btn').forEach(function(x) { x.classList.remove('active'); });
      b.classList.add('active');
      ch = +b.dataset.ch;
      updateLabel();
    });
  });

  document.querySelectorAll('.dur-btn').forEach(function(b) {
    b.addEventListener('click', function() {
      document.querySelectorAll('.dur-btn').forEach(function(x) { x.classList.remove('active'); });
      b.classList.add('active');
      dur = +b.dataset.d;
      updateLabel();
    });
  });

  connect();
</script>

</body>
</html>
)rawliteral";

// ── LED helpers ───────────────────────────────────────────────────────────────
void setLedColor(uint8_t r, uint8_t g, uint8_t b) {
  led.setPixelColor(0, led.Color(r, g, b));
  led.show();
}

void setLedOff() {
  led.clear();
  led.show();
}

void ledFlashWhite() {
  for (int i = 0; i < 3; i++) {
    setLedColor(255, 255, 255);
    delay(80);
    setLedOff();
    delay(80);
  }
}

// ── Relay helpers ─────────────────────────────────────────────────────────────
void setRelay(int ch, bool on) {
  if (ch < 1 || ch > 4) return;
  digitalWrite(RELAY_PINS[ch - 1], on ? HIGH : LOW);
}

void allRelaysOff() {
  for (int i = 0; i < 4; i++) digitalWrite(RELAY_PINS[i], LOW);
}

// ── Scent control ─────────────────────────────────────────────────────────────
void startScent(int ch, unsigned long durationMs) {
  if (durationMs < DUR_MIN) {
    Serial.printf("[WARN] Duration %lu ms clamped to %d ms\n", durationMs, DUR_MIN);
    durationMs = DUR_MIN;
  }
  if (durationMs > DUR_MAX) {
    Serial.printf("[WARN] Duration %lu ms clamped to %d ms\n", durationMs, DUR_MAX);
    durationMs = DUR_MAX;
  }

  if (activeChannel != 0) {
    setRelay(activeChannel, false);
    setLedOff();
    delay(50);  // relay settle
  }

  activeChannel   = ch;
  scentStartMs    = millis();
  scentDurationMs = durationMs;
  setRelay(ch, true);

  switch (ch) {
    case 1: setLedColor( 16, 185, 129); break;  // Green  #10b981
    case 2: setLedColor( 59, 130, 246); break;  // Blue   #3b82f6
    case 3: setLedColor(239,  68,  68); break;  // Red    #ef4444
    case 4: setLedColor(234, 179,   8); break;  // Yellow #eab308
  }

  Serial.printf("[SCENT] Channel %d ON for %lu ms\n", ch, durationMs);
}

void stopScent() {
  if (activeChannel == 0) return;
  Serial.printf("[SCENT] Channel %d OFF (stop)\n", activeChannel);
  setRelay(activeChannel, false);
  activeChannel   = 0;
  scentStartMs    = 0;
  scentDurationMs = 0;
  ledFlashWhite();
  setLedOff();
}

void updateRelays() {
  if (activeChannel == 0) return;
  if (millis() - scentStartMs >= scentDurationMs) {
    Serial.printf("[SCENT] Channel %d OFF (timeout)\n", activeChannel);
    setRelay(activeChannel, false);
    activeChannel = 0;
    setLedOff();
  }
}

// ── Command parser ────────────────────────────────────────────────────────────
void handleCommand(const char* cmd) {
  while (*cmd == ' ') cmd++;  // ltrim

  if (strncmp(cmd, "SCENT", 5) == 0) {
    int  ch  = 0;
    long dur = 0;
    if (sscanf(cmd + 5, " %d %ld", &ch, &dur) == 2) {
      if (ch < 1 || ch > 4) {
        Serial.printf("[WARN] Channel %d out of range, ignoring\n", ch);
        return;
      }
      startScent(ch, (unsigned long)dur);
    } else {
      Serial.printf("[WARN] Bad SCENT syntax: %s\n", cmd);
    }
  } else if (strncmp(cmd, "STOP", 4) == 0) {
    stopScent();
  } else if (strncmp(cmd, "RESETWIFI", 9) == 0) {
    Serial.println("[WIFI] Reset requested — clearing credentials, restarting...");
    resetWifiRequested = true;  // handled safely in loop(), not inside a callback
  } else {
    Serial.printf("[WARN] Unknown command: %s\n", cmd);
  }
}

// ── Serial input (USB) ────────────────────────────────────────────────────────
void checkSerial() {
  static char buf[32];
  static int  idx = 0;
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      if (idx > 0) {
        buf[idx] = '\0';
        handleCommand(buf);
        idx = 0;
      }
    } else if (idx < (int)sizeof(buf) - 1) {
      buf[idx++] = c;
    }
  }
}

// ── HTTP handlers ─────────────────────────────────────────────────────────────
void handleRoot() {
  httpServer.sendHeader("Cache-Control", "no-cache");
  httpServer.send_P(200, "text/html", INDEX_HTML);
}

void handleNotFound() {
  httpServer.send(404, "text/plain", "Not found");
}

// ── WebSocket handler ─────────────────────────────────────────────────────────
void onWsEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_TEXT) {
    payload[length] = '\0';  // library guarantees length+1 bytes for text frames
    Serial.printf("[WS]   Client %u: %s\n", num, (char*)payload);
    handleCommand((char*)payload);
  }
}

// ── setup ─────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Serial.println("\n[BOOT] Aroma Controller starting...");
  Serial.println("[BOOT] Serial commands: SCENT <ch> <ms>  |  STOP  |  RESETWIFI");

  for (int i = 0; i < 4; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], LOW);
  }

  led.begin();
  led.setBrightness(80);
  setLedOff();

  // WiFiManager runs its own WebServer during captive portal, tears it down
  // before autoConnect() returns — httpServer is added safely after this point.
  WiFiManager wm;
  wm.setHostname(HOSTNAME);
  if (!wm.autoConnect("AromaController-Setup")) {
    Serial.println("[ERROR] WiFiManager failed, restarting...");
    ESP.restart();
  }
  Serial.printf("[WIFI] Connected. IP: %s\n", WiFi.localIP().toString().c_str());

  if (MDNS.begin(HOSTNAME)) {
    MDNS.addService("http", "tcp", HTTP_PORT);
    Serial.println("[mDNS] aroma.local ready");
  }

  udp.begin(UDP_PORT);
  Serial.printf("[UDP]  Listening on port %d\n", UDP_PORT);

  httpServer.on("/", handleRoot);
  httpServer.onNotFound(handleNotFound);
  httpServer.begin();
  Serial.printf("[HTTP] Server on port %d\n", HTTP_PORT);

  wsServer.begin();
  wsServer.onEvent(onWsEvent);
  Serial.printf("[WS]   Server on port %d\n", WS_PORT);

  Serial.println("[BOOT] Ready.");
}

// ── loop ──────────────────────────────────────────────────────────────────────
void loop() {
  checkSerial();
  httpServer.handleClient();
  wsServer.loop();

  // Deferred WiFi reset — executed here rather than inside a WS/serial callback
  // to avoid restarting while the network stack is mid-operation.
  if (resetWifiRequested) {
    allRelaysOff();
    setLedOff();
    WiFiManager wm;
    wm.resetSettings();
    delay(200);
    ESP.restart();
  }

  int packetSize = udp.parsePacket();
  if (packetSize > 0) {
    char buf[64];
    int len = udp.read(buf, sizeof(buf) - 1);
    if (len > 0) {
      buf[len] = '\0';
      Serial.printf("[UDP]  Received: %s\n", buf);
      handleCommand(buf);
    }
  }

  updateRelays();
}
