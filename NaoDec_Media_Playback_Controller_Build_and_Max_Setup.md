# NaoDec Media Playback Controller Build and Max Setup

**Revision:** 3.1  
**Date:** 2026-07-10  
**Controller:** ESP32-S3 wired-Ethernet (W5500) OSC controller for Max/MSP media playback  
**Schematic:** `NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html`

> Rev 3.1 — Added a Quick Reference table ahead of Section 1: all four OSC addresses
> (including `/volume` for the encoder — not just the transport switches), mDNS
> hostname, UDP port, Max host IP, and the controller's reserved IP. Also aligned
> Section 6 with firmware 3.1.0 (optional Wi-Fi fallback provisioned over USB serial
> with `SETWIFI`; Ethernet remains primary and wins whenever its link returns).
> Documentation only — hardware is unchanged at Rev 3.0.
>
> Rev 3.0 — Wired-Ethernet migration, matching Schematic Rev 3.0: added U2 (WIZnet
> W5500 Lite Ethernet module, SPI on GPIO13–18), C6 (100 nF decoupling at U2), and
> W2 (~6 m Cat6 to the ASUS LAN port). Firmware 3.0.0 swaps the network layer from
> Wi-Fi to the W5500 — same OSC/UDP contract and IP scheme — and drops Wi-Fi
> provisioning entirely (no credentials anywhere; DHCP reservation is keyed to the
> Ethernet MAC printed by the `STATUS` serial command). See
> `NaoDec_Media_Playback_Controller_Rev3_Ethernet_Rationale.md` for why.
>
> Rev 2.2 — Added an "R1/R2/C1/C2 Fallback (Troubleshooting Reference)" note under the
> encoder section: build with those four parts unpopulated, and only fit them
> (10 kOhm / 100 nF, matching the button RC values) if the KY-040 shows encoder misreads
> that firmware filtering alone doesn't resolve.
>
> Rev 2.1 — Added an explicit placement requirement: U1 and its support PCB must be
> mounted inside the operator panel enclosure, not staged near the router or any other
> remote equipment. See Section 1.
>
> Rev 2.0 — Design hardening: LED1 Wi-Fi status indicator (GPIO12 via R11 330 Ω),
> R6–R10 100 Ω series protection on every off-board GPIO line, H1 keyed JST-XH 5-pin
> encoder connector, encoder shaft-to-GND continuity check, USB-C cable spec ≤ 1 m.
> Also folds in the KY-040 optional encoder-replacement documentation. Rev 1.0
> schematic remains in the repo for reference.
>
> Rev 1.1 — Sections 6 and 8 aligned with the real ASUS RT-AX1800HP LAN: Max host
> `192.168.50.2`, controller reserved at `192.168.50.114` per the `.11x` convention.

## Quick Reference

| Item | Value |
|---|---|
| Play button OSC | `/transport/play 1` (integer) |
| Pause button OSC | `/transport/pause 1` (integer) |
| Stop button OSC | `/transport/stop 1` (integer) |
| Volume encoder OSC | `/volume <float 0.0–1.0>` — e.g. `/volume 0.65` |
| mDNS hostname | `naodec-playback.local` |
| OSC UDP port | `9000` |
| OSC destination (Max computer) | `192.168.50.2` |
| Controller reserved IP (DHCP) | `192.168.50.114` |

## 1. Purpose

This controller is a small operator panel for a Max/MSP media player. It does not carry audio, video, LED data, or LED power. It only sends control messages over wired Ethernet using OSC over UDP.

Functions:

| Control | Action in Max |
|---|---|
| Volume encoder | Sends `/volume <0.0...1.0>` |
| Play button | Sends `/transport/play 1` |
| Pause button | Sends `/transport/pause 1` |
| Stop button | Sends `/transport/stop 1` |

The Max computer should be connected to the ASUS router by wired Ethernet. The ESP32-S3 joins the same LAN by wired Ethernet too, through U2 — a WIZnet W5500 Lite SPI module — and the ~6 m Cat6 run (W2). Rev 3.0 replaced the original 2.4 GHz Wi-Fi link because the router sits inside a metal ATX case that attenuates its radio; see `NaoDec_Media_Playback_Controller_Rev3_Ethernet_Rationale.md`.

### Placement Requirement

**U1 (the ESP32-S3) and its support PCB must be mounted inside the operator panel enclosure**, next to the encoder and buttons it drives. Do not place U1 near the router, the Mac Mini, or any other equipment and run long wires out to a separate panel.

The wire schedule in the schematic specifies a maximum run of about 0.5 m for every panel signal (encoder A/B, Play/Pause/Stop, status LED). These are unbuffered 3.3 V logic lines: a switch-to-GND button line or a quadrature encoder line stretched to several meters acts as a noise antenna, and R6-R10 (100 Ohm) only provide ESD/ringing protection for short runs, not EMI immunity over distance. Extending these runs to meters of cable, especially near a Wi-Fi router or switching power supplies, risks phantom button presses, missed presses, and misread encoder detents.

There is no benefit to placing U1 near the router: the *long* leg of the signal path (to the router and on to the Max computer) is exactly what the W2 Cat6 run is for. Ethernet is engineered for 100 m, so ~6 m is trivial, while the unbuffered panel signals are rated for ~0.5 m. Keep U1 (and U2) at the panel, keep the encoder/button/LED runs short, and let the Cat6 carry the distance; only the USB-C power cable and the Ethernet cable arrive at the panel location.

If a project constraint truly requires the microcontroller to sit apart from the panel by more than about 0.5 m, that is a different design (a remote I/O interconnect over UART/RS-485 or a buffered I2C expander) and is out of scope for this hardware.

## 2. Required Items

| Ref | Qty | Item | Description |
|---|---:|---|---|
| U1 | 1 | ESP32-S3-DevKitC-1 | Main controller board, USB-C, N8R8 or N16R8 preferred |
| U2 | 1 | WIZnet W5500 Lite Ethernet module | SPI Ethernet (10/100) with RJ45 magnetics. **3.3 V only — never 5 V**; ~150 mA from the ESP32 3V3 rail |
| ENC1 | 1 | NEBDS-01 / EC11 encoder module | Preferred rotary encoder module with Schmitt trigger / anti-bounce, pins `A`, `B`, `SW`, `VCC`, `GND`; KY-040 may be used as an optional replacement |
| SW1-SW3 | 3 | Normally-open momentary pushbutton | Play, Pause, Stop panel buttons |
| R3-R5 | 3 | 10 kOhm resistor | Pull-ups for Play/Pause/Stop buttons |
| R6-R10 | 5 | 100 Ohm resistor | Series protection between each GPIO and its panel wire (ESD / short protection, edge damping) |
| R11 | 1 | 330 Ohm resistor | Series resistor for LED1 status LED |
| LED1 | 1 | Panel-mount LED, 3-5 mm | Network status indicator on the operator panel |
| C3-C5 | 3 | 100 nF capacitor | Button debounce capacitors, X7R ceramic, 25 V or higher |
| C6 | 1 | 100 nF capacitor | Decoupling at U2's 3V3/GND pins, X7R ceramic, 25 V or higher, placed close to the module |
| J1 | 1 | USB-C cable | Power cable for ESP32-S3 board, quality cable, 1 m or shorter |
| W2 | 1 | Cat6 Ethernet cable, ~6 m | U2 RJ45 → ASUS RT-AX1800HP LAN port. Cat5e is sufficient; Cat8 is unnecessary (the W5500 is 10/100) |
| PSU1 | 1 | USB power adapter | Regulated 5 V, 2 A wall adapter |
| PCB1 | 1 | Prototype PCB | 2.54 mm prototype PCB or custom PCB, approx. 70 x 50 mm |
| ENCLOSURE | 1 | Nonconductive enclosure | Plastic controller box with strain relief and ventilation |
| H1 | 1 | JST-XH 5-pin connector set | Keyed connector for the encoder harness (mis-plug-proof) |
| H2-H5 | 4 | 2-pin locking connectors | Front-panel connectors for buttons and LED1 |
| W1 | 1 lot | Hookup wire | 24 AWG stranded wire, 7 colors, 300 V insulation or better |
| HW1 | 1 lot | Assembly hardware | Standoffs, M3 screws, encoder knob, labels, heat-shrink tubing |

Recommended spares:

| Item | Qty |
|---|---:|
| NEBDS-01 / EC11 encoder module, or KY-040 module for bench/prototype replacement | 1 |
| Momentary pushbutton | 1 |
| 10 kOhm resistor | 2 |
| 100 Ohm resistor | 2 |
| 100 nF capacitor | 2 |
| Panel-mount LED | 1 |

## 3. Pin Connections

### ESP32-S3 Pin Map

| Function | ESP32-S3 Pin | Wire Color | Notes |
|---|---|---|---|
| Encoder A | GPIO7 | Green | To `ENC1 A` (or `CLK` on KY-040) through R6 (100 Ohm) |
| Encoder B | GPIO8 | Blue | To `ENC1 B` (or `DT` on KY-040) through R7 (100 Ohm) |
| Play | GPIO9 | White | Button input, active low, through R8 (100 Ohm) |
| Pause | GPIO10 | Yellow | Button input, active low, through R9 (100 Ohm) |
| Stop | GPIO11 | Orange | Button input, active low, through R10 (100 Ohm) |
| Status LED | GPIO12 | Grey | To LED1 anode through R11 (330 Ohm), active high |
| W5500 SCLK | GPIO13 | — (SPI harness) | To `U2 SCLK` |
| W5500 MOSI | GPIO14 | — (SPI harness) | To `U2 MOSI` |
| W5500 MISO | GPIO15 | — (SPI harness) | To `U2 MISO` |
| W5500 SCS | GPIO16 | — (SPI harness) | To `U2 SCS` (chip select) |
| W5500 INT | GPIO17 | — (SPI harness) | To `U2 INT` |
| W5500 RST | GPIO18 | — (SPI harness) | To `U2 RST` |
| Encoder/module power | 3V3 | Red | Connect to `ENC1 VCC` on NEBDS-01, or `+` on KY-040; also feeds `U2 3V3` |
| Ground | GND | Black | Common ground for encoder, buttons, LED1, and U2 |
| Power input | USB-C | USB cable | Use USB-C input path, not GPIO or 3V3 pin |

Every signal that leaves the PCB (GPIO7-GPIO11) passes through a 100 Ohm series resistor
(R6-R10) mounted on the PCB, close to the ESP32. These protect the GPIOs against ESD and
wiring shorts and damp reflections on the panel runs, regardless of which encoder module is fitted.
The U2 SPI harness stays on the PCB (no panel run), so it has no series resistors — keep it
short instead (under ~0.1 m).

### W5500 Ethernet Module (U2)

| U2 pin | ESP32-S3 connection | Note |
|---|---|---|
| SCLK | GPIO13 | SPI clock |
| MOSI | GPIO14 | SPI data, ESP32 → W5500 |
| MISO | GPIO15 | SPI data, W5500 → ESP32 |
| SCS | GPIO16 | SPI chip select |
| INT | GPIO17 | Interrupt (wired in this build; firmware also supports polling on esp32 core >= 3.1 if a bench module lacks it) |
| RST | GPIO18 | Reset — pulsed by the firmware's Ethernet driver at boot |
| 3V3 | 3V3 | **3.3 V only — never 5 V.** Decouple with C6 (100 nF) directly at these pins |
| GND | GND | Common ground |
| RJ45 | — | W2 Cat6 → ASUS RT-AX1800HP LAN port |

The W5500 carries its own MAC/PHY and TCP/IP offload; the ESP32-S3 has no built-in
Ethernet MAC, which is why this SPI module is required for a wired link.

### Encoder Module: NEBDS-01 Preferred, KY-040 Optional

| Function | NEBDS-01 / EC11 Schmitt Pin | KY-040 Pin | ESP32-S3 Connection |
|---|---|---|---|
| Encoder channel A | `A` | `CLK` | GPIO7 via R6 (100 Ohm) |
| Encoder channel B | `B` | `DT` | GPIO8 via R7 (100 Ohm) |
| Encoder switch | `SW` | `SW` | Not connected |
| Module power | `VCC` | `+` | ESP32 3V3 |
| Ground | `GND` | `GND` | ESP32 GND |

The encoder harness terminates in `H1`, a keyed JST-XH 5-pin connector (A, B, VCC, GND,
plus one spare position for `SW`). A single keyed connector makes it impossible to swap
power against signal pins at reassembly.

Do not add external 100 nF capacitors to encoder `A` or `B` when using this Schmitt trigger module. The original bare-encoder RC parts `R1`, `R2`, `C1`, and `C2` are not populated for this build.

KY-040 optional replacement notes:

| Topic | NEBDS-01 / EC11 Schmitt Module | KY-040 Optional Replacement |
|---|---|---|
| Signal conditioning | Schmitt trigger / anti-bounce output | Usually raw or lightly pulled-up mechanical encoder output |
| Wiring | `A -> R6 -> GPIO7`, `B -> R7 -> GPIO8`, `VCC -> 3V3`, `GND -> GND`, `SW -> NC` | `CLK -> R6 -> GPIO7`, `DT -> R7 -> GPIO8`, `+ -> 3V3`, `GND -> GND`, `SW -> NC` |
| External A/B RC parts | Do not populate `R1`, `R2`, `C1`, or `C2` | Leave `R1`, `R2`, `C1`, and `C2` unpopulated first; use firmware filtering and test rotation behavior |
| Firmware requirement | Normal quadrature validation | Stronger transition validation / debounce is recommended |
| Best use | Final installed controller | Bench test or replacement when NEBDS-01 is unavailable |

Power any module-style encoder from ESP32 `3V3`, not 5 V. If the KY-040 is powered from 5 V, its `CLK`, `DT`, or `SW` outputs may also pull up to 5 V, which is not safe for ESP32-S3 GPIO. R6/R7 (100 Ohm) apply to either module and do not substitute for using the correct 3.3 V supply.

The NEBDS-01 / EC11's metal frame and shaft normally ground through the module mounting
pins. After mounting, verify continuity from the encoder shaft to GND — the knob is the
most-touched, most ESD-exposed part of a plastic enclosure. Most KY-040 breakout boards use
a plastic shaft with no frame ground path; this check applies only if the fitted module has
a metal shaft or frame.

### R1 / R2 / C1 / C2 Fallback (Troubleshooting Reference)

Build the controller with `R1`, `R2`, `C1`, and `C2` unpopulated. Do not fit them by default,
with either encoder module.

Only revisit this if you observe encoder misreads in testing: the volume jumps by more than
one step per detent, skips steps, or reads the wrong direction intermittently. This is a
symptom of unfiltered mechanical contact bounce that firmware filtering alone did not fully
clean up, and it is only expected with the KY-040 (bare mechanical contacts). It should not
happen with the NEBDS-01 (Schmitt trigger conditioning is already onboard).

| Module | Default | If encoder misreads occur |
|---|---|---|
| NEBDS-01 / EC11 | `R1`/`R2`/`C1`/`C2` unpopulated | Do not populate — the module's onboard Schmitt trigger already conditions the signal. Look for a wiring or grounding fault instead. |
| KY-040 | `R1`/`R2`/`C1`/`C2` unpopulated; rely on firmware filtering first | Populate `R1` = `R2` = 10 kOhm (to 3V3) and `C1` = `C2` = 100 nF (to GND) — the same values as `R3`-`R5`/`C3`-`C5` on the buttons, giving the same ~1 ms RC debounce constant |

### Play / Pause / Stop Buttons

Each button is a normally-open switch from its GPIO input to ground.

| Button | GPIO | Pull-Up | Debounce Capacitor | Series Resistor | Switch Wiring |
|---|---|---|---|---|---|
| Play | GPIO9 | R3, 10 kOhm to 3V3 | C3, 100 nF to GND | R8, 100 Ohm | Button closes the line to GND |
| Pause | GPIO10 | R4, 10 kOhm to 3V3 | C4, 100 nF to GND | R9, 100 Ohm | Button closes the line to GND |
| Stop | GPIO11 | R5, 10 kOhm to 3V3 | C5, 100 nF to GND | R10, 100 Ohm | Button closes the line to GND |

The pull-up and debounce capacitor sit at the GPIO node on the PCB; the 100 Ohm series
resistor sits between that node and the panel wire to the button.

### Status LED (LED1)

| Item | Connection |
|---|---|
| LED1 anode | GPIO12 through R11 (330 Ohm), active high |
| LED1 cathode | GND (operator-panel ground return) |
| Drive current | ~4 mA from the 3.3 V GPIO — safe for any GPIO, bright enough indoors |

| LED state | Meaning |
|---|---|
| Solid on | Ethernet link up with a DHCP lease, controller operational |
| Blinking | No link or no lease (cable unplugged, router port down, DHCP pending) |
| Off | No power (or firmware fault) |

## 4. Build Steps

1. Drill the enclosure for the encoder, three buttons, the status LED, the USB cable, the Cat6 cable (or a panel-mount RJ45 coupler), and any service access.
2. Arrange controls left to right as `VOLUME`, `PLAY`, `PAUSE`, `STOP`, with `LED1` visible from the operator position.
3. Mount the ESP32-S3 board inside this same enclosure. Do not mount U1 in a separate location and run extension wires to the panel (see Section 1, Placement Requirement).
4. Mount U2 (W5500 Lite) beside U1 with its RJ45 facing the cable exit, and keep the planned SPI harness short (under ~0.1 m).
5. Mount the NEBDS-01 / EC11 encoder module and fit the knob. If using the optional KY-040 module, mount it in the same volume encoder position.
6. Mount the three normally-open pushbuttons and LED1.
7. Build the 3.3 V and GND buses on the prototype PCB.
8. Install R3-R5 from 3.3 V to GPIO9/GPIO10/GPIO11.
9. Install C3-C5 from GPIO9/GPIO10/GPIO11 to GND.
10. Install the series resistors on the PCB, close to the ESP32: R6-R10 (100 Ohm) in line with GPIO7-GPIO11, and R11 (330 Ohm) in line with GPIO12.
11. Install C6 (100 nF) directly across U2's `3V3` and `GND` pins.
12. Wire the U2 SPI harness: `SCLK`→GPIO13, `MOSI`→GPIO14, `MISO`→GPIO15, `SCS`→GPIO16, `INT`→GPIO17, `RST`→GPIO18, plus `3V3` and `GND` from the PCB buses. **3.3 V only — never wire U2 to 5 V.**
13. Wire encoder `A`, `B`, `VCC`, and `GND` to the ESP32 through the keyed H1 JST-XH connector.
14. Leave encoder `SW` unconnected and insulated (route it to the spare H1 position if you want it available later).
15. Wire each pushbutton between its series resistor output and GND.
16. Wire LED1 anode to the R11 output and LED1 cathode to GND.
17. Verify continuity from the encoder shaft/frame to GND after mounting.
18. Add strain relief for the USB-C cable (quality cable no longer than 1 m) and for the W2 Cat6 run at its exit.
19. Label both ends of every wire.
20. Inspect for solder bridges, loose strands, and reversed connectors.

## 5. Electrical Checks Before Firmware

Perform these checks before plugging the controller into a computer or router setup.

| Check | Method | Pass Condition |
|---|---|---|
| Visual inspection | Inspect PCB and connectors | No shorts, loose strands, or unlabeled harnesses |
| Unpowered resistance | Measure 5 V-to-GND and 3.3 V-to-GND | No near-short |
| Series resistors | Measure from each GPIO pad to its panel-side point, unpowered | ~100 Ohm (GPIO7-11), ~330 Ohm (GPIO12) — not 0 Ohm |
| Encoder shaft ground | Measure encoder shaft/frame to GND | Continuity (near 0 Ohm) |
| 3.3 V rail | Power by USB-C and measure 3V3 to GND | 3.20 V to 3.40 V |
| Encoder module VCC | Measure `ENC1 VCC` or KY-040 `+` to GND | 3.20 V to 3.40 V |
| W5500 supply | Measure `U2 3V3` to GND at the module pins | 3.20 V to 3.40 V — U2 must never see 5 V |
| Button idle voltage | Release Play/Pause/Stop and measure GPIO9-11 | Above 3.0 V |
| Button active voltage | Press each button and measure its GPIO | Below 0.3 V |
| Encoder A/B level | Rotate encoder and measure A/B, or KY-040 CLK/DT | Logic should stay within 0 V to 3.3 V |
| Status LED | Drive GPIO12 high (or run test firmware) | LED1 lights; current ~4 mA |

Do not apply 5 V to GPIO7, GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, the encoder module signal pins, or any U2 pin (the W5500 Lite is a 3.3 V device).

## 6. Firmware Configuration

Out of the box there is nothing to provision: no SSID, no password, no config file — the controller is wired-only and its address comes from the router's DHCP reservation. `MAX_HOST` and `OSC_PORT` are plain `#define`s at the top of the sketch (they are public values, already published here). Optionally, firmware 3.1.0 accepts Wi-Fi fallback credentials over USB serial (`SETWIFI`, stored in NVS — never in the source, never printed); with none stored the board behaves exactly like Rev 3.0 wired-only.

Project network assignment:

| Device / Setting | Value |
|---|---|
| Media playback controller reserved IP | `192.168.50.114` |
| Max player computer IP | Confirm from the ASUS router setup |
| OSC UDP port | `9000` |

The controller IP `192.168.50.114` should normally be assigned by ASUS DHCP reservation keyed to the controller's **Ethernet MAC** — the `STATUS` serial command prints it (it is not the same as the ESP32's Wi-Fi MAC, so a reservation made for firmware 1.x must be re-keyed). `MAX_HOST` is different: it must be the IP address of the Max player computer that receives OSC.

Firmware behavior required (firmware 3.1.0 on hardware Rev 3.0):

| Area | Requirement |
|---|---|
| Network | Bring up the W5500 (SPI on GPIO13-18), lease by DHCP, and re-acquire automatically after link loss — no manual reconnect action. If the Ethernet link stays down and `SETWIFI` credentials are stored, fall back to Wi-Fi; switch back to Ethernet the moment its link + lease return |
| Logging | Report the Ethernet MAC, link state, assigned IP, Max host, and events over USB serial (`STATUS` command) |
| Credentials | None required. Optional Wi-Fi fallback credentials are provisioned over USB serial (`SETWIFI`) into NVS — never compiled into the sketch, never printed |
| Buttons | Send one OSC command on the debounced press edge only |
| Encoder | Decode valid quadrature transitions from GPIO7/GPIO8; apply stronger filtering if KY-040 is used |
| Volume | Maintain integer volume `0...100` |
| Volume step | Change volume by 2 percentage points per detent |
| OSC volume | Send normalized float `0.0...1.0` |
| Limits | Clamp volume between `0.0` and `1.0` |
| Memory | Save last volume after about 2 seconds of inactivity |
| Boot | Do not send Play, Pause, or Stop on boot; booting with the Ethernet cable unplugged must wait (LED blinking), not restart-loop |
| Status LED | GPIO12 solid high when the Ethernet link is up with a DHCP lease; mostly-on with a short off-blip while running on the Wi-Fi fallback; blink at ~2 Hz while there is no network at all |

## 7. OSC Message Contract

This OSC contract is carried unchanged since Rev 1.0 — the Rev 3.0 Ethernet migration changed only the transport underneath it. Confirm that the final Max patch uses the same addresses and UDP port before acceptance testing.

| Function | OSC Address | Argument | Example |
|---|---|---:|---|
| Play | `/transport/play` | integer `1` | `/transport/play 1` |
| Pause | `/transport/pause` | integer `1` | `/transport/pause 1` |
| Stop | `/transport/stop` | integer `1` | `/transport/stop 1` |
| Volume | `/volume` | float `0.0...1.0` | `/volume 0.65` |

Default UDP destination port: `9000`.

## 8. ASUS Router Setup

This project's ASUS RT-AX1800HP is already configured per the NaoDec network setup guide. Reuse that configuration rather than creating a new one.

Router proximity is a network concern only. It has no bearing on where U1 is physically mounted — U1 belongs inside the operator panel enclosure regardless of how far that panel sits from the router (see Section 1, Placement Requirement). The W2 Cat6 run carries the panel-to-router distance; the controller no longer uses the router's 2.4 GHz radio at all.

1. Connect W2 (the ~6 m Cat6) from U2's RJ45 to a free ASUS LAN port. The cable carries data only — this router has no PoE, so the panel is still powered locally by PSU1/J1.
2. The Max computer (Mac Mini) connects to an ASUS LAN port by Ethernet, static IP `192.168.50.2`, with the Router field left blank so the Mac keeps using its Wi-Fi interface for internet (see the network setup guide, section 3).
3. The wired controller and the wired Max computer share the same LAN, gateway `192.168.50.1`.
4. DHCP pool is `192.168.50.100`-`192.168.50.199`; the Max computer's `192.168.50.2` is a static address outside the pool, not a reservation.
5. Reserve a DHCP address for the media playback controller under LAN -> DHCP Server -> Manually Assigned IP, at `192.168.50.114`, keyed to the **Ethernet MAC printed by the `STATUS` serial command**. If an entry from the Wi-Fi firmware (1.x) exists, replace it — the Ethernet MAC is a different address.
6. Record the controller's Ethernet MAC and confirm the reservation with `ping 192.168.50.114`.

(The 2.4 GHz SSID `ASUS_NAODEC` and its AP-isolation setting no longer matter to this controller; they remain relevant only to other NaoDec Wi-Fi devices.)

Addressing for this LAN:

| Device | IP |
|---|---|
| ASUS RT-AX1800HP (gateway) | `192.168.50.1` |
| Max computer (Mac Mini, Ethernet, static) | `192.168.50.2` |
| Media playback controller (this build, wired, DHCP reservation) | `192.168.50.114` |

`192.168.50.114` follows the existing NaoDec convention of assigning each new ESP32 the next `.11x` address (`.111`, `.112`, `.113` are already in use by other NaoDec ESP32 modules).

Do not set `MAX_HOST` to `192.168.50.114`; that address belongs to the ESP32 controller. Set `MAX_HOST` to the Max player computer's IP (`192.168.50.2`).

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
| ESP32 not reachable | LED1 blinking means no link/lease: check the Cat6 at both ends, the router LAN port, and the DHCP reservation (type `STATUS` for link/IP/MAC). Then confirm same LAN/VLAN |
| Duplicate button messages | Increase firmware debounce or check switch wiring |
| Encoder direction reversed | Swap A/B wiring or reverse direction in firmware |
| Volume affects lights | The Max patch is mapped to NeoDDP brightness instead of media gain |

## 11. Acceptance Tests

Run these before calling the controller ready.

| ID | Test | Pass Condition |
|---|---|---|
| ELEC-01 | Visual inspection | No shorts, loose wires, or exposed conductors |
| ELEC-02 | 3.3 V rail | 3.20 V to 3.40 V |
| ELEC-03 | Encoder shaft ground | Continuity from shaft/frame to GND |
| NET-01 | Ethernet DHCP | Controller gets DHCP address `192.168.50.114` within 15 seconds of link up |
| NET-02 | Max reachability | Max computer and ESP32 are on same LAN/VLAN |
| NET-03 | UDP receive | Max receives only on the configured IP and port |
| NET-04 | Reconnect | Controller re-leases and OSC resumes after a cable unplug/replug and after a router reboot, with no manual action |
| NET-05 | Cold boot unplugged | Booted with the Cat6 unplugged for 2 minutes: no restart loop, LED keeps blinking; after plug-in the LED goes solid and controls work |
| FUNC-01 | Play | One press sends one play command |
| FUNC-02 | Pause | One press sends one pause command |
| FUNC-03 | Stop | One press sends one stop command |
| FUNC-04 | Held button | Holding button for 3 seconds sends no repeats |
| FUNC-05 | Volume clockwise | Ten detents increase by about 20 percentage points |
| FUNC-06 | Volume counterclockwise | Ten detents decrease by about 20 percentage points |
| FUNC-07 | Volume limits | Output remains clamped from `0.0` to `1.0` |
| FUNC-08 | Boot behavior | No Play, Pause, or Stop command on power-up |
| FUNC-09 | Status LED | LED1 solid within 15 s of power-up with the cable connected; blinks within a few seconds of unplugging the Cat6; returns to solid after replug (ties into NET-04) |
| SYS-01 | Site link | Reliable control at the final operator location over the installed ~6 m Cat6 run |
| SYS-02 | Soak | Stable operation for 8 hours with no unintended command |

## 12. Commissioning Record

Fill this out for each built controller.

| Field | Value |
|---|---|
| Controller serial / asset ID | |
| ESP32-S3 board variant | |
| Firmware version / commit | |
| Router / LAN port used | |
| Controller Ethernet MAC (from `STATUS`) | |
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
| Wired link test | Pass |
| Enclosure | Closed, labeled, strain-relieved, and free of exposed conductors |
| Documentation | Commissioning record complete |
