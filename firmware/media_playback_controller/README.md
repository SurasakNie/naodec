# Media Playback Controller Firmware

Arduino-IDE sketch for the NaoDec Media Playback Controller — an ESP32-S3-DevKitC-1
operator panel (rotary volume encoder + Play/Pause/Stop buttons + network status LED)
that sends OSC-over-UDP transport/volume commands to a Max/MSP patch. It carries no
audio, video, or LED data/power.

Firmware 3.x targets hardware **Rev 3.0**, which reaches the LAN over **wired
Ethernet** — U2, a WIZnet W5500 Lite SPI module — instead of Wi-Fi; see
[`NaoDec_Media_Playback_Controller_Rev3_Ethernet_Rationale.md`](../../NaoDec_Media_Playback_Controller_Rev3_Ethernet_Rationale.md)
for why. The firmware version tracks the schematic revision it targets
(FW 3.0.x ↔ Schematic Rev 3.0).

Full hardware assembly, wiring, network setup, and acceptance tests:
[`NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md`](../../NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md)
(Rev 3.0). Schematic: [`NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html`](../../NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html).

## Build requirements

- Arduino IDE with the **esp32 by Espressif Systems** board package **version
  3.0.0 or newer** (Boards Manager) — W5500 support lives in the core's `ETH.h`.
  If the build fails with `ETH_PHY_W5500` undeclared, the installed core is
  2.x; update it.
- **No third-party libraries.** (FW 1.x needed WiFiManager; it is no longer
  used and can be uninstalled.)
- Board setting: **ESP32S3 Dev Module**, matching the ESP32-S3-DevKitC-1 board
  (N8R8 or N16R8 per the Build doc BOM).

Command-line compile check, if you use arduino-cli:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc firmware/media_playback_controller
```

## Network setup (Ethernet / DHCP reservation)

There is nothing to provision on the board — no SSID, no password, no captive
portal. The controller DHCPs over the wired link and the router hands it its
reserved address.

1. Connect the W5500's RJ45 to an ASUS RT-AX1800HP LAN port with the ~6 m Cat6
   run (W2 in the Build doc BOM).
2. Flash the firmware, open the Serial Monitor at 115200 baud, and type
   `STATUS`. Copy the `MAC (ETH)` line. **The Ethernet MAC is not the same as
   the old Wi-Fi MAC** — a DHCP reservation created for FW 1.x will not match
   this interface.
3. On the router, under LAN → DHCP Server → Manually Assigned IP, replace the
   old Wi-Fi-MAC entry with the Ethernet MAC at `192.168.50.114` (the `.11x`
   convention from Build doc Section 8).
4. Replug the cable (or power-cycle). `STATUS` should now show
   `IP address: 192.168.50.114`; confirm with `ping 192.168.50.114` and
   `ping naodec-playback.local` (mDNS).

The board is safe to boot with the cable unplugged: the status LED blinks at
~2 Hz until link + DHCP lease, then goes solid. If the reservation is missing,
the panel still works (OSC is outbound-only) — it just leases a pool address
(`192.168.50.100`–`199`), visible via `STATUS`.

## Serial commands (USB, 115200 baud)

| Command | Effect |
|---|---|
| `STATUS` | Prints firmware version, Ethernet link state/speed, IP address, Ethernet MAC (for the DHCP reservation), hostname, OSC target, current volume, and uptime. |

`RESETWIFI` was removed in FW 3.x — a wired build has nothing to provision;
typing it prints a note saying so.

## Configuration

`MAX_HOST` (`192.168.50.2`) and `OSC_PORT` (`9000`) are `#define`s at the top of
the `.ino`, matching the network plan in Build doc Section 8. These aren't
secrets — they're already published in that document — and with Wi-Fi gone
there are no credentials anywhere in the sketch.

W5500 wiring is fixed by Schematic Rev 3.0 and mirrored by the `PIN_ETH_*`
defines:

| W5500 signal | ESP32-S3 GPIO |
|---|---|
| SCLK | 13 |
| MOSI | 14 |
| MISO | 15 |
| SCS (CS) | 16 |
| INT | 17 |
| RST | 18 |

`ETH_SPI_MHZ_W5500` (default 20 MHz) can be dropped to 10–16 if a jumper-wired
bench module shows SPI errors. If a bench build leaves INT unwired, polled mode
(`irq = -1`) requires esp32 core 3.1 or newer.

If the encoder direction comes out backwards on the bench (Build doc Section 9
troubleshooting table), flip `ENCODER_REVERSED` to `1` instead of re-wiring A/B.

If FUNC-05/06 show about half the expected step (ten detents move volume ~10
points instead of ~20), the fitted encoder emits two quadrature transitions per
detent rather than four — set `ENCODER_STEPS_PER_DETENT` to `2`.

## Status LED

| LED state | Meaning |
|---|---|
| Solid on | Ethernet link up with a DHCP lease — controller operational |
| Blinking ~2 Hz | No link or no lease (check cable, router port, DHCP) |
| Off | No power (or firmware fault) |

## Validating before installation

This firmware implements the behavior table in Build doc Section 6 and the OSC
contract in Section 7. Before calling a built unit ready, run the full
acceptance test list in Section 11 — the network tests are exercised with the
Ethernet cable (unplug/replug) rather than the router's Wi-Fi radio — and fill
out the Section 12 commissioning record, including the `FW_VERSION` string this
firmware prints at boot as the "Firmware version" field.
