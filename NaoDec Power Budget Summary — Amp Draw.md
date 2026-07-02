# NaoDec — Power Budget Summary (Amp Draw)

**Project:** Wellness Center · Tetra & Octa Hedral · LED Controller / Power & Controller Box
**Companion to:** *NaoDec Power Wiring Diagram — Rev 1.5*
**Date:** 2026-07-02

> ⚠ **Superseded figures — see `NaoDec PC Case — Power Usage Summary.md` for the corrected budget.**
> This sheet's 12 V total (~33 A) overcounts CH1 and the slave-board logic; the corrected 12 V peak is
> **~27–28 A / ~329–341 W**. **PSU sizing was also revised (2026-07-02): the ATX is right-sized to
> **~650 W 80+ Bronze, single rail** (not the 750 W shown below) — the box is remote (fan noise
> irrelevant) and sessions are short. See the PSU report for the shortlist and
> `NaoDec_ATX_PSU_Wiring_and_Connectors.md` for wiring.

---

## 1. Power Sources

| Source | Voltage | Rated Current | Rated Power | Feeds |
|---|---|---|---|---|
| **ATX PSU** (650 W, right-sized single-rail) | 12 V | ~54 A (12 V rail) | 650 W | Scent, Vertex Coil, WS2815 logic, **all LED strips** |
| | 5 V | ~20 A | | WS2815 ESP32 logic |
| **Mean Well LRS-600-24** | 24 V | 25 A | 600 W | GAB8 amplifier **only** |
| **USB-C wall adapter** (isolated) | 5 V | 2 A | 10 W | Playback Controller **only** |

> The ATX is the single high-current hub for the LED system. GAB8 and Playback are deliberately kept **off** the ATX (see §6).

---

## 2. ATX 12 V Rail — Two Paths

The ATX 12 V splits into a **low-current path** (through the breakout board) and a **high-current path** (through Molex/PCIe pigtails → bus bar → fuses). They must stay separate — the breakout PCB traces cannot carry LED-strip current.

### Path A — Breakout board 12 V (controller logic)

| Load | Realistic | Peak | Protection |
|---|---|---|---|
| Scent Controller (Waveshare Relay-6CH, all relays on) | 0.3 A | 0.5 A | — |
| Vertex Series Coil (XL4015 buck → coils) | 1.5 A | 3.0 A | 3 A fast-blow inline |
| **Path A subtotal** | **~1.8 A** | **~3.5 A** | — |

Breakout 12 V trace limit ≈ **8–10 A** → **~35 % utilized at peak.** ✔ Safe.

### Path B — Bus bar 12 V (LED strips)

| Load | Strips | Per-strip | Total | Protection |
|---|---|---|---|---|
| **CH1 Vertex edge-strip** (Bus OUT-A) | 1 | ~4.2 A | **~4.2 A** | F1 7.5 A ATC inline |
| **CH2–CH7 Edge strips** (Bus OUT-B → FB1) | 6 | ~4.2 A | **~25.2 A** | F2–F7 7.5 A each; NTC1 10 Ω inrush |
| **Path B subtotal** | 7 | | **~29.4 A** | — |

Bus bar rated **30 A+**; fed by 2× PCIe 8-pin pigtails (~25 A) or 3–4× Molex 4-pin (~18–24 A). ✔

### ATX 12 V total

| | Current |
|---|---|
| Path A (logic) | ~3.5 A |
| Path B (LED strips) | ~29.4 A |
| **Total 12 V draw (peak)** | **~33 A** |
| ATX 12 V available | ~62 A |
| **12 V headroom** | **~29 A (47 %)** ✔ |

---

## 3. ATX 5 V Rail — WS2815 Logic

| Load | Realistic | Peak |
|---|---|---|
| ESP32-S3 Master | 0.2 A | 0.3 A |
| ESP32-S3 Slave × 6 | 0.9 A | 1.5 A |
| **Total 5 V draw** | **~1.1 A** | **~1.8 A** |

Breakout 5 V trace limit ≈ **10 A** → **~18 % utilized.** ✔ Very light.

---

## 4. Separate Rails (not on ATX)

| Rail | Load | Draw | Notes |
|---|---|---|---|
| **24 V Mean Well** | GAB8 amplifier | up to 25 A rated (audio-dependent; typical average far lower) | Own IEC mains feed |
| **5 V USB-C isolated** | Playback ESP32-S3 | ~0.5 A typical (2 A adapter) | Isolated to break audio ground loop |

---

## 5. Total System Power at Peak

| Rail | Voltage | Peak Current | Peak Power |
|---|---|---|---|
| ATX 12 V | 12 V | ~33 A | ~396 W |
| ATX 5 V | 5 V | ~1.8 A | ~9 W |
| **ATX subtotal** | | | **~405 W** (of 750 W) |
| Mean Well 24 V | 24 V | ≤ 25 A | ≤ 600 W |
| USB-C isolated | 5 V | ~0.5 A | ~3 W |

ATX loaded to **~54 %** at LED peak — comfortable margin for a continuous-duty supply.

---

## 6. Why the Splits

- **LED strips bypass the breakout board.** 29 A would burn the breakout's ~20 A PCB traces. High current goes ATX → Molex/PCIe pigtail → bus bar → fuses → strips.
- **GAB8 on its own 24 V PSU.** Different voltage; keeps a 600 W audio amp off the LED supply.
- **Playback on isolated USB-C.** Its audio signal reaches GAB8; a shared ATX ground would create a 50/60 Hz hum loop. Isolation breaks it. Playback GND does **not** tie to the ATX star ground.
- **Common ground everywhere else.** All ATX-fed GNDs (breakout, bus bar, strips, logic) share one star point so WS2815 data references match.

---

## 7. Fuse & Protection Map

| Device | Value | Location |
|---|---|---|
| F1 | 7.5 A ATC inline | Bus bar OUT-A → CH1 Vertex strip |
| F2–F7 | 7.5 A ATC each | FB1 6-ch block → CH2–7 Edge strips |
| NTC1 | 10 Ω / 10 A inrush | In series, bus bar OUT-B → FB1 input |
| Vertex Coil fuse | 3 A fast-blow | Breakout 12 V → JST SM → coil board |

---

## 8. Wire Gauge Reference

| Run | Gauge |
|---|---|
| Molex/PCIe pigtail → bus bar | 16 AWG (Molex) / 16 AWG (PCIe) |
| Bus bar → FB1 / F1 trunk | 12 AWG |
| Fuse → strip head V+ (each branch) | 14 AWG |
| Mid-injection to strips | 14 AWG |
| Breakout 12 V → Scent / Vertex Coil | 18 AWG (ferrule) |
| Breakout 5 V → ESP32 logic | 22 AWG |

---

## Quick Verdict

| Rail | Peak Load | Capacity | Status |
|---|---|---|---|
| ATX 12 V | ~33 A | ~62 A | ✔ 47 % headroom |
| ATX 5 V | ~1.8 A | ~20 A | ✔ ample |
| Breakout 12 V (logic only) | ~3.5 A | 8–10 A | ✔ safe |
| Breakout 5 V | ~1.8 A | ~10 A | ✔ light |
| Bus bar 12 V (LED) | ~29.4 A | 30 A+ | ✔ within rating |

**All rails within safe limits. The ATX comfortably powers the full LED system plus logic.**
