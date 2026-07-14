# NaoDec Build — Decision Record (Steps 3–9)

**Date asked:** 2026-07-14 · **Date answered:** 2026-07-14
**Status:** ✅ **All answered.** This file is now the decision record for the build work-instruction docs (`NaoDec_Build_Step3…Step9`). The answers below are folded into the step docs; residual unknowns each decision left open are flagged in the step docs' Open Items.

> Background: items 1–3 were originally submitted as revision notes via the plan-approval dialog on 2026-07-14, but a session connection failure dropped the note text before it reached the assistant. This file exists so no decision can be lost that way again.

---

## 1. Node 0 vs "node 1" (cable entry point)

The LED mapping doc (`NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.3.html`) defines the common cable entry as **Node 0 "POWER IN"**, a synthetic bus point below the base center; feeds fan out from it to base vertices v1–v5. The build outline says all cables "start from node 1" (v1 is the chair-facing vertex and the start of the vertex chain, circuits C1/C6, and the coil positive).

**Answer:** **Node 0 is the controller unit itself.** The original plan put the unit under the platform (hence the mapping doc drawing Node 0 below the base center). The current build places the controller unit **outside the structure framework, ~2–3 m from node 1 (v1)**. The operator station and the Mac mini (controlling media: light, sound, vibration) are in the same area.

---

## 2. Audio hardware

Nothing in the repo documented the audio chain: 6 speakers (edges A, H, C, F, Y, M), the subwoofer, the 4 chair transducers, or any amplifier / audio interface out of the Mac mini.

**Answer:** Mac mini → **3.5 mm jack cable → subwoofer** (direct). Mac mini → **USB Type-C → Wondom GAB8** amplifier board, powered from **24 VDC**. The GAB8 outputs drive the **6 speakers** and **2 transducer sets** (back set + seat set; 4 transducers total).

---

## 3. Series-coil routing

The series-coil / electromagnet subsystem (60 coils at the vertex units, pre-release Rev 0) was absent from the step outline, but its wiring shares the Node 0 → v1 path with the CH1 vertex LED chain.

**Answer:** **The coils route along the same path as the vertex units** → documented inside Step 3 (Vertex Units Installation), pre-release caveats retained.

---

## 4. Scent unit location

The outline placed "scent control" next to the subwoofer; the repo docs put the Waveshare board inside the controller box.

**Answer:** **Only the atomizer/mist unit sits by the subwoofer. The Waveshare board stays inside the controller unit.**

---

## 5. Controller unit contents

**Answer:**
1. LED Master + LED Slave (2× ESP32-S3)
2. The Waveshare (which is an ESP32-S3) → **3 ESP32-class boards total in the unit**
3. The media playback controller's ESP32 is **inside the media playback controller at the chair** — a design change from the original in-unit plan, made because of the signal-wire issue (matches the Placement Requirement in `NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md` §1). Its LAN cable runs from the **router (inside the controller unit)** to the chair and plugs into the W5500 module's RJ45.
4. The **Mac mini is NOT inside the controller unit** — it sits on a table, side-by-side with the unit.

---

## 6. + 7. Door hinge edge · Hinges at the other joints

**Answer (combined):** **Every pentagon-panel edge gets 2 hinges** — this is how the panels attach together rigidly. **Only the edges resting on the ground/platform have no hinges** (the 5 unlettered base edges). So all 25 lettered joints are hinged, 2 hinges each (50 hinges total).

> Residual open item (flagged in Step 2): with all four of its lettered edges hinged, the mechanism by which the door (f11) opens — swing side, lift-off pins, or fully removable — still needs deciding.

---

## 8. Commissioning step

**Answer:** **Add Step 9 — Commissioning & Test.**

---

## 9. Clarified installation order + edge covers *(added with the second revision message)*

**Answer:** After all 11 pentagon panels are up:
1. Install the **vertex units**, routing all wires/cables
2. Install the **internal edge units**, routing all wires/cables
3. Install the **speakers**, routing all wires/cables
4. **Move the scent control, subwoofer, and the chair in.** Position the chair, then route all cables
5. **Cover all the external edges with the edge covers — 25 pieces**

Resulting step numbering: **1** Platform · **2** Structure · **3** Vertex Units · **4** Internal Edge Units · **5** Speakers · **6** Move-In · **7** Edge Covers · **8** Controller Unit Hookup · **9** Commissioning & Test.

---

## 10. Pictures in the docs *(added via the plan dialog)*

**Answer:** **Mermaid diagrams + snapshots of the interactive 3D pages** (no photo placeholders). Snapshots live in [`images/build/`](images/build/) and are generated headless from `NaoDec_3D_Structure_Framework_Rev1.0.html` and `NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.3.html`.
