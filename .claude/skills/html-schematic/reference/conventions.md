# Drawing Conventions

## Units

| Context | Unit |
|---|---|
| SVG geometry (`x`, `y`, `cx`, `cy`, `r`, `width`, `height`, stroke-width, font-size) | SVG user units (1 unit ≡ 1 CSS px at zoom 1.0) |
| `viewBox` | SVG user units |
| CSS sizes (UI controls, tooltip, body) | `px` only — no `rem`, `em`, `pt`, or `%` for sizing |
| Letter spacing | `px` positive integer via `letter-spacing="N"` on `<text>` |
| Stroke widths | unitless number |

**Rule:** never mix length systems. No `mm` / `pt` inside the SVG.

## Primitives by use

| Primitive | When |
|---|---|
| `<line>` | Single straight segment (bus, separator) |
| `<polyline>` | Manhattan-routed wire (orthogonal segments only) |
| `<path>` | Wire with rounded branch corners or curves |
| `<rect>` | Component bodies, panels, legend swatches, table header backgrounds |
| `<circle>` | Pin / junction dots |
| `<text>` / `<tspan>` | All labels (no HTML text in the diagram) |

## Rounded branch corners

Use `<path>` with 5 px arc for soft tap-off or junction hop:

```html
<path d="M 850,495 L 1240,495 A 5,5 0 0,0 1250,495 L 1440,495"
      class="wdata" data-info="…"/>
```

Arc syntax: `A rx ry x-axis-rotation large-arc-flag sweep-flag x y`  
Convention: `A 5,5 0 0,0 x,y` for counter-clockwise hop; `A 5,5 0 0,1 x,y` for clockwise.  
Both absolute `A` and relative `a` are valid SVG; relative `a` is used in the hop snippets for portability.

## Stroke-width hierarchy

| Width | Use |
|---|---|
| `4` | Power / ground bus trunk |
| `2.5` | Primary power branches (12V, GND drops) |
| `2` | Secondary power (5V, 3.3V) and all data |
| `1.5` | Component outlines, panel borders, dashed section borders |
| `1` | Table header borders, final row separators |
| `0.5` | Wire-gauge / GPIO-map row separators (with opacity 0.4) |
| `0.3` | Harness-table in-row separators (with opacity 0.4) |

## Dot radius hierarchy

| Radius | Use |
|---|---|
| `4.5` | Major power junction |
| `3.5` | Secondary power junction |
| `3` | Standard pin marker (`.pin`) |
| `2.5` | Minor signal junction |

## text-anchor

| Value | Use |
|---|---|
| `start` (default) | Left-aligned labels (BOM rows, GPIO pin lists, table cells) |
| `middle` | Component titles, section panel titles, warning text, strip captions |
| `end` | Right-aligned labels (GPIO pins on right side of IC, latest revision row) |

## Vertical alignment

SVG text has no vertical anchor — set `y` baselines manually:
- Text inside a row of height `H` starting at `y0`: baseline ≈ `y0 + 0.7 × H`
- Text labeling a horizontal line at `y0`: baseline `y0 - 5` (above) or `y0 + 12` (below)

## Routing Rules

Mandatory layout constraints — these apply to every wire placed in the diagram.

| # | Rule | Detail |
|---|---|---|
| 1 | **No overlap (VR3)** | Wires must never pass through the bounding box of a component body (`<rect class="comp">`) or any SVG `<text>` label. Route around with orthogonal detours. Validator VR3 is a topological segment-vs-rectangle intersection test. VR1 handles near-miss spacing on non-intersecting pairs. **FAIL.** |
| 2 | **Crossing hop — ALL net types (VR10)** | When two unconnected wires cross — **regardless of net type** — the foreground wire must use a 5 px arc hop. Validator VR10 fails any cross-over without an arc hop within ±6 px. |
| 3 | **No parallel overlap** | Two wires of different nets must never share the same line segment. Offset perpendicularly by ≥ 8 px or bundle into a labeled bus. |
| 4 | **Universal clearance ≥ 10 units (VR1)** | For pairs whose bboxes do not intersect (VR3 catches the intersecting case), min edge-to-edge distance must be ≥ 10 SVG units. **FAIL.** |
| 5 | **Axis alignment + grid (VR2)** | Every wire segment strictly horizontal or vertical (no diagonals). Component `<rect>` no `transform="rotate(...)"`. Wire endpoints + polyline vertices on a 10-unit grid. Arc-hop paths exempt. **FAIL.** |
| 6 | **Tooltip presence and content (VR4)** | `[data-info]` on every `<line>`, `<polyline>`, `<path>`, component `<g>`, junction `<circle>`. Field count is element-type dependent: wires = exactly 3 (`NET_ID\|role\|gauge`); components = 3–4 (`ID\|brief\|spec\|note?`); junctions = 2–3 (`NET_ID\|role\|note?`). No field may be empty or whitespace-only. Pin dots, text labels, `class="deco"` exempt. **FAIL.** |
| 7 | **Channel identification (VR7)** | Two cooperating mechanisms (no per-wire midpoint label required as of v4.0): (a) **legend strip** inside `<g id="title-block">` has a swatch+label entry for every wire class used; (b) every named non-rail net surfaces as ≥1 `<text>` annotation somewhere in the schematic body (junction caption, terminal label, bus end-cap, harness-table NET cell, or dev-board annotation). `<text class="channel-label">` is decorative-optional, no longer required. Power rails (`w12v`/`w5v`/`w3v3`/`wgnd` + `-bus` variants) need only the legend swatch — no body annotation required. **FAIL.** |

To add a new routing rule in the future: append a numbered row to this table and update the snippet comment in `wire-rounded.html` if the rule has an associated snippet.

### VR-number index (validator hooks)

The table-row numbers above (1–7) order the rules for reading; the **VR-numbers** below are the stable codes the Validator and SKILL.md reference.

| VR# | Rule | Defined in |
|----|---|---|
| VR1 | Universal clearance ≥ 10 units (non-intersecting pairs) | Routing Rules row 4 |
| VR2 | Axis alignment + 10-unit endpoint grid | Routing Rules row 5; spec `reference/validator-spec.md` § VR2 |
| VR3 | No-overlap topology | Routing Rules row 1; spec `reference/validator-spec.md` § VR3 |
| VR4 | Tooltip presence and content (`[data-info]` + field-count + non-empty fields) | Routing Rules row 6; spec `reference/validator-spec.md` § VR4 |
| VR5 | Wire/bg contrast ≥ 3:1 (WCAG luminance) | SKILL.md validator checklist; spec `reference/validator-spec.md` § VR5 |
| VR6 | BOM format (`<foreignObject>` + `<table class="bom">`) | `reference/tables.md` BOM section; spec `reference/validator-spec.md` § VR6 |
| VR7 | Channel identification (legend strip + body annotations) | Routing Rules row 7; spec `reference/validator-spec.md` § VR7 |
| VR8 | Text clear-space (text vs wire centerline / pin / junction circle ≥ 5 px) | SKILL.md validator checklist; spec `reference/validator-spec.md` § VR8 |
| VR9 | Net color follows signal, not voltage | Project Wire Assignment Table (below) |
| VR10 | Arc-hop at every wire crossing | Routing Rules row 2 |

### GND-symbol exception (rule 1 corollary)

When a GND wire to the common ground bus would force a long detour through a congested area, the Wire Router may instead place a GND symbol (`⏚` text label, `fill="var(--wire-gnd)"`) directly adjacent to or below the component's GND pin. The symbol replaces the wire — there is no implied connection except via the labeled ground net.

---

## Arc-hop variants

5 px radius. `(x,y)` is the crossing point. Pick the variant whose hop bulges away from the underlying wire.

**Two arc-hop patterns exist — use the right one:**
- **`snippets/wire-rounded.html`** (primary): a complete wire + embedded hop in one `<path>` element. Use this when the Wire Router is placing a new wire that crosses an existing one.
- **Standalone paths below** (secondary): a 10-unit arc element added over a pre-existing wire that cannot be regenerated. Use only when patching an existing schematic without rerouting.

Both patterns must include `class="{wire-class} arc"` and `data-info` — the `arc` secondary class is required to exempt the path from VR2 (curved-path check) and VR7 (channel-label check).

| Orientation (which wire goes "over") | Path snippet |
|---|---|
| Horizontal wire hopping **up** over a vertical wire | `<path d="M {x-5},{y} a 5,5 0 0,0 10,0" class="{wire-class} arc" data-info="{Net name}|crossing hop|over {OTHER_NET}" fill="none"/>` |
| Horizontal wire hopping **down** under a vertical wire | `<path d="M {x-5},{y} a 5,5 0 0,1 10,0" class="{wire-class} arc" data-info="{Net name}|crossing hop|under {OTHER_NET}" fill="none"/>` |
| Vertical wire hopping **right** over a horizontal wire | `<path d="M {x},{y-5} a 5,5 0 0,1 0,10" class="{wire-class} arc" data-info="{Net name}|crossing hop|over {OTHER_NET}" fill="none"/>` |
| Vertical wire hopping **left** over a horizontal wire | `<path d="M {x},{y-5} a 5,5 0 0,0 0,10" class="{wire-class} arc" data-info="{Net name}|crossing hop|under {OTHER_NET}" fill="none"/>` |

**Sweep-flag rule of thumb (SVG y-axis points DOWN):**
- `sweep-flag = 0` → arc swept counter-clockwise → for a left-to-right horizontal, bumps **UP**; for a top-to-bottom vertical, bumps **LEFT**.
- `sweep-flag = 1` → arc swept clockwise → for a left-to-right horizontal, bumps **DOWN**; for a top-to-bottom vertical, bumps **RIGHT**.
- The bump direction should be AWAY from the wire being crossed when net hierarchy differs (bus on top → branch hops up over bus; branch on top → bus hops down under branch is rare but valid).

The hop path inherits the foreground wire's class so it keeps the correct color/stroke-width. Always `fill="none"` — a filled arc reads as a connector blob.

---

## Text rotation / reading-direction convention

**Default for vertical text is bottom-to-top.** This matches the engineering-drawing and book-spine convention — when a label runs along a vertical rail, the reader tilts their head left, not right.

| Orientation | `transform` | Reading direction | Use when |
|---|---|---|---|
| Horizontal (default) | none | left → right | always, unless space forces vertical |
| Vertical ascending | `rotate(-90, x, y)` ≡ `rotate(270, x, y)` | **bottom → top** | left-edge labels, side-rail annotations, narrow inter-column callouts, COM-bus jumper notes |
| Vertical descending | `rotate(90, x, y)` | top → bottom | **exception only** — use when layout forces it (e.g. right-edge label beneath another rotated element). When used, leave a one-line SVG comment above the `<text>` explaining why descending was chosen. |

The center of rotation `(x, y)` is the text's anchor point — passing the same `x, y` to both the text attributes and the `rotate(...)` keeps the anchor in place after rotation. Always use this 3-argument form; the bare `rotate(deg)` form rotates around the SVG origin and is almost never what you want.

---

## Fill-vs-outline rule (text-occlusion guard)

| Object | Fill |
|---|---|
| Container shapes that wrap text — `<rect>`, `<polygon>`, large `<circle>`/`<ellipse>` used as component bodies, panels, banners, table cells | **`fill="none"`** |
| Indicator shapes — junction dots (`.j*` classes, r ≤ 5), pin dots (`.pin`, r ≤ 3), GND symbol fill, color-swatch rects in legends/harness tables (≤ 4 px tall) | **Filled** with the corresponding token |
| `<text>` | Filled with `var(--text-*)` or `var(--accent)` / wire color tokens |

Rationale: filled container shapes mask underlying text and arc hops when exported. Indicator dots and swatches are small enough that their fill is the signal — they must stay solid.

---

## Unused-channel dimming (L2)

When a multi-channel component (relay board, ADC, multi-channel driver) has channels physically present on the PCB but not wired up in this schematic, render the unused channels with reduced visual weight so the eye reads them as "present but inactive."

| Property | Active channel | Unused channel |
|---|---|---|
| Stroke | Net color (`var(--wire-dataN)` or matching rail) | `var(--comp-stroke)` (grey) |
| Opacity | 1.0 | 0.40 – 0.45 |
| Terminal label fill | Net color | `var(--text-secondary)` |
| Terminal label opacity | 1.0 | 0.40 – 0.45 |

Canonical example: Scent Controller §10.6 U1, where channels CH5 and CH6 are drawn at `opacity 0.45` with grey strokes while CH1–CH4 stay at full opacity in their assigned net colors. This convention is built into the `dev-board-visual` snippet — pass an `is_unused: true` flag per-channel to apply the dimming.

The dimming is a designer cue, not a separate net class — unused channels keep their original `class="comp"` and remain valid VR3/VR6 targets.

---

## Internal wiring inside dev-board-visual (L6)

Wires drawn INSIDE a `<g transform="translate(...) scale(...)">` board replica (the COM jumper bus from Scent Controller §10.6 U1, traces inside an IC silk drawing, etc.) are authored as part of the snippet — Sub-Agent 6 (Wire Router) does NOT route into transformed sub-groups. The router treats the dev-board-visual outer `<g>` as a single component for routing purposes; everything inside is the snippet's job.

When you need a labeled jumper or bus inside the board frame, follow the Scent Controller §10.6 pattern: a vertical spine `<line>` + horizontal stubs to each pin, both in the same wire-rail color (often `var(--wire-5v)` for relay-COM bussing), with a rotated label between the spine and the board edge using the 3-argument `rotate(270, x, y)` form.

---

## Glyphs

| Glyph | Use |
|---|---|
| `·` (U+00B7) | Inline separator in subtitle / spec lines |
| `→` | Signal flow direction in `data-info` strings |
| `─` / `──` | Decorative borders in text labels |
| `⚠` | Warning markers (always paired: `⚠ … ⚠`) |
| `×` (U+00D7) | Quantity prefix ("2× ESP32-S3") |
| `Ω` / `µ` / `°` | Component values |
| `&amp;` | All literal `&` in attributes must be entity-encoded |

Use UTF-8 throughout (`<meta charset="UTF-8">`); never substitute `+/-` or `->`.

---

## Project Wire Assignment Table (VR9 — project-scoped rule)

If the working directory contains a `CLAUDE.md` with a **Wire Assignment Table**, the Wire Router MUST read it at session start and treat it as binding. Never reassign a channel that appears in the table.

Expected format in project `CLAUDE.md`:

```
| wdata channel | Hex     | Assigned to (GPIO / bus)        |
|---------------|---------|--------------------------------|
| wdata         | #…     | <signal description>           |
| wdata2        | #…     | <signal description>           |
```

**VR9 — Net color follows signal, not voltage:**
Once a net is assigned a wdata class, that class covers the entire routed path — GPIO output → driver input → driver output → MOSFET gate → MOSFET drain → load.
Exception: the always-hot wire from PSU/fuse to MOSFET drain (upstream of the switch) stays `.w12v` — it is never switched.
