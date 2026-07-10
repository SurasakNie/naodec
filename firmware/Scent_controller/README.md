# Scent Controller Firmware

Arduino-IDE sketch for the NaoDec Scent Controller — a **Waveshare
ESP32-S3-Relay-6CH** board driving **4× JY-M27AO atomizers** over its onboard
relays. Each relay switches one atomizer on for a bounded duration to disperse a
scent, then turns it off. The board carries no audio, video, or LED
data/power — it is scent-only.

The sketch is `Scent_controller_web_R2.0.ino` (firmware **R2.0**). It presents a
built-in mobile-friendly web UI and accepts the same commands from three
independent entry points, all funnelled through a single `handleCommand()` code
path:

- **Web UI (HTTP, port 80)** — `http://aroma.local/` (or the board's IP) serves
  a self-contained page; the browser then talks to the board over a **WebSocket
  on port 81**. No files to host, everything is embedded in PROGMEM.
- **Max/MSP (UDP, port 4210)** — send a plain-text command as a UDP packet for
  show integration, unchanged from the earlier build.
- **Serial (USB, 115200 baud)** — type commands directly in the Serial Monitor.

## Build requirements

- Arduino IDE with the **esp32 by Espressif Systems** board package (Boards
  Manager). Select board **ESP32S3 Dev Module** for the Waveshare
  ESP32-S3-Relay-6CH.
- Libraries (Arduino Library Manager):
  - **WebSockets** by Markus Sattler — `WebSocketsServer.h`
  - **WiFiManager** by tzapu — captive-portal Wi-Fi provisioning
  - **Adafruit NeoPixel** — onboard status LED
  - `WiFi.h`, `WiFiUdp.h`, `ESPmDNS.h`, `WebServer.h` ship with the esp32 core.

Command-line compile check, if you use arduino-cli:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3 firmware/Scent_controller
```

## Wi-Fi setup (captive portal)

There are no credentials in the sketch. On first boot (or after a Wi-Fi reset)
the board brings up a **`AromaController-Setup`** hotspot via WiFiManager:

1. Join the `AromaController-Setup` Wi-Fi network from a phone or laptop; the
   captive portal opens automatically.
2. Pick your network and enter the password. Credentials are saved to flash and
   reused on every subsequent boot.
3. Once connected, the board registers mDNS and is reachable at
   **`http://aroma.local/`** (see the Serial Monitor for the assigned IP if the
   `.local` name does not resolve on your network).

To clear the stored network and re-provision, either type `RESETWIFI` in the
Serial Monitor or tap **Change WiFi Network** in the web UI — the board wipes
its credentials, turns everything off, and restarts back into the
`AromaController-Setup` hotspot.

## Commands

The same three commands work from the web UI, UDP, and Serial:

| Command | Effect |
|---|---|
| `SCENT <ch> <ms>` | Turn on atomizer channel `<ch>` (1–4) for `<ms>` milliseconds, then off automatically. Starting a new channel stops any active one first. |
| `STOP` | Immediately stop the active channel (LED flashes white to confirm). |
| `RESETWIFI` | Clear stored Wi-Fi credentials and restart into the setup hotspot. |

**Duration is clamped to 1000–30000 ms** (1–30 s); values outside that range are
pulled to the nearest bound and a warning is logged to Serial. Channel numbers
outside 1–4 are rejected. Only one channel runs at a time.

The web UI exposes channels 1–4 and duration presets of 1–10 s; it sends the
selected duration as milliseconds over the WebSocket.

## Hardware / pin map

Relay channels and the status LED are fixed by the Waveshare board and mirrored
by the `#define`s at the top of the `.ino`:

| Channel | Board relay | ESP32-S3 GPIO | UI color | LED color |
|---|---|---|---|---|
| CH1 | Relay 1 | GPIO1 | Green | `#10b981` |
| CH2 | Relay 2 | GPIO2 | Blue | `#3b82f6` |
| CH3 | Relay 3 | GPIO41 | Red | `#ef4444` |
| CH4 | Relay 4 | GPIO42 | Yellow | `#eab308` |
| — | Onboard NeoPixel | GPIO38 | — | status |

The onboard NeoPixel shows the active channel's color while it is dispersing,
flashes white on `STOP`, and is off when idle.

## Network configuration

The network ports and hostname are `#define`s at the top of the sketch and are
not secrets:

| Setting | Value | Notes |
|---|---|---|
| `HOSTNAME` | `aroma` | resolves as `aroma.local` via mDNS |
| `HTTP_PORT` | `80` | web UI |
| `WS_PORT` | `81` | WebSocket control channel |
| `UDP_PORT` | `4210` | Max/MSP command input |
| `DUR_MIN` / `DUR_MAX` | `1000` / `30000` | duration clamp (ms) |

Wi-Fi credentials are the only secret and are never in the sketch — WiFiManager
stores them in flash at runtime, so nothing sensitive is committed to this
(public) repo.
