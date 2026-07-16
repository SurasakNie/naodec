# Max Patch Comparison — Transport Receive Test → Test Player (Resume)

**From:** `TransportReceiveTest1.maxpat` (shipped inside `TransportReceiveTest1.maxpat.zip`)
**To:** `NaoDec_TestPlayer_rev3.1.2_resume.maxpat`

Both patches live in `firmware/media_playback_controller/` and are bench-side tools for the
NaoDec Media Playback Controller — the ESP32-S3 operator panel (rotary volume encoder +
Play/Pause/Stop buttons) that sends **OSC-over-UDP** transport and volume commands to Max/MSP
on port `9000`. This note records how that tool evolved from a *receive-only indicator* into a
*functional test player* that actually plays audio and implements the resume behavior the
firmware's OSC contract promises.

## Summary

`TransportReceiveTest1.maxpat` proves only that the panel's OSC messages **arrive and route
correctly** — it blinks a button and flashes a Play/Pause/Stop label per command and moves a
volume slider. It contains **no audio objects at all** (the Build doc §10 "test with prints
first" stage).

`NaoDec_TestPlayer_rev3.1.2_resume.maxpat` is a **real test player**: it opens a sound file,
plays it through `sfplay~ → *~ → ezdac~`, applies volume as a ramped gain, and adds a
stopped / playing / paused **state machine** so that Play resumes from a pause but restarts
from a stop — matching the Build doc mapping "`/transport/play 1` = Start **or resume** media
playback". It also drops the CNMAT `OSC-route` dependency in favor of a stock `route` object.

## File metadata

| | `TransportReceiveTest1.maxpat` | `NaoDec_TestPlayer_rev3.1.2_resume.maxpat` |
|---|---|---|
| Role | OSC receive indicator / router test | Full test player with resume logic |
| Audio | None | `sfplay~ → *~ → ezdac~` |
| OSC routing | 4× CNMAT `OSC-route` externals (package required) | 1× vanilla `route` (no externals) |
| `udpreceive` arg | `naodec-playback.local 9000` | `9000` |
| Volume | Display-only slider (0.0–1.0) | Functional, ramped gain + numeric readout |
| Console logging | None | `print PLAY / PAUSE / STOP / VOL` |
| View | Presentation mode, 600×200, styled panel, toolbar hidden | Plain patcher, 920×650, toolbar visible |
| Packaging | Zipped `.maxpat` | Plain (diffable) `.maxpat` JSON |
| Max file format | 9.1.4 (x64) | 9.1.4 (x64) |

## What changed

### 1. From indicator to player

The old patch's whole job was visual confirmation. Each incoming command flashed a blink
button and a styled textbutton (`Play` green / `Pause` amber / `Stop` red), and `/volume`
moved a 0–1 slider. Nothing produced sound.

The new patch adds a full playback chain:

- `open` message → **`sfplay~`** (file player)
- `sfplay~` → **`*~ 0.`** (gain stage, starts muted)
- `*~` → **`ezdac~`** (stereo DAC / speaker output)

### 2. Transport state machine with resume semantics

The new patch keeps a shared state in a `value naodec_transport_state` object
(**0 = stopped, 1 = playing, 2 = paused**) and gates each command on the current value:

| Command | `TransportReceiveTest1` | `NaoDec_TestPlayer_rev3.1.2_resume` |
|---|---|---|
| Play while **stopped** | flash "Play" | `sfplay~` message `1` → start from the beginning; state → playing |
| Play while **playing** | flash "Play" | ignored (`sel 0 1 2` outlet for state 1 is left unconnected) |
| Play while **paused** | flash "Play" | `sfplay~` message `resume` → continue; state → playing |
| Pause | flash "Pause" | acts only while playing (`sel 1`): `pause` → `sfplay~`; state → paused |
| Stop | flash "Stop" | unconditional `0` → `sfplay~` (stop + rewind); state → stopped |

Housekeeping resets state to **stopped** so the next Play restarts cleanly: the `sfplay~`
end-of-file bang (right outlet), the `open` message, and a boot-time `loadbang` all write `0`.
The old patch had no state at all.

### 3. OSC routing rebuilt with stock objects

Old: four separate CNMAT **`OSC-route`** externals — `/transport/play/`, `/transport/pause/`,
`/transport/stop/`, `/volume/` — fed in parallel from `udpreceive`. These require the CNMAT
package to be installed in Max, and were the objects audited during the Play/Pause
cross-trigger investigation (see `NaoDec_Media_Playback_Controller_PlayPause_CrossTrigger_Fix.md`).

New: a single vanilla **`route /transport/play /transport/pause /transport/stop /volume`**, so
the patch runs on a bare Max install with no third-party externals.

### 4. `udpreceive` cleaned up

`udpreceive naodec-playback.local 9000` → **`udpreceive 9000`**. The object takes only a listen
*port*; the mDNS hostname is the panel's (sender's) name and was a stray argument that
`udpreceive` does not use.

### 5. Volume is now functional

- **Old:** display-only slider, no effect on anything.
- **New:** the `/volume` float feeds a `flonum` + `* 127.` slider readout **and**, in parallel,
  `pack 0. 50 → line~ → *~` — a real gain applied to the audio with a **50 ms ramp** to avoid
  clicks. A `loadbang → 0.7` sets a sensible default volume at patch load.

### 6. Console logging added

`print PLAY`, `print PAUSE`, `print STOP`, and `print VOL` echo every received command to the
Max console. The old patch gave only visual blinks.

### 7. UI style: control surface → engineering patch

- **Old:** opened in presentation mode — a fixed 600×200 black rounded panel, large styled
  transport textbuttons, an any-packet activity blinker, toolbar hidden. A polished standalone
  monitor (its commit message was "Standalone tester for Mac").
- **New:** a plain 920×650 patcher window, toolbar visible, one small colored blink button per
  command, and a 7-line instruction comment describing the resume rules.

### 8. Packaging and naming

The new file is committed as plain (diffable) `.maxpat` JSON rather than a zip, and its name
tracks the firmware it partners with (**FW 3.1.2**) plus the feature (**`_resume`**).

## What stayed the same

- UDP listen port **`9000`**.
- The four lowercase OSC addresses: `/transport/play`, `/transport/pause`, `/transport/stop`,
  `/volume`.
- One visual blink indicator per transport command.
- Max **9.1.4** (x64) file format.

> **Case-sensitivity note:** the copy of `TransportReceiveTest1.maxpat` in the repo zip already
> carries the 2026-07-14 audit fix that corrected its Stop route from `/transport/Stop/` to
> lowercase `/transport/stop/`. Only the original 2026-07-10 upload had the mis-cased route.
> Both patches now agree on the lowercase addresses the firmware actually emits.

## Object inventory

**`TransportReceiveTest1.maxpat`** — `comment` ×2 (title + reference info), `button` ×4 (one
any-packet blinker + three per-command), `slider` (volume display), `OSC-route` ×4,
`udpreceive`, `textbutton` ×3 (Play/Pause/Stop), `panel` (presentation background).

**`NaoDec_TestPlayer_rev3.1.2_resume.maxpat`** — `comment` (instructions), `udpreceive`,
`route`, `button` ×3, `print` ×4, `value naodec_transport_state` ×3 (shared),
`sel` ×2 (`sel 0 1 2`, `sel 1`), `t b b` ×4, `message` ×8 (`1`, `resume`, `pause`, `0`, state
writes `1`/`2`/`0`, `open`, `0.7`), `flonum`, `* 127.`, `slider`, `pack 0. 50`, `line~`,
`sfplay~`, `*~ 0.`, `ezdac~`, `loadbang`.
