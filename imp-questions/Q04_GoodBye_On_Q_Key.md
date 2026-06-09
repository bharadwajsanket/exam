# Q04: GoodBye On Q Key

## 1. Question Statement
When the player presses the Q key, display the message "Good Bye". The message should disappear when the key is released, and the game should terminate.

---

## 2. Idea in Simple English
The program starts with a black window. We create a red text saying "Good Bye" in the center, which is hidden by default. We track key states using the window event system:
- When the user presses the `Q` key, we detect it inside `pollEvent` and set a visibility flag `showMessage` to `true`.
- When the user releases the `Q` key, we set `showMessage` to `false` (hiding the text) and call `window.close()`, which closes the screen and terminates the program.

---

## 3. Step-by-Step Explanation
1. **Initialize text**: Set up a font and construct an `sf::Text` with the string `"Good Bye"`. Center the text inside the window coordinates $(400, 300)$.
2. **State Flag**: Define a boolean variable `showMessage` set to `false`.
3. **Event Polling**: 
   - Look for `Event::KeyPressed` with `event.key.code == Keyboard::Q`. When detected, set `showMessage = true`.
   - Look for `Event::KeyReleased` with `event.key.code == Keyboard::Q`. When detected, set `showMessage = false` and invoke `window.close()`.
4. **Drawing**:
   - Clear the screen with black.
   - If `showMessage` is `true`, render the text object.
   - Display the window. If `window.close()` was called, the loop condition `window.isOpen()` becomes false in the next iteration, exiting `main()`.

---

## 4. Important SFML Functions Used
* `Event::KeyPressed`: Event type indicating a key was pressed down.
* `Event::KeyReleased`: Event type indicating a key was released.
* `window.close()`: Closes the active rendering window and cleans up resources.
* `window.isOpen()`: Returns `true` as long as the window is active (has not been closed).

---

## 5. How to Compile
Compile the code in Ubuntu terminal:
```bash
g++ Q04_GoodBye_On_Q_Key.cpp -o Q04_app -lsfml-graphics -lsfml-window -lsfml-system
```

---

## 6. How to Run
Run the executable:
```bash
./Q04_app
```

---

## 7. Viva Questions
1. **Q: Why does the program close immediately when Q is released?**
   * *A:* Because inside the event loop, when we capture the `Event::KeyReleased` event for the `Q` key, we call `window.close()`. This breaks the main game loop condition `window.isOpen()`.
2. **Q: What is the difference between event-driven key checking and real-time key checking?**
   * *A:* Event-driven check (`Event::KeyReleased`) occurs exactly once when the key changes state. Real-time checking (`sf::Keyboard::isKeyPressed`) checks the state continuously. We use events here because we want the release event to trigger a single close operation.
3. **Q: How does `window.close()` affect the main game loop?**
   * *A:* It closes the graphical window and sets `isOpen()` state to false, which breaks the main loop condition `while (window.isOpen())`.
4. **Q: Can we capture keys without checking `pollEvent`?**
   * *A:* We can check key states using `sf::Keyboard::isKeyPressed()`, but we cannot capture *release events* reliably without standard event polling (`window.pollEvent`).
5. **Q: What color does `sf::Color::Red` specify?**
   * *A:* It represents the solid red color RGB(255, 0, 0) used for rendering shapes and text.

---

## 8. Common Mistakes
* **Instant Exit on Press**: Placing `window.close()` inside the `KeyPressed` section instead of the `KeyReleased` section. This causes the program to close instantly when `Q` is pressed down, meaning the message is never seen.
* **Incorrect Key Mapping**: Checking `Keyboard::Q` under mouse events or mismatching variable types.
* **Missing Close event handling**: Forgetting standard `Closed` event checks inside the loop, meaning you can't close the window using the window close button.

---

## 9. 30-Second Exam Revision
* Press event: `event.type == Event::KeyPressed && event.key.code == Keyboard::Q` $\rightarrow$ `showMessage = true;`
* Release event: `event.type == Event::KeyReleased && event.key.code == Keyboard::Q` $\rightarrow$ `showMessage = false; window.close();`
* Remember: Centering calculation: `text.setOrigin(width / 2.f, height / 2.f);`
* Link tags: `-lsfml-graphics -lsfml-window -lsfml-system` at the end of compilation.
