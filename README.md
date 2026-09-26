# Ojueti

**Eyes and ears at the edge.**

![firmware-ci](https://github.com/olawalekaybee/ojueti/actions/workflows/firmware-ci.yml/badge.svg)

Ojueti is a camera and audio edge-AI device built on the Waveshare ESP32-P4-WIFI6. It is part of my **EdgeCore Series**, where I build real embedded products in public, one episode at a time.

The name comes from Yoruba: *ojú* means eye and *etí* means ear. That is the whole idea of the device.

## What I'm building

A small, self-contained device that sees and hears. It captures video through a MIPI-CSI camera, listens through an onboard microphone, runs AI inference on the device itself, and connects over Wi-Fi 6 only when it has something worth reporting.

The goal is useful intelligence at the edge, with no cloud dependency for the core function.

## Hardware

| Part | Role |
|---|---|
| Waveshare ESP32-P4-WIFI6 | Main board |
| ESP32-P4NRW32 | Compute: dual-core RISC-V, 32 MB PSRAM, MIPI-CSI with ISP, H.264 encoder |
| ESP32-C6-MINI-1 | Wi-Fi 6 and Bluetooth 5 co-processor, linked over SDIO |
| ES8311 + NS4150B | Audio codec and speaker amplifier |
| Raspberry Pi Camera (B), OV5647 | Camera, on the 22-pin CSI connector |
| 8 ohm speaker, onboard MEMS mic | Audio output and input |

Pin map, power tree and schematic notes: [docs/hardware/board-notes.md](docs/hardware/board-notes.md).

## Repository structure

```
ojueti/
├── .github/
│   ├── workflows/firmware-ci.yml   Build on every push, release on every tag
│   └── pull_request_template.md
├── .vscode/                        Editor settings (IntelliSense from the real build)
├── firmware/                       ESP-IDF project
│   ├── main/                       Application entry point
│   ├── components/board/           Pin map and board bring-up, all hardware details in one place
│   ├── CMakeLists.txt
│   └── sdkconfig.defaults
├── docs/
│   ├── hardware/board-notes.md     Pin map, power tree and schematic notes
│   ├── reference/                  Links to vendor datasheets and the schematic
│   └── setup/windows-setup.md      Toolchain setup
├── media/
│   ├── episodes/                   Video and social media material, one folder per episode
│   └── roadmap.md                  Episode plan
├── CHANGELOG.md
└── LICENSE
```

## Quick start

I develop on Windows 10 from the command line. Full setup: [docs/setup/windows-setup.md](docs/setup/windows-setup.md).

```powershell
git clone https://github.com/olawalekaybee/ojueti.git
cd ojueti\firmware
idf.py set-target esp32p4
idf.py build
idf.py -p COM5 flash monitor
```

Replace `COM5` with the port your board shows in Device Manager. Press `Ctrl+]` to leave the monitor.

## Project status

- [x] **Episode 1:** schematic review, toolchain, repository, CI/CD, board health check
- [ ] Episode 2: audio pipeline (mic capture and speaker playback)
- [ ] Episode 3: camera pipeline (OV5647, ISP, JPEG)
- [ ] Episode 4: Wi-Fi 6 through the ESP32-C6
- [ ] Episode 5: on-device vision AI
- [ ] Episode 6: on-device audio AI
- [ ] Episode 7: sensor fusion and OTA updates from CI releases
- [ ] Episode 8: enclosure, power and final demo

Full plan: [media/roadmap.md](media/roadmap.md). Release history: [CHANGELOG.md](CHANGELOG.md).

## What the Episode 1 firmware does

On boot, the board prints a health report: firmware version, chip revision, flash and PSRAM size, and free memory. It then scans the shared I2C bus and confirms the audio codec and the camera sensor are both present. After that, a heartbeat logs uptime and free memory every 10 seconds.

## CI/CD

Every push and pull request is built by GitHub Actions in Espressif's official ESP-IDF container. Tagging a commit, for example `v0.1.0`, publishes a GitHub Release with the flashable binaries attached. Each episode ends with a tagged release.

## Follow the build

- YouTube: *link coming with Episode 1*
- LinkedIn: [Balogun Kabiru](https://linkedin.com/in/balogun-kabiru-00b580167)
- Instagram: *link*
- X: *link*

## License

MIT. See [LICENSE](LICENSE).