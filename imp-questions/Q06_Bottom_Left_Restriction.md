# Q06: Bottom Left Restriction

## 1. Question Statement
Restrict the player's movement so that it remains entirely within the bottom-left quadrant of the arena and cannot move outside that region.

---

## 2. Idea in Simple English
The program draws a $500 \times 500$ pixel arena outline. We divide the arena into four equal $250 \times 250$ quadrants. We visually highlight the bottom-left quadrant using a semi-transparent yellow rectangle.
The player controls a magenta circle (player) using the keyboard. 
Every frame, as the player moves, we check if the new position crosses the boundaries of the bottom-left quadrant instead of the full arena. The player is locked inside this specific quadrant, meaning the right edge of the quadrant acts as a wall blocking movement to the right, and the top edge of the quadrant acts as a ceiling blocking movement upward. We also offset these walls by the player's radius to ensure no visual overlap.

---

## 3. Step-by-Step Explanation
1. **Initialize Objects**: Create a transparent $500 \times 500$ rectangle positioned at $(150, 50)$ for the arena, and a yellow highlighted $250 \times 250$ rectangle at $(150, 300)$ representing the bottom-left quadrant.
2. **Define Player Circle**: Create a circle of radius 15, center its origin, and place it in the middle of the bottom-left quadrant at $(275, 425)$.
3. **Capture Input**: Process movement vectors based on keyboard keys (Left, Right, Up, Down / WASD).
4. **Define Bottom-Left Quadrant Limits**:
   - The left boundary of the arena is at $X = 150$. The center line (right wall of the quadrant) is at $X = 150 + 250 = 400$.
   - The center line of the arena (top ceiling of the quadrant) is at $Y = 50 + 250 = 300$. The bottom boundary of the arena is at $Y = 50 + 500 = 550$.
   - Account for the player radius ($15.f$) to establish the active clamping coordinates:
     - $X$ range: $[150 + 15, 400 - 15] = [165, 385]$
     - $Y$ range: $[300 + 15, 550 - 15] = [315, 535]$
5. **Clamp Coordinates**: Adjust the candidate position values against these quadrant limits.
6. **Position Player & Render**: Call `player.setPosition()`, redraw screen layers, and display.

---

## 4. Important SFML Functions Used
* `shape.setPosition(x, y)`: Coordinates of the shape.
* `shape.getOrigin()`: Returns the pivot point of the shape.
* `sf::Color(R, G, B, Alpha)`: Constructor supporting alpha transparency (0-255) for overlay UI.

---

## 5. How to Compile
Compile in the Ubuntu terminal:
```bash
g++ Q06_Bottom_Left_Restriction.cpp -o Q06_app -lsfml-graphics -lsfml-window -lsfml-system
```

---

## 6. How to Run
Execute the program:
```bash
./Q06_app
```

---

## 7. Viva Questions
1. **Q: How do you mathematically divide a centered 500x500 arena (at 150, 50) into quadrants?**
   * *A:* The midpoint is $(X_{start} + \frac{Width}{2}, Y_{start} + \frac{Height}{2}) = (150 + 250, 50 + 250) = (400, 300)$.
2. **Q: What coordinates define the bottom-left quadrant?**
   * *A:* $X$ coordinates go from the left edge of the arena ($150$) to the center midpoint ($400$). $Y$ coordinates go from the center midpoint ($300$) to the bottom edge of the arena ($550$).
3. **Q: Why does the Y axis start at 0 at the top and increase downward?**
   * *A:* In computer graphics, the origin $(0, 0)$ is at the top-left corner of the window. The X axis increases to the right, and the Y axis increases downwards.
4. **Q: How can we draw a semi-transparent quadrant layout?**
   * *A:* Initialize a rectangle shape and set its fill color to a color with a low alpha channel value, such as `sf::Color(255, 255, 0, 30)`.
5. **Q: What is the purpose of setting `window.setFramerateLimit(60)`?**
   * *A:* It ensures that update updates run at a constant frequency, making player movement consistent across different computers in the lab.

---

## 8. Common Mistakes
* **Flipped Quadrants**: Restricting the player to $X \in [150, 400]$ and $Y \in [50, 300]$, which is the *top-left* quadrant, or $X \in [400, 650]$ and $Y \in [300, 550]$, which is the *bottom-right* quadrant.
* **Missing Radius Offset on Interior Midpoint Walls**: Forgetting to subtract the player's radius when checking boundaries at the interior quadrant dividers, which causes the circle to clip halfway across the dividers.
* **Single Axis Lock**: Accidentally locking both axes when only one axis boundary is hit. Ensure you evaluate boundary checks for X and Y coordinates independently.

---

## 9. 30-Second Exam Revision
* Bottom-left bounds: $X_{min} = 150$, $X_{max} = 400$, $Y_{min} = 300$, $Y_{max} = 550$.
* Clamp variables with radius ($R$): X: `[150+R, 400-R]`, Y: `[300+R, 550-R]`.
* Complete clamp template:
  ```cpp
  if (nextPos.x < minX) nextPos.x = minX;
  if (nextPos.x > maxX) nextPos.x = maxX;
  if (nextPos.y < minY) nextPos.y = minY;
  if (nextPos.y > maxY) nextPos.y = maxY;
  ```
* Remember to link libraries `-lsfml-graphics -lsfml-window -lsfml-system`.
