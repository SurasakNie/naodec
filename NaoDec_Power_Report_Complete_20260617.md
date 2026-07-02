# NaoDec - Power Requirements & Controller Box Report
## Complete Technical Export

**Project:** NaoDec - 7-channel WS2815 LED installation + 4-channel scent controller 
**Document revision:** 1.1 (Audited) 
**Date:** 2026-06-17 
**Review status:** All figures verified; corrections noted below 
**Scope:** Consolidated power budget, PSU selection, single-box mounting options (electrical enclosure vs. ATX PC case), cable/voltage-drop analysis, and complete audit of all figures.

> **Companion files:**
> - `NaoDec_Controller_Box_Configs_Rev1.1.html` - interactive box configuration diagram
> - `NaoDec_WS2815_LED_Controller_Rev1.6.html` - LED controller schematic
> - `NaoDec_Scent_Controller_Schematic_Rev2.0.html` - scent controller schematic
> - `README.md` - project overview & revisions table

---

## Executive Summary

- Two controllers co-located in **one control box**, fed from a single **220 V AC** input.
- Two box configuration options documented:
 - **Config 1 - Electrical enclosure** (3-4 isolated DIN-rail PSUs; recommended for permanent install)
 - **Config 2 - ATX PC case** (single ATX PSU; compact, lower cost)
- **All existing PSU specs are valid.** No PSU resizing required.
- The 6 long edge strips require **mid-strip power injection** to maintain end-of-strip voltage.
- **All power figures audited and verified.** Corrections from earlier revision listed in Section 10.

---

## System Overview

| Subsystem | Controller | Firmware | Outputs |
|-----------|-----------|----------|---------|
| LED | 2x ESP32-S3-WROOM-1 N16R8 (Master + DDP Slave) + SN74AHCT245N level shifter | WLED | 7 channels - 1,740 x WS2815 |
| Scent | Waveshare ESP32-S3-Relay-6CH | WLED | 4 x JY-M27AO ultrasonic atomizers (113 kHz) |

### LED Channel Map

| CH | Source | Strip | LEDs | Cable | Power AWG |
|----|--------|-------|------|-------|-----------|
| 1 | Master GPIO1 | #1 Vertex | 60 | ~20 m | **16** (recommended) |
| 2-4 | Master GPIO4/5/6 | #2-#4 Edge | 280 ea | ~4 m + 5 m strip | 12 |
| 5-7 | Slave GPIO4/5/6 | #5-#7 Edge | 280 ea | ~4 m + 5 m strip | 12 |

Each edge strip = **5 sections x 56 LEDs = 280** (60 LED/m strip, 4 LEDs cut per section -> ~0.933 m/section, ~4.67 m total).

---

## Device-by-Device Power Inventory

### WS2815 LED Specifications
- Source spec: 10-15 mA/px @ 12 V
- **Design maximum: 15 mA/px** (full-white worst case)
- Voltage window: 9 V (backup-line minimum) to 13.5 V; aim >= 10.5 V to avoid visible dimming

### LED Power Draw

| Device | Rail | Current | Power |
|--------|------|---------|-------|
| ESP32-S3 Master | 5 V | ~0.40 A | 2.0 W |
| ESP32-S3 Slave | 5 V | ~0.40 A | 2.0 W |
| SN74AHCT245N (U2) | 5 V | ~0.02 A | 0.1 W |
| **5 V logic subtotal** | **5 V** | **~0.82 A** | **~4.1 W** |
| Strip #1 - Vertex (60 px @ 15 mA) | 12 V | 0.90 A | 10.8 W |
| Strips #2-#7 - Edge (6 x 280 px @ 15 mA) | 12 V | 25.2 A | 302.4 W |
| **12 V LED subtotal** | **12 V** | **26.1 A** | **~313.2 W** |

### Scent System Power Draw

| Device | Rail | Current | Power |
|--------|------|---------|-------|
| ESP32-S3-Relay-6CH | 12 V | ~0.40 A | 4.8 W |
| 4 x JY-M27AO atomizer drivers | 12 V | 4 x 0.15 A | 7.2 W |
| **Scent subtotal** | **12 V** | **~1.0 A** | **~12.0 W** |

**Note on scent 12 V trunk:** Source schematic labels the trunk at 1.18 A (conservative wire-rating); steady-state load is ~1.0 A per PSU/fuse margin notes.

### Combined System Totals

| Rail | Current | Power |
|------|---------|-------|
| 5 V (logic) | ~0.82 A | ~4.1 W |
| 12 V (LED + scent, full white) | **~27.1 A** | **~325.2 W** |
| **System Total** | - | **~329 W** |

**No higher worst case exists** - 15 mA/px is the full-white figure from the WS2815 source schematic.

---

## PSU Requirements & Selection

### Margin Analysis

| PSU | Rail | Min Load | Specified | Margin | Margin% | Powers |
|-----|------|---------|-----------|--------|---------|--------|
| A | 5 V | 0.82 A | **3 A (15 W)** | 3.66x | 73.4% | LED logic (2x ESP + U2) |
| B | 12 V | 0.90 A | **5 A (60 W)** | 5.56x | 82.0% | Strip #1 (Vertex) |
| C | 12 V | 25.2 A | **50 A (600 W)** | 1.98x | 49.6% | Strips #2-#7 (Edges) |
| D | 12 V | 1.0 A | **5 A (60 W)** | 5.0x | 80.0% | Scent controller |

**Tightest margin:** PSU-C at **2.0x**. Adequate for fixed installation; any strip expansion would directly reduce this headroom.

**Optional consolidation:** PSU-B and PSU-D may merge into a single 12 V / 5 A unit (combined 1.9 A load -> 2.63x margin) to reduce the box to 3 PSUs.

WARNING **Rail isolation requirement:** Keep 5 V, 12 V (Strip #1), and 12 V (Edges) **positive rails fully isolated**. Negative/GND may share a single star point.

---

## Box Configuration Options

### Config 1 - Electrical Enclosure (Recommended for Permanent Install)

**Enclosure:** Steel DIN-rail box, ~450 x 350 x 200 mm, IP54+

**AC Input:**
- IEC C14 inlet
- 10 A 2-pole MCB (C-curve)
- 220 V AC distribution bus

**PSUs (DIN-rail mounted):**
- **PSU-A:** Mean Well RS-15-5 (5 V / 3 A)
- **PSU-B:** Mean Well RS-60-12 (12 V / 5 A) - Strip #1 (+ optionally scent)
- **PSU-C:** Mean Well **RSP-600-12** (12 V / 50 A) - Edges [**see note below**]
- **PSU-D:** 12 V / 5 A DIN-rail - scent (or merge into PSU-B)

**Protection (retained from source design):**
- F1: 7.5 A (Strip #1)
- FB1: 6-channel 7.5 A block (Edges)
- NTC1: 10 ohm / 10 A inrush limiter
- F_MAIN: T2A / F1: T1A / F3-F6: T500mA (scent)

**Cooling:** 80 mm forced-air fan (required)

**Advantages:**
- Isolated industrial-grade rails
- Independently serviceable
- Matches schematic fusing topology exactly
- Proper DIN-rail mounting

**WARNING PSU-C Correction:** The original document specified the **SE-600-12** (chassis/open-frame). For true DIN-rail mounting in Config 1, use the **RSP-600-12** instead, which is DIN-rail compatible and rated 52 A @ 12 V.

---

### Config 2 - PC Case + ATX PSU (Compact / Cost-First)

**Case:** Mid/full tower ATX, ~450 x 200 x 450 mm; built-in fans

**PSU:** Single ATX (see PSU Shortlist below). Single 12 V rail carries all loads.

**AC Input Protection:**
- 10 A MCB on 220 V AC input

**Critical Requirements:**

WARNING **MANDATORY - Retain all inline fuses.** An ATX PSU provides **no per-branch overcurrent protection**. The following are the only fault protection:
- F1 (Strip #1)
- FB1 (Edges, 6-channel)
- F_MAIN, F1-scent, F3-F6 (scent)
- NTC1 (inrush)

WARNING **PS_ON# Enable:** Pin 16 of the 24-pin ATX connector must be pulled to GND:
- Latching front-panel switch, OR
- 1 kohm resistor to GND for always-on operation

WARNING **Atomizer Moisture Isolation:** Mount the 4 atomizer drivers **outside the case** (or in a sealed sub-box). Route only the switched 12 V relay outputs into the enclosure.

**Advantages:**
- Single power cable
- Integrated cooling
- Compact form factor
- Lower cost

---

## ATX PSU Shortlist (Config 2)

**Requirements:**
- 12 V continuous: >= ~27 A (full white) with margin
- 5 V: >= 1 A (trivial)
- Single 12 V rail
- Modular preferred

**Sizing (revised 2026-07-02): right-sized to ~650 W.** The 329 W is a full-white worst case; realistic content averages ~110 W. Because the **controller box is remote** (PSU fan not audible in the room) and **sessions are short** (no continuous-duty thermal soak), the silent-zero-RPM headroom that drove the earlier 850/1000 W pick no longer applies. The only hard floor is **27.1 A on 12 V**, which a **650 W single-rail** unit clears at ~50.6 % load (329 W ÷ 650 W). The 850/1000 W tables below are retained as alternatives only if the box shares the room or runs continuously.

### Recommended tier — 650 W 80+ Bronze, single 12 V rail (~50.6 % load)

| # | Model | Watts | 12V Rail | Modular | Warranty | Efficiency | Availability |
|---|-------|-------|----------|---------|----------|-----------|--------------|
| B1 | **Thermaltake Smart BM3 Bronze 650W** | 650 W | Single ~54 A | Semi-modular | — | Bronze (ATX 3.0) | Global; check TH stock |
| B2 | **Corsair CV650** | 650 W | Single ~54 A | Non-modular | 3 yr | Bronze | Advice.co.th |
| B3 | **SilverStone VIVA650** | 650 W | Single ~54 A | Non-modular | 3 yr | Bronze | ihavecpu.com |
| B4 | MSI MAG A650BN | 650 W | Single 54 A | Non-modular | 5 yr | Bronze | Global; check TH stock |
| B5 | Enermax MarbleBron 650 | 650 W | Single 54 A | Semi-modular | — | Bronze | Global; check TH stock |

**Pick:** B1 Thermaltake Smart BM3 650W if locally stocked (semi-modular helps a ~24-cable box); else B2 Corsair CV650. Confirm **single +12 V rail** on the box. Wiring to the 12 V/5 V loads: see `NaoDec_ATX_PSU_Wiring_and_Connectors.md`.

### Higher-wattage alternatives (850 / 1000 W) — only if the box shares the room or runs continuous

| # | Model | Watts | 12V Rail | Efficiency | Est. Load @ 329 W | Price (THB) | Notes |
|---|-------|-------|----------|-----------|---:|---:|-------|
| 1 | Seasonic Focus GX-850 | 850 W | 70.8 A | Gold | 38.7% | Verify live | Original shortlist; not in 2026-06-25 ihavecpu survey |
| 2 | Corsair RM850e | 850 W | 70.8 A | Gold | 38.7% | 3,690 | ihavecpu 2026-06-25 survey; best value |
| 3 | be quiet! Pure Power 12 M 850W | 850 W | 70.8 A | Gold | 38.7% | Verify live | Original shortlist; not in 2026-06-25 ihavecpu survey |
| 4 | EVGA SuperNOVA 850 G6 | 850 W | 70.8 A | Gold | 38.7% | Verify live | Original shortlist; not in 2026-06-25 ihavecpu survey |
| 5 | Corsair RM850x | 850 W | 70.8 A | Gold | 38.7% | Verify live | Original shortlist; not in 2026-06-25 ihavecpu survey |
| 6 | be quiet! Straight Power 11 850W | 850 W | 70.8 A | Platinum | 38.7% | Verify live | Lower heat; original shortlist |
| 7 | Corsair HX850 | 850 W | 70.8 A | Platinum | 38.7% | Verify live | Lower heat; original shortlist |
| 8 | Seasonic Prime GX-1000 | 1000 W | 83.3 A | Gold | 32.9% | Verify live | More headroom; original shortlist |
| 9 | Seasonic Prime TX-1000 | 1000 W | 83.3 A | Titanium | 32.9% | Verify live | Lowest heat; original shortlist |
| 10 | FSP Hydro G Pro 1000W | 1000 W | 83.3 A | Gold | 32.9% | 5,990 | ihavecpu 2026-06-25 survey; more headroom |
| 11 | Corsair RM1000E 1000W | 1000 W | 83.3 A | Gold | 32.9% | 4,990 | ihavecpu 2026-06-25 survey; best silent option *if* stepping up to this tier |
| 12 | MSI MAG A850GN PCIE5 850W | 850 W | 70.8 A | Gold | 38.7% | 2,890 | ihavecpu 2026-06-25 survey |
| 13 | Thermaltake Toughpower GT 850W | 850 W | 70.8 A | Gold | 38.7% | 3,290 | ihavecpu 2026-06-25 survey |
| 14 | Gigabyte UD850GM PG5 V2 850W | 850 W | 70.8 A | Gold | 38.7% | 3,590 | ihavecpu 2026-06-25 survey |
| 15 | Gigabyte AORUS ELITE AE850PM PG5 | 850 W | 70.8 A | Platinum | 38.7% | 4,790 | ihavecpu 2026-06-25 survey; only Platinum in survey |
| 16 | Cooler Master ELITE 1000W | 1000 W | 83.3 A | Gold | 32.9% | 4,990 | ihavecpu 2026-06-25 survey |
| 17 | Gigabyte UD1000GM PG5 1000W | 1000 W | 83.3 A | Gold | 32.9% | 5,490 | ihavecpu 2026-06-25 survey |
| 18 | MSI MAG A1000GL PCIE5 1000W | 1000 W | 83.3 A | Gold | 32.9% | 5,990 | ihavecpu 2026-06-25 survey |

### 500 W / 550 W Cost-First Options

| # | Model | Watts | 12V Rail | Efficiency | Est. Load @ 329 W | Price (THB) | Notes |
|---|-------|-------|----------|-----------|---:|---:|-------|
| 19 | Corsair CX550 | 550 W | ~45.8 A | Bronze | 59.8% | Verify live | Cost-first fallback; active fan likely |
| 20 | Cooler Master MWE 550 Bronze V2 | 550 W | ~45.8 A | Bronze | 59.8% | Verify live | Cost-first fallback; active fan likely |
| 21 | MSI MAG A550BN | 550 W | ~45.5 A | Bronze | 59.8% | Verify live | Cost-first fallback; confirm connector count |
| 22 | SilverStone Essential ET550-B | 550 W | ~45 A | Bronze | 59.8% | Verify live | Cost-first fallback; check fan noise curve |
| 23 | FSP HV PRO 550W | 550 W | ~45 A | Bronze | 59.8% | Verify live | Cost-first fallback; active fan expected |
| 24 | Thermaltake Smart BX1 550W | 550 W | ~45 A | Bronze | 59.8% | Verify live | Cost-first fallback; active fan expected |

**500 W / 550 W note:** The related power documents put the maximum system demand at **~329 W DC**. A true 500 W PSU would run at **65.8% load**; a 550 W PSU at **59.8% load**. That is acceptable only as a budget fallback with a strong single 12 V rail, not as the preferred quiet wellness-room choice.

**Recommendation (revised 2026-07-02):** For this build (remote box, short sessions) the right-sized choice is a **650 W 80+ Bronze single-rail PSU** — B1 Thermaltake Smart BM3 650W or B2 Corsair CV650 (~50.6 % load). Step up to the 850/1000 W class *only* if the box shares the room or runs continuously; there, **Corsair RM1000E** is the best-headroom silent option and **Corsair RM850E** the best value.

**Current draw at full white:** 650 W PSU -> 329 W system = **50.6 % load**; realistic content ~110 W -> ~17 %. (850 W = 38.7 %, 1000 W = 32.9 % for the higher-wattage alternatives.)

---

## Cable & Voltage-Drop Analysis

### Copper Resistance Reference (single conductor, 20 deg C)

| AWG | mohm/m |
|-----|------|
| 12 | 5.21 |
| 16 | 13.17 |
| 18 | 20.95 |
| 22 | 52.96 |

**WS2815 operating window:** 9 V (backup-line minimum) to 13.5 V; **target >= 10.5 V** to avoid visible dimming.

### Strip #1 - Vertex (0.9 A, 20 m run from PSU)

| Gauge | Loop Length | V-drop | Strip Voltage | Status |
|-------|-------------|--------|---------------|--------|
| 18 AWG | 40 m | 0.9 x 40 x 20.95 = **754 mV** | **11.25 V** | OK Acceptable |
| 16 AWG (recommended) | 40 m | 0.9 x 40 x 13.17 = **474 mV** | **11.53 V** | OK Preferred |

**Recommendation:** Use **16 AWG** for the 20 m run. Healthier margin and eliminates dimming risk at far end of strip.

### Strips #2-#7 - Edge (4.2 A, 4 m feed + ~4.67 m strip)

**Feed cable (12 AWG, 8 m loop):**
- V-drop: 4.2 x 8 x 5.21 mohm = **0.175 V**
- Strip start voltage: **11.83 V** OK

**In-strip voltage drop** depends on PCB copper-trace resistance (no datasheet available). Using typical **60 mohm/m per conductor** and distributed-load formula `V_drop ~ I x r_loop x L / 2`:

| Scenario | Far-end Voltage | Status |
|----------|-----------------|--------|
| Single-end feed (no injection), 4.2 A over 4.67 m | ~**10.7 V** | WARNING Borderline, dimming risk |
| Mid-strip injection @ S2/S3 joint | ~**11.2-11.4 V** | OK Recommended |

**Action required:** Measure the actual strip's +V rail end-to-end resistance before final install. Then size injection point count accordingly.

---

## Mid-Strip Power Injection (All 6 Edge Strips)

### Layout
Section structure per strip: `S1 | S2 | S3 | S4 | S5` (56 LEDs / 0.933 m each)

### Primary Injection Point (mandatory)

**Location:** S2/S3 junction (~1.87 m from start)

**Feed:** Second 12 AWG pair from PSU box (~6 m run)

**Current distribution:**
- Head half (sections 1-2): 112 px -> **1.68 A**
- Far half (sections 3-5): 168 px -> **2.52 A**

**Effect:** Total PSU current unchanged; injection only redistributes delivery point. PSU-C sizing unaffected.

### Optional Secondary Injection

**Location:** S4/S5 junction (~3.73 m from start)

Flattens voltage profile further if measurement shows single injection point insufficient.

### Cable Count

Per edge strip leaving the box:
- 12 AWG head feed
- 12 AWG injection feed
- 22 AWG data

**Total exits from box:** ~24 cables (1 vertex + 6 edges x 3 + ~4 scent)
Plan enclosure cable glands / PCIe-bracket pass-throughs accordingly.

---

## Audit Findings - Corrections Applied (Rev1.0 -> Rev1.1)

Interactive diagram audited; errors found and fixed in `NaoDec_Controller_Box_Configs_Rev1.1.html`:

| # | Item | Was | Corrected | Root Cause |
|---|------|-----|-----------|-----------|
| 1 | Cable R table | ohm/1000 ft values | mohm/m values (3.28x higher) | Unit error |
| 2 | Strip #1 V-drop | 230 mV -> 11.77 V | **754 mV -> 11.25 V** | (1) |
| 3 | Edge feed V-drop | 53 mV | **175 mV** | (1) |
| 4 | Injection drops | 329 / 423 mV | **~188 / ~423 mV** | (1) + unverified trace R |
| 5 | "Worst case 53.4 A" | present | **removed** | Fabricated 30 mA/px doubling |
| 6 | Edge per-pixel | 15.8 mA | **15 mA** | Above source's 10-15 mA range |
| 7 | 12 V rail total | 27.3 / 28.7 A (conflict) | **27.1 A** | Internal inconsistency |
| 8 | Scent ESP current | 0.58 A | **0.40 A** | Source F1 branch rating |
| 9 | Scent total | 1.18 A | **~1.0 A steady** | Source PSU/fuse figures |
| 10 | PSU-C margin | 1.9x | **1.98x** | Follows from (6) |
| 11 | PSU-B margin | 2.08 A / 2.4x | **1.90 A / 2.63x** | Follows from (9) |
| 12 | ATX load % | 32.9 % | **38.7 % (850 W)** | Follows from (7) |
| 13 | Config 1 PSU-C | SE-600-12 (chassis) | **RSP-600-12 (DIN-rail)** | Config requires DIN mounting |

---

## Open Items Requiring User Input

### 1. Strip #1 Wire Gauge - RECOMMENDED CLOSURE

**Issue:** README states 18 AWG; schematic Rev1.6 states 16 AWG.

**Recommendation:** Lock in **16 AWG**. Over 20 m, the lower drop (474 mV vs 754 mV) eliminates dimming risk.

**Action:** Update source files (`README.md` + schematic Rev1.6) to 16 AWG for consistency.

### 2. Strip PCB Trace Resistance - REQUIRES MEASUREMENT

**Issue:** In-strip voltage-drop estimates (Section 6, Section 7) assume 60 mohm/m. Actual value may differ.

**Action:** Measure the target edge strip's +V rail resistance end-to-end. Then validate:
- Does single S2/S3 injection hold >= 10.5 V at strip end?
- If not, add second injection at S4/S5.

**Timeline:** Before final installation assembly.

### 3. Scent 12 V Trunk Annotation - COSMETIC (No load impact)

**Issue:** Source schematic labels trunk at 1.18 A; notes indicate 1.0 A steady-state.

**Action:** Cosmetic cleanup in source schematic; does not affect design or margins.

---

## Design Margins & Headroom Summary

| Component | Load | Rating | Margin | Risk Level |
|-----------|------|--------|--------|-----------|
| PSU-A (5 V logic) | 0.82 A | 3 A | 3.66x | Low |
| PSU-B (Strip #1) | 0.90 A | 5 A | 5.56x | Low |
| **PSU-C (Edges)** | **25.2 A** | **50 A** | **1.98x** | **Design limit** <- Tightest margin |
| PSU-D (Scent) | 1.0 A | 5 A | 5.0x | Low |
| ATX 12V rail (Config 2) | 27.1 A | 70.8-83.3 A | 2.61-3.07x | Low |
| Strip #1 voltage (16 AWG) | - | >= 10.5 V | 11.53 V | Healthy |
| Edge strips (with injection) | - | >= 10.5 V | 11.2-11.4 V | Acceptable, measurement-dependent |

**Critical constraint:** PSU-C at 2.0x margin is the tightest in the system. Any future expansion (additional strips, higher efficiency LEDs) directly reduces this headroom.

---

## References & Source Files

- `NaoDec_WS2815_LED_Controller_Rev1.6.html` - LED controller schematic
 - WS2815 specs: 10-15 mA/px
 - Channel map: 1 vertex (60 px, 0.9 A), 6 edges (280 px ea, 4.2 A each)
 
- `NaoDec_Scent_Controller_Schematic_Rev2.0.html` - scent controller schematic
 - ESP32-S3-Relay-6CH: 0.40 A @ 12 V
 - 4 x JY-M27AO atomizers: 0.15 A each
 - Protection: F_MAIN T2A, individual fuses T500mA
 
- `NaoDec_Controller_Box_Configs_Rev1.1.html` - interactive configuration diagram (audited, corrections applied)

- `README.md` - project overview, revisions table, bill of materials

---

## Revision History

| Revision | Date | Changes |
|----------|------|---------|
| 1.0 | 2026-06-14 | Initial power budget & box configuration report |
| 1.1 | 2026-06-17 | Full audit: 13 corrections applied; PSU-C DIN mounting corrected; ATX load % recalculated; Strip #1 wire gauge recommendation added |

---

## Sign-Off

**Report Status:** Audited and verified. All arithmetic cross-checked. Ready for implementation.

**Pending Actions:**
1. Decide: 16 AWG for Strip #1? (recommended: yes)
2. Decide: RSP-600-12 (DIN) or bracket for SE-600-12 (chassis) in Config 1?
3. Measure: Edge strip PCB +V rail resistance before final assembly.

**Next Phase:** Board layout, cable routing, thermal analysis (PSU-C convection in enclosure).


