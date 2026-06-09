# Pong Snippet Library

This library contains actual code snippets from the project, explanations of what they do, and guidance on typical modifications requested during practical exams.

---

## 1. Window Creation
* **Source File**: `S-01-clean-window/main.cpp`
* **Code Snippet**:
```cpp
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    VideoMode vm(960, 540);
    RenderWindow window(vm, "Pong Game!!!");
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close(); 
        }
        window.clear(Color(28, 27, 55));
        window.display();
    } 
    return 0;
}
```
* **What It Does**: Creates a render window of size 960x540 pixels with a title "Pong Game!!!", enters a basic event loop, clears the screen with a dark color, and updates the display.
* **Typical Exam Modification**: Change window resolution (e.g. `VideoMode vm(1920, 1080)`), modify title, or change the background color inside `window.clear()`.

---

## 2. Bat Class
* **Source File**: `S-05-score/Bat.h` & `S-05-score/Bat.cpp`
* **Code Snippet**:
```cpp
// Header (Bat.h)
class Bat {
private:
    Vector2f m_Position;
    RectangleShape m_Shape;
    float m_Speed = 600.0f;
    bool m_MovingLeft = false;
    bool m_MovingRight = false;
public:
    Bat(float startX, float startY);
    FloatRect getPosition();
    RectangleShape getShape();
};

// Implementation (Bat.cpp)
Bat::Bat(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setSize(sf::Vector2f(50,5));
    m_Shape.setPosition(m_Position);
}
```
* **What It Does**: Defines the structural properties of a paddle/bat using a private `sf::RectangleShape` and controls its start position.
* **Typical Exam Modification**: Resizing the bat (`m_Shape.setSize(Vector2f(newWidth, newHeight))`) or setting custom fill colors (`m_Shape.setFillColor(Color::Green)`).

---

## 3. Bat Movement
* **Source File**: `S-05-score/Bat.cpp` & `S-05-score/main.cpp`
* **Code Snippet**:
```cpp
// Bat.cpp movement update (includes boundaries)
void Bat::update(Time dt)
{	 if(m_MovingLeft)
		if(m_Position.x >0)
     		m_Position.x -= m_Speed * dt.asSeconds();
     
     if(m_MovingRight){
     	if(m_Position.x < 910)
     		m_Position.x += m_Speed * dt.asSeconds();
     }
     m_Shape.setPosition(m_Position);
}

// Keyboard Polling (main.cpp)
if (Keyboard::isKeyPressed(Keyboard::Left))
    bat.moveLeft();
else
    bat.stopLeft();

if (Keyboard::isKeyPressed(Keyboard::Right))
    bat.moveRight();
else
    bat.stopRight();
```
* **What It Does**: Reads keyboard input to toggle left/right moving states and moves the paddle while ensuring it stays within screen boundaries (`0` and `910`).
* **Typical Exam Modification**: Changing key binds (e.g. `Keyboard::A`, `Keyboard::D`), changing boundaries to adapt to screen resizing, or adding vertical movement for dual-paddle games.

---

## 4. Ball Class
* **Source File**: `S-05-score/Ball.h` & `S-05-score/Ball.cpp`
* **Code Snippet**:
```cpp
// Header (Ball.h)
class Ball {
private:
     Vector2f m_Position;
     CircleShape m_Shape;
     float m_Speed = 1000.0f;
     float m_DirectionX = 0.2f;
     float m_DirectionY = 0.2f;	 
public:
     Ball(float startX, float startY);
     FloatRect getPosition();
     CircleShape getShape();
};

// Implementation (Ball.cpp)
Ball::Ball(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setRadius(10);
    m_Shape.setPosition(m_Position);
}
```
* **What It Does**: Defines structural properties of a bouncing ball using `sf::CircleShape` and tracking velocity directions.
* **Typical Exam Modification**: Modify the ball radius, initial speeds (`m_Speed`), or direct angles.

---

## 5. Ball Movement
* **Source File**: `S-05-score/Ball.cpp`
* **Code Snippet**:
```cpp
void Ball::update(Time dt)
{
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}
```
* **What It Does**: Moves the ball continuously in 2D space based on directional multipliers and speed.
* **Typical Exam Modification**: Speed up the ball dynamically (e.g., `m_Speed *= 1.1f` on bounce) or add gravity.

---

## 6. Collision Detection
* **Source File**: `S-05-score/main.cpp` & `S-05-score/Ball.cpp`
* **Code Snippet**:
```cpp
// Horizontal Wall Collision
if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
    ball.reboundSides();
}
// Top Wall Collision
if (ball.getPosition().top < 0) {
    coli = false;
    ball.reboundBatOrTop();       
}
// Bat/Paddle Collision
if (ball.getPosition().intersects(bat.getPosition()) && coli == false) {
    ball.reboundBatOrTop();
    score++;
    coli = true;
}
```
* **What It Does**: Detects intersection between ball and bat bounds using `FloatRect::intersects()` and checks screen boundaries using window dimensions.
* **Typical Exam Modification**: Randomizing angle deviation on paddle bounce, or custom response when hitting different parts of the paddle.

---

## 7. Score System
* **Source File**: `S-05-score/main.cpp`
* **Code Snippet**:
```cpp
Text hud;
Font font;
font.loadFromFile("font/Debrosee.ttf");
hud.setFont(font);
hud.setCharacterSize(30);
hud.setFillColor(Color::White);
hud.setPosition(20,20);

// Rendering Score in Game Loop
std::stringstream ss;
ss << "Score" << score << "Lives" << lives;
hud.setString(ss.str());
```
* **What It Does**: Loads a font file, initializes text settings, dynamically sets the string representation of score and lives, and updates on-screen text.
* **Typical Exam Modification**: Resizing text, changing font files, positioning text at the center, or implementing Game Over/Victory message flags.

---

## 8. Game Loop
* **Source File**: `S-05-score/main.cpp`
* **Code Snippet**:
```cpp
Clock clock;
while (window.isOpen())
{   
    Time dt = clock.restart();
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
    // Update Objects
    bat.update(dt);
    ball.update(dt);
    // Draw Objects
    window.clear(Color(28, 27, 55));
    window.draw(hud);
    window.draw(bat.getShape());
    window.draw(ball.getShape());
    window.display();
}
```
* **What It Does**: Regulates game frame updates and drawings relative to Delta Time (`dt`) using a high-resolution clock.
* **Typical Exam Modification**: Adding a pause state (`bool paused`) and skipping updates when true.

---

## 9. Build Command
* **Source File**: `command.txt`
* **Code Snippet**:
```bash
g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system && ./main
```
* **What It Does**: Compiles the entry source file and links required SFML shared libraries, executing it on success.
* **Typical Exam Modification**: Renaming binary output, compiling multiple translation units individually, or adding warning options (`-Wall -Wextra`).

---

## Likely Practical Questions

* **Move object with keyboard**: Update `main.cpp` input polling using `sf::Keyboard::isKeyPressed()`.
* **Move object with mouse**: Bind paddle coordinates directly to `sf::Mouse::getPosition(window).x`.
* **Add boundary restriction**: Implement bounds checks `m_Position.x > 0` and `m_Position.x < limit` inside updating methods.
* **Add score counter**: Track with an integer `score`, increment on collision, and write to a `std::stringstream` bound to a `sf::Text` object.
* **Add collision**: Call `shapeA.getGlobalBounds().intersects(shapeB.getGlobalBounds())`.
* **Display text**: Create `sf::Font`, load `.ttf` file, instantiate `sf::Text`, set font, set string, and call `window.draw()`.
* **Create paddle**: Instantiated via `sf::RectangleShape` with specific width/height dimensions.
* **Create ball**: Instantiated via `sf::CircleShape` with a specific radius.
