#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

int main() {
    // 1. Create window and limit framerate
    RenderWindow window(VideoMode(800, 600), "Q06: Bottom-Left Restriction");
    window.setFramerateLimit(60);

    // 2. Define the full 500x500 Arena (centered inside 800x600 window)
    // Left boundary: 150, Top boundary: 50
    RectangleShape arena(Vector2f(500.0f, 500.0f));
    arena.setFillColor(Color::Transparent);
    arena.setOutlineColor(Color::White);
    arena.setOutlineThickness(2.0f);
    arena.setPosition(150.0f, 50.0f);

    // 3. Define the Bottom-Left Quadrant Visual Highlight
    // Top-left of bottom-left quadrant: (150, 300) | Size: (250, 250)
    RectangleShape bottomLeftQuad(Vector2f(250.0f, 250.0f));
    bottomLeftQuad.setFillColor(Color(255, 255, 0, 30)); // Transparent yellow tint
    bottomLeftQuad.setOutlineColor(Color::Yellow);
    bottomLeftQuad.setOutlineThickness(2.0f);
    bottomLeftQuad.setPosition(150.0f, 300.0f);

    // 4. Define the Player (magenta circle)
    float playerRadius = 15.0f;
    CircleShape player(playerRadius);
    player.setFillColor(Color::Magenta);
    player.setOrigin(playerRadius, playerRadius); // Center origin
    
    // Spawn player in the center of the bottom-left quadrant:
    // x = 150 + 125 = 275
    // y = 300 + 125 = 425
    player.setPosition(275.0f, 425.0f);

    float speed = 5.0f;

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // 5. Capture keyboard movement inputs (real-time query)
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

        // Compute proposed position coordinate
        Vector2f nextPos = player.getPosition() + movement;

        // 6. Define physical boundary limits of the Bottom-Left Quadrant
        // Arena starts at x = 150, midpoint is x = 400
        // Arena midpoint is y = 300, ends at y = 550
        float minX = 150.0f + playerRadius;
        float maxX = 400.0f - playerRadius;
        float minY = 300.0f + playerRadius;
        float maxY = 550.0f - playerRadius;

        // Apply boundary clamp constraints
        if (nextPos.x < minX) nextPos.x = minX;
        if (nextPos.x > maxX) nextPos.x = maxX;
        if (nextPos.y < minY) nextPos.y = minY;
        if (nextPos.y > maxY) nextPos.y = maxY;

        // Set clamped position
        player.setPosition(nextPos);

        // Render phase
        window.clear(Color::Black);
        window.draw(arena);          // Draw full arena outline
        window.draw(bottomLeftQuad); // Draw highlighted quadrant region
        window.draw(player);          // Draw player
        window.display();
    }

    return 0;
}
