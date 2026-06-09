#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

int main() {
    // 1. Create window and limit framerate
    RenderWindow window(VideoMode(800, 600), "Q03: Bullet Boundary 500x500");
    window.setFramerateLimit(60);

    // 2. Define the 500x500 arena (centered inside 800x600 window)
    // Left boundary = (800 - 500) / 2 = 150
    // Top boundary = (600 - 500) / 2 = 50
    // Width = 500, Height = 500
    RectangleShape arena(Vector2f(500.0f, 500.0f));
    arena.setFillColor(Color::Transparent);
    arena.setOutlineColor(Color::White);
    arena.setOutlineThickness(5.0f);
    arena.setPosition(150.0f, 50.0f);

    // 3. Define the bullet (red circle)
    float bulletRadius = 10.0f;
    CircleShape bullet(bulletRadius);
    bullet.setFillColor(Color::Red);
    bullet.setOrigin(bulletRadius, bulletRadius); // Origin at center
    bullet.setPosition(400.0f, 300.0f); // Place at the center of the arena

    float speed = 5.0f;

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // 4. Capture keyboard inputs for movement (real-time query)
        Vector2f movement(0.0f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            movement.x -= speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            movement.x += speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
            movement.y -= speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
            movement.y += speed;
        }

        // Calculate next candidate position
        Vector2f nextPos = bullet.getPosition() + movement;

        // 5. Apply Boundary Clamping
        // Left limit: 150 + radius
        // Right limit: 650 - radius (150 + 500)
        // Top limit: 50 + radius
        // Bottom limit: 550 - radius (50 + 500)
        float minX = 150.0f + bulletRadius;
        float maxX = 650.0f - bulletRadius;
        float minY = 50.0f + bulletRadius;
        float maxY = 550.0f - bulletRadius;

        if (nextPos.x < minX) nextPos.x = minX;
        if (nextPos.x > maxX) nextPos.x = maxX;
        if (nextPos.y < minY) nextPos.y = minY;
        if (nextPos.y > maxY) nextPos.y = maxY;

        // Apply clamped position to the shape
        bullet.setPosition(nextPos);

        // Render phase
        window.clear(Color::Black);
        window.draw(arena);  // Draw the boundary lines
        window.draw(bullet); // Draw the bullet
        window.display();
    }

    return 0;
}
