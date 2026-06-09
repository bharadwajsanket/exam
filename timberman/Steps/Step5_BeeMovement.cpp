// =============================================================================
// STEP 5 — Bee Movement: Sprite.move(), Random Speed, Reset Logic
// =============================================================================
//
// WHAT THIS STEP TEACHES:
//   • Sprite.move() vs Sprite.setPosition()
//   • Using a bool flag to manage a 2-state system (active/inactive)
//   • rand() with expressions to get values in a range
//   • Off-screen spawning and reset when leaving the other side
//   • Why movement must use delta time (dt)
//
// BEE BEHAVIOUR:
//   State A (beeActive = false):
//     → Pick a random speed between 200 and 399
//     → Pick a random height between 500 and 999
//     → Place the bee far to the right (x = 2000, off-screen)
//     → Set beeActive = true → switch to State B
//
//   State B (beeActive = true):
//     → Move the bee LEFT every frame
//     → When bee goes past x = -100 (off left edge):
//       → Set beeActive = false → switch back to State A
//
// RESULT: A bee that continuously flies from right to left, at random
//         heights and speeds, looping forever while the game runs.
// =============================================================================

#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime> // needed for time(0) in srand
using namespace sf;
using namespace std;

int main()
{
    // Seed the random number generator ONCE at program start.
    // time(0) returns the current time as a number — different each run.
    // This ensures rand() gives different sequences every time you play.
    srand(time(0));

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

    // ---- HUD (from Steps 3 & 4) ---------------------------------------------
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
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(960, 540);

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(760, 980);
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;
    Clock clock;
    Time dt;

    // =========================================================================
    // NEW: BEE SPRITE
    // =========================================================================
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");

    Sprite spriteBee(textureBee);
    // Place the bee far to the right (off screen) as a starting position.
    // When the game starts, it will be reinitialized properly.
    spriteBee.setPosition(2000, 800);

    // =========================================================================
    // NEW: BEE STATE VARIABLES
    // =========================================================================
    // beeActive tracks WHICH state the bee is in.
    // false = waiting to be initialized / needs a new position + speed
    // true  = currently flying across the screen
    bool beeActive = false;

    // beeSpeed stores how fast the bee moves this "run"
    // It's 0.0 now and will be set each time the bee resets.
    float beeSpeed = 0.0f;

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

            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Enter)
            {
                paused = false;
                timeRemaining = 6.0f;
                clock.restart();
                messageText.setString("");
            }
        }

        // ----- UPDATE --------------------------------------------------------
        if (!paused)
        {
            dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out of Time!");
            }

            // ==================================================================
            // BEE LOGIC — The 2-State System
            // ==================================================================

            // --- STATE A: Bee is inactive ---
            // This block runs whenever beeActive is false.
            // It sets up a new bee traversal with random parameters.
            if (!beeActive)
            {
                // Pick a random speed between 200 and 399 pixels/second
                // rand() % 200 gives a number 0–199
                // + 200 shifts that range up to 200–399
                beeSpeed = (rand() % 200) + 200;

                // Pick a random vertical height between 500 and 999 pixels
                // rand() % 500 gives 0–499, + 500 gives 500–999
                // (The screen is 1080 tall; this keeps the bee in lower half)
                float height = (rand() % 500) + 500;

                // Place bee at far right (off screen) at the random height
                // x = 2000 is beyond the right edge of the 1920-wide screen
                spriteBee.setPosition(2000, height);

                // Switch to State B — the bee is now "flying"
                beeActive = true;
            }

            // --- STATE B: Bee is active (flying) ---
            // This block runs every frame while beeActive is true.
            else
            {
                // move() adds to the CURRENT position each frame
                // Compare with setPosition() which JUMPS to an absolute spot
                //
                // move(-beeSpeed * dt.asSeconds(), 0) breaks down as:
                //   -beeSpeed          → negative X = moving LEFT
                //   * dt.asSeconds()   → scaled by frame time (0.016s at 60fps)
                //   , 0                → no vertical movement (Y stays same)
                //
                // Example: beeSpeed=300, dt=0.016
                //   movement = -300 × 0.016 = -4.8 pixels left this frame
                spriteBee.move(-beeSpeed * dt.asSeconds(), 0);

                // Check if bee has flown off the LEFT edge
                // x = -100 means fully off screen (bee width is about 100px)
                if (spriteBee.getPosition().x < -100)
                {
                    // Switch BACK to State A — bee will respawn on right side
                    beeActive = false;
                }
            }
        }
        // When paused, the entire update block is skipped.
        // The bee freezes in place until the player unpauses.

        // ----- DRAW ----------------------------------------------------------
        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spriteBee); // ← NEW: draw the bee
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(scoreText);
        window.draw(timeBar);

        if (paused)
            window.draw(messageText);

        window.display();
    }

    return 0;
}

// =============================================================================
// THINGS TO THINK ABOUT:
//
// Q: Why is the bee drawn BETWEEN the tree and the player?
//    A: So it appears in front of the tree bark but behind the player/axe.
//       Layer order: background → tree → bee → player → axe → HUD
//
// Q: Why does beeActive start as false?
//    A: So the VERY FIRST frame sets up a random height and speed.
//       If it started true with no position set, bee would fly from (2000,800)
//       every time — no randomness on the first run.
//
// Q: What does .getPosition().x return?
//    A: The current X coordinate of the sprite as a float.
//       getPosition() returns a Vector2f {x, y}.
//       .x accesses just the X part.
//
// Q: Why -100 as the threshold, not 0?
//    A: At x=0, the LEFT edge of the sprite is at the screen edge.
//       The bee still partially shows. x=-100 ensures it's fully gone.
//
// Q: What if beeSpeed is 0.0f initially?
//    A: It doesn't matter — the bee always hits `if (!beeActive)` first
//       (since beeActive starts false), which sets a proper speed before
//       the bee ever moves.
// =============================================================================
