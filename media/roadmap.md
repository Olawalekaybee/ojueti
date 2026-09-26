# Ojueti roadmap | EdgeCore Series

Each episode delivers one working capability, one tagged release, and one video with matching posts on LinkedIn, Instagram and X.

| Ep | Title | Deliverable | Release |
|---|---|---|---|
| 1 | Board deep dive, setup and CI/CD | Schematic walkthrough, Windows CLI toolchain, repo, GitHub Actions, board health check | v0.1.0 |
| 2 | Giving it ears and a voice | ES8311 codec over I2S, microphone capture, speaker playback, audio level meter | v0.2.0 |
| 3 | Giving it eyes | OV5647 over MIPI-CSI, ISP tuning, JPEG snapshots to the microSD card | v0.3.0 |
| 4 | Getting it online | Wi-Fi 6 through the ESP32-C6 with ESP-Hosted, snapshot served over HTTP | v0.4.0 |
| 5 | Vision AI on the device | Person or face detection running locally on the P4 | v0.5.0 |
| 6 | Audio AI on the device | Wake word or keyword detection running locally | v0.6.0 |
| 7 | Putting it together | Sound or motion triggers vision, event log, OTA updates pulled from CI releases | v0.7.0 |
| 8 | From prototype to product | Enclosure, power budget, final demo and lessons learned | v1.0.0 |

The AI episodes use Espressif's ESP-DL and ESP-SR libraries. I'll confirm model choices once the camera and audio pipelines are measured on real hardware, and I'll share the numbers either way.

## Episode checklist

1. Branch `epNN-topic` from `main`.
2. Build the feature, with the terminal and camera recording.
3. Pull request, CI green, merge.
4. Tag the release.
5. Edit and publish the video.
6. Publish the LinkedIn, Instagram and X posts from that episode's content kit, all linking to the video and the release.
