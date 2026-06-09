# Tutorial Progression Guide

This guide details the step-by-step progress of the laboratory course. Each step inside the [Steps/](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps) directory represents a complete, runnable C++ program. Students should progress sequentially from Step 1 to Step 6.

---

## Step 1 – Black Window

* **Source File:** [Step1_BlackWindow.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step1_BlackWindow.cpp)
* **Goal:** Initialize a window framework and construct the skeleton of the infinite game loop.

### What Was Added
- Core headers and namespace directives (`#include <SFML/Graphics.hpp>`).
- Resolution metrics (`sf::VideoMode`).
- Desktop renderer frame (`sf::RenderWindow`).
- Graphic viewport (`sf::View`) to handle window scaling.
- The standard event poll loop to handle OS commands (like clicking the "Close" button).

### SFML Concepts Introduced
- **`sf::RenderWindow`:** The canvas that draws components and communicates window events with the OS.
- **Double Buffering:** Splitting visual output into a hidden "back-buffer" and a visible "front-buffer". This eliminates visual tearing and flickering during execution.
- **The Event Queue:** A list of user inputs (keys, clicks, resizing) that the OS queues up. The program processes them one by one.

### Key Code Snippet
```cpp
// Window Initialization
VideoMode vm(1920, 1080);
RenderWindow window(vm, "Timber Game!!!");

// The Game Loop
while (window.isOpen())
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }
    
    window.clear();   // Wipe previous frame (fill with black)
    // Draw calls go here
    window.display(); // Swap buffers to show the new frame
}
```

### Important SFML APIs
- `sf::RenderWindow::isOpen()`
- `sf::RenderWindow::pollEvent(sf::Event& event)`
- `sf::RenderWindow::clear()`
- `sf::RenderWindow::display()`

### What Students Should Learn
1. How to open and safely close a standard graphics window without memory leakage.
2. The core structures of dynamic apps: **Input Phase** (events), **Update Phase** (calculations), and **Draw Phase** (rendering).

---

## Step 2 – Sprite Layers

* **Source File:** [Step2_SpriteLayers.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step2_SpriteLayers.cpp)
* **Goal:** Load image files from disk into GPU memory and render them in a layered hierarchy.

### What Was Added
- Texture definitions for background, tree trunk, player character, and axe.
- Corresponding sprite objects referencing those textures.
- Positional coordinates mapping assets on a virtual 1920x1080 canvas.
- Layered drawing order inside the render block.

### SFML Concepts Introduced
- **Texture vs. Sprite Decoupling:**
  - `sf::Texture` stores raw image pixel matrices in GPU RAM (expensive).
  - `sf::Sprite` holds reference pointers, transform matrices (position, rotation, scaling), and color modifiers (inexpensive).
- **Stacking Order (Painter's Algorithm):** Drawn components overlap based on statement execution sequence. Backgrounds are drawn first, followed by midground elements, and foreground elements last.

### Key Code Snippet
```cpp
// Load texture into video memory
Texture texturePlayer;
texturePlayer.loadFromFile("graphics/player.png");

// Bind to sprite container and position it
Sprite spritePlayer(texturePlayer);
spritePlayer.setPosition(580, 720); // (X, Y) layout coordinates

// Draw order (inside the game loop)
window.draw(spriteBackground); // Bottom layer
window.draw(spriteTree);       // Midground
window.draw(spritePlayer);     // Foreground
window.draw(spriteAxe);        // Top layer
```

### Important SFML APIs
- `sf::Texture::loadFromFile(const std::string& filename)`
- `sf::Sprite::Sprite(const sf::Texture& texture)`
- `sf::Sprite::setPosition(float x, float y)`
- `sf::RenderWindow::draw(const sf::Drawable& drawable)`

### What Students Should Learn
1. How to split graphics into lightweight sprites referencing heavy textures.
2. Coordinate mapping: origin `(0,0)` sits at the **Top-Left** corner; X increases to the right, and Y increases downward.

---

## Step 3 – HUD

* **Source File:** [Step3_HUD.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step3_HUD.cpp)
* **Goal:** Integrate typography systems, render dynamic game scores, and build shapes for the timer bar.

### What Was Added
- TrueType font asset loader (`KOMIKAP_.ttf`).
- Text rendering objects (`scoreText`, `messageText`).
- String formatting streams (`std::stringstream`).
- Bounding-box alignment calculations to center the start message.
- A procedural rectangle shape container (`sf::RectangleShape`) representing the timer bar.

### SFML Concepts Introduced
- **`sf::Font` & `sf::Text`:** Text characters are vector definitions converted into bitmap formats during execution.
- **Bounding Boxes:** Every visual node possesses a local boundary rectangle defining its size on screen.
- **Procedural Geometries:** Dynamic generation of basic shapes without loading static images.

### Key Code Snippet
```cpp
// Load Font and Initialize Text
Font font;
font.loadFromFile("font/KOMIKAP_.ttf");

Text messageText;
messageText.setFont(font);
messageText.setString("Press Enter to Start");

// Centering text logic using local bounds
FloatRect textRect = messageText.getLocalBounds();
messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                      textRect.top + textRect.height / 2.0f);
messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

// Shape layout creation
RectangleShape timeBar;
timeBar.setSize(Vector2f(400.f, 80.f));
timeBar.setFillColor(Color::Red);
timeBar.setPosition(760, 980);
```

### Important SFML APIs
- `sf::Font::loadFromFile(const std::string& filename)`
- `sf::Text::setFont(const sf::Font& font)`
- `sf::Text::getLocalBounds()`
- `sf::Transformable::setOrigin(float x, float y)`
- `sf::RectangleShape::setSize(const sf::Vector2f& size)`

### What Students Should Learn
1. How to render text and align it dynamically using local bounds calculations.
2. The role of the HUD: rendering UI overlays *after* drawing game world objects to keep them visible on top.

---

## Step 4 – Enter To Start + Timer

* **Source File:** [Step4_EnterToStart_Timer.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step4_EnterToStart_Timer.cpp)
* **Goal:** Control game states (paused vs. running) and implement frame-rate independent countdown timers.

### What Was Added
- State control flag (`paused`).
- Enter key trigger monitoring.
- Precision clock component (`sf::Clock`).
- Frame-rate independence using Delta Time (`dt`).
- Linear scaling math to shrink the timer bar over time.

### SFML Concepts Introduced
- **Frame-Rate Independence (Delta Time):** High-end computers run games at hundreds of frames per second, while standard computers run at 60fps. Delta Time (`dt`) represents the elapsed time between frames in seconds (e.g., `0.016s` at 60fps). Multiplying coordinates or timing changes by `dt` guarantees consistent speed on all hardware configurations.
- **Clock Restarts:** Capturing elapsed time and resetting the clock at the start of each frame.

### Key Code Snippet
```cpp
bool paused = true;
Clock clock;
Time dt;

while (window.isOpen())
{
    // Capture elapsed time since last frame
    dt = clock.restart();
    
    // ... Event Polling handles Keyboard::Enter -> paused = false ...
    
    if (!paused)
    {
        // Subtract real-world elapsed time
        timeRemaining -= dt.asSeconds();
        
        // Scale the visual rectangle width
        timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
        
        if (timeRemaining <= 0.0f)
        {
            paused = true;
            messageText.setString("Out of Time!");
        }
    }
}
```

### Important SFML APIs
- `sf::Clock::restart()`
- `sf::Time::asSeconds()`

### What Students Should Learn
1. How to use boolean flags to manage states (e.g., Start, Running, Game Over).
2. The logic behind Delta Time and its role in game performance stability.

---

## Step 5 – Bee Movement

* **Source File:** [Step5_BeeMovement.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step5_BeeMovement.cpp)
* **Goal:** Move objects across coordinates using random velocities and height parameters.

### What Was Added
- Seed initialization (`srand(time(0))`) for random generation.
- Dynamic bee sprite assets.
- Logic states (`beeActive` boolean tracker).
- Boundary-crossing check scripts.
- Multiplicative delta-movement equations.

### SFML Concepts Introduced
- **`Sprite::move(x, y)`:** Offsets the current position of a sprite by a relative distance rather than jumping to an absolute point (`setPosition`).
- **Object Recycling:** Repositioning an object to a start state once it exits the display screen bounds.

### Key Code Snippet
```cpp
if (!beeActive)
{
    // Generate speed range [200, 399] pixels per second
    beeSpeed = (rand() % 200) + 200;
    
    // Generate Y altitude range [500, 999]
    float height = (rand() % 500) + 500;
    
    // Spawn off-screen to the right
    spriteBee.setPosition(2000, height);
    beeActive = true;
}
else
{
    // Shift left based on speed and delta time
    spriteBee.move(-beeSpeed * dt.asSeconds(), 0);
    
    // Check if fully off-screen to the left
    if (spriteBee.getPosition().x < -100)
    {
        beeActive = false; // Triggers reset next frame
    }
}
```

### Important SFML APIs
- `sf::Sprite::move(float offsetX, float offsetY)`
- `sf::Transformable::getPosition()`

### What Students Should Learn
1. How to use pseudo-random formulas (`rand() % range + offset`) to generate gameplay variance.
2. How to implement the standard off-screen object cycle: **Deactivate -> Re-randomize -> Respawn -> Move -> Recross**.

---

## Step 6 – Branch System

* **Source File:** [Step6_BranchSystem.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/TimberMan/Steps/Step6_BranchSystem.cpp)
* **Goal:** Implement core gameplay algorithms using arrays, scoped enums, and origin rotations.

### What Was Added
- Scoped enum (`enum class Side`) to logically represent branch orientations (`LEFT`, `RIGHT`, `NONE`).
- Global fixed array storing `NUM_BRANCHES` sprite structures.
- Logic array matching sprite layouts (`Side branchPositions[NUM_BRANCHES]`).
- Backwards shifting logic within `updateBranches()` to move branches down on each chop.
- Sprite pivot coordinate adjustment (`setOrigin`) and rotation manipulation.
- Off-screen asset hiding (`x = 3000`).

### SFML Concepts Introduced
- **Sprite Rotation and Pivot Origins:** By default, sprites rotate around their top-left corner `(0, 0)`. Adjusting the origin moves this pivot point. Setting the origin to the branch's connection point enables clean rotations when flipping branches left or right.
- **Model-View-Controller Separation:** Decoupling structural variables (`Side branchPositions[]`) from visual elements (`Sprite branches[]`).

### Key Code Snippet
```cpp
// Backwards Shifting Conveyor Algorithm
void updateBranches(int seed)
{
    // Shift elements down by copying the previous slot's state
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    // Spawn a random branch at the top (index 0)
    int r = rand() % 5;
    if (r == 0)      branchPositions[0] = Side::LEFT;
    else if (r == 1) branchPositions[0] = Side::RIGHT;
    else             branchPositions[0] = Side::NONE;
}

// Drawing Sync Loop (inside main game loop)
for (int i = 0; i < NUM_BRANCHES; i++)
{
    float height = i * 150; // Vertical spacing
    
    if (branchPositions[i] == Side::LEFT)
    {
        branches[i].setPosition(610, height);
        branches[i].setRotation(180); // Rotate 180 degrees to flip left
    }
    else if (branchPositions[i] == Side::RIGHT)
    {
        branches[i].setPosition(1330, height);
        branches[i].setRotation(0);   // Keep default facing right
    }
    else // NONE
    {
        branches[i].setPosition(3000, height); // Hide off-screen
    }
}
```

### Important SFML APIs
- `sf::Sprite::setRotation(float angle)`
- `sf::Sprite::setOrigin(float x, float y)`

### What Students Should Learn
1. The importance of iterating arrays backwards during queue shift updates.
2. How to map logical enums to graphic positions and rotation orientations.
3. The role of coordinate origin shifts in rotations and screen placements.
