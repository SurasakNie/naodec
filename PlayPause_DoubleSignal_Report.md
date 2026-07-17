# Report — Play button sends two transport signals (Play + Pause) to Max

**Date:** 2026-07-17
**Unit:** NaoDec Media Playback Controller, hardware Rev 3.0 (ESP32‑S3‑DevKitC‑1)
**Firmware:** `media_playback_controller_R3.1.2.ino` (FW 3.2.1)
**Max patch:** `TransportReceiveTest1.maxpat`
**Reference:** `NaoDec_Media_Playback_Controller_PlayPause_CrossTrigger_Fix.md` — https://github.com/SurasakNie/naodec

---

## 1. Symptom

- Pressing the physical **Play** switch → the Max patch registers **two** signals: **Play *and* Pause**.
- Pressing the physical **Pause** switch → the Max patch registers **one** signal: Pause only.

## 2. Conclusion (summary)

This is a **hardware wiring fault on the controller, not a Max problem and not a firmware
bug.** The ESP32 is genuinely transmitting two OSC packets (`/transport/play/ 1` **and**
`/transport/pause/ 1`) on a single Play press, because the **Pause input (GPIO10) is being
pulled LOW at the same time as the Play input (GPIO9)** — an electrical bridge between the
two button lines. The one‑way behaviour (Pause looks clean) points to the bridge being at
the **Play switch itself**, so it only conducts while Play is pressed.

The real fix is to locate and clear the bridge (Section 6). No change to the Max patch is
needed, and the firmware requires no change to correct this.

## 3. The Max patch is not at fault

Tracing every patch cord in `TransportReceiveTest1.maxpat`:

- The Pause indicators (`button obj‑9` → `textbutton obj‑201`) are driven **only** by
  `[OSC‑route /transport/pause/]` (`obj‑8`).
- A `/transport/play/` packet is routed by `[OSC‑route /transport/play/]` (`obj‑5`) and
  **cannot** match the pause route — there is no cord from the play path to the pause
  indicator.
- The only object that flashes on *every* packet (`obj‑30`) sits in a different position
  (far left), not on the Pause control.

So when Max shows a Pause, it genuinely received a `/transport/pause/` packet. The two
signals are coming from the controller.

## 4. Root cause

Play = **GPIO9**, Pause = **GPIO10** — physically adjacent pins on the DevKitC‑1 header.
Each button idles HIGH through its own pull‑up and reads LOW when pressed (to ground). A
bridge between the two lines (solder whisker, stray strand, flux, or a mis‑wired switch
lug/pole) makes **closing the Play switch pull *both* lines LOW**, so one physical press is
read as two button presses and the firmware emits two OSC commands.

## 5. Why the firmware's existing guard does not stop it

FW 3.1.2 already contains a guard (`updateButtons()`) meant to reject exactly this kind of
cross‑trigger — **but it only fires when both button edges are detected in the *same*
program loop.** In practice each channel's contact bounce settles a few milliseconds apart,
and the controller loops many times per millisecond, so the two "presses" are detected in
*different* loops. Each one looks like a normal, lone press, slips past the guard, and is
sent. That is why you see two clean signals and (likely) no `[FAULT]` line.

## 6. Why Pause looks clean — and what it tells us

A simple, permanent short between the GPIO9 and GPIO10 *nets* would be **symmetric**:
pressing Pause would double‑fire too. It does not. A one‑way symptom (Play doubles, Pause
does not) indicates the bridge **only conducts when the Play switch is actuated** — most
likely a second pole or a wrong lug on the **Play switch** that also grounds the Pause line,
or a marginal/high‑resistance bridge. Importantly, a *static* continuity check (probe with
nothing pressed) can read **open** in this case and miss the fault entirely.

This reasoning assumes Pause genuinely stays single. Confirm that with the serial check in
Section 7A first: if Pause fires twice as well, the fault is instead a plain **symmetric**
short across the two button nets, and attention shifts to the header/PCB and harness rather
than the Play switch.

## 7. How to confirm

**A. Serial monitor** (USB, 115200 baud) — press Play and watch:
- Both `[BTN]  Play -> /transport/play/ 1` **and** `[BTN]  Pause -> /transport/pause/ 1`
  appearing a few ms apart confirms the controller is emitting both.
- Note whether a `[FAULT] Simultaneous transport inputs` line ever appears (see table below
  for what that implies).
- Then press **Pause** by itself several times and confirm only `[BTN]  Pause -> /transport/pause/ 1`
  appears each time, with no Play line. This proves the doubling really is confined to Play
  and is not simply being overlooked on Pause.

**B. Continuity check between GPIO9 and GPIO10, power OFF:**

| Reading | Meaning | Action |
|---|---|---|
| ~0 Ω (with nothing pressed) | Hard bridge at header/PCB | Reflow GPIO9 & GPIO10 joints; remove whisker/strand |
| ~200 Ω | Short through the panel harness | Inspect Play/Pause wires, connectors, and button lugs |
| ~20 kΩ | Healthy pull‑up path (no static short) | **Do not stop here** — re‑measure **while holding Play pressed** |
| Open when idle, **~0 Ω only while Play is held** | Bridge at the Play switch (2nd pole / wrong lug) | Re‑wire the Play switch; this is the most likely case here |

**Serial‑log discriminator:** double‑fires with an *occasional* `[FAULT]` line lean toward a
hard header/PCB bridge; double‑fires with *never* a `[FAULT]` line lean toward the
Play‑switch / marginal‑bridge case above.

## 8. Recommended fix

1. Run the checks in Section 7 to locate the bridge (focus on the Play switch wiring, testing
   with Play held down).
2. Clear the short / re‑wire the offending lug.
3. Re‑test: one press → one command, no fault.

**Firmware note (optional, not required):** the FW 3.1.2 guard could be widened from
"same loop" to a short time window (~50 ms) so it also catches millisecond‑staggered
cross‑triggers and suppresses the phantom command with a logged fault. This is
defense‑in‑depth only — it does **not** fix the wiring and would leave the Play button
non‑functional (faulting) until the hardware bridge is cleared. **Not implemented here.**

## 9. Reference

- `NaoDec_Media_Playback_Controller_PlayPause_CrossTrigger_Fix.md` (GPIO9↔GPIO10 fix doc,
  continuity table, Build doc Section 10) — https://github.com/SurasakNie/naodec
