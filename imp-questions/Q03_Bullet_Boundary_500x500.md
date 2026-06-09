# Q03: Bullet Boundary 500x500

## 1. Question Statement
Create an SFML program that controls a bullet's movement and prevents it from moving outside a 500 × 500 arena.

---

## 2. Idea in Simple English
We draw a $500 \times 500$ pixel outline square (arena) in the middle of our window. We place a red circle (bullet) in the center of the arena. 
The player can move the bullet in any direction using the arrow keys or WASD keys.
Before updating the bullet's position on screen, we check if the new position would push it outside the arena's boundaries. If the coordinates are too far left, right, up, or down, we reset them to the edge coordinates of the arena. We also offset these checks by the bullet's radius to ensure it doesn't visually bleed past the boundary lines.

---

## 3. Step-by-Step Explanation
1. **Initialize Arena Shape**: Create a transparent `sf::RectangleShape` of size $500 \times 500$. Set its outline thickness to 5 and outline color to White. Center it inside the $800 \times 600$ window by placing it at coordinates $(150, 50)$.
2. **Initialize Bullet Shape**: Create a circle shape of radius 10. Set its origin to the center (coordinates $(10, 10)$) so the positioning is calculated relative to its middle point. Spawn it at coordinates $(400, 300)$.
3. **Capture Inputs**: Check key states continuously using `Keyboard::isKeyPressed()`. Calculate a direction offset (e.g. `movement.x += speed` when the Right key is held).
4. **Boundary Definition**:
   - Arena spans horizontally from $150$ to $650$ ($150 + 500$).
   - Arena spans vertically from $50$ to $550$ ($50 + 500$).
   - Offset the limits by adding the radius to minimum limits and subtracting it from maximum limits.
5. **Clamping logic**: If `nextX < 160`, set `nextX = 160`. If `nextX > 640`, set `nextX = 640`. Perform similar checks for the Y axis.
6. **Set Position**: Update the shape's coordinates with the clamped values, clear screen, draw the boundary and bullet shapes, and display.

---

## 4. Important SFML Functions Used
* `shape.setFillColor(Color::Transparent)`: Makes shape interior clear so underlying colors show through.
* `shape.setOutlineThickness(value)`: Sets border thickness.
* `shape.setOutlineColor(color)`: Sets color of border outline.
* `Keyboard::isKeyPressed(key)`: Returns `true` if specified key is held down.
* `shape.getPosition()`: Returns coordinates of shape.

---

## 5. How to Compile
Compile the source code with:
```bash
g++ Q03_Bullet_Boundary_500x500.cpp -o Q03_app -lsfml-graphics -lsfml-window -lsfml-system
```

---

## 6. How to Run
Execute the binary:
```bash
./Q03_app
```

---

## 7. Viva Questions
1. **Q: How do you draw an empty outline box in SFML?**
   * *A:* Create a shape, set the fill color to transparent (`Color::Transparent`), and set outline thickness and color properties.
2. **Q: Why does the arena position range from 150 to 650 on the X-axis?**
   * *A:* The window width is 800. To center a 500-wide arena, we subtract 500 from 800 (leaving 300) and divide by 2, which gives an offset of 150. The right limit is therefore $150 + 500 = 650$.
3. **Q: Why do we offset boundaries by the shape's radius?**
   * *A:* Because the shape's position tracks its origin (which we set to the center). If we clamp position coordinates exactly to the boundaries, half of the shape will clip through the borders. Offsetting keeps the shape inside.
4. **Q: What is the benefit of using independent X and Y checks for boundaries?**
   * *A:* It allows sliding collision. If the bullet hits the top boundary, the Y coordinate is locked, but it can still move freely left and right along the X-axis.
5. **Q: How do you set the origin of a shape to its center?**
   * *A:* Use `shape.setOrigin(radius, radius)` for a circle, or `shape.setOrigin(width / 2.f, height / 2.f)` for a rectangle.

---

## 8. Common Mistakes
* **Clipping Issues**: Forgetting to account for the shape radius in clamping logic, which causes the circle's edges to cross the boundary lines.
* **Hardcoded Limits**: Hardcoding screen limits (like $0$ and $800$) instead of using the custom $500 \times 500$ arena coordinates ($150$ and $650$).
* **Flipped Signs**: Subtracting the radius from the minimum boundary instead of adding it, which causes the circle to clip out of bounds.

---

## 9. 30-Second Exam Revision
* Arena X range: `[150.f, 650.f]`, Y range: `[50.f, 550.f]`
* Target limits with radius ($R$): X: `[150+R, 650-R]`, Y: `[50+R, 550-R]`
* Clamping logic template:
  ```cpp
  if (nextPos.x < minX) nextPos.x = minX;
  if (nextPos.x > maxX) nextPos.x = maxX;
  ```
* Remember to link libraries `-lsfml-graphics -lsfml-window -lsfml-system`.
