# NaoDec Build — Pending Decisions (Steps 3–8)

**Date:** 2026-07-14
**Status:** Awaiting the author's answers. These 8 decisions shape the remaining build work-instruction docs (`NaoDec_Build_Step3…Step8`). Everything *not* listed here stays as a flagged Open Item in the step docs (panel materials, load ratings, chair model, etc.) and can be filled in later.

**How to answer:** either reply in chat, or edit this file — put your answer on the `**Answer:**` line of each item — and commit/push. Once all 8 are answered, this file becomes the decision record; the answers get folded into the step docs.

> Background: items 1–3 were originally submitted as revision notes via the plan-approval dialog on 2026-07-14, but a session connection failure dropped the note text before it reached the assistant. This file exists so no decision can be lost that way again.

---

## 1. Node 0 vs "node 1" (cable entry point)

The LED mapping doc (`NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.3.html`) defines the common cable entry as **Node 0 "POWER IN"**, a synthetic bus point below the base center; feeds fan out from it to base vertices v1–v5. The build outline says all cables "start from node 1" (v1 is the chair-facing vertex and the start of the vertex chain, circuits C1/C6, and the coil positive).

Decide: rename everything to **node 1** · keep the docs' **Node 0** name · other convention.

**Answer:** _(pending)_

---

## 2. Audio hardware

Nothing in the repo documents the audio chain: 6 speakers (edges A, H, C, F, Y, M), the subwoofer, the 4 chair transducers, or any amplifier / audio interface out of the Mac mini.

Decide: provide the gear list (speaker/sub/transducer models, amp or interface, and where the amp lives) · or mark the whole chain **TBD** in the docs.

**Answer:** _(pending)_

---

## 3. Series-coil routing

The series-coil / electromagnet subsystem (60 coils at the vertex units, pre-release Rev 0) is absent from the 8-step outline, but its wiring shares the Node 0 → v1 path with the CH1 vertex LED chain installed in Step 3.

Decide: coils install **together with the vertex chain in Step 3** · get their **own step** · are **out of scope** for this build revision.

**Answer:** _(pending)_

---

## 4. Scent unit location

Step 7 of the outline places "scent control" next to the subwoofer, inside the structure. The repo docs (`NaoDec_Scent_Controller_Schematic_Rev2.0.html`, `NaoDec_Controller_Box_Configs_Rev1.1.html`) put the Waveshare ESP32-S3-Relay-6CH board **inside the controller box**, with the 4 JY-M27AO atomizers as its remote loads.

Decide: the **whole controller** moves inside next to the subwoofer · only the **atomizer/mist unit** sits inside and the board stays in the box.

**Answer:** _(pending)_

---

## 5. Controller unit contents

The outline lists "3× ESP32s, 1× Waveshare, all PSU, Router" in the controller unit. The docs show **3 boards total** in the box — LED Master + LED Slave + the Waveshare (which is itself an ESP32-S3 board); the 4th project ESP32 (media playback) mounts at the chair.

Decide: (a) is it **3 boards total** (docs) or is there a 4th board not yet documented? (b) is the **Mac mini** inside the controller unit too? (Step 5 cables the subwoofer to it; the media docs place it with the router "in a metal ATX case" ~6 m from the chair.)

**Answer:** _(pending)_

---

## 6. Door hinge edge

The door is panel f11 (single panel, not part of a hinged pair). Its four lettered joints are: **B** (to f2), **A** (to f6), **L** (to f7), **K** (to f10).

Decide: which joint does the door hinge/swing on — **B**, **A**, **L**, or **K** — or is the door a fully **removable** panel rather than a swinging one?

**Answer:** _(pending)_

---

## 7. Hinges at the other joints

The 5 pre-built pairs hinge along joints **M** (f7-f8), **O** (f9-f10), **R** (f2-f6), **T** (f3-f4), **U** (f1-f5). That leaves 20 lettered joints joined on site.

Decide: do the remaining site joints also get **hinges**, or a different **fastener** (bolts, clamps, latches, …)? If different — what?

**Answer:** _(pending)_

---

## 8. Commissioning step

Power-up order, WLED/DDP/network configuration, Max/MSP bring-up, and end-to-end testing have no home in the 8-step outline.

Decide: add a **Step 9 — Commissioning & Test** doc · or keep 8 steps and leave commissioning flagged as a missing step.

**Answer:** _(pending)_
