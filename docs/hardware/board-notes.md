# Hardware notes: Waveshare ESP32-P4-WIFI6

These are my notes from reading the official Waveshare schematic before writing any code. Knowing every rail, pin and shared bus up front is what keeps later debugging short.

## Power

- USB-C 5V passes through a P-MOSFET power-path switch (Q2, AO3401) to `VCC_5V`.
- An MP1658 buck converter produces the main 3.3V rail (`ESP_3V3`). Its enable is exposed as `EN` on the 40-pin header.
- The P4 core rail (`VDD_HP`) comes from a second buck converter (MP1605), which the P4 switches on itself through its `EN_DCDC` pin.
- Audio has its own clean 3.3V from an RT9193 LDO, separate from the digital rail.
- The P4 internal LDOs supply the flash (VO1) and the microSD card I/O (VO4).

## Clocks

- 40 MHz main crystal.
- 32.768 kHz RTC crystal on GPIO0 and GPIO1, so those two pins are not available.

## Programming and USB

- The USB-C port connects only to a CH343P USB-UART bridge, wired to UART0 (GPIO37 TX, GPIO38 RX).
- DTR and RTS drive EN and BOOT (GPIO35) through a transistor pair, so flashing needs no button presses.
- The P4 high-speed USB OTG PHY goes to the 4-pin `USB` header (V, D-, D+, G).
- GPIO24 and GPIO25 (USB Serial/JTAG) are on the 40-pin header.

## Pin map

| Function | GPIO | Notes |
|---|---|---|
| I2C SDA / SCL | 7 / 8 | Shared by codec, camera, display and header. 2.2K pull-ups on board |
| I2S MCLK / SCLK / LRCK | 13 / 12 / 10 | ES8311 codec |
| I2S ASDOUT (mic data in) | 11 | |
| I2S DSDIN (speaker data out) | 9 | |
| Amplifier enable | 53 | NS4150B, active high, pulled down |
| SD CLK / CMD | 43 / 44 | 4-bit SDMMC |
| SD D0 to D3 | 39 to 42 | |
| SD card power | 45 | P-MOS switch, low means powered (default) |
| C6 SDIO CLK / CMD | 18 / 19 | |
| C6 SDIO D0 to D3 | 14 to 17 | 51K pull-ups |
| C6 reset (CHIP_PU) | 54 | |
| C6 IO2 | 6 | |
| BOOT button | 35 | Strapping pin |
| UART0 TX / RX | 37 / 38 | To the CH343P |

I2C addresses: ES8311 at `0x18`, OV5647 at `0x36`.

## Free GPIOs on the 40-pin header

2, 3, 4, 5, 20 to 33, and 46 to 52, plus test pads for 34 and 36 on the underside. That gives 27 in total.

GPIO34 to GPIO38 are strapping pins. I avoid attaching anything to 34 or 36 that could pull them at reset.

## Camera and display connectors

Both are 22-pin, Raspberry Pi 5 style, 2-lane MIPI. My Raspberry Pi Camera (B) has a 15-pin connector, so it needs a 22-to-15 pin adapter cable.

## ESP32-C6 firmware

The C6 runs ESP-Hosted slave firmware. If the host and slave versions drift apart, Wi-Fi fails to start. To reflash the C6 directly: hold C6 IO9 low at power-up, put the P4 into download mode as well, and flash through the C6 UART pads (RXD, TXD) on header H4.
