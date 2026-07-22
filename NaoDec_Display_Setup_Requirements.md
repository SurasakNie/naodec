# NaoDec — Department Store Display Setup: Technical Requirements

**Project**: NaoDec — **3 m × 3 m × 2.5 m (W × L × H)** interactive product-display structure
**Scope**: Single display area in department store
**Footprint**: **4 m × 5.5 m (22 m²)** total allocated floor area · structure occupies a 3 m × 3 m
zone within it · operator/controller station sits in the remaining area, outside the structure ·
**minimum 2.75 m** ceiling clearance
**Role**: Vendor/Supplier technical team setup
**Power basis**: Requirement = **1.25× the current setup**, from a **220 V single-phase** main input, **10 hrs/day** operation

> This document adapts the generic *Display Setup Requirements* template to the actual NaoDec
> build. Electrical figures are worked from the audited
> [`NaoDec_Power_and_Controller_Box_Report.md`](NaoDec_Power_and_Controller_Box_Report.md)
> plus the AV/host and motion equipment confirmed in
> [`NaoDec_Build_Pending_Decisions.md`](NaoDec_Build_Pending_Decisions.md) and
> [`NaoDec_Build_Step6_Move_In.md`](NaoDec_Build_Step6_Move_In.md). See §9 for sources and the
> assumptions still to be confirmed against equipment nameplates.

---

## 1. STORE REQUIREMENTS TO CONFIRM

### Physical & Space
- [x] Floor load capacity — total design load **~305 kg** (incl. occupant rated **max 100 kg**) over the structure's **9 m² footprint ≈ 34 kg/m²** (§4); comfortably within typical retail ratings — **confirm the store's actual rating on site**
- [x] Ceiling height clearance — **minimum 2.75 m** available + service access; the structure's **2.5 m** height fits with **~0.25 m margin** — keep this margin clear of the platform/riser
- [ ] Access routes — confirm doorways/corridors/elevator fit every load-in component (see the
  **Move-In Component Schedule** below); the **chair platform (1.91 m × 1.82 m)** is the single
  largest item and the likely bottleneck; **door aperture vs. chair — measure before move-in**,
  Step 6 Open Item #1
- [ ] Flooring type — tile, wood, or concrete (affects platform footing method)
- [ ] Structural anchoring allowed? — bolts, adhesive, or weights only? (free-standing platform assumed)
- [ ] Column/obstruction clearance within the **4 m × 5.5 m (22 m²)** allocated area

### Electrical
- [x] Available power outlet near booth — **1 needed** at the controller/operator station (outside the cube, ~2–3 m from vertex v1)
- [x] Voltage/phase configuration — **220 V single-phase** ✅ (confirmed input)
- [x] Maximum circuit capacity — request **one dedicated 16 A** circuit (see §3; 20 A also acceptable)
- [ ] Distance from power source to booth (cable run length) — **confirm on site**
- [x] Socket/plug standard — **Thai TIS 166-2549** (16 A)
- [x] Backup power — **not required** (10 hrs/day, not 24/7); optional store add-on only
- [x] Dedicated circuit or shared load? — **dedicated required** (mixed AV + LED + motion loads)

### HVAC & Environment
- [ ] Store temperature operating range (typically 20–25 °C)
- [ ] Humidity control — relevant to the scent atomizer (condensation) and enclosed occupant (Step 6 Open Item #5)
- [x] Ventilation — the display has **2 × 38 W cooling fans**; confirm they are not obstructed
- [ ] Air circulation pattern near booth location

### Safety & Compliance
- [ ] Fire code — emergency exits access, extinguisher placement (occupant sits inside an enclosed 3 m × 3 m × 2.5 m volume — egress path must stay clear, Step 6 Safety)
- [x] Structural stability certification — **recommended as required** (structure height 2.5 m, at the template's >2.5 m threshold, occupied (max 100 kg) + ~305 kg design load; see §4)
- [ ] Product liability insurance requirements
- [ ] Safety railings/barriers — n/a (no elevated platform/fall hazard; occupant is seated at floor level)
- [x] Emergency shutdown — **accessible kill switch on the 220 V feed required by code** (see §3)
- [ ] First aid/emergency contact protocol

### Access & Operations
- [ ] Setup date/time window (assembly target < 1 day; see build steps 1–9)
- [ ] **Move-in/setup time allowance** — how much time is available to bring in every component and
  fully set up? **Is overnight setup an option** (store closed hours)?
- [ ] **Drop-off / loading gate** — where is it? **Ground level, or an upper-floor loading gate?**
  If upper floor, confirm which floor and how goods reach it.
- [ ] **Distance from the drop-off gate to the display area** — affects trolley trips, cable
  slack, and move-in duration.
- [ ] **Floor protection** — does the plaza provide protection mats/runners for the move-in path,
  or must the vendor supply their own? (Distinct from the Step 6 in-structure base-edge LED
  protection, which the vendor already supplies.)
- [ ] **Trolley/hand-truck** — is one available to borrow from the store? If so, **what size** and
  **maximum load rating**? (Needed to plan the door-step/side panels — see schedule below.)
- [ ] **Elevator (if used)** — **cab interior dimensions**, **door clear-opening width**, and
  **weight capacity**. Check specifically against the **chair platform (1.91 m × 1.82 m)** — the
  largest single component (see Move-In Component Schedule below) — before committing to
  elevator-based delivery; a freight elevator or a wide corridor bypass may be required.
- [ ] Store operating hours vs. technical-team access hours
- [ ] Security during off-hours (the cube is lockable via the door panel f11)
- [ ] On-site maintenance during operating hours — store staff or vendor team?
- [ ] Teardown timeline and process
- [ ] Storage of packaging/excess materials during display period

### Move-In Component Schedule

Dimensions/weights as measured by the vendor (2026-07-22).

| Component | Qty | Dimensions (W × H × D) | Weight (each) | Notes |
|---|---|---|---|---|
| Pentagon panel | 11 | 1.69 m × 1.61 m × 0.03 m | ~6 kg | ~66 kg total; flat, large 2D footprint but light |
| Chair platform (pentagon) | 1 | 1.91 m × 1.82 m; platform height 0.23 m | ~50 kg | **largest footprint — likely bottleneck**; light enough for a 2-person carry |
| Structure platform — door step | 1 | 0.35 m × 0.7 m × 0.15 m | 18 kg | |
| Structure platform — side | 4 | 0.10 m × 0.7 m × 0.15 m | 6.2 kg (24.8 kg total) | |
| Chair — **Perfect Chair PC-610** | 1 | 1.09 m L × 0.79 m W × 1.19 m H upright (extends to 1.60 m reclined) | ~30 kg | inside the 3×3 m structure zone |
| Table (height-adjustable) | 1 | 0.6 m × 1.2 m × 0.8 m | ~15 kg | **outside** the 3×3 m structure zone (operator station) |
| Pallet (plastic) | 1 | 1.1 m × 1.1 m × 0.16 m | ~5 kg | |

**Action:** given these weights, no single item is a load-capacity concern (heaviest single carry
≈ 50 kg — well within a standard hand trolley or a 2-person lift). The constraint is **size, not
weight**: confirm the elevator/doorway clear opening against the **chair platform's 1.91 m ×
1.82 m** footprint (diagonal ≈ 2.64 m) — if it doesn't fit flat, check whether it can be tilted
through with adequate clearance, or whether it disassembles/ships in sections.

### Commercial Terms
- [ ] Booth rental fee and payment schedule
- [ ] Display duration (weeks/months/seasonal)
- [ ] Signage restrictions (size, branding, placement limits)
- [ ] Exclusive product category or non-compete clause
- [ ] Liability and damage responsibility

---

## 2. DATA TO PREPARE FOR STORE

| Deliverable | Content | Format |
|---|---|---|
| **Floor Plan** | **4 m × 5.5 m (22 m²)** allocated area — the **3 m × 3 m × 2.5 m** structure (+ chair + subwoofer + egress) occupies a 3 × 3 m zone; the **operator, table, controller unit, Mac mini, and monitor sit outside that zone**, in the remaining allocated area; min 2.75 m ceiling; cable route to the single 220 V outlet | CAD/PDF drawing |
| **Electrical Load Sheet** | Continuous **~1.0 kW** (1.25× of ~792 W current draw), transient peak **~1.37 kW**, **~7.9 kWh/day** at 10 h/day, 220 V single-phase, dedicated 16 A — full-white worst-case basis | Signed technical sheet (this §3) |
| **Structural Analysis** | Weight distribution (**~305 kg design load over the 9 m² structure footprint ≈ 34 kg/m²**, incl. occupant rated max 100 kg), platform footing, stability certification (structure height **2.5 m**, at the template's >2.5 m threshold), CoG / tipping analysis | Eng. report or calc |
| **Material Documentation** | SDS for scent fragrance/atomizer fluid; no other hazardous materials | PDF datasheet |
| **Setup Manual** | 9-step assembly ([`NaoDec_Build_Work_Instructions.md`](NaoDec_Build_Work_Instructions.md)) | Technical manual (PDF) |
| **Move-In Component Schedule** | Dimensions/weights of every load-in piece (§1) — for the store's trolley/elevator/dock sizing check | Sheet (this §1) |
| **Operation Manual** | Daily power-up/down, emergency shutdown, scent refill, staff responsibilities | User-friendly guide |
| **Insurance Certificate** | General + product liability, store named additional insured | PDF certificate |
| **Site Contact Info** | On-site lead + emergency contact + escalation | Written sheet (§7) |
| **Timeline & Schedule** | Setup / operating / teardown dates, blackout periods | Calendar/schedule |

---

## 3. ELECTRICAL SPECIFICATIONS

**Input:** 220 V single-phase (Thai grid). **Operation:** 10 hrs/day. **Requirement basis:**
the store provisioning target is **1.25× the current setup's operating draw**.

### 3.1 Connected-Load Inventory (AC mains draw per device)

The control box's figures are DC loads from the audited power report, converted to AC input at
~85 % PSU efficiency; all other devices are drawn directly from the wall.

| # | Item | Typical operating | Rated / peak | Basis |
|---|------|-------------------|--------------|-------|
| A | Control box — LED strips (1,740 × WS2815, full white @ 15 mA/px) + 5 V logic + scent controller | ~387 W | ~387 W | audited **329 W DC** ÷ 0.85 |
| B | Mac mini (media/show host, Max/MSP) | ~65 W | ~90 W | Apple-silicon typical |
| C | Operator monitor | ~50 W | ~50 W | 24–27″ desktop display |
| D | 2 × cooling fans @ 38 W | ~76 W | ~76 W | **nameplate (user)** |
| E | Media playback controller (standalone; 5 V/2 A USB adapter) | ~12 W | ~12 W | Step 6 doc |
| F | Wondom **GAB8** amplifier on **Mean Well LRS-350-24** (24 V / 14.6 A / 350 W); drives 6 speakers + 4 transducers | ~120 W | ~400 W | PSU ceiling; typ ≈ ⅓ |
| G | **Edifier T5** active subwoofer (70 W RMS, class-D) | ~70 W | ~100 W | model spec |
| H | Router — **ASUS RT-AX1800HP** (in controller unit; wired LAN to Mac mini + chair W5500) | ~12 W | ~18 W | typical draw / 12 V-1.5 A adapter rating |
| | **Continuous operating subtotal (A–H)** | **~792 W** | ~1,133 W | |
| I | Chair recline actuator — **Perfect Chair PC-610** | 0 W idle | ~120 W | intermittent¹ |
| J | Table height-adjust actuator | 0 W idle | ~120 W | intermittent¹ |

*Notes:* The **6 speakers and 4 chair transducers are passive** — they are driven by the GAB8
and sit inside item F's budget, not separate mains loads. The **vertex-strip 12 VDC injection**
adds **no** new load; it only redistributes the 0.9 A the vertex strip already draws (counted in
item A). ¹Actuators draw power only for the few seconds they move (~0 W at rest), so they count
toward the transient peak / breaker sizing but **not** the continuous total.

### 3.2 Power Requirement — 1.25× the current setup

| Quantity | Value | Notes |
|---|---|---|
| Current setup — continuous operating load | **~792 W** | all subsystems active, LEDs full white |
| **1.25× design requirement (deliverable)** | **~990 W ≈ 1.0 kW** | sustained provisioning target |
| Worst-case transient | **~1,373 W (~1.37 kW)** | all supplies at rated max + both actuators moving, seconds only |

**At 220 V single-phase** (power factor ≈ 0.9 assumed):

| Condition | Power | Current @ 220 V |
|---|---|---|
| Continuous operating | ~792 W | **~4.0 A** |
| **1.25× target** | ~990 W | **~5.0 A** |
| Worst-case transient | ~1,373 W | **~6.9 A** |

**Daily energy (10 h/day):** ~792 W × 10 h ≈ **~7.9 kWh/day** (~238 kWh/month); actuator energy
is negligible.

### 3.3 Connection Requirements

- **Recommended:** one **dedicated 16 A** single-phase 220 V circuit (capacity ≈ 3,520 W). At the
  1.25× target the circuit runs **~28 % loaded**, comfortably absorbing the ~1.37 kW transient plus
  actuator/SMPS inrush. The template's dedicated **20 A** is also acceptable and adds margin.
  - The **1.25× figure is the sustained headroom**; the **circuit rating** independently covers
    short transients.
- **Cable gauge:** size to the run length from the store outlet to the operator station — consult
  the store electrician (≥ 2.5 mm² for a 16 A run is typical).
- **Termination:** Thai-standard **TIS 166-2549** connector (16 A).
- **Surge protection:** recommended (retail voltage fluctuations).
- **Emergency cutoff:** accessible **kill switch** on the 220 V feed — required by code.
- **Distribution behind the single outlet:** the one dedicated circuit feeds (i) the **control box**
  — which retains its own **10 A 2-pole C-curve MCB + NTC 10 Ω inrush limiter** guarding only its
  ~387 W branch — plus (ii) the **AV/host station** (Mac mini, monitor, media controller, **router**),
  (iii) the **GAB8 24 V PSU (LRS-350-24)**, (iv) the **Edifier T5 subwoofer** (own mains), and (v) the
  **two actuators**. Use a fused/breakered power strip or sub-distribution at the operator station —
  the repo itself flags this as an open item (`NaoDec_Build_Step8_Controller_Unit_Hookup.md`: *"no
  single mains/CB plan exists"* for the unit + Mac mini + GAB8 + subwoofer + chair adapter).
- **Rail isolation (internal):** keep the 5 V, 12 V-Strip#1, 12 V-Edges, and 24 V-amp **positive**
  rails isolated per the source design; GND may share a single star point.

---

## 4. STRUCTURAL & SAFETY

### Load Verification
```
Total Design Load ≈ 302 kg (round to ~305 kg for margin) =
    Structure (dodecahedron panels/edges + vertex & edge LED units)
  + chair (PC-610) + occupant (rated max 100 kg) + subwoofer + scent unit
Confined to the structure's 3 m × 3 m = 9 m² footprint (within the 22 m² allocated area).

Floor loading ≈ 305 kg / 9 m² ≈ 34 kg/m²

The operator + table + controller unit + Mac mini + monitor sit OUTSIDE the 3 × 3 m
structure footprint, in the remaining allocated area — a separate, much lighter load zone.
```
**Action:** Confirm the store floor rating supports **~34 kg/m²** under the structure zone.
Retail floors are typically rated 500–800 kg/m² — comfortably sufficient; confirm the store's
actual rating and check the operator-station zone separately (lightweight: table + electronics).

**Weight reconciliation** (against the §1 Move-In Component Schedule), using the **rated maximum
occupant weight (100 kg)** as the structural design basis rather than an average-adult estimate:
known structure-zone hardware — 11 panels (~66 kg) + structure platform (~42.8 kg) + chair
platform (~50 kg) + pallet (~5 kg) + chair (~30 kg) ≈ **~194 kg**. Adding the **100 kg max
occupant rating** and the Edifier T5 subwoofer (~8.6 kg, per its published spec) ≈ **~302 kg**.
This is **~12 kg above** the originally-stated **~290 kg** figure — the difference is the switch
from an average-adult assumption to the maximum rated occupant; use **~305 kg** (rounded up for
margin) as the structural design total going forward. The remaining small gap versus itemized
hardware is plausibly framework hardware, hinges, wiring, LED strips, and the scent unit, none
individually itemized. The operator table (~15 kg) is **excluded** — it sits outside the
structure zone. **Chair capacity cross-check:** the Perfect Chair PC-610 itself is rated for
occupants up to **~181 kg (400 lb)** — comfortably clears the 100 kg design cap.

### Stability Certification
- Structure height is **2.5 m** — exactly at the template's **>2.5 m** mandatory-certification
  threshold (not strictly over it). Given the structure is **occupied** (a seated person, rated
  max **100 kg**) and carries a **~305 kg** design load, proceed with stability certification and
  CoG/tipping analysis as best practice regardless of the literal threshold.
- Structure height fits under the **2.75 m** ceiling clearance with **~0.25 m** margin.
- Free-standing platform; document center of gravity and tipping-hazard analysis.
- 25 lettered panel joints are hinged (2 hinges each, 50 total) for rigidity; the 5 base edges rest
  on the platform.

### Safety Railings
- Not applicable — no elevated platform or hanging fall hazard; the occupant is seated at floor
  level inside the cube. Keep the door→chair egress path clear (Step 6 Safety).

---

## 5. PRE-INSTALLATION CHECKLIST

### 3–4 Weeks Before
- [ ] Confirm booth location with store manager
- [ ] Request store specs (floor load, **dedicated 16 A / 220 V outlet**, ceiling ≥ 2.75 m, HVAC)
- [x] Electrical load sheet prepared (this §3)
- [ ] Begin/confirm structural stability analysis (structure height 2.5 m, at the >2.5 m threshold — see §4)

### 2 Weeks Before
- [ ] Finalize drawings and calculations
- [ ] Order/prepare insurance certificate
- [ ] In-house electrical test — simulate the full 10 h daily run; verify draw ≈ §3 figures
- [ ] Prefab / test-fit the cube panels in the facility
- [ ] Prepare scent SDS + safety documentation

### 1 Week Before
- [ ] Confirm setup date/time with store (signed schedule)
- [ ] Brief team on store access + emergency contacts
- [ ] Pack cube modules with labeling and the 9-step assembly guide
- [ ] Prepare **TIS 166-2549** cable adapters + operator-station power distribution
- [ ] Brief store staff on daily operation

### Day of Setup
- [ ] Arrive early — verify the **dedicated 16 A / 220 V** outlet, floor, access
- [ ] Unpack and inspect components
- [ ] Test the electrical connection before permanent install (measure draw at the outlet)
- [ ] Assemble per steps 1–9
- [ ] Power-on / load test (run all subsystems + one actuator cycle; confirm ≤ ~7 A peak)
- [ ] Sign off with store manager (safe, operational, contacts recorded)

### During Operation
- [ ] Daily walk-through — fasteners, cable wear, fan operation, temperature
- [ ] Weekly log (temperature, humidity, power draw)
- [ ] Respond to store complaints within 4 hours
- [ ] Prepare teardown schedule (confirm 2 weeks prior)

---

## 6. EMERGENCY PROCEDURES

| Scenario | Action |
|---|---|
| **Power outage** | Immediate safe shutdown; no backup fitted. Notify store manager; power-up sequence on restore. |
| **Overheat / fan failure** | Check the 2 × 38 W fan intakes for blockage. If unresolved in 30 min, shut the display down. |
| **Structural creaking/movement** | STOP. Evacuate the cube. Call structural support. Do not resume until certified safe. |
| **Water leak / atomizer over-condensation** | Immediate power cutoff (kill switch). Do not touch. Call emergency contact. |
| **Fire alarm** | Evacuate per store protocol. Kill the 220 V feed if safe to do so. |
| **Occupant stuck / chair fault** | The PC-610 recline and table actuators are low-force; assist the occupant out, then kill power to the chair branch. |

**On-site Lead Responsibility**: Keep the emergency contact list posted and brief all store staff.

---

## 7. CONTACTS & DOCUMENTATION LOG

| Role | Name | Phone | Email | Notes |
|---|---|---|---|---|
| Your Technical Lead | ___________ | ___________ | ___________ | Setup & daily ops |
| 24/7 Emergency | ___________ | ___________ | ___________ | For critical issues |
| Store Manager | ___________ | ___________ | ___________ | Day-to-day liaison |
| Electrician (backup) | ___________ | ___________ | ___________ | If power issues arise |

**Documents Stored At**:
- [ ] Store copy: Manager office
- [ ] Your team copy: On-site lead
- [ ] Backup copy: Off-site secure storage

---

## 8. SIGN-OFF

**Prepared By**: _________________________ (Lead Mechanical Engineer)
**Date**: _____________
**Reviewed By**: _________________________ (Store Manager)
**Date**: _____________

**Booth Location**: _________________________ (Aisle/Section)
**Setup Date/Time**: _________________________
**Operational Start**: _________________________
**Teardown Date**: _________________________

---

## 9. SOURCES & ASSUMPTIONS

**Requirement basis:** power requirement = **1.25× the current setup's continuous operating draw**;
main input **220 V single-phase**; operation **10 hrs/day** (not 24/7 → no backup power required).
Space: **4 m × 5.5 m (22 m²)** total allocated floor area, **minimum 2.75 m** ceiling clearance;
structure is **3 m × 3 m × 2.5 m (W×L×H)**, occupying a 3×3 m zone within the allocated area; total
structure-zone design weight **~305 kg** (incl. occupant rated **max 100 kg** — see §4 for the
switch from an average-adult estimate to this rated max), with the operator/table/controller-unit/Mac mini/monitor sitting
outside that zone (all user-confirmed).
Power factor assumed **≈ 0.9**; control-box PSU efficiency assumed **≈ 85 %** for the DC→AC
conversion. LED figure is the **full-white worst case** (15 mA/px) — there is no higher case.

**Sources:**
- [`NaoDec_Power_and_Controller_Box_Report.md`](NaoDec_Power_and_Controller_Box_Report.md) — audited control-box budget (329 W DC: LED ~313 W, logic ~4 W, scent ~12 W; 10 A MCB; PSU specs).
- [`NaoDec_Build_Pending_Decisions.md`](NaoDec_Build_Pending_Decisions.md) §2 — audio chain (Mac mini → Wondom GAB8 @ 24 VDC → 6 speakers + 4 transducers; Mac mini → subwoofer).
- [`NaoDec_Build_Step6_Move_In.md`](NaoDec_Build_Step6_Move_In.md) — subwoofer own-mains, chair + transducers, media controller USB adapter.
- [`NaoDec_Build_Step8_Controller_Unit_Hookup.md`](NaoDec_Build_Step8_Controller_Unit_Hookup.md) — confirms the router lives in the controller unit and flags *"no single mains/CB plan exists"* for the unit + Mac mini + GAB8 + subwoofer + chair adapter (Open Item).
- [`NaoDec_Media_Playback_Controller_Rev3.0_Ethernet_Rationale.md`](NaoDec_Media_Playback_Controller_Rev3.0_Ethernet_Rationale.md) — ASUS RT-AX1800HP router (Mac mini + chair W5500 both wired to it; no separate switch needed).
- Mean Well **LRS-350-24 / LRS-350N2** — 24 V / 14.6 A / 350 W. **This is the GAB8 manufacturer's
  own recommended PSU model** ([Wondom/Sure Electronics GAB8 user manual](https://files.sure-electronics.com/download/GAB8_10x50W_USB_Codec_Input_User_Manual.pdf);
  [Audiophonics product page](https://www.audiophonics.fr/en/amplifier-boards/wondom-gab8-p-18755.html)) —
  confirms the chosen PSU is exactly matched to the board, not oversized/undersized.
- [**Edifier T5**](https://www.edifier.com/global/p/subwoofers/t5) — 70 W RMS active subwoofer,
  class-D amp, universal switching PSU, auto-standby when idle.
- Human Touch **Perfect Chair PC-610** Omni-Motion power recliner.

**Datasheet findings (items 1–2 below):** neither the GAB8 amplifier board nor the Edifier T5
publish a "typical AC input consumption" figure — both manufacturers spec only **RMS output
power** and **recommended PSU rating**, which is standard practice for class-D audio gear (actual
draw is program-dependent). No better figure than an engineering estimate exists for either.

**Remaining assumptions / estimates** (refine §3.1 if better data becomes available):
1. **GAB8 typical operating draw (~120 W)** — engineering estimate ≈ ⅓ of the manufacturer-matched
   LRS-350-24 rating (350 W); no published typical-draw figure exists. PSU ceiling (350 W / ~400 W
   AC) is firm and manufacturer-specified.
2. **Edifier T5 typical draw (~70 W) / peak (~100 W)** — engineering estimate from the 70 W RMS
   output rating; no published AC input consumption figure exists. Auto-standby reduces draw when
   idle (not modeled — conservative for the continuous-operation total).
3. **Chair PC-610 actuator (~120 W, intermittent)** — engineering estimate for a standard dual-motor
   ~29 V linear-actuator recliner mechanism; no published wattage. Finalized per user direction.
4. **Table height actuator (~120 W, intermittent)** — engineering estimate (no model specified);
   finalized per user direction.
5. **Router draw (~12 W typical / ~18 W adapter max)** — standard 12 V/1.5 A brick rating for this
   router class; confirm from the RT-AX1800HP's actual adapter label if precision is needed.
6. **Component weights** (panels ~6 kg, chair platform ~50 kg, chair ~30 kg, table ~15 kg, pallet
   ~5 kg) — all user-provided (2026-07-22); see the §1 Move-In Component Schedule and the §4
   weight reconciliation. The remaining small gap between itemized hardware and the ~305 kg design
   total (framework/hinges/wiring/LED strips/scent unit) is not individually itemized but is small
   enough not to be a concern.
7. **Occupant weight** — design basis is the **rated maximum of 100 kg per occupant**, not an
   average-adult estimate; this raises the structural design total from the originally-stated
   ~290 kg to **~305 kg** (§4). The Perfect Chair PC-610 itself is rated to ~181 kg (400 lb),
   comfortably above this cap.

**Version**: 1.6 | **Last Updated**: 2026-07-22 | **Status**: Ready for Distribution
