# Q05: Player Follows Mouse

## 1. Question Statement
Implement player movement such that the player continuously follows the mouse cursor position within the arena.

---

## 2. Idea in Simple English
The program opens a window containing a centered $500 \times 500$ arena. Inside, we have a blue circle representing the player. 
The player's goal is to move towards the mouse cursor. 
Every frame, we find where the mouse is and calculate the distance between the player and the mouse. If they are far apart, the player moves towards the mouse at a constant speed. If the player gets very close to the mouse, it stops moving to prevent vibrating back and forth (jittering). Finally, we clamp the player's position so that it cannot escape the boundary walls of the arena, even if the mouse cursor goes outside the arena.

---

## 3. Step-by-Step Explanation
1. **Define Shapes**: Create a transparent $500 \times 500$ rectangle at coordinates $(150, 50)$ for the arena, and a blue circle of radius 20 for the player. Center the origin of the circle.
2. **Find Target**: In the update block, get the mouse cursor position using `Mouse::getPosition(window)` and store it as a target vector (`Vector2f target`).
3. **Calculate Tracking Vector**:
   - Vector direction: `direction = target - playerPos;`
   - Distance: `distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);`
4. **Move Smoothly**: If the distance is greater than 2.0 (to avoid jittering):
   - Normalize the direction: `normalizedDir = direction / distance;`
   - Increment position: `nextPos += normalizedDir * std::min(speed, distance);` (using `std::min` prevents the player from overshooting the mouse if the mouse is closer than the step speed).
5. **Clamp coordinates inside the Arena**:
   - Limit X to range $[150 + \text{radius}, 650 - \text{radius}] = [170, 630]$.
   - Limit Y to range $[50 + \text{radius}, 550 - \text{radius}] = [70, 530]$.
6. **Apply Position**: Call `player.setPosition(clampedPos)`. Render and display.

---

## 4. Important SFML Functions Used
* `Mouse::getPosition(window)`: Retrieves current cursor position inside window boundaries.
* `player.getPosition()`: Returns the player's current coordinate vector.
* `std::min(a, b)`: Returns the smaller of two numbers (from `<algorithm>` header).
* `std::sqrt()`: Computes square root (from `<cmath>` header).

---

## 5. How to Compile
Compile code in your Ubuntu terminal:
```bash
g++ Q05_Player_Follows_Mouse.cpp -o Q05_app -lsfml-graphics -lsfml-window -lsfml-system
```

---

## 6. How to Run
Run the executable file:
```bash
./Q05_app
```

---

## 7. Viva Questions
1. **Q: How does tracking the mouse differ from snapping to the mouse?**
   * *A:* Snapping immediately sets the player's coordinates to the mouse coordinates (`player.setPosition(mousePos)`). Tracking moves the player towards the mouse coordinate gradually over time at a fixed speed, which looks smoother.
2. **Q: What is "jittering" in mouse-following logic, and how is it resolved?**
   * *A:* Jittering is rapid shaking that occurs when the player overshoots the mouse cursor position, reverses direction, overshoots it again, and repeats this back and forth. We prevent it using a threshold check (e.g. only move if `distance > 2.0f`) and limiting movement steps to `std::min(speed, distance)`.
3. **Q: What is the math formula to move a player towards a mouse target?**
   * *A:* Let direction $\vec{d} = \vec{T} - \vec{P}$ and distance $dist = |\vec{d}|$. If $dist > \text{threshold}$, the new position is $\vec{P}_{new} = \vec{P} + (\frac{\vec{d}}{dist}) \times speed$.
4. **Q: Why does the clamping range differ from the arena dimensions?**
   * *A:* To account for the player shape's radius. Clamping by the radius prevents the edges of the circle from crossing the borders of the arena.
5. **Q: Why do we call `window.setFramerateLimit(60)`?**
   * *A:* It caps the update speed of the loop, ensuring that the movement speed calculations remain consistent and readable across different PCs.

---

## 8. Common Mistakes
* **Overshooting Jitter**: Forgetting to check distance thresholds or using hardcoded snaps that cause vibrating shapes when the player reaches the mouse cursor.
* **Incorrect Casts**: Attempting to use `mousePos` directly in float math without casting the coordinates from `int` to `float`.
* **Out of Arena Glitch**: Clamping the coordinates to screen bounds ($0$ to $800$) instead of the smaller arena bounds ($150$ to $650$).

---

## 9. 30-Second Exam Revision
* Mouse position: `Vector2f target(Mouse::getPosition(window));`
* Displacement: `dir = target - playerPos; dist = sqrt(dx*dx + dy*dy);`
* Clamp check offset bounds: `[150 + R, 650 - R]` and `[50 + R, 550 - R]`.
* Step size calculation: `normalizedDir * std::min(speed, distance)` to prevent overshooting.
* Compilation library links: `-lsfml-graphics -lsfml-window -lsfml-system`.
