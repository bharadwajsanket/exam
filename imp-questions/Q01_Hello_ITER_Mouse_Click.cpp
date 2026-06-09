#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

int main() {
    // 1. Create a window of size 800x600 pixels
    RenderWindow window(VideoMode(800, 600), "Q01: Hello ITER");
    window.setFramerateLimit(60);

    // 2. Load font (mandatory for rendering text in SFML)
    Font font;
    // We check the standard Ubuntu path first, then try the local directory
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Warning: Could not load font file. Text might not render!" << std::endl;
        }
    }

    // 3. Set up the text object
    Text text;
    text.setFont(font);
    text.setString("Hello ITER");
    text.setCharacterSize(50);
    text.setFillColor(Color::Cyan);

    // 4. Center the text in the middle of the window
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
    text.setPosition(400.0f, 300.0f);

    // 5. State variable to track whether we should display the text
    bool showText = false;

    // 6. Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Exit window on close click
            if (event.type == Event::Closed) {
                window.close();
            }

            // Detect mouse press
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    showText = true;
                }
            }

            // Detect mouse release
            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    showText = false;
                }
            }
        }

        // Render phase
        window.clear(Color::Black); // Clear screen with black background

        if (showText) {
            window.draw(text); // Draw text if showText flag is true
        }

        window.display(); // Swap buffer and draw to screen
    }

    return 0;
}
