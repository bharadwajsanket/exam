# Repository Recommendations & Improvements

This document lists architectural recommendations to modernize the TimberMan repository, improve asset management, automate builds, and provide future laboratory extensions for students.

---

## 1. Directory Structure Reorganization

The current repository layout mixes source code files, compiled binaries, utility files, and asset folders in the root directory. To align with industry standards, the repository should be structured as follows:

```text
TimberMan_Standard/
├── CMakeLists.txt               ← Global CMake build system configuration
├── LICENSE                      ← Repository license agreement
├── README.md                    ← User-facing documentation
├── docs/                        ← Student study guides
│   ├── BUILD.md
│   └── ARCHITECTURE.md
├── include/                     ← Header declarations (.hpp / .h)
│   └── AssetManager.hpp
├── src/                         ← Source code implementations (.cpp)
│   ├── Main.cpp                 ← Game entry point
│   ├── Game.cpp                 ← Game loop orchestrator
│   └── AssetManager.cpp
├── Steps/                       ← Milestone files for step-by-step learning
│   ├── Step1_BlackWindow.cpp
│   └── ...
├── assets/                      ← Asset container
│   ├── fonts/                   ← Typography assets
│   │   └── KOMIKAP_.ttf
│   ├── graphics/                ← Sprites and background textures
│   │   ├── player.png
│   │   └── background.png
│   └── sounds/                  ← Wave audio clips
│       └── chop.wav
└── build/                       ← Compilation output directory (ignored by git)
```

---

## 2. Cross-Platform CMake Build System

To replace hardcoded manual g++ compilation commands, we recommend adding a `CMakeLists.txt` file in the project root. This automates dependency resolution and builds across Linux, macOS, and Windows.

### Recommended `CMakeLists.txt` Template

```cmake
cmake_minimum_required(VERSION 3.12)
project(TimberMan VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find SFML Libraries
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# 2. Add Executable Targets
add_executable(TimberMan src/Main.cpp)

# 3. Include Header Directories
target_include_directories(TimberMan PRIVATE include)

# 4. Link Libraries
target_link_libraries(TimberMan PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# 5. Asset Copying Command
# Automatically copies the assets folder to the build target output directory
add_custom_command(TARGET TimberMan POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TimberMan>/assets
    COMMENT "Copying assets folder to build directory..."
)
```

---

## 3. Asset Management Improvements (Caching)

In the current codebase, textures and font loaders are defined as local variables in `main()`. This approach is hard to maintain in larger projects and makes it easy to accidentally deallocate texture assets.

We recommend creating a centralized, static **`AssetManager`** class. It stores assets in a hash map (`std::unordered_map`) and caches them so that textures are only loaded once.

### Caching Asset Manager Interface

```cpp
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class AssetManager {
private:
    std::unordered_map<std::string, sf::Texture> m_Textures;
    std::unordered_map<std::string, sf::Font> m_Fonts;

    // Singleton instance getter
    static AssetManager* s_Instance;

public:
    AssetManager();
    static AssetManager& Get();

    // Returns texture reference. Loads from disk if not already cached.
    sf::Texture& GetTexture(const std::string& filename);
    
    // Returns font reference. Loads from disk if not already cached.
    sf::Font& GetFont(const std::string& filename);
};
```

---

## 4. Debug & Diagnostics Enhancements

Students often struggle to find layout coordinates when moving sprites or aligning bounding boxes.
- **Visual Bounding Boxes:** Draw outline borders around sprite shapes to help students visualize their colliders.
  ```cpp
  sf::FloatRect bounds = spritePlayer.getGlobalBounds();
  sf::RectangleShape outline(sf::Vector2f(bounds.width, bounds.height));
  outline.setPosition(bounds.left, bounds.top);
  outline.setFillColor(sf::Color::Transparent);
  outline.setOutlineColor(sf::Color::Green);
  outline.setOutlineThickness(2.f);
  window.draw(outline);
  ```
- **Error Handling Validation:** The current code assumes files load successfully. If a file is missing, it prints to standard error but continues running with a blank white box. We recommend adding explicit validations that display helpful error dialogs or terminate the process safely:
  ```cpp
  if (!texture.loadFromFile("graphics/player.png")) {
      throw std::runtime_error("Critical Error: Missing file graphics/player.png");
  }
  ```

---

## 5. Coding Omissions in `Timber.cpp`

During our audit, we identified several bugs in the primary game file `Timber.cpp`:
- **Unused Entities:** `spriteBee` and the cloud variables are declared and drawn, but they are never updated in the game's update loop. This causes the bee and clouds to remain frozen on screen.
- **Log Movement:** The log asset (`graphics/log.png`) is loaded and drawn, but the movement calculations that throw the chopped log off-screen are missing.
- **Resolution:** `TimberTuto.cpp` includes the movement calculations for the bee and clouds, but lacks the audio code and the high score feature present in `Timber.cpp`.

### Fix: Syncing files
Students should be assigned a lab exercise to refactor `Timber.cpp` and merge the missing elements from `TimberTuto.cpp`. Specifically, they should add the update loops for the bee and clouds:

```cpp
// Inside Timber.cpp -> if (!paused) -> update block:
if (!beeActive) {
    beeSpeed = (rand() % 200) + 200;
    float height = (rand() % 500) + 500;
    spriteBee.setPosition(2000, height);
    beeActive = true;
} else {
    spriteBee.move(-beeSpeed * dt.asSeconds(), 0);
    if (spriteBee.getPosition().x < -100) {
        beeActive = false;
    }
}
```

---

## 6. Future Laboratory Assignments & Extensions

To expand the course material, instructors can assign these advanced exercises:

### Assignment A: Frame-by-Frame Animations (Sprite Sheets)
Students replace the static `player.png` with a sprite sheet. Using `sf::IntRect`, they can cycle the rendering viewport to animate the player swinging their axe.

### Assignment B: Particle Systems (Splinter Effects)
Students can implement a simple particle system. When the player chops the tree, it spawns small brown wood splinters that fly off the trunk and fall off-screen using gravity physics.

### Assignment C: State Pattern (Game State Manager)
Replace the simple `paused` boolean flag with a clean State Pattern. This allows students to build separate classes for different game states:
- `MainMenuState` (Start Screen)
- `GameplayState` (Active Chop loop)
- `PauseState` (Overlay screen)
- `GameOverState` (Squished / Timeout display screen)
