# NaoDec — PC Case Power Usage Summary

**Enclosure:** ATX mid-tower ("PC case")
**Companion to:** *NaoDec PC Case Layout — Rev 1.2* · *NaoDec Power Wiring Diagram — Rev 1.5*
**Date:** 2026-07-02

Every powered component in the case, its supply, and its current/power draw. Figures taken from the PC Case Layout component tooltips.

---

## ⚡ TOTAL CURRENT DRAW (headline)

Current is per-rail (amps at different voltages don't add meaningfully) — totals are shown per supply, plus a combined power figure.

| Supply | Peak Current | Peak Power |
|---|---|---|
| **ATX 12 V** | **~28.1 A** | ~337 W |
| **ATX 5 V** | **~0.82 A** | ~4 W |
| **Mean Well 24 V** (GAB8) | **≤ 25 A** | ≤ 600 W |
| **USB-C isolated 5 V** (Playback) | **~0.4 A** | ~2 W |
| **Sum of all currents (reference only)** | **~54.3 A** | — |
| **TOTAL SYSTEM POWER (worst case)** | | **≤ ~945 W** |

> **The number that sizes the build: ATX draws ~28 A on 12 V** — everything else on the ATX rides on top of that. The 25 A on 24 V is the amplifier on its own separate supply.

---

## 1. Supplies Inside the Case

| Supply | Voltage | Rated | Powers |
|---|---|---|---|
| **ATX PSU** (650 W, right-sized) | 12 V / 5 V / 3.3 V | ~54 A on 12 V | LED strips, Scent, Vertex coil, all logic |
| **Mean Well LRS-600-24** | 24 V | 25 A · 600 W | GAB8 amplifier only |
| **USB-C wall adapter** (isolated) | 5 V | 2 A | Playback Controller only |

---

## 2. Component-by-Component Draw

### Module 1 — WS2815 LED Controller (Rev 1.6)

| Component | Supply | Current | Power | Notes |
|---|---|---|---|---|
| ESP32-S3 Master (N16R8) | ATX 5 V | ~0.40 A | ~2.0 W | WLED, CH1–CH4 |
| ESP32-S3 Slave (N16R8) | ATX 5 V | ~0.40 A | ~2.0 W | DDP receiver, CH5–CH7 |
| U2 · SN74AHCT245N level shifter | ATX 5 V | ~0.02 A | ~0.1 W | 3.3 V → 5 V, 7 ch |
| **CH1 Vertex strip** (60× WS2815) | ATX 12 V | **~0.9 A** | ~10.8 W | Single feed, F1 7.5 A |
| **CH2–CH7 Edge strips** (6× 280 LED) | ATX 12 V | **~25.2 A** | ~302 W | 4.2 A each, FB1 F2–F7 |

### Module 2 — Scent Controller (Rev 2.0)

| Component | Supply | Current | Power | Notes |
|---|---|---|---|---|
| Waveshare ESP32-S3-Relay-6CH | ATX 12 V | ~0.40 A | ~4.8 W | 12 V direct, no buck |
| Scent station (atomisers) | *external* | — | — | Mounted outside case |

### Module 3 — Media Playback Controller (Rev 1.0)

| Component | Supply | Current | Power | Notes |
|---|---|---|---|---|
| ESP32-S3-DevKitC-1 | **USB-C isolated** | ~0.40 A | ~2.0 W | NOT on ATX (ground-loop isolation) |
| Front-panel controls (encoder + 3 btn) | 3.3 V logic | negligible | — | Powered off the ESP board |

### Module 4 — GAB8 Audio Amplifier

| Component | Supply | Current | Power | Notes |
|---|---|---|---|---|
| GAB8 Class-D amp board | **24 V Mean Well** | ≤ 25 A | ≤ 600 W | Audio-dependent; average far lower |
| 6× Microlab X3 + 4× Dayton TT25 | *external* | — | — | Speaker/transducer loads |

### Module 5 — Vertex Series Coil (Rev 1.0a)

| Component | Supply | Current | Power | Notes |
|---|---|---|---|---|
| XL4015 buck (input side) | ATX 12 V | ~1.6 A | ~19 W | CC 3.0 A / ~5.55 V out |
| Coil array L1–L6 | (buck output) | ~3.0 A @ 5.55 V | ~16.6 W | Current-limited series loop |
| F1 3 A slow-blow + TCO1 | inline | — | — | Fault protection |

---

## 3. Roll-Up by Supply

### ATX 12 V

| Load | Current |
|---|---|
| Edge strips CH2–CH7 | 25.2 A |
| Vertex strip CH1 | 0.9 A |
| Vertex coil (buck input) | 1.6 A |
| Scent Controller | 0.4 A |
| **Total 12 V (peak)** | **~28.1 A** |

### ATX 5 V

| Load | Current |
|---|---|
| ESP32-S3 Master | 0.40 A |
| ESP32-S3 Slave | 0.40 A |
| U2 level shifter | 0.02 A |
| **Total 5 V** | **~0.82 A** |

### ATX total

| Rail | Current | Power |
|---|---|---|
| 12 V | ~28.1 A | ~337 W |
| 5 V | ~0.82 A | ~4 W |
| **ATX total (peak)** | | **~341 W** |
| ATX capacity (650 W, right-sized) | | ~650 W |
| **Loaded** | | **~52.5 %** ✔ |

---

## 4. Whole-System Power at Peak

| Supply | Voltage | Peak Current | Peak Power | Loaded |
|---|---|---|---|---|
| ATX PSU | 12 V + 5 V | ~29 A | **~341 W** | 52.5 % of 650 W |
| Mean Well 24 V | 24 V | ≤ 25 A | **≤ 600 W** | audio peaks only |
| USB-C isolated | 5 V | ~0.4 A | **~2 W** | trickle |
| **Case total (worst case)** | | | **≤ ~945 W** | |

> Realistic sustained draw is well below this — the GAB8 only pulls near 600 W at continuous full audio output, and the LED strips rarely run all channels at full white simultaneously.

---

## 5. Dominant Loads (where the power goes)

1. **Edge LED strips (CH2–CH7): ~302 W** — 89 % of the ATX load. This is the number that sizes the ATX 12 V rail, the bus bar (30 A+), and the PCIe/Molex pigtails.
2. **GAB8 amplifier: up to 600 W** — biggest single number, but on its own dedicated 24 V supply, so it never touches the ATX budget.
3. Everything else (logic, scent, coil, vertex strip): **~37 W combined** — trivial.

---

## 6. Headroom Verdict

| Supply | Peak Load | Capacity | Status |
|---|---|---|---|
| ATX 12 V | ~28 A | ~54 A (650 W) | ✔ ~48 % headroom |
| ATX 5 V | ~0.82 A | ~20 A | ✔ ample |
| Mean Well 24 V | ≤ 25 A | 25 A | ✔ sized to match |
| USB-C isolated | ~0.4 A | 2 A | ✔ ample |

**The 650 W ATX is right-sized for the LED + logic + scent + coil load (~52 % loaded, ~48 % 12 V headroom). The 24 V Mean Well is matched to the amplifier. No supply is stressed.**

---

## Note on figures corrected from the earlier budget file

Two numbers in *NaoDec Power Budget Summary — Amp Draw.md* were high and are corrected here per the PC Case Layout:

| Item | Old (budget file) | Correct (this file) |
|---|---|---|
| CH1 Vertex strip | 4.2 A | **0.9 A** (60 LEDs) |
| 5 V logic total | 1.8 A (7 boards) | **0.82 A** (Master + 1 Slave) |

Net effect: ATX 12 V peak drops from ~33 A to **~28 A**; the "comfortable headroom" conclusion is unchanged and now larger.
