# Development setup on Windows 10

My workstation for this series is an HP OMEN 15 (Intel Core i5-9300H, 16 GB RAM, Windows 10 Pro). I work from the command line and use VS Code as the editor. I don't use the ESP-IDF VS Code extension.

Every command below runs in **PowerShell**.

## 1. Install the prerequisites

```powershell
winget install --id Git.Git -e
winget install --id Python.Python.3.11 -e
winget install --id Microsoft.VisualStudioCode -e
winget install --id GitHub.cli -e
```

Close and reopen PowerShell so the new tools are on the PATH.

## 2. Prepare Git and PowerShell

```powershell
git config --global core.longpaths true
git config --global user.name  "Olawale Kabiru Balogun"
git config --global user.email "you@example.com"
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

Long paths matter because ESP-IDF has deep folder structures. The execution policy lets the ESP-IDF scripts run.

## 3. Install ESP-IDF

I keep ESP-IDF in a short path, `C:\esp`, to stay clear of Windows path-length limits.

```powershell
mkdir C:\esp
git clone -b release/v5.5 --recursive https://github.com/espressif/esp-idf.git C:\esp\esp-idf
cd C:\esp\esp-idf
.\install.ps1 esp32p4
```

## 4. Load ESP-IDF with one command

ESP-IDF needs its environment loaded in every new terminal. I add a shortcut to my PowerShell profile:

```powershell
if (!(Test-Path $PROFILE)) { New-Item -ItemType File -Path $PROFILE -Force }
Add-Content $PROFILE 'function idf { . C:\esp\esp-idf\export.ps1 }'
```

From then on, typing `idf` in any terminal loads the toolchain.

## 5. Speed up builds (recommended)

Windows Defender scans every file the compiler touches, which slows builds noticeably. In an **Administrator** PowerShell:

```powershell
Add-MpPreference -ExclusionPath "C:\esp", "$HOME\.espressif", "$HOME\Projects"
```

Adjust the last path to wherever you keep your repositories.

## 6. Connect the board

Plug the board into the USB-C port. It should appear in Device Manager under **Ports (COM & LPT)**. If it shows as an unknown device instead, install the WCH CH343SER driver from the WCH website.

Then check the chip revision before building anything:

```powershell
idf
esptool.py --port COM5 chip_id
```

If it reports revision v3.x or later, remove the `CONFIG_ESP32P4_SELECTS_REV_LESS_V3=y` line from `firmware/sdkconfig.defaults`. If it reports v1.x, leave it in.

## 7. Clone, build and flash

```powershell
mkdir $HOME\Projects -Force
cd $HOME\Projects
gh auth login
gh repo clone olawalekaybee/ojueti
cd ojueti\firmware

idf
idf.py set-target esp32p4
idf.py build
idf.py -p COM5 flash monitor
```

Press `Ctrl+]` to leave the monitor. The first build takes a few minutes; later builds only recompile what changed.

## 8. Open in VS Code

Launch VS Code from the repository root, in the same terminal, so it inherits the ESP-IDF environment:

```powershell
cd ..
code .
```

After the first build, IntelliSense reads `firmware/build/compile_commands.json`, so code navigation and error highlighting match the real ESP-IDF build exactly.

## Daily workflow

```powershell
idf
cd $HOME\Projects\ojueti
git switch -c ep02-audio          # one branch per episode
cd firmware
idf.py build
idf.py -p COM5 flash monitor
cd ..
git add -A
git commit -m "Add ES8311 microphone capture"
git push -u origin ep02-audio
gh pr create --fill               # CI builds the pull request
```

When an episode is finished and merged:

```powershell
git switch main
git pull
git tag v0.2.0
git push origin v0.2.0            # CI publishes the release with binaries
```

## Creating the repository the first time

If you are starting from these files rather than cloning:

```powershell
cd $HOME\Projects\ojueti
git init -b main
git add -A
git commit -m "Episode 1: project scaffold, board health check and CI"
gh repo create olawalekaybee/ojueti --public --source . --push
git tag v0.1.0
git push origin v0.1.0
```
