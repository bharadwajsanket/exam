# Code Snippet Extraction Library

This document provides exact, extracted C++ and SFML code snippets from the TimberMan codebase. Each section explains the snippet's purpose, details the active APIs, and outlines potential exam questions and modifications.

---

## 1. Window Creation

### Purpose
To initialize a graphical window canvas and configure a virtual camera view that maintains the 1920x1080 design coordinates regardless of resizing.

### Extracted Code Snippet
From [Timber.cpp:L35-40](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L35-40):
```cpp
VideoMode vm(1920,1080);
RenderWindow window(vm,"Timber Game!!!");

View view(FloatRect(0,0,1920,1080));
window.setView(view);
```

### SFML APIs Used
- **`sf::VideoMode`:** Defines the width and height of the window.
- **`sf::RenderWindow`:** Creates the OS window container.
- **`sf::View`:** Implements screen scaling to maintain a virtual resolution.

### Exam Usage
* **What it does:** Sets up a window at 1920x1080 resolution and maps a viewport camera to it.
* **Typical Exam Question:** "Write the C++ SFML code to initialize a window titled 'Exam Game' with a width of 800 and height of 600, using a view that maps the same coordinates."
* **How to modify it:**
  ```cpp
  VideoMode vm(800, 600);
  RenderWindow window(vm, "Exam Game");
  View view(FloatRect(0, 0, 800, 600));
  window.setView(view);
  ```
* **Difficulty Level:** Easy

---

## 2. Texture Loading

### Purpose
Loads a raw image from disk (like background, players, clouds) directly into the GPU's memory.

### Extracted Code Snippet
From [Timber.cpp:L41-43](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L41-43):
```cpp
Texture textureBackground;
textureBackground.loadFromFile("graphics/background.png");
```

### Exam Usage
* **What it does:** Allocates RAM/VRAM buffer for the background image asset.
* **Typical Exam Question:** "Demonstrate how to load an image named 'character.png' located inside an 'images' subfolder using SFML, and explain how to verify if loading succeeded."
* **How to modify it:**
  ```cpp
  Texture texturePlayer;
  if (!texturePlayer.loadFromFile("images/character.png")) {
      // Handle loading failure (e.g., exit or print error)
  }
  ```
* **Difficulty Level:** Easy

---

## 3. Sprite Creation

### Purpose
Creates a visual representation of a texture that can be positioned, scaled, and drawn on the screen.

### Extracted Code Snippet
From [Timber.cpp:L50-59](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L50-59):
```cpp
Texture textureCloud;
textureCloud.loadFromFile("graphics/cloud.png");

Sprite spriteCloud1(textureCloud);
Sprite spriteCloud2(textureCloud);
Sprite spriteCloud3(textureCloud);

spriteCloud1.setScale(0.6,0.6);
spriteCloud2.setScale(0.4,0.4);
spriteCloud3.setScale(0.9,0.9);
```

### Exam Usage
* **What it does:** Creates three distinct cloud sprites that share a single texture in memory, and scales their dimensions.
* **Typical Exam Question:** "Write a code snippet to instantiate a sprite linked to a previously loaded texture and scale it to 25% of its original size."
* **How to modify it:**
  ```cpp
  Sprite mySprite(myTexture);
  mySprite.setScale(0.25f, 0.25f);
  ```
* **Difficulty Level:** Easy

---

## 4. Font Loading

### Purpose
Loads vector font glyph definitions from a TrueType Font (`.ttf`) file on disk to format text interfaces.

### Extracted Code Snippet
From [Timber.cpp:L131-132](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L131-132):
```cpp
Font font;
font.loadFromFile("font/KOMIKAP_.ttf");
```

### Exam Usage
* **What it does:** Loads vector font definitions into system memory.
* **Typical Exam Question:** "Load a font file called 'arial.ttf' located in the system font directory and handle errors if the file is missing."
* **How to modify it:**
  ```cpp
  Font arialFont;
  if (!arialFont.loadFromFile("font/arial.ttf")) {
      // Error handling code
  }
  ```
* **Difficulty Level:** Easy

---

## 5. Text Rendering (HUD Overlay)

### Purpose
Renders text elements on the screen. This section shows how to set up aligned score displays (top-left) and screen-centered overlays ("Press Enter to Start").

### Extracted Code Snippet
From [Timber.cpp:L134-160](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L134-160):
```cpp
Text scoreText;
scoreText.setFont(font);
scoreText.setCharacterSize(100);
scoreText.setFillColor(Color::Red);
scoreText.setPosition(20,20);

// Score initialization
int score = 0;

Text messageText;
messageText.setFont(font);
messageText.setCharacterSize(75);
messageText.setFillColor(Color::Green);
messageText.setString("Press Enter to Start");

FloatRect textRect=messageText.getLocalBounds();
messageText.setOrigin(
    textRect.left+textRect.width/2.0f,
    textRect.top+textRect.height/2.0f);
messageText.setPosition(1920/2.0f,1080/2.0f);
```

### Exam Usage
* **What it does:** Renders red score text at fixed coordinates and places a green status overlay centered in the middle of a 1920x1080 layout.
* **Typical Exam Question:** "Explain how `getLocalBounds()` and `setOrigin()` are used to center text in SFML. Write a code snippet to display the string 'GAME OVER' in yellow, centered on a 1280x720 window."
* **How to modify it:**
  ```cpp
  Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setString("GAME OVER");
  gameOverText.setFillColor(Color::Yellow);
  gameOverText.setCharacterSize(80);

  FloatRect rect = gameOverText.getLocalBounds();
  gameOverText.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
  gameOverText.setPosition(1280 / 2.0f, 720 / 2.0f);
  ```
* **Difficulty Level:** Medium

---

## 6. Keyboard Input

### Purpose
Checks for keyboard input using two methods: Event-based polling (best for one-time events) and real-time state checks (best for rapid, continuous input).

### Extracted Code Snippet
From [Timber.cpp:L181-216](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L181-216) (Event Polling) and [L234-273](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L234-273) (Real-time checks):
```cpp
// A. Event Loop Key Triggers
Event event;
while(window.pollEvent(event))
{
    if(event.type==Event::Closed)
        window.close();

    // Trigger Enter key (Event based)
    if(event.type==Event::KeyPressed &&
       event.key.code==Keyboard::Enter && paused)
    {
        paused=false;
        // reset parameters...
    }

    // Reset input buffer flag on Key Release
    if(event.type==Event::KeyReleased && !paused)
    {
        acceptInput=true;
        spriteAxe.setPosition(2000,830); // Hide axe
    }
}

// B. Real-time Keyboard Checks (inside update loop)
if(acceptInput)
{
    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        playerSide=Side::LEFT;
        spritePlayer.setPosition(580,720);
        spriteAxe.setPosition(AXE_POSITION_LEFT,830);
        acceptInput=false; // Lock input
        chopSound.play();
    }
    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        playerSide=Side::RIGHT;
        spritePlayer.setPosition(1200,720);
        spriteAxe.setPosition(AXE_POSITION_RIGHT,830);
        acceptInput=false; // Lock input
        chopSound.play();
    }
}
```

### Exam Usage
* **What it does:** Starts the game when the Enter key is pressed, handles key releases to reset the chopping state, and detects left/right keypresses to move the player and axe sprites.
* **Typical Exam Question:** "Write an event handler that closes the window when the Escape key is pressed, and state the difference between `sf::Event::KeyPressed` and `sf::Keyboard::isKeyPressed`."
* **How to modify it:**
  Add this check inside the `while(window.pollEvent(event))` loop:
  ```cpp
  if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
  {
      window.close();
  }
  ```
* **Difficulty Level:** Medium

---

## 7. Mouse Input

### Purpose
Captures mouse clicks and coordinates. *(Note: Not used in TimberMan, so this is a standard SFML pattern)*.

### Extracted Code Snippet
*Not used in TimberMan. Standard SFML pattern:*
```cpp
// Query current mouse state
if (Mouse::isButtonPressed(Mouse::Left))
{
    // Retrieve relative coordinates of the mouse inside the window frame
    Vector2i mousePos = Mouse::getPosition(window);
    
    // Check if the click sits inside a target button rectangle bounds
    FloatRect buttonBounds(100.f, 100.f, 200.f, 50.f);
    if (buttonBounds.contains(static_cast<Vector2f>(mousePos)))
    {
        // Execute button action
    }
}
```

### Exam Usage
* **What it does:** Tracks left mouse clicks and checks if they occur within a specific button region.
* **Typical Exam Question:** "Write a code block to capture a left mouse click, obtain the click coordinates relative to the window, and check if the click is within a 200x200 pixel box at coordinate (500,500)."
* **How to modify it:**
  ```cpp
  if (Mouse::isButtonPressed(Mouse::Left)) {
      Vector2i mousePos = Mouse::getPosition(window);
      if (mousePos.x >= 500 && mousePos.x <= 700 && mousePos.y >= 500 && mousePos.y <= 700) {
          // Perform task inside the coordinate box
      }
  }
  ```
* **Difficulty Level:** Medium

---

## 8. Timer System

### Purpose
Implements a shrinking timer bar to track the remaining gameplay time.

### Extracted Code Snippet
From [Timber.cpp:L161-171](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L161-171) and [L220-232](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L220-232):
```cpp
// Initialization
RectangleShape timeBar;
float timeBarStartWidth = 400;
float timeBarHeight = 80;
timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
timeBar.setFillColor(Color::Red);
timeBar.setPosition((1920/2)-timeBarStartWidth/2,980);

float timeRemaining = 6.0f;
float timeBarWidthPerSecond = timeBarStartWidth/timeRemaining;

Clock clock;
Time dt;

// Update Frame Loop (when !paused)
dt=clock.restart();
timeRemaining -= dt.asSeconds();
timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
```

### Exam Usage
* **What it does:** Restarts the clock to calculate the elapsed delta time (`dt`), decrements the timer, and updates the size of the red progress bar shape.
* **Typical Exam Question:** "Using `sf::Clock` and `sf::Time`, write a program block that counts down from 10 seconds. When time runs out, print 'Failed' and close the window."
* **How to modify it:**
  ```cpp
  float timeLimit = 10.0f;
  Clock frameClock;
  // inside the loop...
  Time elapsed = frameClock.restart();
  timeLimit -= elapsed.asSeconds();
  if (timeLimit <= 0.f) {
      printf("Failed\n");
      window.close();
  }
  ```
* **Difficulty Level:** Medium

---

## 9. Random Number Generation

### Purpose
Generates randomized speeds and positions for gameplay elements like clouds, bees, and branches.

### Extracted Code Snippet
From [Timber.cpp:L21-28](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L21-28) and [TimberTuto.cpp:L407-409](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/TimberTuto.cpp#L407-409):
```cpp
// Seeding in main()
srand((int)time(0));

// Random choice (0 to 4)
int r = rand() % 5;

// Random cloud velocity
cloudSpeed1 = rand() % 200; // range 0 to 199

// Random bee velocity and Y coordinates
beeSpeed = (rand() % 200) + 200; // range 200 to 399
float height = (rand() % 500) + 500; // range 500 to 999
```

### Exam Usage
* **What it does:** Seeds the random generator and uses modulo calculations to generate random numbers within specific ranges.
* **Typical Exam Question:** "Write a C++ statement to generate a random float coordinate height between 100.0 and 400.0 pixels for an obstacle sprite."
* **How to modify it:**
  ```cpp
  float randomHeight = (rand() % 301) + 100; // 301 values from 0 to 300, offset by +100
  ```
* **Difficulty Level:** Easy

---

## 10. Branch Queue & Conveyor Shifting

### Purpose
Implements the core branch updating algorithm. When the player chops, this moves branches down the tree like a conveyor belt and spawns a new random branch at the top.

### Extracted Code Snippet
From [Timber.cpp:L16-29](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L16-29):
```cpp
const int NUM_BRANCHES = 6;
enum class Side { LEFT, RIGHT, NONE };
Side branchPositions[NUM_BRANCHES];

void updateBranches(int seed)
{
    // Shift: iterate backwards through the array to avoid overwriting data
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    int r = rand() % 5;

    switch (r)
    {
        case 0: branchPositions[0] = Side::LEFT; break;
        case 1: branchPositions[0] = Side::RIGHT; break;
        default: branchPositions[0] = Side::NONE; break;
    }
}
```

### Explanation of Shifting Logic
1. **The Array Shifting Loop:** To shift elements down, the loop starts at index `5` (the bottom) and moves backwards to `1`. Each slot copies the value of the slot above it (`branchPositions[j] = branchPositions[j - 1]`). 
2. **Backward Traversal:** Shifting backwards is required. If the loop went forward (`0` to `5`), index `1` would copy the value of `0`. Then, index `2` would copy index `1` (which now has the value of `0`), resulting in the first value copying through the entire array.
3. **Random Spawning:** Index `0` (the top of the tree) is assigned a new random state: `Side::LEFT` (20% chance), `Side::RIGHT` (20% chance), or `Side::NONE` (60% chance).

### Exam Usage
* **What it does:** Shifts the enum states in the array down one slot and adds a new random value at index 0.
* **Typical Exam Question:** "Describe why a conveyor-shifting array algorithm must iterate backwards. Implement a function to shift an array of 5 integer elements down by one slot and insert a default value of 99 at index 0."
* **How to modify it:**
  ```cpp
  int data[5];
  void shiftArray() {
      for (int i = 4; i > 0; i--) {
          data[i] = data[i - 1];
      }
      data[0] = 99; // Insert at index 0
  }
  ```
* **Difficulty Level:** Hard

---

## 11. Collision & Death Detection

### Purpose
Checks if a branch has collided with the player, triggering a game-over state.

### Extracted Code Snippet
From [Timber.cpp:L275-292](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L275-292):
```cpp
if (branchPositions[5] == playerSide)
{
    paused = true;
    acceptInput = false;

    // Move player sprite off-screen (hide player)
    spritePlayer.setPosition(2000,720);

    // Place RIP gravestone at player's location
    if (playerSide == Side::LEFT)
        spriteRip.setPosition(600,720);
    else
        spriteRip.setPosition(1150,720);

    if (score > highestScore)
        highestScore = score;

    messageText.setString("SQUISHED!!");
    deathSound.play();
}
```

### Exam Usage
* **What it does:** Pauses the game, hides the player, displays the tombstone at the player's last coordinates, updates the high score, displays the game over message, and plays the death sound effect.
* **Typical Exam Question:** "Write a C++ condition to check if an obstacle at index `5` of an array matches the player's current side, and show how to transition the game state to 'Paused' while playing a sound effect."
* **How to modify it:**
  ```cpp
  if (obstacleArray[5] == activeSide) {
      isPaused = true;
      statusText.setString("COLLISION!");
      soundPlayer.play();
  }
  ```
* **Difficulty Level:** Medium

---

## 12. Sound System

### Purpose
Loads audio files into a buffer and plays them when actions occur.

### Extracted Code Snippet
From [Timber.cpp:L119-130](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L119-130) and [L252](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L252):
```cpp
// Loading sound buffer and binding sound player
SoundBuffer chopBuffer;
chopBuffer.loadFromFile("sound/chop.wav");
Sound chopSound(chopBuffer);

// Playback (inside input update triggers)
chopSound.play();
```

### Exam Usage
* **What it does:** Loads a WAV sound file into a memory buffer and links it to a player object to play the audio.
* **Typical Exam Question:** "Write the SFML C++ code to load a sound file named 'laser.wav' and play it when the Space bar is pressed."
* **How to modify it:**
  ```cpp
  SoundBuffer laserBuffer;
  laserBuffer.loadFromFile("sound/laser.wav");
  Sound laserSound(laserBuffer);
  // inside the loop...
  if (Keyboard::isKeyPressed(Keyboard::Space)) {
      laserSound.play();
  }
  ```
* **Difficulty Level:** Medium

---

## 13. The Game Loop Structure

### Purpose
The core loop of the game. It controls event polling (Input), game state updates (Update), and visual rendering (Draw).

### Extracted Code Snippet
From [Timber.cpp:L177-325](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Timber.cpp#L177-325):
```cpp
while(window.isOpen())
{
    dt = clock.restart();

    // 1. INPUT PHASE (Event Polling)
    Event event;
    while(window.pollEvent(event))
    {
        if(event.type == Event::Closed)
            window.close();
        
        // check keyboard start keys...
    }

    // 2. UPDATE PHASE (runs when active)
    if(!paused)
    {
        timeRemaining -= dt.asSeconds();
        // Update positions, collisions, and state variables
    }

    // 3. RENDER PHASE
    window.clear(); // clear screen
    
    // Draw background and sprites
    window.draw(spriteBackground);
    window.draw(spriteTree);
    for(int i = 0; i < NUM_BRANCHES; i++)
        window.draw(branches[i]);
    window.draw(spritePlayer);
    window.draw(spriteRip);
    window.draw(spriteAxe);
    
    // Draw HUD elements
    window.draw(scoreText);
    window.draw(timeBar);
    
    if(paused)
        window.draw(messageText);

    window.display(); // swap buffers
}
```

### Exam Usage
* **What it does:** Orchestrates the core game loop, handling inputs, updating game states, and rendering sprites in the correct layered order.
* **Typical Exam Question:** "Draw a flowchart or write a pseudocode block representing the standard three-part Game Loop pipeline, showing where event checks, movement updates, and draw buffers are processed."
* **How to modify it:**
  ```cpp
  // Add a background color modification during clear phase
  window.clear(Color::Blue); // Clears background to Blue
  ```
* **Difficulty Level:** Medium

---

## 14. Build Command

### Purpose
Compiles the C++ source files, linking the required SFML modules.

### Extracted Command Snippet
From [command.txt:L5](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/command.txt#L5):
```bash
g++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### Exam Usage
* **What it does:** Invokes the GCC compiler to build `Timber.cpp` into a binary executable named `Timber`, linking the graphic, window, system, and audio dynamic libraries.
* **Typical Exam Question:** "Write the command to compile an SFML application named 'game.cpp' into a binary called 'game.exe', linking graphics, window, and system libraries without audio."
* **How to modify it:**
  ```bash
  g++ game.cpp -o game.exe -lsfml-graphics -lsfml-window -lsfml-system
  ```
* **Difficulty Level:** Easy
