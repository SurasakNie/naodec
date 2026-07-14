# NaoDec Build — Step 1: Base Platform Setup

**Revision:** 1.1
**Date:** 2026-07-14
**Status:** Drafted from the author's outline — materials, dimensions, and load rating are not yet specified (see Open Items). Do not place an occupant on the finished platform until those are filled in and the Release Gate passes.

> Rev 1.1 — Cable-egress open items updated for decision 1 (controller unit sits *outside*
> the structure, ~2–3 m from node 1 — not under the platform as originally planned), plus
> floor cable protection on the walk-in path. See
> [`NaoDec_Build_Pending_Decisions.md`](NaoDec_Build_Pending_Decisions.md).

[← Back to Build Work Instructions](NaoDec_Build_Work_Instructions.md) · Next: [Step 2 — NaoDec Structure Set-Up](NaoDec_Build_Step2_Structure_Setup.md)

## Purpose

Step 1 builds the load path the whole installation stands and sits on, bottom to top:

```
ground → plastic pallet → rise-up platform → chair platform → chair → occupant
                              └── also carries the NaoDec frame (Step 2) ──┘
```

The pallet spreads load to the ground; the riser lifts the frame clear of the vertex hardware; the chair platform carries the chair and occupant and routes their weight back down through the riser to the pallet.

## Quick Reference

| Sub-step | Element | Carries |
|---|---|---|
| 1.1 | Plastic pallet | Everything above it — the foundation |
| 1.2 | Rise-up platform | The NaoDec frame (Step 2); sets clearance for the Vertex units |
| 1.3 | Chair platform | The chair + occupant; routes weight to the pallet |

## 1.1 The Plastic Pallet

**Purpose:** base of the chair platform — the foundation layer the rest of Step 1 sits on.

**Inputs needed (not yet specified — fill in before build):**
- Pallet size, quantity, and layout (single pallet vs. multiple joined together)
- Rated load capacity of the pallet(s)
- Ground/floor surface it sits on, and whether it needs leveling shims or anchoring
- Whether pallets are fixed to each other or to the ground

**Procedure**

1. *(TBD — confirm the pallet spec above first)* Select and inspect the pallet(s): no cracked or missing deck boards/ribs, rated for the expected load.
2. Position on level, solid ground in the final installation footprint.
3. Check level in both axes; shim as needed.
4. *(TBD)* If more than one pallet is used, join them per the layout above.

**Acceptance check:** pallet(s) level, stable underfoot, no rock/flex when weight is applied at the corners.

## 1.2 Structure Rise-Up Platform

**Purpose:** raises the NaoDec framework structure up off the pallet, adding clearance underneath for the Vertex units.

**Inputs needed (not yet specified):**
- Riser height (driven by how much clearance the Vertex units need underneath — see Open Items)
- Riser material and construction
- Attachment method to the pallet below and to the structure above
- Whether the riser is a full platform (deck) or a perimeter/frame support

**Procedure**

1. *(TBD)* Build/position the riser at the specified height on top of the pallet(s).
2. Fasten to the pallet per the attachment method above.
3. Verify clearance underneath matches what the Vertex units (Step 2 / LED channel 1 hardware — see `NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.3.html`) actually need.
4. Recheck level after the riser is on.

**Acceptance check:** riser is level, fixed to the pallet (no shift), and clearance underneath matches the Vertex unit requirement.

## 1.3 The Chair Platform

**Purpose:** base for the chair and occupant. Distributes their combined weight down to the pallet. The chair sits on this platform with its legs **position-locked** so it can't shift.

**Inputs needed (not yet specified):**
- Platform size/shape and material
- Rated load: chair weight + max occupant weight + safety factor *(see Safety, below — this is the one that matters most)*
- Chair make/model and leg footprint (spacing/pattern), so the lock hardware lines up
- Lock mechanism at the chair legs (e.g. cleats, brackets, track, pins — not yet chosen)

**Procedure**

1. *(TBD)* Build/position the chair platform on top of the riser (1.2), fastened per its attachment method.
2. Mark and install the chair-leg lock hardware at the chair's actual leg footprint.
3. Place the chair and engage the leg locks.
4. Test: apply expected occupant weight and confirm no shift, rock, or leg walk at the locks.

**Acceptance check:** chair platform fixed to the riser; chair legs locked and immovable under test load.

## Safety

**This platform is going to carry a seated person.** None of the load-path elements above (pallet, riser, chair platform) have a stated rated load or safety factor yet. Following the same standard the Series Coil subsystem holds itself to (no live current until the loop resistance is measured and gated) — **don't allow an occupant until:**

- A rated load (with safety factor) is specified for the full stack, and
- The assembled stack has been tested at that load without shift, rock, or structural concern.

## Release Gate

Don't proceed to erecting Step 2 on top of this platform until:

| Gate | Required Result |
|---|---|
| Pallet | Level, stable, rated load specified |
| Rise-up platform | Level, fixed to pallet, clearance confirmed against Vertex unit needs |
| Chair platform | Fixed to riser, rated load specified |
| Chair leg lock | Installed, tested under expected occupant weight, no shift |
| Occupant safety | Rated load + safety factor confirmed (see Safety) |

## Open Items

1. **Pallet spec** — size, quantity/layout, rated load: not given yet.
2. **Riser height and clearance figure** — how much clearance the Vertex units need underneath isn't stated; needed to size the riser.
3. **Chair platform load rating** — no number yet for chair + occupant + safety factor. Safety-relevant; see the Safety section above.
4. **Chair leg lock hardware** — mechanism not chosen (cleat/bracket/track/pin), and depends on the actual chair's leg footprint.
5. **Interface to Step 2** — how the dodecahedron's open bottom face (`f12`, per `NaoDec_3D_Structure_Framework_Rev1.0.html`) actually lands on / attaches to this platform isn't described yet in either step.
6. **Cable exit at node 1** — every wire run (Steps 3–6) leaves the structure near the v1 base corner toward the controller unit ~2–3 m away, at ground level. The pass-through (under a ground edge? a notch in the platform lip? a grommeted channel?) has to be provisioned in this step's build, and isn't specified.
7. **Floor cable protection** — the occupant walks in through the door (`f11`) and across the platform to the chair; the base-edge LED runs and the node-1 harness cross that path. Ramped covers / routing away from the walk path: not specified.

---

[← Back to Build Work Instructions](NaoDec_Build_Work_Instructions.md) · Next: [Step 2 — NaoDec Structure Set-Up](NaoDec_Build_Step2_Structure_Setup.md)
