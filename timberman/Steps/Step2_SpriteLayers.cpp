// =============================================================================
// STEP 2 — Loading Images and Drawing Sprite Layers
// =============================================================================
//
// WHAT THIS STEP TEACHES:
//   • The Texture → Sprite pattern (2-step image loading)
//   • setPosition() — placing sprites on screen
//   • Drawing order matters — later draws appear ON TOP
//   • Why you need one Texture for each image but can have many Sprites
//
// NEW IN THIS STEP (compared to Step 1):
//   • Texture objects for background, tree, player, axe
//   • Sprite objects for each
//   • Drawing them in correct layer order
//
// RESULT: A visible game scene with background, tree, player, and axe.
// =============================================================================

#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber Game!!!");

    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // =========================================================================
    // LOADING IMAGES — The Texture/Sprite Pattern
    // =========================================================================
    // In SFML, to display a PNG image you need TWO objects:
    //
    //   Texture — raw image data loaded from disk into memory (RAM)
    //   Sprite  — the actual drawable object that REFERENCES a Texture
    //
    // WHY TWO objects?
    //   Imagine a Texture as a stamp, and Sprites as stamps pressed on paper.
    //   You have ONE rubber stamp (Texture) but can make MANY prints (Sprites).
    //   For branches later, 6 sprites share ONE texture — saves memory!
    //
    // IMPORTANT: The Texture must stay in memory as long as the Sprite uses it.
    //            If Texture is destroyed, Sprite has nothing to draw!

    // ---- Layer 1: Background ------------------------------------------------
    // The background fills the entire 1920×1080 screen.
    Texture textureBackground;
    // loadFromFile() loads the PNG from disk.
    // Path is RELATIVE to where the .exe runs (the TimberMan folder).
    textureBackground.loadFromFile("graphics/background.png");

    // Create a Sprite and immediately attach the Texture to it.
    Sprite spriteBackground(textureBackground);
    // No setPosition needed — by default sprites start at (0, 0)
    // which is the top-left corner, exactly where we want the background.

    // ---- Layer 2: Tree ------------------------------------------------------
    // The tree runs vertically from the top of the screen downward.
    // We place it at x=810 so it's roughly centered.
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);

    // setPosition(x, y):
    //   x=810 — how far from the LEFT edge
    //   y=0   — starts at the TOP of the screen
    spriteTree.setPosition(810, 0);

    // ---- Layer 3: Player ----------------------------------------------------
    // The player stands to the LEFT of the tree.
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer(texturePlayer);

    // x=580 puts the player to the left of the tree (tree is at x=810)
    // y=720 puts the player near the bottom (screen height is 1080)
    spritePlayer.setPosition(580, 720);

    // ---- Layer 4: Axe -------------------------------------------------------
    // The axe is near the player's hands, slightly in front of the tree.
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);

    // x=700 is between player (580) and tree (810)
    // y=830 is roughly at arm height
    spriteAxe.setPosition(700, 830);

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
        // Nothing to update yet. We just display a static scene.

        // ----- DRAW ----------------------------------------------------------
        // CRITICAL: clear() FIRST, then draw, then display()
        window.clear();

        // Drawing order = visual stacking order
        // Each draw() call paints OVER what was drawn before.
        //
        // Think of it like layers of paper:
        //   background is placed on the desk first (bottom)
        //   tree is placed on top of background
        //   player is placed on top of tree
        //   axe is placed on top of player

        window.draw(spriteBackground); // Layer 1 — furthest back
        window.draw(spriteTree);       // Layer 2 — on top of background
        window.draw(spritePlayer);     // Layer 3 — on top of tree
        window.draw(spriteAxe);        // Layer 4 — on top of player

        // SWAP the hidden back-buffer to the visible screen
        window.display();
    }

    return 0;
}

// =============================================================================
// THINGS TO THINK ABOUT:
//
// Q: What happens if you draw spriteTree AFTER spritePlayer?
//    A: The tree would cover the player — order matters!
//
// Q: Why does spriteBackground start at (0,0) without setPosition?
//    A: Sprites default to position (0,0) — the top-left. The background
//       image is sized to fill the screen, so this is exactly right.
//
// Q: What if you flip the draw order and draw spriteAxe before spriteBackground?
//    A: The background would cover everything — axe would be invisible!
//
// Q: The player is at x=580, tree is at x=810. Why isn't the player at x=0?
//    A: The screen is 1920 wide. x=580 visually places the player
//       to the LEFT of the tree but not at the edge of the screen.
// =============================================================================
