# Exam & Viva Preparation Guide

This guide compiles common theoretical viva (oral exam) questions and maps typical laboratory exam problems to the TimberMan codebase.

---

## Part 1: Frequently Asked Viva Questions (50 Questions)

### Section A: SFML & Project Basics
1. **What is SFML?**
   * *Answer:* SFML stands for "Simple and Fast Multimedia Library". It is a cross-platform, object-oriented C++ software development library that provides API access to graphics, windowing, audio, network services, and system utilities.
2. **Which SFML headers are used in this project?**
   * *Answer:* `#include <SFML/Graphics.hpp>` handles window drawing, textures, sprites, shapes, and texts. `#include <SFML/Audio.hpp>` provides classes to load sound buffers and play audio clips.
3. **What are the five main modules of SFML?**
   * *Answer:* System, Window, Graphics, Audio, and Network.
4. **Why is `using namespace sf;` used?**
   * *Answer:* It prevents the need to write the scope resolution prefix `sf::` before every SFML class or namespace element (e.g., writing `Sprite` instead of `sf::Sprite`).
5. **What is a virtual view (`sf::View`), and why is it used?**
   * *Answer:* `sf::View` is a 2D camera viewport. It defines a virtual coordinate rectangle (like 1920x1080) that SFML maps to the actual size of the window, preventing game objects from stretching if the window is resized.

---

### Section B: The Game Loop Subsystem
6. **What is a Game Loop?**
   * *Answer:* An infinite loop running continuously while the game window is open. It orchestrates three repeating stages: processing inputs, updating physics/variables, and rendering graphical frames.
7. **What happens if you omit the `window.clear()` call?**
   * *Answer:* The window will not wipe previous frames. Moving objects will leave a trailing trail on the screen (known as screen smearing or ghosting).
8. **What does `window.display()` do?**
   * *Answer:* It swaps the background buffer (where the game is currently drawing) with the visible front buffer on the screen.
9. **Explain "Double Buffering".**
   * *Answer:* A rendering technique that uses two buffers: a front buffer visible on screen, and a back buffer where drawing commands are executed in memory. Swapping them instantly prevents screen tearing and rendering flicker.
10. **What is the typical target framerate of a game loop, and how does it relate to frame rendering?**
    * *Answer:* The standard target is 60 frames per second (FPS), meaning one iteration of the game loop takes roughly 16.67 milliseconds.

---

### Section C: Textures & Sprites
11. **Explain the difference between `sf::Texture` and `sf::Sprite`.**
    * *Answer:* `sf::Texture` is a heavy resource storing raw pixel data in GPU memory. `sf::Sprite` is a lightweight object that references a texture and holds transform properties (position, scale, rotation) to draw it on the screen.
12. **Why shouldn't you reload the same texture file for three different cloud sprites?**
    * *Answer:* Loading the file three times duplicates pixel data in GPU memory, wasting resource bandwidth. The correct approach is to load one `sf::Texture` and bind it to three different `sf::Sprite` objects.
13. **What happens if a texture variable goes out of scope before its sprite is drawn?**
    * *Answer:* The sprite will refer to deallocated GPU memory, resulting in a blank white rectangle on the screen.
14. **How do you set the position of a sprite?**
    * *Answer:* Use the `setPosition(x, y)` method, passing the X (horizontal) and Y (vertical) coordinates as floats.
15. **What is the default position of a newly created sprite?**
    * *Answer:* The top-left corner of the screen: coordinate origin `(0, 0)`.

---

### Section D: Screen Coordinates & Transformations
16. **How does the coordinate system work in SFML?**
    * *Answer:* The coordinate system is 2D, with the origin `(0, 0)` at the **top-left** corner. The positive X-axis goes right, and the positive Y-axis goes down.
17. **What is a sprite's "origin"?**
    * *Answer:* The coordinate pivot point of the sprite. By default, it is the top-left corner `(0, 0)` of the texture.
18. **Why do we modify a sprite's origin using `setOrigin()`?**
    * *Answer:* To change the pivot point for scaling and rotations (e.g., centering the pivot so a branch rotates around its base, or centering text).
19. **How do you rotate a sprite?**
    * *Answer:* Use the `setRotation(angle)` method, passing the rotation angle in degrees clockwise.
20. **How do you scale a sprite down to half its original size?**
    * *Answer:* Use `setScale(0.5f, 0.5f)`.

---

### Section E: Fonts & Text
21. **Which class processes font files, and what format does it load?**
    * *Answer:* `sf::Font`, which load vector font formats such as TrueType Fonts (`.ttf`) or OpenType Fonts (`.otf`).
22. **How do you assign a loaded font to a text object?**
    * *Answer:* Call `text.setFont(font)`.
23. **What is the function of `text.getLocalBounds()`?**
    * *Answer:* It returns a rectangle (`sf::FloatRect`) outlining the width, height, and offsets of the rendered text string.
24. **How do you center a text element horizontally in the middle of a 1920-width screen?**
    * *Answer:* Find the text's width with `getLocalBounds()`, set its origin X to `width / 2.0f`, and then position the text at X coordinate `960.0f`.
25. **Why do we use `std::stringstream` for UI text updates?**
    * *Answer:* It provides an easy way to combine string literals and dynamic numeric variables (like scores) into a single string stream before displaying it.

---

### Section F: Timing & Delta Time
26. **What is Delta Time (dt)?**
    * *Answer:* The elapsed time between the start of the previous frame and the current frame, measured in seconds.
27. **Why is Delta Time critical for movement?**
    * *Answer:* It ensures objects move at the same speed regardless of the computer's rendering performance (framerate independence).
28. **How do you calculate delta time in SFML?**
    * *Answer:* Declare an `sf::Clock` object and call `clock.restart()` at the start of each frame. This returns the elapsed time as an `sf::Time` object.
29. **What is the difference between `sf::Clock` and `sf::Time`?**
    * *Answer:* `sf::Clock` measures elapsed time using hardware counters. `sf::Time` is a data container holding a time value that can be represented in seconds, milliseconds, or microseconds.
30. **How do you convert a time object `dt` into a float representation of seconds?**
    * *Answer:* Call `dt.asSeconds()`.

---

### Section G: Event Handling & Inputs
31. **What is the difference between event polling and real-time input checks?**
    * *Answer:* Event polling (`window.pollEvent`) handles discrete actions like window closes or key releases. Real-time checking (`sf::Keyboard::isKeyPressed`) queries the current state of a key every frame, which is ideal for fluid character movement.
32. **What issue does the `acceptInput` flag solve in TimberMan?**
    * *Answer:* It prevents "rapid-fire" chopping. It ensures that the player must release the chop key before they can chop again.
33. **Which event type detects key releases?**
    * *Answer:* `sf::Event::KeyReleased`.
34. **How do you check if the Left Arrow key is pressed?**
    * *Answer:* Call `sf::Keyboard::isKeyPressed(sf::Keyboard::Left)`.
35. **What happens if you poll events inside an infinite loop without checking `window.pollEvent`?**
    * *Answer:* The operating system will flag the program as "Not Responding" because it is not processing window and system messages.

---

### Section H: Enums & Arrays
36. **Why use an `enum class` instead of integers to represent states?**
    * *Answer:* It improves code readability and type safety, preventing invalid assignments (e.g., using `Side::LEFT` instead of a magic number like `0`).
37. **What is the size of the branch array in this project?**
    * *Answer:* 6 slots, defined by the constant `NUM_BRANCHES = 6`.
38. **Explain the algorithm to shift branches down. Why do we loop backwards?**
    * *Answer:* We shift branch positions down on each chop. We loop backwards (`j = 5` down to `1`) so we don't overwrite the positions of the branches below before copying them.
39. **How is a new branch generated at the top of the tree?**
    * *Answer:* By using `rand() % 5`. A value of `0` spawns a left branch, `1` spawns a right branch, and any other value spawns no branch (`NONE`), giving a 60% chance of a gap.
40. **How are branches visually hidden if their logical position is `Side::NONE`?**
    * *Answer:* Their position coordinates are set way off-screen (e.g., `x = 3000`), making them invisible to the player.

---

### Section I: Sound Systems
41. **What is the difference between `sf::SoundBuffer` and `sf::Sound`?**
    * *Answer:* `sf::SoundBuffer` loads and stores raw sound sample data in system memory. `sf::Sound` is a player object that references a buffer to play, pause, or adjust the pitch of the audio.
42. **Why separate audio buffers from sound players?**
    * *Answer:* Multiple sound sources (e.g., several identical chop sounds playing at once) can share a single sound buffer in memory without reloading the file.
43. **Which file format is used for game audio, and which SFML library flag is required?**
    * *Answer:* WAVE (`.wav`) files are used. Compilation requires the `-lsfml-audio` library flag.
44. **How do you play a sound effect?**
    * *Answer:* Call `sound.play()`.
45. **What is the difference between playing a short sound effect (`sf::Sound`) and streaming long background music (`sf::Music`)?**
    * *Answer:* Short sounds are loaded entirely into memory, while long background music is streamed from the disk on the fly to save RAM.

---

### Section J: Collision, States & Optimization
46. **What is the collision condition in TimberMan?**
    * *Answer:* The game checks if the bottom branch (index 5) matches the player's side: `branchPositions[5] == playerSide`.
47. **How does the game handle player death?**
    * *Answer:* It pauses the updates, hides the player off-screen, displays the tombstone (`spriteRip`) at the player's last position, updates the status message to `"SQUISHED!!"`, and plays the death sound.
48. **How is a cloud initialized when it is marked inactive?**
    * *Answer:* It is assigned a random speed and height, set off-screen to the left (`x = -200`), and marked active to begin moving right.
49. **What does `srand((int)time(0))` do?**
    * *Answer:* Seeds the random number generator using the system time, ensuring the game generates a different sequence of branches, clouds, and bees on every run.
50. **How does the game check if the bee has flown off-screen to the left?**
    * *Answer:* It checks if the bee's X coordinate is less than `-100`: `spriteBee.getPosition().x < -100`.

---

## Part 2: Practical Lab Question Mapping

This section maps common exam and laboratory tasks to the implementation patterns in the TimberMan project.

### 1. Rendering Text (Scores & Overlays)
* **Goal:** Render a text string on the screen using a custom font.
* **Code Reference:** Look at `Timber.cpp` lines 131–160.
* **Implementation Pattern:**
  1. Load font: `font.loadFromFile("path/to/font.ttf")`
  2. Bind font to text: `text.setFont(font)`
  3. Set properties: `setFillColor()`, `setCharacterSize()`, `setPosition()`
  4. Display the text in the draw block: `window.draw(text)`

### 2. Moving Sprites (The Bee & Clouds)
* **Goal:** Move a sprite across the screen at a constant speed.
* **Code Reference:** Look at `TimberTuto.cpp` lines 413–415 (clouds) and lines 525–529 (bee).
* **Implementation Pattern:**
  ```cpp
  // Move using speed and delta time
  sprite.move(speedX * dt.asSeconds(), speedY * dt.asSeconds());
  ```

### 3. Handling Keyboard Input (Chopping)
* **Goal:** Detect keypresses to trigger actions (like moving left/right).
* **Code Reference:** Look at `Timber.cpp` lines 234–273.
* **Implementation Pattern:**
  1. Check key state: `sf::Keyboard::isKeyPressed(sf::Keyboard::Left)`
  2. Implement an input buffer flag (`acceptInput`) to prevent repeat actions from holding down the key.
  3. Reset the input flag when the key is released: `event.type == sf::Event::KeyReleased`.

### 4. Countdown Timers & Progress Bars (Health/Timer Bar)
* **Goal:** Implement a timer bar that shrinks over time.
* **Code Reference:** Look at `Timber.cpp` lines 161–171 (setup) and lines 220–232 (update).
* **Implementation Pattern:**
  1. Set up an `sf::RectangleShape` at a fixed coordinate position.
  2. Every frame, subtract the elapsed time: `timeRemaining -= dt.asSeconds()`.
  3. Update the bar's size: `timeBar.setSize(sf::Vector2f(scaleFactor * timeRemaining, height))`.
  4. Trigger game over when `timeRemaining <= 0.0f`.

### 5. Managing Arrays & Object Shifting (Branch Conveyor Belt)
* **Goal:** Implement an array-shifting algorithm (like shifting obstacle queues or trail effects).
* **Code Reference:** Look at `Timber.cpp` lines 16–29 (update branches function) and lines 97–110 (initial setup).
* **Implementation Pattern:**
  1. Set up logical arrays (`enum` arrays) alongside visual representation arrays (`sf::Sprite` arrays).
  2. Iterate backwards through the array (`size - 1` down to `1`) to copy states:
     ```cpp
     for (int j = size - 1; j > 0; j--)
         array[j] = array[j - 1];
     ```
  3. Spawn a new random element at index `0`.

### 6. Sprite Animation & State Flipping (Branch Rotations)
* **Goal:** Flip or rotate a sprite cleanly around a specific pivot point.
* **Code Reference:** Look at `Timber.cpp` lines 308–320 (draw synchronization loop).
* **Implementation Pattern:**
  1. Offset the origin to the pivot point: `sprite.setOrigin(pivotX, pivotY)`.
  2. Adjust position and rotate: `sprite.setRotation(180)` to flip the sprite, or `sprite.setRotation(0)` to keep it normal.

### 7. Sound Effect Triggers (Chop/Death Audio)
* **Goal:** Play a low-latency sound effect when an action occurs.
* **Code Reference:** Look at `Timber.cpp` lines 118–130 (setup) and lines 231, 252, 271, 291 (triggers).
* **Implementation Pattern:**
  1. Load sound buffer: `buffer.loadFromFile("sound.wav")`.
  2. Bind buffer to sound player: `sound.setBuffer(buffer)`.
  3. Trigger the sound when an action occurs: `sound.play()`.
