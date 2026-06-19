# NaoDec

Interactive wiring and schematics for a 7-channel WS2815 LED installation driven by dual ESP32-S3 controllers running WLED.

Published at https://surasaknie.github.io/naodec/ (auto-indexed).

---

## Overview

NaoDec is a browser-based documentation set for a large-scale addressable LED rig. All files are self-contained HTML â€” no build step, no dependencies. Open any file locally or browse the auto-indexed GitHub Pages site.

The design uses two ESP32-S3-WROOM-1 N16R8 modules running WLED in a master/slave DDP configuration to drive 1,740 WS2815 (12 V) pixels across 7 independent channels, with a SN74AHCT245N octal transceiver for 3.3 V â†’ 5 V logic conversion.

---

## Repository

```
naodec/
â”œâ”€â”€ index.html                                     # GitHub Pages auto-index
â”œâ”€â”€ NaoDec_WS2815_LED_Controller_Rev1.6.html       # Full controller schematic (interactive)
â”œâ”€â”€ NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.2.html  # 3D LED position & channel map
â”œâ”€â”€ NaoDec_Series_Coil_Build_Rev0_Pre-Release.html # Series coil / electromagnet subsystem (pre-release)
â”œâ”€â”€ NaoDec_Vertex_Series_Coil_Rev1.0.html          # Interactive series-coil schematic (current in-file Rev 1.0a)
â”œâ”€â”€ XL4015_CC_CV_Mockup_Test_Procedure.md          # Pre-coil converter qualification procedure
â”œâ”€â”€ Simple_WS2815_Controller_Rev_1.0.html          # Simplified single-controller reference
â””â”€â”€ Archived/                                      # Previous revisions
```

---

## Hardware

### Controllers

| Component | Part | Notes |
|-----------|------|-------|
| U1 â€” Master | ESP32-S3-WROOM-1 N16R8 | WLED master Â· CH1â€“CH4 (GPIO1, 4, 5, 6) |
| U1 â€” Slave | ESP32-S3-WROOM-1 N16R8 | WLED DDP slave Â· CH5â€“CH7 (GPIO4, 5, 6) |
| U2 | SN74AHCT245N | Octal bus transceiver Â· 3.3 V â†’ 5 V Â· 7 ch used |
| R1â€“R7 | 47 Î© Â¼W metal film | Source-end termination, â‰¤20 mm from U2 |
| C1 | 1000 ÂµF 25 V electrolytic | Smoothing cap Â· 12 V 5 A rail |
| C2â€“C6, C8 | 1000 ÂµF 25 V electrolytic | Bypass caps at each strip input |
| C7 | 100 nF ceramic | U2 VCC decoupling |
| NTC1 | 10 Î© / 10 A NTC | Inrush limiter Â· 12 V 50 A rail |
| F1 | 7.5 A ATC/ATO blade fuse | Strip #1 branch |
| FB1 | 6-ch ATC/ATO fuse block | Strips #2â€“#7 Â· F2â€“F7 Â· 7.5 A each |

### Power Rails

| Rail | Supply | Load |
|------|--------|------|
| 5 V logic | PSU 5 V 3 A (15 W) | Master Vin Â· Slave Vin Â· U2 VCC |
| 12 V (5 A) | PSU 12 V 5 A (60 W) | Strip #1 â€” Vertex set (60 LEDs Â· ~0.9 A) |
| 12 V (50 A) | PSU 12 V 50 A (600 W) | Strips #2â€“#7 â€” Edge sets (~25.2 A max) |

> **âš  Never connect the 5 V, 12 V 5 A, and 12 V 50 A positive rails together. Keep all V+ rails fully isolated.**

### LED Channels

| CH | GPIO (board) | Buffer | Strip | LEDs | Cable | Wire AWG |
|----|-------------|--------|-------|------|-------|----------|
| 1 | GPIO1 (Master) | U2 A1â†’B1 | #1 Vertex | 60 | ~20 m | 18 |
| 2 | GPIO4 (Master) | U2 A2â†’B2 | #2 Edge A | 280 | ~8 m | 12 |
| 3 | GPIO5 (Master) | U2 A3â†’B3 | #3 Edge B | 280 | ~8 m | 12 |
| 4 | GPIO6 (Master) | U2 A4â†’B4 | #4 Edge C | 280 | ~8 m | 12 |
| 5 | GPIO4 (Slave) | U2 A5â†’B5 | #5 Edge D | 280 | ~8 m | 12 |
| 6 | GPIO5 (Slave) | U2 A6â†’B6 | #6 Edge E | 280 | ~8 m | 12 |
| 7 | GPIO6 (Slave) | U2 A7â†’B7 | #7 Edge F | 280 | ~8 m | 12 |

**Total: 1,740 Ã— WS2815 (12 V)**

---

## Series Coil / Electromagnet Subsystem

Sixty hand-wound copper coils are wired end-to-end in one series loop. Each coil has 7 turns of 1 mm copper around a **12.5 mm ID crystal core**, with 5 cm of straight lead before the winding and 7 cm after it. The calculated copper length is approximately 0.417 m per coil and 25.0 m for all 60 coils. Full design write-up: [`NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`](NaoDec_Series_Coil_Build_Rev0_Pre-Release.html). Interactive schematic: [`NaoDec_Vertex_Series_Coil_Rev1.0.html`](NaoDec_Vertex_Series_Coil_Rev1.0.html). Standalone converter test: [`XL4015_CC_CV_Mockup_Test_Procedure.md`](XL4015_CC_CV_Mockup_Test_Procedure.md).

> **âš  An inductor does nothing on steady-state DC** (`Z = jÏ‰L â†’ 0` at DC). The current cold-loop estimate is **~1.85 Î©**: approximately 0.55 Î© for all coils plus 1.30 Î© measured for all 20 AWG installation wiring. Direct connection to 12 V would attempt approximately 6.5 A and 78 W if the PSU allowed it.

> **âš  A crystal core is non-magnetic** (Î¼ â‰ˆ air) â€” it gives **no field boost**, so the coils behave as weak air-core coils. At the 3 A current limit, each 7-turn coil produces approximately 21 ampere-turns.

### Interactive Schematic (Rev 1.0a)

[Open the live Vertex Series Coil schematic](https://surasaknie.github.io/naodec/NaoDec_Vertex_Series_Coil_Rev1.0.html).

The current in-file revision is **Rev 1.0a**, presented in the Dark Blue-Mint technical theme. It documents the complete current-limited path:

`12 V PSU â†’ exact 3 A T-type fuse â†’ local 220â€“470 ÂµF + 100 nF input decoupling â†’ dual-pot XL4015 â†’ 70â€“80 Â°C thermal cutoff â†’ 20 groups / 60 coils â†’ 20 AWG return`

The page includes:

- Current design values: ~1.85 Î© cold-loop estimate, 3.0 A CC, ~5.55 V loaded output, and ~16.65 W total output.
- Compact one-group coil detail, direct-12 V warning, and pre-release bench-qualification banner.
- BOM, XL4015 harness, protection summary, engineering notes, and revision history.
- Hover/focus tooltips, zoom, pan, touch support, keyboard shortcuts, fit-to-screen, print SVG export, and themed PNG export.
- Explicit provisional-status messaging pending the final assembled-loop resistance and thermal commissioning measurements.

### Wiring

Loop topology:

```mermaid
flowchart LR
  PSU["12 V PSU (+)"] --> F["3 A slow-blow fuse"]
  F --> B["XL4015 CC/CV<br/>CV 11 V Â· CC 3 A"]
  B --> T["70â€“80 Â°C TCO"]
  T --> G1["Group 1<br/>3 coils"]
  G1 -->|"1 m"| G2["Group 2<br/>3 coils"]
  G2 -.->|"..."| G20["Group 20<br/>3 coils"]
  G20 -->|"6 m return"| PSUN["12 V PSU (-)"]
```

One coil geometry:

```mermaid
flowchart LR
  IN["Series input"] -->|"5 cm straight lead"| C1(["7 turns Â· 12.5 mm ID"])
  C1 -->|"7 cm straight lead"| OUT["Series output"]
```

### Bill of Materials

| Component | Spec | Notes |
|-----------|------|-------|
| Coils | 60 Ã— 7-turn, 1 mm Cu, ~0.417 m each | 12.5 mm ID **crystal core**; 5 cm input lead + 7 cm output lead; ~0.55 Î© total calculated at 20 Â°C |
| Cable | 20 AWG installation wiring, measured ~1.30 Î© total | All interconnect and return wiring; keep every run and all slack uncoiled |
| Connectors | 20 Ã— JST SM 2-pin | Both pins paralleled onto the series conductor; OK once the buck caps the loop at ~3 A (single SM pin = 3 A). VH (10 A) / XT30 / Anderson are higher-margin alternatives |
| PSU | 12 V DC | Feeds the buck input; may be a shared rail, but keep this branch fused and V+ isolated |
| CC/CV buck module | Dual-pot XL4015 HW-083-B, 12 V input | Set CV to 11.0 V and CC to 3.0 A; loaded output settles near 5.55 V in CC mode |
| Input decoupling | 220â€“470 ÂµF low-ESR electrolytic (â‰¥25 V) â€– 100 nF X7R (â‰¥25 V) | Mount directly across XL4015 IN+/INâˆ’ |
| Fuse | 3 A slow-blow (T-type), inline at buck input | **Exactly 3 A, not 3â€“5 A.** CC regulation is not fault interruption; a buck can fail shorted |
| Thermal cutoff | 70â€“80 Â°C, rated â‰¥5 A | Required for a manned installation; bond to hottest connector/cable area |
| Crystal cores | 1 per coil | Per design â€” non-magnetic, no field boost |
| Flyback diode *(opt.)* | 1N4007 / 1N5819 | Kick is tiny (~0.4 mJ); only if switched electronically |

### Electrical Summary

| Quantity | Value | Note |
|----------|-------|------|
| Coil resistance | ~0.55 Î© calculated | ~0.009 Î© per coil; an individual coil displays `0.0 Î©` on a 0.1 Î©-resolution meter |
| Wiring resistance | ~1.30 Î© measured | Complete 20 AWG installation wiring |
| Complete cold loop | ~1.85 Î© estimated | Confirm end-to-end after assembly; joints and copper temperature add variation |
| Direct 12 V, no buck | ~6.5 A / ~78 W | Unsafe if the PSU can supply it; do not use this operating mode |
| XL4015 operating point | 3.0 A / ~5.55 V / ~16.65 W | CV ceiling 11.0 V; converter operates in CC mode under load |
| Voltage split at 3 A | ~3.90 V wiring / ~1.65 V coils | Determined by the 1.30 Î© / 0.55 Î© resistance split |
| Power split at 3 A | ~11.70 W wiring / ~4.95 W coils | ~0.083 W per coil; keep wiring uncoiled for heat rejection |
| Estimated input | ~1.5â€“1.7 A from 12 V | Depends on converter efficiency and component tolerance |
| Field per coil | ~21 AT | 7 turns Ã— 3 A; crystal core provides no magnetic gain |

> **âš  Safety:** use only the dual-pot CC/CV XL4015, set CV to 11.0 V and CC to 3.0 A. Install an exact 3 A slow-blow input fuse, local input decoupling, and a 70â€“80 Â°C thermal cutoff for manned operation. Keep the complete 20 AWG run uncoiled, keep bare copper from touching, and keep this V+ rail isolated from the LED rails. Never run the string without the buck.

### XL4015 Mockup Qualification

Before connecting the real coils, reproduce the ~1.85 Î© loop with the measured 1.30 Î© mock wire and a ~0.56 Î© resistor bank. A practical metal-film bank is 10 Ã— 5.6 Î©/1 W in parallel, giving 0.56 Î©/10 W. At the 3.0 A CC setting, expect approximately 5.58 V total, 3.90 V across the mock wire, and 1.68 V across the resistor bank. The ammeter is connected in series after XL4015 OUT+. See [`XL4015_CC_CV_Mockup_Test_Procedure.md`](XL4015_CC_CV_Mockup_Test_Procedure.md) for the complete wiring and pass/fail procedure.

---

## Signal Flow

```
Mac mini
  â””â”€ USB-C â†’ UART â”€â”€â–º ESP32-S3 Master (WLED)
                          â”œâ”€ GPIO1/4/5/6 â†’ U2 (3.3Vâ†’5V) â†’ R1â€“R4 â†’ CH1â€“CH4
                          â””â”€ DDP (Wi-Fi) â”€â”€â–º ESP32-S3 Slave (WLED)
                                                â””â”€ GPIO4/5/6 â†’ U2 â†’ R5â€“R7 â†’ CH5â€“CH7
```

The master calculates all effects and streams pixel data to the slave over DDP/Wi-Fi. The slave is a pure DDP receiver â€” no local effect computation.

---

## Firmware

Both controllers run **WLED** .

- Master: standard WLED instance, outputs CH1â€“CH4
- Slave: WLED configured as DDP receiver, outputs CH5â€“CH7
- Host: Mac mini sends WLED / Art-Net data via USB-C to UART

> Avoid strapping pins **GPIO 0, 3, 45, 46** on the ESP32-S3 â€” these conflict with boot mode.

---

## Usage

All documents are static HTML. No installation required.

```bash
# Clone and open locally
git clone https://github.com/SurasakNie/naodec.git
open naodec/NaoDec_WS2815_LED_Controller_Rev1.6.html
```

Or browse online: **https://surasaknie.github.io/naodec/**

Each schematic supports:
- **Pan** â€” click and drag
- **Zoom** â€” scroll wheel or `+` / `-` buttons
- **Component info** â€” click any component or wire for a tooltip

---

## Revisions

| File | Rev | Notes |
|------|-----|-------|
| NaoDec_WS2815_LED_Controller | 1.6 | Current Â· 7-ch dual ESP32-S3 DDP |
| NaoDec_3D_Vertex_and_Edges_LED_Mapping | 1.2 | Current Â· 3D position map |
| NaoDec_Series_Coil_Build | 0 (pre-release) | Pre-release Â· 60-coil series electromagnet subsystem |
| Simple_WS2815_Controller | 1.0 | Single-controller reference |
| NaoDec_Controller_Box_Configs | 1.1 | Current Â· electrical enclosure vs PC case Â· audited power calculations |
| NaoDec_Power_and_Controller_Box_Report | 1.0 | Full power budget, PSU specs, voltage-drop analysis, audit findings |

---

## License

MIT â€” see [LICENSE](LICENSE)

