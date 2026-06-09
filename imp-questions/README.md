# SFML 2.x Practical Exam Survival Kit 🚀

This repository is a complete, beginner-friendly SFML 2.x practical exam survival kit. Each question consists of a standalone, self-contained `.cpp` source file and an accompanying `.md` guide explaining the logic, mathematics, compile commands, and common viva topics.

---

## 📅 Suggested Exam Study Order

We recommend studying the questions in this order, starting from basic input toggles, moving to mouse tracking, and finishing with 2D vector mathematics:

```
Q01 (Mouse Click Text Toggle) 
  ↓
Q04 (Q-Key Text Toggle & App Quit) 
  ↓
Q05 (Smooth Mouse-Following Physics) 
  ↓
Q06 (Sub-Dividing Arena & Quadrant Lock) 
  ↓
Q03 (Clamping Coordinates inside Arena) 
  ↓
Q02 (2D Vector Normalization & Angle Shooting)
```

---

## 🗂️ Complete Exam Directory

### 1. [Q01: Hello ITER Mouse Click](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q01_Hello_ITER_Mouse_Click.md)
* **One-Line Description**: Displays "Hello ITER" when the left mouse button is pressed and hides it when released.
* **Compile**: 
  ```bash
  g++ Q01_Hello_ITER_Mouse_Click.cpp -o Q01_app -lsfml-graphics -lsfml-window -lsfml-system
  ```
* **Run**: 
  ```bash
  ./Q01_app
  ```
* **Source**: [Q01_Hello_ITER_Mouse_Click.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q01_Hello_ITER_Mouse_Click.cpp)

---

### 2. [Q04: GoodBye On Q Key](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q04_GoodBye_On_Q_Key.md)
* **One-Line Description**: Renders "Good Bye" when holding down the `Q` key and terminates the game when released.
* **Compile**: 
  ```bash
  g++ Q04_GoodBye_On_Q_Key.cpp -o Q04_app -lsfml-graphics -lsfml-window -lsfml-system
  ```
* **Run**: 
  ```bash
  ./Q04_app
  ```
* **Source**: [Q04_GoodBye_On_Q_Key.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q04_GoodBye_On_Q_Key.cpp)

---

### 3. [Q05: Player Follows Mouse](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q05_Player_Follows_Mouse.md)
* **One-Line Description**: Player smoothly glides towards the mouse position inside a centered $500 \times 500$ arena.
* **Compile**: 
  ```bash
  g++ Q05_Player_Follows_Mouse.cpp -o Q05_app -lsfml-graphics -lsfml-window -lsfml-system
  ```
* **Run**: 
  ```bash
  ./Q05_app
  ```
* **Source**: [Q05_Player_Follows_Mouse.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q05_Player_Follows_Mouse.cpp)

---

### 4. [Q06: Bottom Left Restriction](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q06_Bottom_Left_Restriction.md)
* **One-Line Description**: Locks player movement inside the bottom-left $250 \times 250$ quadrant of the central arena.
* **Compile**: 
  ```bash
  g++ Q06_Bottom_Left_Restriction.cpp -o Q06_app -lsfml-graphics -lsfml-window -lsfml-system
  ```
* **Run**: 
  ```bash
  ./Q06_app
  ```
* **Source**: [Q06_Bottom_Left_Restriction.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q06_Bottom_Left_Restriction.cpp)

---

### 5. [Q03: Bullet Boundary 500x500](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q03_Bullet_Boundary_500x500.md)
* **One-Line Description**: Controls a bullet inside a centered $500 \times 500$ arena using clamping logic and shape radius offsets.
* **Compile**: 
  ```bash
  g++ Q03_Bullet_Boundary_500x500.cpp -o Q03_app -lsfml-graphics -lsfml-window -lsfml-system
  ```
* **Run**: 
  ```bash
  ./Q03_app
  ```
* **Source**: [Q03_Bullet_Boundary_500x500.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q03_Bullet_Boundary_500x500.cpp)

---

### 6. [Q02: Bullet Towards Mouse](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q02_Bullet_Towards_Mouse.md)
* **One-Line Description**: Fires a bullet from the screen center towards the mouse coordinate with normalized velocity vectors on `F` key press.
* **Compile**: 
  ```bash
  g++ Q02_Bullet_Towards_Mouse.cpp -o Q02_app -lsfml-graphics -lsfml-window -lsfml-system
  ```
* **Run**: 
  ```bash
  ./Q02_app
  ```
* **Source**: [Q02_Bullet_Towards_Mouse.cpp](file:///Users/sanketbharadwaj/Downloads/C++%20LAB/Imp-Questions/Q02_Bullet_Towards_Mouse.cpp)

---

## 🛠️ Quick Setup for Ubuntu (Lab Environment)
If standard SFML libraries are not installed on the system:
```bash
sudo apt update
sudo apt install g++ libsfml-dev -y
```

### ⚠️ Important Linker Note
SFML requires the linker libraries to be loaded in the compiler call. **Always append** `-lsfml-graphics -lsfml-window -lsfml-system` at the end of the `g++` command. Putting them before the source filename will trigger a compilation linking error.
