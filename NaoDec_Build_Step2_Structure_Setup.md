# NaoDec Build — Step 2: NaoDec Structure Set-Up

**Revision:** 1.0
**Date:** 2026-07-13
**Status:** Drafted from the author's outline — 2.1 (Pentagon Panel) is outlined down to the "Side and Ceiling" build-method split; 2.2 is not yet defined. Frame/fabric materials and fasteners are not yet specified (see Open Items).

[← Back to Build Work Instructions](NaoDec_Build_Work_Instructions.md) · Previous: [Step 1 — Base Platform Setup](NaoDec_Build_Step1_Base_Platform_Setup.md)

## Purpose

Step 2 builds and erects the NaoDec frame itself on top of the Step 1 platform: the 11 built pentagon panels that make up a regular dodecahedron.

## Quick Reference (established facts — see Cross-References)

| Fact | Value |
|---|---|
| Shape | Regular dodecahedron |
| Vertices / edges / faces | 20 / 30 / 12 (Euler check 20−30+12=2) |
| Faces built | 11 of 12 — `f12` (bottom) intentionally left unbuilt as the entry opening |
| Panel construction | Wooden frame + stretched fabric |
| Door face | Face 5 (`f11`) |
| Top / ceiling face | Face 10 (`f1`) |
| Joint marking | Shared edges between built faces share a letter, A–Z (no `W`) — 25 lettered joints; match identical letters to assemble/disassemble, no face lookup needed |
| Edges resting on the platform | 5 unlettered edges, on faces 1, 5, 6, 7, 8 |

## 2.1 Pentagon Panel

**Purpose:** build the 11 wooden-frame + stretched-fabric pentagon panels that form the dodecahedron's faces.

### 2.1.1 How to Build the Panel?

**Inputs needed (not yet specified):**
- Frame material and section size
- Corner joinery method (how the 5 frame members meet at each pentagon corner)
- Fabric type and how it's stretched/attached to the frame
- Fastener spec
- Finished pentagon edge length and per-panel weight

Whatever the build method, every panel still needs its **assembly letters** transferred onto the frame at each edge, per `NaoDec_Face_Edge_Marking_Rev1.0.html` (or the interactive variant), so panels can be matched up correctly on site.

#### 2.1.1.1 Side and Ceiling

Your outline splits the panel build method into **Side** and **Ceiling** variants. Two things worth deciding before this goes further (see Open Items #2–3):

- **Side** presumably covers the 9 faces that are neither the top, nor the door, nor the unbuilt bottom.
- **Ceiling** is face 10 (`f1`) — the top, opposite the unbuilt bottom.
- Not yet covered by this split: the **door** (face 5 / `f11`), which per the README needs to open or be removable — arguably a third build variant, not a Side panel. Also not addressed: how the frame confirms the bottom (`f12`) stays unbuilt/open at the platform interface.

*(TBD — the actual build steps, materials, and what specifically differs between Side and Ceiling panels are pending your input.)*

## 2.2 *(Not yet defined)*

Your outline stops at "2." with no title. Candidates that would logically follow 2.1 (not prescribing — just flagging for your consideration): the panel-to-panel erection sequence (which face goes up first, rigging/lifting method for a panel this size, how many people/tools it takes), and how the assembled frame's open bottom edges physically attach to the Step 1 chair/rise-up platform.

## Cross-References

- [`NaoDec_3D_Structure_Framework_Rev1.0.html`](NaoDec_3D_Structure_Framework_Rev1.0.html) — pure vertex/edge/face geometry, no LED wiring
- [`NaoDec_Face_Edge_Marking_Rev1.0.html`](NaoDec_Face_Edge_Marking_Rev1.0.html) / [interactive variant](NaoDec_Face_Edge_Marking_Interactive_Rev1.0.html) — per-face diagrams and the edge cross-reference table
- [`Paint_Comparison_Maxzo_RustTech_vs_JBP_SmartGlaze.md`](Paint_Comparison_Maxzo_RustTech_vs_JBP_SmartGlaze.md) — wood/metal coating comparison; relevant if panel frames get painted (not yet placed in this step — see Open Items)

## Safety

The erected frame surrounds and stands over the Step 1 chair platform and its occupant. No load rating or fastening spec exists yet for the frame itself, or for its attachment to the Step 1 platform (see Step 1 Open Items #5). Don't consider the structure occupant-safe until both are specified and confirmed.

## Release Gate

| Gate | Required Result |
|---|---|
| All 11 panels built | Frame + fabric complete, assembly letters marked per the marking guide |
| Panels erected | All lettered joints matched and fastened |
| Frame-to-platform attachment | Fixed to Step 1's rise-up platform, per a specified method |
| Door | Opens/closes or removes as intended |
| Occupant safety | Frame load path confirmed (see Safety) |

## Open Items

1. **2.2 has no title or content** — left as "Not yet defined."
2. **Door face isn't addressed in the Side/Ceiling split** — face 5 (`f11`) needs its own build variant if it's meant to open or be removable.
3. **Bottom face (`f12`) interface isn't described** — it's intentionally unbuilt (5 unlettered edges resting on the platform, per the structure framework doc), but how those edges physically land on/attach to the Step 1 platform isn't specified in either step.
4. **Panel construction specifics** — frame material/section, joinery, fabric type/attachment, fasteners, finished dimensions and weight: none specified yet.
5. **Side vs. Ceiling build differences** — what actually differs between the two (e.g. rigging points on the ceiling panel, orientation, reinforcement) isn't described yet.
6. **Erection sequence and rigging** — order of raising panels, lifting method, crew/tooling: not covered.
7. **Painting/finishing** — `Paint_Comparison_Maxzo_RustTech_vs_JBP_SmartGlaze.md` already exists in this repo comparing wood/metal coatings, but no step references it yet; worth deciding whether/where panel frames get painted.

---

[← Back to Build Work Instructions](NaoDec_Build_Work_Instructions.md) · Previous: [Step 1 — Base Platform Setup](NaoDec_Build_Step1_Base_Platform_Setup.md)
