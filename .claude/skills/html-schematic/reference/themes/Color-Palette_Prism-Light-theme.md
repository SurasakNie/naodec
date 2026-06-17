# Prism Light Color Theme

> **Light-canvas theme** — first non-dark palette in the library.
> Crisp white background with rainbow-gradient ribbon accents. Modern business / corporate-infographic aesthetic. High clarity, friendly.
> **To use as a schematic theme:** replace every `--pl-*` name with the contract token name shown in the remap table below, then paste the block into the skeleton's `/* === THEME START … END === */` section.

> ⚠️ **Light-theme caveat:** the schematic contract token `--bg-dark` is set to a near-white value here. Wire and text colors are *darker* saturated values (not white) so they remain readable on the light canvas. If you forget to swap `--wire-data2` away from pure white, that wire will be invisible.

---

## Token Remap — Prism Light → Schematic Contract

Replace `--pl-*` names with these contract names before dropping into a schematic:

| Contract token (use this) | Prism Light source token | Hex |
|---|---|---|
| `--bg-dark` | `--pl-bg` *(actually a near-white)* | `#FAFAFA` |
| `--bg-panel` | `--pl-surface` @ 95% opacity | `rgba(245, 245, 247, 0.95)` |
| `--wire-12v` | `--pl-orange` | `#F57C00` |
| `--wire-5v` | `--pl-yellow` | `#FBC02D` |
| `--wire-3v3` | `--pl-red` | `#E64A19` |
| `--wire-gnd` | neutral gray (readable on white) | `#757575` |
| `--wire-data` | `--pl-blue` | `#0288D1` |
| `--wire-data2` | `--pl-text` (dark, **not** white) | `#212121` |
| `--wire-data3` | `--pl-cyan` | `#29B6F6` |
| `--wire-data4` | `--pl-pink` | `#EC407A` |
| `--wire-data5` | `--pl-purple` | `#7E57C2` |
| `--wire-data6` | `--pl-teal` | `#00897B` |
| `--wire-data7` | `--pl-lime` 400-stop (3:1 min) | `#43A047` |
| `--text-primary` | `--pl-text` | `#212121` |
| `--text-secondary` | `--pl-text-dim` | `#616161` |
| `--accent` | `--pl-orange` | `#F57C00` |
| `--comp-fill` | `--pl-surface` | `#F5F5F7` |
| `--comp-fill-hover` | `--pl-bg-2` | `#EEEEEE` |
| `--comp-stroke` | `--pl-border` | `#BDBDBD` |
| `--border` | `--pl-border` @ 60% opacity | `rgba(189, 189, 189, 0.6)` |
| `--pin-dot` | `--pl-orange` | `#F57C00` |
| `--warn` | `--pl-red` | `#E64A19` |
| `--warn-bg` | light red wash | `#FFEBEE` |

---

## CSS Variables

Paste into your `:root {}` block.

```css
:root {
  /* Prism accents (vibrant, saturated for light canvas) */
  --pl-yellow:    #FBC02D;
  --pl-orange:    #F57C00;
  --pl-red:       #E64A19;
  --pl-pink:      #EC407A;
  --pl-magenta:   #C2185B;
  --pl-cyan:      #29B6F6;
  --pl-blue:      #0288D1;
  --pl-purple:    #7E57C2;
  --pl-indigo:    #5E35B1;
  --pl-teal:      #00897B;
  --pl-lime:      #66BB6A;

  /* Backgrounds (lightest → darkest) */
  --pl-bg:        #FAFAFA;   /* base canvas */
  --pl-bg-2:      #EEEEEE;   /* content area / hover */
  --pl-surface:   #F5F5F7;   /* card / panel */
  --pl-border:    #BDBDBD;   /* divider / stroke */

  /* Typography (dark on light) */
  --pl-text:      #212121;   /* primary body */
  --pl-text-dim:  #616161;   /* secondary / muted */
}
```

---

## Primary Accents

| Token | Hex | Use | Step in source |
|---|---|---|---|
| `--pl-yellow` | `#FBC02D` | Highlights, attention | Step 01 (top) |
| `--pl-orange` | `#F57C00` | Primary CTA, brand | Step 02 |
| `--pl-pink` | `#EC407A` | Energetic accent | Step 03 |
| `--pl-blue` | `#0288D1` | Info, links | Step 04 |
| `--pl-cyan` | `#29B6F6` | Secondary info | Step 04 (top) |
| `--pl-purple` | `#7E57C2` | Decorative | Step 05 |
| `--pl-indigo` | `#5E35B1` | Decorative dark | Step 05 (bottom) |
| `--pl-teal` | `#00897B` | Success, fresh | Step 06 |
| `--pl-lime` | `#66BB6A` | Positive, success | Step 07 |
| `--pl-red` | `#E64A19` | Danger, alerts | Step 02 (bottom) |
| `--pl-magenta` | `#C2185B` | Brand-deep accent | Step 03 (bottom) |

---

## Color Ramps

Each ramp runs 7 stops: `50` (lightest) → `900` (darkest).

### Yellow → Orange
| Stop | Hex |
|---|---|
| 50 | `#FFFDE7` |
| 100 | `#FFF59D` |
| 200 | `#FBC02D` |
| 400 | `#F57C00` |
| 600 | `#E65100` |
| 800 | `#8C3000` |
| 900 | `#451800` |

### Pink → Magenta
| Stop | Hex |
|---|---|
| 50 | `#FCE4EC` |
| 100 | `#F8BBD0` |
| 200 | `#EC407A` |
| 400 | `#C2185B` |
| 600 | `#8A0F40` |
| 800 | `#5A0828` |
| 900 | `#2D0414` |

### Cyan → Blue
| Stop | Hex |
|---|---|
| 50 | `#E1F5FE` |
| 100 | `#B3E5FC` |
| 200 | `#29B6F6` |
| 400 | `#0288D1` |
| 600 | `#01579B` |
| 800 | `#003366` |
| 900 | `#001A33` |

### Purple → Indigo
| Stop | Hex |
|---|---|
| 50 | `#EDE7F6` |
| 100 | `#D1C4E9` |
| 200 | `#7E57C2` |
| 400 | `#5E35B1` |
| 600 | `#3F1F8C` |
| 800 | `#26115A` |
| 900 | `#13082D` |

### Teal → Lime
| Stop | Hex |
|---|---|
| 50 | `#E0F2F1` |
| 100 | `#B2DFDB` |
| 200 | `#00897B` |
| 400 | `#43A047` |
| 600 | `#2E7D32` |
| 800 | `#1B5E20` |
| 900 | `#0D2E10` |

### Neutral (background / grays)
| Stop | Hex |
|---|---|
| 50 | `#FFFFFF` |
| 100 | `#FAFAFA` |
| 200 | `#F5F5F7` |
| 400 | `#EEEEEE` |
| 600 | `#BDBDBD` |
| 800 | `#616161` |
| 900 | `#212121` |

---

## Usage Patterns

### Backgrounds — layering order (light theme)
```
--pl-bg          page canvas (#FAFAFA)
  └── --pl-surface   card / panel (#F5F5F7)
        └── --pl-bg-2    hover / raised (#EEEEEE)
```

### Text contrast rules
- Body text on `--pl-bg` → use `--pl-text` (`#212121`) — **dark text on light**
- Secondary labels → use `--pl-text-dim` (`#616161`)
- Step-ribbon text (on saturated accents) → use white `#FFFFFF`
- Never use `--pl-text` on saturated colored backgrounds — drop to white instead

### Accent contrast on white background (#FAFAFA)
| Accent | Contrast ratio |
|---|---|
| `#F57C00` orange | ~3.4 : 1 ⚠️ (UI only, not body text) |
| `#E64A19` red | ~5.2 : 1 ✅ |
| `#EC407A` pink | ~4.0 : 1 ⚠️ (UI only) |
| `#0288D1` blue | ~5.0 : 1 ✅ |
| `#7E57C2` purple | ~5.2 : 1 ✅ |
| `#00897B` teal | ~4.5 : 1 ✅ |
| `#66BB6A` lime 200 | ~2.3 : 1 ❌ decorative only — use `#43A047` (400) for wires |
| `#43A047` lime 400 | ~3.2 : 1 ✅ use for `--wire-data7` |
| `#212121` text | ~16 : 1 ✅✅ |
| `#616161` dim text | ~6.9 : 1 ✅ |

For accent text on white, prefer the 400/600 stops from each ramp. The 200 stops are decorative.

---

## Component Recipes

### Step ribbon (signature element)
```css
.step-ribbon {
  background: linear-gradient(180deg, var(--pl-yellow) 0%, var(--pl-orange) 100%);
  color: #FFFFFF;
  padding: 1.5rem 2rem;
  clip-path: polygon(0 0, 100% 0, 100% 100%, 50% 92%, 0 100%);
  font-family: 'Montserrat', 'Poppins', sans-serif;
}
.step-ribbon .step-num {
  font-size: 2.5rem;
  font-weight: 800;
}
```

### Primary button
```css
.btn-primary {
  background: var(--pl-orange);
  color: #FFFFFF;
  border: none;
  padding: 10px 22px;
  font-family: 'Montserrat', sans-serif;
  font-weight: 600;
  letter-spacing: 0.04em;
  border-radius: 6px;
  transition: background 0.15s, box-shadow 0.15s;
}
.btn-primary:hover {
  background: #E65100;       /* orange-600 */
  box-shadow: 0 4px 14px rgba(245, 124, 0, 0.35);
}
```

### Card / panel
```css
.card {
  background: var(--pl-surface);
  border: 1px solid var(--pl-border);
  border-radius: 8px;
  padding: 1.25rem 1.5rem;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.06);
}
.card--accent {
  border-top: 4px solid var(--pl-orange);
}
```

### Icon badge (circular)
```css
.icon-badge {
  width: 56px;
  height: 56px;
  border-radius: 50%;
  background: var(--pl-orange);
  color: #FFFFFF;
  display: flex;
  align-items: center;
  justify-content: center;
  box-shadow: 0 4px 12px rgba(245, 124, 0, 0.3);
}
```

### Info callout
```css
.callout-info {
  background: #E1F5FE;                /* blue-50 */
  border-left: 4px solid var(--pl-blue);
  color: #01579B;                     /* blue-600 */
  padding: 12px 16px;
  border-radius: 4px;
}
```

### Badge / tag
```css
/* light theme: light bg from ramp 50 + dark text from ramp 600 */
.badge-orange { background: #FFFDE7; color: #E65100; }
.badge-pink   { background: #FCE4EC; color: #8A0F40; }
.badge-blue   { background: #E1F5FE; color: #01579B; }
.badge-purple { background: #EDE7F6; color: #3F1F8C; }
.badge-teal   { background: #E0F2F1; color: #2E7D32; }

.badge {
  font-size: 11px;
  font-family: 'Montserrat', sans-serif;
  letter-spacing: 0.06em;
  padding: 3px 10px;
  border-radius: 3px;
  text-transform: uppercase;
  font-weight: 700;
}
```

---

## Typography Recommendations

| Role | Font | Style |
|---|---|---|
| Display / heading | `'Montserrat'`, `'Poppins'` | weight 700–800, tight letter-spacing |
| Body / UI | `'Inter'`, `'Roboto'`, sans-serif | weight 400, color `--pl-text` |
| Numbers / step labels | `'Montserrat'` | weight 800, all-caps for "STEP" labels |
| Data / code | `'JetBrains Mono'`, `'IBM Plex Mono'` | weight 400 |

Google Fonts import:
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@400;700;800&family=Inter:wght@400;600&display=swap" rel="stylesheet">
```

---

## Quick-Start HTML Template

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Prism Light UI</title>
  <style>
    :root {
      --pl-yellow:   #FBC02D;
      --pl-orange:   #F57C00;
      --pl-red:      #E64A19;
      --pl-pink:     #EC407A;
      --pl-magenta:  #C2185B;
      --pl-cyan:     #29B6F6;
      --pl-blue:     #0288D1;
      --pl-purple:   #7E57C2;
      --pl-indigo:   #5E35B1;
      --pl-teal:     #00897B;
      --pl-lime:     #66BB6A;
      --pl-bg:       #FAFAFA;
      --pl-bg-2:     #EEEEEE;
      --pl-surface:  #F5F5F7;
      --pl-border:   #BDBDBD;
      --pl-text:     #212121;
      --pl-text-dim: #616161;
    }

    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: var(--pl-bg);
      color: var(--pl-text);
      font-family: 'Inter', 'Roboto', sans-serif;
      min-height: 100vh;
    }
  </style>
</head>
<body>
  <!-- your content here -->
</body>
</html>
```

---

*Theme version: 1.0 — Prism Light (first light-canvas theme)*
