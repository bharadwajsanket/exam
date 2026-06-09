# ZombieArena Quick Reference

## Compile Command
```bash
g++ ZombieArena.cpp -o ZombieArena -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

## Window Creation
```cpp
Vector2f resolution(1920, 1080);
RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
window.setView(mainView);
```

## Player Creation
```cpp
Player player;
IntRect arena;
int tileSize = 50;
player.spawn(arena, resolution, tileSize);
```

## Zombie Creation
```cpp
Zombie* zombies = createHorde(numZombies, arena);
```

## Bullet Creation
```cpp
Bullet bullets[100];
int currentBullet = 0;
```

## Pickup Creation
```cpp
Pickup healthPickup(1); // 1 = health
Pickup ammoPickup(2);   // 2 = ammo
```

## Input Handling
```cpp
// Keyboard inputs for WASD player movement
if (Keyboard::isKeyPressed(Keyboard::W)) player.moveUp();
else player.stopUp();

if (Keyboard::isKeyPressed(Keyboard::S)) player.moveDown();
else player.stopDown();

if (Keyboard::isKeyPressed(Keyboard::A)) player.moveLeft();
else player.stopLeft();

if (Keyboard::isKeyPressed(Keyboard::D)) player.moveRight();
else player.stopRight();

// Mouse input for firing bullets
if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
    currentBullet++;
    if (currentBullet > 99) currentBullet = 0;
}
```

## Collision Detection
```cpp
// Intersection detection between bounding boxes
if (shapeA.getGlobalBounds().intersects(shapeB.getGlobalBounds())) {
    // Collision detected
}
```

## Score Updates
```cpp
std::stringstream ssScore;
ssScore << "Score:" << score;
scoreText.setString(ssScore.str());
```

## Sound Effects
```cpp
#include <SFML/Audio.hpp>

SoundBuffer buffer;
buffer.loadFromFile("sound/shoot.wav");
Sound sound(buffer);
sound.play();
```
