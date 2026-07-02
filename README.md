# NaoDec

Interactive wiring and schematics for a 7-channel WS2815 LED installation driven by dual ESP32-S3 controllers running WLED.

Published at https://surasaknie.github.io/naodec/ (auto-indexed).

---

## Overview

NaoDec is a browser-based documentation set for a large-scale addressable LED rig. All files are self-contained HTML — no build step, no dependencies. Open any file locally or browse the auto-indexed GitHub Pages site.

The design uses two ESP32-S3-WROOM-1 N16R8 modules running WLED in a master/slave DDP configuration to drive 1,740 WS2815 (12 V) pixels across 7 independent channels, with a SN74AHCT245N octal transceiver for 3.3 V → 5 V logic conversion.

---

## Repository

```
naodec/
├── index.html                                     # GitHub Pages auto-index
├── NaoDec_WS2815_LED_Controller_Rev1.6.html       # Full controller schematic (interactive)
├── NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.2.html  # 3D LED position & channel map
├── NaoDec_Series_Coil_Build_Rev0_Pre-Release.html # Series coil / electromagnet subsystem (pre-release)
├── NaoDec_Vertex_Series_Coil_Rev1.0.html          # Interactive series-coil schematic (current in-file Rev 1.0a)
├── XL4015_CC_CV_Mockup_Test_Procedure.md          # Pre-coil converter qualification procedure
├── NaoDec_Media_Playback_Controller_Schematic_Rev1.0.html  # ESP32-S3 Wi-Fi OSC operator panel (interactive)
├── NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md # Playback controller build, network & Max/MSP setup
├── Simple_WS2815_Controller_Rev_1.0.html          # Simplified single-controller reference
└── Archived/                                      # Previous revisions
```

---

## Hardware

### Controllers

| Component | Part | Notes |
|-----------|------|-------|
| U1 — Master | ESP32-S3-WROOM-1 N16R8 | WLED master · CH1–CH4 (GPIO1, 4, 5, 6) |
| U1 — Slave | ESP32-S3-WROOM-1 N16R8 | WLED DDP slave · CH5–CH7 (GPIO4, 5, 6) |
| U2 | SN74AHCT245N | Octal bus transceiver · 3.3 V → 5 V · 7 ch used |
| R1–R7 | 47 Ω ¼W metal film | Source-end termination, ≤20 mm from U2 |
| C1 | 1000 µF 25 V electrolytic | Smoothing cap · 12 V 5 A rail |
| C2–C6, C8 | 1000 µF 25 V electrolytic | Bypass caps at each strip input |
| C7 | 100 nF ceramic | U2 VCC decoupling |
| NTC1 | 10 Ω / 10 A NTC | Inrush limiter · 12 V 50 A rail |
| F1 | 7.5 A ATC/ATO blade fuse | Strip #1 branch |
| FB1 | 6-ch ATC/ATO fuse block | Strips #2–#7 · F2–F7 · 7.5 A each |

### Power Rails

| Rail | Supply | Load |
|------|--------|------|
| 5 V logic | PSU 5 V 3 A (15 W) | Master Vin · Slave Vin · U2 VCC |
| 12 V (5 A) | PSU 12 V 5 A (60 W) | Strip #1 — Vertex set (60 LEDs · ~0.9 A) |
| 12 V (50 A) | PSU 12 V 50 A (600 W) | Strips #2–#7 — Edge sets (~25.2 A max) |

> **⚠ Never connect the 5 V, 12 V 5 A, and 12 V 50 A positive rails together. Keep all V+ rails fully isolated.**

### LED Channels

| CH | GPIO (board) | Buffer | Strip | LEDs | Cable | Wire AWG |
|----|-------------|--------|-------|------|-------|----------|
| 1 | GPIO1 (Master) | U2 A1→B1 | #1 Vertex | 60 | ~20 m | 18 |
| 2 | GPIO4 (Master) | U2 A2→B2 | #2 Edge A | 280 | ~8 m | 12 |
| 3 | GPIO5 (Master) | U2 A3→B3 | #3 Edge B | 280 | ~8 m | 12 |
| 4 | GPIO6 (Master) | U2 A4→B4 | #4 Edge C | 280 | ~8 m | 12 |
| 5 | GPIO4 (Slave) | U2 A5→B5 | #5 Edge D | 280 | ~8 m | 12 |
| 6 | GPIO5 (Slave) | U2 A6→B6 | #6 Edge E | 280 | ~8 m | 12 |
| 7 | GPIO6 (Slave) | U2 A7→B7 | #7 Edge F | 280 | ~8 m | 12 |

**Total: 1,740 × WS2815 (12 V)**

---

## Series Coil / Electromagnet Subsystem

Sixty hand-wound copper coils are wired end-to-end in one series loop. Each coil has 7 turns of 1 mm copper around a **12.5 mm ID crystal core**, with 5 cm of straight lead before the winding and 7 cm after it. The calculated copper length is approximately 0.417 m per coil and 25.0 m for all 60 coils. Full design write-up: [`NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`](NaoDec_Series_Coil_Build_Rev0_Pre-Release.html). Interactive schematic: [`NaoDec_Vertex_Series_Coil_Rev1.0.html`](NaoDec_Vertex_Series_Coil_Rev1.0.html). Standalone converter test: [`XL4015_CC_CV_Mockup_Test_Procedure.md`](XL4015_CC_CV_Mockup_Test_Procedure.md).

> **⚠ An inductor does nothing on steady-state DC** (`Z = jωL → 0` at DC). The current cold-loop estimate is **~1.85 Ω**: approximately 0.55 Ω for all coils plus 1.30 Ω measured for all 20 AWG installation wiring. Direct connection to 12 V would attempt approximately 6.5 A and 78 W if the PSU allowed it.

> **⚠ A crystal core is non-magnetic** (μ ≈ air) — it gives **no field boost**, so the coils behave as weak air-core coils. At the 3 A current limit, each 7-turn coil produces approximately 21 ampere-turns.

### Interactive Schematic (Rev 1.0a)

[Open the live Vertex Series Coil schematic](https://surasaknie.github.io/naodec/NaoDec_Vertex_Series_Coil_Rev1.0.html).

The current in-file revision is **Rev 1.0a**, presented in the Dark Blue-Mint technical theme. It documents the complete current-limited path:

`12 V PSU → exact 3 A T-type fuse → local 220–470 µF + 100 nF input decoupling → dual-pot XL4015 → 70–80 °C thermal cutoff → 20 groups / 60 coils → 20 AWG return`

The page includes:

- Current design values: ~1.85 Ω cold-loop estimate, 3.0 A CC, ~5.55 V loaded output, and ~16.65 W total output.
- Compact one-group coil detail, direct-12 V warning, and pre-release bench-qualification banner.
- BOM, XL4015 harness, protection summary, engineering notes, and revision history.
- Hover/focus tooltips, zoom, pan, touch support, keyboard shortcuts, fit-to-screen, print SVG export, and themed PNG export.
- Explicit provisional-status messaging pending the final assembled-loop resistance and thermal commissioning measurements.

### Wiring

Loop topology:

```mermaid
flowchart LR
  PSU["12 V PSU (+)"] --> F["3 A slow-blow fuse"]
  F --> B["XL4015 CC/CV<br/>CV 11 V · CC 3 A"]
  B --> T["70–80 °C TCO"]
  T --> G1["Group 1<br/>3 coils"]
  G1 -->|"1 m"| G2["Group 2<br/>3 coils"]
  G2 -.->|"..."| G20["Group 20<br/>3 coils"]
  G20 -->|"6 m return"| PSUN["12 V PSU (-)"]
```

One coil geometry:

```mermaid
flowchart LR
  IN["Series input"] -->|"5 cm straight lead"| C1(["7 turns · 12.5 mm ID"])
  C1 -->|"7 cm straight lead"| OUT["Series output"]
```

### Bill of Materials

| Component | Spec | Notes |
|-----------|------|-------|
| Coils | 60 × 7-turn, 1 mm Cu, ~0.417 m each | 12.5 mm ID **crystal core**; 5 cm input lead + 7 cm output lead; ~0.55 Ω total calculated at 20 °C |
| Cable | 20 AWG installation wiring, measured ~1.30 Ω total | All interconnect and return wiring; keep every run and all slack uncoiled |
| Connectors | 20 × JST SM 2-pin | Both pins paralleled onto the series conductor; OK once the buck caps the loop at ~3 A (single SM pin = 3 A). VH (10 A) / XT30 / Anderson are higher-margin alternatives |
| PSU | 12 V DC | Feeds the buck input; may be a shared rail, but keep this branch fused and V+ isolated |
| CC/CV buck module | Dual-pot XL4015 HW-083-B, 12 V input | Set CV to 11.0 V and CC to 3.0 A; loaded output settles near 5.55 V in CC mode |
| Input decoupling | 220–470 µF low-ESR electrolytic (≥25 V) ‖ 100 nF X7R (≥25 V) | Mount directly across XL4015 IN+/IN− |
| Fuse | 3 A slow-blow (T-type), inline at buck input | **Exactly 3 A, not 3–5 A.** CC regulation is not fault interruption; a buck can fail shorted |
| Thermal cutoff | 70–80 °C, rated ≥5 A | Required for a manned installation; bond to hottest connector/cable area |
| Crystal cores | 1 per coil | Per design — non-magnetic, no field boost |
| Flyback diode *(opt.)* | 1N4007 / 1N5819 | Kick is tiny (~0.4 mJ); only if switched electronically |

### Electrical Summary

| Quantity | Value | Note |
|----------|-------|------|
| Coil resistance | ~0.55 Ω calculated | ~0.009 Ω per coil; an individual coil displays `0.0 Ω` on a 0.1 Ω-resolution meter |
| Wiring resistance | ~1.30 Ω measured | Complete 20 AWG installation wiring |
| Complete cold loop | ~1.85 Ω estimated | Confirm end-to-end after assembly; joints and copper temperature add variation |
| Direct 12 V, no buck | ~6.5 A / ~78 W | Unsafe if the PSU can supply it; do not use this operating mode |
| XL4015 operating point | 3.0 A / ~5.55 V / ~16.65 W | CV ceiling 11.0 V; converter operates in CC mode under load |
| Voltage split at 3 A | ~3.90 V wiring / ~1.65 V coils | Determined by the 1.30 Ω / 0.55 Ω resistance split |
| Power split at 3 A | ~11.70 W wiring / ~4.95 W coils | ~0.083 W per coil; keep wiring uncoiled for heat rejection |
| Estimated input | ~1.5–1.7 A from 12 V | Depends on converter efficiency and component tolerance |
| Field per coil | ~21 AT | 7 turns × 3 A; crystal core provides no magnetic gain |

> **⚠ Safety:** use only the dual-pot CC/CV XL4015, set CV to 11.0 V and CC to 3.0 A. Install an exact 3 A slow-blow input fuse, local input decoupling, and a 70–80 °C thermal cutoff for manned operation. Keep the complete 20 AWG run uncoiled, keep bare copper from touching, and keep this V+ rail isolated from the LED rails. Never run the string without the buck.

### XL4015 Mockup Qualification

Before connecting the real coils, reproduce the ~1.85 Ω loop with the measured 1.30 Ω mock wire and a ~0.56 Ω resistor bank. A practical metal-film bank is 10 × 5.6 Ω/1 W in parallel, giving 0.56 Ω/10 W. At the 3.0 A CC setting, expect approximately 5.58 V total, 3.90 V across the mock wire, and 1.68 V across the resistor bank. The ammeter is connected in series after XL4015 OUT+. See [`XL4015_CC_CV_Mockup_Test_Procedure.md`](XL4015_CC_CV_Mockup_Test_Procedure.md) for the complete wiring and pass/fail procedure.

---

## Signal Flow

```
Mac mini
  └─ USB-C → UART ──► ESP32-S3 Master (WLED)
                          ├─ GPIO1/4/5/6 → U2 (3.3V→5V) → R1–R4 → CH1–CH4
                          └─ DDP (Wi-Fi) ──► ESP32-S3 Slave (WLED)
                                                └─ GPIO4/5/6 → U2 → R5–R7 → CH5–CH7
```

The master calculates all effects and streams pixel data to the slave over DDP/Wi-Fi. The slave is a pure DDP receiver — no local effect computation.

---

## Firmware

Both controllers run **WLED** .

- Master: standard WLED instance, outputs CH1–CH4
- Slave: WLED configured as DDP receiver, outputs CH5–CH7
- Host: Mac mini sends WLED / Art-Net data via USB-C to UART

> Avoid strapping pins **GPIO 0, 3, 45, 46** on the ESP32-S3 — these conflict with boot mode.

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
- **Pan** — click and drag
- **Zoom** — scroll wheel or `+` / `-` buttons
- **Component info** — click any component or wire for a tooltip

---

## Revisions

| File | Rev | Notes |
|------|-----|-------|
| NaoDec_WS2815_LED_Controller | 1.6 | Current · 7-ch dual ESP32-S3 DDP |
| NaoDec_3D_Vertex_and_Edges_LED_Mapping | 1.2 | Current · 3D position map |
| NaoDec_Series_Coil_Build | 0 (pre-release) | Pre-release · 60-coil series electromagnet subsystem |
| Simple_WS2815_Controller | 1.0 | Single-controller reference |
| NaoDec_Controller_Box_Configs | 1.1 | Current · electrical enclosure vs PC case · audited power calculations |
| NaoDec_Power_and_Controller_Box_Report | 1.0 | Full power budget, PSU specs, voltage-drop analysis, audit findings |

---

## License

MIT — see [LICENSE](LICENSE)

