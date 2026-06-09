# Q02: Bullet Towards Mouse

## 1. Question Statement
Create an SFML program where a bullet moves toward the mouse cursor position whenever the F key is pressed.

---

## 2. Idea in Simple English
The program displays a green player box in the center of the window. When the user presses the `F` key:
1. We read the mouse cursor's position.
2. We calculate a path pointing from the player to the mouse coordinates.
3. We scale this path to a fixed speed so the bullet doesn't move too fast or too slow depending on where the mouse was clicked.
4. We spawn a red bullet and make it fly along this path until it goes off the screen boundaries.

---

## 3. Step-by-Step Explanation
1. **Setup Shapes**: Initialize a green rectangle representing the player and a red circle representing the bullet. Center the origins of both shapes.
2. **Keyboard Events**: Inside the event polling loop, check if `event.type == Event::KeyPressed` and if `event.key.code == Keyboard::F`.
3. **Capture Mouse coordinates**: When `F` is clicked, grab the mouse coordinates relative to the window using `Mouse::getPosition(window)`. Convert coordinates from integers to floats.
4. **Vector Math**:
   - Calculate direction: `Vector2f direction = targetPos - startPos;`
   - Calculate distance: `float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);`
   - Normalize and scale: `bulletVelocity = (direction / distance) * bulletSpeed;` (assuming distance > 0).
5. **Move the Bullet**: In the update phase, if `isBulletFlying` is true, add the velocity vector to the bullet position variables. Set the shape position accordingly.
6. **Boundary Check**: If the bullet coordinates cross the window boundaries ($X < 0, X > 800, Y < 0, Y > 600$), set `isBulletFlying = false` to stop drawing it.

---

## 4. Important SFML Functions Used
* `Mouse::getPosition(window)`: Retrieves pixel coordinates of the mouse relative to the window area.
* `event.key.code`: Variable containing the identifier of the key pressed.
* `shape.setPosition(vector)`: Sets coordinates of a shape.
* `shape.getPosition()`: Returns a `Vector2f` containing current coordinates.

---

## 5. How to Compile
Compile using:
```bash
g++ Q02_Bullet_Towards_Mouse.cpp -o Q02_app -lsfml-graphics -lsfml-window -lsfml-system
```

---

## 6. How to Run
Run the compiled code:
```bash
./Q02_app
```

---

## 7. Viva Questions
1. **Q: How do you find the direction vector between two points in 2D space?**
   * *A:* Subtract the source point from the target point: $\vec{D} = \vec{P}_{target} - \vec{P}_{source}$ ($D.x = target.x - source.x$, $D.y = target.y - source.y$).
2. **Q: Why is vector normalization required for bullet movement?**
   * *A:* Normalization scales the direction vector to a length of 1.0. Without normalization, the bullet would move extremely fast if the mouse is far away, and extremely slow if the mouse is close. Normalizing ensures constant speed.
3. **Q: Why do we use `<cmath>` and what does `std::sqrt` compute?**
   * *A:* `<cmath>` provides mathematical operations. `std::sqrt` is used to compute the square root, which is needed to calculate the vector magnitude/distance using the Pythagorean theorem: $distance = \sqrt{dx^2 + dy^2}$.
4. **Q: Why do we cast mouse positions to `float`?**
   * *A:* `Mouse::getPosition(window)` returns integers (`sf::Vector2i`), but position and coordinate changes in SFML shapes use floats (`sf::Vector2f`). Casting is required to avoid type errors.
5. **Q: How do you check if the bullet has gone off screen?**
   * *A:* Check if the bullet's X coordinate is less than 0 or greater than window width, or if its Y coordinate is less than 0 or greater than window height.

---

## 8. Common Mistakes
* **Division by Zero**: Dividing the direction components by distance without checking if `distance > 0`. This causes a program crash or weird behavior if you press `F` while the mouse is exactly on the player.
* **Linker Flags Order**: Placing `-lsfml-*` flags before the source filename during compilation.
* **State Reset Fail**: Forgetting to reset the bullet's coordinate back to the player's position before firing a new shot.

---

## 9. 30-Second Exam Revision
* Direction: `dir = target - source;`
* Distance: `dist = sqrt(dir.x * dir.x + dir.y * dir.y);`
* Velocity: `vel = (dir / dist) * speed;` (if `dist > 0`)
* Update: `pos += vel; bullet.setPosition(pos);`
* Link flags: `-lsfml-graphics -lsfml-window -lsfml-system` at the end.
