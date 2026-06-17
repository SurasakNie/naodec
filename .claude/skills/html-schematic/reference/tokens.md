# Token Reference

## Theme contract — all 23 tokens required

| Group | Tokens |
|---|---|
| Surface | `--bg-dark`, `--bg-panel` |
| Power rails | `--wire-12v`, `--wire-5v`, `--wire-3v3`, `--wire-gnd` |
| Data channels | `--wire-data`, `--wire-data2` … `--wire-data7` (all 7 — keep slots even if unused). To add channels beyond 7: define `--wire-data8`, `--wire-data9` … and add matching `.wdataN` / `.jdataN` classes in the skeleton CSS following the existing pattern. The theme contract requires at least 7; extras are additive. |
| Text | `--text-primary`, `--text-secondary`, `--accent` |
| Component / structure | `--comp-fill`, `--comp-fill-hover`, `--comp-stroke`, `--border`, `--pin-dot` |
| Warning | `--warn`, `--warn-bg` |

A theme may add tokens but must never remove a contract token.

## Token semantics

| Token(s) | Purpose |
|---|---|
| `--bg-dark`, `--bg-panel` | Page background; semi-transparent panels (legend strip, button background) |
| `--wire-12v`, `--wire-5v`, `--wire-3v3`, `--wire-gnd` | Power rail colors |
| `--wire-data` … `--wire-data7` | Seven distinct signal-channel hues |
| `--text-primary`, `--text-secondary`, `--accent` | Body / muted / titles & active highlights. `--accent` ≈ `--wire-data` by convention (Cyberpunk default: both `#0FF0B3`) |
| `--comp-fill`, `--comp-fill-hover` | IC body fill / hover fill |
| `--comp-stroke`, `--border` | IC outline / panel borders |
| `--pin-dot` | GPIO pin marker dot (≈ `--wire-data` by convention) |
| `--warn`, `--warn-bg` | Red foreground + near-black-red background — never use for nets |

## Available themes

| File | Name | Canvas | Source namespace | Note |
|---|---|---|---|---|
| `reference/themes/Color-Palette_Cyberpunk-theme.md` | Cyberpunk | dark | `--cp-*` | **Default theme** — remapped to contract names in skeleton. |
| `reference/themes/Color-Palette_Dark-Teal-theme.md` | Dark Teal | dark | *(none — contract-only)* | Drops into `:root` directly; no remap needed. |
| `reference/themes/Color-Palette_Midnight-Blue-theme.md` | Midnight Blue | dark | `--mb-*` | |
| `reference/themes/Color-Palette_Nebula-Pop-theme.md` | Nebula Pop | dark | `--np-*` | |
| `reference/themes/Color-Palette_Cobalt-Pop-theme.md` | Cobalt Pop | dark | `--cb-*` | |
| `reference/themes/Color-Palette_Editorial-Navy-theme.md` | Editorial Navy | dark | `--en-*` | |
| `reference/themes/Color-Palette_Prism-Light-theme.md` | Prism Light | **light** | `--pl-*` | Light canvas — `--wire-*` defaults inverted to dark hex (e.g., `#212121`). |
| `reference/themes/Color-Palette_Mosaic-Pastel-theme.md` | Mosaic Pastel | **light** | `--mp-*` | Light canvas — `--wire-*` defaults inverted to dark hex (e.g., `#4A5258`). |

Add new themes to `reference/themes/` as `Color-Palette_{Name}-theme.md`. Mirror any new theme in SKILL.md's Export Specialist § Available themes table.

## Theme-coupled inline literals — sweep checklist

When adding custom snippets or migrating older schematics, watch these spots:

| Location | Correct value |
|---|---|
| `.tip { background: ... }` | `var(--bg-dark)` |
| `.comp:hover { fill: ... }` | `var(--comp-fill-hover)` |
| Warning banner `<rect fill="...">` | `var(--warn-bg)` |
| SVG export `bgRect.setAttribute("fill", ...)` | Read via `getComputedStyle(document.documentElement).getPropertyValue('--bg-dark').trim()` — CSS vars can't be used in JS attribute setters |

Always use `var(--name)` over a hardcoded hex even when the value matches a token.

## Font

- Family: `'Roboto', sans-serif` (imported from Google Fonts)
- Weights used: 400 (base), 500 (default `text`), 700 (`.bold-text`), 900 (`.black-text`)
- All SVG text: `font-family: 'Roboto', sans-serif; font-weight: 500;` via stylesheet

## Spacing / letter-spacing

| Use | Value |
|---|---|
| Wordmark / section titles | `letter-spacing="4"` |
| Sub-titles, legend labels | `letter-spacing="1"` |
| Bus end-cap decorators | `letter-spacing="3"` |
| Body / BOM / GPIO labels | no letter-spacing attribute |
