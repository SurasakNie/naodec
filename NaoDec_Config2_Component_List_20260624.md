# NaoDec — Config 2 Component List (Bill of Materials)

**Project:** NaoDec — WS2815 LED + scent controller, Config 2 (single ~650 W ATX PSU)
**Date:** 2026-06-24
**Scope:** All components in the combined Config 2 build (LED controller + scent controller
on one ATX PSU). **Audio excluded** (GAB8 amp, Microlab speakers, Edifier T5 — separate 24 V subsystem).
**Source:** `NaoDec_Config2_Combined_Wiring_Rev1.0.html` (schematic BOM, 22 line items)

---

## 1. Power & AC Input

| Designator | Qty | Component | Notes |
|---|---|---|---|
| IEC1 | 1 | IEC C14 mains inlet | 220 V AC · 10 A |
| MCB1 | 1 | Miniature circuit breaker | 10 A · 2-pole · C-curve |
| PSU1 | 1 | **~650 W ATX PSU, single 12 V rail** (e.g. Thermaltake Smart BM3 650W or Corsair CV650) | 650 W · 80+ Bronze · single-rail · 12 V + 5 V rails · ~50.6 % loaded. See PSU report + `NaoDec_ATX_PSU_Wiring_and_Connectors.md` |
| SW1 | 1 | Latching SPST switch | PS_ON# enable (pin 16 → GND) |
| NTC1 | 1 | NTC inrush limiter | 10 Ω / 10 A · on 12 V → FB1 feed |

## 2. LED Control

| Designator | Qty | Component | Notes |
|---|---|---|---|
| U1 | 1 | ESP32-S3-WROOM-1 N16R8 — **MASTER** | WLED + FX engine + DDP TX · CH1–CH4 (GPIO1,4,5,6) |
| U3 | 1 | ESP32-S3-WROOM-1 N16R8 — **SLAVE** | WLED DDP receiver · CH5–CH7 (GPIO4,5,6) |
| U2 | 1 | SN74AHCT245N octal bus transceiver | 3.3 V → 5 V level shifter · DIR=VCC, OE=GND |
| R1–R7 | 7 | 47 Ω 1/4 W metal-film resistor | Data source termination (≤20 mm from U2) |
| C7 | 1 | 100 nF ceramic X7R capacitor | U2 VCC decoupling |
| HOST1 | 1 | Mac mini | WLED host via USB-C / UART (off-board) |

## 3. LED Power Distribution

| Designator | Qty | Component | Notes |
|---|---|---|---|
| F1 | 1 | 7.5 A ATC/ATO blade fuse | Strip #1 (Vertex) branch |
| FB1 | 1 | 6-channel ATC/ATO fuse block | 7.5 A/ch (F2…F7) → edge strips |
| C1–C6, C8 | 7 | 1000 µF 25 V electrolytic capacitor | Strip input bulk reservoir (C7 is U2 decoupling) |

## 4. LED Strips (Loads)

| Designator | Qty | Component | Notes |
|---|---|---|---|
| STRIP1 | 1 | Strip #1 — Vertex · 60× WS2815 | ~0.9 A · 16 AWG · 20 m run · CH1 · single feed |
| STRIP2–STRIP7 | 6 | Edge sets A–F · 280× WS2815 each | ~4.2 A ea · 12 AWG · head feed + mid-strip injection |

## 5. Scent Subsystem

| Designator | Qty | Component | Notes |
|---|---|---|---|
| U4 | 1 | Waveshare ESP32-S3-Relay-6CH | 12 V · WLED · 4 relay channels used |
| F_MAIN | 1 | T2A 5×20 mm fuse | Scent branch main fuse |
| F1-scent | 1 | T1A 5×20 mm fuse | Scent ESP sub-branch fuse |
| F3–F6 | 4 | T500 mA 5×20 mm fuse | Per-atomizer fuse |
| RC1–RC4 | 4 | 100 nF + 100 Ω RC snubber | Across each relay COM–NO pair |
| A1–A4 | 4 | JY-M27AO ultrasonic atomizer driver | 12 V · ~150 mA · 113 kHz · **mount external (moisture)** |

---

## Totals

- **BOM line items:** 22
- **Physical parts:** ~50
- **ICs / controllers:** 4 (U1, U2, U3, U4)
- **WS2815 pixels:** 1,740 (60 vertex + 6 × 280 edge)
- **Fuses:** 13 (F1 + FB1's 6 + F_MAIN + F1-scent + F3–F6 ×4)
- **Capacitors:** 8 (C1–C8) · **Resistors:** 7 (R1–R7) · **Snubbers:** 4 (RC1–RC4)

## Power summary (per rail, worst case)

| Rail | Source | Worst-case load |
|---|---|---|
| 5 V (logic: U1, U2, U3) | ATX 5 V | ~0.82 A · ~4 W |
| 12 V (LEDs + scent) | ATX 12 V | ~27.1 A · ~325 W |
| **System total (DC)** | — | **~329 W** |
| **PSU (650 W) load** | — | **~50.6 %** |
| **AC mains** | 220 V | **~358 W → ~1.6 A** |

## Excluded — audio subsystem (separate 24 V build)

Not part of this BOM; documented in `NaoDec_Config2_Audio_Integration_20260622.md`:
- WONDOM GAB8 amplifier (24 V) + dedicated 24 V PSU (e.g. Mean Well LRS-240-24)
- 6× Microlab Satellite X3 (passive, driven by GAB8)
- Edifier T5 powered subwoofer (self-powered, own AC plug)

---

## References
- `NaoDec_Config2_Combined_Wiring_Rev1.0.html` — combined wiring schematic (source of this BOM)
- `NaoDec_Power_Report_Complete_20260617.md` — power budget & PSU analysis
- `NaoDec_ATX_PSU_Wiring_and_Connectors.md` — routing 12 V / 5 V / 3.3 V from the ATX PSU to each device
- `NaoDec WS2815 LED Controller — 12VDC — Rev 1.6.html` — source LED controller schematic
- `NaoDec_Config2_Audio_Integration_20260622.md` — deferred audio subsystem
