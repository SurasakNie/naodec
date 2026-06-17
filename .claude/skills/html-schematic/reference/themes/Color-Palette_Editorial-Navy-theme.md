# Editorial Navy Color Theme

> Deep editorial navy with gold + coral analytical accents. Magazine / business-report aesthetic — sophisticated, data-dense, high-contrast.
> Inspired by Bloomberg/Quartz-style infographics.
> **To use as a schematic theme:** replace every `--en-*` name with the contract token name shown in the remap table below, then paste the block into the skeleton's `/* === THEME START … END === */` section.

---

## Token Remap — Editorial Navy → Schematic Contract

Replace `--en-*` names with these contract names before dropping into a schematic:

| Contract token (use this) | Editorial Navy source token | Hex |
|---|---|---|
| `--bg-dark` | `--en-bg` | `#0F1F3A` |
| `--bg-panel` | `--en-surface` @ 95% opacity | `rgba(31, 48, 80, 0.95)` |
| `--wire-12v` | `--en-yellow` | `#F5C842` |
| `--wire-5v` | `--en-coral` | `#E94B3C` |
| `--wire-3v3` | `--en-amber` | `#D89148` |
| `--wire-gnd` | `--en-steel` | `#6B8FA0` |
| `--wire-data` | `--en-powder` | `#B5D4E8` |
| `--wire-data2` | `--en-text` | `#FFFFFF` |
| `--wire-data3` | `--en-blue` | `#5BA3D9` |
| `--wire-data4` | `--en-coral` lightened | `#F47A6E` |
| `--wire-data5` | `--en-yellow` lightened | `#F7DA82` |
| `--wire-data6` | `--en-steel` lightened | `#8FA8BD` |
| `--wire-data7` | `--en-beige` | `#E3C9A0` |
| `--text-primary` | `--en-text` | `#FFFFFF` |
| `--text-secondary` | `--en-text-dim` | `#B5C5D8` |
| `--accent` | `--en-yellow` | `#F5C842` |
| `--comp-fill` | `--en-bg-2` | `#1A2D4F` |
| `--comp-fill-hover` | `--en-bg-3` | `#243C66` |
| `--comp-stroke` | `--en-border` | `#3A4F75` |
| `--border` | `--en-border` @ 60% opacity | `rgba(58, 79, 117, 0.6)` |
| `--pin-dot` | `--en-yellow` | `#F5C842` |
| `--warn` | `--en-coral` | `#E94B3C` |
| `--warn-bg` | dark coral tint | `#2E0F0A` |

---

## CSS Variables

Paste into your `:root {}` block.

```css
:root {
  /* Editorial accents */
  --en-yellow:    #F5C842;   /* primary gold ring */
  --en-coral:     #E94B3C;   /* signature donut color */
  --en-amber:     #D89148;   /* warm secondary */
  --en-powder:    #B5D4E8;   /* light data bars */
  --en-blue:      #5BA3D9;   /* mid-blue accent */
  --en-steel:     #6B8FA0;   /* muted chart fill */
  --en-beige:     #E3C9A0;   /* warm neutral accent */

  /* Backgrounds (darkest → lightest) */
  --en-bg:        #0F1F3A;   /* base canvas — editorial navy */
  --en-bg-2:      #1A2D4F;   /* content area */
  --en-bg-3:      #243C66;   /* raised section */
  --en-surface:   #1F3050;   /* card / panel */
  --en-border:    #3A4F75;   /* divider / stroke */

  /* Typography */
  --en-text:      #FFFFFF;   /* primary body */
  --en-text-dim:  #B5C5D8;   /* secondary / muted */
}
```

---

## Primary Accents

| Token | Hex | Use |
|---|---|---|
| `--en-yellow` | `#F5C842` | Hero stat, primary callouts, key data |
| `--en-coral` | `#E94B3C` | Alerts, highlight stats (e.g. "80%"), CTAs |
| `--en-powder` | `#B5D4E8` | Data bars, secondary chart fill |
| `--en-blue` | `#5BA3D9` | Info, links, mid-tier data |
| `--en-steel` | `#6B8FA0` | Neutral chart segments, muted bars |
| `--en-amber` | `#D89148` | Warm secondary, tertiary data |
| `--en-beige` | `#E3C9A0` | Soft warm accent |

---

## Color Ramps

Each ramp runs 7 stops: `50` (lightest) → `900` (darkest).

### Yellow (Gold)
| Stop | Hex |
|---|---|
| 50 | `#FFFAE0` |
| 100 | `#FFEDA3` |
| 200 | `#F5C842` |
| 400 | `#C49E1D` |
| 600 | `#8A6F0D` |
| 800 | `#594806` |
| 900 | `#2D2402` |

### Coral
| Stop | Hex |
|---|---|
| 50 | `#FCE3E0` |
| 100 | `#F7AAA3` |
| 200 | `#E94B3C` |
| 400 | `#BF2D20` |
| 600 | `#8A1A11` |
| 800 | `#5A0E08` |
| 900 | `#2D0704` |

### Powder Blue
| Stop | Hex |
|---|---|
| 50 | `#F0F8FC` |
| 100 | `#D9EBF5` |
| 200 | `#B5D4E8` |
| 400 | `#5BA3D9` |
| 600 | `#3A78A8` |
| 800 | `#1F4E70` |
| 900 | `#0F2738` |

### Steel
| Stop | Hex |
|---|---|
| 50 | `#E8EEF2` |
| 100 | `#C5D2DB` |
| 200 | `#8FA8BD` |
| 400 | `#6B8FA0` |
| 600 | `#496978` |
| 800 | `#2D434E` |
| 900 | `#162127` |

### Amber
| Stop | Hex |
|---|---|
| 50 | `#FBF1E0` |
| 100 | `#F2D7A3` |
| 200 | `#D89148` |
| 400 | `#B07125` |
| 600 | `#7A4D0E` |
| 800 | `#4F3008` |
| 900 | `#281804` |

### Navy (background)
| Stop | Hex |
|---|---|
| 50 | `#0F1F3A` |
| 100 | `#142745` |
| 200 | `#1A2D4F` |
| 400 | `#1F3050` |
| 600 | `#243C66` |
| 800 | `#3A4F75` |
| 900 | `#5A6F95` |

---

## Usage Patterns

### Backgrounds — layering order
```
--en-bg          canvas / full-page background
  └── --en-bg-2      content wrapper / main area
        └── --en-surface   card / panel
              └── --en-bg-3    hover / raised state
```

### Text contrast rules
- Body text on `--en-bg` → use `--en-text` (`#FFFFFF`)
- Secondary labels / captions → use `--en-text-dim` (`#B5C5D8`)
- Stat percentages on coral/yellow circles → use white or navy depending on accent saturation
- Big display numerals (e.g. "80%") work best in white on coral, or coral on navy

### Accent contrast on dark navy background
| Accent | Background | Contrast ratio |
|---|---|---|
| `#F5C842` yellow | `#0F1F3A` | ~10.8 : 1 ✅ |
| `#E94B3C` coral | `#0F1F3A` | ~5.0 : 1 ✅ |
| `#B5D4E8` powder | `#0F1F3A` | ~10.1 : 1 ✅ |
| `#5BA3D9` blue | `#0F1F3A` | ~6.4 : 1 ✅ |
| `#6B8FA0` steel | `#0F1F3A` | ~4.6 : 1 ✅ |
| `#D89148` amber | `#0F1F3A` | ~6.3 : 1 ✅ |
| `#E3C9A0` beige | `#0F1F3A` | ~9.4 : 1 ✅ |

All accents pass WCAG AA (4.5:1) on the base navy canvas.

---

## Component Recipes

### Stat donut (signature element)
```css
.stat-donut {
  width: 160px;
  height: 160px;
  border-radius: 50%;
  border: 12px solid var(--en-coral);
  display: flex;
  align-items: center;
  justify-content: center;
  background: var(--en-bg);
  color: #FFFFFF;
  font-family: 'Georgia', 'Playfair Display', serif;
}
.stat-donut .number {
  font-size: 2.5rem;
  font-weight: 700;
  letter-spacing: -0.02em;
}
```

### Primary button
```css
.btn-primary {
  background: var(--en-yellow);
  color: var(--en-bg);
  border: none;
  padding: 10px 22px;
  font-family: 'Inter', sans-serif;
  font-weight: 700;
  letter-spacing: 0.05em;
  text-transform: uppercase;
  border-radius: 2px;
  transition: background 0.15s;
}
.btn-primary:hover {
  background: #FFEDA3;       /* yellow-100 */
}
```

### Card / panel
```css
.card {
  background: var(--en-surface);
  border: 1px solid var(--en-border);
  border-radius: 4px;
  padding: 1.25rem 1.5rem;
}
.card--accent {
  border-left: 3px solid var(--en-yellow);
}
```

### Horizontal bar (data chart)
```css
.bar-row {
  display: flex;
  align-items: center;
  gap: 12px;
  margin-bottom: 8px;
}
.bar-row .bar {
  height: 22px;
  background: var(--en-powder);
  color: var(--en-bg);
  font-family: 'Inter', sans-serif;
  font-weight: 700;
  font-size: 12px;
  padding: 0 10px;
  display: flex;
  align-items: center;
}
.bar-row .bar--accent { background: var(--en-yellow); }
.bar-row .bar--alert  { background: var(--en-coral); color: #FFFFFF; }
```

### Editorial pull-quote / display number
```css
.display-stat {
  font-family: 'Playfair Display', 'Georgia', serif;
  font-size: 5rem;
  font-weight: 900;
  color: var(--en-coral);
  line-height: 1;
  letter-spacing: -0.03em;
}
```

### Badge / tag
```css
/* use the 900 bg + 100 text from the same ramp */
.badge-yellow { background: #2D2402; color: #FFEDA3; }
.badge-coral  { background: #2D0704; color: #F7AAA3; }
.badge-blue   { background: #0F2738; color: #D9EBF5; }
.badge-steel  { background: #162127; color: #C5D2DB; }
.badge-amber  { background: #281804; color: #F2D7A3; }

.badge {
  font-size: 11px;
  font-family: 'Inter', sans-serif;
  letter-spacing: 0.08em;
  padding: 3px 10px;
  border-radius: 2px;
  text-transform: uppercase;
  font-weight: 700;
}
```

---

## Typography Recommendations

| Role | Font | Style |
|---|---|---|
| Display / stat numerals | `'Playfair Display'`, `'Georgia'` | weight 900, tight letter-spacing |
| Headline | `'Inter'`, `'Roboto'` | weight 800, all-caps, tracked |
| Body / UI | `'Inter'`, `'Source Sans 3'` | weight 400, color `--en-text` |
| Caption / label | `'Inter'` | weight 600, uppercase, letter-spacing 0.1em |
| Data / code | `'IBM Plex Mono'`, `'JetBrains Mono'` | weight 400 |

Google Fonts import:
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600;800&family=Playfair+Display:wght@700;900&display=swap" rel="stylesheet">
```

---

## Quick-Start HTML Template

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Editorial Navy UI</title>
  <style>
    :root {
      --en-yellow:   #F5C842;
      --en-coral:    #E94B3C;
      --en-amber:    #D89148;
      --en-powder:   #B5D4E8;
      --en-blue:     #5BA3D9;
      --en-steel:    #6B8FA0;
      --en-beige:    #E3C9A0;
      --en-bg:       #0F1F3A;
      --en-bg-2:     #1A2D4F;
      --en-bg-3:     #243C66;
      --en-surface:  #1F3050;
      --en-border:   #3A4F75;
      --en-text:     #FFFFFF;
      --en-text-dim: #B5C5D8;
    }

    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: var(--en-bg);
      color: var(--en-text);
      font-family: 'Inter', 'Source Sans 3', sans-serif;
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

*Theme version: 1.0 — Editorial Navy*
