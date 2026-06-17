# Table Patterns

All patterns use SVG `<text>`, `<rect>`, `<line>` — never HTML `<table>`.

Available patterns: GPIO Map · BOM List · Revision History · Wire-Gauge · Wire-Harness / Pinout (per part).

---

## GPIO Map

### Section title
```html
<text x="710" y="1405" font-size="14" fill="var(--accent)" class="black-text" letter-spacing="1">GPIO MAPPING</text>
```

### Header row (replace `{Y}` with the actual y-coordinate)
```html
<rect x="705" y="{Y}" width="620" height="18" fill="rgba(234,221,170,0.12)" rx="1"/>
<line x1="705" y1="{Y}"     x2="1325" y2="{Y}"     stroke="var(--border)" stroke-width="1"/>
<line x1="705" y1="{Y+18}"  x2="1325" y2="{Y+18}"  stroke="var(--border)" stroke-width="1"/>
<text x="713"  y="{Y+13}" font-size="11" fill="var(--accent)" class="black-text">GPIO</text>
<text x="783"  y="{Y+13}" font-size="11" fill="var(--accent)" class="black-text">Buffer</text>
<text x="863"  y="{Y+13}" font-size="11" fill="var(--accent)" class="black-text">Channel</text>
<text x="953"  y="{Y+13}" font-size="11" fill="var(--accent)" class="black-text">Strip</text>
<text x="1103" y="{Y+13}" font-size="11" fill="var(--accent)" class="black-text">LEDs</text>
<text x="1173" y="{Y+13}" font-size="11" fill="var(--accent)" class="black-text">Type</text>
```

### Data row + separator (replace `{Y}` with the actual y-coordinate)
```html
<text x="713"  y="{Y}" font-size="11" fill="var(--wire-data)"      class="bold-text">GPIO1 (M)</text>
<text x="783"  y="{Y}" font-size="11" fill="var(--text-secondary)" class="bold-text">U2 CH1</text>
<text x="863"  y="{Y}" font-size="11" fill="var(--wire-data)"      class="bold-text">CH1</text>
<text x="953"  y="{Y}" font-size="11" fill="var(--text-secondary)" class="bold-text">#1</text>
<text x="1103" y="{Y}" font-size="11" fill="var(--text-primary)"   class="bold-text">60</text>
<text x="1173" y="{Y}" font-size="11" fill="var(--text-secondary)" class="bold-text">Vertex</text>
<line x1="705" y1="{Y+7}" x2="1325" y2="{Y+7}" stroke="var(--border)" stroke-width="0.5" opacity="0.4"/>
```

### Geometry rules
- Header height: `18 px`
- Row pitch: `20 px` (data baselines at `y = header_y+18+17, +37, +57, …`)
- Row separator: `0.5 px` stroke, `0.4` opacity, `7 px` below baseline
- Final bottom border: `1 px` stroke (no opacity), under last row at baseline + 7
- Column x positions: `713, 783, 863, 953, 1103, 1173`

---

## BOM (Bill of Materials)

The BOM lives in the bottom panel BOM region (Layout Manifest: `x ∈ [40, 660]`). Rendered as **pure SVG** — `<text>`, `<rect>`, and `<line>` only, no `<foreignObject>` and no HTML `<table>`. This keeps the schematic exportable cleanly to standalone SVG and PNG across all browsers, with no `<foreignObject>` serialization fragility.

**Container structure** (wraps the entire BOM in a single `<g>` so VR6 can detect it):

```svg
<g id="bom-panel" class="bom-panel" data-info="Bill of Materials|Component list">
  <rect x="40" y="1080" width="620" height="{H}" rx="4"
        fill="none" stroke="var(--comp-stroke)" stroke-width="1.5"/>
  <text x="350" y="1100" font-size="14" fill="var(--accent)"
        text-anchor="middle" class="black-text" letter-spacing="2">BILL OF MATERIALS</text>
  <line x1="40" y1="1108" x2="660" y2="1108" stroke="var(--comp-stroke)" stroke-width="1"/>
  <!-- column header band -->
  <rect x="40" y="1108" width="620" height="20" fill="var(--bg-panel)" stroke="none"/>
  <text x="60"  y="1122" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">#</text>
  <text x="105" y="1122" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">QTY</text>
  <text x="195" y="1122" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">REF</text>
  <text x="455" y="1122" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">DESCRIPTION</text>
  <line x1="40"  y1="1128" x2="660" y2="1128" stroke="var(--comp-stroke)" stroke-width="0.5"/>
  <!-- vertical column dividers -->
  <line x1="80"  y1="1108" x2="80"  y2="{Y_BOTTOM}" stroke="var(--comp-stroke)" stroke-width="0.5" opacity="0.4"/>
  <line x1="130" y1="1108" x2="130" y2="{Y_BOTTOM}" stroke="var(--comp-stroke)" stroke-width="0.5" opacity="0.4"/>
  <line x1="260" y1="1108" x2="260" y2="{Y_BOTTOM}" stroke="var(--comp-stroke)" stroke-width="0.5" opacity="0.4"/>
  <!-- BOM rows here — see Row template below -->
</g>
```

**Row template** (one block per BOM line item; emitted by Sub-Agent 10):

```svg
<text x="60"  y="{ROW_Y}" font-size="10" fill="var(--text-primary)" text-anchor="middle">{N}</text>
<text x="105" y="{ROW_Y}" font-size="10" fill="var(--text-primary)" text-anchor="middle">{QTY}</text>
<text x="195" y="{ROW_Y}" font-size="10" fill="var(--accent)"       text-anchor="middle" class="bold-text">{REF}</text>
<text x="268" y="{ROW_Y}" font-size="10" fill="var(--text-primary)">{DESCRIPTION}</text>
<line x1="80" y1="{ROW_Y+5}" x2="655" y2="{ROW_Y+5}" stroke="var(--comp-stroke)" stroke-width="0.3" opacity="0.4"/>
```

**Geometry rules:**

- First row baseline: `y = 1143`
- Row pitch: `16 px` (next row `y = ROW_Y + 16`)
- Column x-anchors: `60` (#), `105` (QTY), `195` (REF), `268` (DESCRIPTION — left-anchored, no `text-anchor`)
- Row separator: `<line>` at `y = ROW_Y + 5`, stroke `0.3`, opacity `0.4`, spanning `x = 80 → 655`
- Outer panel height `{H}`: `28 + ROW_COUNT × 16 + 20` (header band + rows + bottom margin); the column dividers' `{Y_BOTTOM}` matches the panel's bottom edge.

**Column rules:**

| Column | Rule |
|---|---|
| **Item #** | Contiguous 1-based sequence. Stable across rebuilds (append; don't renumber). |
| **Qty** | Total count of this part. Multiple designators in one row are summed (e.g., `R1, R2` → `2`). |
| **Designator (REF)** | Comma-space separated list (`R1, R2, R3`) OR range (`A1–A4`). Sorted by letter then number. Rendered in `var(--accent)` with `class="bold-text"`. |
| **Description** | Value + package + tolerance + (rating), in order. Use Unicode units (`kΩ`, `µF`, `°C`). Left-anchored (no `text-anchor` attribute). |

**Critical-row highlighting** (M5): when a component has `is_critical=true` in the manifest (auto-set for fuses where `margin_ratio < 1.5`), every cell in that row uses `fill="var(--warn)"` and adds `class="bold-text"` — including the row's `<line>` separator below. Canonical example: Scent Controller §15.1 rows 8 (F_MAIN, T2A) and 10 (F2, T1.5A).

**Validator VR6** enforces: exactly one `<g class="bom-panel">` container in the body; column header `<text>` elements present in order (`#`, `QTY`, `REF`, `DESCRIPTION`); every `<rect class~="comp">` designator present in exactly one REF-column `<text>`; Item# contiguous 1-based; row baselines aligned across the 4 cells. See [`validator-spec.md`](validator-spec.md) § VR6 for the algorithm.

---

## Revision History

```html
<text x="1370" y="1466" font-size="14" fill="var(--accent)"
      class="black-text" letter-spacing="1">REVISION HISTORY</text>
```

Single-line entry:
```html
<text x="1370" y="{Y}" font-size="13" fill="var(--text-secondary)" class="bold-text">
  <tspan fill="var(--text-primary)">Rev {X.Y}</tspan> — {Change summary}.
</text>
```

Multi-line entry (continuation indented 60 px, 16 px line-feed):
```html
<text x="1370" y="{Y}" font-size="13" fill="var(--text-secondary)" class="bold-text">
  <tspan fill="var(--text-primary)">Rev {X.Y}</tspan> — {Lead clause};
  <tspan x="1430" dy="16">{Continuation 1};</tspan>
  <tspan x="1430" dy="16">{Continuation 2}.</tspan>
</text>
```

Latest revision — highlight with accent color:
```html
<text x="1370" y="{Y}" font-size="13" fill="var(--accent)" class="bold-text">
  <tspan fill="var(--text-primary)">Rev {X.Y}</tspan> — {Change}.
</text>
```

- Single-line pitch: `20 px`
- Continuation: `<tspan x="1430" dy="16">` (+60 px indent from x=1370 anchor)

---

## Wire-Gauge Table

Documents the AWG / cross-section / current rating per wire color. Lives in the lower section between BOM and the harness-table column.

```html
<g class="wire-gauge-table" transform="translate(690,1080)" data-info="Wire gauge|AWG and current rating per net color">
  <rect x="0" y="0" width="300" height="180" rx="2"
        fill="none" stroke="var(--comp-stroke)" stroke-width="1.5"/>
  <text x="150" y="19" font-size="13" fill="var(--accent)"
        text-anchor="middle" class="black-text" letter-spacing="1.5">WIRE GAUGE</text>
  <line x1="0" y1="28" x2="300" y2="28" stroke="var(--comp-stroke)" stroke-width="1"/>

  <!-- header row -->
  <text x="40"  y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">CH</text>
  <text x="120" y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">AWG</text>
  <text x="200" y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">A / mm²</text>
  <text x="265" y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">NOTE</text>

  <!-- data row (repeat) -->
  <rect x="20" y="58" width="20" height="4" rx="1" class="j5v"/>
  <text x="120" y="64" font-size="11" fill="var(--text-primary)"   text-anchor="middle" class="bold-text">18</text>
  <text x="200" y="64" font-size="11" fill="var(--text-secondary)" text-anchor="middle">10A · 0.82</text>
  <text x="265" y="64" font-size="11" fill="var(--text-secondary)" text-anchor="middle">power</text>
</g>
```

- Row pitch: `22 px`
- Use the same `j*` class as the corresponding wire so the swatch tracks any theme switch.
- Outline-only frame (`fill="none"`).

---

## Fuse-Margin Table

Documents `fuse rating / steady load / margin ratio` per fuse component. Lives in its own slot in the lower section (default `x=690 y=1290 w=300 h=180`), typically stacked below the Wire-Gauge table.

```html
<g class="fuse-margin-table" transform="translate(690,1290)" data-info="Fuse margin summary|Steady load vs fuse rating">
  <rect x="0" y="0" width="300" height="180" rx="2"
        fill="none" stroke="var(--comp-stroke)" stroke-width="1.5"/>
  <text x="150" y="19" font-size="13" fill="var(--accent)"
        text-anchor="middle" class="black-text" letter-spacing="1.5">FUSE MARGIN</text>
  <line x1="0" y1="28" x2="300" y2="28" stroke="var(--comp-stroke)" stroke-width="1"/>

  <!-- header row -->
  <text x="40"  y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">ID</text>
  <text x="120" y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">RATING</text>
  <text x="200" y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">LOAD</text>
  <text x="265" y="44" font-size="10" fill="var(--text-secondary)" text-anchor="middle" class="bold-text">MARGIN</text>

  <!-- data row (repeat) — flagged in --warn when margin_ratio < 1.5 -->
  <text x="40"  y="64" font-size="11" fill="var(--accent)"         text-anchor="middle" class="bold-text">{FUSE_ID}</text>
  <text x="120" y="64" font-size="11" fill="var(--text-primary)"   text-anchor="middle">{RATING} A</text>
  <text x="200" y="64" font-size="11" fill="var(--text-secondary)" text-anchor="middle">{LOAD} A</text>
  <text x="265" y="64" font-size="11" fill="{MARGIN_FILL}"         text-anchor="middle" class="bold-text">{MARGIN}×</text>
</g>
```

- Row pitch: `22 px`
- `{MARGIN_FILL}` is `var(--text-primary)` for `margin_ratio ≥ 1.5`, `var(--warn)` (with `class="bold-text"`) for `< 1.5`.
- Critical fuses (`margin_ratio < 1.5`) auto-stamp `is_critical = true` on the corresponding component entry — this drives BOM warn-color highlighting (Sub-Agent 10).
- Outline-only frame (`fill="none"`).

---

## Wire-Harness / Pinout Table (per part)

Emit one table per **IC / dev kit / connector / header** with **≥ 4 used pins**. Skip 2-pin parts (R, C, LED, transistor, 2-pin header).

**Coverage:**
- ICs — DIP-8 op-amps, ESP32, ATmega, MAX485, regulators with > 3 pins
- Dev kits — Arduino Uno/Nano/Mega header rows, Raspberry Pi 40-pin header, ESP32 dev boards
- Connectors — JST PH/XH, Molex, Dupont, terminal blocks
- Headers — 2.54 mm pin headers, IDC ribbon, board-to-board

**Placement:** in the lower section, in the column adjacent to the wire-gauge table. Tables stack vertically in the order their parts appear in the main diagram (top-down, left-to-right).

**Template:** see [`snippets/harness-table.html`](../snippets/harness-table.html). 4 columns — Pin # / Pin Name / Net / Color swatch.

**Geometry rules:**
- Title bar height: `28 px`
- Header row height: `22 px`
- Data row height: `22 px`
- Total height: `28 + 22 + ROW_COUNT × 22` (= `50 + ROW_COUNT × 22`)
- Default width: `300 px` (ICs) or `360 px` (dev kits, 40-pin headers)
- Column proportions: `14% / 36% / 36% / 14%` (pin # / name / net / swatch)
- Outline-only frame; row separators at `0.3 px` stroke with `0.4` opacity

**Color swatch:** small `<rect width="20" height="4"/>` with the wire's `j*` class (e.g. `class="j5v"` for a 5V pin, `class="jdata3"` for a CH3 GPIO). The class makes the swatch follow theme switches automatically.

**`data-info` tooltip:** `"{PART_NAME} pinout|Wire-harness map"`.

---

## Channel identification (VR7)

Channels are identified by **two cooperating mechanisms**, not by per-midpoint labels on every wire:

1. **Legend strip** in the title block — paired color swatch + text label for every wire class used in the schematic.
2. **Net annotations** scattered through the body — short labels like `PSU+`, `ATZ1+`, `DATA_RGB` placed near terminal blocks, junctions, branch points, or bus end-caps.

The legend tells the reader "what color = what rail/channel"; the body annotations tell the reader "this specific net here is X". A `<text class="channel-label">` on every wire midpoint (the v3.1 contract) is no longer required — engineers don't actually draw that way at the densities real schematics reach. Channel labels are **decorative and optional** in v4.0.

### Legend strip format

Lives inside `<g id="title-block">`. One swatch+label pair per wire class in use:

```svg
<rect x="600" y="46" width="24" height="3" rx="1.5" fill="var(--wire-12v)"/>
<text x="632" y="52" font-size="12" fill="var(--text-secondary)" class="bold-text" letter-spacing="1">12V</text>
```

**Geometry:** swatch is `24 × 3` px with `rx=1.5`. Text baseline is `+6` px below the swatch row, anchored 8 px right of the swatch's right edge. Stride between entries: typically 60-80 px along x.

**Label conventions:**

| Wire class | Legend label |
|---|---|
| `w12v` (and `-bus` variant) | `12V` |
| `w5v` (and `-bus` variant) | `5V` |
| `w3v3` (and `-bus` variant) | `3.3V` or `3V3` |
| `wgnd` (and `-bus` variant) | `GND` |
| `wdata`, `wdata2` … `wdataN` | channel name from working-dir CLAUDE.md "Wire Assignment Table"; fall back to uppercased class suffix (`DATA`, `DATA2`, …) |

Bus variants share the rail entry — no separate trunk vs branch swatches.

### Body annotations

Every data net (`wdata`, `wdata2`, …) must appear as ≥1 `<text>` annotation somewhere in the schematic body. Acceptable placements:

- Near a junction or terminal block (e.g. `PSU+`, `ATZ1+` next to a relay COM/NO pin)
- As a bus end-cap label (e.g. `── COMMON GROUND BUS ──`)
- As a net-ID caption inside a `dev-board-visual` snippet's schematic-frame text layer
- As a wire-harness table NET-column entry

Power rails (`w12v`, `w5v`, `w3v3`, `wgnd`) are exempt from this body-annotation requirement — their identity is conveyed by the legend swatch alone.

### Optional decorative channel labels

`<text class="channel-label">` is still a valid decoration when a wire's identity might otherwise be ambiguous (e.g. parallel wires crossing a busy region). When used:

```svg
<line x1="200" y1="300" x2="400" y2="300" class="wdata2"/>
<text x="300" y="294" class="channel-label" text-anchor="middle">CAN_TX</text>
```

The label is exempt from VR2 (curved-path), VR4 (data-info), and VR7 (itself). Style baseline:

```css
.channel-label { font-family: monospace; font-size: 9px; fill: var(--text-secondary); pointer-events: none; }
```

**Validator VR7** checks: (a) every wire class used in the body has a swatch+label in the legend strip; (b) every named non-rail net surfaces as ≥1 text annotation in the body. See [`validator-spec.md`](validator-spec.md) § VR7 for the algorithm.

**Tooltip interaction:** body annotations and channel labels are decorative; VR4 exempts `<text>` elements, so `data-info` is not required on them. The hover tooltip remains on the wire itself.
