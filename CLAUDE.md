# CLAUDE.md — NaoDec

Project memory for the **NaoDec** 7-channel WS2815 LED installation (1,740 px) — dual
ESP32-S3-WROOM-1 running WLED in master/slave DDP, 3.3 V → 5 V via an SN74AHCT245N.
Docs are self-contained interactive HTML schematics (browse: https://surasaknie.github.io/naodec/).

## Wire Assignment Table

| wdata channel | Hex     | Assigned to (GPIO / bus) |
|---------------|---------|--------------------------|
| wdata         | #88e2d6 | CH1                      |
| wdata2        | #ffffff | CH2                      |
| wdata3        | #7cb3ff | CH3                      |
| wdata4        | #c8a2e8 | CH4                      |
| wdata5        | #f0997b | CH5                      |
| wdata6        | #97c459 | CH6                      |
| wdata7        | #f0d060 | CH7                      |

**Binding** for the `html-schematic` skill (VR9 net-color rule). The Net Color Allocator,
Wire Router, and Style Validator MUST read this table at session start and never reassign a
channel listed here. Hex values are the **Dark Teal** palette, matching the existing
Rev-series schematics in this repo — keep new/revised schematics on that theme so colors
stay consistent.

> Power rails are fixed (not reassignable): `w12v` `#eaddaa` "12V" · `w5v` `#c9a86a` "5V" ·
> `w3v3` `#a28854` "3.3V" · `wgnd` `#4a6b6d` "GND".

## Channel reference (full mapping)

Source: README hardware tables + `NaoDec_WS2815_LED_Controller_Rev1.6.html`.

| CH  | wdata class | Strip      | GPIO (board)   | Buffer    | LEDs |
|-----|-------------|------------|----------------|-----------|------|
| CH1 | wdata       | #1 Vertex  | GPIO1 (Master) | U2 A1→B1  | 60   |
| CH2 | wdata2      | #2 Edge A  | GPIO4 (Master) | U2 A2→B2  | 280  |
| CH3 | wdata3      | #3 Edge B  | GPIO5 (Master) | U2 A3→B3  | 280  |
| CH4 | wdata4      | #4 Edge C  | GPIO6 (Master) | U2 A4→B4  | 280  |
| CH5 | wdata5      | #5 Edge D  | GPIO4 (Slave)  | U2 A5→B5  | 280  |
| CH6 | wdata6      | #6 Edge E  | GPIO5 (Slave)  | U2 A6→B6  | 280  |
| CH7 | wdata7      | #7 Edge F  | GPIO6 (Slave)  | U2 A7→B7  | 280  |

Theme reference: `.claude/skills/html-schematic/reference/themes/Color-Palette_Dark-Teal-theme.md`.
