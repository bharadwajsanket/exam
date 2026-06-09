# SFML 2-Minute Quick Reference

A syntax revision cheat sheet for laboratory classes.

---

## 1. Window Creation
```cpp
#include <SFML/Graphics.hpp>
using namespace sf;

// Resolution and Window Instantiation
VideoMode vm(1920, 1080);
RenderWindow window(vm, "Timber Game!!!");

// Virtual Camera View Setup (Maintains Aspect Ratio)
View view(FloatRect(0, 0, 1920, 1080));
window.setView(view);
```

---

## 2. Textures & Sprites
```cpp
// 1. Load Texture (from project folder)
Texture texture;
texture.loadFromFile("graphics/player.png");

// 2. Bind to Sprite
Sprite sprite(texture);

// 3. Transformations
sprite.setPosition(800.f, 600.f);    // Position absolute coordinates
sprite.setScale(0.5f, 0.5f);         // Scaling factors (50% size)
sprite.setOrigin(100.f, 50.f);       // Shift pivot origin coordinate
sprite.setRotation(180.f);           // Rotate clockwise (in degrees)
sprite.move(-10.f, 0.f);             // Shift position relative to current
```

---

## 3. Fonts & Text
```cpp
#include <sstream>

// 1. Load Font
Font font;
font.loadFromFile("font/KOMIKAP_.ttf");

// 2. Set up Text Object
Text text;
text.setFont(font);
text.setCharacterSize(80);           // Size in pixels
text.setFillColor(Color::Yellow);
text.setPosition(50, 50);

// 3. Set text string (use stringstream to merge numbers)
std::stringstream ss;
int score = 42;
ss << "Score = " << score;
text.setString(ss.str());

// 4. Centering Text origin
FloatRect bounds = text.getLocalBounds();
text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
```

---

## 4. Inputs
```cpp
// A. Real-time Keyboard Checks (Fluid, multiple frames)
if (Keyboard::isKeyPressed(Keyboard::Left)) {
    // Left key is currently pressed down
}

// B. Event Handling (Discrete, one-time triggers)
Event event;
while (window.pollEvent(event)) {
    if (event.type == Event::Closed) {
        window.close(); // Closed event
    }
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
        // Enter key was pressed down once
    }
    if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space) {
        // Space key was released
    }
}

// C. Mouse Input (Coordinates relative to the Window)
if (Mouse::isButtonPressed(Mouse::Left)) {
    Vector2i position = Mouse::getPosition(window);
    // Left click at position.x and position.y
}
```

---

## 5. Clocks & Time (Delta Time)
```cpp
Clock clock;
Time dt;

while (window.isOpen()) {
    // Restart clock and capture elapsed seconds
    dt = clock.restart();
    float dtSeconds = dt.asSeconds(); // e.g., 0.016 at 60fps
    
    // Scale movement by dt
    float speed = 200.f; // 200 pixels per second
    sprite.move(speed * dtSeconds, 0);
}
```

---

## 6. Sound Effects
```cpp
#include <SFML/Audio.hpp>

// 1. Load Buffer from Disk
SoundBuffer buffer;
buffer.loadFromFile("sound/chop.wav");

// 2. Bind buffer to a Sound Player
Sound sound(buffer);

// 3. Play sound effect
sound.play();
```

---

## 7. Compilation & Run Commands

### Linux (Ubuntu) Compilation
```bash
# Compile project with Audio support
g++ Timber.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Compile tutorial steps (no Audio support)
g++ Steps/Step1_BlackWindow.cpp -o Step1 -lsfml-graphics -lsfml-window -lsfml-system
```

### Run Command (Execute from Project Root)
```bash
./Timber
```
*(Make sure to run your program from the directory containing `graphics/`, `font/`, and `sound/` folders!)*
