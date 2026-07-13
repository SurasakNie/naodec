# NaoDec — Full Build Work Instructions

**Revision:** 1.0
**Date:** 2026-07-13
**Status:** In progress. Steps 1–2 are drafted from the author's own step list; later steps are not yet defined. Do not treat this as a complete build plan until every step below is filled in and the Open Items are resolved.

This is the top-level index for building the physical NaoDec installation — platform, structure, and (as later steps are added) the LED, coil, media, and scent subsystems already documented elsewhere in this repo. It sequences the physical build and links out to one document per step; it does not duplicate the wiring/schematic detail that already lives in the other `NaoDec_*` docs.

## How to Use This Document

- Each numbered **step** below is a separate Markdown file, linked from the table.
- Sub-steps (1.1, 1.2, 2.1.1, …) are sections *inside* that step's file, not separate files — so each step doc stays self-contained, matching how this repo's other build/report docs are structured (e.g. `NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md`).
- A step marked **Not yet defined** is a placeholder in the sequence, not a claim that the work doesn't exist.
- Work through steps in order. Each step file ends with a **Release Gate** — don't start the next step until the current one's gate passes.

## Build Sequence

| Step | Title | Status | Doc |
|---|---|---|---|
| 1 | Base Platform Setup | Drafted — materials/load rating pending (see Open Items) | [`NaoDec_Build_Step1_Base_Platform_Setup.md`](NaoDec_Build_Step1_Base_Platform_Setup.md) |
| 2 | NaoDec Structure Set-Up | Drafted — 2.1 outlined, 2.2 not yet defined | [`NaoDec_Build_Step2_Structure_Setup.md`](NaoDec_Build_Step2_Structure_Setup.md) |
| 3+ | *(not yet defined)* | Not started | — |

## Open Items (flagged for author review)

Gaps noticed while drafting Steps 1–2 — flagged per your request so you can decide what to do with each, not decisions made on your behalf.

1. **Step 2.2 is currently blank.** Your outline stops at `2.2.` with no title, so it's left as "Not yet defined" in `NaoDec_Build_Step2_Structure_Setup.md` rather than guessed at.
2. **The "Side and Ceiling" split (2.1.1.1) doesn't mention the Door face.** Per `README.md` / `NaoDec_Face_Edge_Marking_Rev1.0.html`, face 5 (`f11`) is a **door** — presumably needs to open/close or be removable, which reads like a third panel-build type, not a Side variant.
3. **The unbuilt bottom face (`f12`) isn't addressed.** The 3D structure framework treats the bottom as intentionally open (5 unlettered edges resting on the platform). Neither step yet says how those edges physically land on / attach to the Step 1 platform — that's the actual physical interface between the two steps you've written so far.
4. **No step yet covers the subsystems this repo already documents in detail:**
   - LED strip install & wiring per channel (`NaoDec_WS2815_LED_Controller_Rev1.6.html`, `NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.3.html`)
   - Controller box build (`NaoDec_Controller_Box_Configs_Rev1.1.html`, `NaoDec_Power_and_Controller_Box_Report.md`)
   - Series coil / electromagnet subsystem — **pre-release** (`NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`, `NaoDec_Vertex_Series_Coil_Rev1.0.html`, `XL4015_CC_CV_Mockup_Test_Procedure.md`)
   - Media playback controller build (`NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md`)
   - **Scent controller** (`NaoDec_Scent_Controller_Schematic_Rev2.0.html`) — not even mentioned in `README.md`'s repository tree today; it only surfaces on the published site because `index.html` globs all `*.html` files.
   - Panel finishing/paint (`Paint_Comparison_Maxzo_RustTech_vs_JBP_SmartGlaze.md` — wood + metal coating comparison, presumably for the pentagon panel frames and/or platform, but not yet placed in any step)
   - Final erection sequence (rigging/lifting order for the 11 panels, fastening at the lettered joints), commissioning/test, and teardown/storage — the marking guide implies this rig is assembled and torn down on site.
5. **No safety/load-rating figures exist yet for the platform stack** (pallet → riser → chair platform) that will carry an occupant. Flagged explicitly in Step 1's Safety section — this needs a real rated-load-plus-safety-factor number before anyone sits on it, the same way the Series Coil subsystem gates on a measured loop resistance before it's powered.

## References

- [`README.md`](README.md) — hardware/subsystem overview
- [`NaoDec_3D_Structure_Framework_Rev1.0.html`](NaoDec_3D_Structure_Framework_Rev1.0.html) — vertex/edge/face geometry
- [`NaoDec_Face_Edge_Marking_Rev1.0.html`](NaoDec_Face_Edge_Marking_Rev1.0.html) / [interactive variant](NaoDec_Face_Edge_Marking_Interactive_Rev1.0.html) — panel joint marking guide
