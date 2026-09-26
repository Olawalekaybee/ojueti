# Ojueti firmware

ESP-IDF v5.5 project for the ESP32-P4 on the Waveshare ESP32-P4-WIFI6.

```powershell
idf.py set-target esp32p4
idf.py build
idf.py -p COM5 flash monitor
```

## Layout 

| Path | Purpose |
|---|---|
| `main/` | Application entry point and application logic |
| `components/board/` | Pin map and board bring-up. Every GPIO number lives in `board.h` and nowhere else |
| `sdkconfig.defaults` | Project-wide configuration (flash size, PSRAM, chip revision) |

New subsystems (audio, camera, networking, AI) will be added as their own components under `components/`, one per episode.

Before the first build, check the chip revision with `esptool.py --port COMx chip_id` and follow the note in `sdkconfig.defaults`.
