# NaoDec — ATX PSU Wiring & Connectors (12 V / 5 V / 3.3 V)

**Companion to:** *NaoDec — Power Requirements & Controller Box Report* · Config 2 (PC Case + ATX PSU)
**Date:** 2026-07-02
**Scope:** How to get 12 V, 5 V (and 3.3 V) off a standard ATX PSU and to each NaoDec device —
which connector, which wire, how much current it may carry, how to switch the PSU on without a
motherboard, and how to tap it cleanly.

> **Sizing context:** this build uses a **~650 W single-12 V-rail ATX PSU** (see the PSU report).
> The 12 V rail must deliver the **27.1 A** full-white peak; a 650 W unit gives ~54 A on 12 V, so
> the load sits at ~50 % of the rail. Everything below is about *distributing* that safely.

---

## 1. Every ATX PSU already outputs all these rails

You do **not** need a special model. Any standard ATX PSU provides, simultaneously:

| Rail | Nominal | Typical 650 W capacity | Used by NaoDec |
|------|---------|------------------------|----------------|
| **+12 V** | 12 V | ~54 A (single rail) | LED strips, scent, vertex coil buck |
| **+5 V** | 5 V | ~20 A (100 W) | ESP32 logic (Master + Slave + U2) |
| **+3.3 V** | 3.3 V | ~20 A | *not used* (WLED boards make their own 3.3 V) |
| **+5 VSB** (standby) | 5 V | ~2.5 A | *not used* (always live, even when "off") |
| **−12 V** | −12 V | ~0.3 A | *not used* |

> ⚠ **Avoid "ATX12VO" PSUs.** A 12VO ("12-volt-only") unit outputs **only 12 V** and expects a
> motherboard to derive 5 V/3.3 V — you would get no 5 V for the logic. Standard ATX and **ATX 3.0**
> both keep the 5 V/3.3 V rails; only the specific **"12VO"** label is the problem. All of the
> shortlisted 650 W Bronze units are standard multi-rail ATX — just confirm on the box.

---

## 2. Wire colour code (universal, all brands)

| Wire colour | Rail |
|-------------|------|
| **Yellow** | +12 V |
| **Red** | +5 V |
| **Orange** | +3.3 V |
| **Black** | GND (common return for all rails) |
| **Purple** | +5 V standby |
| **Green** | PS_ON# (turn-on signal) |
| Grey | Power-OK |
| Blue | −12 V |

GND is common — the yellow (12 V) and red (5 V) loads share the black return wires. This is why one
**star ground point** works for the whole ATX side (see §7).

---

## 3. Which connector carries which rail

| Connector | Pins | Rails present | Best used for |
|-----------|------|---------------|---------------|
| **24-pin ATX** (main) | 24 | 12 V, 5 V, 3.3 V, 5 VSB, GND, **PS_ON#** | Turn-on + low-current 12 V/5 V taps (via breakout) |
| **EPS / CPU** | 4+4 | **12 V only** + GND | Highest single-connector 12 V current (~28 A) |
| **PCIe / VGA** | 6+2 | **12 V only** + GND | High-current 12 V (edge-strip bus bar) |
| **SATA power** | 15 | **12 V, 5 V, 3.3 V** + GND | Small mixed 12 V + 5 V taps |
| **Molex** (peripheral) | 4 | **12 V + 5 V** + GND | Small 12 V and/or 5 V taps |
| Floppy (Berg) | 4 | 12 V, 5 V (tiny) | *ignore* |

**Rule of thumb:** *big 12 V current → PCIe / EPS; small mixed taps → Molex / SATA.*

---

## 4. Current each connector may safely carry

The limit is usually the **wire gauge**, not the connector pin.

| Path | Per-wire safe current | Notes |
|------|----------------------|-------|
| PCIe 8-pin (3× 12 V wires) | ~150 W / connector (spec); ~12–15 A practical | Two of these ≈ the 25 A edge load |
| EPS 8-pin (4× 12 V wires) | ~28 A / connector | Beefiest single 12 V source |
| Molex 12 V (yellow, 18 AWG) | ~5–6 A per wire | Fine for all NaoDec small taps |
| SATA 12 V / 5 V | ~4.5 A per rail (54 W total) | Fine for logic + one small 12 V tap |

**Never** run the 25.2 A edge-strip load through Molex or SATA — those wires overheat. That current
**must** go through PCIe (or EPS) connectors into the bus bar.

---

## 5. NaoDec load → connector map

| Load | Rail | Current | Take it from | Wires |
|------|------|--------:|--------------|-------|
| **Edge strips CH2–CH7** (bus bar) | 12 V | 25.2 A | **2× PCIe 8-pin** (or 1× EPS 8-pin) | Yellow + Black |
| Vertex strip CH1 | 12 V | 0.9 A | Molex or SATA | Yellow + Black |
| Scent controller (Relay-6CH) | 12 V | 0.4 A | Molex or SATA | Yellow + Black |
| Vertex coil buck (XL4015 input) | 12 V | ~1.6 A | Molex | Yellow + Black |
| **ESP32 logic** (Master + Slave + U2) | **5 V** | 0.82 A | Molex or SATA | **Red + Black** |

All the small taps together are < 3 A on 12 V and < 1 A on 5 V — a single Molex/SATA chain per rail
covers them. The edges are the only heavy path.

---

## 6. Turning the PSU on without a motherboard

An ATX PSU idles (only 5 VSB live) until **PS_ON# (green, pin 16 of the 24-pin)** is pulled to any
**black GND**. Two ways:

- **Always-on:** jumper green → black (a wire or the 1 kΩ resistor the report specifies). PSU runs
  whenever AC is present.
- **Switched:** wire a **latching front-panel switch** across green ↔ black for a real power button.

A "Power-OK" (grey) wire goes high shortly after; you can ignore it for this build.

---

## 7. How to physically tap the wires (cleanest first)

1. **24-pin ATX breakout board** (~a few hundred THB): clips onto the main connector and exposes
   screw terminals labelled **12 V / 5 V / 3.3 V / GND**, usually with a **built-in on-switch**.
   Best home for the small 12 V/5 V taps + turn-on. *Does not* carry the 25 A edge load.
2. **Cut the PCIe 8-pin pigtails** and land yellow/black straight onto the **bus bar → FB1 fuse
   block** for the edge strips (the high-current path).
3. **Molex / SATA → screw-terminal adapters** if you prefer not to cut factory cables.

**Recommended layout:** breakout board for logic + scent + vertex + coil (and the on-switch);
bare PCIe pigtails to the bus bar for the six edge strips.

---

## 8. Protection is still your job

An ATX PSU gives **no per-branch overcurrent protection** — the group OCP only trips near the rail
limit (tens of amps). Every downstream fuse from the source design stays **mandatory**:

- **F1** 7.5 A — Vertex strip CH1
- **FB1** 6-channel 7.5 A block — edge strips CH2–CH7
- **NTC1** 10 Ω / 10 A — inrush limiter on the 12 V bus
- **F_MAIN / F1-scent / F3–F6** — scent controller
- **10 A MCB** on the 220 V AC input

Add an inline fuse on the coil buck's 12 V input too (3–5 A), per the coil subsystem notes.

---

## 9. What an ATX PSU can *not* do

- **No 24 V.** ATX rails are 12 V / 5 V / 3.3 V only. The GAB8 audio amp needs its **own 24 V supply**
  (e.g. Mean Well LRS-240-24) — keep it off the ATX entirely.
- **No isolated rails.** All ATX outputs share one ground. Where you need isolation (e.g. the
  Playback Controller, to break an audio ground loop), power it from a **separate USB-C adapter**, not
  the ATX.

---

## References

- `NaoDec_Power_and_Controller_Box_Report.md` — PSU sizing, shortlist, fusing topology
- `NaoDec_Config2_PSU_Survey_Sheet_20260625B.md` — surveyed models & prices
- `NaoDec_WS2815_LED_Controller_Rev1.6.html` — LED controller schematic (bus bar, FB1, NTC1)
- `NaoDec_Scent_Controller_Schematic_Rev2.0.html` — scent controller fusing
