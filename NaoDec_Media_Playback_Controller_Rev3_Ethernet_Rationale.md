# NaoDec Media Playback Controller — Rev 3.0 Ethernet Change Rationale

**Date:** 2026-07-08
**Schematic:** `NaoDec_Media_Playback_Controller_Schematic_Rev3.0.html`
**Supersedes:** `Rev 2.2` (archived)

This note records **why** Rev 3.0 adds a wired-Ethernet interface (WIZnet W5500)
to the Media Playback Controller, the physical problem that forced the change,
the alternatives that were considered, and the new components the revision
introduces.

---

## 1. Physical setup

- The playback controller (rotary encoder + Play/Pause/Stop buttons + status
  LED) mounts on the **side of a chair**.
- It sends transport/volume commands to a **Mac Mini** running Max/MSP as
  **OSC over UDP**.
- The **ASUS RT-AX1800HP** Wi-Fi router and the Mac Mini live in a metal **ATX
  case**, roughly **6 m** away from the chair. The Mac Mini is on **wired
  Ethernet** to the router; only the controller needs to reach the same LAN.

---

## 2. The problem: a 6 m unbuffered signal run does not work

The original design assumes the ESP32-S3 sits **inside the operator panel**,
with the encoder/button/LED wiring kept short. The schematic wire schedule
rates every panel signal at a **maximum run of ~0.5 m**. These are **unbuffered
3.3 V logic lines** straight into the ESP32 GPIOs.

Running those signals **~6 m** (12× the rated distance) from the chair to an
ESP32 placed in the ATX case causes:

| Signal | Failure at 6 m |
|---|---|
| **Encoder (KY-040 CLK/DT)** | Worst affected. A raw quadrature signal over 6 m of unshielded wire picks up capacitance, cross-talk and EMI → **phantom detents, missed steps, jumpy volume**. |
| **Buttons (Play/Pause/Stop)** | High-impedance lines act as antennas → **phantom presses and missed presses**, worse near the router / switching supplies. |
| **Status LED** | Output; mostly tolerant, minor voltage drop. |
| **Ground / ESD** | Ground-reference offset over distance; the knob is the most-touched, most ESD-exposed part feeding an unprotected GPIO. |

The 100 Ω series resistors (R6–R10) provide ESD/edge protection for **short**
runs, not EMI immunity over metres.

---

## 3. Options considered

### Option 1 — ESP32 in the ATX case + 6 m signal wire to the chair ❌
Puts the fragile **unbuffered logic** on the 6 m run (the failure mode above).
Wi-Fi would be fine (ESP32 next to router), but signal integrity is not.
**Rejected.**

### Option 2 — ESP32 at the chair + Wi-Fi to the router ⚠️
Signal wiring becomes short/clean, but the router's radio is sealed inside a
**metal ATX case**, which acts like a partial Faraday cage and attenuates
2.4 GHz badly. Viable **only** if the router's four external antennas are
routed outside the case. Workable but depends on fixing the enclosure and
leaves the link wireless.

### Option 3 — ESP32 at the chair + **wired Ethernet** to the router ✅ (chosen)
Keep the encoder/button/LED runs short at the chair, and cross the 6 m with a
**Cat6 Ethernet cable** instead of logic wires. Ethernet is designed for 100 m,
so 6 m is trivially reliable, and it removes any dependence on Wi-Fi through the
metal case. This is the belt-and-suspenders choice for a permanent install and
is what **Rev 3.0** implements.

---

## 4. Why Rev 3.0 = wired Ethernet (W5500)

- **Signal integrity:** encoder/buttons stay < 0.5 m from the ESP32; only a
  robust differential Ethernet cable spans the 6 m.
- **Network reliability:** no 2.4 GHz link through a metal case — a wired
  Cat6 run to a router LAN port is unaffected by the enclosure.
- **Minimal disruption:** the OSC-over-UDP contract and the Max patch are
  unchanged; only the transport underneath moves from Wi-Fi to Ethernet.

> The ESP32-S3 has **no built-in Ethernet MAC**, so an SPI Ethernet controller
> (WIZnet **W5500**, which carries its own MAC + PHY + TCP/IP stack) is
> required to give it a wired link.

---

## 5. New components in Rev 3.0

| Ref | Qty | Component | Notes |
|---|---:|---|---|
| **U2** | 1 | **WIZnet W5500 Lite** Ethernet module (SPI, RJ45 with magnetics) | **3.3 V ONLY** — never 5 V. ~150 mA. RJ45 → Cat6 → router LAN. |
| **C6** | 1 | 100 nF X7R ceramic, ≥25 V | Decoupling at the W5500 3V3/GND, placed close to the module. |
| **W2** | 1 | **Cat6** Ethernet cable, ~6 m | Chair (W5500 RJ45) → ASUS RT-AX1800HP LAN port. Cat5e is sufficient; Cat8 is unnecessary (W5500 is 10/100 Mbps). |

Everything else is retained: **U1** ESP32-S3, **ENC1** KY-040, **SW1–SW3**,
**LED1**, **R6–R10** (100 Ω protection), **R11** (330 Ω LED), and the
DNP/optional **R1–R5 / C1–C5** front-end (unchanged).

### W5500 ↔ ESP32-S3 wiring (SPI)

| W5500 pin | ESP32-S3 | Net |
|---|---|---|
| SCLK | GPIO13 | SPI_SCLK |
| MOSI | GPIO14 | SPI_MOSI |
| MISO | GPIO15 | SPI_MISO |
| SCS (CS) | GPIO16 | SPI_SCS |
| INT | GPIO17 | SPI_INT (optional) |
| RST | GPIO18 | SPI_RST (optional) |
| 3V3 | 3V3 | 3.3 V — **not 5 V** |
| GND | GND | common ground |
| RJ45 | — | Cat6 → ASUS router LAN |

### Power

The ESP32 is fed from a local **5 V supply** at the chair (into the board's
5 V/USB input). The board's onboard 3.3 V regulator then powers the W5500 from
its **3V3** pin. A plain Cat6 cable carries **data only** — it does **not**
power the controller (this router has no PoE), so power stays local at the
chair.

---

## 6. Firmware follow-up (not yet done)

The schematic change is hardware-only. The `.ino` still needs the network layer
swapped from **Wi-Fi** to the **W5500 Ethernet** library (SPI on GPIO13–18),
keeping the same OSC/UDP contract and IP scheme. The encoder/button/LED logic
and the Max patch are unaffected.
