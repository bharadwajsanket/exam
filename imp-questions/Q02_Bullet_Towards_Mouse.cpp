#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

int main() {
    // 1. Create window and limit framerate
    RenderWindow window(VideoMode(800, 600), "Q02: Bullet Towards Mouse");
    window.setFramerateLimit(60);

    // 2. Create the player (green rectangle) positioned at the center
    RectangleShape player(Vector2f(40.0f, 40.0f));
    player.setFillColor(Color::Green);
    player.setOrigin(20.0f, 20.0f); // Center origin
    player.setPosition(400.0f, 300.0f);

    // 3. Create the bullet (red circle)
    float bulletRadius = 8.0f;
    CircleShape bullet(bulletRadius);
    bullet.setFillColor(Color::Red);
    bullet.setOrigin(bulletRadius, bulletRadius); // Center origin

    // Physics variables
    Vector2f bulletPos = player.getPosition();
    bullet.setPosition(bulletPos);
    Vector2f bulletVelocity(0.0f, 0.0f);
    float bulletSpeed = 8.0f;
    bool isBulletFlying = false;

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Detect one-time press of F key
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::F) {
                    // Fetch mouse coordinates
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                    // Reset bullet position to player
                    bulletPos = player.getPosition();
                    bullet.setPosition(bulletPos);

                    // Math: Direction = Target - Source
                    Vector2f direction = target - bulletPos;

                    // Calculate vector length (Distance)
                    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                    // Prevent division by zero and normalize the velocity vector
                    if (distance > 0.0f) {
                        bulletVelocity = (direction / distance) * bulletSpeed;
                        isBulletFlying = true;
                    }
                }
            }
        }

        // 4. Update phase (Physics)
        if (isBulletFlying) {
            bulletPos += bulletVelocity;
            bullet.setPosition(bulletPos);

            // Despawn bullet if it flies off-screen
            if (bulletPos.x < 0 || bulletPos.x > 800 || bulletPos.y < 0 || bulletPos.y > 600) {
                isBulletFlying = false;
            }
        }

        // 5. Render phase
        window.clear(Color::Black);
        window.draw(player);
        if (isBulletFlying) {
            window.draw(bullet);
        }
        window.display();
    }

    return 0;
}
