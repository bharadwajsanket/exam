# Pong Quick Reference

## Compile Command
```bash
g++ main.cpp -o Pong -lsfml-graphics -lsfml-window -lsfml-system
```

## Window Creation
```cpp
#include <SFML/Graphics.hpp>
using namespace sf;

VideoMode vm(960, 540);
RenderWindow window(vm, "Pong Game!!!");
```

## Bat Creation
```cpp
// Header (Bat.h)
class Bat {
private:
    Vector2f m_Position;
    RectangleShape m_Shape;
public:
    Bat(float startX, float startY);
    FloatRect getPosition();
    RectangleShape getShape();
};

// Source (Bat.cpp)
Bat::Bat(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setSize(Vector2f(50, 5));
    m_Shape.setPosition(m_Position);
}
FloatRect Bat::getPosition() { return m_Shape.getGlobalBounds(); }
RectangleShape Bat::getShape() { return m_Shape; }
```

## Ball Creation
```cpp
// Header (Ball.h)
class Ball {
private:
    Vector2f m_Position;
    CircleShape m_Shape;
public:
    Ball(float startX, float startY);
    FloatRect getPosition();
    CircleShape getShape();
};

// Source (Ball.cpp)
Ball::Ball(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setRadius(10);
    m_Shape.setPosition(m_Position);
}
FloatRect Ball::getPosition() { return m_Shape.getGlobalBounds(); }
CircleShape Ball::getShape() { return m_Shape; }
```

## Movement
### Bat Keyboard Movement
```cpp
// Bat.cpp updates (with boundaries)
void Bat::update(Time dt) {
    if (m_MovingLeft && m_Position.x > 0)
        m_Position.x -= m_Speed * dt.asSeconds();
    if (m_MovingRight && m_Position.x < 910)
        m_Position.x += m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}
```

### Ball Continuous Movement
```cpp
// Ball.cpp update
void Ball::update(Time dt) {
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}
```

## Collision
```cpp
// Left/Right walls
if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
    ball.reboundSides(); // reverse X direction
}

// Top wall
if (ball.getPosition().top < 0) {
    ball.reboundBatOrTop(); // reverse Y direction
}

// Bat collision
if (ball.getPosition().intersects(bat.getPosition())) {
    ball.reboundBatOrTop(); // reverse Y direction
}
```

## Score
```cpp
#include <sstream>

int score = 0;
int lives = 3;

Text hud;
Font font;
font.loadFromFile("font/Debrosee.ttf");
hud.setFont(font);
hud.setCharacterSize(30);
hud.setFillColor(Color::White);
hud.setPosition(20, 20);

// In game loop
std::stringstream ss;
ss << "Score" << score << "Lives" << lives;
hud.setString(ss.str());
```
