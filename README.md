# Snake Game in SFML
![alt text](screenshots/snakegame-screenshot1.png)
![alt text](screenshots/snakegame-screenshot2.png)

## Overview
This repository contains a classic Snake game implemented in C++ using the SFML (Simple and Fast Multimedia Library). The game showcases fundamental game development concepts such as game loops, event handling, and rendering.

## Features
- **Classic Snake Gameplay**: Control the snake to eat food and grow longer.
- **Smooth Graphics**: Utilizes SFML for rendering graphics.
- **Responsive Controls**: Real-time keyboard input handling.
- **Score System**: Track your current score during gameplay.
- **High Score Tracking**: Persistent high score saved across sessions.
- **Pause/Resume**: Press P or Space to pause the game.
- **Restart**: Press R to restart after game over.
- **Self-Collision**: Game ends if the snake collides with itself.
- **Dynamic Difficulty**: Game speed increases as your score grows.
- **Start Menu**: Welcome screen with game instructions.
- **Cross-Platform**: No Windows-specific dependencies.

## Controls
| Key | Action |
|-----|--------|
| ↑ | Move Up |
| ↓ | Move Down |
| ← | Move Left |
| → | Move Right |
| P / Space | Pause/Resume |
| R | Restart (after game over) |
| Enter | Start game (from menu) |
| Esc | Quit game |


## Getting Started

### Prerequisites
- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., GCC, Clang, MSVC).
  https://sourceforge.net/projects/gcc-win64/
- **SFML Library**: Download and install the SFML library from SFML's official website.
https://www.sfml-dev.org/download/sfml/2.6.1/

### Building

**Visual Studio (Windows):**
1. Open `snake-game-using-sfml.sln`
2. Build the solution

**g++ (Linux/macOS):**
```bash
g++ -o snake codes/src/*.cpp -I codes/headerfiles -lsfml-graphics -lsfml-window -lsfml-system
```

**g++ (Windows with MinGW):**
```bash
g++ -o snake.exe codes/src/*.cpp -I codes/headerfiles -lsfml-graphics -lsfml-window -lsfml-system
```

## How to Play
- **Objective**: Guide the snake to eat food and grow longer.
- **Scoring**: Earn 10 points for each food eaten.
- **Speed**: Game speed increases every 50 points.
- **Game Over**: The game ends if the snake collides with the walls or itself.

## Documentation
See [CHANGELOG.md](CHANGELOG.md) for detailed documentation of all features and changes.

## Contributing
Contributions are welcome! If you have any improvements or bug fixes, feel free to open a pull request

## Acknowledgments
- SFML: Thanks to the SFML team for providing an excellent multimedia library.
- Inspiration: Inspired by the classic Snake game. 


## Contact
For any questions or feedback, feel free to reach out to me at kabileshwaran1896@gmail.com
