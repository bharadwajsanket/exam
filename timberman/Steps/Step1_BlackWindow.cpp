// =============================================================================
// STEP 1 — Creating a Window (The Black Screen)
// =============================================================================
//
// WHAT THIS STEP TEACHES:
//   • How to include SFML
//   • What VideoMode and RenderWindow are
//   • What a View is
//   • The 3-part Game Loop: Events → Update → Draw
//   • Why window.clear(), window.display() are needed every frame
//
// RESULT: A black 1920×1080 window that stays open until you close it.
//
// TO COMPILE (from TimberMan folder):
//   g++ Steps/Step1_BlackWindow.cpp -o Step1.exe
//     -IC:/SFML/include -LC:/SFML/lib
//     -lsfml-graphics -lsfml-window -lsfml-system
// =============================================================================

// ---- INCLUDES ---------------------------------------------------------------
// SFML/Graphics.hpp gives us EVERYTHING we need to draw on screen:
//   RenderWindow, VideoMode, View, Sprite, Texture, Font, Text, Clock etc.
#include <SFML/Graphics.hpp>

// 'using namespace sf' means we can write:
//   Sprite   instead of   sf::Sprite
//   Clock    instead of   sf::Clock
// Without this every SFML type needs 'sf::' in front — it gets tedious fast.
using namespace sf;

// ---- MAIN FUNCTION ----------------------------------------------------------
// Every C++ program MUST have a main() — execution starts here.
int main()
{
    // =========================================================================
    // STEP 1.1 — Define the window size
    // =========================================================================
    // VideoMode holds width and height of the window in pixels.
    // 1920 × 1080 is "Full HD" resolution.
    VideoMode vm(1920, 1080);

    // =========================================================================
    // STEP 1.2 — Create the actual window
    // =========================================================================
    // RenderWindow is the SFML object that represents the OS window on screen.
    // It takes:
    //   • A VideoMode (size)
    //   • A title string (shown in the title bar)
    RenderWindow window(vm, "Timber Game!!!");

    // =========================================================================
    // STEP 1.3 — Set up the View (the camera)
    // =========================================================================
    // A View is like a camera for the game world.
    // FloatRect(left, top, width, height) defines what region the camera shows.
    //
    // Here we say: the camera shows the rectangle starting at (0,0)
    //              and covering 1920 pixels wide and 1080 pixels tall.
    // This matches the window exactly, so there's no scaling or offset.
    //
    // WHY? — If you resize the window later, you can adjust the View so the
    //         game world always maps correctly to the screen.
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // =========================================================================
    // THE GAME LOOP — Runs forever until the window is closed
    // =========================================================================
    // window.isOpen() returns true as long as the window exists.
    // The moment someone calls window.close(), this loop exits and the
    // program ends.
    while (window.isOpen())
    {
        // =====================================================================
        // PART 1 — EVENTS
        // Handle things that happened: key presses, mouse clicks, window close
        // =====================================================================
        // Event is a struct that holds information about one user action.
        Event event;

        // pollEvent fills 'event' with the next pending event.
        // It returns false when there are no more events to process.
        // The while loop processes ALL events that happened since last frame.
        //
        // Why a loop? — Multiple events can pile up in one frame.
        //   e.g., user pressed AND released a key in the same frame.
        while (window.pollEvent(event))
        {
            // Check if the user clicked the red X button on the window
            if (event.type == Event::Closed)
                window.close(); // this makes window.isOpen() return false
        }

        // =====================================================================
        // PART 2 — UPDATE
        // Move things, calculate scores, check collisions
        // (nothing to update yet — we'll add things in later steps)
        // =====================================================================

        // =====================================================================
        // PART 3 — DRAW
        // Wipe screen, draw everything, show result
        // =====================================================================

        // clear() fills the window with solid black.
        // WHY? — Without this, old frames would show through.
        //        Imagine drawing on a whiteboard without erasing first!
        window.clear();

        // --- draw things here (nothing yet) ---

        // display() shows everything we drew.
        // SFML uses "double buffering":
        //   - You draw on a hidden back-buffer (invisible)
        //   - display() swaps it to the visible screen instantly
        // This prevents flickering — you never see a half-drawn frame.
        window.display();

    } // ← end of game loop. We only reach here when window.close() was called.

    return 0; // main returns 0 to the OS to say "program finished OK"
}
