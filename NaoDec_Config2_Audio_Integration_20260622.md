# NaoDec — Config 2 (PC Case) + Audio Integration Summary

**Project:** NaoDec — WS2815 LED + scent controller, with added audio subsystem
**Date:** 2026-06-22
**Scope:** Adding a GAB8 amplifier, 6 Microlab Satellite X3 speakers, and an Edifier T5
subwoofer to the **Config 2 (PC Case + ATX PSU)** build.
**Companion docs:** `NaoDec_Power_Report_Complete_20260617.md` (base design)

---

## 1. Key Finding — Audio is a SEPARATE Power Subsystem

The audio gear does **not** load the ATX / 12 V LED system. The three audio
components split across three different power domains:

| Component | Type | Power source | Loads the ATX? |
|-----------|------|--------------|----------------|
| **WONDOM GAB8** amplifier | DC amp board | **24 V DC** (own supply) | ❌ No |
| **Microlab Satellite X3** ×6 | **Passive** speakers | Driven *by* the GAB8 | ❌ No |
| **Edifier T5** subwoofer | **Powered/active** sub | **AC mains** (own plug) | ❌ No |

**Consequences:**
- The 6 satellites are passive — their "21 W" is power-handling, not consumption.
  You count the *amplifier's* draw, not the speakers'.
- The Edifier T5 is self-powered (internal amp + switching PSU) — it only takes a
  **line-level signal** cable. Zero DC load on the box.
- Because none of the audio is on the ATX, **the ATX sizing does not change.**

---

## 2. The 24 V Problem (drives every decision)

- **GAB8 input: 24 V DC recommended** (accepts 15–30 V).
- An **ATX PSU cannot make 24 V** — its rails are 12 V / 5 V / 3.3 V.
- 12 V is **below** the GAB8's 15 V minimum, so the LED rail can't run it either.

➡ The GAB8 **requires its own dedicated 24 V supply.** This is the single most
important integration fact.

---

## 3. Recommended Build (Config 2 + Audio)

```
220 V AC ─► IEC inlet ─► 10 A MCB ─┬─► ATX PSU (650 W)  ──► 12 V LEDs+scent, 5 V logic
                                   │
                                   ├─► 24 V PSU (240 W)  ──► GAB8 ──► 6× Microlab satellites
                                   │
                                   └─► (or wall plug) ───► Edifier T5  (self-powered sub)
```

### Parts to add
| Part | Spec | Purpose |
|------|------|---------|
| **24 V PSU** — Mean Well LRS-240-24 | 24 V / 10 A / 240 W | Powers the GAB8 (headroom for 6 satellites) |
| 24 V branch fuse | ~10–12 A inline | Per-branch protection (PSU gives none) |
| Line-level cable | RCA / 3.5 mm | GAB8 sub-out → Edifier T5 input |
| Fused AC splitter | downstream of MCB | Feeds both ATX and 24 V PSU |

*(Step up to LRS-350-24 only if driving the satellites hard or adding channels.)*

---

## 4. ATX PSU Selection (from report shortlist)

Audio does **not** change the ATX pick — the ATX still only carries LEDs + logic + scent
(~329 W worst case ≈ **50.6 % load at 650 W**; the GAB8 is on its own 24 V supply). The build is
**right-sized to a ~650 W 80+ Bronze single-rail PSU** (see the PSU report + `NaoDec_ATX_PSU_Wiring_and_Connectors.md`):

| Rank | Model | Why |
|------|-------|-----|
| ✅ **Best** | **Thermaltake Smart BM3 Bronze 650W** (B1) | Semi-modular (tidy cabling), ATX 3.0, single 12 V rail |
| Runner-up | **Corsair CV650** (B2) | Confirmed Thai stock, single rail, budget |
| Alt | SilverStone VIVA650 (B3) / MSI A650BN (B4) | Single-rail Bronze equivalents |
| Avoid | be quiet! Straight Power 11 850W (#6) | Multi-rail (two 21 A rails < 27.1 A load, no single-rail mode) — plus 850 W is oversized here |

> **If the audio gear shares one cramped case**, that's an **airflow** matter, not a reason to oversize:
> keep a case intake/exhaust fan across the PSU and GAB8. A 650 W Bronze at ~50 % load runs only
> mildly warm. Fan *noise* is a non-issue because the box is remote from the room.
>
> Note: the shortlist's "70.8 A / 83.3 A" 12 V figures are just watts ÷ 12; a 650 W single rail is
> ~54 A. Irrelevant at ~29 A draw either way.

---

## 5. Power Totals (with audio)

**DC side — what the box supplies:**
| Rail | Source | Worst case | Typical |
|------|--------|-----------|---------|
| 5 V logic | ATX | 4 W | 4 W |
| 12 V LED + scent | ATX | 329 W | 60–150 W |
| 24 V audio (GAB8) | **new 24 V PSU** | ~140 W | 20–40 W |
| **DC supply capacity** | | **~570 W** | — |

**AC mains side — what the 220 V circuit feeds:**
| Source | Worst case AC |
|--------|---------------|
| ATX (LEDs + logic + scent) | ~385 W |
| 24 V GAB8 supply | ~280 W |
| Edifier T5 (own plug) | ~120 W |
| **Total AC, worst case** | **~785 W (~3.6 A @ 220 V)** |
| **Total AC, realistic operating** | **~250–350 W** |

Well within the existing 10 A MCB.

---

## 6. Fitting the GAB8 in the Same PC Case

**Possible? Yes** — a PC case is built for a full ATX board + GPU + cooler, far
bulkier than this hardware. Space is **not** the constraint.

**What goes in:** GAB8 board (+ its fan) and the 24 V PSU (~199 × 98 × 38 mm).
Both mount easily on the motherboard tray, drive bays, or case floor.

**The real constraints (not volume):**
1. **EMI / noise isolation** — the LED side (switching PSU, ESP32 Wi-Fi, fast LED
   data) is noisy; the GAB8 is a noise-sensitive analog amp. Buzz/hiss risk if not
   isolated.
2. **Heat / airflow** — ATX + 24 V PSU + GAB8 fan all add heat. Use a **full tower**
   and put the GAB8 in the fan path.
3. **PSU mount** — the case has one ATX mount; the 24 V supply mounts on the
   floor/bay with a bracket.

**Zone the case:**
```
┌─────────────── PC CASE (full tower) ───────────────┐
│  AUDIO ZONE          │  CONTROL ZONE                │
│  • 24 V PSU          │  • ATX PSU                   │
│  • GAB8 (+ fan)      │  • 2× ESP32 (LED M/S)        │
│  • shielded audio    │  • SN74AHCT245N level shift  │
│    cables only       │  • Waveshare scent relay     │
│                      │  • LED data out, fuses       │
└──────────────────────┴──────────────────────────────┘
   audio + LED wiring on opposite sides · single star-point GND
```

---

## 7. Recommendation / Opinion

- **If staying with Config 2:** the build above works well — 850 W be quiet!
  Straight Power 11, dedicated 24 V supply, full tower, zoned for noise isolation.
- **Stronger recommendation for a permanent install:** once a 24 V audio rail is
  added, Config 2 loses its "one supply, one cable" simplicity — it becomes an ATX
  + a bolt-on supply. **Config 1 (DIN enclosure) is cleaner**, because adding 24 V
  is just one more DIN PSU on the rail (isolated, fused, serviceable by design).
- **GAB8 is oversized** for six 2.5″ satellites (500 W / 10 ch driving ~21 W speakers)
  — works fine, just more amp than needed.
- **Keep the Edifier T5 on its own wall plug** — don't integrate a powered sub.

---

## 8. Open Items

1. **Confirm GAB8 board dimensions** against the chosen case before final layout.
2. **Decide audio location:** inside the shared case (zoned) vs. a separate/partitioned
   audio box (cleanest for hum-free audio).
3. **Grounding plan:** single star point tying ATX, 24 V supply, and signal grounds —
   avoid ground loops that hum through the speakers.
4. Base-design open items from the source report still apply (Strip #1 wire gauge,
   in-strip trace resistance measurement).

---

## References
- `NaoDec_Power_Report_Complete_20260617.md` — base power & box design
- WONDOM GAB8 manual — 24 V in, 10×50 W TPA3244
- Edifier T5 — 70 W RMS powered subwoofer (self-powered, AC)
- Microlab X3 — 2.5″ satellites, ~21 W RMS each
