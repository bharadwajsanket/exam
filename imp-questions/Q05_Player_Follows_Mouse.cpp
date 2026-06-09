#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm> // For std::min

using namespace sf;

int main() {
    // 1. Create window and limit framerate
    RenderWindow window(VideoMode(800, 600), "Q05: Player Follows Mouse");
    window.setFramerateLimit(60);

    // 2. Define the 500x500 arena boundary (centered inside 800x600 window)
    // Left boundary = 150, Top boundary = 50
    RectangleShape arena(Vector2f(500.0f, 500.0f));
    arena.setFillColor(Color::Transparent);
    arena.setOutlineColor(Color::White);
    arena.setOutlineThickness(5.0f);
    arena.setPosition(150.0f, 50.0f);

    // 3. Define the player (blue circle)
    float playerRadius = 20.0f;
    CircleShape player(playerRadius);
    player.setFillColor(Color::Blue);
    player.setOrigin(playerRadius, playerRadius); // Set origin to center
    player.setPosition(400.0f, 300.0f); // Start in the middle of the arena

    float speed = 4.0f; // Velocity coefficient

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // 4. Get current mouse position (real-time tracking)
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // 5. Calculate displacement vector and distance
        Vector2f currentPos = player.getPosition();
        Vector2f direction = target - currentPos;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        Vector2f nextPos = currentPos;

        // Epsilon threshold to prevent jittering when very close to target mouse position
        if (distance > 2.0f) {
            Vector2f normalizedDir = direction / distance;
            // Move towards target, limiting step by the actual remaining distance
            nextPos += normalizedDir * std::min(speed, distance);
        }

        // 6. Clamp player inside the 500x500 arena bounds
        // Left boundary: 150, Right boundary: 650
        // Top boundary: 50, Bottom boundary: 550
        float minX = 150.0f + playerRadius;
        float maxX = 650.0f - playerRadius;
        float minY = 50.0f + playerRadius;
        float maxY = 550.0f - playerRadius;

        if (nextPos.x < minX) nextPos.x = minX;
        if (nextPos.x > maxX) nextPos.x = maxX;
        if (nextPos.y < minY) nextPos.y = minY;
        if (nextPos.y > maxY) nextPos.y = maxY;

        // Apply position update
        player.setPosition(nextPos);

        // Render phase
        window.clear(Color::Black);
        window.draw(arena);  // Draw the boundary lines
        window.draw(player); // Draw the player
        window.display();
    }

    return 0;
}
