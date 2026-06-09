# TimberMan

An educational C++ game repository designed for university Game Programming laboratory courses. The game is based on the classic arcade game "Timber!", built step-by-step using SFML (Simple and Fast Multimedia Library).

---

## Overview

TimberMan is a fast-paced game where the player acts as a lumberjack chopping down an endless tree. The objective is to chop as many segments of the tree as possible while avoiding incoming branches and beating a rapidly draining countdown timer. 

This repository serves as a pedagogical reference, guiding students through the process of building a graphical interactive program from a simple blank window up to a fully layered game with animation, timing systems, branch-generation algorithms, and audio feedback.

---

## Features

- **Double-Buffered Graphical Rendering:** High-resolution sprite layering using GPU-accelerated graphics.
- **Dynamic HUD (Heads-Up Display):** Real-time score indicator, highest score tracking, and status prompt screens.
- **Linear Congruential Generator (LCG) Branch System:** A dynamic branch placement algorithm that shifts branches down like a conveyor belt on each chop, randomly spawning new branch positions.
- **Timer Countdown Bar:** A shrinking rectangle shape that tracks the remaining time. Chops add time with diminishing returns to increase difficulty.
- **Decorative Atmosphere System:** Cloud and bee sprites flying at randomized speeds and altitudes.
- **Spatial Audio Design:** Distinct audio clips for chops, time-outs, and death states.

---

## Controls

The game is controlled entirely via the keyboard:

| Key | Action |
| --- | --- |
| **Enter** | Start or restart the game (from title or game over states) |
| **Left Arrow** | Stand on the left side of the tree and chop |
| **Right Arrow** | Stand on the right side of the tree and chop |
| **Escape** | Close the window (if default OS event mappings are active) |

---

## Technologies

- **Language:** C++ (compatible with C++11 and higher)
- **Framework:** SFML 2.x (Simple and Fast Multimedia Library)
  - **sfml-graphics** (Textures, Sprites, Fonts, Text, RectangleShape)
  - **sfml-window** (RenderWindow, Events, Keyboard Input)
  - **sfml-system** (Vector2f, Clock, Time)
  - **sfml-audio** (SoundBuffer, Sound)
- **Compiler:** GCC / `g++` (Linux), MSVC (Windows), or Clang (macOS)
- **Build System:** CMake (Recommended for cross-platform support)

---

## Folder Structure

```text
TimberMan/
├── README.md                           ← Repository overview and quick start (this file)
├── Timber.cpp                          ← Final game source file (includes audio & high score)
├── TimberTuto.cpp                      ← Reference source file with comments and cloud/bee updates
├── setup.sh                            ← Ubuntu dependency installation script
├── font/                               ← TrueType font files
│   └── KOMIKAP_.ttf                    ← UI font asset
├── graphics/                           ← Sprite image files (.png format)
│   ├── background.png                  ← 1920x1080 background scene
│   ├── tree.png / tree2.png            ← Tree trunk textures
│   ├── branch.png                      ← Tree branch texture
│   ├── player.png                      ← Player sprite sheets/images
│   ├── axe.png                         ← Axe sprite
│   ├── log.png                         ← Flying wood log sprite
│   ├── bee.png                         ← Bee animation obstacle
│   ├── cloud.png                       ← Atmospheric clouds
│   └── rip.png                         ← Player gravestone (death screen)
├── sound/                              ← Waveform audio files (.wav format)
│   ├── chop.wav                        ← Played on keypress (chop)
│   ├── death.wav                       ← Played when squished by branch
│   └── out_of_time.wav                 ← Played when timer reaches zero
├── docs/                               ← Comprehensive educational guides
│   ├── BUILD.md                        ← Compilation and runtime debugging guide
│   ├── TUTORIAL_PROGRESS.md            ← Progressive analysis of lab steps
│   ├── ARCHITECTURE.md                 ← Technical game loop and system architecture
│   ├── EXAM_GUIDE.md                   ← 50+ Viva questions and practical map
│   ├── QUICK_REFERENCE.md              ← 2-minute API and command reference
│   └── REPOSITORY_RECOMMENDATIONS.md   ← Code improvement and extension ideas
└── Steps/                              ← Tutorial milestones (complete runnable programs)
    ├── Step1_BlackWindow.cpp           ← RenderWindow creation and basic loop
    ├── Step2_SpriteLayers.cpp          ← Loading textures and drawing order
    ├── Step3_HUD.cpp                   ← Fonts, Text rendering, and RectangleShape HUD
    ├── Step4_EnterToStart_Timer.cpp    ← sf::Clock timing, pausing, and countdown
    ├── Step5_BeeMovement.cpp           ← Vector movement, random ranges, and resetting
    └── Step6_BranchSystem.cpp          ← enums, arrays, and branch conveyor-shifting
```

---

## How To Build

Make sure you have installed SFML dependencies. On Ubuntu, run `sudo apt install libsfml-dev`.

To compile the final game:
```bash
g++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

To compile a tutorial step:
```bash
g++ Steps/Step1_BlackWindow.cpp -o Step1 -lsfml-graphics -lsfml-window -lsfml-system
```

For detailed platform setup and compilation instructions, read [BUILD.md](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/docs/BUILD.md).

---

## How To Run

Execute the program from the project root directory:
```bash
./Timber
```

---

## Learning Outcomes

Upon studying this repository, students will achieve the following competencies:
1. **Game Loop Understanding:** Structuring standard graphical applications using the Event Poll, Update state, Clear window, Draw layer, and Display buffer pipeline.
2. **GPU Asset Pipelines:** Managing GPU memory via the `sf::Texture` (video memory buffer) and `sf::Sprite` (transformable representation) architecture.
3. **Dynamic Object Management:** Spawning, shifting, and cycling entities dynamically using arrays and standard index shifting algorithms.
4. **Frame-Rate Independence:** Implementing real-world speed values using Delta Time calculations to ensure consistent game speed across machines.
5. **Linear Coordinates & Pivot Points:** Using origins, scale factors, and local bounds to center text and orient rotated assets.

---

## SFML Concepts Demonstrated

- **`sf::RenderWindow` & `sf::VideoMode`:** Creates the desktop window frame and defines pixel bounds.
- **`sf::View`:** Implements screen scaling to maintain a virtual 1920x1080 display space independent of window resize events.
- **`sf::Texture` & `sf::Sprite`:** Decoupled architecture for image processing.
- **`sf::Clock` & `sf::Time`:** High-precision hardware clock timers measuring elapsed seconds.
- **`sf::Text` & `sf::Font`:** Vector font rasterization and visual rendering.
- **`sf::RectangleShape`:** Procedural shape creation, colors, and dynamic resizing.
- **`sf::SoundBuffer` & `sf::Sound`:** Low-latency audio buffer queuing and sample playback.

---

## Screenshots Section Placeholder

> [!NOTE]
> *(Insert dynamic gameplay screenshots here when running the application on your target platform)*
>
> | Title Screen | Gameplay | Game Over (Squished) |
> | --- | --- | --- |
> | *Waiting for Enter* | *Chapping branches left/right* | *Tombstone showing RIP* |
