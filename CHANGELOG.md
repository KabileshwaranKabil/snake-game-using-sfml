# Snake Game Enhancement Changelog

## Version 2.0.0 - Enhanced Edition

This document provides a detailed explanation of all enhancements and changes made to the Snake Game project.

---

## Overview of Changes

The game has been significantly enhanced with the following features:
- **Score System**: Real-time score display during gameplay
- **High Score Tracking**: Persistent high score saved to file
- **Pause/Resume**: Ability to pause and resume the game
- **Restart Functionality**: Quick restart after game over
- **Self-Collision Detection**: Snake dies when it hits itself
- **Dynamic Difficulty**: Game speed increases as score grows
- **Start Menu**: Welcome screen with game instructions
- **Improved Game Over Screen**: Shows final score and new high score notification
- **Cross-Platform Compatibility**: Removed Windows-specific dependencies

---

## Detailed Changes

### 1. Cross-Platform Compatibility

**Files Modified:** `Food.h`, `Snake.h`, `Food.cpp`, `Snake.cpp`, `main.cpp`

**Problem:** The original code used Windows-specific types and functions:
- `COORD` struct from `<windows.h>`
- `Sleep()` function from `<Windows.h>`

**Solution:** 
- Created a custom `Point` struct in `Food.h` to replace `COORD`:
```cpp
struct Point {
    int X;
    int Y;
    Point() : X(0), Y(0) {}
    Point(int x, int y) : X(x), Y(y) {}
    bool operator==(const Point& other) const {
        return X == other.X && Y == other.Y;
    }
};
```
- Removed all `#include<windows.h>` and `#include<Windows.h>` directives
- The game loop now uses SFML's built-in timing instead of `Sleep()`

---

### 2. Game State System

**File Modified:** `main.cpp`

**Implementation:** Added an enumeration to manage different game states:
```cpp
enum GameState {
    MENU,      // Start menu screen
    PLAYING,   // Active gameplay
    PAUSED,    // Game paused
    GAME_OVER  // Game ended
};
```

This allows for cleaner code organization and proper handling of different game phases.

---

### 3. Score System

**File Modified:** `main.cpp`

**Features:**
- Score increases by 10 points for each food eaten
- Score is displayed in real-time at the top-left corner of the screen
- Score text uses white color for visibility

**Implementation:**
```cpp
Text scoreText;
scoreText.setFont(font);
scoreText.setCharacterSize(20);
scoreText.setFillColor(Color::White);
scoreText.setPosition(10, 10);
// ...
scoreText.setString("Score: " + std::to_string(score));
window.draw(scoreText);
```

---

### 4. High Score Tracking

**File Modified:** `main.cpp`

**Features:**
- High score is loaded from `highscore.txt` when the game starts
- High score is automatically saved when a new record is achieved
- High score is displayed during gameplay and on the menu screen
- Special "NEW HIGH SCORE!" notification on game over

**Implementation:**
```cpp
int loadHighScore() {
    std::ifstream file("highscore.txt");
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
    }
    return score;
}

void saveHighScore(int score) {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    }
}
```

---

### 5. Pause/Resume Functionality

**File Modified:** `main.cpp`

**Controls:**
- Press `P` or `Space` to toggle pause/resume

**Features:**
- Semi-transparent overlay when paused
- "PAUSED" message with resume instructions
- Game timer stops when paused

**Implementation:**
```cpp
if (Keyboard::isKeyPressed(Keyboard::P)) {
    if (!pKeyPressed) {
        if (gameState == PLAYING) {
            gameState = PAUSED;
        } else if (gameState == PAUSED) {
            gameState = PLAYING;
        }
        pKeyPressed = true;
    }
} else {
    pKeyPressed = false;
}
```

---

### 6. Restart Functionality

**Files Modified:** `Snake.h`, `Snake.cpp`, `main.cpp`

**Control:** Press `R` after game over to restart

**Implementation:** Added a `reset()` method to the Snake class:
```cpp
void Snake::reset(Point newPos) {
    pos = newPos;
    len = 1;
    dir = 0;
    prevDir = 0;
    snakeBody.clear();
    snakeBody.push_back(pos);
}
```

---

### 7. Self-Collision Detection

**Files Modified:** `Snake.h`, `Snake.cpp`, `main.cpp`

**Problem:** The original game only detected wall collisions, not self-collisions.

**Solution:** Added `selfCollided()` method to check if the snake's head intersects with its body:
```cpp
bool Snake::selfCollided() {
    for (size_t i = 0; i < snakeBody.size() - 1; i++) {
        if (pos.X == snakeBody[i].X && pos.Y == snakeBody[i].Y) {
            return true;
        }
    }
    return false;
}
```

---

### 8. Direction Reversal Prevention

**Files Modified:** `Snake.h`, `Snake.cpp`

**Problem:** The snake could instantly reverse direction (e.g., press Left when going Right), causing immediate self-collision.

**Solution:** Track the previous direction and prevent 180-degree turns:
```cpp
void Snake::setDir(int d) {
    if ((d == 'u' && prevDir != 'd') ||
        (d == 'd' && prevDir != 'u') ||
        (d == 'l' && prevDir != 'r') ||
        (d == 'r' && prevDir != 'l') ||
        prevDir == 0) {
        dir = d;
    }
}
```

---

### 9. Dynamic Difficulty (Speed Increase)

**File Modified:** `main.cpp`

**Features:**
- Base speed delay: 0.1 seconds
- Speed increases every 50 points (delay decreases by 0.01 seconds)
- Maximum speed capped at 0.03 seconds delay
- Speed level displayed on screen

**Implementation:**
```cpp
if (score % 50 == 0 && delay > 0.03f) {
    delay -= 0.01f;
}
```

---

### 10. Start Menu Screen

**File Modified:** `main.cpp`

**Features:**
- Game title display
- Control instructions
- High score display
- Press ENTER to start

**Content:**
```
SNAKE GAME

Controls:
Arrow Keys - Move
P or Space - Pause
R - Restart (after game over)
Esc - Quit

Press ENTER to Start!
```

---

### 11. Improved Game Over Screen

**File Modified:** `main.cpp`

**Features:**
- Semi-transparent dark overlay
- Final score display
- "NEW HIGH SCORE!" notification if applicable
- Restart and quit instructions

---

### 12. Wall Collision Fix

**File Modified:** `Snake.cpp`

**Problem:** Original collision detection had off-by-one error.

**Fix:** Changed from `==` to `<=` and `>=` comparisons:
```cpp
bool Snake::collided() {
    if (pos.X <= 0 || pos.X >= WIDTH + 1 || pos.Y <= 0 || pos.Y >= HEIGHT + 1) {
        return true;
    }
    return false;
}
```

---

### 13. Code Quality Improvements

**General Improvements:**
- Moved snake and food from global scope to local (main function)
- Added proper error handling for texture and font loading
- Added explicit type casts to avoid compiler warnings
- Improved code organization with comments
- Added key state tracking for single-press detection (prevents repeated triggers)

---

## File Changes Summary

| File | Changes |
|------|---------|
| `codes/headerfiles/Food.h` | Added `Point` struct, removed Windows dependency |
| `codes/headerfiles/Snake.h` | Added new methods, removed Windows dependency |
| `codes/src/Food.cpp` | Updated to use `Point` struct |
| `codes/src/Snake.cpp` | Added self-collision, direction prevention, reset functionality |
| `codes/src/main.cpp` | Complete rewrite with all new features |
| `.gitignore` | Added `highscore.txt` |
| `CHANGELOG.md` | This documentation file (new) |
| `README.md` | Updated with new features |

---

## Controls Summary

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

---

## Building the Project

The project can be built using:
1. **Visual Studio**: Open `snake-game-using-sfml.sln` and build
2. **g++ (Linux/macOS)**: 
   ```bash
   g++ -o snake codes/src/*.cpp -I codes/headerfiles -lsfml-graphics -lsfml-window -lsfml-system
   ```
3. **g++ (Windows with MinGW)**:
   ```bash
   g++ -o snake.exe codes/src/*.cpp -I codes/headerfiles -lsfml-graphics -lsfml-window -lsfml-system
   ```

---

## Future Enhancement Ideas

- Sound effects and background music
- Different food types with varying point values
- Multiple difficulty presets (Easy, Medium, Hard)
- Snake skin customization
- Obstacle/maze mode
- Multiplayer support
- Leaderboard with multiple high scores
