# Q01: Hello ITER Mouse Click

## 1. Question Statement
Create an SFML program that displays the text "Hello ITER" when the left mouse button is clicked and hides the text when the left mouse button is released.

---

## 2. Idea in Simple English
The program opens a black window. We create a text object saying "Hello ITER" and center it, but we keep it hidden by default. We track whether to show or hide this text using a boolean variable (`showText`). 
- When the user presses the left mouse button, an event is sent, and we set `showText` to `true`.
- When the user releases the left mouse button, another event is sent, and we set `showText` to `false`.
In the rendering part of the loop, we only draw the text if `showText` is `true`.

---

## 3. Step-by-Step Explanation
1. **Window Creation**: Initialize a window of size `800x600` and set the framerate limit to 60.
2. **Font Loading**: Load a font from the computer because SFML cannot render text without a font file. We check a standard Linux folder (`/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf`) and then check the current directory.
3. **Text Configuration**: Create an `sf::Text` object, assign the loaded font to it, change size, and center it on the screen.
4. **Visibility Flag**: Define a boolean variable `showText` initialized to `false`.
5. **Event Handling**: 
   - Listen for `Event::MouseButtonPressed`. If the button is `Mouse::Left`, set `showText = true`.
   - Listen for `Event::MouseButtonReleased`. If the button is `Mouse::Left`, set `showText = false`.
6. **Drawing**: Inside the draw section, clean the screen, draw the text if `showText` is true, and then display the screen.

---

## 4. Important SFML Functions Used
* `RenderWindow(VideoMode, title)`: Creates the graphical application window.
* `font.loadFromFile(path)`: Loads standard vector font files.
* `text.setFont(font)`: Associates a font with the text object.
* `text.setString(string)`: Sets the message to render.
* `text.getLocalBounds()`: Retrieves the width and height of the text box for centering.
* `text.setOrigin(x, y)`: Sets the anchor point of the text (useful to center it).
* `window.pollEvent(event)`: Fetches user actions (clicks, keypresses) from the operating system queue.

---

## 5. How to Compile
Run the following command in your Ubuntu terminal:
```bash
g++ Q01_Hello_ITER_Mouse_Click.cpp -o Q01_app -lsfml-graphics -lsfml-window -lsfml-system
```

---

## 6. How to Run
Run the executable using:
```bash
./Q01_app
```

---

## 7. Viva Questions
1. **Q: Why does the program display a blank screen or box instead of characters?**
   * *A:* This happens because the font file (`.ttf`) failed to load or the path was incorrect. SFML requires an external font file to draw text.
2. **Q: What is the difference between `sf::Event::MouseButtonPressed` and `sf::Mouse::isButtonPressed`?**
   * *A:* `MouseButtonPressed` is an *event* triggered once when the button is clicked down. `Mouse::isButtonPressed` is a *real-time check* that returns true continuously as long as the mouse button remains pressed.
3. **Q: How does `getLocalBounds()` help in centering text?**
   * *A:* It returns the local bounding box (`width` and `height`) of the text. Setting the origin to half of the width and height puts the alignment anchor at the center, making it easy to center the text on the screen.
4. **Q: Why do we write `using namespace sf;`?**
   * *A:* It allows us to omit the prefix `sf::` when writing SFML classes like `sf::RenderWindow`, `sf::Text`, etc.
5. **Q: What happens if you forget `window.display()`?**
   * *A:* The window will remain blank (usually black), because the draw commands are done on a hidden buffer and `display()` is what shows them on the screen.

---

## 8. Common Mistakes
* **Wrong Font Path**: Writing `font.loadFromFile("arial.ttf")` and forgetting to copy the font file to the terminal's working directory.
* **Wrong Event Check**: Checking `event.key.code` instead of `event.mouseButton.button` when handling mouse click events.
* **Missing Window Clear**: Forgetting `window.clear()`, which causes the text to leave trails on the screen if its position changes.

---

## 9. 30-Second Exam Revision
* Mouse click event: `event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left`
* Mouse release event: `event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left`
* Toggle state boolean: `showText = true` (on press) and `showText = false` (on release).
* Remember: Link library flags `-lsfml-graphics -lsfml-window -lsfml-system` at the end of compilation!
