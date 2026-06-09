#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

int main() {
    // 1. Create a window of size 800x600 pixels
    RenderWindow window(VideoMode(800, 600), "Q04: GoodBye on Q");
    window.setFramerateLimit(60);

    // 2. Load font (essential to display text)
    Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Warning: Could not load font file. Text might not render!" << std::endl;
        }
    }

    // 3. Configure the Goodbye message text object
    Text goodbyeText;
    goodbyeText.setFont(font);
    goodbyeText.setString("Good Bye");
    goodbyeText.setCharacterSize(60);
    goodbyeText.setFillColor(Color::Red);

    // Center the text
    FloatRect textBounds = goodbyeText.getLocalBounds();
    goodbyeText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
    goodbyeText.setPosition(400.0f, 300.0f);

    // Visibility control variable
    bool showMessage = false;

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Standard close event (clicking the X window button)
            if (event.type == Event::Closed) {
                window.close();
            }

            // Keyboard press detection
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Q) {
                    showMessage = true;
                }
            }

            // Keyboard release detection
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Q) {
                    showMessage = false; // Hide text
                    window.close();      // Close the window (terminate game)
                }
            }
        }

        // Render phase
        window.clear(Color::Black);

        if (showMessage) {
            window.draw(goodbyeText); // Display the message only if showMessage is true
        }

        window.display();
    }

    return 0;
}
