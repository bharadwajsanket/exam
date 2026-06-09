// =============================================================================
// STEP 6 — Branch System: Arrays, Enums, Shifting, and Random Placement
// =============================================================================
//
// WHAT THIS STEP TEACHES:
//   • Global variables — why the branch array must be accessible to a function
//   • enum class Side — giving meaningful names to positions
//   • Array of Sprites — one texture, multiple sprite objects
//   • The "conveyor belt" shifting algorithm in updateBranches()
//   • setRotation() — flipping a sprite 180° for left vs right branches
//   • setOrigin() — why it matters for rotation-based positioning
//   • Off-screen hiding (x=3000) for NONE branches
//   • Calling updateBranches() 5 times to pre-fill the tree
//
// HOW THE BRANCH SYSTEM WORKS:
//
//   The tree has 6 visible branch slots spaced 150px apart vertically.
//   Array index 0 = TOPMOST branch on tree
//   Array index 5 = BOTTOMMOST branch on tree
//
//   When updateBranches() is called:
//     → Every branch shifts DOWN one slot (index 0 → 1, 1 → 2, etc.)
//     → A NEW random branch fills slot 0 (top) = LEFT, RIGHT, or NONE
//
//   Think of it like a queue / conveyor belt moving downward:
//
//     Before update:         After update:
//     [0] = NONE             [0] = RIGHT  ← new random value
//     [1] = LEFT             [1] = NONE   ← was [0]
//     [2] = RIGHT            [2] = LEFT   ← was [1]
//     [3] = NONE             [3] = RIGHT  ← was [2]
//     [4] = LEFT             [4] = NONE   ← was [3]
//     [5] = RIGHT            [5] = LEFT   ← was [4]  (old [5] is lost)
//
//   During DRAWING, each branch's screen position is calculated:
//     LEFT  → x=610,  rotation=180° (branch hangs left)
//     RIGHT → x=1330, rotation=0°   (branch hangs right)
//     NONE  → x=3000                (off screen, invisible)
//
// RESULT: A tree with randomly placed branches that shift when you call
//         updateBranches(). (In the final game, you call it on Space press.)
// =============================================================================

#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
using namespace sf;
using namespace std;

// =========================================================================
// GLOBAL CONSTANTS AND GLOBALS
// =========================================================================
// These are defined OUTSIDE main() so the updateBranches() function
// can access them.
//
// If they were inside main(), updateBranches() couldn't see them.
// That's called "scope" — variables only exist inside their { } block.

const int NUM_BRANCHES = 6; // const = cannot be changed after this line

// ---- enum class Side --------------------------------------------------------
// An enum class defines a NEW type that can only hold the values listed.
// Side can ONLY be: Side::LEFT, Side::RIGHT, or Side::NONE
//
// Why not just use integers (0 for LEFT, 1 for RIGHT, 2 for NONE)?
//   if (side == 0)   ← What does 0 mean? You have to remember.
//   if (side == Side::LEFT)  ← Immediately clear.
//
// enum class (scoped enum) is safer than plain enum because:
//   - Values must be written as Side::LEFT (not just LEFT)
//   - Prevents accidental collisions with other variable names
enum class Side
{
    LEFT,
    RIGHT,
    NONE
};

// ---- Global Arrays ----------------------------------------------------------
// Array of 6 Sprite objects — one for each branch on the tree.
// All 6 will share ONE texture (saves memory).
Sprite branches[NUM_BRANCHES];

// Array of 6 Side values — tracks where each branch is (LEFT/RIGHT/NONE)
// This is the LOGICAL data. branches[] is the VISUAL data.
// They stay in sync: branches[i] is drawn based on branchPositions[i].
Side branchPositions[NUM_BRANCHES];

// ============================================================================
// FUNCTION: updateBranches()
// ============================================================================
// This function is called every time the player chops (presses Space).
// Each call shifts the branch pattern DOWN and adds a new random branch at top.
//
// Parameter 'seed' is accepted but not actually used here — it's passed in
// the original code's calls but rand() doesn't need it. Keep it for
// compatibility with the final Timber.cpp.
void updateBranches(int seed)
{
    // ---- STEP 1: Shift all branches down one slot ---------------------------
    // We go BACKWARDS from the bottom (index 5) to index 1.
    // Each branch copies the value of the one ABOVE it.
    //
    // WHY backwards? If we went forward:
    //   branchPositions[1] = branchPositions[0];   // [0] value now in [1]
    //   branchPositions[2] = branchPositions[1];   // WRONG! [1] already changed
    //   We'd copy the NEW [1] instead of the original [1].
    //
    // Going backwards is safe:
    //   j=5: branchPositions[5] = branchPositions[4];  // save old [4] into [5]
    //   j=4: branchPositions[4] = branchPositions[3];  // save old [3] into [4]
    //   j=3: branchPositions[3] = branchPositions[2];  // etc.
    //   j=2: branchPositions[2] = branchPositions[1];
    //   j=1: branchPositions[1] = branchPositions[0];
    //   (j=0 is NOT copied — it will be overwritten with new random value)
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    // ---- STEP 2: Assign a new random branch at index 0 (top) ----------------
    // rand() % 5 → random number from 0 to 4
    //   case 0 → LEFT
    //   case 1 → RIGHT
    //   case 2,3,4 → NONE  (3 out of 5 chances = 60% chance of no branch)
    int r = rand() % 5;

    switch (r)
    {
    case 0:
        branchPositions[0] = Side::LEFT;
        break;
    case 1:
        branchPositions[0] = Side::RIGHT;
        break;
    default: // cases 2, 3, 4 all land here
        branchPositions[0] = Side::NONE;
        break;
    }
}

// ============================================================================
// MAIN
// ============================================================================
int main()
{
    srand(time(0)); // seed random ONCE

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // ---- Sprites (from Step 2) ----------------------------------------------
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

    // ---- Bee (from Step 5) --------------------------------------------------
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee(textureBee);
    spriteBee.setPosition(2000, 800);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    bool paused = true;
    Clock clock;
    Time dt;

    // =========================================================================
    // NEW: BRANCH INITIALIZATION
    // =========================================================================
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    // ---- Set up all 6 branch sprites ----------------------------------------
    // This loop runs 6 times (i = 0, 1, 2, 3, 4, 5)
    // Each iteration initializes one branch sprite.
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        // All branches share the SAME texture (one PNG, 6 sprites)
        branches[i].setTexture(textureBranch);

        // Hide all branches off-screen to start
        // We'll position them correctly in the draw loop
        branches[i].setPosition(-2000, -2000);

        // ---- setOrigin — The pivot point for rotation ----
        // The branch image is horizontal (pointing right by default).
        // When we rotate it 180° for a LEFT branch, it rotates around
        // the ORIGIN point.
        //
        // setOrigin(220, 20) sets the pivot to 220px from left, 20px from top.
        // This point is roughly where the branch meets the tree trunk.
        // So rotation happens around the trunk attachment point — looks natural!
        //
        // (220, 20) was chosen by looking at the branch.png dimensions
        // and finding the "trunk attachment" pixel approximately.
        branches[i].setOrigin(220, 20);

        // Mark all branch slots as NONE (no branch)
        branchPositions[i] = Side::NONE;
    }

    // ---- Pre-fill the tree with branches ------------------------------------
    // Call updateBranches() 5 times to populate the tree before the game shows.
    // Without this, ALL branches would be NONE on startup — the tree looks empty.
    //
    // Each call shifts the conveyor and adds a new random branch at the top.
    // After 5 calls, the bottom 5 slots have been filled with random values.
    // (Slot 0 gets filled on the 5th call, slots 1–4 shifted from previous calls)
    for (int i = 0; i < 5; i++)
        updateBranches(i);

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

            // NOTE: Space bar chopping (calling updateBranches + score++)
            // is NOT added here yet — that's the next feature to implement!
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

            // ---- Bee logic (from Step 5) ------------------------------------
            if (!beeActive)
            {
                beeSpeed = (rand() % 200) + 200;
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                spriteBee.move(-beeSpeed * dt.asSeconds(), 0);
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }
        }

        // =====================================================================
        // BRANCH RENDER POSITIONING
        // This runs EVERY frame (not just when unpaused) so branches always
        // appear even on the start screen.
        // =====================================================================
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            // Each branch i is placed 150 pixels lower than the one above it.
            // i=0 → height=0    (top branch)
            // i=1 → height=150
            // i=2 → height=300
            // i=3 → height=450
            // i=4 → height=600
            // i=5 → height=750  (bottom branch)
            float height = i * 150;

            if (branchPositions[i] == Side::LEFT)
            {
                // Left branch: placed at x=610 (left side of trunk)
                // Rotation 180° flips the branch to point LEFT
                // The setOrigin(220,20) means the pivot = trunk attachment
                // So branch hangs to the LEFT of x=610
                branches[i].setPosition(610, height);
                branches[i].setRotation(180);
            }
            else if (branchPositions[i] == Side::RIGHT)
            {
                // Right branch: placed at x=1330 (right side of trunk)
                // Rotation 0° is default — branch points RIGHT
                branches[i].setPosition(1330, height);
                branches[i].setRotation(0);
            }
            else // Side::NONE
            {
                // Push it way off screen so it's invisible
                // x=3000 is way past the right edge (screen is 1920 wide)
                branches[i].setPosition(3000, height);
            }
        }

        // ----- DRAW ----------------------------------------------------------
        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteTree);

        // Draw all 6 branches (some visible, some hidden at x=3000)
        for (int i = 0; i < NUM_BRANCHES; i++)
            window.draw(branches[i]);

        window.draw(spriteBee);
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
// Q: Why does the shift loop go from j = NUM_BRANCHES-1 DOWN TO j = 1?
//    A: To avoid overwriting values before we've saved them.
//       Going forward would copy the new value instead of the original.
//
// Q: Why does default in the switch give NONE 3 out of 5 times?
//    A: rand() % 5 gives 0,1,2,3,4. Only 0 = LEFT, 1 = RIGHT.
//       2,3,4 all hit default = NONE. That's 3/5 = 60% chance of no branch.
//       This makes gaps on the tree, which is more realistic and fair.
//
// Q: Why does setRotation(180) make the branch go LEFT?
//    A: The branch image points RIGHT by default (rotation=0).
//       Rotating 180° around the origin (220,20) = trunk attachment
//       flips it to point LEFT while staying connected at the trunk.
//
// Q: Why pre-fill with 5 updateBranches() calls?
//    A: Without pre-filling, all 6 slots would be NONE on game start.
//       The tree would look bare. 5 calls fills slots 0–4 with random data.
//       (5 is enough — calling 6 would shift the 1st one out before showing)
//
// Q: Why is the branch rendering loop OUTSIDE the `if (!paused)` block?
//    A: So branches are visible even before the game starts.
//       If it were inside the paused check, branches wouldn't show until
//       the player presses Enter.
// =============================================================================
