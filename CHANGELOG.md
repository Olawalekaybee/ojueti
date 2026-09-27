# Changelog

All notable changes to Ojueti are recorded here. Each release matches one episode of the series.

## [0.1.0] - Episode 1

### Added
- ESP-IDF firmware project for the Waveshare ESP32-P4-WIFI6.
- Board support component with the full pin map from the Waveshare schematic.
- Board health check: firmware version, chip revision, flash and PSRAM size, I2C scan, codec and camera detection, heartbeat.
- GitHub Actions pipeline: build on every push and pull request, release with binaries on every tag.
- Hardware notes, Windows setup guide, series roadmap and Episode 1 content kit.

### Verified on hardware
- Waveshare ESP32-P4-WIFI6, ESP32-P4 revision v1.3 at 360 MHz, built with ESP-IDF v5.5.
- 32 MB flash and 32 MB PSRAM (200 MHz) detected, PSRAM memory test passed.
- ES8311 codec (0x18) and OV5647 camera (0x36) detected on the shared I2C bus.
- Free memory stable across a 9 minute heartbeat run: 573 KB internal, 32,765 KB PSRAM.