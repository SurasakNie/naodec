# Mosaic Pastel Color Theme

> **Light-canvas theme** — soft warm pastels with sky-blue and lime accents.
> Inspired by diamond/rhombus mosaic infographic templates. Friendly, approachable, business-casual.
> **To use as a schematic theme:** replace every `--mp-*` name with the contract token name shown in the remap table below, then paste the block into the skeleton's `/* === THEME START … END === */` section.

> ⚠️ **Light-theme caveat:** the schematic contract token `--bg-dark` is set to near-white. Wire and text colors are *darker* saturated values (not white) so they remain readable. If you forget to swap `--wire-data2` away from pure white, that wire will be invisible.

---

## Token Remap — Mosaic Pastel → Schematic Contract

Replace `--mp-*` names with these contract names before dropping into a schematic:

| Contract token (use this) | Mosaic Pastel source token | Hex |
|---|---|---|
| `--bg-dark` | `--mp-bg` *(near-white)* | `#FFFFFF` |
| `--bg-panel` | `--mp-surface` @ 95% opacity | `rgba(250, 250, 250, 0.95)` |
| `--wire-12v` | `--mp-orange` 600-stop (3:1 min) | `#A05D14` |
| `--wire-5v` | `--mp-cream` (saturated for stroke) | `#E8B560` |
| `--wire-3v3` | `--mp-coral` | `#E85D5D` |
| `--wire-gnd` | warm taupe gray (readable on white) | `#8A8278` |
| `--wire-data` | `--mp-blue` 600-stop (3:1 min) | `#3A75A8` |
| `--wire-data2` | `--mp-text` (dark, **not** white) | `#4A5258` |
| `--wire-data3` | `--mp-powder` (darker for contrast) | `#5A9BCC` |
| `--wire-data4` | `--mp-pink` | `#F47676` |
| `--wire-data5` | `--mp-lime` 600-stop (3:1 min) | `#52852A` |
| `--wire-data6` | `--mp-peach` (saturated) | `#E8A06A` |
| `--wire-data7` | `--mp-lime` darkened | `#7BB84A` |
| `--text-primary` | `--mp-text` | `#4A5258` |
| `--text-secondary` | `--mp-text-dim` | `#7A8290` |
| `--accent` | `--mp-orange` | `#F2A555` |
| `--comp-fill` | `--mp-surface` | `#FAFAFA` |
| `--comp-fill-hover` | `--mp-bg-2` | `#F8F5F0` |
| `--comp-stroke` | `--mp-border` | `#D4DAE0` |
| `--border` | `--mp-border` @ 60% opacity | `rgba(212, 218, 224, 0.6)` |
| `--pin-dot` | `--mp-orange` | `#F2A555` |
| `--warn` | `--mp-coral` | `#E85D5D` |
| `--warn-bg` | light coral wash | `#FDE8E8` |

---

## CSS Variables

Paste into your `:root {}` block.

```css
:root {
  /* Mosaic tile accents (pastel tones) */
  --mp-coral:     #E85D5D;   /* deep coral red */
  --mp-pink:      #F47676;   /* soft pink */
  --mp-orange:    #F2A555;   /* warm orange */
  --mp-peach:     #F9D5A8;   /* peach pastel */
  --mp-cream:     #FFE5B8;   /* cream / warm yellow */
  --mp-blue:      #6FB8E8;   /* sky blue */
  --mp-powder:    #B8DEF0;   /* powder blue */
  --mp-lime:      #A8DC6F;   /* lime green */

  /* Backgrounds (lightest → darkest) */
  --mp-bg:        #FFFFFF;   /* base canvas — pure white */
  --mp-bg-2:      #F8F5F0;   /* warm off-white */
  --mp-surface:   #FAFAFA;   /* card / panel */
  --mp-border:    #D4DAE0;   /* divider / stroke */

  /* Typography (dark on light) */
  --mp-text:      #4A5258;   /* primary body — soft slate */
  --mp-text-dim:  #7A8290;   /* secondary / muted */
}
```

---

## Primary Accents

| Token | Hex | Use | Source tile |
|---|---|---|---|
| `--mp-coral` | `#E85D5D` | Strong accent, CTAs, error states | top-left corner |
| `--mp-pink` | `#F47676` | Soft accent, hover, decorative | adjacent pink tile |
| `--mp-orange` | `#F2A555` | Primary brand, callouts | center orange |
| `--mp-peach` | `#F9D5A8` | Soft warm background fill | peach pastel band |
| `--mp-cream` | `#FFE5B8` | Highlight band, soft alerts | cream tile |
| `--mp-blue` | `#6FB8E8` | Info, links, secondary brand | sky-blue tile |
| `--mp-powder` | `#B8DEF0` | Subtle info wash | powder tile |
| `--mp-lime` | `#A8DC6F` | Success, positive accent | lime tile |

---

## Color Ramps

Each ramp runs 7 stops: `50` (lightest) → `900` (darkest).

### Coral / Pink
| Stop | Hex |
|---|---|
| 50 | `#FDE8E8` |
| 100 | `#FBCACA` |
| 200 | `#F47676` |
| 400 | `#E85D5D` |
| 600 | `#B83838` |
| 800 | `#7A2020` |
| 900 | `#3D1010` |

### Orange / Peach
| Stop | Hex |
|---|---|
| 50 | `#FFF4E5` |
| 100 | `#F9D5A8` |
| 200 | `#F2A555` |
| 400 | `#D88532` |
| 600 | `#A05D14` |
| 800 | `#683B08` |
| 900 | `#341D04` |

### Cream / Yellow
| Stop | Hex |
|---|---|
| 50 | `#FFFAEF` |
| 100 | `#FFE5B8` |
| 200 | `#FACE7A` |
| 400 | `#E8B560` |
| 600 | `#A88130` |
| 800 | `#6E521A` |
| 900 | `#37290D` |

### Blue
| Stop | Hex |
|---|---|
| 50 | `#EAF6FC` |
| 100 | `#B8DEF0` |
| 200 | `#6FB8E8` |
| 400 | `#5A9BCC` |
| 600 | `#3A75A8` |
| 800 | `#1E4D75` |
| 900 | `#0F273B` |

### Lime
| Stop | Hex |
|---|---|
| 50 | `#F0FAE2` |
| 100 | `#D5EFAE` |
| 200 | `#A8DC6F` |
| 400 | `#7BB84A` |
| 600 | `#52852A` |
| 800 | `#345417` |
| 900 | `#1A2A0B` |

### Neutral (background / grays)
| Stop | Hex |
|---|---|
| 50 | `#FFFFFF` |
| 100 | `#FAFAFA` |
| 200 | `#F8F5F0` |
| 400 | `#E5E8EB` |
| 600 | `#D4DAE0` |
| 800 | `#7A8290` |
| 900 | `#4A5258` |

---

## Usage Patterns

### Backgrounds — layering order (light theme)
```
--mp-bg          page canvas (#FFFFFF)
  └── --mp-surface   card / panel (#FAFAFA)
        └── --mp-bg-2    warm off-white / hover (#F8F5F0)
```

### Text contrast rules
- Body text on `--mp-bg` → use `--mp-text` (`#4A5258`) — soft slate, easier on the eye than pure black
- Secondary labels → use `--mp-text-dim` (`#7A8290`)
- On colored tile backgrounds → drop to white `#FFFFFF` or use the matching ramp-600 stop
- Never use `--mp-text` on coral/orange backgrounds — drop to white instead

### Accent contrast on white background (#FFFFFF)
| Accent | Contrast ratio | Verdict |
|---|---|---|
| `#E85D5D` coral | ~4.0 : 1 | ⚠️ UI only, not body text |
| `#F47676` pink | ~3.4 : 1 | ⚠️ decorative only |
| `#F2A555` orange 200 | ~2.0 : 1 | ❌ tile/decorative only — use `#A05D14` (600) for wires |
| `#A05D14` orange 600 | ~5.2 : 1 | ✅ use for `--wire-12v` |
| `#6FB8E8` blue 200 | ~2.2 : 1 | ❌ tile/decorative only — use `#3A75A8` (600) for wires |
| `#5A9BCC` blue 400 | ~3.0 : 1 | ✅ use for `--wire-data3` |
| `#3A75A8` blue 600 | ~4.9 : 1 | ✅ use for `--wire-data` |
| `#A8DC6F` lime 200 | ~1.6 : 1 | ❌ tile/decorative only — use `#52852A` (600) for wires |
| `#7BB84A` lime 400 | ~2.4 : 1 | ⚠️ use for `--wire-data7` only (stroke-only, close to 3:1 threshold) |
| `#52852A` lime 600 | ~4.4 : 1 | ✅ use for `--wire-data5` |
| `#4A5258` text | ~8.9 : 1 | ✅ ✅ |
| `#7A8290` dim text | ~4.7 : 1 | ✅ |

For schematic wires, use 600-stop variants. The 200-stop pastels are tile/decorative elements, not wire colors.

---

## Component Recipes

### Mosaic tile (signature element)
```css
.tile {
  aspect-ratio: 1;
  background: var(--mp-orange);
  color: var(--mp-text);
  padding: 1.25rem;
  transform: rotate(45deg);
  position: relative;
  box-shadow: 2px 2px 8px rgba(0, 0, 0, 0.08);
}
.tile .inner {
  transform: rotate(-45deg);
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 100%;
}
.tile .number {
  font-family: 'Open Sans', sans-serif;
  font-size: 2rem;
  font-weight: 300;
  color: var(--mp-text);
}
.tile .label {
  font-size: 11px;
  letter-spacing: 0.15em;
  text-transform: uppercase;
  color: var(--mp-text-dim);
}
```

### Primary button
```css
.btn-primary {
  background: var(--mp-orange);
  color: #FFFFFF;
  border: none;
  padding: 10px 24px;
  font-family: 'Open Sans', 'Inter', sans-serif;
  font-weight: 600;
  border-radius: 4px;
  box-shadow: 0 2px 6px rgba(242, 165, 85, 0.3);
  transition: transform 0.15s, box-shadow 0.15s;
}
.btn-primary:hover {
  transform: translateY(-1px);
  box-shadow: 0 4px 12px rgba(242, 165, 85, 0.4);
}
```

### Card / panel
```css
.card {
  background: var(--mp-surface);
  border: 1px solid var(--mp-border);
  border-radius: 8px;
  padding: 1.25rem 1.5rem;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.04);
}
.card--accent {
  border-top: 3px solid var(--mp-orange);
}
```

### Stat tile (number + label)
```css
.stat-tile {
  padding: 1.5rem;
  text-align: center;
  background: var(--mp-bg);
  border: 1px solid var(--mp-border);
  border-radius: 6px;
}
.stat-tile .number {
  font-family: 'Open Sans', sans-serif;
  font-size: 2.5rem;
  font-weight: 300;
  color: var(--mp-text);
  line-height: 1;
}
.stat-tile .label {
  font-size: 11px;
  letter-spacing: 0.18em;
  text-transform: uppercase;
  color: var(--mp-text-dim);
  margin-top: 0.5rem;
}
```

### Soft callout
```css
.callout-info {
  background: #EAF6FC;                /* blue-50 */
  border-left: 3px solid var(--mp-blue);
  color: #1E4D75;                     /* blue-800 */
  padding: 12px 16px;
  border-radius: 4px;
}
.callout-success {
  background: #F0FAE2;                /* lime-50 */
  border-left: 3px solid var(--mp-lime);
  color: #345417;                     /* lime-800 */
  padding: 12px 16px;
  border-radius: 4px;
}
```

### Badge / tag
```css
/* light theme: 50 bg + 600 text from each ramp */
.badge-coral  { background: #FDE8E8; color: #B83838; }
.badge-orange { background: #FFF4E5; color: #A05D14; }
.badge-cream  { background: #FFFAEF; color: #A88130; }
.badge-blue   { background: #EAF6FC; color: #3A75A8; }
.badge-lime   { background: #F0FAE2; color: #52852A; }

.badge {
  font-size: 10px;
  font-family: 'Open Sans', sans-serif;
  letter-spacing: 0.1em;
  padding: 3px 10px;
  border-radius: 12px;
  text-transform: uppercase;
  font-weight: 600;
}
```

---

## Typography Recommendations

| Role | Font | Style |
|---|---|---|
| Display / heading | `'Open Sans'`, `'Lato'` | weight 300, generous tracking |
| Body / UI | `'Open Sans'`, `'Inter'`, sans-serif | weight 400, color `--mp-text` |
| Label / caption | `'Open Sans'` | weight 600, uppercase, letter-spacing 0.15em |
| Data / code | `'Source Code Pro'`, `'JetBrains Mono'` | weight 400 |

The pastel aesthetic benefits from **lighter font weights** — avoid heavy 800/900 displays. Light/Regular keeps it airy.

Google Fonts import:
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Open+Sans:wght@300;400;600&display=swap" rel="stylesheet">
```

---

## Quick-Start HTML Template

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Mosaic Pastel UI</title>
  <style>
    :root {
      --mp-coral:    #E85D5D;
      --mp-pink:     #F47676;
      --mp-orange:   #F2A555;
      --mp-peach:    #F9D5A8;
      --mp-cream:    #FFE5B8;
      --mp-blue:     #6FB8E8;
      --mp-powder:   #B8DEF0;
      --mp-lime:     #A8DC6F;
      --mp-bg:       #FFFFFF;
      --mp-bg-2:     #F8F5F0;
      --mp-surface:  #FAFAFA;
      --mp-border:   #D4DAE0;
      --mp-text:     #4A5258;
      --mp-text-dim: #7A8290;
    }

    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: var(--mp-bg);
      color: var(--mp-text);
      font-family: 'Open Sans', 'Inter', sans-serif;
      font-weight: 400;
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

*Theme version: 1.0 — Mosaic Pastel (light-canvas theme)*
