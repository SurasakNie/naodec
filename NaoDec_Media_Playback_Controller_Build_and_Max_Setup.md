# NaoDec Media Playback Controller Build and Max Setup

**Revision:** 1.0  
**Date:** 2026-07-01  
**Controller:** ESP32-S3 Wi-Fi OSC controller for Max/MSP media playback  
**Schematic:** `Media_Playback_Controller_Schematic_Rev1.0.html`

## 1. Purpose

This controller is a small operator panel for a Max/MSP media player. It does not carry audio, video, LED data, or LED power. It only sends control messages over Wi-Fi using OSC over UDP.

Functions:

| Control | Action in Max |
|---|---|
| Volume encoder | Sends `/volume <0.0...1.0>` |
| Play button | Sends `/transport/play 1` |
| Pause button | Sends `/transport/pause 1` |
| Stop button | Sends `/transport/stop 1` |

The Max computer should be connected to the ASUS router by wired Ethernet. The ESP32-S3 connects to the same LAN by 2.4 GHz Wi-Fi.

## 2. Required Items

| Ref | Qty | Item | Description |
|---|---:|---|---|
| U1 | 1 | ESP32-S3-DevKitC-1 | Main controller board, USB-C, N8R8 or N16R8 preferred |
| ENC1 | 1 | NEBDS-01 / EC11 encoder module | Preferred rotary encoder module with Schmitt trigger / anti-bounce, pins `A`, `B`, `SW`, `VCC`, `GND`; KY-040 may be used as an optional replacement |
| SW1-SW3 | 3 | Normally-open momentary pushbutton | Play, Pause, Stop panel buttons |
| R3-R5 | 3 | 10 kOhm resistor | Pull-ups for Play/Pause/Stop buttons |
| C3-C5 | 3 | 100 nF capacitor | Button debounce capacitors, X7R ceramic, 25 V or higher |
| J1 | 1 | USB-C cable | Power cable for ESP32-S3 board |
| PSU1 | 1 | USB power adapter | Regulated 5 V, 2 A wall adapter |
| PCB1 | 1 | Prototype PCB | 2.54 mm prototype PCB or custom PCB, approx. 70 x 50 mm |
| ENCLOSURE | 1 | Nonconductive enclosure | Plastic controller box with strain relief and ventilation |
| H1-H5 | 5 | 2-pin locking connectors | Optional removable front-panel connectors |
| W1 | 1 lot | Hookup wire | 24 AWG stranded wire, 7 colors, 300 V insulation or better |
| HW1 | 1 lot | Assembly hardware | Standoffs, M3 screws, encoder knob, labels, heat-shrink tubing |

Recommended spares:

| Item | Qty |
|---|---:|
| NEBDS-01 / EC11 encoder module, or KY-040 module for bench/prototype replacement | 1 |
| Momentary pushbutton | 1 |
| 10 kOhm resistor | 2 |
| 100 nF capacitor | 2 |

## 3. Pin Connections

### ESP32-S3 Pin Map

| Function | ESP32-S3 Pin | Wire Color | Notes |
|---|---|---|---|
| Encoder A | GPIO7 | Green | Connect to `ENC1 A` on NEBDS-01, or `CLK` on KY-040 |
| Encoder B | GPIO8 | Blue | Connect to `ENC1 B` on NEBDS-01, or `DT` on KY-040 |
| Play | GPIO9 | White | Button input, active low |
| Pause | GPIO10 | Yellow | Button input, active low |
| Stop | GPIO11 | Orange | Button input, active low |
| Encoder/module power | 3V3 | Red | Connect to `ENC1 VCC` on NEBDS-01, or `+` on KY-040 |
| Ground | GND | Black | Common ground for encoder and buttons |
| Power input | USB-C | USB cable | Use USB-C input path, not GPIO or 3V3 pin |

### Encoder Module: NEBDS-01 Preferred, KY-040 Optional

| Function | NEBDS-01 / EC11 Schmitt Pin | KY-040 Pin | ESP32-S3 Connection |
|---|---|---|---|
| Encoder channel A | `A` | `CLK` | GPIO7 |
| Encoder channel B | `B` | `DT` | GPIO8 |
| Encoder switch | `SW` | `SW` | Not connected in Rev 1.0 |
| Module power | `VCC` | `+` | ESP32 3V3 |
| Ground | `GND` | `GND` | ESP32 GND |

Do not add external 100 nF capacitors to encoder `A` or `B` when using this Schmitt trigger module. The original bare-encoder RC parts `R1`, `R2`, `C1`, and `C2` are not populated for this build.

KY-040 optional replacement notes:

| Topic | NEBDS-01 / EC11 Schmitt Module | KY-040 Optional Replacement |
|---|---|---|
| Signal conditioning | Schmitt trigger / anti-bounce output | Usually raw or lightly pulled-up mechanical encoder output |
| Wiring | `A -> GPIO7`, `B -> GPIO8`, `VCC -> 3V3`, `GND -> GND`, `SW -> NC` | `CLK -> GPIO7`, `DT -> GPIO8`, `+ -> 3V3`, `GND -> GND`, `SW -> NC` |
| External A/B RC parts | Do not populate `R1`, `R2`, `C1`, or `C2` | Leave `R1`, `R2`, `C1`, and `C2` unpopulated first; use firmware filtering and test rotation behavior |
| Firmware requirement | Normal quadrature validation | Stronger transition validation / debounce is recommended |
| Best use | Final installed controller | Bench test or replacement when NEBDS-01 is unavailable |

Power any module-style encoder from ESP32 `3V3`, not 5 V. If the KY-040 is powered from 5 V, its `CLK`, `DT`, or `SW` outputs may also pull up to 5 V, which is not safe for ESP32-S3 GPIO.

### Play / Pause / Stop Buttons

Each button is a normally-open switch from its GPIO input to ground.

| Button | GPIO | Pull-Up | Debounce Capacitor | Switch Wiring |
|---|---|---|---|---|
| Play | GPIO9 | R3, 10 kOhm to 3V3 | C3, 100 nF to GND | Button closes GPIO9 to GND |
| Pause | GPIO10 | R4, 10 kOhm to 3V3 | C4, 100 nF to GND | Button closes GPIO10 to GND |
| Stop | GPIO11 | R5, 10 kOhm to 3V3 | C5, 100 nF to GND | Button closes GPIO11 to GND |

## 4. Build Steps

1. Drill the enclosure for the encoder, three buttons, USB cable, and any service access.
2. Arrange controls left to right as `VOLUME`, `PLAY`, `PAUSE`, `STOP`.
3. Mount the ESP32-S3 board so the antenna end faces plastic, not metal.
4. Keep at least 10 mm clearance around the ESP32 antenna area.
5. Mount the NEBDS-01 / EC11 encoder module and fit the knob. If using the optional KY-040 module, mount it in the same volume encoder position.
6. Mount the three normally-open pushbuttons.
7. Build the 3.3 V and GND buses on the prototype PCB.
8. Install R3-R5 from 3.3 V to GPIO9/GPIO10/GPIO11.
9. Install C3-C5 from GPIO9/GPIO10/GPIO11 to GND.
10. Wire encoder `A`, `B`, `VCC`, and `GND` to the ESP32.
11. Leave encoder `SW` unconnected and insulated.
12. Wire each pushbutton between its GPIO input and GND.
13. Add strain relief for the USB-C cable.
14. Label both ends of every wire.
15. Inspect for solder bridges, loose strands, reversed connectors, and accidental contact near the antenna.

## 5. Electrical Checks Before Firmware

Perform these checks before plugging the controller into a computer or router setup.

| Check | Method | Pass Condition |
|---|---|---|
| Visual inspection | Inspect PCB and connectors | No shorts, loose strands, or unlabeled harnesses |
| Unpowered resistance | Measure 5 V-to-GND and 3.3 V-to-GND | No near-short |
| 3.3 V rail | Power by USB-C and measure 3V3 to GND | 3.20 V to 3.40 V |
| Encoder module VCC | Measure `ENC1 VCC` or KY-040 `+` to GND | 3.20 V to 3.40 V |
| Button idle voltage | Release Play/Pause/Stop and measure GPIO9-11 | Above 3.0 V |
| Button active voltage | Press each button and measure its GPIO | Below 0.3 V |
| Encoder A/B level | Rotate encoder and measure A/B, or KY-040 CLK/DT | Logic should stay within 0 V to 3.3 V |

Do not apply 5 V to GPIO7, GPIO8, GPIO9, GPIO10, GPIO11, or the encoder module signal pins.

## 6. Firmware Configuration

Store Wi-Fi and Max destination settings in a local config file that is excluded from Git.

Project network assignment:

| Device / Setting | Value |
|---|---|
| Media playback controller reserved IP | `192.168.50.114` |
| Max player computer IP | Confirm from the ASUS router setup |
| OSC UDP port | `9000` |

The controller IP `192.168.50.114` should normally be assigned by ASUS DHCP reservation using the ESP32 MAC address. `MAX_HOST` is different: it must be the IP address of the Max player computer that receives OSC.

```text
WIFI_SSID=<ASUS 2.4 GHz SSID>
WIFI_PASSWORD=<password>
MAX_HOST=<Max player computer IP>
MAX_OSC_PORT=9000
```

Firmware behavior required for Rev 1.0:

| Area | Requirement |
|---|---|
| Wi-Fi | Connect by DHCP and reconnect automatically after loss |
| Logging | Report assigned IP, Max host, and events over USB serial |
| Credentials | Never print the Wi-Fi password |
| Buttons | Send one OSC command on the debounced press edge only |
| Encoder | Decode valid quadrature transitions from GPIO7/GPIO8; apply stronger filtering if KY-040 is used |
| Volume | Maintain integer volume `0...100` |
| Volume step | Change volume by 2 percentage points per detent |
| OSC volume | Send normalized float `0.0...1.0` |
| Limits | Clamp volume between `0.0` and `1.0` |
| Memory | Save last volume after about 2 seconds of inactivity |
| Boot | Do not send Play, Pause, or Stop on boot |

## 7. OSC Message Contract

These OSC messages are the Rev 1.0 proposed contract. Confirm that the final Max patch uses the same addresses and UDP port before acceptance testing.

| Function | OSC Address | Argument | Example |
|---|---|---:|---|
| Play | `/transport/play` | integer `1` | `/transport/play 1` |
| Pause | `/transport/pause` | integer `1` | `/transport/pause 1` |
| Stop | `/transport/stop` | integer `1` | `/transport/stop 1` |
| Volume | `/volume` | float `0.0...1.0` | `/volume 0.65` |

Default UDP destination port: `9000`.

## 8. ASUS Router Setup

1. Enable a 2.4 GHz SSID.
2. Connect the Max computer to an ASUS LAN port by Ethernet.
3. Make sure the ESP32 Wi-Fi network and wired Max computer are on the same LAN or VLAN.
4. Disable wireless client isolation or AP isolation for this SSID.
5. Reserve a DHCP address for the Max computer.
6. Reserve the ESP32 media playback controller at `192.168.50.114`.
7. Record the final SSID, controller IP, Max IP, and UDP port.

Project addressing:

| Device | Example IP |
|---|---|
| Max computer | Confirm from ASUS router setup |
| Media playback controller | `192.168.50.114` |

Do not set `MAX_HOST` to `192.168.50.114`; that address belongs to the ESP32 controller. Set `MAX_HOST` to the Max player computer's IP.

## 9. Connect to Max/MSP

The Max computer receives OSC over UDP from the ESP32 controller. Use a receive chain like this:

```text
[udpreceive 9000]
       |
   [oscparse]
       |
[route transport volume]
```

Recommended routing:

```text
[route transport volume]
      |          |
      |          +--> volume float 0.0...1.0 -> clamp -> master gain
      |
      +--> [route play pause stop]
              |     |      |
              |     |      +--> stop and reset player
              |     +--------> pause player
              +--------------> start player
```

Map messages this way:

| Incoming Message | Max Action |
|---|---|
| `/transport/play 1` | Start or resume media playback |
| `/transport/pause 1` | Pause playback |
| `/transport/stop 1` | Stop playback and reset according to patch behavior |
| `/volume 0.0...1.0` | Clamp, then drive media-player master gain |

Keep media-player volume separate from NeoDDP global brightness. They may both use normalized values, but they control different things.

## 10. Max Test Patch Checklist

Before connecting to the real media player actions, test with prints first.

1. Add `[udpreceive 9000]`.
2. Connect it to `[oscparse]`.
3. Connect that to `[print OSC_IN]`.
4. Power the ESP32 controller.
5. Press Play once and confirm one `/transport/play 1` event.
6. Press Pause once and confirm one `/transport/pause 1` event.
7. Press Stop once and confirm one `/transport/stop 1` event.
8. Rotate the encoder clockwise and confirm volume increases.
9. Rotate the encoder counterclockwise and confirm volume decreases.
10. Only after the printed messages are correct, connect them to the player controls.

If Max receives nothing:

| Symptom | Check |
|---|---|
| No UDP messages | Confirm ESP32 `MAX_HOST` is the Max computer IP, not `192.168.50.114` |
| Wrong port | Confirm both firmware and Max use UDP `9000` |
| ESP32 not reachable | Confirm same LAN/VLAN and AP isolation disabled |
| Duplicate button messages | Increase firmware debounce or check switch wiring |
| Encoder direction reversed | Swap A/B wiring or reverse direction in firmware |
| Volume affects lights | The Max patch is mapped to NeoDDP brightness instead of media gain |

## 11. Acceptance Tests

Run these before calling the controller ready.

| ID | Test | Pass Condition |
|---|---|---|
| ELEC-01 | Visual inspection | No shorts, loose wires, or exposed conductors |
| ELEC-02 | 3.3 V rail | 3.20 V to 3.40 V |
| NET-01 | Wi-Fi join | Controller gets DHCP address `192.168.50.114` within 15 seconds |
| NET-02 | Max reachability | Max computer and ESP32 are on same LAN/VLAN |
| NET-03 | UDP receive | Max receives only on the configured IP and port |
| NET-04 | Reconnect | Controller reconnects after Wi-Fi/router interruption |
| FUNC-01 | Play | One press sends one play command |
| FUNC-02 | Pause | One press sends one pause command |
| FUNC-03 | Stop | One press sends one stop command |
| FUNC-04 | Held button | Holding button for 3 seconds sends no repeats |
| FUNC-05 | Volume clockwise | Ten detents increase by about 20 percentage points |
| FUNC-06 | Volume counterclockwise | Ten detents decrease by about 20 percentage points |
| FUNC-07 | Volume limits | Output remains clamped from `0.0` to `1.0` |
| FUNC-08 | Boot behavior | No Play, Pause, or Stop command on power-up |
| SYS-01 | Site range | Reliable control at final operator location |
| SYS-02 | Soak | Stable operation for 8 hours with no unintended command |

## 12. Commissioning Record

Fill this out for each built controller.

| Field | Value |
|---|---|
| Controller serial / asset ID | |
| ESP32-S3 board variant | |
| Firmware version / commit | |
| ASUS SSID | |
| Controller MAC address | |
| Controller reserved IP | `192.168.50.114` |
| Max computer IP | |
| OSC UDP port | |
| Max patch filename / revision | |
| PSU make / model | |
| Test date | |
| Tested by | |
| Result / open issues | |

## 13. Release Gate

The controller is ready for installation only when:

| Gate | Required Result |
|---|---|
| Electrical tests | Pass |
| Network tests | Pass |
| Max OSC contract | Confirmed against the actual Max patch |
| Functional tests | Pass |
| Site range test | Pass |
| Enclosure | Closed, labeled, strain-relieved, and free of exposed conductors |
| Documentation | Commissioning record complete |
