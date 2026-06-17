# Cyberpunk Color Theme

> Dark-first neon design system. All values are hardcoded hex — no dynamic generation required.
> **To use as a schematic theme:** replace every `--cp-*` name with the contract token name shown in the remap table below, then paste the block into the skeleton's `/* === THEME START … END === */` section.

---

## Token Remap — Cyberpunk → Schematic Contract

Replace `--cp-*` names with these contract names before dropping into a schematic:

| Contract token (use this) | Cyberpunk source token | Hex |
|---|---|---|
| `--bg-dark` | `--cp-bg` | `#0A0A0F` |
| `--bg-panel` | `--cp-surface` @ 95% opacity | `rgba(26,26,38,0.95)` |
| `--wire-12v` | `--cp-orange` | `#FF6B2B` |
| `--wire-5v` | `--cp-yellow` | `#F5E642` |
| `--wire-3v3` | `--cp-purple` | `#BF5FFF` |
| `--wire-gnd` | gray-200 (readable on `#0A0A0F`) | `#606080` |
| `--wire-data` | `--cp-cyan` | `#0FF0B3` |
| `--wire-data2` | `--cp-text` | `#E0E0F0` |
| `--wire-data3` | `--cp-blue` | `#4DBBFF` |
| `--wire-data4` | `--cp-magenta` | `#FF2D78` |
| `--wire-data5` | `--cp-orange` lightened | `#FF9E6B` |
| `--wire-data6` | `--cp-yellow` lightened | `#F8EE7A` |
| `--wire-data7` | `--cp-purple` lightened | `#D48FFF` |
| `--text-primary` | `--cp-text` | `#E0E0F0` |
| `--text-secondary` | `--cp-text-dim` | `#8888A0` |
| `--accent` | `--cp-cyan` | `#0FF0B3` |
| `--comp-fill` | `--cp-bg-2` | `#14141F` |
| `--comp-fill-hover` | `--cp-bg-3` | `#22222E` |
| `--comp-stroke` | `--cp-border` | `#2C2C40` |
| `--border` | `--cp-border` @ 60% opacity | `rgba(44,44,64,0.6)` |
| `--pin-dot` | `--cp-cyan` | `#0FF0B3` |
| `--warn` | `--cp-magenta` | `#FF2D78` |
| `--warn-bg` | `--cp-bg` + magenta tint | `#1F0A14` |

---

## CSS Variables

Paste into your `:root {}` block.

```css
:root {
  /* Neon accents */
  --cp-cyan:      #0FF0B3;
  --cp-magenta:   #FF2D78;
  --cp-yellow:    #F5E642;
  --cp-blue:      #4DBBFF;
  --cp-purple:    #BF5FFF;
  --cp-orange:    #FF6B2B;

  /* Backgrounds (darkest → lightest) */
  --cp-bg:        #0A0A0F;   /* base canvas */
  --cp-bg-2:      #14141F;   /* content area */
  --cp-bg-3:      #22222E;   /* raised section */
  --cp-surface:   #1A1A26;   /* card / panel */
  --cp-border:    #2C2C40;   /* divider / stroke */

  /* Typography */
  --cp-text:      #E0E0F0;   /* primary body */
  --cp-text-dim:  #8888A0;   /* secondary / muted */
}
```

---

## Primary Accents

| Token | Hex | Use |
|---|---|---|
| `--cp-cyan` | `#0FF0B3` | Primary CTA, links, active states |
| `--cp-magenta` | `#FF2D78` | Danger, alerts, destructive actions |
| `--cp-yellow` | `#F5E642` | Warnings, highlights, data callouts |
| `--cp-blue` | `#4DBBFF` | Info states, secondary links |
| `--cp-purple` | `#BF5FFF` | Decorative, special badges |
| `--cp-orange` | `#FF6B2B` | Warm accents, energy indicators |

---

## Color Ramps

Each ramp runs 7 stops: `50` (lightest) → `900` (darkest).

### Cyan
| Stop | Hex |
|---|---|
| 50 | `#E0FFF9` |
| 100 | `#A3FCED` |
| 200 | `#0FF0B3` |
| 400 | `#00C9A7` |
| 600 | `#008F78` |
| 800 | `#005E50` |
| 900 | `#002E28` |

### Magenta
| Stop | Hex |
|---|---|
| 50 | `#FFE0EC` |
| 100 | `#FFA3C1` |
| 200 | `#FF2D78` |
| 400 | `#CC1F5C` |
| 600 | `#8C1240` |
| 800 | `#5C0828` |
| 900 | `#2E0214` |

### Yellow
| Stop | Hex |
|---|---|
| 50 | `#FFFDE0` |
| 100 | `#FFF8A3` |
| 200 | `#F5E642` |
| 400 | `#C9BC1A` |
| 600 | `#8C830A` |
| 800 | `#5C5600` |
| 900 | `#2E2B00` |

### Blue
| Stop | Hex |
|---|---|
| 50 | `#E0F4FF` |
| 100 | `#A3DAFF` |
| 200 | `#4DBBFF` |
| 400 | `#1D8FD4` |
| 600 | `#0D5A8C` |
| 800 | `#06355C` |
| 900 | `#021A2E` |

### Purple
| Stop | Hex |
|---|---|
| 50 | `#F5E0FF` |
| 100 | `#DCA3FF` |
| 200 | `#BF5FFF` |
| 400 | `#9030E0` |
| 600 | `#5C1A8C` |
| 800 | `#38085C` |
| 900 | `#1C022E` |

### Orange
| Stop | Hex |
|---|---|
| 50 | `#FFE8E0` |
| 100 | `#FFC0A3` |
| 200 | `#FF6B2B` |
| 400 | `#D44D14` |
| 600 | `#8C2F06` |
| 800 | `#5C1C02` |
| 900 | `#2E0E01` |

### Background Dark
| Stop | Hex |
|---|---|
| 50 | `#0A0A0F` |
| 100 | `#0F0F1A` |
| 200 | `#14141F` |
| 400 | `#1A1A26` |
| 600 | `#22222E` |
| 800 | `#2C2C38` |
| 900 | `#38383F` |

### Gray
| Stop | Hex |
|---|---|
| 50 | `#B0B0C0` |
| 100 | `#8888A0` |
| 200 | `#606080` |
| 400 | `#404058` |
| 600 | `#2C2C40` |
| 800 | `#1A1A2C` |
| 900 | `#0F0F1A` |

---

## Usage Patterns

### Backgrounds — layering order
```
--cp-bg        canvas / full-page background
  └── --cp-bg-2      content wrapper / main area
        └── --cp-surface   card / panel
              └── --cp-bg-3    hover / raised state
```

### Text contrast rules
- Body text on `--cp-bg` → use `--cp-text` (`#E0E0F0`)
- Secondary labels → use `--cp-text-dim` (`#8888A0`)
- Never use pure `#FFFFFF` — it breaks the dark atmosphere

### Neon on dark backgrounds — minimum contrast
| Accent | Background | Contrast ratio |
|---|---|---|
| `#0FF0B3` cyan | `#0A0A0F` | ~9.8 : 1 ✅ |
| `#FF2D78` magenta | `#0A0A0F` | ~5.2 : 1 ✅ |
| `#F5E642` yellow | `#0A0A0F` | ~13.1 : 1 ✅ |
| `#4DBBFF` blue | `#0A0A0F` | ~8.4 : 1 ✅ |
| `#BF5FFF` purple | `#0A0A0F` | ~6.1 : 1 ✅ |
| `#FF6B2B` orange | `#0A0A0F` | ~5.6 : 1 ✅ |

All accents pass WCAG AA (4.5:1) on the base canvas.

---

## Component Recipes

### Primary button
```css
.btn-primary {
  background: transparent;
  color: var(--cp-cyan);
  border: 1px solid var(--cp-cyan);
  padding: 8px 20px;
  font-family: 'Courier New', monospace;
  letter-spacing: 0.08em;
  text-transform: uppercase;
  transition: background 0.15s, color 0.15s;
}
.btn-primary:hover {
  background: var(--cp-cyan);
  color: #0A0A0F;
}
```

### Card / panel
```css
.card {
  background: var(--cp-surface);
  border: 0.5px solid var(--cp-border);
  border-radius: 4px;
  padding: 1rem 1.25rem;
}
/* accent left border variant */
.card--accent {
  border-left: 2px solid var(--cp-cyan);
}
```

### Danger / alert state
```css
.alert-danger {
  background: #1A020C;          /* magenta-900 */
  border: 0.5px solid #8C1240; /* magenta-600 */
  color: #FFA3C1;               /* magenta-100 */
  border-radius: 4px;
  padding: 10px 14px;
}
```

### Text input
```css
input {
  background: var(--cp-bg-2);
  border: 0.5px solid var(--cp-border);
  color: var(--cp-text);
  padding: 8px 12px;
  font-family: 'Courier New', monospace;
  border-radius: 4px;
  outline: none;
}
input:focus {
  border-color: var(--cp-cyan);
  box-shadow: 0 0 0 2px rgba(15, 240, 179, 0.15);
}
```

### Badge / tag
```css
/* use the 900 bg + 100 text from the same ramp */
.badge-cyan    { background: #002E28; color: #A3FCED; }
.badge-magenta { background: #2E0214; color: #FFA3C1; }
.badge-yellow  { background: #2E2B00; color: #FFF8A3; }
.badge-blue    { background: #021A2E; color: #A3DAFF; }
.badge-purple  { background: #1C022E; color: #DCA3FF; }
.badge-orange  { background: #2E0E01; color: #FFC0A3; }

.badge {
  font-size: 11px;
  font-family: 'Courier New', monospace;
  letter-spacing: 0.08em;
  padding: 3px 10px;
  border-radius: 2px;
  text-transform: uppercase;
}
```

---

## Typography Recommendations

| Role | Font | Style |
|---|---|---|
| Display / heading | `'Share Tech Mono'`, `'Orbitron'` | uppercase, tracked |
| Body / UI | `'Courier New'`, `monospace` | normal, letter-spacing 0.04em |
| Data / code | `'IBM Plex Mono'`, `monospace` | weight 400 |

Google Fonts import (display + body):
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700&family=Share+Tech+Mono&display=swap" rel="stylesheet">
```

---

## Quick-Start HTML Template

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Cyberpunk UI</title>
  <style>
    :root {
      --cp-cyan:     #0FF0B3;
      --cp-magenta:  #FF2D78;
      --cp-yellow:   #F5E642;
      --cp-blue:     #4DBBFF;
      --cp-purple:   #BF5FFF;
      --cp-orange:   #FF6B2B;
      --cp-bg:       #0A0A0F;
      --cp-bg-2:     #14141F;
      --cp-bg-3:     #22222E;
      --cp-surface:  #1A1A26;
      --cp-border:   #2C2C40;
      --cp-text:     #E0E0F0;
      --cp-text-dim: #8888A0;
    }

    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: var(--cp-bg);
      color: var(--cp-text);
      font-family: 'Courier New', monospace;
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

*Theme version: 1.0 — Cyberpunk*
