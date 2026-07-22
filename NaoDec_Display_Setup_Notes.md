# NaoDec — Department Store Display Setup: Team Notes

**Purpose:** internal briefing that walks the team through *how* every number in
[`NaoDec_Display_Setup_Requirements.md`](NaoDec_Display_Setup_Requirements.md) (the store-facing
deliverable) was derived — the reasoning, sources, and revision history behind the figures, so
anyone picking this up mid-project has full context without re-deriving it.

**Companion document:** `NaoDec_Display_Setup_Requirements.md` v1.7 (2026-07-22) — send that one
to the store; use this one internally.

---

## 1. Executive Summary

| Question | Answer |
|---|---|
| Power requirement | **~1.0 kW continuous** (1.25× of ~792 W current draw), ~1.37 kW transient peak |
| Main input | **220 V single-phase**, dedicated **16 A** circuit (TIS 166-2549) |
| Operating pattern | **10 hrs/day** (not 24/7) → no backup power needed; ~7.9 kWh/day |
| Total floor area | **4 m × 5.5 m (22 m²)** allocated; structure occupies a 3×3 m zone within it |
| Structure size | **3 m × 3 m × 2.5 m (W×L×H)** — fits under the 2.75 m min ceiling with ~0.25 m margin |
| Structural design load | **~345 kg** over the structure's 9 m² footprint ≈ **38 kg/m²** (incl. occupant rated max 100 kg) |
| Logistics bottleneck | **Chair platform (1.91 m × 1.82 m)** — largest single component; confirm elevator/door clearance before committing to elevator delivery |
| Biggest open item | Elevator/gate/trolley specs from the store — not yet known |

---

## 2. Space & Structure

- **Total allocated floor area:** 4 m × 5.5 m = **22 m²**.
- **Structure footprint:** 3 m × 3 m = **9 m²**, sitting inside the allocated area.
- **Structure height:** **2.5 m** (W × L × H = 3 m × 3 m × 2.5 m) — this is the real, confirmed
  dimension. It fits under the store's **minimum 2.75 m** ceiling clearance with **~0.25 m**
  margin; keep that margin clear of the platform/riser.
- **Operator station** (table, controller unit, Mac mini, monitor) sits **outside** the 3×3 m
  structure zone, in the remaining ~13 m² of the allocated area.
- One nuance worth flagging to the team: the structure's height (2.5 m) sits **exactly at** the
  template's ">2.5 m mandatory stability-certification" threshold, not strictly over it. We're
  recommending certification anyway given the structure is occupied and carries a ~345 kg load —
  don't skip it on a technicality.

---

## 3. Power Requirement — full derivation

**The rule:** provisioning target = **1.25× the current setup's continuous operating draw**,
main input 220 V single-phase, 10 hrs/day operation (so no backup power requirement).

### 3.1 Connected-load inventory (every device, AC mains draw)

| # | Item | Typical | Rated/Peak | Basis |
|---|------|--------:|-----------:|-------|
| A | Control box — LED strips (1,740× WS2815 @ 15 mA/px full white) + 5 V logic + scent controller | ~387 W | ~387 W | Audited **329 W DC** ÷ 0.85 PSU efficiency |
| B | Mac mini (media/show host) | ~65 W | ~90 W | Apple-silicon typical |
| C | Operator monitor | ~50 W | ~50 W | 24–27″ desktop display |
| D | 2× cooling fans @ 38 W | ~76 W | ~76 W | Nameplate (measured) |
| E | Media playback controller (standalone, 5 V/2 A adapter) | ~12 W | ~12 W | Build docs |
| F | Wondom GAB8 amp on Mean Well LRS-350-24 (drives 6 speakers + 4 transducers) | ~120 W | ~400 W | PSU ceiling; typical ≈ ⅓ |
| G | Edifier T5 active subwoofer (70 W RMS) | ~70 W | ~100 W | Manufacturer spec |
| H | Router — ASUS RT-AX1800HP (in controller unit) | ~12 W | ~18 W | Typical 12 V/1.5 A adapter class |
| | **Continuous subtotal (A–H)** | **~792 W** | **~1,133 W** | |
| I | Chair recline actuator (Perfect Chair PC-610) | 0 W idle | ~120 W | Intermittent — moves for seconds only |
| J | Table height-adjust actuator | 0 W idle | ~120 W | Intermittent |

**Notes:** the 6 speakers + 4 chair transducers are passive, driven by the GAB8 (item F) — not
separate loads. The vertex-strip 12 VDC power injection redistributes existing current, adding
no new load. The full-white LED figure (15 mA/px) is already the worst case — there's no higher
draw scenario for the LEDs.

### 3.2 The 1.25× calculation

```
Current continuous draw:      792 W
1.25× design target:          792 × 1.25 = 990 W  ≈  1.0 kW
Worst-case transient:         1,133 W (all rated max) + 240 W (both actuators) = 1,373 W ≈ 1.37 kW
```

**Converted to current @ 220 V single-phase** (power factor ≈ 0.9 assumed):

| Condition | Power | Current |
|---|---:|---:|
| Continuous operating | 792 W | ~4.0 A |
| **1.25× target (the deliverable)** | **990 W** | **~5.0 A** |
| Worst-case transient | 1,373 W | ~6.9 A |

**Daily energy:** 792 W × 10 h ≈ **~7.9 kWh/day** (~238 kWh/month).

### 3.3 Circuit recommendation

One **dedicated 16 A, 220 V single-phase** circuit (TIS 166-2549 socket), running at only ~28%
load at the 1.25× target — comfortably absorbs the 1.37 kW transient plus actuator/SMPS inrush.
20 A also works if the store prefers more margin. Add: surge protection, an accessible **kill
switch**, and a fused sub-distribution at the operator station feeding the control box (which
keeps its own 10 A MCB + inrush limiter), the AV/host station, the GAB8's 24 V PSU, the
subwoofer, and both actuators.

### 3.4 What we couldn't get better numbers for

Neither the **GAB8 amp** nor the **Edifier T5** publish a "typical AC consumption" figure —
manufacturers only spec RMS output and recommended PSU rating (normal for class-D audio gear;
actual draw is program-dependent). Useful corroboration we did find: **the GAB8's own manual
recommends the Mean Well LRS-350-24/N2** — exactly the PSU already chosen, confirming it's
correctly matched. The ~120 W (GAB8) and ~70 W (T5) figures are engineering estimates, cited to
the manufacturer sources, not guesses pulled from nowhere.

---

## 4. Structural Weight — full derivation and revision history

**Why this moved three times** (so nobody's confused seeing different numbers in old messages):

| Stage | Total | What changed |
|---|---:|---|
| 1 | ~290 kg | Original figure as stated |
| 2 | ~305 kg | Switched occupant from an assumed average-adult (~75 kg) to the **rated maximum (100 kg)** — the correct basis for structural design, not a typical case |
| 3 | **~345 kg** | Itemized the previously-unaccounted LED tubes/edge covers/vertex units/speakers (~30 kg) and corrected the chair weight from ~30 kg to the confirmed **40 kg** |

**Current design total: use ~345 kg.**

### 4.1 Itemized breakdown

| Item | Weight |
|---|---:|
| 11× pentagon panel @ ~6 kg | ~66 kg |
| Structure platform (1× door step 18 kg + 4× side 6.2 kg) | ~42.8 kg |
| Chair platform (pentagon, 1.91 × 1.82 m) | ~50 kg |
| Plastic pallet | ~5 kg |
| Chair — Perfect Chair PC-610 | **40 kg** |
| LED tubes (30 × 100 g) | 3 kg |
| Edge covers (30 × 200 g) | 6 kg |
| Vertex units (20 × 400 g) | 8 kg |
| Speakers w/ mounts (6 × 1,000 g) | 6 kg |
| *(above 4 rows + wiring/cable allowance, rounded)* | **~30 kg** |
| Occupant — **rated maximum**, not average | **100 kg** |
| Edifier T5 subwoofer (published spec) | ~8.6 kg |
| **Total** | **≈ 342 kg → use ~345 kg** (rounded for margin) |

**Floor loading:** 345 kg / 9 m² ≈ **38 kg/m²** — trivial against a typical retail floor rating
of 500–800 kg/m², but still needs sign-off from the actual store engineer.

**Chair capacity cross-check:** the Perfect Chair PC-610 itself is rated to carry occupants up to
**~181 kg (400 lb)** — comfortably above our 100 kg design cap, so the chair isn't a limiting
factor.

**Excluded from this total:** the operator table (~15 kg), controller unit, Mac mini, and monitor
— these sit **outside** the 3×3 m structure footprint, in a separate and much lighter load zone.

---

## 5. Logistics & Move-In

This is a newer addition — the original draft of the requirements doc had almost nothing on
move-in logistics. Now covered:

### 5.1 Component schedule (for trolley/elevator/dock planning)

| Component | Qty | Size | Weight |
|---|--:|---|--:|
| Pentagon panel | 11 | 1.69 × 1.61 × 0.03 m | ~6 kg ea |
| **Chair platform** | 1 | **1.91 × 1.82 m**, 0.23 m tall | ~50 kg |
| Structure platform — door step | 1 | 0.35 × 0.7 × 0.15 m | 18 kg |
| Structure platform — side | 4 | 0.10 × 0.7 × 0.15 m | 6.2 kg ea |
| Chair (PC-610) | 1 | 1.09 × 0.79 × 1.19 m (extends to 1.60 m) | 40 kg |
| Table | 1 | 0.6 × 1.2 × 0.8 m | ~15 kg |
| Pallet | 1 | 1.1 × 1.1 × 0.16 m | ~5 kg |

**Key finding: weight is not the constraint, size is.** The heaviest single carry (~50 kg, the
chair platform) is trivial for a hand trolley or a two-person lift. The real risk is the **chair
platform's 1.91 m × 1.82 m footprint** (diagonal ≈ 2.64 m) — this is the single largest
component and the most likely reason an elevator or standard doorway won't take it flat. Confirm
this against the actual elevator cab/door dimensions before committing to elevator delivery; a
freight elevator, a wide corridor route, or sectional shipping may be needed.

### 5.2 Logistics questions still open with the store

None of these were in the original draft — now added to the requirements doc §1:

- Move-in/setup time allowance — **is overnight setup possible**?
- Drop-off/loading gate location — **ground level or an upper-floor gate**? Distance to the
  display area?
- Floor protection — does the plaza supply mats/runners for the move-in path, or do we bring
  our own?
- Trolley/hand-truck — available to borrow? Size and max load rating?
- **Elevator** — cab interior dimensions, door clear-opening width, weight capacity (check
  against the 1.91 × 1.82 m chair platform specifically).

---

## 6. Open Items — What We Still Need From the Store or Ourselves

**From the store (can't be resolved by us):**
- Numeric floor-load rating, flooring type, anchoring policy
- Ceiling/HVAC specifics (temp/humidity range, ventilation pattern)
- Fire code / egress requirements, insurance requirements
- Operating hours, security policy, on-site maintenance ownership
- Commercial terms (rental fee, duration, signage limits, exclusivity)
- All the §5.2 logistics questions above

**From us / needs physical measurement, not more research:**
- Door aperture vs. chair dimensions (repo itself flags this as unverified)
- Cable run length from the outlet to the operator station
- Actual measured current draw for the GAB8/subwoofer/router at commissioning (Step 9), to
  replace the engineering estimates with real numbers
- Confirm the elevator/doorway clearance against the chair platform's 1.91 × 1.82 m footprint

---

## 7. Sources

- [`NaoDec_Power_and_Controller_Box_Report.md`](NaoDec_Power_and_Controller_Box_Report.md) —
  audited control-box power budget (329 W DC).
- [`NaoDec_Build_Pending_Decisions.md`](NaoDec_Build_Pending_Decisions.md) §2 — audio chain
  (Mac mini → GAB8 @ 24 VDC → speakers/transducers; Mac mini → subwoofer).
- [`NaoDec_Build_Step6_Move_In.md`](NaoDec_Build_Step6_Move_In.md) — subwoofer own-mains, chair +
  transducers, media controller adapter.
- [`NaoDec_Build_Step8_Controller_Unit_Hookup.md`](NaoDec_Build_Step8_Controller_Unit_Hookup.md) —
  router location; flags "no single mains/CB plan exists" as its own open item.
- Mean Well LRS-350-24/N2 datasheet + Wondom/Sure Electronics GAB8 manual — confirms the PSU is
  manufacturer-matched to the amp.
- Edifier T5 product page — 70 W RMS spec.
- Human Touch Perfect Chair PC-610 — ~181 kg (400 lb) rated occupant capacity.
- All physical dimensions/weights in §4–§5 are vendor/user-provided measurements (2026-07-22).

---

**Version**: 1.0 | **Companion to Requirements v1.7** | **Last Updated**: 2026-07-22
