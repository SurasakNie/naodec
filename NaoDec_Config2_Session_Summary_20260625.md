# NaoDec — Config 2 Working Session Summary

**Date:** 2026-06-25
**Topic:** Power review, audio-integration analysis, ATX PSU selection, and a combined
Config 2 wiring schematic for the NaoDec WS2815 LED + scent controller box.
**Outcome:** Audio descoped to a separate 24 V subsystem; Config 2 finalized on a single
Corsair HX850 ATX; combined wiring schematic built and a component list produced.

---

## 1. Document review (starting point)

Reviewed the existing files and found they are technically sound but **inconsistent across versions**:

- The interactive diagram is named `Rev1.1` but its content is effectively Rev1.0 — subtitle still reads "REV 1.0", PSU-C still SE-600-12, Strip #1 still 18 AWG, ATX load % still 38.3 %.
- The two markdown reports disagree on **audit item #13** (SE-350-12 headroom note vs SE-600-12→RSP-600-12 DIN-mount correction), on **PSU-C margin** (2.0× vs 1.98×), and on **ATX load %** (38.3 % vs 38.7 %).
- Recommendation made: make the HTML a true Rev1.1, retire the older 06-14 report, and split the double-meaning audit #13. (Not yet executed.)

The underlying engineering math (LED currents, voltage drops, injection splits) checked out.

---

## 2. Config 2 power inventory

Worst-case (full white + all scent on), single ATX:

| Rail | Load | Power |
|---|---|---|
| 5 V (2× ESP32 + level shifter) | 0.82 A | ~4 W |
| 12 V (LEDs 26.1 A + scent 1.0 A) | 27.1 A | ~325 W |
| **System total (DC)** | — | **~329 W** |
| **AC mains** | ~1.6 A @ 220 V | ~358 W |

**Key insight — the LEDs are ~99 % of the load.** Everything else (both ESPs, level
shifter, scent board, atomizers) totals ~16 W.

## 3. "Do the LEDs really draw that much?" — No

313 W is the **full-white worst case** (15 mA/px). Real operation is far lower:
- Brightness scales current ~linearly; color matters (white = all 3 channels).
- Realistic wellness-room operation: **~60–150 W on 12 V**, not 313 W.
- You still **size** for worst case (WLED can be commanded to full white); WLED's ABL can hard-cap current if desired.

Wiring was discussed: long runs don't add to LED consumption — they cause **voltage drop**.
The design already handles this (longest run = lowest-current vertex; high-current edges kept
short; **mid-strip injection** mandated on all 6 edges). Open item: measure actual strip
trace resistance to confirm one injection point per strip is enough.

---

## 4. Audio addition analysis (then descoped)

Components considered: **WONDOM GAB8** amplifier, **6× Microlab Satellite X3**, **Edifier T5** subwoofer.

**Findings:**
- The audio is a **separate power subsystem** — none of it loads the ATX.
- **GAB8 needs 24 V** (15–30 V range); an ATX cannot supply 24 V, and 12 V is below the GAB8's 15 V minimum → it requires its own **24 V supply** (e.g. Mean Well LRS-240-24).
- The **6 Microlab satellites are passive** — driven by the GAB8, not separate loads.
- The **Edifier T5 is self-powered** (own AC plug + internal amp) — only takes a line-level signal.
- Speakers' wattage ratings = power handling, **not** consumption.
- Audio worst case ≈ 145 W (GAB8) + 120 W (T5, own plug); combined system AC worst case ≈ 645 W (~2.9 A), still well within the 10 A MCB.

**Decision:** **GAB8/audio excluded** from "this system" (it's on 24 V). The audio is documented
separately in `NaoDec_Config2_Audio_Integration_20260622.md` as a deferred 24 V subsystem.

> Opinion recorded: once a 24 V audio rail is added, Config 1 (DIN enclosure) becomes cleaner
> than Config 2 for a permanent install — adding 24 V is just one more DIN PSU. For audio-clean
> results, a partitioned/separate audio box is preferred.

---

## 5. ATX PSU selection — Corsair HX850 (#7)

Compared the three short-listed 850–1000 W units. Audio doesn't change the choice (it isn't on the ATX);
at ~329 W the ATX runs ~39 % loaded (efficiency sweet spot), so the tie-breaker is **heat/noise**.

| | #6 be quiet! Straight Power 11 | **#7 Corsair HX850** | #9 Seasonic Prime TX-1000 |
|---|---|---|---|
| Efficiency | Platinum | Platinum | Titanium |
| Fan at ~39 % load | always on (quiet) | **zero-RPM (silent)** | fanless (silent) |
| Warranty | 5 yr | **10 yr** | 12 yr |
| Price | ~$150 | ~$160 | ~$290–310 |

**Pick: #7 Corsair HX850** — silent fan-off at this load, 10-yr warranty, right-sized.
(#9 only if you want lowest heat + headroom and don't mind ~2× cost.)

---

## 6. Rev 1.6 LED controller schematic review

The source `NaoDec WS2815 LED Controller — 12VDC — Rev 1.6` is **solid**: correct level-shifter
config, 47 Ω source termination, WS2815 backup-data-line wiring, star-point grounding, decoupling.

Two items to reconcile before build:
1. **No mid-strip injection drawn** on the edge strips (the power report requires it).
2. **CH1's 20 m run** is a signal-integrity risk (the schematic flags it) — bench-verify or add a differential driver.

For the **HX850/Config 2** build: the Rev 1.6's three separate supplies (5 V/3 A, 12 V/5 A, 12 V/50 A)
**collapse onto the single ATX 12 V bus + 5 V rail**; everything downstream (NTC1, FB1, fuses, caps,
termination, data) stays identical.

---

## 7. Combined Config 2 wiring schematic — built

Produced `NaoDec_Config2_Combined_Wiring_Rev1.0.html` via the html-schematic skill:
- Merges the Rev 1.6 LED controller + scent controller onto one HX850 ATX (three rails → one 12 V bus).
- AC input (IEC C14, 10 A MCB, PS_ON# enable), NTC1, F1, FB1, bulk caps.
- **Mid-strip injection shown on all 6 edge strips** (reconciles the Rev 1.6 gap).
- Scent: Waveshare relay board, F_MAIN/scent fuses, RC snubbers, atomizers in a dashed external sub-box.
- Bottom panels: BOM, wire-gauge, harness/pinout tables, notes + revision history.
- Verified: 0 console errors, 48 components, 22 BOM rows, 0 hardcoded hex.

**Legibility pass:** brightened the muted label color (#8888A0 → #B6BAD2), channel labels 10 px bold,
BOM 12 px, strip titles 16 px / specs 12 px, and bumped all 9–10 px text to 11 px globally.
Verified **0 text overlaps** via DOM geometry check after the changes.

---

## 8. Deliverables created this session

| File | Purpose |
|---|---|
| `NaoDec_Config2_Audio_Integration_20260622.md` | Audio (GAB8 + speakers + sub) analysis — deferred 24 V subsystem |
| `NaoDec_Config2_Combined_Wiring_Rev1.0.html` | Combined Config 2 wiring schematic (LED + scent on HX850) |
| `NaoDec_Config2_Component_List_20260624.md` | Full Config 2 bill of materials (22 line items, ~50 parts) |
| `NaoDec_Config2_Session_Summary_20260625.md` | This summary |

---

## 9. Open items / next steps

1. **Reconcile the source docs** — make the interactive diagram a true Rev1.1; retire the 06-14 report; fix audit #13's double meaning; lock Strip #1 at 16 AWG and PSU-C at RSP-600-12 (DIN).
2. **Bench-verify the 20 m CH1 data run**; add a differential driver if it fails.
3. **Measure edge-strip +V trace resistance** to confirm one mid-strip injection point per strip suffices.
4. **Audio (if/when pursued):** add a dedicated 24 V supply for the GAB8; keep the Edifier T5 on its own AC plug; consider Config 1 (DIN) or a partitioned audio box for clean power.
5. Optionally bump the combined schematic to Rev 1.1 and log the clarity edits.
