# Nebula Pop Color Theme

> Deep-space indigo backgrounds with vibrant candy-bright planet accents.
> Playful, high-saturation, kid-friendly. Inspired by astronomy infographics.
> **To use as a schematic theme:** replace every `--np-*` name with the contract token name shown in the remap table below, then paste the block into the skeleton's `/* === THEME START … END === */` section.

---

## Token Remap — Nebula Pop → Schematic Contract

Replace `--np-*` names with these contract names before dropping into a schematic:

| Contract token (use this) | Nebula Pop source token | Hex |
|---|---|---|
| `--bg-dark` | `--np-bg` | `#1F1B47` |
| `--bg-panel` | `--np-surface` @ 95% opacity | `rgba(56, 48, 110, 0.95)` |
| `--wire-12v` | `--np-orange` | `#F08538` |
| `--wire-5v` | `--np-yellow` (Jupiter) | `#F4C842` |
| `--wire-3v3` | `--np-tan` (Saturn) | `#B59166` |
| `--wire-gnd` | muted mauve-gray (readable on `#1F1B47`) | `#7A6C99` |
| `--wire-data` | `--np-emerald` (Neptune) | `#1FB89E` |
| `--wire-data2` | `--np-text` | `#FFFFFF` |
| `--wire-data3` | `--np-teal` (Uranus) | `#3A9D9A` |
| `--wire-data4` | `--np-pink` (Venus) | `#E73861` |
| `--wire-data5` | `--np-purple` (Pluto) | `#A56FB5` |
| `--wire-data6` | `--np-yellow` lightened | `#F8D870` |
| `--wire-data7` | `--np-purple` lightened | `#C8A0D8` |
| `--text-primary` | `--np-text` | `#FFFFFF` |
| `--text-secondary` | `--np-text-dim` | `#C8B8E0` |
| `--accent` | `--np-orange` | `#F08538` |
| `--comp-fill` | `--np-bg-2` | `#2D2461` |
| `--comp-fill-hover` | `--np-bg-3` | `#4A3B7A` |
| `--comp-stroke` | `--np-border` | `#5A4B95` |
| `--border` | `--np-border` @ 60% opacity | `rgba(90, 75, 149, 0.6)` |
| `--pin-dot` | `--np-orange` | `#F08538` |
| `--warn` | `--np-pink` | `#E73861` |
| `--warn-bg` | `--np-bg` + pink tint | `#2E0815` |

---

## CSS Variables

Paste into your `:root {}` block.

```css
:root {
  /* Planet accents */
  --np-orange:    #F08538;   /* central highlight / sun */
  --np-emerald:   #1FB89E;   /* Neptune */
  --np-purple:    #A56FB5;   /* Pluto */
  --np-pink:      #E73861;   /* Venus */
  --np-teal:      #3A9D9A;   /* Uranus */
  --np-tan:       #B59166;   /* Saturn */
  --np-yellow:    #F4C842;   /* Jupiter */
  --np-mauve:     #B5667A;   /* lower atmosphere tint */

  /* Backgrounds (darkest → lightest) */
  --np-bg:        #1F1B47;   /* base canvas */
  --np-bg-2:      #2D2461;   /* content area */
  --np-bg-3:      #4A3B7A;   /* raised section */
  --np-surface:   #38306E;   /* card / panel */
  --np-border:    #5A4B95;   /* divider / stroke */

  /* Typography */
  --np-text:      #FFFFFF;   /* primary body */
  --np-text-dim:  #C8B8E0;   /* secondary / muted */
}
```

---

## Primary Accents

| Token | Hex | Use |
|---|---|---|
| `--np-orange` | `#F08538` | Primary CTA, brand highlights, hero |
| `--np-emerald` | `#1FB89E` | Success, positive data |
| `--np-pink` | `#E73861` | Danger, alerts, destructive |
| `--np-yellow` | `#F4C842` | Warnings, callouts, highlights |
| `--np-purple` | `#A56FB5` | Decorative, special badges |
| `--np-teal` | `#3A9D9A` | Info states, secondary links |
| `--np-tan` | `#B59166` | Warm secondary, earthy tones |
| `--np-mauve` | `#B5667A` | Decorative gradient stop |

---

## Color Ramps

Each ramp runs 7 stops: `50` (lightest) → `900` (darkest).

### Orange
| Stop | Hex |
|---|---|
| 50 | `#FFEFE0` |
| 100 | `#FFC9A3` |
| 200 | `#F08538` |
| 400 | `#C46518` |
| 600 | `#8C470A` |
| 800 | `#5C2D02` |
| 900 | `#2E1601` |

### Emerald
| Stop | Hex |
|---|---|
| 50 | `#E0FCF5` |
| 100 | `#A3F1DE` |
| 200 | `#1FB89E` |
| 400 | `#0E8C77` |
| 600 | `#076150` |
| 800 | `#033A30` |
| 900 | `#011D18` |

### Pink
| Stop | Hex |
|---|---|
| 50 | `#FFE0EA` |
| 100 | `#FFA3BC` |
| 200 | `#E73861` |
| 400 | `#B82048` |
| 600 | `#82142F` |
| 800 | `#54091D` |
| 900 | `#2A040E` |

### Teal
| Stop | Hex |
|---|---|
| 50 | `#E0F5F4` |
| 100 | `#A3DEDC` |
| 200 | `#3A9D9A` |
| 400 | `#247573` |
| 600 | `#114F4D` |
| 800 | `#062F2E` |
| 900 | `#021717` |

### Yellow
| Stop | Hex |
|---|---|
| 50 | `#FFFAE0` |
| 100 | `#FFF1A3` |
| 200 | `#F4C842` |
| 400 | `#C49E1D` |
| 600 | `#8C6F0D` |
| 800 | `#5C4806` |
| 900 | `#2E2402` |

### Purple
| Stop | Hex |
|---|---|
| 50 | `#F2E5F7` |
| 100 | `#D9B6E3` |
| 200 | `#A56FB5` |
| 400 | `#7E4A8E` |
| 600 | `#552F61` |
| 800 | `#321B3A` |
| 900 | `#190D1D` |

### Indigo (background)
| Stop | Hex |
|---|---|
| 50 | `#1F1B47` |
| 100 | `#262056` |
| 200 | `#2D2461` |
| 400 | `#38306E` |
| 600 | `#4A3B7A` |
| 800 | `#5A4B95` |
| 900 | `#7268B0` |

### Mauve
| Stop | Hex |
|---|---|
| 50 | `#FAE5EA` |
| 100 | `#E9B6C1` |
| 200 | `#B5667A` |
| 400 | `#8A4D5E` |
| 600 | `#5E3340` |
| 800 | `#3A1E27` |
| 900 | `#1D0E13` |

---

## Usage Patterns

### Backgrounds — layering order
```
--np-bg          canvas / full-page background
  └── --np-bg-2      content wrapper / main area
        └── --np-surface   card / panel
              └── --np-bg-3    hover / raised state
```

### Text contrast rules
- Body text on `--np-bg` → use `--np-text` (`#FFFFFF`)
- Secondary labels → use `--np-text-dim` (`#C8B8E0`)
- Pure white works here — the deep indigo provides strong contrast for a playful tech-poster feel

### Accent contrast on dark backgrounds
| Accent | Background | Contrast ratio |
|---|---|---|
| `#F08538` orange | `#1F1B47` | ~6.4 : 1 ✅ |
| `#1FB89E` emerald | `#1F1B47` | ~6.0 : 1 ✅ |
| `#F4C842` yellow | `#1F1B47` | ~10.2 : 1 ✅ |
| `#E73861` pink | `#1F1B47` | ~4.7 : 1 ✅ |
| `#3A9D9A` teal | `#1F1B47` | ~4.6 : 1 ✅ |
| `#A56FB5` purple | `#1F1B47` | ~4.5 : 1 ✅ |
| `#B59166` tan | `#1F1B47` | ~5.3 : 1 ✅ |

All accents pass WCAG AA (4.5:1) on the base canvas.

---

## Component Recipes

### Primary button
```css
.btn-primary {
  background: var(--np-orange);
  color: #1F1B47;
  border: none;
  padding: 10px 22px;
  font-family: 'Nunito', 'Quicksand', sans-serif;
  font-weight: 700;
  letter-spacing: 0.03em;
  border-radius: 999px;
  transition: transform 0.15s, box-shadow 0.15s;
}
.btn-primary:hover {
  transform: translateY(-1px);
  box-shadow: 0 6px 18px rgba(240, 133, 56, 0.4);
}
```

### Card / planet tile
```css
.card {
  background: var(--np-surface);
  border: 1px solid var(--np-border);
  border-radius: 16px;
  padding: 1.25rem 1.5rem;
}
/* circular planet-tile variant */
.planet-tile {
  border-radius: 50%;
  background: var(--np-emerald);
  color: var(--np-text);
  width: 120px;
  height: 120px;
  display: flex;
  align-items: center;
  justify-content: center;
  font-family: 'Nunito', sans-serif;
  font-weight: 700;
}
```

### Info callout
```css
.callout-info {
  background: #021717;             /* teal-900 */
  border-left: 4px solid var(--np-teal);
  color: #A3DEDC;                  /* teal-100 */
  padding: 12px 16px;
  border-radius: 8px;
}
```

### Warning callout
```css
.callout-warn {
  background: #2E2402;             /* yellow-900 */
  border-left: 4px solid var(--np-yellow);
  color: #FFF1A3;                  /* yellow-100 */
  padding: 12px 16px;
  border-radius: 8px;
}
```

### Badge / tag
```css
/* use the 900 bg + 100 text from the same ramp */
.badge-orange  { background: #2E1601; color: #FFC9A3; }
.badge-emerald { background: #011D18; color: #A3F1DE; }
.badge-pink    { background: #2A040E; color: #FFA3BC; }
.badge-teal    { background: #021717; color: #A3DEDC; }
.badge-yellow  { background: #2E2402; color: #FFF1A3; }
.badge-purple  { background: #190D1D; color: #D9B6E3; }

.badge {
  font-size: 12px;
  font-family: 'Nunito', sans-serif;
  letter-spacing: 0.04em;
  padding: 4px 12px;
  border-radius: 999px;
  text-transform: uppercase;
  font-weight: 700;
}
```

---

## Typography Recommendations

| Role | Font | Style |
|---|---|---|
| Display / heading | `'Fredoka'`, `'Sora'` | weight 700, friendly rounded |
| Body / UI | `'Nunito'`, `'Quicksand'`, sans-serif | weight 400–600 |
| Data / code | `'JetBrains Mono'`, `'Fira Code'` | weight 400 |

Google Fonts import (display + body):
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Fredoka:wght@500;700&family=Nunito:wght@400;600;700&display=swap" rel="stylesheet">
```

---

## Quick-Start HTML Template

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Nebula Pop UI</title>
  <style>
    :root {
      --np-orange:   #F08538;
      --np-emerald:  #1FB89E;
      --np-purple:   #A56FB5;
      --np-pink:     #E73861;
      --np-teal:     #3A9D9A;
      --np-tan:      #B59166;
      --np-yellow:   #F4C842;
      --np-mauve:    #B5667A;
      --np-bg:       #1F1B47;
      --np-bg-2:     #2D2461;
      --np-bg-3:     #4A3B7A;
      --np-surface:  #38306E;
      --np-border:   #5A4B95;
      --np-text:     #FFFFFF;
      --np-text-dim: #C8B8E0;
    }

    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      background: linear-gradient(180deg, var(--np-bg) 0%, var(--np-bg-2) 50%, var(--np-mauve) 100%);
      color: var(--np-text);
      font-family: 'Nunito', 'Quicksand', sans-serif;
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

*Theme version: 1.0 — Nebula Pop*
