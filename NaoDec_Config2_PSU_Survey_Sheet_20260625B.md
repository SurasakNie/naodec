# NaoDec - Config 2 PSU Market Survey Sheet Session

**Date:** 2026-06-25 (Session B)
**Topic:** Build and format the PSU Market Survey Google Sheet at ihavecpu.com
**Outcome:** Completed 11-column table with color coding, load %, fan noise ratings,
and pick labels - all data verified and column order finalized.

---

## Sheet link

[NaoDec Config 2 - PSU Market Survey (ihavecpu.com)](https://docs.google.com/spreadsheets/d/1ZUJ49EZ5-Fg2cFUbCkCBeJARMCSUVuzcM7GiZRs8OgM/edit)

---

## System context

- **Load:** 329 W worst-case DC on 12 V rail (NaoDec WS2815 LED + scent controller)
- **Target PSU:** 850-1000 W ATX, Gold/Platinum or better, semi-fanless or zero-RPM
- **Retailer surveyed:** ihavecpu.com (Thailand, prices in THB)
- **Load % benchmarks:** 329 W / 850 W = **38.7 %** | 329 W / 1000 W = **32.9 %**
- **Key criterion:** Fan stays OFF below ~40 % load in semi-fanless / Zero RPM mode -> silent operation for wellness room

---

## PSU models surveyed

### 850 W section

| # | Model | Efficiency | Warranty | Price (THB) | Discount | Load % | Fan Noise | Pick |
|---|---|---|---|---|---|---|---|---|
| 1 | MSI MAG A850GN PCIE5 850W | Gold | 7Y | 2,890 | - | 38.70% | Semi-fanless | |
| 2 | Thermaltake Toughpower GT 850W | Gold | 5Y | 3,290 | -8% | 38.70% | Semi-fanless | |
| 3 | Gigabyte UD850GM PG5 V2 850W | Gold | 5Y | 3,590 | -18% | 38.70% | Semi-fanless | |
| 4 | Corsair RM850E 850W | Gold | 7Y | 3,690 | -14% | 38.70% | Borderline silent | * Best Value |
| 5 | Gigabyte AORUS ELITE AE850PM PG5 | Platinum | 10Y | 4,790 | - | 38.70% | Near-silent (Platinum) | * Only Platinum |

### 1000 W section

| # | Model | Efficiency | Warranty | Price (THB) | Discount | Load % | Fan Noise | Pick |
|---|---|---|---|---|---|---|---|---|
| 6 | Corsair RM1000E 1000W | Gold | 7Y | 4,990 | -22% | 32.90% | Silent | * Best Headroom |
| 7 | Cooler Master ELITE 1000W | Gold | 5Y | 4,990 | - | 32.90% | Active fan | |
| 8 | Gigabyte UD1000GM PG5 1000W | Gold | - | 5,490 | - | 32.90% | Semi-fanless | |
| 9 | MSI MAG A1000GL PCIE5 1000W | Gold | 7Y | 5,990 | - | 32.90% | Semi-fanless | |
| 10 | FSP VITA GM 1000W | Gold | 10Y | 5,990 | - | 32.90% | Semi-fanless | |

---

## Three starred picks - comparison

| | * Best Value | * Only Platinum | * Best Headroom |
|---|---|---|---|
| **Model** | Corsair RM850E 850W | Gigabyte AORUS ELITE AE850PM PG5 | Corsair RM1000E 1000W |
| **Price** | 3,690 THB (after -14%) | 4,790 THB | 4,990 THB (after -22%) |
| **Efficiency** | Gold (87-89%) | Platinum (89-92%) | Gold (87-89%) |
| **Warranty** | 7 years | 10 years | 7 years |
| **Load at 329 W** | 38.7% | 38.7% | 32.9% |
| **Fan behavior** | Fan off below ~40% (borderline) | Fan off below ~40% (quiet Platinum) | Fan fully off at 32.9% (silent) |
| **Heat output** | Moderate (Gold efficiency) | Less heat (Platinum runs cooler) | Slightly less heat than 850W Gold |
| **Best for** | Budget-conscious, silent enough | Best efficiency + quietest at this wattage | Most headroom, deepest in Zero RPM zone |

**Fan noise reasoning at 329 W:**
- RM850E (38.7%): right at the zero-RPM threshold - fan may spin intermittently under transient peaks
- AORUS ELITE (38.7%): Platinum efficiency means less heat generated -> fan threshold triggered less often
- RM1000E (32.9%): well below 40% -> fan stays off reliably; no borderline behavior

**Overall recommendation (unchanged from prior session):** Corsair RM1000E is the safest
silent-operation choice for a wellness room. If budget is the constraint, Corsair RM850E is
the next best and will be mostly silent in practice.

---

## Sheet formatting

| Element | Format |
|---|---|
| Header row (row 1) | Dark green background, white bold text |
| Section dividers (rows 2, 8) | Light green background (" - 850W - ", " - 1000W - ") |
| Starred picks (rows 6, 7, 9) | Light yellow #FFF2CC background |
| Standard rows | White |
| Product Link column | Hyperlinked "View ->" text |

---

## Final column order (A -> K)

```
A #
B Model
C Wattage
D Efficiency
E Warranty
F Price (THB)
G Discount
H Load %
I Fan Noise
J Pick
K Product Link
```

---

## Work done this session

1. Browsed ihavecpu.com PSU category, scraped 10 in-stock 850-1000 W models
2. Built the Google Sheet Table1 with rows 1-13 (header + 2 dividers + 10 products)
3. Applied color formatting to header, dividers, and starred rows
4. Added **Load %** column (H) - calculated from 329 W / rated wattage
5. Added **Fan Noise** column - researched each model's fan control spec
6. Wrote comparison of the 3 starred picks including fan/noise/heat analysis
7. Reordered columns: moved Load % and Fan Noise ahead of Pick and Product Link
 - Final order: ... Discount | **Load %** | **Fan Noise** | Pick | Product Link

### Column reorder technical notes (Google Sheets quirks)

- Native Table format blocks "Cut -> Insert cut cells" - had to use `left_click_drag` on column headers instead
- Column must be **pre-selected** (single-column blue highlight) before dragging; starting a drag from a non-selected header creates a range selection instead of a column move
- `Tab` character inside `type` actions embeds a literal tab into a cell - entering multi-column data requires separate clicks per cell
- `key: "Return"` inside `browser_batch` fails; use `type: "\n"` instead

---

## Open items (carried forward)

1. Reconcile source docs - make interactive diagram a true Rev1.1; fix audit #13; lock Strip #1 at 16 AWG, PSU-C at RSP-600-12
2. Bench-verify 20 m CH1 data run (physical lab work)
3. Measure edge-strip trace resistance (physical lab work)
4. Final PSU purchase decision - RM1000E recommended for silent wellness-room use
---

## 2026-07-01 Update - Price Column, 500 W Options, and Max Power Check

### Source and pricing status

- 850 W and 1000 W prices below are from the previously verified ihavecpu.com survey in this document.
- Live ihavecpu.com product search was not text-accessible during this update; the site homepage loaded, but search/product data did not expose usable rows through the text fetch.
- Live Advice.co.th search page loaded and exposed its backend configuration, but product rows are client-rendered and were not directly extractable in this environment.
- Treat prices as market-check values, not purchase locks. Reconfirm at checkout.

### Maximum overall power requirement from related documents

| Source document | Evidence | Requirement |
|---|---|---|
| `NaoDec_Power_Report_Complete_20260617.md` | Combined system totals: 5 V logic ~4.1 W; 12 V LED + scent ~27.1 A / ~325.2 W; System Total ~329 W | **~329 W max DC system power** |
| `NaoDec_Power_and_Controller_Box_Report_20260614.md` | Combined totals repeat 12 V full-white ~27.1 A / ~325 W and System total ~329 W; notes no higher full-white worst case exists | **~329 W max DC system power** |
| `NaoDec_WS2815_LED_Controller_Rev1.6_BOM.txt` | LED count 1,740; Strip #1 ~0.9 A; Strips #2-#7 ~25.2 A max; 12 V / 50 A PSU required for edges | Supports LED subtotal of **~26.1 A at 12 V** |
| `NaoDec_WS2815_LED_Controller_Rev1.6_ItemList.csv` | Edge rail shared by Strips #2-#7; total max ~25.2 A; Strip #1 max ~0.9 A | Supports LED subtotal of **~26.1 A at 12 V** |

**Conclusion:** the maximum overall requirement found in related docs is **~329 W DC** for the complete LED + scent system at full-white design maximum. The controlling rail is **12 V at ~27.1 A (~325 W)**. A 500 W ATX PSU would run at **65.8% load** at this maximum; electrically possible if it has a strong single 12 V rail, but it is outside the original silent-operation target because the fan will likely run.

### 500 W ATX options to compare

| # | Model | Watts | 12V Rail | Efficiency | Est. Load @ 329 W | Price (THB) | Notes |
|---|---|---:|---:|---|---:|---:|---|
| 11 | Corsair CX550 | 550 W | ~45.8 A | Bronze | 59.8% | Verify live | Better than true 500 W; common budget option |
| 12 | Cooler Master MWE 550 Bronze V2 | 550 W | ~45.8 A | Bronze | 59.8% | Verify live | Common Thailand-market budget option |
| 13 | MSI MAG A550BN | 550 W | ~45.5 A | Bronze | 59.8% | Verify live | Budget ATX option; confirm connector count |
| 14 | SilverStone Essential ET550-B | 550 W | ~45 A | Bronze | 59.8% | Verify live | Budget option; check fan noise curve |
| 15 | FSP HV PRO 550W | 550 W | ~45 A | Bronze | 59.8% | Verify live | Budget option; active fan expected |
| 16 | Thermaltake Smart BX1 550W | 550 W | ~45 A | Bronze | 59.8% | Verify live | Budget option; active fan expected |

**500 W / 550 W assessment:** acceptable only as a cost-first fallback. It gives enough 12 V current on paper, but it loses the main benefit of Config 2's 850-1000 W recommendation: low fan noise and thermal headroom. For the wellness-room use case, keep **Corsair RM1000E** as the preferred silent option and **Corsair RM850E** as the budget silent-enough option.

