# NaoDec — Project Knowledge & History (Rev 1.0)

**Snapshot date:** 2026-07-14
**Scope:** A single, plain-text compendium of *everything known about NaoDec* — not just what
the schematics say today. It deliberately captures three kinds of information that are otherwise
scattered or missing:

1. **Current facts** — the live design, per subsystem, with pointers to the authoritative file.
2. **Information not (well) represented in the GitHub repo** — knowledge that lives only in
   commit messages, files that are referenced but absent, and material that never reaches the
   published site.
3. **Outdated / superseded information** — old numbers and decisions kept on purpose, each with
   what replaced it and where the stale copy still appears.

This document is a *reference and audit*, not a correction. Per the task decision it changes no
other file: nothing here edits the README, `CLAUDE.md`, or any schematic. Where it flags a stale
link or a wrong number, that is a finding to act on later, not a change made here.

> **How to read the citations.** Sources are given as either a repo file path or a git commit
> hash (e.g. `dc0122a`). "Live" means the value is still shown in a current, non-archived file.
> Where two live files disagree, both are cited so the conflict is visible.

---

## 1. What NaoDec is

NaoDec is a large addressable-LED art installation built as a **regular dodecahedron**
(20 vertices, 30 edges, 12 pentagonal faces; Euler check 20 − 30 + 12 = 2). Eleven faces are
wooden-frame + stretched-fabric panels; the twelfth (bottom) face is left open as the entry.
The lighting is **1,740 × WS2815 (12 V) pixels across 7 channels**, driven by **two
ESP32-S3-WROOM-1 N16R8** modules running **WLED** in a master/slave **DDP** configuration, with a
**SN74AHCT245N** octal transceiver doing 3.3 V → 5 V logic level shifting. A Mac mini running
**Max/MSP** is the show host.

Around that core are several ancillary subsystems, each with its own documentation set: a series
**electromagnet coil** loop, a **media-playback operator panel**, a **scent controller**, and a
consolidated **power / controller-box** study. There is also a **paint** reference note for the
physical build.

The repo is a set of **self-contained interactive HTML schematics** (no build step, no
dependencies) plus Markdown/DOCX notes and Arduino firmware. It is published via GitHub Pages at
**https://surasaknie.github.io/naodec/**, where `index.html` is auto-generated on push to `main`
by `.github/workflows/update-index.yml`.

---

## 2. Current system snapshot (per subsystem)

### 2.1 LED controller — `NaoDec_WS2815_LED_Controller_Rev1.6.html` (current)

- **Topology:** two ESP32-S3-WROOM-1 N16R8 modules. **Master** = WLED, drives CH1–CH4
  (GPIO1, 4, 5, 6). **Slave** = WLED DDP receiver, drives CH5–CH7 (GPIO4, 5, 6). The master
  computes all effects and streams pixel data to the slave over DDP/Wi-Fi; the slave does no
  local effect computation.
- **Level shifting:** U2 = SN74AHCT245N octal transceiver, 3.3 V → 5 V, 7 channels used
  (A1→B1 … A7→B7).
- **Channel map:**

  | CH | GPIO (board)   | Buffer    | Strip       | LEDs | Cable | Wire AWG |
  |----|----------------|-----------|-------------|------|-------|----------|
  | 1  | GPIO1 (Master) | U2 A1→B1  | #1 Vertex   | 60   | ~20 m | 18       |
  | 2  | GPIO4 (Master) | U2 A2→B2  | #2 Edge A   | 280  | ~8 m  | 12       |
  | 3  | GPIO5 (Master) | U2 A3→B3  | #3 Edge B   | 280  | ~8 m  | 12       |
  | 4  | GPIO6 (Master) | U2 A4→B4  | #4 Edge C   | 280  | ~8 m  | 12       |
  | 5  | GPIO4 (Slave)  | U2 A5→B5  | #5 Edge D   | 280  | ~8 m  | 12       |
  | 6  | GPIO5 (Slave)  | U2 A6→B6  | #6 Edge E   | 280  | ~8 m  | 12       |
  | 7  | GPIO6 (Slave)  | U2 A7→B7  | #7 Edge F   | 280  | ~8 m  | 12       |

  Total **1,740** WS2815. Source-end termination R1–R7 = **47 Ω** ¼ W metal film, ≤20 mm from U2.
- **Power rails (keep V+ fully isolated):** 5 V logic (PSU 5 V 3 A / 15 W → both Vin + U2 VCC);
  12 V 5 A (60 W → Strip #1 vertex set, ~0.9 A); 12 V 50 A (600 W → Strips #2–#7 edge sets,
  ~25.2 A max). Smoothing C1 1000 µF/25 V, bypass C2–C6/C8 1000 µF/25 V, U2 decouple C7 100 nF,
  inrush NTC1 10 Ω/10 A on the 12 V 50 A rail. Fusing: F1 7.5 A blade (Strip #1) + FB1 6-ch block
  F2–F7 7.5 A each.
- **Strapping-pin warning:** avoid GPIO 0, 3, 45, 46 on the ESP32-S3 (boot-mode conflict).
- **Signal flow:** Mac mini → USB-C/UART → Master (WLED) → U2 → R1–R4 → CH1–CH4; Master → DDP
  (Wi-Fi) → Slave (WLED) → U2 → R5–R7 → CH5–CH7.
- **In-file revision history (Rev 1.0 → 1.6):** 1.0 initial · 1.1 added FB1 fuse block · 1.2
  revised resistors + C7 decoupling · 1.3 swapped 2× SN74AHCT125N for 1× SN74HCT245N · 1.4 dual
  ESP32-S3 with DDP (master/slave), single SN74AHCT245N, BI→GND · 1.5 grew to 7 strips (280 each),
  CH7 via A7/B7, slave GPIO6, added R7/C8/F7 + NTC1, R2–R7 corrected 100 Ω → 47 Ω · **1.6 upgraded
  the PSU from 5 A to 10 A** (current).

> **Naming note:** the Rev 1.3 line says "SN74**HCT**245N" while every other reference (README,
> CLAUDE.md, the part list) says "SN74**AHCT**245N". Treat AHCT as authoritative; the HCT spelling
> in the Rev 1.3 changelog line is a typo. (Source: `NaoDec_WS2815_LED_Controller_Rev1.6.html:1034`.)

A stripped-down single-strip reference, **`Simple_WS2815_Controller_Rev_1.0.html`** ("LED Strip
Test Kit"), exists for bench-testing one strip in isolation.

### 2.2 3D structure & mapping

- **`NaoDec_3D_Structure_Framework_Rev1.0.html`** (current) — pure geometry: vertices v1–v20,
  edges, faces f1–f12, **no LED wiring**. Default view hides vertices/node numbers and shows the
  30 structural edges, each carrying its physical assembly letter. **f1 = top**, **f11 = door**,
  **f12 = unbuilt bottom**; the 5 base edges bordering f12 render as **OPEN** (they rest on the
  platform).
- **`NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.3.html`** (current) — the full LED
  vertex/edge circuit mapping and channel tracing.
- **`NaoDec_Face_Edge_Marking_Rev1.0.html`** (current) — edge-letter marking guide for the 11
  built faces, one labeled diagram per face plus an auto-validated edge cross-reference. Shared
  edges between two built faces carry the **same letter** (A–Z, **no W**), so assembly/tear-down
  is match-identical-letters with no face lookup. Faces 7–11 carry the 5 unlettered platform
  edges.
- **`NaoDec_Face_Edge_Marking_Interactive_Rev1.0.html`** (current) — same marking data, alternate
  design with an interactive joint-highlight dropdown instead of a static-only table.

### 2.3 Series coil / electromagnet subsystem — **pre-release**

Authoritative pages: **`NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`** (design write-up, Rev 0
pre-release) and **`NaoDec_Vertex_Series_Coil_Rev1.0.html`** (interactive schematic, in-file
**Rev 1.0a**, Dark Blue-Mint theme).

- **Physical build:** 60 hand-wound copper coils in one series loop. Each coil = 7 turns of 1 mm
  copper on a **12.5 mm ID crystal core**, 5 cm straight lead in + 7 cm out, ~0.417 m copper per
  coil, ~25.0 m total. Grouped as **20 groups × 3 coils**.
- **Two hard physical facts:** (a) an inductor does nothing on steady-state DC (Z = jωL → 0), so
  the loop is a resistive near-short; (b) the crystal core is **non-magnetic** (μ ≈ air) → no
  field boost, so these behave as weak air-core coils.
- **Adopted current-limited path** (README + Vertex Rev 1.0a — the current design):

  `12 V PSU → exact 3 A slow-blow (T) fuse → 220–470 µF + 100 nF input decoupling → dual-pot
  XL4015 (CV 11.0 V, CC 3.0 A) → 70–80 °C thermal cutoff → 20 groups / 60 coils → 20 AWG return`

- **Current electrical summary (Gen 3 — see §4.1):** ~1.85 Ω cold-loop estimate (≈0.55 Ω coils +
  1.30 Ω measured 20 AWG wiring); 3.0 A CC; ~5.55 V loaded output; ~16.65 W total output; ~21 AT
  per coil.
- **Safety rules:** dual-pot CC/CV XL4015 only; CV 11.0 V / CC 3.0 A; **exact 3 A** slow-blow
  input fuse (CC regulation is not fault protection; bucks fail *shorted*); local input
  decoupling; 70–80 °C thermal cutoff for manned operation; keep the full 20 AWG run **uncoiled**;
  keep this V+ rail isolated from the LED rails; **never run the string without the buck**.
- **Connectors:** 20 × JST SM 2-pin, both pins paralleled onto the series conductor (fine once the
  buck caps the loop at ~3 A; single SM pin = 3 A). VH (10 A) / XT30 / Anderson are
  higher-margin alternatives.

### 2.4 Media Playback Controller — hardware Rev 3.0, firmware 3.1.x

An ESP32-S3-DevKitC-1 **operator panel** (rotary volume encoder + Play/Pause/Stop buttons +
network-status LED) mounted on the side of a chair. It **carries no audio/video/LED data or
power** — it only sends OSC-over-UDP transport/volume commands to the Mac mini's Max/MSP patch.

- **Schematic:** `NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html` (current). Rev 3.0 added
  **U2 = WIZnet W5500 Lite Ethernet** module (SPI on GPIO13–18) + C6 100 nF decoupling + a ~6 m
  Cat6 run to the ASUS router; the R1–C5 encoder/button front-end is unchanged from Rev 2.x.
- **Why wired Ethernet:** the panel sits ~6 m from the router/Mac mini; the original design
  assumed the ESP32-S3 inside the panel with ≤0.5 m unbuffered 3.3 V signal runs. Moving the board
  to the router would stretch those lines into noise antennas. Wired Ethernet keeps the board in
  the panel and solves the distance problem. (Full reasoning:
  `NaoDec_Media_Playback_Controller_Rev3.0_Ethernet_Rationale.md`.)
- **Firmware:** `firmware/media_playback_controller/media_playback_controller_R3.1.ino`. FW 3.0.x =
  Ethernet-only; **FW 3.1.x adds an optional Wi-Fi fallback** on the same Rev 3.0 hardware —
  Ethernet stays primary and wins the instant its link + DHCP lease return; Wi-Fi is used only if
  the cable drops *and* credentials were stored over serial (`SETWIFI`). No credentials in the
  sketch; DHCP reservation is keyed to the printed Ethernet MAC (`STATUS` serial command).
- **Network / OSC contract** (from `NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md`,
  Rev 3.1):

  | Item | Value |
  |------|-------|
  | Play / Pause / Stop | `/transport/play 1` · `/transport/pause 1` · `/transport/stop 1` (int) |
  | Volume encoder | `/volume <float 0.0–1.0>` (e.g. `/volume 0.65`) |
  | mDNS hostname | `naodec-playback.local` |
  | OSC UDP port | `9000` |
  | OSC destination (Max computer) | `192.168.50.2` |
  | Controller reserved IP (DHCP) | `192.168.50.114` |
  | Router | ASUS RT-AX1800HP |

### 2.5 Scent Controller — schematic Rev 2.0, firmware R2.0

A **Waveshare ESP32-S3-Relay-6CH** board driving **4× JY-M27AO atomizers** over its onboard
relays; scent-only, no audio/video/LED. Each relay switches one atomizer on for a bounded
duration.

- **Schematic:** `NaoDec_Scent_Controller_Schematic_Rev2.0.html` (current). Rev 2.0 (2026-05-19)
  **removed the 5 V rail** (deleted U2, F2, RC1–RC4) and moved the COM bus from 5 V to 12 V direct;
  Note 2 specifies 4 separate pigtails, not a daisy-chain. (Rev 1.0, 2026-05-14, is archived.)
- **Firmware:** `firmware/Scent_controller/Scent_controller_web_R2.0.ino` (R2.0). Three command
  entry points, all funnelled through one `handleCommand()`: **Web UI** (HTTP :80, then a
  **WebSocket on :81**, all embedded in PROGMEM), **Max/MSP** (UDP **:4210**), and **Serial**
  (USB 115200). Built-in mobile web UI at **`http://aroma.local/`** (see the naming caveat in §4.3).

### 2.6 Controller box & power

- **`NaoDec_Controller_Box_Configs_Rev1.1.html`** (current) — houses both the LED and scent
  controllers in **one control box** from a single 220 V AC input. Two documented options:
  **Config 1** = electrical enclosure with 3–4 isolated DIN-rail PSUs (recommended for a permanent
  install); **Config 2** = ATX PC case with a single ATX PSU (compact/cheaper, viable only with
  mandatory inline fusing kept).
- **`NaoDec_Power_and_Controller_Box_Report.md`** (Rev 1.0, 2026-06-14) — the consolidated power
  budget, PSU selection, cable/voltage-drop analysis, and the audit of all figures. Key findings:
  existing PSU specs are valid (no resizing needed); the 6 long edge strips (5 m strip + 4 m feed
  each) **require mid-strip power injection** to hold end-of-strip voltage; all figures were
  audited and recalculated (see §4.4 for the corrections applied Rev 1.0 → Rev 1.1).

### 2.7 Ancillary knowledge

- **Paint:** `Paint_Comparison_Maxzo_RustTech_vs_JBP_SmartGlaze.md` compares three oil/alkyd
  coatings for the wood build — Maxzo Rust Tech 2IN1 #8300 (matte, metal-primary, *not* labeled for
  solid/hardwood), JBP Smart Glaze Ultra Gloss Enamel (alkyd topcoat, needs separate primer on bare
  wood), and JBP Smart Glaze 2IN1 (acrylic, primer + topcoat, explicitly wood-labeled).
- **Wire-color palette (design binding):** `CLAUDE.md` holds the Wire Assignment Table used by the
  `html-schematic` skill — the **Dark Teal** palette that keeps every schematic's net colors
  consistent. Per-channel: wdata #88e2d6 (CH1), wdata2 #ffffff (CH2), wdata3 #7cb3ff (CH3),
  wdata4 #c8a2e8 (CH4), wdata5 #f0997b (CH5), wdata6 #97c459 (CH6), wdata7 #f0d060 (CH7). Fixed
  power rails: w12v #eaddaa, w5v #c9a86a, w3v3 #a28854, wgnd #4a6b6d.
- **Tooling:** `.claude/skills/html-schematic/` is the vendored org skill (v4.0.0) that generates
  these interactive SVG schematics, with theme palettes under `reference/themes/`.

---

## 3. Information NOT in the GitHub repo

This is the heart of the request: knowledge that is real but that a reader browsing GitHub (or the
Pages site) would not find.

### 3.1 A referenced file that does not exist — `XL4015_CC_CV_Mockup_Test_Procedure.md`

The README links this file **three times** (repo tree, Series-Coil intro, and the "XL4015 Mockup
Qualification" section), but **the file is not in the repo.** The link is dead on GitHub and on the
Pages site.

What is *recoverable* about its intended contents, from the README's "XL4015 Mockup Qualification"
paragraph (this is the only surviving description):

- **Goal:** before wiring the real coils, reproduce the ~1.85 Ω loop on the bench.
- **Mock load:** the measured **1.30 Ω** mock wire in series with a **~0.56 Ω** resistor bank.
  Practical bank = **10 × 5.6 Ω / 1 W metal-film in parallel** → 0.56 Ω / 10 W.
- **Expected readings at the 3.0 A CC setting:** ~**5.58 V** total, ~**3.90 V** across the mock
  wire, ~**1.68 V** across the resistor bank.
- **Instrumentation:** ammeter in series **after XL4015 OUT+**.

Everything beyond that outline (the step-by-step wiring and the pass/fail thresholds the README
says the file contains) is **not preserved anywhere in the repo** — it was either never committed
or was lost. If the procedure is needed, it must be reconstructed from the outline above.

### 3.2 Knowledge that lives only in git commit messages

These facts are not in any current document body — only in the commit log:

- **Bench-measured coil operating point (commit `dc0122a`):** on the bench the string ran at
  **11.68 V / 2.75 A (~32 W)** at the buck output, implying a **real loop ~4.3 Ω** — above the
  ~3 Ω estimate that was current at the time — so current settled just under the 3 A cap, sitting
  at the CV/CC knee rather than deep in CC. This measurement is still shown on the **Rev 0
  pre-release page** but was **not carried into the later ~1.85 Ω / ~5.55 V design** (README /
  Vertex Rev 1.0a). See §4.1 for why the two disagree.
- **Firmware/file rename `aroma_controller` → `Scent_controller` (commits `bb07f2d`, `c48b8ad`,
  `f94a881`):** the scent firmware was originally named "aroma"; the source file and folder were
  renamed to "Scent", but the **`aroma.local` mDNS hostname and UDP command scheme were kept** (see
  §4.3).
- **Edge-position convention fix (commit `e4f3ade`):** edge numbering is **CCW from edge 1, not
  CW** — a corrected convention that a reader of the current pages would not know was ever wrong.
- **"Standalone tester for Mac" (commit `8b5c7b4`):** this is what
  `firmware/media_playback_controller/TransportReceiveTest1.maxpat.zip` is — a zipped Max patch for
  bench-testing the OSC transport messages without the full show patch. The repo ships the zip with
  no README entry explaining it.
- **The media-playback / media-doc rename & archive chain** (commits `543554f`, `4ebb872`,
  `81de444`, `6fc1cdc`, `e8bc454`) — files were renamed for consistency and old revisions moved to
  `Archived/`; the "why" is only in those commit subjects.

### 3.3 Knowledge that never reaches the published site

`index.html` is auto-generated by `.github/workflows/update-index.yml`, which lists **only
`*.html`** (except `index.html` itself). Therefore **none of the Markdown or DOCX knowledge is
linked from https://surasaknie.github.io/naodec/** — invisible to a Pages visitor:

- `NaoDec_Power_and_Controller_Box_Report.md` (the entire power budget + audit)
- `NaoDec_Media_Playback_Controller_Rev3.0_Ethernet_Rationale.md`
- `NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md` (+ the `.docx`)
- `Paint_Comparison_Maxzo_RustTech_vs_JBP_SmartGlaze.md`
- both `firmware/**/README.md` files and all firmware source
- `CLAUDE.md` (project memory, incl. the wire-color palette binding)
- **this** document

They are reachable only by browsing the GitHub repo directly, not the Pages site.

### 3.4 Placeholder / empty content

- `Archived/Note.txt` contains only the single word "Note" — a placeholder with no information.

---

## 4. Outdated / superseded information (kept on purpose)

These are old facts that still exist somewhere in the repo. Each is listed with what replaced it,
so the stale copy can be recognized on sight.

### 4.1 The series-coil numbers went through three generations

The coil subsystem's electrical model was revised twice; **all three generations still exist in the
repo** in different files, and they do not agree.

| Quantity | **Gen 1** — Rev 0 pre-release page *(still live)* | **Gen 2** — `CLAUDE.md` status notes *(still live)* | **Gen 3** — README + Vertex Rev 1.0a *(current design)* |
|---|---|---|---|
| Loop resistance | ~3 Ω estimate; **bench-measured ~4.3 Ω** | ~3 Ω | **~1.85 Ω** cold-loop (0.55 Ω coils + 1.30 Ω wiring) |
| Wire gauge | **24 AWG** | (unstated) | **20 AWG** |
| CC / CV setting | CC ~3 A; CV ~11–12 V | CC ~3 A | **CC 3.0 A / CV 11.0 V** |
| Loaded output | **bench 11.68 V / 2.75 A (~32 W)** | (n/a) | **~5.55 V / ~16.65 W** |
| Unlimited (no buck) draw | ~4 A | (implied near-short) | ~6.5 A / ~78 W |
| Field per coil | **~28 AT** (7 turns × ~4 A) | **~28 AT** | **~21 AT** (7 turns × 3 A) |
| Input fuse | **3–5 A** guidance | **3–5 A** | **exactly 3 A** slow-blow |
| Thermal cutoff | not specified | not specified | **70–80 °C TCO required** |
| Connectors | JST SM paralleled | JST SM paralleled | JST SM paralleled (unchanged) |

**How to reconcile:**

- The single biggest driver is the **wire-gauge change (24 AWG → 20 AWG)**. Gen 1's bench loop of
  ~4.3 Ω was measured on 24 AWG; Gen 3's ~1.85 Ω uses a *measured* 1.30 Ω of 20 AWG plus ~0.55 Ω of
  coils. So the resistance drop from 4.3 Ω to 1.85 Ω is a real design change, not a contradiction.
- The **field-per-coil** figure fell from ~28 AT to ~21 AT purely because the assumed operating
  current dropped from ~4 A to a firm 3.0 A.
- **Unreconciled:** the loaded-output voltages (**bench 11.68 V** vs **design ~5.55 V**) have *not*
  been squared against each other. Gen 3 is a *predicted* operating point for the 1.85 Ω / 20 AWG
  loop; the 11.68 V bench figure was a *measurement* on the older 24 AWG loop. Neither has been
  confirmed against the **final assembled loop**, which is exactly why the subsystem is still
  **Rev 0 pre-release** pending real end-to-end resistance + thermal commissioning.

**Stale-copy locations to watch:**
- `CLAUDE.md` "Status notes" still describe **Gen 2** (~3 Ω, ~28 AT, fuse 3–5 A) — two generations
  behind the current README design.
- The Rev 0 pre-release HTML still shows **Gen 1** (24 AWG, ~4 A, ~28 AT, 3–5 A fuse, bench
  11.68 V/2.75 A). It is correctly labeled pre-release, so this is expected, but a reader must not
  mistake its numbers for the current design.

### 4.2 Archived revision catalog

Everything in `Archived/` and the lineage that produced the current files:

| Subsystem | Archived revisions | Current | What changed along the way |
|---|---|---|---|
| 3D LED mapping | `..Vertex_and_Edges..Rev1.0/1.1/1.2`, plus split experiments `..Vertex_LED_Mapping_Rev1.1` (vertices only) and `..Internal_Edges_LED_Mapping_Rev1.2` (edges only) | `..Vertex_and_Edges..Rev1.3` | The combined map went 1.0→1.3; the vertices-only and internal-edges-only pages were interim splits later folded back into the combined page. Edge convention corrected to CCW-from-edge-1 (`e4f3ade`). |
| Media Playback schematic | `Rev1.0`, `Rev2.0`, `Rev2.2` | `Rev3.0` | 1.0 initial ESP32-S3 OSC panel (encoder + 3 buttons, Schmitt + RC debounce) · 2.0 Wi-Fi status LED (GPIO12+R11), R6–R10 100 Ω GPIO protection, keyed JST-XH, KY-040 option · 2.1 required U1 co-located in the panel · 2.2 PCB-layout placeholder + R1/R2/C1/C2 fallback note (no electrical change) · **3.0 W5500 wired Ethernet**. |
| Media Playback firmware | R3.0 (Ethernet only) | **R3.1** (+ Wi-Fi fallback) | FW minor digit tracks feature releases on Rev 3.0 hardware. |
| Media Playback build doc (DOCX) | `..Rev3.0.docx` | `..Rev3.1.docx` | Rev 3.1 added the Quick Reference table and aligned to FW 3.1.0. |
| Scent schematic | `Rev1.0` (2026-05-14) | `Rev2.0` (2026-05-19) | 2.0 removed the 5 V rail (U2/F2/RC1–RC4 deleted), COM bus 5 V → 12 V. |
| Controller box configs | `Rev1.0` | `Rev1.1` | 1.1 applied the audited power corrections (see §4.4). |
| Series coil build | *(demoted, not moved)* "Rev 1.0" → **Rev 0 pre-release** | Rev 0 pre-release | Commit `c8fb4c2` renamed it to signal provisional status; it stays at repo root. |

### 4.3 The `aroma.local` legacy name

The scent firmware and file were renamed **aroma → Scent** (§3.2), but the running system still
answers to the **old** identity: the web UI is at **`http://aroma.local/`** and the Max/UDP scheme
is unchanged. So "Scent Controller" (docs/filenames) and "aroma" (hostname/runtime) refer to the
**same board** — a naming split a new operator would trip over.

### 4.4 Power-figure corrections already applied (Rev 1.0 → Rev 1.1)

The controller-box diagram was audited; these errors were found in the Rev 1.0 diagram and fixed in
Rev 1.1 (Rev 1.0 archived). Recorded here because the corrected values are the ones to trust and
the *old* values may still be quoted from memory or from the archived page:

| # | Item | Was | Corrected |
|---|------|-----|-----------|
| 1 | Cable resistance table | Ω/1000 ft | mΩ/m (3.28× higher) |
| 2 | Strip #1 V-drop | 230 mV → 11.77 V | **754 mV → 11.25 V** |
| 3 | Edge feed V-drop | 53 mV | **175 mV** |
| 5 | "Worst case 53.4 A" | present | **removed** (fabricated 30 mA/px doubling) |
| 6 | Edge per-pixel | 15.8 mA → 26.6 A | **15 mA → 25.2 A** |
| 7 | 12 V rail total | 27.3 A / 28.7 A (conflicting) | **27.1 A** |
| 8 | Scent ESP current | 0.58 A | **0.40 A** |
| 9 | Scent total | 1.18 A | **~1.0 A steady** |
| 12 | ATX load % | 32.9 % | **38.3 % (850 W) / 32.7 % (1000 W)** |

(Full 13-row table with causes: `NaoDec_Power_and_Controller_Box_Report.md` §9.)

### 4.5 Stale-in-place items (documented, not fixed)

These are live inconsistencies in current files. Per the task decision, **none are changed here** —
this is the punch-list.

**README (`README.md`):**
- Links **`XL4015_CC_CV_Mockup_Test_Procedure.md`** (×3) — file does not exist (§3.1).
- Links **`NaoDec_Media_Playback_Controller_Rev3_Ethernet_Rationale.md`** — the actual filename is
  `..._Rev3.0_Ethernet_Rationale.md` (with `.0`). The same old name is also referenced in
  `NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md` and in
  `firmware/media_playback_controller/README.md`.
- Links **`NaoDec_Media_Playback_Controller_Build_and_Max_Setup.docx`** — the actual file is
  `..._Rev3.1.docx`.
- Repo-tree lists **`NaoDec_Media_Playback_Controller_Schematic_Rev1.0.html`** at root ("Previous
  revision (kept for reference)"), but that file is in **`Archived/`**.
- Labels the Build & Max Setup doc **"(Rev 2.2)"** in the repo tree; the file is **Rev 3.1**.
- README repo tree / revisions table **omit** several shipped files: the Scent Controller schematic
  + firmware, the paint comparison note, the `_Rev3.1.docx`, and this document.

**Other files:**
- `firmware/media_playback_controller/README.md` still says the Build & Max Setup doc "is still at
  Rev 3.0 … will be revised to Rev 3.1 as a follow-up" — that follow-up **is already done** (the doc
  is Rev 3.1).
- Controller-box title/label mismatch **both directions**: the current
  `NaoDec_Controller_Box_Configs_Rev1.1.html` carries an internal sub-header reading **"REV 1.0"**,
  while the archived `Archived/NaoDec_Controller_Box_Configs_Rev1.0.html` has a `<title>` of
  **"Rev 1.1"**. (Filenames are correct; the in-page labels are swapped/stale.)
- `CLAUDE.md` Series-Coil "Status notes" are two generations behind the current coil design (§4.1).
- Rev 1.3 changelog line in the LED controller says "SN74HCT245N" vs the authoritative "AHCT"
  elsewhere (§2.1).

---

## 5. Project timeline (condensed)

From the 97-commit history, the decision arc:

1. **Initial uploads** — LED controller schematic + README + 3D vertex/edge mapping (early
   revisions), GitHub Pages auto-index workflow.
2. **Series-coil saga** — added the electromagnet subsystem (`02c3b0a`); discovered the
   DC-near-short / non-magnetic-core problems; added a **CC/CV buck (~3 A)** as the current limiter
   (`53674ac`); spelled out that the fuse goes **before** the buck (`7551e7b`); **bench-measured
   11.68 V / 2.75 A** (`dc0122a`); **demoted the build to Rev 0 pre-release** (`c8fb4c2`); later
   re-modeled to the ~1.85 Ω / 20 AWG / exact-3 A design (README + Vertex Rev 1.0a).
3. **Power & box study** — Controller Box Configs Rev 1.0 → **audited** → Rev 1.1 (`f7ad5f3`);
   full power report Rev 1.0 (`a3f1096`).
4. **Tooling & memory** — vendored the `html-schematic` skill v4.0.0 (`e81107e`); added `CLAUDE.md`
   with the Dark Teal Wire Assignment Table (`2f48b3c`).
5. **Scent controller** — schematic Rev 1.0 → Rev 2.0 (5 V rail removed); firmware **aroma →
   Scent** rename (`bb07f2d`/`c48b8ad`); firmware README (`2f00b2a`).
6. **Media Playback Controller** — schematic Rev 1.0 → 2.0 → 2.1 → 2.2 → **3.0 (W5500 wired
   Ethernet)**; firmware R3.0 (Ethernet) → **R3.1 (Wi-Fi fallback)**; build/setup doc to Rev 3.1;
   Ethernet rationale note; standalone Max tester patch (`8b5c7b4`).
7. **Structure & marking** — dodecahedron face edge-letter marking guide (`327bc44`), CCW edge
   convention fix (`e4f3ade`), interactive marking variant, pure **3D Structure Framework** page,
   face renumbering to match f1–f12 (`1b5c77a`).
8. **Housekeeping** — grouped `index.html` links by document type (`67ac340`, latest).

---

## 6. Quick file map

**Current (root):** `NaoDec_WS2815_LED_Controller_Rev1.6.html` · `NaoDec_3D_Structure_Framework_Rev1.0.html`
· `NaoDec_3D_Vertex_and_Edges_LED_Mapping_Rev1.3.html` · `NaoDec_Face_Edge_Marking_Rev1.0.html` ·
`NaoDec_Face_Edge_Marking_Interactive_Rev1.0.html` · `NaoDec_Series_Coil_Build_Rev0_Pre-Release.html`
· `NaoDec_Vertex_Series_Coil_Rev1.0.html` · `NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html`
· `NaoDec_Scent_Controller_Schematic_Rev2.0.html` · `NaoDec_Controller_Box_Configs_Rev1.1.html` ·
`Simple_WS2815_Controller_Rev_1.0.html`

**Notes (root, Markdown/DOCX):** `README.md` · `CLAUDE.md` · `NaoDec_Power_and_Controller_Box_Report.md`
· `NaoDec_Media_Playback_Controller_Rev3.0_Ethernet_Rationale.md` ·
`NaoDec_Media_Playback_Controller_Build_and_Max_Setup.md` (+ `_Rev3.1.docx`) ·
`Paint_Comparison_Maxzo_RustTech_vs_JBP_SmartGlaze.md` · this file.

**Firmware:** `firmware/media_playback_controller/` (`media_playback_controller_R3.1.ino`,
`TransportReceiveTest1.maxpat.zip`, README) · `firmware/Scent_controller/`
(`Scent_controller_web_R2.0.ino`, README).

**Archived:** prior 3D-mapping, media-playback, scent, and box-config revisions, the Rev 3.0 build
DOCX, and `Note.txt` (placeholder).

**Referenced but missing:** `XL4015_CC_CV_Mockup_Test_Procedure.md` (§3.1).
