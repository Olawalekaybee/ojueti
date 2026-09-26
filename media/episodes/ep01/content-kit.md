# Ojueti | Episode 1 content kit

Everything I need to publish Episode 1 across YouTube, LinkedIn, Instagram and X. Replace the placeholders in square brackets before posting.

---

## YouTube

### Title options

1. Ojueti: An ESP32-P4 Edge AI Device That Sees and Hears | EP1
2. Building Ojueti, an Edge AI Camera and Audio Device on the ESP32-P4 | EP1
3. I'm Building a Camera + Audio AI Device on the ESP32-P4 | EdgeCore Series EP1

### Thumbnail

Board close-up on the left, camera and speaker attached. Right side text: **"EDGE AI | EP1"** with a smaller line **"ESP32-P4 + C6"**.

### Description

In this first episode of my EdgeCore Series, I start building Ojueti, a camera and audio edge-AI device on the Waveshare ESP32-P4-WIFI6. The name comes from two Yoruba words, ojú (eye) and etí (ear), because this device is built to see and hear.

The board combines two Espressif chips. The ESP32-P4 handles compute: a dual-core RISC-V processor with 32 MB PSRAM, a MIPI-CSI camera interface with a hardware ISP, and an H.264 encoder. The ESP32-C6 sits beside it as a wireless co-processor, adding Wi-Fi 6 and Bluetooth 5 over SDIO.

Before writing application code, I go through the schematic block by block, set up a command-line ESP-IDF toolchain on Windows, create the GitHub repository, add a CI/CD pipeline with GitHub Actions, and flash a board health check that verifies the chip, memory, audio codec and camera sensor.

Chapters
00:00 What I'm building
[00:00] The board: ESP32-P4 and ESP32-C6
[00:00] Reading the schematic
[00:00] Toolchain setup on Windows (CLI)
[00:00] Repository structure and VS Code
[00:00] CI/CD with GitHub Actions
[00:00] First flash: board health check
[00:00] What's next

Source code: https://github.com/olawalekaybee/ojueti
Release for this episode: https://github.com/olawalekaybee/ojueti/releases/tag/v0.1.0

Hardware
Waveshare ESP32-P4-WIFI6
Raspberry Pi Camera (B), OV5647
8 ohm 2W speaker

#ESP32P4 #EdgeAI #EmbeddedSystems #ESP32 #IoT

### Recording outline

1. **Hook (30 s).** Show the board with camera and speaker attached. "By the end of this series, this board will see, hear and decide on its own, without the cloud."
2. **The board (2 to 3 min).** Point out the P4, the C6 module, flash, camera and display connectors, mic, speaker header, USB header and TF slot. Explain why the P4 needs the C6: it has no radio of its own.
3. **Schematic walkthrough (4 to 5 min).** Power tree, clocks, programming path, the shared I2C bus, audio chain, SD card power switch, C6 SDIO link. End with the free GPIO count.
4. **Toolchain (4 min).** PowerShell: winget installs, ESP-IDF clone and install, the `idf` shortcut, Defender exclusions, `esptool.py chip_id`.
5. **Repository (3 min).** Walk through the folders. Explain why every pin lives in `board.h` and nowhere else.
6. **CI/CD (3 min).** Show the workflow file, push, the Actions run going green, then tag `v0.1.0` and show the release with binaries.
7. **First flash (3 min).** `idf.py flash monitor`. Read the health report line by line: revision, 32 MB flash, 32 MB PSRAM, codec at 0x18, camera at 0x36, heartbeat.
8. **Close (1 min).** Next episode is audio. Ask viewers what they would build with this board.

---

## LinkedIn

I've started a new build-in-public series. The project is Ojueti, a camera and audio edge-AI device on the ESP32-P4.

The name joins two Yoruba words: ojú (eye) and etí (ear). That is exactly what it is being built to do.

The board is the Waveshare ESP32-P4-WIFI6, and it pairs two Espressif chips:

🔹 ESP32-P4 for compute: dual-core RISC-V, 32 MB PSRAM, MIPI-CSI camera input with a hardware ISP, and H.264 encoding
🔹 ESP32-C6 as a wireless co-processor, adding Wi-Fi 6 and Bluetooth 5 over SDIO

Before writing a single line of application code, I went through the schematic block by block. A few things stood out:

→ The P4 switches on its own core supply through an external buck converter
→ The microSD card I/O runs from one of the P4's internal LDOs, which the driver has to configure
→ One I2C bus is shared by the audio codec, the camera, the display and the expansion header

Mapping this up front is what keeps debugging short later.

Episode 1 covers the schematic, a command-line ESP-IDF setup on Windows, the GitHub repository, and a CI/CD pipeline with GitHub Actions. Every push is built automatically, and every episode ends with a tagged release carrying flashable binaries.

The first firmware is a board health check. It confirms the chip revision, 32 MB flash, 32 MB PSRAM, and that both the audio codec and the camera sensor answer on the bus.

Next episode: the audio path, from microphone capture to speaker playback.

🎥 Video: [YouTube link]
💻 Code: github.com/olawalekaybee/ojueti

If you work on embedded vision or on-device AI, I'd value your input on what you want to see covered.

#EmbeddedSystems #EdgeAI #ESP32 #RISCV #IoT #FirmwareEngineering #BuildInPublic

---

## Instagram

### Carousel (5 slides)

1. Board photo with camera and speaker. Text: **"Building an Edge AI device. EP1"**
2. Close-up of the two chips. Text: **"ESP32-P4 thinks. ESP32-C6 connects."**
3. Schematic crop. Text: **"Read the schematic before the code."**
4. GitHub Actions run, green. Text: **"Every commit built automatically."**
5. Serial monitor health report. Text: **"Codec found. Camera found. We're live."**

### Caption

Episode 1 of my EdgeCore Series is out. 🚀

I'm building Ojueti (ojú + etí: eye and ear), a camera and audio edge-AI device on the ESP32-P4, a board that pairs a dual-core RISC-V processor with an ESP32-C6 for Wi-Fi 6.

This episode: schematic deep dive, command-line toolchain on Windows, GitHub repo, CI/CD, and the first flash.

Full video on YouTube. Link in bio. 🎥

#ESP32 #ESP32P4 #EdgeAI #EmbeddedSystems #Electronics #IoT #RISCV #EngineeringLife #MakersGonnaMake #TechNigeria #BuildInPublic

---

## X (thread)

**1/**
I'm building Ojueti, a camera + audio edge-AI device on the ESP32-P4, in public, one episode at a time.

Ojú + etí: Yoruba for eye and ear.

Episode 1 is live. 🧵

**2/**
The board: Waveshare ESP32-P4-WIFI6.

ESP32-P4 for compute: dual-core RISC-V, 32 MB PSRAM, MIPI-CSI with a hardware ISP, H.264 encoder.

ESP32-C6 alongside it for Wi-Fi 6 and Bluetooth 5, linked over SDIO.

**3/**
I read the schematic before writing code.

The P4 enables its own core supply. The SD card I/O runs from an internal LDO. One I2C bus serves the codec, camera, display and header.

Knowing this early saves hours later.

**4/**
Workflow: ESP-IDF from the command line on Windows, VS Code as the editor, GitHub for source, and GitHub Actions building every commit.

Every episode ends with a tagged release and flashable binaries.

**5/**
First firmware: a board health check.

Chip revision, 32 MB flash, 32 MB PSRAM, and the audio codec and camera sensor both answering on I2C.

**6/**
Next up: audio. Microphone in, speaker out, through the ES8311 codec.

🎥 [YouTube link]
💻 github.com/olawalekaybee/ojueti
