# NaoDec — project memory

Browser-based documentation set for a 7-channel WS2815 LED installation (dual
ESP32-S3 / WLED) plus supporting subsystems. All docs are self-contained HTML —
no build step, no dependencies. Published at https://surasaknie.github.io/naodec/.

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
  - Safety: fuse it (3–5 A), prefer a current-limited supply (≤3 A; unlimited
    draw ≈ 4 A), upgrade connectors (common JSTs are over rating at 4 A), keep
    cable runs uncoiled, and never reduce cable resistance without a limiter.
