# Ojueti

![firmware-ci](https://github.com/olawalekaybee/ojueti/actions/workflows/firmware-ci.yml/badge.svg)

**Ojueti** is a camera and audio edge-AI device built on the Waveshare ESP32-P4-WIFI6. The name joins two Yoruba words, *ojú* (eye) and *etí* (ear), because the device is built to see and hear, then decide on its own.

It is part of my **EdgeCore Series**, where I build real embedded products in public, one episode at a time.

## What I'm building

A small, self-contained device that captures video through a MIPI-CSI camera, listens through an onboard microphone, runs AI inference on the device itself, and connects over Wi-Fi 6 only when it has something worth reporting.

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

Pin map and schematic notes: [docs/hardware/board-notes.md](docs/hardware/board-notes.md)

## Repository structure

```
ojueti/
├── .github/
│   └── workflows/
│       └── firmware-ci.yml        Build on every push, release on every tag
├── .vscode/                       Editor settings shared with the repo
├── docs/
│   ├── hardware/
│   │   └── board-notes.md         Power tree, pin map, schematic findings
│   ├── setup/
│   │   └── windows-setup.md       Command-line toolchain on Windows 10
│   └── reference/
│       └── README.md              Links to the schematic, datasheet and TRM
├── firmware/                      ESP-IDF project root
│   ├── CMakeLists.txt
│   ├── sdkconfig.defaults
│   ├── main/
│   │   ├── CMakeLists.txt
│   │   └── app_main.c             Application entry point
│   └── components/
│       └── board/                 Pin map and board bring-up, the only place GPIOs are defined
│           ├── CMakeLists.txt
│           ├── board.c
│           └── include/
│               └── board.h
├── media/
│   ├── roadmap.md                 Episode plan for the series
│   └── episodes/
│       └── ep01/
│           └── content-kit.md     YouTube, LinkedIn, Instagram and X material
├── .clang-format
├── .gitignore
├── CHANGELOG.md
├── LICENSE
└── README.md
```

Firmware, documentation and series content each have their own top-level folder, so the repository can grow into hardware (enclosure, carrier board) and tooling later without mixing concerns.

## Quick start

I develop on Windows 10 from the command line. The full setup is in [docs/setup/windows-setup.md](docs/setup/windows-setup.md).

```powershell
git clone https://github.com/olawalekaybee/ojueti.git
cd ojueti\firmware
idf.py set-target esp32p4
idf.py build
idf.py -p COM5 flash monitor
```

Replace `COM5` with the port shown in Device Manager. Press `Ctrl+]` to leave the monitor.

## Project status

- [x] **Episode 1:** schematic review, toolchain, repository, CI/CD, board health check
- [ ] Episode 2: audio pipeline
- [ ] Episode 3: camera pipeline
- [ ] Episode 4: Wi-Fi 6 through the ESP32-C6
- [ ] Episode 5: on-device vision AI
- [ ] Episode 6: on-device audio AI
- [ ] Episode 7: sensor fusion and OTA updates
- [ ] Episode 8: enclosure, power and final demo

Full plan: [media/roadmap.md](media/roadmap.md)

## CI/CD

Every push and pull request builds the firmware in Espressif's official ESP-IDF container. Pushing a tag such as `v0.1.0` publishes a GitHub Release with the flashable binaries attached. Each episode ends with a tagged release.

## Follow the build

- YouTube: *link coming with Episode 1*
- LinkedIn: [Balogun Kabiru](https://linkedin.com/in/balogun-kabiru-00b580167)
- Instagram: *link*
- X: *link*

## License

MIT. See [LICENSE](LICENSE).
