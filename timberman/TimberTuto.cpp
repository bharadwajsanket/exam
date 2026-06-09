// ============================================================
//  TIMBER GAME - Main Source File
//  Built with SFML (Simple and Fast Multimedia Library)
//
//  WHAT IS SFML?
//  SFML is a free C++ library that makes it easy to:
//    - Open a game window
//    - Draw images and shapes on screen
//    - Handle keyboard/mouse input
//    - Play sounds
//  Think of it as the "engine" powering this game.
// ============================================================

// HEADERS (libraries we need to include)
#include <SFML/Graphics.hpp> // Core SFML header: window, textures, sprites, text, shapes
#include <sstream>           // For converting numbers to strings (used in score display)
#include <ctime>             // For seeding random numbers using the current time

// 'using namespace' saves us from typing "sf::" and "std::" before every SFML/standard command
using namespace sf;
using namespace std;

// ============================================================
//  HOW IMAGES WORK IN SFML (Texture + Sprite concept)
//
//  Texture = the actual image data loaded into GPU memory
//            (think of it as the photo)
//
//  Sprite  = an object that HOLDS a texture and lets you:
//            - position it anywhere on screen
//            - rotate it
//            - scale it
//            - change its color tint
//            (think of it as a picture frame that holds the photo)
//
//  You ALWAYS need both:  Texture -> loaded from file
//                         Sprite  -> linked to the texture, drawn on screen
//
//  Why separate? Because one Texture can be shared by MANY sprites
//  without loading the image multiple times. (Memory efficient!)
//  Example below: all 3 cloud sprites share ONE cloud texture.
// ============================================================

// ============================================================
//  BRANCH SYSTEM
//  The tree has 6 "slots" for branches (index 0 = top, index 5 = bottom/chop level).
//  Each slot can have a branch on the LEFT, RIGHT, or have NO branch (NONE).
//  Every time the player chops, branches "fall down" one level (like a conveyor belt).
//  A new random branch spawns at the top.
// ============================================================

const int NUM_BRANCHES = 6; // Total branch slots on the tree

// 'enum class Side' is a custom type with only 3 possible values.
// Using an enum makes the code readable — instead of 0,1,2 we say LEFT,RIGHT,NONE.
enum class Side
{
    LEFT,
    RIGHT,
    NONE
};

// Global arrays storing the sprite visuals and logical positions of all 6 branches
Sprite branches[NUM_BRANCHES];      // Array of 6 branch sprites (visual objects)
Side branchPositions[NUM_BRANCHES]; // Array of 6 positions (LEFT / RIGHT / NONE)

// updateBranches() is called every time the player chops.
// It shifts all branches DOWN by one slot (branch at index 0 moves to index 1, etc.)
// then randomly generates a NEW branch at the top (index 0).
void updateBranches(int seed)
{
    // Shift: move each branch down one slot (start from bottom, work upward)
    // j=5 gets what j=4 had, j=4 gets what j=3 had, ... j=1 gets what j=0 had
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    // Generate a random number 0-4 to decide what spawns at the top
    int r = rand() % 5;

    // r=0 -> left branch, r=1 -> right branch, r=2/3/4 -> no branch (NONE)
    // Having 3 outcomes for NONE makes empty slots more likely than branches
    switch (r)
    {
    case 0:
        branchPositions[0] = Side::LEFT;
        break;
    case 1:
        branchPositions[0] = Side::RIGHT;
        break;
    default:
        branchPositions[0] = Side::NONE;
        break;
    }
}
// ------------------------------------------------

int main()
{
    // Seed the random number generator ONCE using current time.
    // Without this, rand() produces the same sequence every run.
    srand((int)time(0));

    // ============================================================
    //  WINDOW SETUP
    //  VideoMode defines the resolution (width x height in pixels).
    //  RenderWindow is the actual game window object — everything is drawn here.
    // ============================================================
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");

    // View = a "camera" / viewport into the game world.
    // FloatRect(0, 0, 1920, 1080) means: show the region from (0,0) to (1920,1080).
    // This ensures the game looks correct at any resolution.
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // ============================================================
    //  BACKGROUND
    //  Step 1: Create a Texture and load the PNG image into it.
    //  Step 2: Create a Sprite, linked to that texture.
    //  The sprite is drawn at (0,0) by default = top-left corner.
    // ============================================================
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground); // covers entire 1920x1080 screen

    // ============================================================
    //  TREE
    //  Positioned at x=810 so it appears roughly in the center of the screen.
    //  y=0 means it starts at the very top of the screen and hangs downward.
    // ============================================================
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810, 0); // (x=810, y=0) -> top-center area

    // ============================================================
    //  CLOUD SYSTEM
    //  3 clouds share ONE texture (memory efficient).
    //  Each cloud has its own sprite, an "active" flag, and a speed variable.
    //  When a cloud goes off the right edge of the screen, it resets to the left.
    // ============================================================
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    // All 3 sprites point to the SAME texture (no duplicate image in memory)
    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);

    // cloudActive = false means the cloud is "waiting to be launched"
    // Once launched, it moves right until it exits the screen, then resets
    bool cloudActive1 = false, cloudActive2 = false, cloudActive3 = false;
    float cloudSpeed1 = 0, cloudSpeed2 = 0, cloudSpeed3 = 0;

    // ============================================================
    //  PLAYER
    //  Player starts on the LEFT side of the tree.
    //  Position (580, 720) = left side of tree, at trunk level.
    //  When player presses Right arrow, position changes to (1200, 720).
    // ============================================================
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(580, 720); // Default: left side

    // ============================================================
    //  AXE
    //  The axe is a separate sprite that appears briefly when chopping.
    //  It has two fixed X positions — one for left side, one for right side.
    //  After each chop, the axe is moved off-screen (x=2000) to "hide" it.
    // ============================================================
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(700, 830); // Default: left chop position

    const float AXE_POSITION_LEFT = 700;   // X position of axe when player is on left
    const float AXE_POSITION_RIGHT = 1075; // X position of axe when player is on right

    Side playerSide = Side::LEFT; // Track which side the player is currently on
    bool acceptInput = false;     // Prevents multiple chops from a single key hold

    // ============================================================
    //  RIP (Gravestone) SPRITE
    //  Shown at the player's location when they are squished by a branch.
    //  Hidden off-screen (x=3000) at all other times.
    //  rip.png is loaded from the graphics folder.
    // ============================================================
    Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    Sprite spriteRip(textureRip);
    spriteRip.setPosition(3000, 720); // Off-screen by default (hidden)

    // ============================================================
    //  BRANCH SPRITES INITIALIZATION
    //  Each branch sprite shares ONE texture (memory efficient, same as clouds).
    //  setOrigin(220, 20) sets the rotation pivot to the center of the branch image,
    //  so when we rotate 180 degrees it flips to the LEFT side correctly.
    //  Initial logical positions are all set to NONE (no branches visible at start).
    // ============================================================
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setOrigin(220, 20);  // pivot near center-left of the sprite
        branchPositions[i] = Side::NONE; // start with no branches
    }

    // Pre-populate the branch system by calling updateBranches 5 times.
    // This fills up all 6 slots with a random initial pattern before the game starts.
    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);
    branchPositions[5] = Side::NONE; // Always clear bottom slot — player stands here safe at start

    // ============================================================
    //  BEE SYSTEM
    //  The bee flies from RIGHT to LEFT across the screen as a visual element.
    //  It doesn't harm the player — it's purely decorative / atmospheric.
    //  When it goes off the LEFT edge, beeActive resets to false, and on the
    //  next frame it gets a new random speed and Y position before re-launching.
    // ============================================================
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee(textureBee);

    bool beeActive = false; // false = waiting to be launched from the right side
    float beeSpeed = 0;     // speed in pixels per second (randomized each launch)

    // ============================================================
    //  UI - FONT + TEXT
    //
    //  Font: loads a TrueType font file (.ttf) from disk.
    //  Text: an SFML object that renders text on screen using a Font.
    //        You can set: font, size, color, position, and actual string content.
    //
    //  scoreText   -> shows current score (top-left)
    //  messageText -> shows "Press Enter to Start", "SQUISHED!!", "Out of Time!" etc.
    //                 It is centered on screen using getLocalBounds() math (see below).
    // ============================================================
    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100); // font size in pixels
    scoreText.setFillColor(Color::Red);
    scoreText.setPosition(20, 20); // near top-left corner

    int score = 0; // player's current score (increments on every chop)

    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start");

    // CENTER the message text on screen:
    // getLocalBounds() returns the bounding box of the text (width + height).
    // setOrigin() moves the sprite's anchor point to its own center.
    // Then setPosition(screen_center) places that anchor at the screen's center.
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(
        textRect.left + textRect.width / 2.0f, // horizontal center of text
        textRect.top + textRect.height / 2.0f  // vertical center of text
    );
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f); // screen center

    // ============================================================
    //  TIME BAR
    //  A red rectangle at the bottom of the screen showing remaining time.
    //  It shrinks from full width (400px) to zero as time runs out.
    //  Formula: bar width = timeBarWidthPerSecond * timeRemaining
    //  This means: every second, the bar shrinks by (400 / 6) ≈ 66.7 pixels.
    // ============================================================
    RectangleShape timeBar;
    float timeBarStartWidth = 400; // full width = 400 pixels
    float timeBarHeight = 80;      // height of the bar
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980); // centered at bottom

    float timeRemaining = 6.0f;                                      // start with 6 seconds
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining; // pixels lost per second

    // ============================================================
    //  GAME STATE
    //  paused = true  -> game is not running (waiting for Enter, or game over)
    //  paused = false -> game is actively running
    // ============================================================
    bool paused = true; // start paused, waiting for player to press Enter

    // ============================================================
    //  CLOCK AND DELTA TIME (dt)
    //  Clock measures real-world elapsed time.
    //  dt (delta time) = time since the last frame in seconds.
    //  WHY? Different computers run at different speeds (FPS).
    //  By multiplying movement/time by dt, everything moves at the
    //  SAME real-world speed regardless of frame rate.
    //  Example: speed=200 means 200 pixels/second, not 200 pixels/frame.
    // ============================================================
    Clock clock;
    Time dt;

    // ============================================================
    //  THE GAME LOOP  (the heart of every game)
    //
    //  This while loop runs CONTINUOUSLY as long as the window is open.
    //  Every single iteration = one "frame" on screen.
    //  A typical game runs this loop 60 times per second (60 FPS).
    //
    //  Each frame does 3 things in order:
    //    1. INPUT   - check what the player pressed
    //    2. UPDATE  - move objects, update timers, check collisions
    //    3. RENDER  - clear old frame, draw everything, display new frame
    // ============================================================
    while (window.isOpen())
    {
        // Restart clock and get delta time (time elapsed since last frame)
        // dt.asSeconds() gives a tiny float like 0.016 (= 1/60 second at 60 FPS)
        dt = clock.restart();

        // ============================================================
        //  1. INPUT PHASE — Event Handling
        //  pollEvent() checks if anything happened (key press, window close, etc.)
        //  It fills the 'event' variable with what happened.
        //  We loop through ALL events that happened this frame.
        // ============================================================
        Event event;
        while (window.pollEvent(event))
        {
            // If the red X on the window is clicked -> close the window
            if (event.type == Event::Closed)
                window.close();

            // If Enter is pressed -> START or RESTART the game
            if (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Enter)
            {
                paused = false;                     // unpause and start playing
                timeRemaining = 6.0f;               // reset timer to 6 seconds
                score = 0;                          // reset score to 0
                acceptInput = true;                 // allow player to chop
                messageText.setString("");          // clear any message (start/gameover text)
                spritePlayer.setPosition(580, 720); // put player back to left side

                // Hide the RIP gravestone sprite off-screen when restarting
                spriteRip.setPosition(3000, 720);

                // Reset branch positions to clear any dangerous leftover pattern
                for (int i = 0; i < NUM_BRANCHES; i++)
                    branchPositions[i] = Side::NONE;

                // Re-populate branches with a fresh random pattern
                updateBranches(1);
                updateBranches(2);
                updateBranches(3);
                updateBranches(4);
                updateBranches(5);
                branchPositions[5] = Side::NONE; // keep bottom row safe at start
            }

            // When the player RELEASES a key, re-allow input for the next chop.
            // Also move the axe off-screen to "hide" it after a chop animation.
            if (event.type == Event::KeyReleased && !paused)
            {
                acceptInput = true;
                spriteAxe.setPosition(2000, 830); // move axe off-screen (hidden)
            }
        }

        // ============================================================
        //  2. UPDATE PHASE — runs only when the game is NOT paused
        //  Everything that changes over time lives here.
        // ============================================================
        if (!paused)
        {
            // ---- TIMER UPDATE ----
            // Subtract the real elapsed time (in seconds) from the remaining time.
            // dt.asSeconds() is very small (e.g. 0.016s), so this drains slowly.
            timeRemaining -= dt.asSeconds();

            // Shrink the time bar proportionally to remaining time
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining,
                                     timeBarHeight));

            // If time runs out -> pause the game and show game-over message
            if (timeRemaining <= 0)
            {
                paused = true;
                messageText.setString("Out of Time!");
            }

            // ---- CLOUD SYSTEM UPDATE ----
            // Each cloud independently checks: am I active?
            //   NO  -> pick a new random speed + y position, place it off the left edge (-200)
            //   YES -> move right using: position += speed * dt (frame-rate independent)
            //          if gone past right edge (x > 1920) -> deactivate so it resets next frame

            if (!cloudActive1)
            {
                cloudSpeed1 = rand() % 200;                   // random speed 0-199 px/sec
                spriteCloud1.setPosition(-200, rand() % 150); // start off left edge, random height
                cloudActive1 = true;
            }
            else
            {
                spriteCloud1.move(cloudSpeed1 * dt.asSeconds(), 0); // move right each frame
                if (spriteCloud1.getPosition().x > 1920)            // gone off right edge?
                    cloudActive1 = false;                           // reset for next launch
            }

            if (!cloudActive2)
            {
                cloudSpeed2 = rand() % 200;
                spriteCloud2.setPosition(-200, (rand() % 300) - 150); // slight altitude variation
                cloudActive2 = true;
            }
            else
            {
                spriteCloud2.move(cloudSpeed2 * dt.asSeconds(), 0);
                if (spriteCloud2.getPosition().x > 1920)
                    cloudActive2 = false;
            }

            if (!cloudActive3)
            {
                cloudSpeed3 = rand() % 200;
                spriteCloud3.setPosition(-200, (rand() % 450) - 150); // wider altitude range
                cloudActive3 = true;
            }
            else
            {
                spriteCloud3.move(cloudSpeed3 * dt.asSeconds(), 0);
                if (spriteCloud3.getPosition().x > 1920)
                    cloudActive3 = false;
            }

            // ---- CHOP LOGIC (Player Input) ----
            // acceptInput is a one-shot flag: it's set to false immediately after a chop
            // and only goes back to true when the player RELEASES the key.
            // This prevents holding down the key from doing rapid-fire chops.
            if (acceptInput)
            {
                // Player pressed LEFT arrow -> chop from left side
                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    playerSide = Side::LEFT;
                    spritePlayer.setPosition(580, 720);            // move player to left side
                    spriteAxe.setPosition(AXE_POSITION_LEFT, 830); // show axe on left

                    score++; // increment score
                    // Add time bonus each chop. Formula breakdown:
                    //   (2 / score) uses INTEGER DIVISION:
                    //     score=1 -> 2/1 = 2 -> bonus = 2.15 seconds
                    //     score=2 -> 2/2 = 1 -> bonus = 1.15 seconds
                    //     score=3+ -> 2/3 = 0 -> bonus = 0.15 seconds (flat)
                    // This gives big bonuses early and a flat +0.15s once you're good at it.
                    timeRemaining += (2 / score) + .15;

                    updateBranches(score); // shift branches down and spawn new one at top
                    acceptInput = false;   // block further input until key is released
                }

                // Player pressed RIGHT arrow -> chop from right side
                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    playerSide = Side::RIGHT;
                    spritePlayer.setPosition(1200, 720);            // move player to right side
                    spriteAxe.setPosition(AXE_POSITION_RIGHT, 830); // show axe on right

                    score++;
                    // Same diminishing returns formula as left side (see above)
                    timeRemaining += (2 / score) + .15;

                    updateBranches(score);
                    acceptInput = false;
                }
            }

            // ---- DEATH DETECTION ----
            // After updateBranches(), the branch that was at index 4 is now at index 5.
            // Index 5 = the BOTTOM of the tree = exactly where the player stands.
            // If branchPositions[5] matches the player's current side -> SQUISHED!
            if (branchPositions[5] == playerSide)
            {
                paused = true;       // freeze the game
                acceptInput = false; // no more input

                // Move player sprite off-screen (hide the player character)
                spritePlayer.setPosition(2000, 720);

                // Show the RIP gravestone at the player's last position
                // LEFT side = x:600, RIGHT side = x:1150 (centered on player area)
                if (playerSide == Side::LEFT)
                    spriteRip.setPosition(600, 720);
                else
                    spriteRip.setPosition(1150, 720);

                // Show death message, re-center it on screen
                messageText.setString("SQUISHED!!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(
                    textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            // ---- BEE UPDATE ----
            // The bee flies from right to left (negative X movement).
            // Same active/inactive pattern as the clouds.
            if (!beeActive)
            {
                beeSpeed = (rand() % 200) + 200;                   // random speed 200-399 px/sec
                spriteBee.setPosition(2000, (rand() % 500) + 500); // start off right edge, random height between y=500-999
                beeActive = true;
            }
            else
            {
                spriteBee.move(-beeSpeed * dt.asSeconds(), 0); // move LEFT (negative x direction)
                if (spriteBee.getPosition().x < -100)          // gone off left edge?
                    beeActive = false;                         // reset for next launch
            }

            // ---- SCORE TEXT UPDATE ----
            // stringstream converts the integer score into a string.
            // Then we set it as the displayed text.
            stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        // ============================================================
        //  BRANCH POSITION SYNC
        //  This runs EVERY frame (even when paused) to keep sprites in sync
        //  with the branchPositions[] logical array.
        //
        //  Branch slots are spaced 150 pixels apart vertically.
        //  index 0 = top (y=0), index 5 = bottom (y=750).
        //
        //  LEFT  branches: placed at x=610, rotated 180° (flips to left side)
        //  RIGHT branches: placed at x=1330, rotated 0° (normal orientation)
        //  NONE  branches: moved off-screen to x=3000 (invisible)
        // ============================================================
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            float height = i * 150; // vertical spacing: 0, 150, 300, 450, 600, 750

            if (branchPositions[i] == Side::LEFT)
            {
                branches[i].setPosition(610, height);
                branches[i].setRotation(180); // flip sprite horizontally to face left
            }
            else if (branchPositions[i] == Side::RIGHT)
            {
                branches[i].setPosition(1330, height);
                branches[i].setRotation(0); // normal orientation faces right
            }
            else
            {
                branches[i].setPosition(3000, height); // move off-screen (hidden)
            }
        }

        // ============================================================
        //  3. RENDER PHASE — Drawing everything to screen
        //
        //  IMPORTANT: Drawing order = layering order (like painting layers).
        //  Things drawn FIRST appear BEHIND things drawn LATER.
        //  So: background first -> clouds -> tree -> branches -> player -> UI on top
        //
        //  Steps:
        //    window.clear()   - wipes the previous frame (prevents ghosting/smearing)
        //    window.draw(...) - paints each sprite/shape onto the back buffer
        //    window.display() - swaps the back buffer to screen (shows the new frame)
        // ============================================================
        window.clear(); // wipe screen (fills with black)

        window.draw(spriteBackground); // layer 1: background image (behind everything)

        window.draw(spriteCloud1); // layer 2: clouds (in front of background)
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree); // layer 3: tree trunk

        for (int i = 0; i < NUM_BRANCHES; i++)
            window.draw(branches[i]); // layer 4: all 6 branch sprites

        window.draw(spritePlayer); // layer 5: player character
        window.draw(spriteRip);    // layer 5b: RIP gravestone (shown only on death)
        window.draw(spriteAxe);    // layer 6: axe (on top of player, briefly visible)
        window.draw(spriteBee);    // layer 7: bee (decorative)

        window.draw(scoreText); // layer 8: UI - score text
        window.draw(timeBar);   // layer 9: UI - time bar

        // The message text is only drawn when the game is paused
        // (start screen, game over screen, or squished screen)
        if (paused)
            window.draw(messageText); // layer 10: overlay message text

        // Display everything we just drew — this is the "flip" that shows the frame
        window.display();
    } // <-- end of game loop: immediately goes back to top for next frame

    return 0; // program ends cleanly when window.close() is called
}