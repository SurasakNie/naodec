# Media Playback Controller Firmware

Arduino-IDE sketch for the NaoDec Media Playback Controller — an ESP32-S3-DevKitC-1
operator panel (rotary volume encoder + Play/Pause/Stop buttons + Wi-Fi status LED)
that sends OSC-over-UDP transport/volume commands to a Max/MSP patch. It carries no
audio, video, or LED data/power.

Full hardware assembly, wiring, network setup, and acceptance tests:
[`NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md`](../../NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md)
(Rev 2.2). Schematic: [`NaoDec_Media_Playback_Controller_Schematic_Rev2.0.html`](../../NaoDec_Media_Playback_Controller_Schematic_Rev2.0.html).

## Build requirements

- Arduino IDE with the **esp32 by Espressif Systems** board package installed
  (Boards Manager).
- Library: **WiFiManager** by tzapu (Library Manager) — no other third-party
  libraries are required. Wi-Fi credentials and the Max/MSP OSC contract are
  handled without any external OSC library.
- Board setting: **ESP32S3 Dev Module**, matching the ESP32-S3-DevKitC-1 board
  (N8R8 or N16R8 per the Build doc BOM).

## First boot / Wi-Fi provisioning

The firmware never has a Wi-Fi SSID or password compiled in. On first boot (or
after a `RESETWIFI`), it opens a captive portal:

1. Power the board. It creates a Wi-Fi access point named `NaoDecPlayback-Setup`.
2. From a phone or laptop, connect to that AP and follow the captive portal
   page to pick `ASUS_NAODEC` and enter its password.
3. The board reboots, joins the LAN, and should receive its DHCP reservation
   at `192.168.50.114` per the Build doc's `.11x` addressing convention
   (Section 8) — confirm the reservation is set up on the router first.

## Serial commands (USB, 115200 baud)

| Command | Effect |
|---|---|
| `RESETWIFI` | Clears saved Wi-Fi credentials and restarts into the captive portal. |
| `STATUS` | Prints Wi-Fi state, IP address, current volume, and uptime. |

## Configuration

`MAX_HOST` (`192.168.50.2`) and `OSC_PORT` (`9000`) are `#define`s at the top of
the `.ino`, matching the network plan in Build doc Section 8. These aren't
secrets — they're already published in that document — so there's no separate
config file to keep out of Git; only the Wi-Fi password is kept out of source,
via WiFiManager.

If the encoder direction comes out backwards on the bench (Build doc Section 9
troubleshooting table), flip `ENCODER_REVERSED` to `1` instead of re-wiring A/B.

## Validating before installation

This firmware implements the behavior table in Build doc Section 6 and the OSC
contract in Section 7. Before calling a built unit ready, run the full
acceptance test list in Section 11 (electrical, network, functional, and soak
tests) and fill out the Section 12 commissioning record — include the
`FW_VERSION` string this firmware prints at boot as the "Firmware version"
field.
