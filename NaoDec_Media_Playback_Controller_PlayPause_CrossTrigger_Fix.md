# NaoDec Media Playback Controller — Play/Pause Cross-Trigger Fix

**Date:** 2026-07-14
**Applies to:** Media Playback Controller hardware **Rev 3.0**, firmware **FW 3.1.2**
**Related:**
[`media_playback_controller_R3.1.ino`](firmware/media_playback_controller/media_playback_controller_R3.1.ino) ·
[`NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md`](NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md) (Rev 3.2, Section 10) ·
[`NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html`](NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html)

## Symptom

On a built controller, pressing **Play** also fires **Pause** (and vice-versa).
The coupling is symmetric — either button triggers both transport commands.

## Root cause

A **short between GPIO9 (Play) and GPIO10 (Pause)**. These are physically
adjacent pins on the ESP32-S3-DevKitC-1 header, so a solder whisker, stray
strand, pinched harness, or flux bridge ties the two button nodes together. Each
button input idles high through its own 10 kΩ pull-up (R3/R4) and pulls low when
its switch closes to GND; once the two nodes are bridged, closing **either**
switch pulls **both** low, so one physical press reads as two.

This is a **build/wiring fault, not a design fault** — the Rev 3.0 schematic
keeps the two channels fully independent (separate pull-up R3/R4, debounce cap
C3/C4, series resistor R8/R9, GPIO, and wire color).

### Layers ruled out during the audit

| Layer | Finding |
|---|---|
| Firmware button logic | Each pin is debounced independently (`DebouncedButton` per button); no shared state, no cross-coupling. |
| Max test patch | `/transport/play` and `/transport/pause` are matched by **separate** `OSC-route` objects fed in parallel from `udpreceive`, with no cross-wire — verified in `TransportReceiveTest1.maxpat`. |
| Hardware | GPIO9↔GPIO10 short — **confirmed root cause.** |

A hard short cannot be cured in software: with the two pins bridged they read the
identical value, so firmware cannot recover which button was actually pressed.

## What was changed

### 1. Firmware FW 3.1.2 — detect and contain (not a cure)

The three transport buttons are mutually exclusive: a person cannot close two
separate panel switches within the same debounce instant. `updateButtons()` now
samples all three debounced inputs once per pass and, if more than one press edge
lands together, **rejects** the ambiguous event and logs:

```
[FAULT] Simultaneous transport inputs (Play Pause) — a single press cannot
trigger two buttons; suspect a short between the button GPIOs (check
GPIO9<->GPIO10, Build doc Section 10). Command suppressed.
```

- Stops the phantom Pause on every Play (no wrong OSC command is emitted).
- Turns a confusing intermittent symptom into an explicit, logged fault that
  names the suspect pins.
- On a correctly wired panel exactly one edge fires per press, so the guard
  never triggers — zero behavior change.

This is a **guard and a diagnostic aid**, not a replacement for clearing the
short.

### 2. Max patch — corrected Stop route (found in the same audit)

`TransportReceiveTest1.maxpat` routed Stop as `/transport/Stop/` (capital S),
which never matched the firmware's lowercase `/transport/stop` (OSC address
matching is case-sensitive). Corrected to `/transport/stop/` so all four routes
match. Unrelated to the Play/Pause short, but Stop was silently dead in the test
patch.

### 3. Documentation

- Build doc **Section 10** troubleshooting row now points at the `[FAULT]` log
  and the GPIO9↔GPIO10 continuity check.
- Firmware README documents FW 3.1.2 and the patch correction.

## The actual remedy (hardware)

The fault is cleared on the bench, not in firmware. Power the board **off** and
measure continuity between GPIO9 and GPIO10:

| Reading | Meaning | Action |
|---|---|---|
| ≈ 0 Ω | Bridge at the adjacent DevKitC-1 header pins or the PCB node (before R8/R9) | Reflow / clean the GPIO9 & GPIO10 solder joints; remove the whisker or strand |
| ≈ 200 Ω | Panel-side short through R8 + R9 | Inspect the white (Play) / yellow (Pause) harness, H3/H4 connectors, and button lugs |
| ≈ 20 kΩ | Healthy (R3 + R4 through the 3V3 bus) | No short — recheck the firmware GPIO pin map / Max patch |

## Verification

- **Guard logic:** exercised with a standalone unit test covering all input
  combinations — single Play/Pause/Stop each emit exactly one command with no
  fault; any two-or-three simultaneous edges emit nothing and log a `[FAULT]`.
- **Max patch:** JSON re-validated after the edit; all four routes
  (`/transport/play`, `/transport/pause`, `/transport/stop`, `/volume`) confirmed
  present and lowercase.
- **On hardware:** flash FW 3.1.2, open the USB serial monitor (115200 baud),
  press Play. A `[FAULT] Simultaneous transport inputs …` line confirms the short
  is real → clear it per the table above, then re-test: one press = one command,
  no fault line.
