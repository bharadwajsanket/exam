# Game Architecture & System Design

This document details the software architecture, execution pipeline, and sub-systems of the TimberMan game built using C++ and SFML.

---

## 1. The Game Loop Pipeline

TimberMan follows the standard real-time game simulation architecture. The main execution thread runs an infinite loop that processes input events, updates object parameters based on elapsed time, clears the screen, draws graphical objects in a layered order, and displays them.

### Game Loop Workflow Diagram

```text
       +---------------------------------------------+
       |             Initialization Phase            |
       |  - Load fonts, textures, sound buffers      |
       |  - Initialize Sprites, Positions & origins  |
       |  - Pre-populate branches (update 5 times)   |
       +---------------------------------------------+
                              |
                              v
        ================== GAME LOOP ==================
       /  while (window.isOpen())                      \
      +-------------------------------------------------+
      |                                                 |
      |   1. INPUT PHASE                                |
      |      - Iterate through sf::Event queue          |
      |      - Capture window close & Enter presses     |
      |                                                 |
      +-------------------------------------------------+
                              |
                              v
      +-------------------------------------------------+
      |   2. UPDATE PHASE (runs only if !paused)        |
      |      - Calculate Delta Time (dt = clock.restart)|
      |      - Decrement timer: timeRemaining -= dt     |
      |      - Scale HUD time bar width                 |
      |      - Update entity positions: bee, clouds     |
      |      - Process Keyboard input (Left/Right arrow)|
      |      - Shift branches & evaluate Squish Collision|
      +-------------------------------------------------+
                              |
                              v
      +-------------------------------------------------+
      |   3. RENDER PHASE                               |
      |      - window.clear() (fill with black)         |
      |      - Render layered sprites (painter's order) |
      |      - Render HUD text & overlays (if paused)   |
      |      - window.display() (swap buffer display)   |
      +-------------------------------------------------+
      |                                                 |
       \===============================================/
```

---

## 2. Core Game Subsystems

### Initialization Phase
Before the game loop starts, the program:
1. Seeds the random number generator using system epoch time: `srand((int)time(0))`.
2. Creates the `sf::RenderWindow` frame and attaches a virtual `sf::View` mapped to a static resolution of 1920x1080.
3. Loads all binary textures, audio files, and true-type font assets from disk to GPU memory.
4. Spatially positions static layout components (background, tree trunk, HUD indicators).
5. Pre-populates the branch queue array by executing the shifting function five times, keeping the bottom slot (index 5) empty for player safety on startup.

---

### Input Phase
Input is captured in two ways:
- **Event Polling (`window.pollEvent`):** Best for discrete, one-time actions such as window closing or menu selection (e.g., pressing **Enter** to start). This prevents actions from repeating if a key is held down.
- **Real-Time Keyboard Querying (`sf::Keyboard::isKeyPressed`):** Checked during the update loop. This is best for real-time player actions (e.g., holding Left/Right to chop). To prevent rapid, uncontrolled chopping, an `acceptInput` flag is set to `false` immediately upon keypress and only reset to `true` when an `sf::Event::KeyReleased` event is received.

---

### Update Phase
If the game state is active (`!paused`), the update system runs:
1. **Delta Time Calculation:** Measures how long the previous frame took.
2. **Atmosphere Updates:** Moves clouds and bees across the screen, resetting them when they fly off-screen.
3. **Timer Depletion:** Decreases `timeRemaining` by `dt` and updates the size of the progress bar shape.
4. **Collision Check:** Compares the branch position logic against the player side.

---

### Render Phase
To prevent display flickering, SFML uses double buffering. All drawing operations are rendered to an off-screen buffer. Once drawing is complete, `window.display()` swaps this buffer to the screen.

The draw order follows the **Painter's Algorithm** (bottom-to-top stacking):
1. **Background Layer:** `spriteBackground` (fills screen).
2. **Atmospheric Midground Layer:** Clouds and Bee.
3. **Structure Layer:** `spriteTree` trunk.
4. **Interactive Layers:** Tree branches (`branches[0]` to `branches[5]`).
5. **Character Layer:** `spritePlayer` (or the `spriteRip` gravestone on death) and the `spriteAxe`.
6. **UI Layer:** Score text, high score indicators, timer bar, and the game over/start overlays.

---

## 3. Subsystem Design Details

### Asset Loading
Assets are loaded from disk using relative paths:
- Textures: `graphics/background.png`, `graphics/tree.png`, `graphics/bee.png`, etc.
- Fonts: `font/KOMIKAP_.ttf`.
- Audio: `sound/chop.wav`, `sound/death.wav`, `sound/out_of_time.wav` (using `sf::SoundBuffer` and `sf::Sound`).

---

### Timer System
The countdown timer starts at `6.0` seconds. As the game updates:
- Time is subtracted: `timeRemaining -= dt.asSeconds()`.
- The time bar width is updated:
  $$\text{Width} = \frac{\text{Starting Width (400px)}}{\text{Initial Time (6.0s)}} \times \text{timeRemaining}$$
- Each successful chop adds time, but the bonus decreases as the score increases:
  $$\text{Bonus} = \left(\frac{2}{\text{score}}\right) + 0.15\text{ seconds}$$
  *(Note: `2 / score` uses integer division in C++, yielding `2` for score 1, `1` for score 2, and `0` for score 3 or higher. This provides a buffer early on and a flat `+0.15s` bonus as the game progresses.)*

---

### Score System
- The score tracks the number of successful chops and starts at `0`.
- On each chop, the score increments by `1`.
- When the player dies or runs out of time, the current score is compared to the `highestScore`. If the score is higher, the high score is updated:
  ```cpp
  if (score > highestScore)
      highestScore = score;
  ```
- Score displays are updated by passing the values to an `std::stringstream` and converting them to strings:
  ```cpp
  std::stringstream ss;
  ss << "Score = " << score;
  scoreText.setString(ss.str());
  ```

---

### Branch System
The branch system represents the tree slots using two arrays of size `6` (index `0` is the top, index `5` is the bottom chop zone):
1. `Side branchPositions[6]`: Tracks where each branch is (`LEFT`, `RIGHT`, or `NONE`).
2. `sf::Sprite branches[6]`: The visual sprite for each branch.

#### Conveyor-Shift Queue Design
When a player chops, the branches shift down one level. The branch at index `5` is discarded, and a new random branch is generated at index `0`:

```text
Branch Array Shift Sequence:

  [0] New Random (LEFT/RIGHT/NONE) 
  [1] Was [0] <-----+
  [2] Was [1] <---+ |  Downward Shift
  [3] Was [2] <-+ | |  (j = 5 down to 1)
  [4] Was [3] <-+ | |
  [5] Was [4] <---+ |
  [ ] Was [5] ------+--> Discarded (Chop Zone)
```

To flip the branch sprites correctly, their origin is offset to `(220, 20)`. Rotating a branch by `180` degrees flips it to the left side while keeping it connected to the trunk at the same attachment point.

---

### Player System
The player has two states represented by the `Side playerSide` enum:
- **Left Side:** Player positioned at `(580, 720)`, axe at `(700, 830)`.
- **Right Side:** Player positioned at `(1200, 720)`, axe at `(1075, 830)`.

---

### Death Conditions
At the end of the update phase, the game checks if the bottom branch (index `5`) matches the side the player is standing on:

$$\text{Collision State} = (\text{branchPositions}[5] == \text{playerSide}) \land (\text{branchPositions}[5] \neq \text{Side::NONE})$$

If this condition is met:
1. The game is paused: `paused = true`.
2. Input is disabled: `acceptInput = false`.
3. The player sprite is hidden off-screen: `spritePlayer.setPosition(2000, 720)`.
4. The `spriteRip` tombstone is placed at the player's last position (`(600, 720)` on the left, or `(1150, 720)` on the right).
5. The death sound is played: `deathSound.play()`.
6. The status text is updated to `"SQUISHED!!"`.
