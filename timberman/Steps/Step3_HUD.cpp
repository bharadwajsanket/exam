// =============================================================================
// STEP 3 — The HUD (Heads-Up Display): Score Text and Timer Bar
// =============================================================================
//
// WHAT THIS STEP TEACHES:
//   • Loading and using a Font
//   • Creating Text objects (size, color, string, position)
//   • Centering text using getLocalBounds()
//   • Creating a RectangleShape for the timer bar
//   • Using stringstream to combine text + numbers
//   • Drawing UI elements on top of game sprites
//
// "HUD" = Heads-Up Display. The score, timer, lives etc.
//         It's the info overlay always visible on screen.
//
// NEW IN THIS STEP:
//   • Font + scoreText
//   • Font + messageText (centered on screen)
//   • RectangleShape timeBar (the red bar at the bottom)
//
// RESULT: Scene from Step 2 + score text top-left + timer bar at bottom
//         + "Press Enter to Start" centered on screen.
// =============================================================================

#include <SFML/Graphics.hpp>
#include <sstream> // needed for stringstream
using namespace sf;
using namespace std;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");

    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // ---- Sprites (from Step 2, unchanged) -----------------------------------
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground);

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810, 0);

    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(580, 720);

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(700, 830);

    // =========================================================================
    // FONT — The typeface for ALL text in the game
    // =========================================================================
    // Just like Texture is loaded once and reused, Font is loaded ONCE and
    // then used by as many Text objects as you want.
    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf"); // .ttf = TrueType Font file

    // =========================================================================
    // SCORE TEXT — Top-left of screen
    // =========================================================================
    Text scoreText;
    scoreText.setFont(font);            // which font to use
    scoreText.setCharacterSize(100);    // size in pixels (not points!)
    scoreText.setFillColor(Color::Red); // text color
    scoreText.setPosition(20, 20);      // top-left, with a small margin

    // The actual text content — we use stringstream to mix text + number
    int score = 0;
    stringstream ss;
    ss << "Score = " << score;     // builds the string "Score = 0"
    scoreText.setString(ss.str()); // .str() converts stream to string

    // HOW stringstream works:
    //   Think of ss as a whiteboard.
    //   ss << "Score = " writes "Score = " on it.
    //   ss << score      adds the number after it.
    //   ss.str()         gives you the whole whiteboard text as a string.

    // =========================================================================
    // MESSAGE TEXT — Centered on screen ("Press Enter to Start")
    // =========================================================================
    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start");

    // ---- CENTERING the text on screen ----
    // By default, setPosition places the TEXT'S TOP-LEFT CORNER at that point.
    // If we do setPosition(960, 540), the top-left of the text is at center —
    // which means the text sprawls to the right and looks off-center.
    //
    // The fix: change the text's ORIGIN (pivot point) to its own center.
    // Then setPosition(960, 540) places the CENTER of the text at screen center.
    //
    // getLocalBounds() returns a FloatRect:
    //   .left   — offset from origin to left edge (not always 0 due to padding)
    //   .top    — offset from origin to top edge
    //   .width  — total width of the text
    //   .height — total height of the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(
        textRect.left + textRect.width / 2.0f, // horizontal center of text
        textRect.top + textRect.height / 2.0f  // vertical center of text
    );

    // Now setting position to the screen's center (960, 540)
    // makes the TEXT's own center land at (960, 540)
    messageText.setPosition(960, 540);

    // =========================================================================
    // TIMER BAR — Red rectangle at the bottom of screen
    // =========================================================================
    // RectangleShape is an SFML built-in for drawing solid rectangles.
    // Perfect for health bars, timer bars, progress bars.
    RectangleShape timeBar;

    // We store the starting width so we can calculate how much to shrink it
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;

    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    // Vector2f is SFML's 2D vector — holds an x and a y value (both floats)

    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(760, 980); // near the bottom center

    // =========================================================================
    // TIMER LOGIC DATA (no actual countdown yet — that's in Step 4)
    // =========================================================================
    float timeRemaining = 6.0f; // player starts with 6 seconds

    // SHRINK RATE: how many pixels wide the bar loses per second
    // If bar starts at 400px and represents 6 seconds:
    //   400 / 6 = ~66.67 pixels shrink per second
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
    // (We store this so we can use it in the update step later)

    // =========================================================================
    // THE GAME LOOP
    // =========================================================================
    while (window.isOpen())
    {
        // ----- EVENTS --------------------------------------------------------
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // ----- UPDATE --------------------------------------------------------
        // Nothing changes yet (timer doesn't tick, score doesn't increase)
        // We're just displaying the static HUD setup.

        // ----- DRAW ----------------------------------------------------------
        window.clear();

        // GAME WORLD layers (bottom to top)
        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spritePlayer);
        window.draw(spriteAxe);

        // UI / HUD layers — drawn AFTER game world so they appear on top
        window.draw(scoreText);   // score — top left
        window.draw(timeBar);     // timer bar — bottom center
        window.draw(messageText); // center message

        window.display();
    }

    return 0;
}

// =============================================================================
// THINGS TO THINK ABOUT:
//
// Q: Why is there a setOrigin() for messageText but not for scoreText?
//    A: scoreText is anchored to the top-left (x=20, y=20) — no centering needed.
//       messageText needs to be exactly in the screen's center, so we center it.
//
// Q: Why does setCharacterSize(100) look different from a font-size in Word?
//    A: SFML size is in PIXELS on screen, not typographic points.
//       100px in a 1920×1080 window is quite large.
//
// Q: What is Vector2f?
//    A: A simple struct holding two floats: x and y.
//       Vector2f(400, 80) means width=400, height=80.
//
// Q: Why empty the ss stringstream before reusing it?
//    ss.str("");   ← this clears the stringstream
//    Otherwise it keeps appending to the old content!
// =============================================================================
