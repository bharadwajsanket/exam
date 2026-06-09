# Build & Execution Guide

This document describes how to set up the build environment, compile, run, and troubleshoot the TimberMan SFML game and its step-by-step tutorial milestones.

---

## Ubuntu Setup

To compile C++ and SFML applications on Ubuntu, you must install the GCC compiler (`g++`), the build tools (`make`, `cmake`), and the SFML development files.

### 1. Install Required Packages
Run the following commands in your terminal:

```bash
sudo apt update
sudo apt install -y g++ make cmake libsfml-dev
```

### 2. Verify Installation
Ensure that the tools are available on your system:

```bash
g++ --version
cmake --version
dpkg -l | grep libsfml-dev
```

---

## Compile

The compilation commands link the SFML headers and binary library files.

### Compile the Main Game (`Timber.cpp`)
The main game uses audio, graphics, window, and system modules:

```bash
g++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### Compile Tutorial Steps (`Steps/Step1_BlackWindow.cpp` to `Step6_BranchSystem.cpp`)
The tutorial files do **not** use audio, so the `-lsfml-audio` library flag is not required:

```bash
g++ Steps/Step1_BlackWindow.cpp -o Step1 -lsfml-graphics -lsfml-window -lsfml-system
```
*(Replace `Step1_BlackWindow.cpp` and `Step1` with the respective filenames for other steps.)*

---

## Run

To execute the compiled binary, run it directly from the **project root directory** (where the `graphics/`, `font/`, and `sound/` folders reside):

```bash
./Timber
```

---

## Debugging & Common Issues

During laboratory sessions, students frequently encounter runtime or compilation issues. Below are details on identifying and solving them.

### 1. Wrong Working Directory (Asset Loading Failures)
* **Symptom:** The console prints errors like:
  ```text
  Failed to load image "graphics/background.png"
  Failed to load font "font/KOMIKAP_.ttf"
  Failed to load sound buffer "sound/chop.wav"
  ```
  The window opens but displays a blank black/white window, or the application crashes immediately.
* **Cause:** The compiler/runtime environment ran the program with a Working Directory that is not the project root. SFML looks for asset paths *relative to the current working directory of the process*, not the directory where the binary is located.
* **Solution:** Make sure you compile and run from the folder containing the `graphics/`, `font/`, and `sound/` directories:
  ```bash
  # Check your current directory
  pwd
  # Move to the TimberMan root folder
  cd "/path/to/TimberMan"
  # Run the binary
  ./Timber
  ```

### 2. Missing Shared Libraries (`.so` / `.dll` errors)
* **Symptom (Linux):** 
  ```text
  ./Timber: error while loading shared libraries: libsfml-graphics.so.2.5: cannot open shared object file: No such file or directory
  ```
* **Cause:** The dynamic linker cannot find SFML libraries.
* **Solution:** On Ubuntu, ensure `libsfml-dev` is installed. If compiled manually, add the SFML lib directory to `LD_LIBRARY_PATH`:
  ```bash
  export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
  ```
* **Symptom (Windows):** A dialog appears stating that `sfml-graphics-2.dll`, `sfml-window-2.dll`, etc., are missing.
* **Solution:** Copy the `.dll` files from your SFML installation folder's `bin/` directory directly into the directory containing your compiled `.exe` file.

### 3. Audio Failure
* **Symptom:** Program crashes or fails to compile when adding sounds, or prints:
  ```text
  ALSA lib ... pcm.c:xxx:(snd_pcm_recover) underrun occurred
  An internal OpenAL call failed in SoundBuffer.cpp
  ```
* **Cause:** Missing OpenAL dependencies on Linux, or issues with audio drivers/hardware output devices.
* **Solution:** Install the audio configuration packages:
  ```bash
  sudo apt install -y libopenal1 libsndfile1
  ```

### 4. Display Server Connection (WSL / Virtual Machines)
* **Symptom:** 
  ```text
  Failed to open X11 display; check your $DISPLAY environment variable
  ```
* **Cause:** SFML requires a graphical interface. Running inside headless SSH, docker containers, or WSL 1 without an X11 server causes window creation to fail.
* **Solution:** Ensure you are running WSL 2 with GUI support enabled, or use a virtual machine with a graphical desktop environment. Alternatively, set up an X server (like VcXsrv or Xming on Windows) and configure:
  ```bash
  export DISPLAY=:0
  ```
