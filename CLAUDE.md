# CLAUDE.md — NaoDec

Project memory for the **NaoDec** 7-channel WS2815 LED installation (1,740 px) — dual
ESP32-S3-WROOM-1 running WLED in master/slave DDP, 3.3 V → 5 V via an SN74AHCT245N.
Self-contained interactive HTML docs — no build step, no dependencies.
Published at https://surasaknie.github.io/naodec/.

## Wire Assignment Table

| wdata channel | Hex     | Assigned to (GPIO / bus) |
|---------------|---------|--------------------------|
| wdata         | #88e2d6 | CH1                      |
| wdata2        | #ffffff | CH2                      |
| wdata3        | #7cb3ff | CH3                      |
| wdata4        | #c8a2e8 | CH4                      |
| wdata5        | #f0997b | CH5                      |
| wdata6        | #97c459 | CH6                      |
| wdata7        | #f0d060 | CH7                      |

**Binding** for the `html-schematic` skill (VR9 net-color rule). The Net Color Allocator,
Wire Router, and Style Validator MUST read this table at session start and never reassign a
channel listed here. Hex values are the **Dark Teal** palette, matching the existing
Rev-series schematics in this repo — keep new/revised schematics on that theme so colors
stay consistent.

> Power rails are fixed (not reassignable): `w12v` `#eaddaa` "12V" · `w5v` `#c9a86a` "5V" ·
> `w3v3` `#a28854` "3.3V" · `wgnd` `#4a6b6d` "GND".

## Channel reference (full mapping)

Source: README hardware tables + `NaoDec_WS2815_LED_Controller_Rev1.6.html`.

| CH  | wdata class | Strip      | GPIO (board)   | Buffer    | LEDs |
|-----|-------------|------------|----------------|-----------|------|
| CH1 | wdata       | #1 Vertex  | GPIO1 (Master) | U2 A1→B1  | 60   |
| CH2 | wdata2      | #2 Edge A  | GPIO4 (Master) | U2 A2→B2  | 280  |
| CH3 | wdata3      | #3 Edge B  | GPIO5 (Master) | U2 A3→B3  | 280  |
| CH4 | wdata4      | #4 Edge C  | GPIO6 (Master) | U2 A4→B4  | 280  |
| CH5 | wdata5      | #5 Edge D  | GPIO4 (Slave)  | U2 A5→B5  | 280  |
| CH6 | wdata6      | #6 Edge E  | GPIO5 (Slave)  | U2 A6→B6  | 280  |
| CH7 | wdata7      | #7 Edge F  | GPIO6 (Slave)  | U2 A7→B7  | 280  |

Theme reference: `.claude/skills/html-schematic/reference/themes/Color-Palette_Dark-Teal-theme.md`.

## Conventions

- Each document is versioned in its filename as `RevX.Y` (e.g. `..._Rev1.6.html`).
- Superseded revisions are moved to `Archived/`.
- `index.html` is **auto-generated** by `.github/workflows/update-index.yml` on
  push to `main` (it lists every `*.html` except `index.html`, sorted). When
  renaming/adding HTML on a feature branch, update `index.html` and `README.md`
  by hand to stay consistent until the workflow regenerates it on `main`.
- Keep the three 12 V / 5 V power rails fully isolated (never tie V+ rails).

## Status notes

- **Series Coil / Electromagnet subsystem is Rev 0 — pre-release** (renamed from
  `Rev1.0` to `NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`). It is a
  pre-release design, **not** a finalized/current build. Treat its numbers and
  BOM as provisional.
  - It is a ~3 Ω resistive near-short on 12 V DC (an inductor does nothing on
    steady-state DC); current is set only by wire resistance + PSU.
  - The crystal core is non-magnetic (μ ≈ air) → no field boost; weak air-core
    coils (~28 AT each).
  - Adopted solution: a **CC/CV buck (XL4015, CC set ~3 A)** is the current
    limiter — it caps the loop regardless of load resistance (removes the
    runaway risk). Still **fuse the buck input** (3–5 A): the CC limit is
    regulation, not fault protection, and bucks fail *shorted*. Connectors are
    **JST SM 2-pin, both pins paralleled** (fine at the capped ~3 A; VH/XT30/
    Anderson for more margin). Keep runs uncoiled; never run the string without
    the buck.
