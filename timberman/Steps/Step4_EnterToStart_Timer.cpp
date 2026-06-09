// =============================================================================
// STEP 4 — Enter to Start, Pausing, and the Countdown Timer
// =============================================================================
//
// WHAT THIS STEP TEACHES:
//   • Using a bool 'paused' flag to stop/start the game
//   • Detecting Keyboard::Enter in events
//   • Using Clock and Time to measure elapsed time per frame
//   • Subtracting delta time from a countdown variable
//   • Shrinking the timer bar proportionally to remaining time
//   • Showing different messages based on game state
//
// KEY NEW CONCEPT: Delta Time (dt)
//   dt = how long the last frame took (in seconds)
//   Typically ~0.016 seconds at 60fps
//   EVERY movement or time change is multiplied by dt.
//   This makes behavior frame-rate independent.
//
// RESULT: Press Enter → timer counts down → bar shrinks → "Out of Time!" message
// =============================================================================

#include <SFML/Graphics.hpp>
#include <sstream>
using namespace sf;
using namespace std;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // ---- Sprites (from Step 2) -----------------------------------------------
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

    // ---- HUD (from Step 3) ---------------------------------------------------
    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::Red);
    scoreText.setPosition(20, 20);

    int score = 0;
    stringstream ss;
    ss << "Score = " << score;
    scoreText.setString(ss.str());

    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start");

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    messageText.setPosition(960, 540);

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(760, 980);

    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // =========================================================================
    // NEW: PAUSED FLAG
    // =========================================================================
    // A simple bool that controls whether the game is running or frozen.
    // true  = game is paused (waiting for player, or game over)
    // false = game is running (timer ticking, things moving)
    //
    // We start PAUSED — the player must press Enter to begin.
    bool paused = true;

    // =========================================================================
    // NEW: THE CLOCK
    // =========================================================================
    // Clock is SFML's timer. It starts counting the moment it's created.
    //
    // Every frame we call clock.restart() which:
    //   1. Returns how long since the last restart (as a Time object)
    //   2. Resets the clock back to zero
    //
    // The returned Time tells us "how long was the last frame?"
    // This is called DELTA TIME (dt) — the key to frame-rate independent games.
    Clock clock;
    Time dt; // will hold the delta time each frame

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

            // ---- NEW: Listen for Enter key ----
            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Enter)
            {
                // Unpause the game — start playing!
                paused = false;

                // Reset the timer to full 6 seconds
                timeRemaining = 6.0f;

                // Restart the clock so dt on the NEXT frame isn't huge
                // (it would be huge if we measured since program start!)
                clock.restart();

                // Clear the "Press Enter" message
                messageText.setString("");
            }
        }

        // ----- UPDATE --------------------------------------------------------
        // ONLY update if the game is NOT paused
        if (!paused)
        {
            // ------------------------------------------------------------------
            // DELTA TIME — measure how long the last frame took
            // ------------------------------------------------------------------
            // clock.restart() does two things:
            //   1. Returns elapsed time since last restart → stored in 'dt'
            //   2. Resets the clock to 0 for the next frame
            //
            // dt.asSeconds() gives a small float like 0.016 (for ~60fps)
            dt = clock.restart();

            // ------------------------------------------------------------------
            // COUNT DOWN the timer
            // ------------------------------------------------------------------
            // Subtract this frame's duration from the remaining time.
            // At 60fps: each frame subtracts ~0.016 seconds
            // After 375 frames (~6 seconds): timeRemaining hits 0
            timeRemaining -= dt.asSeconds();

            // ------------------------------------------------------------------
            // SHRINK the timer bar to match remaining time
            // ------------------------------------------------------------------
            // timeBarWidthPerSecond = 400 / 6 ≈ 66.67 pixels per second
            // new width = 66.67 × timeRemaining
            //
            // When timeRemaining = 6.0:  width = 66.67 × 6 = 400 (full)
            // When timeRemaining = 3.0:  width = 66.67 × 3 = 200 (half)
            // When timeRemaining = 0.0:  width = 66.67 × 0 = 0   (empty)
            timeBar.setSize(Vector2f(
                timeBarWidthPerSecond * timeRemaining, // new width
                timeBarHeight                          // height stays same
                ));

            // ------------------------------------------------------------------
            // CHECK if time ran out
            // ------------------------------------------------------------------
            if (timeRemaining <= 0.0f)
            {
                paused = true;                         // stop the game
                messageText.setString("Out of Time!"); // show message

                // Note: we don't re-center the text here because it was
                // already centered in setup. "Out of Time!" will appear
                // at the same centered position as "Press Enter to Start".
            }
        }
        // If paused == true, ALL the update code above is skipped.
        // The timer doesn't tick, the bar doesn't shrink. Everything freezes.

        // ----- DRAW ----------------------------------------------------------
        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spritePlayer);
        window.draw(spriteAxe);

        // HUD
        window.draw(scoreText);
        window.draw(timeBar);

        // messageText is ONLY drawn when paused
        // (either "Press Enter to Start" or "Out of Time!")
        if (paused)
            window.draw(messageText);

        window.display();
    }

    return 0;
}

// =============================================================================
// THINGS TO THINK ABOUT:
//
// Q: Why do we call clock.restart() when Enter is pressed?
//    A: The clock has been running since the program started.
//       If we don't restart it here, the FIRST dt after unpausing could
//       be several seconds big — the timer would jump way down!
//
// Q: What is dt.asSeconds() useful for?
//    A: Multiplying speeds by it makes movement frame-rate independent.
//       speed × dt.asSeconds() = pixels moved per frame
//       This gives the same visual speed whether the game runs at 30fps or 120fps.
//
// Q: Why `if (!paused)` instead of `if (paused == false)`?
//    A: `!` is the "NOT" operator. `!paused` means "if paused is NOT true"
//       Both work, but `!paused` is more idiomatic C++.
//
// Q: What happens to timeRemaining when we press Enter while it's 0?
//    A: We reset it: `timeRemaining = 6.0f;` — fresh start!
// =============================================================================
