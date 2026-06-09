# Practical Laboratory Question Bank

This document compiles 75 practical laboratory exam questions based on the TimberMan project. Each entry details the topic, difficulty level, source file dependencies, corresponding snippet sections, and the modifications required to solve the task.

---

## Category A: Window Setup & Views (Questions 1–5)

### 1. Window Resolution Resize
* **Topic:** Window Settings
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Snippet Section:** 1. Window Creation
* **Modification Required:** Change the `VideoMode` resolution values inside `main()` from `(1920, 1080)` to standard HD size `(1280, 720)`.

### 2. Title Bar Modification
* **Topic:** Window Settings
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Snippet Section:** 1. Window Creation
* **Modification Required:** Modify the string parameter inside the `RenderWindow` constructor from `"Timber Game!!!"` to `"Lab Exam: TimberMan"`.

### 3. Aspect-Ratio Adjusting Viewport
* **Topic:** View Settings
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Snippet Section:** 1. Window Creation
* **Modification Required:** Alter the `sf::View` initialization bounds from `(0, 0, 1920, 1080)` to `(0, 0, 800, 600)` to scale the coordinate area down to SVGA dimensions.

### 4. Enable Window Framerate Limit
* **Topic:** Performance Optimization
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Snippet Section:** 1. Window Creation
* **Modification Required:** Call the window method `window.setFramerateLimit(60);` right after creation to cap CPU and GPU usage.

### 5. Disable/Enable Vertical Sync
* **Topic:** Performance Optimization
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Snippet Section:** 1. Window Creation
* **Modification Required:** Call the method `window.setVerticalSyncEnabled(true);` to sync rendering frames with the monitor refresh rate.

---

## Category B: Textures & Sprites (Questions 6–15)

### 6. Background Image Swap
* **Topic:** Texture Loading
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 2. Texture Loading
* **Modification Required:** Change the file loader path `"graphics/background.png"` to load a new texture file `"graphics/background2.png"` (if available) or another valid asset path.

### 7. Sprite Position Relocation
* **Topic:** Sprite Formatting
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 3. Sprite Creation
* **Modification Required:** Change `spritePlayer.setPosition(580, 720);` to `(480, 720)` to shift the player further left.

### 8. Sprite Scale Modification
* **Topic:** Sprite Formatting
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 3. Sprite Creation
* **Modification Required:** Apply `spriteAxe.setScale(1.5f, 1.5f);` to enlarge the weapon sprite in the game scene.

### 9. Sprite Rendering Order Reversal
* **Topic:** Rendering Stacks
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 13. The Game Loop Structure
* **Modification Required:** Move the line `window.draw(spriteBackground);` to compile *after* `window.draw(spriteTree);` and observe how the background covers the tree.

### 10. Load a Second Tree Sprite
* **Topic:** Asset Replicas
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 2. Texture Loading & 3. Sprite Creation
* **Modification Required:** Instantiate a second tree sprite (`spriteTree2`) using `textureTree` and place it at `(1200, 0)` so there are two trees in the background.

### 11. Color Tinting the Player Sprite
* **Topic:** Visual Rendering
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 3. Sprite Creation
* **Modification Required:** Apply a red tint to the player character using `spritePlayer.setColor(Color::Red);`.

### 12. Retrieve Sprite Position Coordinates
* **Topic:** Coordinates & Logging
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 3. Sprite Creation
* **Modification Required:** Access player coordinates via `spritePlayer.getPosition().x` and `spritePlayer.getPosition().y` and output them to the console.

### 13. Load Texture from Sub-directory
* **Topic:** File Resolution
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 2. Texture Loading
* **Modification Required:** Create a new folder `graphics/env` and move `cloud.png` there, then update `textureCloud.loadFromFile("graphics/env/cloud.png");`.

### 14. Check Load Failures (Robust Loading)
* **Topic:** Code Safety
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 2. Texture Loading
* **Modification Required:** Wrap `loadFromFile` in an `if` block, print an error message to `std::cerr`, and return `-1` if it fails.

### 15. Flip Sprite Horizontally (Scale inversion)
* **Topic:** Transformations
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Snippet Section:** 3. Sprite Creation
* **Modification Required:** Flip the player sprite to face left by inverting the X scaling factor: `spritePlayer.setScale(-1.0f, 1.0f);` and offset the origin to compensate.

---

## Category C: Fonts & Text Rendering (Questions 16–25)

### 16. Change Font File
* **Topic:** Fonts
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 4. Font Loading
* **Modification Required:** Change `font.loadFromFile("font/KOMIKAP_.ttf")` to point to a standard system font like `arial.ttf`.

### 17. Modify Text Color
* **Topic:** Typography
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 5. Text Rendering
* **Modification Required:** Change the font color of `scoreText` from `sf::Color::Red` to `sf::Color::Blue`.

### 18. Adjust Text Character Size
* **Topic:** Typography
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 5. Text Rendering
* **Modification Required:** Change the character size of `messageText` from `75` pixels to a smaller `45` pixels.

### 19. Display Student Details on HUD
* **Topic:** HUD UI
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 5. Text Rendering
* **Modification Required:** Create a new `sf::Text` object that renders your student registration number in the top-right corner.

### 20. Align Text to Bottom-Right
* **Topic:** Coordinates
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 5. Text Rendering
* **Modification Required:** Center the text origin, retrieve its width using `getLocalBounds()`, and position it at coordinates `(1900 - width, 1000)`.

### 21. Add Shadow Effect to Score
* **Topic:** Typography Effects
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 5. Text Rendering
* **Modification Required:** Create a duplicate `scoreShadow` text object that has a black font color and is offset by `(5, 5)` pixels behind `scoreText`.

### 22. Dynamically Render Score with Stringstream
* **Topic:** String Streams
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 5. Text Rendering
* **Modification Required:** Use an `std::stringstream` inside the game loop to display: `"Active Score: [Score Value]"`.

### 23. Add Text Outlines
* **Topic:** Typography
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 5. Text Rendering
* **Modification Required:** Apply an outline to `messageText` using `setOutlineColor(Color::Black);` and `setOutlineThickness(3.0f);`.

### 24. HUD Shape Color Shift
* **Topic:** HUD Shapes
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Change the fill color of the timer bar shape from `Color::Red` to `Color::Green`.

### 25. Position Timer Bar at the Top
* **Topic:** Coordinates
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Change `timeBar.setPosition(760, 980);` to `(760, 50)` to move the timer bar to the top-center of the screen.

---

## Category D: Input Systems & Event Loop (Questions 26–35)

### 26. Escape Key to Exit
* **Topic:** Keyboard Event Handling
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** Add a check inside `window.pollEvent` to call `window.close();` when `event.key.code == Keyboard::Escape`.

### 27. Spacebar to Start the Game
* **Topic:** Keyboard Event Handling
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** Replace the key detection trigger `Keyboard::Enter` with `Keyboard::Space` to start/pause the game.

### 28. Pause Toggle Key
* **Topic:** Event Handling
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** Add a check inside the event loop for a key press event (e.g., `Keyboard::P`) that toggles the `paused` flag: `paused = !paused;`.

### 29. Mouse Click Coordinate Tracker
* **Topic:** Mouse Input
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 7. Mouse Input
* **Modification Required:** Detect mouse press events in the event loop and print the click coordinates to the console:
  ```cpp
  if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
      printf("Click at: %d, %d\n", event.mouseButton.x, event.mouseButton.y);
  }
  ```

### 30. Capture Key Releases for Dynamic Axe Hiding
* **Topic:** Event Handling
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** In the event loop, check if `event.type == Event::KeyReleased`. When a key is released, reset the input flag and move the axe sprite off-screen.

### 31. WSAD Chopping Control Mappings
* **Topic:** Keyboard Input
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** Change the real-time chopping check from `Keyboard::Left` to `Keyboard::A` and `Keyboard::Right` to `Keyboard::D`.

### 32. Keypress Action Event Trigger
* **Topic:** Event Handling
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** Print a debug log `"Key Pressed!"` to the console whenever `event.type == Event::KeyPressed` is detected.

### 33. Frame Cycle Debug Tracker
* **Topic:** Performance Monitoring
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Snippet Section:** 13. The Game Loop Structure
* **Modification Required:** Increment a `frameCounter` integer variable at the end of the game loop and print the total frame count every time it reaches a multiple of 100.

### 34. Close Window on Focus Loss
* **Topic:** Focus States
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Snippet Section:** 13. The Game Loop Structure
* **Modification Required:** Add a check in the event loop: `if (event.type == Event::LostFocus) window.close();` to close the game if the user alt-tabs or focuses on another window.

### 35. Mouse Button Collision Trigger
* **Topic:** Mouse Input
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 7. Mouse Input
* **Modification Required:** Check if the player clicked inside a rectangle region at the bottom-center of the screen to start the game.

---

## Category E: Clocks, Timing & Delta Time (Questions 36–45)

### 36. Speed Up Timer Countdown
* **Topic:** Timing
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Double the countdown rate by multiplying delta time by 2: `timeRemaining -= dt.asSeconds() * 2;`.

### 37. Modify Initial Game Time Limit
* **Topic:** Timing
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Increase the starting time limit from `6.0f` seconds to `12.0f` seconds, and update the time bar scale factor accordingly.

### 38. Calculate and Print FPS to Console
* **Topic:** Timing
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Calculate the frames per second using delta time (`float fps = 1.0f / dt.asSeconds();`) and print the result to the console every second.

### 39. Pause Cloud Speed Movement
* **Topic:** Movement
* **Difficulty:** Medium
* **Related Source File:** [TimberTuto.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/TimberTuto.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Freeze cloud movement when the game is paused by only updating cloud positions if `!paused`.

### 40. Custom Decrement Timer
* **Topic:** Timing
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Make the timer shrink faster as the score increases:
  ```cpp
  timeRemaining -= dt.asSeconds() * (1.0f + (score * 0.05f));
  ```

### 41. Increment Time Bonus on Chop
* **Topic:** Timing
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** Change the time bonus formula inside the left/right arrow press handlers to add a flat `+0.5f` seconds on every chop.

### 42. Cap Maximum Timer Bar Width
* **Topic:** Timing
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Clamp `timeRemaining` so it cannot exceed the starting limit of 6 seconds:
  ```cpp
  if (timeRemaining > 6.0f) timeRemaining = 6.0f;
  ```

### 43. Display Elapsed Game Duration
* **Topic:** Timing
* **Difficulty:** Hard
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Create a secondary clock to track the total time elapsed since the game started, and display this value on the HUD.

### 44. Slow Down Atmospheric Elements
* **Topic:** Movement
* **Difficulty:** Easy
* **Related Source File:** [TimberTuto.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/TimberTuto.cpp)
* **Snippet Section:** 9. Random Number Generation
* **Modification Required:** Reduce cloud movement speeds by multiplying their velocities by `0.5f` in the update loop.

### 45. Game Frame Freeze Delay
* **Topic:** Timing
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Snippet Section:** 8. Timer System
* **Modification Required:** Introduce a sleep delay of `10` milliseconds at the end of each frame using `sf::sleep(sf::milliseconds(10));` to test the game loop's response to lower framerates.

---

## Category F: Random Numbers & Ranges (Questions 46–52)

### 46. Seed Random Generator with Fixed Number
* **Topic:** Random Settings
* **Difficulty:** Easy
* **Related Source File:** [Steps/Step5_BeeMovement.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step5_BeeMovement.cpp)
* **Snippet Section:** 9. Random Number Generation
* **Modification Required:** Change `srand(time(0));` to `srand(100);` to make the random generation deterministic (yielding the same sequence of clouds and branches every run).

### 47. Increase Bee Speed Random Range
* **Topic:** Random Generation
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step5_BeeMovement.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step5_BeeMovement.cpp)
* **Snippet Section:** 9. Random Number Generation
* **Modification Required:** Change the bee speed formula to generate values between `400` and `799` pixels per second: `beeSpeed = (rand() % 400) + 400;`.

### 48. Restrict Bee Spawning Heights
* **Topic:** Random Generation
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step5_BeeMovement.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step5_BeeMovement.cpp)
* **Snippet Section:** 9. Random Number Generation
* **Modification Required:** Modify the spawning height code to only spawn the bee in the upper half of the screen (between Y coordinates `100` and `499`): `float height = (rand() % 400) + 100;`.

### 49. Randomize Starting Side of the Bee
* **Topic:** Random Generation
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step5_BeeMovement.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step5_BeeMovement.cpp)
* **Snippet Section:** 9. Random Number Generation
* **Modification Required:** Randomly decide whether the bee spawns on the left side (moving right) or the right side (moving left):
  ```cpp
  bool spawnLeft = (rand() % 2 == 0);
  if (spawnLeft) {
      spriteBee.setPosition(-100, height);
      // set moving direction right
  }
  ```

### 50. Increase Branch Spawn Probability
* **Topic:** Random Generation
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Modify `updateBranches()` so there is a higher probability of spawning a branch (e.g., a `rand() % 3` formula yields a 66% chance of spawning a left or right branch).

### 51. Randomize Cloud Heights
* **Topic:** Random Generation
* **Difficulty:** Medium
* **Related Source File:** [TimberTuto.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/TimberTuto.cpp)
* **Snippet Section:** 9. Random Number Generation
* **Modification Required:** Change `rand() % 150` to `rand() % 300` to increase the vertical spread of the clouds.

### 52. Custom Speed Ranges for Clouds
* **Topic:** Random Generation
* **Difficulty:** Medium
* **Related Source File:** [TimberTuto.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/TimberTuto.cpp)
* **Snippet Section:** 9. Random Number Generation
* **Modification Required:** Update the speed formula for the third cloud to make it faster than the others (between `300` and `499` pixels per second): `cloudSpeed3 = (rand() % 200) + 300;`.

---

## Category G: Branch Shifting & Array Algorithms (Questions 53–60)

### 53. Change Branch Array Capacity
* **Topic:** Arrays
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Change the global constant `NUM_BRANCHES` from `6` to `8` and adjust the drawing loops to handle the extra branches.

### 54. Increase Vertical Spacing Between Branches
* **Topic:** Coordinate Mapping
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Change the height offset formula in the drawing loop from `float height = i * 150;` to `i * 180;` to space the branches further apart.

### 55. Shift Array Elements Forward (Broken Logic Demonstration)
* **Topic:** Shifting Algorithms
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Change the loop in `updateBranches()` to iterate forward (`for(int j=0; j < NUM_BRANCHES-1; j++) branchPositions[j+1] = branchPositions[j];`) to demonstrate why forward shifting fails.

### 56. Clear the Entire Branch Array on Start
* **Topic:** Arrays
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 6. Keyboard Input
* **Modification Required:** Reset all branches to `Side::NONE` in the game reset section to start the game with a clear tree:
  ```cpp
  for(int i = 0; i < NUM_BRANCHES; i++) {
      branchPositions[i] = Side::NONE;
  }
  ```

### 57. Alternate Branch Sides Automatically
* **Topic:** Arrays
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Modify the branch spawning logic so it alternates between left and right branches, avoiding spawning branches on the same side consecutively.

### 58. Adjust Origin Rotation Pivot Points
* **Topic:** Transformations
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Change the origin pivot point of the branch sprites: `branches[i].setOrigin(0, 0);` and observe how they rotate around their corners instead of their bases.

### 59. Align Branches with a Thicker Tree Bark
* **Topic:** Coordinate Mapping
* **Difficulty:** Medium
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Adjust the branch positions to align with a wider tree trunk: change the left branch X coordinate from `610` to `580`, and the right branch X coordinate from `1330` to `1360`.

### 60. Shift Array Elements Manually
* **Topic:** Arrays
* **Difficulty:** Hard
* **Related Source File:** [Steps/Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Snippet Section:** 10. Branch Queue & Conveyor Shifting
* **Modification Required:** Replace the array shift loop in `updateBranches()` with manual index assignments to demonstrate how values are moved between slots:
  ```cpp
  branchPositions[5] = branchPositions[4];
  branchPositions[4] = branchPositions[3];
  // Repeat for all slots...
  ```

---

## Category H: Collisions & Game Over Checks (Questions 61–67)

### 61. Safe Mode: Disable Collisions
* **Topic:** Collision Detection
* **Difficulty:** Easy
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 11. Collision & Death Detection
* **Modification Required:** Disable collision checks by commenting out the `if (branchPositions[5] == playerSide)` condition to test gameplay without dying.

### 62. Adjust Squish Detection Index
* **Topic:** Collision Detection
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 11. Collision & Death Detection
* **Modification Required:** Change the collision check to index `4`: `if (branchPositions[4] == playerSide)`. This makes the player collide with branches one level higher.

### 63. Relocate Gravestone Sprite Placement
* **Topic:** Coordinate Mapping
* **Difficulty:** Easy
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 11. Collision & Death Detection
* **Modification Required:** Change the gravestone placement coordinates on player death: set the left position to `(500, 720)` and the right position to `(1250, 720)`.

### 64. Change Death Message Text
* **Topic:** HUD UI
* **Difficulty:** Easy
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 11. Collision & Death Detection
* **Modification Required:** Change the game-over overlay string from `"SQUISHED!!"` to `"GAME OVER - TRY AGAIN!"` and re-center the text.

### 65. Reset High Score Variable
* **Topic:** State Variables
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 11. Collision & Death Detection
* **Modification Required:** Add a check when starting the game (pressing Enter) that resets the `highestScore` back to `0`.

### 66. Soundless Death Mode
* **Topic:** Game States
* **Difficulty:** Easy
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 11. Collision & Death Detection
* **Modification Required:** Comment out the `deathSound.play();` line to prevent audio playback on player death.

### 67. Log coordinates on collision
* **Topic:** Debugging
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 11. Collision & Death Detection
* **Modification Required:** Print the player's side and the branch's position to the console when a collision occurs.

---

## Category I: Audio Triggers & Setup (Questions 68–72)

### 68. Change Audio Files
* **Topic:** Audio
* **Difficulty:** Easy
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 12. Sound System
* **Modification Required:** Change `chopBuffer.loadFromFile("sound/chop.wav")` to point to a new sound file (e.g., `"sound/laser.wav"`).

### 69. Play Chop Sound on Both Key Press and Release
* **Topic:** Audio Triggers
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 12. Sound System
* **Modification Required:** Trigger `chopSound.play()` in both the arrow press check and the `KeyReleased` event check.

### 70. Add Out-of-Time Sound Trigger
* **Topic:** Audio Triggers
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 12. Sound System & 8. Timer System
* **Modification Required:** Play the `outOfTimeSound` sound effect when `timeRemaining <= 0` inside the update loop.

### 71. Sound Buffer Verification Checks
* **Topic:** Safety
* **Difficulty:** Medium
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 12. Sound System
* **Modification Required:** Wrap the audio loading functions in `if` statements and log errors to `std::cerr` if any audio file fails to load.

### 72. Adjust Audio Volumes
* **Topic:** Sound Properties
* **Difficulty:** Easy
* **Related Source File:** [Timber.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp)
* **Snippet Section:** 12. Sound System
* **Modification Required:** Reduce the volume of the chop sound effect to 50% using `chopSound.setVolume(50.f);`.

---

## Category J: Compilation & Execution Commands (Questions 73–75)

### 73. Compile Steps Separately
* **Topic:** Compilation
* **Difficulty:** Easy
* **Related Source File:** [command.txt](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/command.txt)
* **Snippet Section:** 14. Build Command
* **Modification Required:** Run the compiler command in the terminal to compile Step 3:
  ```bash
  g++ Steps/Step3_HUD.cpp -o Step3 -lsfml-graphics -lsfml-window -lsfml-system
  ```

### 74. Compile with Optimization Flags
* **Topic:** Compilation
* **Difficulty:** Medium
* **Related Source File:** [command.txt](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/command.txt)
* **Snippet Section:** 14. Build Command
* **Modification Required:** Add the `-O2` compiler flag to the build command to generate an optimized binary:
  ```bash
  g++ Timber.cpp -o Timber -O2 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
  ```

### 75. Link C++ Standard Library Version
* **Topic:** Compilation
* **Difficulty:** Medium
* **Related Source File:** [command.txt](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/command.txt)
* **Snippet Section:** 14. Build Command
* **Modification Required:** Add the standard library flag `-std=c++17` to compile using the C++17 standard:
  ```bash
  g++ Timber.cpp -o Timber -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
  ```
