# Dark Teal Color Theme

> Default theme for the HTML Schematic Style Guide (`Claude Working Folder\Hubble Engineering - Document Style Guide\HTML_Schematic_Style_Guide\HTML_Schematic_Style_Guide.md`). Dark, cool surface · warm tan accent · cyan data primary. Extracted from `NaoDec_WS2815_LED_Controller_Rev1.6.html`.

---

## CSS Variables

Drop-in `:root` block. Comment markers included — paste into your schematic HTML between (or in place of) the existing `/* === THEME START === */` … `/* === THEME END === */` markers.

```css
/* === THEME START — Dark Teal === */
:root {
  --bg-dark:          #060a0b;
  --bg-panel:         rgba(10, 18, 20, 0.95);
  --wire-12v:         #eaddaa;
  --wire-5v:          #c9a86a;
  --wire-3v3:         #a28854;
  --wire-gnd:         #4a6b6d;
  --wire-data:        #88e2d6;
  --wire-data2:       #ffffff;
  --wire-data3:       #7cb3ff;
  --wire-data4:       #c8a2e8;
  --wire-data5:       #f0997b;
  --wire-data6:       #97c459;
  --wire-data7:       #f0d060;
  --text-primary:     #ffffff;
  --text-secondary:   #8eb5b8;
  --accent:           #eaddaa;
  --border:           rgba(74, 107, 109, 0.6);
  --comp-fill:        #0f1a1c;
  --comp-fill-hover:  #142326;
  --comp-stroke:      #4a6b6d;
  --pin-dot:          #88e2d6;
  --warn:             #ff5555;
  --warn-bg:          #1f0a0a;
}
/* === THEME END === */
```

---

## Visual Character

- **Surface** is near-black with a subtle teal undertone — sits cool, lets warm power rails pop.
- **Power rails** form a single warm earth-tone family ranging from cream (12V) through gold (5V) to muted brown (3.3V). GND is a desaturated teal that ties back to the surface.
- **Data channels** spread across the wheel: cyan → white → blue → lavender → coral → lime → yellow. Every adjacent pair is highly distinct, so a viewer can trace any signal even when several run in parallel.
- **Accent** is identical to `--wire-12v`. Titles and active highlights tie back visually to the dominant power rail.
- **Pin marker** is identical to `--wire-data` (the first data channel). GPIO dots and CH1 share a hue, reinforcing "this pin sources signal."
- **Warning** is a saturated red foreground over a near-black red background — readable but heavy, used sparingly.

---

## Surface

| Token | Hex / value | Use |
|---|---|---|
| `--bg-dark` | `#060a0b` | Page background. Also tooltip popup background and SVG export bg fill. |
| `--bg-panel` | `rgba(10, 18, 20, 0.95)` | Semi-transparent overlay for the legend strip and zoom-button background. |

---

## Power Rails (warm earth-tone family)

| Token | Hex | Use |
|---|---|---|
| `--wire-12v` | `#eaddaa` | 12 V rail — warm cream. Dominant; most lines on the diagram. |
| `--wire-5v` | `#c9a86a` | 5 V rail — muted gold. One step darker than 12V, same family. |
| `--wire-3v3` | `#a28854` | 3.3 V rail — earthy brown. Quietest of the rails. |
| `--wire-gnd` | `#4a6b6d` | Ground / common return — desaturated teal. Cool foil to warm rails. |

**Design intent:** the eye lands on 12V first, follows 5V/3.3V as supporting rails, treats GND as a quiet trunk. Lightness ladder (cream → gold → brown → teal) makes the hierarchy automatic.

---

## Data Channels (rainbow spread)

| Token | Hex | Use |
|---|---|---|
| `--wire-data` | `#88e2d6` | CH1 — bright cyan (primary; also `--pin-dot`) |
| `--wire-data2` | `#ffffff` | CH2 — pure white |
| `--wire-data3` | `#7cb3ff` | CH3 — bright blue |
| `--wire-data4` | `#c8a2e8` | CH4 — lavender |
| `--wire-data5` | `#f0997b` | CH5 — coral |
| `--wire-data6` | `#97c459` | CH6 — lime green |
| `--wire-data7` | `#f0d060` | CH7 — bright yellow |

**Design intent:** seven distinct hues, none directly adjacent on the wheel, all clearly readable on `--bg-dark`. White (CH2) is a deliberate "no-hue" anchor between cyan and blue.

---

## Text

| Token | Hex | Use |
|---|---|---|
| `--text-primary` | `#ffffff` | Body text inside SVG, button labels, BOM designators. |
| `--text-secondary` | `#8eb5b8` | Muted text — annotations, panel subtitles, secondary BOM info, footer hint. |
| `--accent` | `#eaddaa` | Section titles, hover stroke, tooltip title color. **Identical to `--wire-12v` by intent.** |

---

## Component / Structure

| Token | Hex / value | Use |
|---|---|---|
| `--comp-fill` | `#0f1a1c` | IC body fill — slightly lighter than `--bg-dark` for separation. |
| `--comp-fill-hover` | `#142326` | IC body fill on hover — one step lighter again. Subtle but unmistakable. |
| `--comp-stroke` | `#4a6b6d` | IC outline. **Identical to `--wire-gnd`.** |
| `--border` | `rgba(74, 107, 109, 0.6)` | Panel borders, table separators, button border. Translucent `--comp-stroke`. |
| `--pin-dot` | `#88e2d6` | GPIO pin marker fill. **Identical to `--wire-data`.** |

---

## Warning

| Token | Hex | Use |
|---|---|---|
| `--warn` | `#ff5555` | Warning text + banner stroke. Saturated red. |
| `--warn-bg` | `#1f0a0a` | Warning banner background. Near-black red — readable beneath red text. |

---

## Co-references (intentional duplicates)

| Tokens | Shared hex | Why |
|---|---|---|
| `--accent` ≡ `--wire-12v` | `#eaddaa` | Titles tie to the dominant rail. |
| `--comp-stroke` ≡ `--wire-gnd` | `#4a6b6d` | IC outlines fade quietly into the GND family. |
| `--pin-dot` ≡ `--wire-data` | `#88e2d6` | First data channel and GPIO pins share a hue. |

---

## Contrast on `--bg-dark` (`#060a0b`)

| Foreground | Hex | Contrast | Pass |
|---|---|---|---|
| `--text-primary` | `#ffffff` | ~20.5 : 1 | AAA |
| `--text-secondary` | `#8eb5b8` | ~8.5 : 1 | AAA |
| `--accent` / `--wire-12v` | `#eaddaa` | ~16.0 : 1 | AAA |
| `--wire-5v` | `#c9a86a` | ~9.0 : 1 | AAA |
| `--wire-3v3` | `#a28854` | ~5.4 : 1 | AA |
| `--wire-gnd` | `#4a6b6d` | ~3.4 : 1 | AA — stroke-only use |
| `--wire-data` | `#88e2d6` | ~12.0 : 1 | AAA |
| `--wire-data3` (blue) | `#7cb3ff` | ~9.4 : 1 | AAA |
| `--wire-data4` (lavender) | `#c8a2e8` | ~9.6 : 1 | AAA |
| `--wire-data5` (coral) | `#f0997b` | ~8.5 : 1 | AAA |
| `--wire-data6` (lime) | `#97c459` | ~9.4 : 1 | AAA |
| `--wire-data7` (yellow) | `#f0d060` | ~13.0 : 1 | AAA |
| `--warn` | `#ff5555` | ~5.5 : 1 | AA |

`--wire-gnd` meets the 3:1 VR5 stroke threshold at ~3.4:1 against `--bg-dark`. The GND rail is used exclusively for strokes, never for text.

---

## Compatibility

This theme defines all **23 tokens** in the contract. It drops into any schematic that follows the guide's conventions without further changes.

---

*Theme version: 1.0 — Dark Teal*
