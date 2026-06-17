# Validator Spec — Sub-Agent 8 algorithm reference

This file is the algorithmic companion to the validator checklist in `SKILL.md`. Sub-Agent 8 reads both: SKILL.md states the contract ("VR3 — no wire-overlap on text/components"), and this file states the procedure ("for each wire segment, run Liang-Barsky clipping vs each comp/text bbox; FAIL on non-empty intersection").

Each rule below specifies: **Inputs** (what to read), **Procedure** (pseudocode), **Edge cases** (exemptions, tolerances), **Failure message format**.

This file covers all eleven validator rules (VR1–VR10, plus the WARN-level VR8b). SKILL.md remains the authoritative contract (what each rule enforces); this file provides the algorithmic procedure (how to enforce it).

---

## VR1 — Universal clearance ≥ 10 units

**Inputs:**
- Bounding boxes of all wire elements (`<line>`, `<polyline>`, `<path>`), `<rect class~="comp">` (id resolved via `rect.closest('g[id]')`; if the rect lives inside a transformed `<g>`, compose ancestor transforms before clearance math), `<text>` elements, and junction `<circle>` elements (by circumference: `{x: cx-r, y: cy-r, w: 2r, h: 2r}`)

**Procedure:**

```
objects = gatherBboxes(wires + compRects + texts + junctionCircles)
for each pair (A, B) in objects where A != B:
    if bboxesIntersect(A.bbox, B.bbox):
        continue   # overlapping objects are VR3's domain, not VR1's
    gap = minEdgeToEdgeDist(A.bbox, B.bbox)
    if gap < 10:
        FAIL `VR1 <A.id> too close to <B.id> (${gap.toFixed(1)} units — min 10)`
```

**Edge cases:**
- Intersecting pairs skipped here — VR3 handles actual overlap.
- Canvas registration marks and decorative elements (`class~="deco"`) are excluded.
- Stroke width is not added to bbox — geometric edge suffices.

**Failure message:**
- `VR1 <idA> too close to <idB> (X.X units — min 10)`

---

## VR2 — Axis alignment + 10-unit grid

**Inputs:**
- Every `<line>`, `<polyline>`, `<path>` element in the SVG body
- Every `<rect>` element with `class~="comp"`

**Procedure:**

```
for each wire-shaped element W in body:
    skip if W.class matches /(^| )(arc|hop)( |$)/   # arc-hops exempt

    segments = []
    if W is <line>:
        segments = [(W.x1, W.y1, W.x2, W.y2)]
    elif W is <polyline>:
        pts = parsePoints(W.getAttribute('points'))
        segments = pairwise(pts)
    elif W is <path>:
        cmds = parsePathD(W.getAttribute('d'))
        if any(cmd.type in {'C', 'Q', 'A', 'S', 'T'} for cmd in cmds):
            FAIL `VR2 curved path <W.id> — only M/L/H/V allowed`
        segments = pathToSegments(cmds)

    for (x1, y1, x2, y2) in segments:
        if x1 != x2 and y1 != y2:
            FAIL `VR2 non-axis-aligned segment at (x1,y1)→(x2,y2) on <W.id>`
        for (px, py) in [(x1, y1), (x2, y2)]:
            if isDeclaredPin(px, py):     # endpoint lands on a dev-board-visual schematic_pin or <circle class="pin">
                continue                  # pin coords come from scaled board art — exempt from the grid
            if Math.abs(px) % 10 != 0 or Math.abs(py) % 10 != 0:
                FAIL `VR2 off-grid endpoint at (px, py) on <W.id>`

    if W is <polyline>:
        for (px, py) in pts:                          # intermediate vertices too
            if px % 10 != 0 or py % 10 != 0:
                FAIL `VR2 off-grid vertex at (px, py) on <W.id>`

for each <rect class~="comp"> R:
    t = R.getAttribute('transform') or ''
    if /rotate\s*\(/.test(t):
        FAIL `VR2 rotated component <R.id> — no rotate transforms allowed`
```

**Edge cases:**
- Negative coordinates are valid (e.g., `x1="-170"` passes — `-170 % 10 == 0`).
- The integer modulo is `Math.abs(v) % 10 === 0` to handle JS's negative-modulo behavior cleanly.
- **Pin-landing exemption (dev-board-visual):** a wire endpoint coincident (±0.5) with a declared `schematic_pins` entry or a `<circle class="pin">` center is exempt from the 10-unit grid — those coordinates derive from scaled board artwork and are rarely grid-aligned. `isDeclaredPin(px, py)` returns true on such a match. Intermediate `<polyline>` vertices are NOT exempt (route them on-grid).
- viewBox, stroke-width, font-size, and CSS-only positioning are out of scope.
- Decorative `<rect>` elements (legend swatches, title-block boxes) are out of VR2's scope — VR2 only checks wire endpoints + polyline vertices + component rect rotation.

**Failure messages:**
- `VR2 non-axis-aligned segment at (x1,y1)→(x2,y2) on <id>`
- `VR2 off-grid endpoint at (x,y) on <id>`
- `VR2 off-grid vertex at (x,y) on <id>` (polyline-only)
- `VR2 rotated component <id> — no rotate transforms allowed`
- `VR2 curved path <id> — only M/L/H/V allowed` (elements with class~="arc" or class~="hop" are exempt)

---

## VR3 — No-overlap (topological)

**Inputs:**
- Every wire segment (parsed per VR2's procedure, including arc-hop paths)
- Every `<text>` element's bounding box
- Every `<rect class~="comp">` bounding box (id resolved via `rect.closest('g[id]')`)

**Procedure:**

```
targets = []
for each <text> T in body where T.class does not include 'deco':
    targets.push({id: T.id, bbox: T.getBBox()})
for each <rect class~="comp"> R where R.class does not include 'deco':
    parent_g = R.closest('g[id]')
    id = parent_g ? parent_g.id : (R.id or '<rect>')
    # If R is inside a transformed <g> (translate/scale), compose the bbox into
    # the parent coord frame before comparing against wire segments in that frame.
    bbox = applyAncestorTransforms(R, {x: R.x, y: R.y, w: R.width, h: R.height})
    targets.push({id: id, bbox: bbox})

for each wire-shaped element W:
    segments = parseSegments(W)              # same parser as VR2
    for (x1, y1, x2, y2) in segments:
        for T in targets:
            if liangBarsky(x1, y1, x2, y2, T.bbox):
                mid = ((x1+x2)/2, (y1+y2)/2)
                FAIL `VR3 wire <W.id> overlaps <T.id> at (mid.x, mid.y)`
```

**Liang-Barsky reference:** standard parametric line-clipping algorithm. Returns true if any portion of segment (x1,y1)→(x2,y2) intersects the rect interior (not just touches edge). Touching-edge-only (clearance == 0) is VR1's job, not VR3's.

**Edge cases:**
- Skip targets with `class~="deco"`.
- Wire passing exactly along the rect edge (not through interior): VR3 passes, VR1 fires with `clearance < 10`.
- Self-intersection within one element: not checked.
- `<text class="channel-label">` is included as a target — wires should not overlap their own labels. The ±5-unit allowance from VR7 placement keeps this safe in practice.

**Failure message:**
- `VR3 wire <wire-id> overlaps <target-id> at (x,y)`

---

## VR4 — Tooltip presence and content

**Inputs:**
- Every `<line>`, `<polyline>`, `<path>` (any class except `deco`/`pin`/`arc`-only-overlay variants)
- Every `<g>` with `class~="comp"`
- Every `<circle>` with class matching `/^j/` (junctions)

**Required field count by element kind:**

| Kind | Selector | Required fields | Format |
|---|---|---|---|
| Wire | `line`, `polyline`, `path` | exactly 3 | `NET_ID\|segment role\|gauge or voltage` |
| Component | `rect[class~="comp"]` (id resolved via `rect.closest('g[id]')`) | 3 or 4 | `ComponentID\|brief\|spec[\|note]` |
| Junction | `circle[class^="j"]` | 2 or 3 | `NET_ID\|junction role[\|note]` |

No field may be empty or whitespace-only (catches `"NET\|role\|"`).

**Procedure:**

```
selectors = {
    'wire':      'line:not([class~="deco"]):not([class~="pin"]), polyline:not([class~="deco"]), path:not([class~="deco"])',
    'component': 'rect[class~="comp"]',
    'junction':  'circle[class^="j"]'
}
required = { wire: [3,3], component: [3,4], junction: [2,3] }    # [min, max]

for kind, sel in selectors:
    for each element E matching sel:
        # Resolve display id: for components the human-readable id lives on the
        # parent <g>, not the <rect>. Walk up to the closest g[id].
        display_id = E.id or ''
        if kind == 'component':
            parent_g = E.closest('g[id]')
            if parent_g: display_id = parent_g.id

        info = E.getAttribute('data-info')
        if info is null or info.trim() == '':
            FAIL `VR4 missing data-info on <E.tagName id=display_id class=E.class>`
            continue
        fields = info.split('|')
        n = len(fields)
        [lo, hi] = required[kind]
        if n < lo or n > hi:
            FAIL `VR4 wrong field count on <display_id>: got ${n}, expected ${lo}${lo!=hi?'–'+hi:''} for ${kind}`
            continue
        for i, f in enumerate(fields):
            if f.trim() == '':
                FAIL `VR4 empty field [${i+1}] on <display_id>: "${info}"`
```

**Edge cases:**
- Exempt: `<defs>`, `<style>`, `class~="deco"`, `class="pin"`, `<text>` (text is its own label).
- `.channel-label` text elements are exempt.
- Arc-hop paths (`class~="arc"`) follow the wire format (3 fields). The role field SHOULD describe the crossing (e.g. `crossing hop` or `arc-hop over GND`); the gauge field SHOULD say `over {OTHER_NET}` or `under {OTHER_NET}`.
- Auto-fix path during EDIT_REVISION: when Wire Router emits a new wire fragment (arc hop, jog stub, through-wire), the validator MAY single-retry by asking Wire Router to inherit field 3 (gauge/voltage) from the parent net's most-common upstream segment. Field 1 (NET_ID) auto-fills from the parent net. Field 2 (role) must be authored — empty role triggers `BLOCKED: need user input`, no auto-fix.

**Failure messages:**
- `VR4 missing data-info on <tag id=ID class=CLASS>` (FAIL)
- `VR4 wrong field count on <id>: got N, expected M–K for {kind}` (FAIL)
- `VR4 empty field [i] on <id>: "<info>"` (FAIL)

---

## VR5 — Wire / background contrast

**Inputs:**
- `:root` block parsed from `<style>` in skeleton.html
- Resolved hex values for `--bg-dark` and every `--wire-*` token

**Procedure:**

```
root = parseCssVariables(skeleton.style, ':root')
bgHex = resolveVar(root, '--bg-dark')           # follow var() chains until a hex
if bgHex == null:
    FAIL `VR5 cannot resolve --bg-dark to a hex value`
bgLum = relativeLuminance(parseHex(bgHex))

for name in keys(root) where name.startsWith('--wire-'):
    wireHex = resolveVar(root, name)
    if wireHex == null:
        FAIL `VR5 cannot resolve ${name} to a hex value`
    wireLum = relativeLuminance(parseHex(wireHex))
    ratio = (max(bgLum, wireLum) + 0.05) / (min(bgLum, wireLum) + 0.05)
    if ratio < 3.0:
        FAIL `VR5 ${name} unreadable against --bg-dark (ratio ${ratio.toFixed(2)}:1, threshold 3:1)`

def relativeLuminance(rgb):
    # WCAG 2.x relative luminance
    [r, g, b] = rgb.map(c => {
        cs = c / 255
        return cs <= 0.03928 ? cs / 12.92 : pow((cs + 0.055) / 1.055, 2.4)
    })
    return 0.2126*r + 0.7152*g + 0.0722*b
```

**Edge cases:**
- Hex shorthand (`#abc`) expands to `#aabbcc`.
- Variables referencing other variables (`--wire-data: var(--cp-wire-data)`) must be resolved transitively.
- Tokens with non-hex values (e.g., `transparent`, `currentColor`) → FAIL `VR5 ${name} non-hex value — cannot compute luminance`.
- `rgba(...)` values with an alpha channel: composite against `--bg-dark` first (premultiply), then compute luminance of the composited result.
- **`--wire-gnd` stroke-only exception:** If `--wire-gnd` ratio is between 2.0:1 and 3.0:1 (inclusive), emit `WARN VR5 --wire-gnd below 3:1 (ratio X.XX:1) — stroke-only use acceptable per theme design intent` instead of FAIL. The Dark Teal theme documents this deliberately (GND uses thick strokes ≥ 2.5 px; lower contrast is acceptable at that spatial frequency). Ratios below 2.0:1 still FAIL.

**Failure messages:**
- `VR5 cannot resolve --bg-dark to a hex value`
- `VR5 cannot resolve <token> to a hex value`
- `VR5 <token> unreadable against --bg-dark (ratio X.XX:1, threshold 3:1)`
- `VR5 <token> non-hex value — cannot compute luminance`

---

## VR6 — BOM format

**Inputs:**
- The single `<g class="bom-panel">` container in the body (if present)
- Every `<rect class~="comp">` in the body and its parent `<g>` for designator resolution

**Procedure:**

```
bomG = svg.querySelector('g.bom-panel')
if bomG is null:
    FAIL `VR6 BOM missing — no <g class="bom-panel"> in body`

# 1. Column headers — first row of <text> children of bomG with font-size=10, y near 1122
header_texts = [t for t in bomG.querySelectorAll(':scope > text')
                if abs(parseFloat(t.getAttribute('y')) - 1122) <= 2]
header_texts.sort by parseFloat(t.getAttribute('x'))
headers = [t.textContent.trim() for t in header_texts]
expected = ['#', 'QTY', 'REF', 'DESCRIPTION']
if headers != expected:
    FAIL `VR6 BOM column mismatch — got [${headers.join(' | ')}], expected [${expected.join(' | ')}]`

# 2. Data rows — group <text> children by y-baseline; each row has exactly 4 texts at x≈60/105/195/268
data_texts = [t for t in bomG.querySelectorAll(':scope > text')
              if parseFloat(t.getAttribute('y')) > 1128]    # past header underline
rows_by_y = groupBy(data_texts, t => round(parseFloat(t.getAttribute('y'))))

items = []
designators_in_bom = []
for y in sorted(keys(rows_by_y)):
    cells = sorted(rows_by_y[y], key=t => parseFloat(t.getAttribute('x')))
    if cells.length != 4:
        FAIL `VR6 BOM row at y=${y} has ${cells.length} cells — expected 4`
    expected_x = [60, 105, 195, 268]
    for (i, c) in enumerate(cells):
        if abs(parseFloat(c.getAttribute('x')) - expected_x[i]) > 4:
            FAIL `VR6 BOM row at y=${y} cell ${i+1} mis-aligned — got x=${c.getAttribute('x')}, expected ~${expected_x[i]}`
    items.push(int(cells[0].textContent.trim()))
    # REF cell may contain `R1, R2, R3` or `A1–A4` (an en-dash range) or a single designator
    ref = cells[2].textContent.trim()
    for d in splitDesignators(ref):
        if d == '—' or d == '-' or d == '': continue   # placeholder dash for n/a
        if d in designators_in_bom:
            FAIL `VR6 duplicate designator ${d} in BOM`
        designators_in_bom.push(d)

# 3. Item# contiguity
for (i, v) in enumerate(items):
    if v != i+1:
        FAIL `VR6 non-contiguous Item# at row ${i+1} — got ${v}, expected ${i+1}`

# 4. Cross-check: every component in the schematic body appears in the BOM
schematic_designators = []
for r in svg.querySelectorAll('rect[class~="comp"]'):
    parent = r.closest('g[id]')
    info = r.getAttribute('data-info')
    d = null
    if info:
        d = info.split('|')[0].trim()
    elif parent:
        d = parent.id
    if d: schematic_designators.push(d)

for d in schematic_designators:
    if d not in designators_in_bom and not isCoveredByRange(d, designators_in_bom):
        FAIL `VR6 designator ${d} missing from BOM`
```

**Helpers:**
- `splitDesignators(ref)` — splits on `,` then on `–`/`-` for ranges. A range `A1–A4` expands to `A1, A2, A3, A4` (numeric tail enumerated, alpha prefix preserved).
- `isCoveredByRange(d, list)` — true if `list` contains a range that expands to include `d` (e.g., `A1–A4` covers `A1`, `A2`, `A3`, `A4`).
- `groupBy(items, key)` — group items by key; tolerance ±1 px for row y-baseline matching.

**Edge cases:**
- Empty BOM panel (no data rows beyond the header) is OK if the schematic body has no `<rect class~="comp">` (e.g., the starter skeleton).
- The REF cell may contain a single designator (`U1`), a comma list (`R1, R2`), a range with en-dash (`A1–A4`), or a placeholder `—` (em-dash) for fastener-style line items without a designator.
- Critical-row highlighting (M5) — when row cells use `fill="var(--warn)"` instead of `var(--text-primary)`/`var(--accent)`, this is allowed (and intentional); VR6 does not validate cell colors, only structure.
- Item# starting at 0 instead of 1 → FAIL (sequence must be 1-based).
- Row baselines must align across the 4 cells (±1 px tolerance) so cell grouping is unambiguous.

**Failure messages:**
- `VR6 BOM missing — no <g class="bom-panel"> in body`
- `VR6 BOM column mismatch — got [...], expected [# | QTY | REF | DESCRIPTION]`
- `VR6 BOM row at y=Y has N cells — expected 4`
- `VR6 BOM row at y=Y cell I mis-aligned — got x=X, expected ~X0`
- `VR6 duplicate designator X in BOM`
- `VR6 non-contiguous Item# at row N — got V, expected N`
- `VR6 designator X missing from BOM`

---

## VR7 — Channel identification

**Rationale:** real-world schematics identify net channels via two mechanisms working together: (1) a **legend strip** in the title block — color swatches + text labels for each wire class in use; (2) **net annotations** scattered through the body — short labels like `PSU+`, `ATZ1+`, `DATA_RGB` near junctions, branch points, or terminal blocks. A per-midpoint `<text class="channel-label">` sibling on every wire (the prior v3.1 contract) does not match the patterns experienced engineers actually draw; v4.0 aligns VR7 to the real pattern.

**Inputs:**
- The legend strip inside `<g id="title-block">` — paired `<rect>` swatch + `<text>` label entries
- Every `<line>`, `<polyline>`, `<path>` whose class matches `/^w/` (any net class)
- Every `<text>` element in the schematic body (NET-id annotations and rail labels live here)
- The working-dir `CLAUDE.md` Wire Assignment Table (if present)

**Procedure:**

```
# ── 1. Pre-pass: build the legend index ─────────────────────────────────────
title_block = svg.querySelector('g#title-block')
legend = {}    # wireClass → labelText
if title_block:
    swatches = title_block.querySelectorAll('rect[fill^="var(--wire-"]')
    for swatch in swatches:
        # Map swatch fill (e.g. "var(--wire-12v)") to the wire class ("w12v")
        token = parseTokenFromFillVar(swatch.getAttribute('fill'))
        cls = wireClassForToken(token)            # 'wire-12v' → 'w12v', 'wire-data3' → 'wdata3'
        # Find the nearest <text> to the right of the swatch on the same y row
        label = nearestTextRight(title_block, swatch, dx_max=80, dy_tol=10)
        if label and cls:
            legend[cls] = label.textContent.trim()

# ── 2. Build the set of wire classes actually used in the body ──────────────
used_classes = set()
for W in svg.querySelectorAll('[class^="w"], [class*=" w"]'):
    if W.tagName not in {'line','polyline','path'}: continue
    if /(^| )(arc|hop|channel-label)( |$)/.test(W.class): continue
    cls = first class in W.classList matching /^w/
    if cls: used_classes.add(cls)

# ── 3. Every used wire class must have a legend entry ──────────────────────
for cls in used_classes:
    # Bus variants share the rail's legend entry (w12v-bus ≡ w12v for legend purposes)
    canonical = cls.replace('-bus', '')
    if canonical not in legend:
        FAIL `VR7 wire class "${cls}" used in body but missing from title-block legend strip`

# ── 4. Every named (non-rail) net must appear as at least one body annotation ─
#     Power rails (w12v/w5v/w3v3/wgnd and their -bus variants) are exempt because
#     their identity is conveyed by the legend swatch alone. Data nets must surface
#     a NET_ID somewhere in the body — either a junction caption, terminal label,
#     or bus-endcap text.
data_classes = {c for c in used_classes if c.startsWith('wdata')}
table = readWireAssignmentTable(cwd + '/CLAUDE.md')   # may be null
body_texts = [t.textContent.trim() for t in svg.querySelectorAll('text') if not isInTitleBlock(t)]
body_blob = ' '.join(body_texts)

for cls in data_classes:
    expected_id = table[cls] if (table and cls in table) else cls.replace('wdata','DATA').toUpperCase()
    # accept any text that contains the NET_ID as a token (e.g. 'ATZ1+' matches if expected='ATZ1')
    if not regexp(`(^|[^A-Z0-9])${escape(expected_id)}([^A-Z0-9]|$)`).test(body_blob):
        FAIL `VR7 net class "${cls}" (expected id "${expected_id}") has no annotation text in the schematic body`

def readWireAssignmentTable(path):
    # parse the markdown table under heading "Wire Assignment Table" in CLAUDE.md
    # return {className: channelName} dict, or null if file/heading absent
    ...
```

**Edge cases:**
- Arc-hop paths (`class~="arc"` or `class~="hop"`) and channel-label texts are skipped entirely.
- Bus variants (`w12v-bus`, `w5v-bus`, `w3v3-bus`, `wgnd-bus`) share the rail's legend entry — the strip needs only one swatch per rail color, not separate trunk/branch swatches.
- Net-id annotation matching is **token-bounded**: `ATZ1` matches `ATZ1+` but does not falsely match `ATZ10`. Use word-boundary-like regex `(^|[^A-Z0-9])` and `([^A-Z0-9]|$)`.
- If the schematic uses a `dev-board-visual` snippet, signal-net annotations placed in schematic-frame coords inside the same outer `<g>` count as body annotations.
- `<text class="channel-label">` elements remain VALID (they don't break anything) but are no longer REQUIRED. They stay exempt from VR2 (curved-path), VR4 (data-info), and VR7 itself.
- If the legend strip is absent entirely and the schematic has no `<g id="title-block">`, VR7 fails on the very first used wire class with the missing-legend message — that's the right hint.

**Failure messages:**
- `VR7 wire class "<cls>" used in body but missing from title-block legend strip`
- `VR7 net class "<cls>" (expected id "<EXPECTED>") has no annotation text in the schematic body`

---

## VR8 — Text clear-space

**Purpose:** Catches text labels whose bounding box is cut by a nearby wire centerline or pin/junction circle, making the text appear "blocked" in the rendered SVG. Complements VR3 (which only catches text vs `<rect class="comp">`).

**Inputs:**
- Every `<text>` element (`text-anchor` may be `start`/`middle`/`end`)
- Every `<line>` / `<path>` / `<polyline>` (centerlines used as 1-px-thick reference)
- Every `<circle class="pin">` and `<circle class~="j*">` (pin and junction dots)

**Procedure:**

```
PADDING = 5     # SVG units of required clear space

# 1. Compute text bbox
for each <text> T:
    if T.class includes 'channel-label' or T.parent has class 'deco':
        continue  # exempt
    bbox = T.getBBox()                  # post-render; or estimate:
    # estimate fallback when DOM-less:
    #   w = T.textContent.length × T.font-size × 0.55 + 2
    #   h = T.font-size + 2
    #   anchor maps x to bbox.x: start→x, middle→x-w/2, end→x-w
    expanded = expand(bbox, PADDING)    # inflate by 5 px on all sides

# 2. Wire centerline distance
for each wire W not in T's same-group net (compare data-info[0] or shared parent):
    if W is straight (line):
        d = perpendicular distance from any segment of W to expanded bbox
    else if W is path with arcs:
        sample W at 5 px intervals; min distance to expanded bbox
    if d < PADDING:
        FAIL `VR8 text "<T.textContent>" at (T.x, T.y) within ${d}px of wire <W.id>`

# 3. Pin / junction circle distance
for each <circle> C with class in {'pin'} or matching /^j/:
    # exempt if C is anchored to the SAME net the text labels
    if same_net(C, T):
        continue
    d = distance(C.center, expanded bbox) − C.r
    if d < PADDING:
        FAIL `VR8 text "<T.textContent>" within ${d}px of <C.class> at (cx, cy)`
```

**Same-net test** (used to skip "label sits on its own wire" cases, which are valid):
- For a wire W: parse `W.data-info` field 0 (`NET_ID`); compare against the text's nearest annotation. If the text element has `class~="channel-label"`, its NET_ID is the sibling wire's class suffix.
- For a pin/junction `<circle>`: the circle's `data-info[0]` (if present) or the wire's `data-info[0]` it terminates on.
- If the text is inside the same component `<g>` as the pin, treat as same-net.

**Edge cases:**
- `<text>` with `display="none"` or `opacity="0"` — skip (not visible).
- `<text>` inside a transformed sub-group (`<g transform="translate(...) scale(...)">`) — transform its bbox into the parent coordinate frame before comparing to wires/circles in that frame.
- Component labels (`class~="black-text"`, `class~="bold-text"`) inside a component `<g>` — exempt from clearance against wires/pins that belong to the SAME component (same parent `<g id="COMPONENT">`).
- Text "blocked" by 1-px-thick stroke is technically off-the-centerline by the half-width of the stroke; the PADDING=5 buffer absorbs this.

**Failure messages:**
- `VR8 text "<content>" at (x,y) within Npx of wire <id>` (FAIL)
- `VR8 text "<content>" within Npx of <pin|junction-class> at (cx,cy)` (FAIL)

**Common fix:** nudge text baseline 5–8 px away from the nearest blocking element along the orthogonal axis. If horizontal label sits on a horizontal wire, move y by ±6; if it sits on a vertical wire, move x by ±6 (or flip text-anchor).

---

## VR8b — Intra-container text spacing

**Purpose:** Catches stacked text labels inside the same component `<g>` (e.g. title + value pair) whose bounding boxes crowd each other, producing a "mashed" rendering even when no wire is involved. Complements VR8 (which only checks text-vs-wire/pin clearance) and Component Assembler's multi-text container auto-fit rule (in `SKILL.md` Sub-Agent 4) which is the construction-side counterpart.

**Inputs:**
- Every pair of `<text>` nodes sharing a parent `<g>` that are vertically stacked, defined as: **same `text-anchor` AND their `x` attributes within ±4 px of each other**.

**Procedure:**

```
GAP_MIN = 3     # SVG units of minimum bbox-edge-to-bbox-edge clear space

for each parent <g>:
    texts = sort children of type <text> by y
    for i in 0 .. len(texts) − 2:
        T1, T2 = texts[i], texts[i+1]
        if T1.text-anchor != T2.text-anchor: continue
        if abs(T1.x − T2.x) > 4: continue
        bbox1 = inflate(T1.getBBox(), font_size_1 × 1.0 padding)
        bbox2 = inflate(T2.getBBox(), font_size_2 × 1.0 padding)
        gap = bbox2.top − bbox1.bottom
        if gap < GAP_MIN:
            WARN `VR8b stacked texts "<T1.textContent>" / "<T2.textContent>" — gap ${gap}px < ${GAP_MIN}px`
```

**Severity:** **WARN** (designer judgement; not a hard FAIL). The Assembler auto-fit rule should prevent this at build time; VR8b is a safety net for revisions that hand-tune positions.

**Common fix:** increase the parent rect's height by `(GAP_MIN − gap) + 2` and let the Component Assembler's multi-text auto-fit rule redistribute baselines; or apply a font-scale reduction to one of the texts.

**Failure message:** `VR8b stacked texts "<content1>" / "<content2>" in <g id="..."> — gap Npx < 3px` (WARN)

---

## VR9 — Net color follows signal, not voltage

**Inputs:**
- All wire elements and their CSS class (`w12v`, `wdata`, `wdata3`, etc.)
- Working-dir `CLAUDE.md` Wire Assignment Table (if present)

**Procedure:**

```
table = readWireAssignmentTable(cwd + '/CLAUDE.md')   # null if absent
if table is null: return PASS   # VR9 only applies when a table exists

for each wire-shaped element W:
    cls = first class in W.classList matching /^w/
    if cls in ['w12v', 'w5v', 'w3v3', 'wgnd', 'w12v-bus', 'w5v-bus', 'w3v3-bus', 'wgnd-bus']:
        continue   # power rails not governed by assignment table
    if cls not in table:
        FAIL `VR9 wire class "${cls}" not found in Wire Assignment Table`
    # color match is implicit — using the class means using its CSS color token
```

**Edge cases:**
- Power rail classes (`w12v`, `w5v`, `w3v3`, `wgnd`) and their bus variants are excluded — they carry inherent voltage semantics.
- If the working-dir has no `CLAUDE.md` or no "Wire Assignment Table" heading, VR9 returns PASS.
- The always-hot upstream wire (PSU/fuse → MOSFET drain) stays `.w12v` even if the downstream switched net has a `wdata` class.

**Failure message:**
- `VR9 wire class "<cls>" not found in Wire Assignment Table`

---

## VR10 — Arc-hop at every wire crossing

**Inputs:**
- All wire segments (from `<line>`, `<polyline>`, `<path>`) grouped by net class
- All arc-hop paths (class~="arc" or class~="hop") with their bounding boxes

**Procedure:**

```
segments = []
for each wire-shaped element W:
    netClass = first class in W.classList matching /^w/
    for seg in parseSegments(W):
        segments.push({net: netClass, seg: seg, id: W.id})

hops = svg.querySelectorAll('[class~="arc"], [class~="hop"]')
hopBoxes = [h.getBBox() for h in hops]

for each pair (A, B) in segments where A.net != B.net:
    cross = segmentIntersection(A.seg, B.seg)
    if cross is null: continue
    (cx, cy) = cross
    nearby = hopBoxes.filter(box => abs((box.x + box.width/2) - cx) <= 6 and abs((box.y + box.height/2) - cy) <= 6)
    if nearby.length == 0:
        FAIL `VR10 missing arc hop at (${cx}, ${cy}) — nets ${A.net} × ${B.net}`
```

**Edge cases:**
- Segments of the same net crossing each other: no hop required (junction implied or same net branch).
- T-junctions (endpoint touching midpoint of another wire): these are connections, not crossings — no hop required.
- Floating-point coordinates: use ±0.5 tolerance in `segmentIntersection`.
- The validator may emit `CONSULT → Wire Router` for a single auto-fix retry per FAIL.

**Failure message:**
- `VR10 missing arc hop at (x, y) — nets <netA> × <netB>`

---

## Validator invocation flow (informational)

When the Orchestrator invokes Sub-Agent 8:

1. Load full `skeleton.html` (or the assembled output if mid-pipeline).
2. Parse the SVG DOM.
3. Run checks in order: token contract → stroke/dot hierarchies → no-hex → token-name consistency → container-fill → VR1 → VR2 → VR3 → VR4 → VR5 → VR6 → VR7 → VR8 → VR8b → VR9 → VR10.
4. Aggregate PASS / WARN / FAIL.
5. On any FAIL, emit a structured report:
   ```
   FAIL VR<#>: <message>
     at <element-or-coord>
     suggested fix: <one-line hint>
   ```
6. For VR10 only: may emit `CONSULT → Wire Router` for a single auto-fix retry.

This file is the source of truth for step 3 — each rule's algorithm. SKILL.md is the source of truth for which rules exist and what they enforce.
