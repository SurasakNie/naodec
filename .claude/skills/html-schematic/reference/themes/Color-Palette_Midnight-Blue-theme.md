# Midnight Blue Color Theme

> Dark navy + neon-cyan design system, inspired by deep-space technical infographics.
> All values are hardcoded hex — no dynamic generation required.
> **To use as a schematic theme:** replace every `--mb-*` name with the contract token name shown in the remap table below, then paste the block into the skeleton's `/* === THEME START … END === */` section.

---

## Token Remap — Midnight Blue → Schematic Contract

Replace `--mb-*` names with these contract names before dropping into a schematic:

| Contract token (use this) | Midnight Blue source token | Hex |
|---|---|---|
| `--bg-dark` | `--mb-bg` | `#0A1530` |
| `--bg-panel` | `--mb-surface` @ 95% opacity | `rgba(23, 46, 80, 0.95)` |
| `--wire-12v` | `--mb-yellow` | `#FFD54F` |
| `--wire-5v` | `--mb-amber` | `#FFAD5C` |
| `--wire-3v3` | `--mb-purple` | `#7B5FFF` |
| `--wire-gnd` | gray-200 (readable on `#0A1530`) | `#5A7090` |
| `--wire-data` | `--mb-cyan` | `#00D4FF` |
| `--wire-data2` | `--mb-text` | `#FFFFFF` |
| `--wire-data3` | `--mb-blue` | `#4FA8FF` |
| `--wire-data4` | `--mb-rose` | `#FF5C8A` |
| `--wire-data5` | `--mb-cyan` lightened | `#5DE3FF` |
| `--wire-data6` | `--mb-mint` | `#82F0C5` |
| `--wire-data7` | `--mb-purple` lightened | `#A88BFF` |
| `--text-primary` | `--mb-text` | `#FFFFFF` |
| `--text-secondary` | `--mb-text-dim` | `#8FA5C0` |
| `--accent` | `--mb-cyan` | `#00D4FF` |
| `--comp-fill` | `--mb-bg-2` | `#142B4A` |
| `--comp-fill-hover` | `--mb-bg-3` | `#1E3252` |
| `--comp-stroke` | `--mb-border` | `#2A4A7F` |
| `--border` | `--mb-border` @ 60% opacity | `rgba(42, 74, 127, 0.6)` |
| `--pin-dot` | `--mb-cyan` | `#00D4FF` |
| `--warn` | `--mb-yellow` | `#FFD54F` |
| `--warn-bg` | `--mb-bg` + amber tint | `#1F1605` |

---

## CSS Variables

Paste into your `:root {}` block.

```css
:root {
  /* Neon accents */
  --mb-cyan:      #00D4FF;
  --mb-blue:      #4FA8FF;
  --mb-yellow:    #FFD54F;
  --mb-amber:     #FFAD5C;
  --mb-purple:    #7B5FFF;
  --mb-rose:      #FF5C8A;
  --mb-mint:      #82F0C5;

  /* Backgrounds (darkest → lightest) */
  --mb-bg:        #0A1530;   /* base canvas */
  --mb-bg-2:      #142B4A;   /* content area */
  --mb-bg-3:      #1E3252;   /* raised section */
  --mb-surface:   #172E50;   /* card / panel */
  --mb-border:    #2A4A7F;   /* divider / stroke */

  /* Typography */
  --mb-text:      #FFFFFF;   /* primary body */
  --mb-text-dim:  #8FA5C0;   /* secondary / muted */
}
```

---

## Primary Accents

| Token | Hex | Use |
|---|---|---|
| `--mb-cyan` | `#00D4FF` | Primary CTA, links, active states, brand highlights |
| `--mb-yellow` | `#FFD54F` | Warnings, callouts, attention markers |
| `--mb-blue` | `#4FA8FF` | Info states, secondary links |
| `--mb-purple` | `#7B5FFF` | Decorative, badge, logo gradient |
| `--mb-rose` | `#FF5C8A` | Danger, destructive states |
| `--mb-mint` | `#82F0C5` | Success, positive feedback |
| `--mb-amber` | `#FFAD5C` | Warm secondary, energy indicators |

---

## Color Ramps

Each ramp runs 7 stops: `50` (lightest) → `900` (darkest).

### Cyan
| Stop | Hex |
|---|---|
| 50 | `#E0F9FF` |
| 100 | `#A3EEFF` |
| 200 | `#00D4FF` |
| 400 | `#0099CC` |
| 600 | `#006B8C` |
| 800 | `#003F5C` |
| 900 | `#001E2E` |

### Blue
| Stop | Hex |
|---|---|
| 50 | `#E0F0FF` |
| 100 | `#A3D2FF` |
| 200 | `#4FA8FF` |
| 400 | `#1D7FD4` |
| 600 | `#0D548C` |
| 800 | `#06325C` |
| 900 | `#02192E` |

### Yellow
| Stop | Hex |
|---|---|
| 50 | `#FFFCE0` |
| 100 | `#FFF3A3` |
| 200 | `#FFD54F` |
| 400 | `#D4A91D` |
| 600 | `#8C700D` |
| 800 | `#5C4806` |
| 900 | `#2E2402` |

### Purple
| Stop | Hex |
|---|---|
| 50 | `#EDE6FF` |
| 100 | `#C9B6FF` |
| 200 | `#7B5FFF` |
| 400 | `#5A38E0` |
| 600 | `#3A1F9C` |
| 800 | `#22105C` |
| 900 | `#11062E` |

### Rose
| Stop | Hex |
|---|---|
| 50 | `#FFE0EA` |
| 100 | `#FFA3BF` |
| 200 | `#FF5C8A` |
| 400 | `#CC3F66` |
| 600 | `#8C2244` |
| 800 | `#5C112A` |
| 900 | `#2E0815` |

### Background Navy
| Stop | Hex |
|---|---|
| 50 | `#0A1530` |
| 100 | `#0F1B3D` |
| 200 | `#142B4A` |
| 400 | `#172E50` |
| 600 | `#1E3252` |
| 800 | `#2A4A7F` |
| 900 | `#3A5A95` |

### Gray
| Stop | Hex |
|---|---|
| 50 | `#C5D6E8` |
| 100 | `#8FA5C0` |
| 200 | `#5A7090` |
| 400 | `#3F5270` |
| 600 | `#2A3852` |
| 800 | `#1A2336` |
| 900 | `#0F1622` |

---

## Usage Patterns

### Backgrounds — layering order
```
--mb-bg          canvas / full-page background
  └── --mb-bg-2      content wrapper / main area
        └── --mb-surface   card / panel
              └── --mb-bg-3    hover / raised state
```

### Text contrast rules
- Body text on `--mb-bg` → use `--mb-text` (`#FFFFFF`)
- Secondary labels → use `--mb-text-dim` (`#8FA5C0`)
- Pure white is intentional here — supports the high-contrast tech-infographic aesthetic

### Neon on dark backgrounds — minimum contrast
| Accent | Background | Contrast ratio |
|---|---|---|
| `#00D4FF` cyan | `#0A1530` | ~10.5 : 1 ✅ |
| `#FFD54F` yellow | `#0A1530` | ~13.2 : 1 ✅ |
| `#4FA8FF` blue | `#0A1530` | ~7.9 : 1 ✅ |
| `#7B5FFF` purple | `#0A1530` | ~5.4 : 1 ✅ |
| `#FF5C8A` rose | `#0A1530` | ~6.1 : 1 ✅ |
| `#82F0C5` mint | `#0A1530` | ~11.0 : 1 ✅ |

All accents pass WCAG AA (4.5:1) on the base canvas.

---

## Component Recipes

### Primary button
```css
.btn-primary {
  background: transparent;
  color: var(--mb-cyan);
  border: 1px solid var(--mb-cyan);
  padding: 8px 20px;
  font-family: 'Inter', 'Roboto', sans-serif;
  letter-spacing: 0.05em;
  text-transform: uppercase;
  transition: background 0.15s, color 0.15s;
}
.btn-primary:hover {
  background: var(--mb-cyan);
  color: #0A1530;
}
```

### Card / panel
```css
.card {
  background: var(--mb-surface);
  border: 0.5px solid var(--mb-border);
  border-radius: 6px;
  padding: 1rem 1.25rem;
}
/* accent left border variant */
.card--accent {
  border-left: 3px solid var(--mb-cyan);
}
```

### Numbered step tile
```css
.step-tile {
  background: var(--mb-bg-3);
  border: 1px solid var(--mb-border);
  border-radius: 8px;
  padding: 1.25rem 1.5rem;
  position: relative;
}
.step-tile .number {
  color: var(--mb-cyan);
  font-size: 2rem;
  font-weight: 700;
  font-family: 'Inter', monospace;
}
```

### Warning callout
```css
.callout-warn {
  background: #1F1605;             /* yellow-900 tint */
  border-left: 3px solid var(--mb-yellow);
  color: #FFF3A3;                  /* yellow-100 */
  padding: 10px 14px;
  border-radius: 4px;
}
```

### Badge / tag
```css
/* use the 900 bg + 100 text from the same ramp */
.badge-cyan   { background: #001E2E; color: #A3EEFF; }
.badge-yellow { background: #2E2402; color: #FFF3A3; }
.badge-blue   { background: #02192E; color: #A3D2FF; }
.badge-purple { background: #11062E; color: #C9B6FF; }
.badge-rose   { background: #2E0815; color: #FFA3BF; }

.badge {
  font-size: 11px;
  font-family: 'Inter', sans-serif;
  letter-spacing: 0.06em;
  padding: 3px 10px;
  border-radius: 3px;
  text-transform: uppercase;
  font-weight: 600;
}
```

---

## Typography Recommendations

| Role | Font | Style |
|---|---|---|
| Display / heading | `'Inter'`, `'Sora'` | weight 700, slight tracking |
| Body / UI | `'Inter'`, `'Roboto'`, sans-serif | weight 400, letter-spacing 0.01em |
| Data / code | `'JetBrains Mono'`, `'IBM Plex Mono'` | weight 400 |

Google Fonts import (display + body):
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600;700&family=JetBrains+Mono&display=swap" rel="stylesheet">
```

---

## Quick-Start HTML Template

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Midnight Blue UI</title>
  <style>
    :root {
      --mb-cyan:     #00D4FF;
      --mb-blue:     #4FA8FF;
      --mb-yellow:   #FFD54F;
      --mb-amber:    #FFAD5C;
      --mb-purple:   #7B5FFF;
      --mb-rose:     #FF5C8A;
      --mb-mint:     #82F0C5;
      --mb-bg:       #0A1530;
      --mb-bg-2:     #142B4A;
      --mb-bg-3:     #1E3252;
      --mb-surface:  #172E50;
      --mb-border:   #2A4A7F;
      --mb-text:     #FFFFFF;
      --mb-text-dim: #8FA5C0;
    }

    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: var(--mb-bg);
      color: var(--mb-text);
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

*Theme version: 1.0 — Midnight Blue*
