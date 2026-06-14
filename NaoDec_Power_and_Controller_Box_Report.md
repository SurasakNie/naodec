# NaoDec — Power Requirements & Controller Box Report

**Project:** NaoDec — 7-channel WS2815 LED installation + 4-channel scent controller
**Document revision:** 1.0
**Date:** 2026-06-14
**Scope:** Consolidated power budget, PSU selection, single-box mounting options
(electrical enclosure vs. ATX PC case), cable/voltage-drop analysis, and the
audit of all figures.

> Companion interactive diagram: `NaoDec_Controller_Box_Configs_Rev1.1.html`
> Source schematics: `NaoDec_WS2815_LED_Controller_Rev1.6.html`,
> `NaoDec_Scent_Controller_Schematic_Rev2.0.html`

---

## 1. Executive Summary

- Two controllers are to be co-located in **one control box**, fed from a single
  **220 V AC** input.
- Two box options are documented:
  - **Config 1 — Electrical enclosure** with 3–4 isolated DIN-rail PSUs (truest to
    the source design; recommended for a permanent install).
  - **Config 2 — ATX PC case** with a single ATX PSU (compact, lower cost; viable
    with mandatory inline fusing retained).
- **Existing PSU specs are valid.** No PSU resizing is required.
- The 6 long edge strips (5 m strip + 4 m feed each) **require mid-strip power
  injection** to hold end-of-strip voltage up.
- All power figures in this report have been **audited and recalculated**; the
  corrections are listed in §9.

---

## 2. System Overview

| Subsystem | Controller | Firmware | Outputs |
|-----------|-----------|----------|---------|
| LED | 2× ESP32-S3-WROOM-1 N16R8 (Master + DDP Slave) + SN74AHCT245N level shifter | WLED | 7 channels · 1,740 × WS2815 |
| Scent | Waveshare ESP32-S3-Relay-6CH | WLED | 4 × JY-M27AO ultrasonic atomizers (113 kHz) |

**LED channel map**

| CH | Source | Strip | LEDs | Cable | Power AWG |
|----|--------|-------|------|-------|-----------|
| 1 | Master GPIO1 | #1 Vertex | 60 | ~20 m | 16–18 |
| 2–4 | Master GPIO4/5/6 | #2–#4 Edge | 280 ea | ~4 m + 5 m strip | 12 |
| 5–7 | Slave GPIO4/5/6 | #5–#7 Edge | 280 ea | ~4 m + 5 m strip | 12 |

Each edge strip = **5 sections × 56 LEDs = 280** (60 LED/m strip, 4 LEDs cut per
section → ~0.933 m/section, ~4.67 m total).

---

## 3. Device-by-Device Power Inventory

### WS2815 (per source schematic: 10–15 mA/px @ 12 V; design max **15 mA/px**)

| Device | Rail | Current | Power |
|--------|------|---------|-------|
| ESP32-S3 Master | 5 V | ~0.40 A | 2.0 W |
| ESP32-S3 Slave | 5 V | ~0.40 A | 2.0 W |
| SN74AHCT245N (U2) | 5 V | ~0.02 A | 0.1 W |
| **5 V logic subtotal** | **5 V** | **~0.82 A** | **~4.1 W** |
| Strip #1 — Vertex (60 px) | 12 V | 0.90 A | 10.8 W |
| Strips #2–#7 — Edge (6 × 280 px) | 12 V | 25.2 A | 302 W |
| **12 V LED subtotal** | **12 V** | **26.1 A** | **~313 W** |

### Scent

| Device | Rail | Current | Power |
|--------|------|---------|-------|
| ESP32-S3-Relay-6CH | 12 V | ~0.40 A | 4.8 W |
| 4 × JY-M27AO atomizer drivers | 12 V | 4 × 0.15 A = 0.60 A | 7.2 W |
| **Scent subtotal** | **12 V** | **~1.0 A** | **~12 W** |

> The source schematic labels the 12 V trunk wire at **1.18 A** — that is a
> conservative wire-rating figure; the steady-state load is **~1.0 A** (per the
> PSU note "5× margin over 1.0 A" and the F_MAIN 2.0× fuse margin).

### Combined totals

| Rail | Current | Power |
|------|---------|-------|
| 5 V | ~0.82 A | ~4 W |
| 12 V (LED + scent, full white) | **~27.1 A** | **~325 W** |
| **System total** | — | **~329 W** |

There is **no higher "full-white worst case"** — 15 mA/px already *is* the source
schematic's full-white figure for WS2815.

---

## 4. PSU Requirements

| PSU | Rail | Min load | Specified | Margin | Powers |
|-----|------|---------|-----------|--------|--------|
| A | 5 V | 0.82 A | **3 A (15 W)** | 3.7× | LED logic (2× ESP + U2) |
| B | 12 V | 0.90 A | **5 A (60 W)** | 5.6× | Strip #1 (Vertex) |
| C | 12 V | 25.2 A | **50 A (600 W)** | 2.0× | Strips #2–#7 (Edges) |
| D | 12 V | 1.0 A | **5 A (60 W)** | 5.0× | Scent controller |

All four existing PSUs are **valid as specified**. PSU-B and PSU-D may optionally
be merged into a single 12 V / 5 A unit (combined load 1.9 A → 2.6× margin) to
reduce the box to 3 PSUs.

> ⚠ **Rail isolation:** keep the 5 V, 12 V (Strip #1) and 12 V (Edges) **positive**
> rails fully isolated. Negative/GND may share a single star point.

---

## 5. Box Configuration Options

### Config 1 — Electrical Enclosure (recommended for permanent install)

- **Enclosure:** steel DIN-rail box, ~450 × 350 × 200 mm, IP54+.
- **AC input:** IEC C14 inlet → 10 A 2-pole MCB (C-curve) → 220 V AC distribution bus.
- **PSUs (DIN rail):**
  - PSU-A: Mean Well RS-15-5 (5 V / 3 A)
  - PSU-B: Mean Well RS-60-12 (12 V / 5 A) — Strip #1 (+ optionally scent)
  - PSU-C: Mean Well SE-600-12 (12 V / 50 A) — Edges
  - PSU-D: 12 V / 5 A DIN — scent (or merge into PSU-B)
- **Protection retained:** F1 7.5 A (Strip #1), FB1 6-ch 7.5 A block (Edges),
  NTC1 10 Ω/10 A inrush, F_MAIN T2A / F1 T1A / F3–F6 T500mA (scent).
- **Cooling:** add an 80 mm forced-air fan.
- **Pros:** isolated industrial rails, independently serviceable, matches the
  schematic fusing topology exactly.

### Config 2 — PC Case + ATX PSU (compact / cost-first)

- **Case:** mid/full tower ATX, ~450 × 200 × 450 mm; built-in fans.
- **PSU:** single ATX (see §8). 12 V single rail carries everything.
- ⚠ **CRITICAL — retain all inline fuses.** An ATX PSU provides **no per-branch
  overcurrent protection**; F1, FB1, F_MAIN, F1-scent, F3–F6 and NTC1 are the only
  fault protection. Add a 10 A MCB on the AC input.
- ⚠ **PS_ON# enable:** pin 16 of the 24-pin connector must be pulled to GND
  (latching front-panel switch, or 1 kΩ to GND for always-on).
- ⚠ **Atomizer moisture:** mount the 4 atomizer drivers **outside** the case (or in
  a sealed sub-box); route only the switched 12 V relay outputs out.
- **Pros:** single power cable, integrated cooling, compact, lower cost.

---

## 6. Cable & Voltage-Drop Analysis

**Copper resistance used (single conductor, 20 °C):**

| AWG | mΩ/m |
|-----|------|
| 12 | 5.21 |
| 16 | 13.17 |
| 18 | 20.95 |
| 22 | 52.96 |

WS2815 operating window: ~9 V min … 13.5 V max; aim ≥ 10.5 V to avoid visible
dimming.

### Strip #1 — Vertex (0.9 A, 20 m run)

| Gauge | Loop length | V-drop | Strip voltage |
|-------|------------|--------|---------------|
| 18 AWG | 40 m | 0.9 × 40 × 20.95 mΩ = **0.754 V** | **11.25 V** ✅ |
| 16 AWG (recommended) | 40 m | 0.9 × 40 × 13.17 mΩ = **0.474 V** | **11.53 V** ✅ |

Both are within spec; 16 AWG gives a healthier margin for the long run.

### Strips #2–#7 — Edge (4.2 A, 4 m feed + ~4.67 m strip)

**Feed cable (12 AWG, 8 m loop):** 4.2 × 8 × 5.21 mΩ = **0.175 V** → strip start ≈ 11.83 V.

**In-strip drop** depends on the strip's PCB copper-trace resistance, which we do
**not** have a datasheet figure for. Using a *typical* 60 mΩ/m per conductor and
the distributed-load relation `V_drop ≈ I × r_loop × L / 2`:

| Scenario | Far-end voltage (estimate) |
|----------|---------------------------|
| Single-end feed (no injection), 4.2 A over 4.67 m | ~**10.7 V** — borderline, dimming risk |
| Mid-strip injection at S2/S3 joint | ~**11.2–11.4 V** ✅ |

➡ **These in-strip numbers are estimates.** Confirm by measuring the strip's +V
rail end-to-end resistance before final install, then size injection accordingly.

---

## 7. Mid-Strip Power Injection (all 6 edge strips)

Section layout (each strip): `S1 | S2 | S3 | S4 | S5`, 56 LEDs / 0.933 m each.

- **Inject at the S2/S3 junction** (~1.87 m from start), fed by a second 12 AWG
  pair from the box (~6 m run).
- Current split: head half (sections 1–2) = 112 px → **1.68 A**; far half
  (sections 3–5) = 168 px → **2.52 A**.
- The total PSU current is unchanged — injection only changes *where* it is
  delivered, so PSU-C sizing is unaffected.
- Optional second injection at the S4/S5 junction (~3.73 m) flattens the profile
  further if measurement shows the single point is insufficient.

**Cable count leaving the box (per edge strip):** 12 AWG head feed + 12 AWG
injection feed + 22 AWG data. Plan box cable glands / PCIe-bracket pass-throughs
for ~24 total cable exits.

---

## 8. ATX PSU Shortlist (Config 2)

Required: 12 V continuous ≥ ~27 A (full white) with margin; 5 V ≥ 1 A (trivial);
single 12 V rail; modular preferred. **850 W is sufficient** (~38 % load — the
efficiency sweet spot); **1000 W** adds headroom and runs cooler/quieter.

| # | Model | Watts | 12 V | Efficiency |
|---|-------|-------|------|-----------|
| 1 | Seasonic Focus GX-850 | 850 W | 70.8 A | Gold |
| 2 | Corsair RM850e | 850 W | 70.8 A | Gold |
| 3 | be quiet! Pure Power 12 M 850W | 850 W | 70.8 A | Gold |
| 4 | EVGA SuperNOVA 850 G6 | 850 W | 70.8 A | Gold |
| 5 | Corsair RM850x | 850 W | 70.8 A | Gold |
| 6 | be quiet! Straight Power 11 850W | 850 W | 70.8 A | Platinum |
| 7 | Corsair HX850 | 850 W | 70.8 A | Platinum |
| 8 | Seasonic Prime GX-1000 | 1000 W | 83.3 A | Gold |
| 9 | Seasonic Prime TX-1000 | 1000 W | 83.3 A | Titanium |
| 10 | FSP Hydro G Pro 1000W | 1000 W | 83.3 A | Gold |

Platinum/Titanium units (#6, #7, #9) produce less waste heat — preferable inside
an enclosed case.

---

## 9. Audit Findings — Corrections Applied (Rev1.0 → Rev1.1)

The interactive diagram was audited; the following errors were found and fixed in
`NaoDec_Controller_Box_Configs_Rev1.1.html` (Rev1.0 archived to `Archived/`):

| # | Item | Was | Corrected | Cause |
|---|------|-----|-----------|-------|
| 1 | Cable resistance table | Ω/1000 ft values | mΩ/m values (3.28× higher) | Unit error |
| 2 | Strip #1 V-drop | 230 mV → 11.77 V | **754 mV → 11.25 V** | (1) |
| 3 | Edge feed V-drop | 53 mV | **175 mV** | (1) |
| 4 | Injection drops | 329 / 423 mV → ≥11.52 V | **~188 / ~423 mV, ~11.2–11.4 V (est.)** | (1) + unverified trace R |
| 5 | "Worst case 53.4 A" | present | **removed** | Fabricated 30 mA/px doubling |
| 6 | Edge per-pixel | 15.8 mA → 26.6 A | **15 mA → 25.2 A** | Above source's 10–15 mA range |
| 7 | 12 V rail total | 27.3 A / 28.7 A (conflicting) | **27.1 A** (consistent) | Internal inconsistency |
| 8 | Scent ESP current | 0.58 A | **0.40 A** | Source F1 branch = 0.40 A |
| 9 | Scent total | 1.18 A | **~1.0 A steady** | Source PSU/fuse figures |
| 10 | PSU-C margin | 1.9× | **2.0×** | Follows from (6) |
| 11 | PSU-B margin | 2.08 A / 2.4× | **1.90 A / 2.6×** | Follows from (9) |
| 12 | ATX load % | 32.9 % only | **38.3 % (850 W) / 32.7 % (1000 W)** | Follows from (7) |
| 13 | SE-350-12 alt | "for ~30 % cap" | "**1.15× headroom — only with WLED ABL cap**" | True full-white load |

---

## 10. Open Items (require user input / source data)

1. **Strip #1 wire gauge conflict in source files** — README states 18 AWG; the LED
   schematic (Rev1.6) states 16 AWG. Recommend **16 AWG** (lower drop). Source
   files left unchanged pending decision.
2. **Strip PCB trace resistance** — the in-strip voltage-drop figures (§6, §7) are
   estimates at 60 mΩ/m. **Measure the actual strip's +V rail resistance** to
   finalize injection point count.
3. **Scent total label in source schematic** — 1.18 A (wire annotation) vs 1.0 A
   (PSU/fuse notes); cosmetic, not load-affecting.

---

## 11. References

- `NaoDec_WS2815_LED_Controller_Rev1.6.html` — LED controller schematic (WS2815 = 10–15 mA/px; 4.2 A/strip; 25.2 A edges; 0.9 A vertex)
- `NaoDec_Scent_Controller_Schematic_Rev2.0.html` — scent controller (ESP 0.40 A; 4 × 150 mA atomizers; F_MAIN T2A)
- `NaoDec_Controller_Box_Configs_Rev1.1.html` — interactive box-configuration diagram (audited)
- `README.md` — project overview & revisions table
