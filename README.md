# Snake Game

A classic Snake Game built using **C++ and Object-Oriented Programming (OOP)**. The game runs in the terminal and features interactive controls, multiple difficulty levels, score tracking, and persistent high-score storage.

## Features

- **Snake Movement:** Control the snake using WASD or arrow keys.
- **Food Generation:** Food is randomly generated within the game board.
- **Score System:** Earn 10 points every time the snake eats food.
- **Difficulty Levels:** Choose between Easy, Medium, and Hard.
- **Collision Detection:** Detects wall collisions and self-collisions.
- **Pause & Resume:** Pause the game and resume whenever you want.
- **High Score:** Saves and loads the highest score using file handling.
- **Game Restart:** Restart the game after a game-over event.
- **Modular Architecture:** Organized code using separate header and source files.

## Technologies Used

- **Language:** C++
- **Standard:** C++17
- **Concepts:** Object-Oriented Programming, STL, File Handling
- **Libraries:** Vector, Utility, Algorithm, iostream, fstream
- **Platform:** Linux / Unix Terminal

## Game Controls

| Key | Action |
|---|---|
| W / ↑ | Move Up |
| S / ↓ | Move Down |
| A / ← | Move Left |
| D / → | Move Right |
| P | Pause / Resume |
| Q | Quit |

## Project Structure

```text
Snake-Game/
│
├── main.cc          # Main game loop and game state management
├── config.h         # Game configuration and constants
│
├── snake.h          # Snake class declaration
├── snake.cc         # Snake movement and collision logic
│
├── board.h          # Board class declaration
├── board.cc         # Game board rendering
│
├── menu.h           # Menu class declaration
├── menu.cc          # Game menus and high-score handling
│
├── input.h          # Input function declarations
├── input.cc         # Keyboard input handling
│
└── highscore.txt    # Persistent high-score data (created when saved)
```

## How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/sagargadave/snake-game
```

### 2. Navigate to the Project Directory

```bash
cd Snake-Game
```

### 3. Compile the Project

```bash
g++ main.cc snake.cc board.cc menu.cc input.cc -o snake
```

### 4. Run the Game

```bash
./snake
```

**Note:** This implementation uses Linux/Unix terminal libraries (`termios.h`, `unistd.h`) for real-time keyboard input. It is intended for Linux or a compatible Unix-like environment.

## OOP Concepts Implemented

| Concept | Implementation |
|---|---|
| Classes & Objects | Snake, Board, Menu |
| Encapsulation | Private data members and public methods |
| Abstraction | Game operations exposed through class methods |
| Enumerations | Direction, Difficulty, GameState |
| STL | Vector, Pair, Algorithm |
| File Handling | High-score persistence |
| Modular Programming | Separate header and source files |

## Learning Outcomes

- Improved understanding of C++ and Object-Oriented Programming.
- Practical implementation of STL containers.
- Understanding of game loops and state management.
- Implementing collision detection and movement algorithms.
- Working with terminal input handling and file operations.
- Organizing a C++ project into modular components.

## Author

**Sagar Gadave**

- GitHub: [@sagargadave](https://github.com/sagargadave)

---

⭐ If you find this project interesting, consider giving it a star!
