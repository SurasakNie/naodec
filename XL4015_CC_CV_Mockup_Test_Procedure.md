# XL4015 CC/CV Mockup Test Procedure

**Revision:** 1.0
**Date:** 2026-07-14
**Applies to:** NaoDec Series Coil / Electromagnet subsystem (**pre-release, Rev 0**)
**Purpose:** Bench-qualify each dual-pot XL4015 CC/CV buck on a resistive **mock load** that reproduces the series-coil loop, **before** it is ever connected to the real 60-coil string.

> ⚠ **Pre-release subsystem.** The series coil design is provisional (see
> [`NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`](NaoDec_Series_Coil_Build_Rev0_Pre-Release.html)
> and [`NaoDec_Vertex_Series_Coil_Rev1.0.html`](NaoDec_Vertex_Series_Coil_Rev1.0.html)). This
> procedure is the gate that must pass before coil connection. **Never run the coil string without a
> verified CC/CV buck** — the cold loop is a ~1.85 Ω near-short on 12 V DC (an inductor does nothing
> at steady-state DC), so an unregulated connection would attempt ~6.5 A / ~78 W.

## Why a mockup first

The XL4015's constant-current (CC) limit is what makes the whole subsystem safe: it caps the loop current regardless of load resistance. Before trusting a real coil string to it, prove on a **known resistive load** that the specific board actually regulates at the set current, holds it through a burn-in, and doesn't fail. A resistor bank can't be damaged by a miswired test and gives readings you can check against Ohm's law; the real coils can't.

## What the mock load represents

| Element | Mock part | Value | Represents |
|---|---|---|---|
| Wiring | Mock wire (the real 20 AWG run, or an equivalent length) | **~1.30 Ω** measured | The complete 20 AWG installation wiring |
| Coils | Resistor bank | **~0.56 Ω / ≥10 W** | All 60 coils (~0.55 Ω calculated at 20 °C) |
| **Total mock load** | in series | **~1.86 Ω** | The ~1.85 Ω cold-loop estimate |

**Resistor bank:** a practical build is **10 × 5.6 Ω / 1 W metal-film in parallel = 0.56 Ω / 10 W**. At 3.0 A the bank dissipates ~5.0 W total (~0.5 W per resistor), well within the 1 W-each rating; the 10 W aggregate gives margin for the burn-in.

## Equipment

- The **dual-pot XL4015 HW-083-B** CC/CV buck under test (one per qualification run).
- **12 V DC bench supply** for the buck input, current-capable (≥3 A) and current-limited if possible.
- **Exact 3 A slow-blow (T-type) fuse** inline at the buck input. (Exactly 3 A — CC regulation is not fault interruption, and a buck can fail shorted.)
- **Input decoupling** across the buck IN+/IN−: 220–470 µF low-ESR electrolytic (≥25 V) ‖ 100 nF X7R (≥25 V).
- **Mock wire** of ~1.30 Ω (measure it — see below) and the **0.56 Ω / 10 W resistor bank**.
- **Two DMMs** (one as voltmeter, one on current if not using an inline ammeter) or a DMM + clamp meter.
- **Ammeter in series after XL4015 OUT+.**
- A thermometer / IR probe for the burn-in, and a timer.

## Setup

```
12 V PSU (+) → [exact 3 A T-fuse] → XL4015 IN+
                                     XL4015 IN− → 12 V PSU (−)
      (220–470 µF ‖ 100 nF directly across IN+/IN−)

XL4015 OUT+ → [ammeter] → mock wire (~1.30 Ω) → resistor bank (~0.56 Ω) → XL4015 OUT−
```

1. **Measure the mock wire cold** with a 4-wire / good DMM and record it (target ~1.30 Ω). Measure the resistor bank (target ~0.56 Ω). Their series sum is the mock load (~1.86 Ω).
2. Fit the input fuse and decoupling **before** applying power.
3. Connect the **ammeter in series immediately after OUT+**.
4. Keep everything uncoiled and bare conductors clear of each other, exactly as the real install requires.

## Set the operating point

1. With the mock load connected, apply 12 V.
2. **Set CC to 3.0 ±0.1 A** using the current pot (the board should be in CC mode under this load).
3. **Set the CV ceiling to 11.0 ±0.3 V** (open-load ceiling; under the mock load the output sits far below this, in CC).

### Expected readings at 3.0 A into the 1.86 Ω mock load

| Measurement | Expected | Basis |
|---|---|---|
| Loop current (ammeter) | **3.0 A** (CC setpoint) | — |
| Total output (OUT+ → OUT−) | **~5.58 V** | 3.0 A × 1.86 Ω |
| Across the mock wire | **~3.90 V** | 3.0 A × 1.30 Ω |
| Across the resistor bank | **~1.68 V** | 3.0 A × 0.56 Ω |
| Output power | **~16.7 W** | 5.58 V × 3.0 A |

The three voltages must add up (3.90 + 1.68 ≈ 5.58 V) and each must match Ohm's law against the resistance you measured. A mismatch means a bad joint, a wrong resistor value, or a meter/lead-resistance error — find it before proceeding.

## Burn-in

Hold **30 minutes** at the 3.0 A setpoint on the mock load. During and after:

- Current stays regulated at 3.0 ±0.1 A; output voltage stays ~5.5–5.6 V.
- No thermal runaway: monitor the XL4015 (inductor, IC, diode), the fuse, and the resistor bank. Nothing should exceed its rating or the planned **70–80 °C thermal-cutoff** threshold. If a TCO is fitted in the real loop, confirm it is below trip.
- No smell, discoloration, or fuse nuisance-trip.

## Pass / fail

**PASS** — the board qualifies for coil connection when all of:

| Gate | Requirement |
|---|---|
| CC regulation | Holds 3.0 ±0.1 A on the mock load |
| CV ceiling | 11.0 ±0.3 V open-load |
| Ohm's-law check | Total ≈ 5.58 V; wire ≈ 3.90 V; bank ≈ 1.68 V, consistent with measured resistances |
| Burn-in | 30 min stable, no thermal excursion, no fuse trip |
| Protection fitted | Exact 3 A T-fuse + input decoupling present and intact |

**FAIL** — do not connect coils if the board won't hold CC, oscillates, overheats, trips the fuse, or the voltages don't reconcile. Set it aside; use only a board that has passed.

## After qualification — what the real string does (context, not a target)

The mock target above is the **design operating point** (3.0 A CC on a 1.86 Ω load). The **actual assembled 60-coil string** has been bench-measured at **11.68 V / 2.75 A (~32 W) at the buck output** — its real loop came out nearer ~3 Ω, so it settles at the **CV/CC knee** and draws ~2.75 A, just under the 3 A cap, rather than sitting deep in CC. That is expected and safe (still current-limited); it is documented in
[`NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`](NaoDec_Series_Coil_Build_Rev0_Pre-Release.html). Do **not** re-tune the board to force 3.0 A into the real string — the CC cap is the safety limit, and sitting below it is fine.

After a board passes this mockup and before live operation, still:

- Confirm the **assembled-loop resistance** end-to-end against the ~1.85 Ω estimate (joints and copper temperature add variation).
- Keep the complete 20 AWG run **uncoiled**, keep bare copper from touching, and keep this V+ rail **isolated** from all LED rails.
- Fit the **70–80 °C thermal cutoff** for manned operation.

This procedure is referenced by the build sequence at
[`NaoDec_Build_Step9_Commissioning_and_Test.md`](NaoDec_Build_Step9_Commissioning_and_Test.md) §9.8 (coil commissioning gate) and by the Series Coil section of [`README.md`](README.md).
