# Cobalt Pop Color Theme

> Royal cobalt-blue canvas with bold, saturated accent pops — pink, lime, yellow, cyan, orange, purple.
> Editorial / design-tutorial aesthetic. Energetic, modern, infographic-friendly.
> **To use as a schematic theme:** replace every `--cb-*` name with the contract token name shown in the remap table below, then paste the block into the skeleton's `/* === THEME START … END === */` section.

---

## Token Remap — Cobalt Pop → Schematic Contract

Replace `--cb-*` names with these contract names before dropping into a schematic:

| Contract token (use this) | Cobalt Pop source token | Hex |
|---|---|---|
| `--bg-dark` | `--cb-bg` | `#15226B` |
| `--bg-panel` | `--cb-surface` @ 95% opacity | `rgba(42, 61, 159, 0.95)` |
| `--wire-12v` | `--cb-orange` | `#ED7E3C` |
| `--wire-5v` | `--cb-yellow` | `#F4D944` |
| `--wire-3v3` | `--cb-lime` | `#4FC97D` |
| `--wire-gnd` | muted blue-gray (readable on `#15226B`) | `#6F7CB8` |
| `--wire-data` | `--cb-cyan` | `#4ED7E5` |
| `--wire-data2` | `--cb-text` | `#FFFFFF` |
| `--wire-data3` | `--cb-pink` | `#ED4D7C` |
| `--wire-data4` | `--cb-red` | `#E84C5C` |
| `--wire-data5` | `--cb-pink` lightened | `#F49AB4` |
| `--wire-data6` | `--cb-purple` | `#8B6FE5` |
| `--wire-data7` | `--cb-lime` lightened | `#82E29C` |
| `--text-primary` | `--cb-text` | `#FFFFFF` |
| `--text-secondary` | `--cb-text-dim` | `#C5CFE5` |
| `--accent` | `--cb-cyan` | `#4ED7E5` |
| `--comp-fill` | `--cb-bg-2` | `#2A3D9F` |
| `--comp-fill-hover` | `--cb-bg-3` | `#3147A8` |
| `--comp-stroke` | `--cb-border` | `#4055B0` |
| `--border` | `--cb-border` @ 60% opacity | `rgba(64, 85, 176, 0.6)` |
| `--pin-dot` | `--cb-cyan` | `#4ED7E5` |
| `--warn` | `--cb-red` | `#E84C5C` |
| `--warn-bg` | `--cb-bg` + red tint | `#2E0813` |

---

## CSS Variables

Paste into your `:root {}` block.

```css
:root {
  /* Pop accents */
  --cb-cyan:      #4ED7E5;
  --cb-pink:      #ED4D7C;
  --cb-yellow:    #F4D944;
  --cb-lime:      #4FC97D;
  --cb-orange:    #ED7E3C;
  --cb-red:       #E84C5C;
  --cb-purple:    #8B6FE5;

  /* Backgrounds (darkest → lightest) */
  --cb-bg:        #15226B;   /* base canvas / header band */
  --cb-bg-2:      #2A3D9F;   /* content area */
  --cb-bg-3:      #3147A8;   /* raised section */
  --cb-surface:   #2A3D9F;   /* card / panel */
  --cb-border:    #4055B0;   /* divider / stroke */

  /* Typography */
  --cb-text:      #FFFFFF;   /* primary body */
  --cb-text-dim:  #C5CFE5;   /* secondary / muted */
}
```

---

## Primary Accents

| Token | Hex | Use |
|---|---|---|
| `--cb-cyan` | `#4ED7E5` | Headline highlights, primary CTA, active states |
| `--cb-pink` | `#ED4D7C` | Brand color, callouts, energetic accents |
| `--cb-yellow` | `#F4D944` | Highlights, warnings, attention markers |
| `--cb-lime` | `#4FC97D` | Success, positive data, fresh accents |
| `--cb-orange` | `#ED7E3C` | Warm accents, energy indicators |
| `--cb-red` | `#E84C5C` | Danger, destructive, alerts |
| `--cb-purple` | `#8B6FE5` | Decorative, special badges |

---

## Color Ramps

Each ramp runs 7 stops: `50` (lightest) → `900` (darkest).

### Cyan
| Stop | Hex |
|---|---|
| 50 | `#E0FAFD` |
| 100 | `#A3EEF4` |
| 200 | `#4ED7E5` |
| 400 | `#22A8B5` |
| 600 | `#0F7480` |
| 800 | `#06454D` |
| 900 | `#022226` |

### Pink
| Stop | Hex |
|---|---|
| 50 | `#FCE3EC` |
| 100 | `#F7AAC1` |
| 200 | `#ED4D7C` |
| 400 | `#C32C5B` |
| 600 | `#8A1A3F` |
| 800 | `#5A0E29` |
| 900 | `#2D0714` |

### Yellow
| Stop | Hex |
|---|---|
| 50 | `#FFFCE0` |
| 100 | `#FFF4A3` |
| 200 | `#F4D944` |
| 400 | `#C7B11A` |
| 600 | `#8A7A0D` |
| 800 | `#594F06` |
| 900 | `#2D2702` |

### Lime
| Stop | Hex |
|---|---|
| 50 | `#E3F9EB` |
| 100 | `#A7EBBF` |
| 200 | `#4FC97D` |
| 400 | `#2E9D5B` |
| 600 | `#1A6E3D` |
| 800 | `#0E4525` |
| 900 | `#072212` |

### Orange
| Stop | Hex |
|---|---|
| 50 | `#FCEBE0` |
| 100 | `#F7C5A3` |
| 200 | `#ED7E3C` |
| 400 | `#C25D1F` |
| 600 | `#893F0E` |
| 800 | `#592706` |
| 900 | `#2D1302` |

### Purple
| Stop | Hex |
|---|---|
| 50 | `#ECE5FC` |
| 100 | `#C5B6F4` |
| 200 | `#8B6FE5` |
| 400 | `#6948C7` |
| 600 | `#48298C` |
| 800 | `#2A165A` |
| 900 | `#150A2D` |

### Cobalt (background)
| Stop | Hex |
|---|---|
| 50 | `#15226B` |
| 100 | `#1B2A82` |
| 200 | `#2A3D9F` |
| 400 | `#3147A8` |
| 600 | `#4055B0` |
| 800 | `#5A6DC4` |
| 900 | `#7C8DD9` |

---

## Usage Patterns

### Backgrounds — layering order
```
--cb-bg          canvas / header band / full-page background
  └── --cb-bg-2      content wrapper / main area
        └── --cb-surface   card / panel
              └── --cb-bg-3    hover / raised state
```

### Text contrast rules
- Body text on `--cb-bg` or `--cb-bg-2` → use `--cb-text` (`#FFFFFF`)
- Secondary labels → use `--cb-text-dim` (`#C5CFE5`)
- Pure white intentional — drives the editorial-poster contrast

### Accent contrast on dark backgrounds
| Accent | Background | Contrast ratio |
|---|---|---|
| `#4ED7E5` cyan | `#15226B` | ~8.1 : 1 ✅ |
| `#F4D944` yellow | `#15226B` | ~11.4 : 1 ✅ |
| `#ED4D7C` pink | `#15226B` | ~4.9 : 1 ✅ |
| `#4FC97D` lime | `#15226B` | ~6.7 : 1 ✅ |
| `#ED7E3C` orange | `#15226B` | ~5.6 : 1 ✅ |
| `#E84C5C` red | `#15226B` | ~4.6 : 1 ✅ |
| `#8B6FE5` purple | `#15226B` | ~4.6 : 1 ✅ |

All accents pass WCAG AA (4.5:1) on the base canvas.

---

## Component Recipes

### Primary button
```css
.btn-primary {
  background: var(--cb-cyan);
  color: #15226B;
  border: none;
  padding: 10px 22px;
  font-family: 'Poppins', 'Inter', sans-serif;
  font-weight: 700;
  letter-spacing: 0.05em;
  text-transform: uppercase;
  border-radius: 4px;
  transition: transform 0.15s, box-shadow 0.15s;
}
.btn-primary:hover {
  transform: translateY(-1px);
  box-shadow: 0 6px 18px rgba(78, 215, 229, 0.4);
}
```

### Card / panel
```css
.card {
  background: var(--cb-surface);
  border: 0.5px solid var(--cb-border);
  border-radius: 6px;
  padding: 1.25rem 1.5rem;
}
/* accent left border */
.card--accent {
  border-left: 4px solid var(--cb-pink);
}
```

### Header band (poster-style)
```css
.poster-header {
  background: var(--cb-bg);
  color: var(--cb-text);
  padding: 2rem 2.5rem;
  text-align: center;
}
.poster-header .highlight {
  color: var(--cb-cyan);
  font-weight: 800;
}
```

### Tag stack (highlighter style)
```css
.tag-stack span {
  display: inline-block;
  padding: 4px 14px;
  font-family: 'Poppins', sans-serif;
  font-weight: 600;
  color: #15226B;
  margin-right: 6px;
  border-radius: 3px;
}
.tag-stack .t-pink   { background: var(--cb-pink); }
.tag-stack .t-yellow { background: var(--cb-yellow); }
.tag-stack .t-cyan   { background: var(--cb-cyan); }
.tag-stack .t-lime   { background: var(--cb-lime); }
```

### Badge / tag
```css
/* use the 900 bg + 100 text from the same ramp */
.badge-cyan   { background: #022226; color: #A3EEF4; }
.badge-pink   { background: #2D0714; color: #F7AAC1; }
.badge-yellow { background: #2D2702; color: #FFF4A3; }
.badge-lime   { background: #072212; color: #A7EBBF; }
.badge-orange { background: #2D1302; color: #F7C5A3; }
.badge-purple { background: #150A2D; color: #C5B6F4; }

.badge {
  font-size: 11px;
  font-family: 'Poppins', sans-serif;
  letter-spacing: 0.08em;
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
| Display / heading | `'Poppins'`, `'Montserrat'` | weight 800, tight letter-spacing |
| Body / UI | `'Poppins'`, `'Inter'`, sans-serif | weight 400–500 |
| Script accent (brand mark) | `'Berkshire Swash'`, `'Pacifico'` | display only |
| Data / code | `'JetBrains Mono'`, `'Fira Code'` | weight 400 |

Google Fonts import (display + body):
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;600;800&family=Berkshire+Swash&display=swap" rel="stylesheet">
```

---

## Quick-Start HTML Template

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Cobalt Pop UI</title>
  <style>
    :root {
      --cb-cyan:     #4ED7E5;
      --cb-pink:     #ED4D7C;
      --cb-yellow:   #F4D944;
      --cb-lime:     #4FC97D;
      --cb-orange:   #ED7E3C;
      --cb-red:      #E84C5C;
      --cb-purple:   #8B6FE5;
      --cb-bg:       #15226B;
      --cb-bg-2:     #2A3D9F;
      --cb-bg-3:     #3147A8;
      --cb-surface:  #2A3D9F;
      --cb-border:   #4055B0;
      --cb-text:     #FFFFFF;
      --cb-text-dim: #C5CFE5;
    }

    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: var(--cb-bg-2);
      color: var(--cb-text);
      font-family: 'Poppins', 'Inter', sans-serif;
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

*Theme version: 1.0 — Cobalt Pop*
