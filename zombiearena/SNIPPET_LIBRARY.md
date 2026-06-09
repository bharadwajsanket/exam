# ZombieArena Snippet Library

This document provides exact, extracted C++ and SFML code snippets from the ZombieArena codebase. Each section explains the snippet's purpose, details the active APIs, and outlines potential exam questions and modifications.

---

## 1. Window Creation

### Source File
* [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L22-30)

### Code Snippet
```cpp
resolution.x = 1920;
resolution.y = 1080;
RenderWindow window(VideoMode(resolution.x, resolution.y),
    "Zombie Arena", Style::Fullscreen);

// Create a an SFML View for the main action
View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
window.setView(mainView);
```

### What It Does
Creates a fullscreen render window container at 1920x1080 resolution and maps a viewport camera to scale the player action display.

### Typical Exam Modification
Change window resolution (e.g. `VideoMode(800, 600)`), modify title, or switch style (e.g. `Style::Default` instead of fullscreen).

---

## 2. Player

### Source File
* [Player.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/Player.cpp#L4-38) & [Player.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/Player.cpp#L111-126)

### Code Snippet
```cpp
class Player
{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    Vector2f m_Position;
    Sprite m_Sprite;
    Texture m_Texture;
    ...
};

Player::Player()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
    m_Texture.loadFromFile("graphics/player.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(25, 25);
}
```

### What It Does
Defines member properties for tracking player positions, texture assets, sprites, health, and speed, and instantiates default stats inside the constructor.

### Typical Exam Modification
Modify player initial speed, starting health, or load custom player sprites.

---

## 3. Zombie

### Source File
* [zombie.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/zombie.cpp#L6-30) & [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L677-713)

### Code Snippet
```cpp
class Zombie{
    private:
        const float BLOATER_SPEED=20;
        const float CHASER_SPEED=40;
        const float CRAWLER_SPEED=10;
        ...
};

Zombie* createHorde(int numZombies, IntRect arena){
    Zombie* zombies=new Zombie[numZombies];
    ...
    for(int i=0;i<numZombies;i++){
        ...
        int type=(rand()%3);
        zombies[i].spawn(x,y,type,i);
    }
    return zombies;
}
```

### What It Does
Manages parameters for multiple zombie variants (Bloater, Chaser, Crawler) and dynamically instantiates a zombie array populated near screen boundaries.

### Typical Exam Modification
Create a new zombie type with custom health/speed profiles or alter type distribution rates.

---

## 4. Bullet

### Source File
* [bullet.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/bullet.cpp#L5-29) & [bullet.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/bullet.cpp#L103-119)

### Code Snippet
```cpp
class Bullet
{
private:
    Vector2f m_Position;
    RectangleShape m_BulletShape;
    bool m_InFlight = false;
    float m_BulletSpeed = 1000;
    ...
};

void Bullet::update(float elapsedTime)
{
    m_Position.x += m_BulletDistanceX * elapsedTime;
    m_Position.y += m_BulletDistanceY * elapsedTime;
    m_BulletShape.setPosition(m_Position);
    if (m_Position.x < m_MinX || m_Position.x > m_MaxX ||
        m_Position.y < m_MinY || m_Position.y > m_MaxY)
    {
        m_InFlight = false;
    }
}
```

### What It Does
Traces the continuous flight path of active bullets using linear speed components and deactivates them when out-of-range boundaries are hit.

### Typical Exam Modification
Alter bullet dimension shapes (`m_BulletShape.setSize`), adjust speed multipliers, or decrease maximum range.

---

## 5. Pickup

### Source File
* [pickup.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/pickup.cpp#L3-30) & [pickup.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/pickup.cpp#L72-86)

### Code Snippet
```cpp
class Pickup{
    private:
        const int HEALTH_START_VALUE=50;
        const int AMMO_START_VALUE=12;
        ...
        int m_Type; //1= health, 2=ammo
        ...
};

void Pickup::update(float elapsedTime){
    if(m_Spawned){
        m_SecondsSinceSpawn=m_SecondsSinceSpawn+ elapsedTime;
    }
    else{
        m_SecondsSinceDeSpawn=m_SecondsSinceDeSpawn+ elapsedTime;
    }
    if(m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned){
        spawn();
    }
    if(m_SecondsSinceSpawn>m_SecondsToLive && m_Spawned){
        m_Spawned=false;
        m_SecondsSinceDeSpawn=0;
    }
}
```

### What It Does
Drives spawning timers for health/ammo items that appear inside the arena bounds and despawn after set intervals.

### Typical Exam Modification
Introduce additional pickup classes (e.g. fire-rate boost), adjust values, or alter spawn frequencies.

---

## 6. Input

### Source File
* [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L255-289) & [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L291-316)

### Code Snippet
```cpp
// Keyboard WASD Check
if (Keyboard::isKeyPressed(Keyboard::W)) player.moveUp();
else player.stopUp();
...
// Mouse Fire Check
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
    if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
    {
        bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
        currentBullet++;
        if (currentBullet > 99) currentBullet = 0;
        lastPressed = gameTimeTotal;
        bulletsInClip--;
    }
}
```

### What It Does
Polls current keyboard states to trigger continuous player movement, and captures left mouse button inputs to dispatch projectile entities within limits.

### Typical Exam Modification
Rebind keys to Arrow configurations, or change firing mechanisms (e.g. fire on right-click instead).

---

## 7. Collision

### Source File
* [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L435-501)

### Code Snippet
```cpp
// Check bullet and zombie collisions
for (int i = 0; i < 100; i++) {
    for (int j = 0; j < numZombies; j++) {
        if (bullets[i].isInFlight() && zombies[j].isAlive()) {
            if (bullets[i].getPosition().intersects(zombies[j].getPosition())) {
                bullets[i].stop();
                if (zombies[j].hit()) {
                    score += 10;
                    ...
                }
            }
        }
    }
}
```

### What It Does
Runs nested iterations checking bounds intersections between active bullets and live zombies, registering hits and adjusting score values.

### Typical Exam Modification
Introduce piercing projectiles, add splash damage ranges, or implement invulnerability periods.

---

## 8. Score System

### Source File
* [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L510-537)

### Code Snippet
```cpp
if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
{
    std::stringstream ssAmmo;
    std::stringstream ssScore;
    ...
    ssScore << "Score:" << score;
    scoreText.setString(ssScore.str());
    ...
}
```

### What It Does
Converts numeric game variables to visual strings using stream buffers, and updates on-screen hud components on set intervals.

### Typical Exam Modification
Add a multiplier for consecutive kills, color codes based on scoring thresholds, or record tracking to file.

---

## 9. Wave System

### Source File
* [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L365-385)

### Code Snippet
```cpp
wave++;
arena.width = wave * 500;
arena.height = wave * 500;
arena.left = 0;
arena.top = 0;

int tileSize = createBackground(background, arena);
player.spawn(arena, resolution, tileSize);
numZombies = wave * 2;
delete[] zombies;
zombies = createHorde(numZombies, arena);
numZombiesAlive = numZombies;
```

### What It Does
Manages wave escalation by scaling arena boundary structures, resetting tile backgrounds, and scaling up the generated zombie horde population.

### Typical Exam Modification
Add boss spawn patterns every 5 waves, or alter scaling formulas for zombie population.

---

## 10. Sound System

### Source File
* Standard SFML implementation pattern (assets in `sound/`)

### Code Snippet
```cpp
#include <SFML/Audio.hpp>

// Loading audio resources
SoundBuffer shootBuffer;
shootBuffer.loadFromFile("sound/shoot.wav");
Sound shootSound(shootBuffer);

// Play sound
shootSound.play();
```

### What It Does
Loads dynamic audio files into reusable buffers, linking them to system sound players to trigger audible gameplay feedback.

### Typical Exam Modification
Link reload sounds on key triggers, adjust sound volumes, or loop background ambient tracks.

---

## 11. Game Loop

### Source File
* [ZombieArena.cpp](file:///Users/sanketbharadwaj/Downloads/C%2B%2B%20LAB/TimberMan/exam/zombiearena/ZombieArena.cpp#L179-613)

### Code Snippet
```cpp
while (window.isOpen())
{
    Event event;
    while (window.pollEvent(event)) {
        // Event processing
    }
    
    if (state == State::PLAYING) {
        Time dt = clock.restart();
        // State updates
    }
    
    if (state == State::PLAYING) {
        window.clear();
        window.setView(mainView);
        // Drawing elements
        window.display();
    }
}
```

### What It Does
Coordinates execution loops for input reception, property updating phases, and rendering buffers.

### Typical Exam Modification
Integrate pausing mechanisms or scale rendering elements based on state flags.

---

## 12. Build Command

### Source File
* `build.sh`

### Code Snippet
```bash
g++ ZombieArena.cpp -o ZombieArena -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### What It Does
Invokes compiler processes linking SFML libraries to output executable gameplay files.

### Typical Exam Modification
Target different binary names or add warning tags (`-Wall -Wextra`).

---

## Likely Practical Questions

### Keyboard Movement
* **Mapping**: Player movement updates in `Player.cpp` triggered by key presses polled in `ZombieArena.cpp`.
* **Exam Task**: "Swap WASD configuration to Arrow keys."

### Mouse Movement
* **Mapping**: Crosshair positions and player character rotations calculated from coordinates.
* **Exam Task**: "Constrain or scale player rotation speed."

### Object Spawning
* **Mapping**: Random spawning locations checked in `createHorde` loop algorithms.
* **Exam Task**: "Restructure horde spawning to only appear along top/bottom screen edges."

### Collision Detection
* **Mapping**: Intersection routines checking boundary boxes using the `intersects()` function.
* **Exam Task**: "Apply knockback to the player or zombie upon collision."

### Shooting
* **Mapping**: Spawning of bullet structures and frame updates.
* **Exam Task**: "Change bullets from square shapes to round circle configurations."

### Score Updates
* **Mapping**: Dynamic scoring updates tracking kills and upgrading hud elements.
* **Exam Task**: "Make zombie variants give different score values on hit."

### Sound Effects
* **Mapping**: SFML audio buffers executing playback when events occur.
* **Exam Task**: "Play splat sounds on hit collisions."

### Pickup Collection
* **Mapping**: Detection of player collision with pickup sprites, resetting status.
* **Exam Task**: "Add a speed boost pickup that increases Player speed temporarily."

### Boundary Restriction
* **Mapping**: Restricting coordinate ranges inside updating checks of `Player.cpp`.
* **Exam Task**: "Introduce inner walls that restrict movement."

### Wave Generation
* **Mapping**: Progression escalations recreating backgrounds and zombie arrays.
* **Exam Task**: "Introduce boss wave checkpoints."
