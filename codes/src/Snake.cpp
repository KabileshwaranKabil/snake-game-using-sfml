#include "Snake.h"

#define WIDTH 80
#define HEIGHT 50

Snake::Snake(Point pos) {
    this->pos = pos;
    len = 1;
    dir = 0;
    prevDir = 0;
    snakeBody.push_back(pos);
}

Point Snake::getPos() {
    return pos;
}

void Snake::setDir(int d) {
    // Prevent 180-degree turns (can't go directly opposite direction)
    if ((d == 'u' && prevDir != 'd') ||
        (d == 'd' && prevDir != 'u') ||
        (d == 'l' && prevDir != 'r') ||
        (d == 'r' && prevDir != 'l') ||
        prevDir == 0) {
        dir = d;
    }
}

void Snake::moveSnake() {
    prevDir = dir;  // Update previous direction
    switch (dir) {
    case 'u':
        pos.Y--;
        break;
    case 'd':
        pos.Y++;
        break;
    case 'r':
        pos.X++;
        break;
    case 'l':
        pos.X--;
        break;
    default:
        return;  // Don't move if no direction set
    }
    snakeBody.push_back(pos);
    if (snakeBody.size() > static_cast<size_t>(len)) {
        snakeBody.erase(snakeBody.begin());
    }
}

bool Snake::collided() {
    if (pos.X <= 0 || pos.X >= WIDTH + 1 || pos.Y <= 0 || pos.Y >= HEIGHT + 1) {
        return true;
    }
    return false;
}

bool Snake::selfCollided() {
    // Check if head collides with any body segment (excluding the head itself)
    for (size_t i = 0; i < snakeBody.size() - 1; i++) {
        if (pos.X == snakeBody[i].X && pos.Y == snakeBody[i].Y) {
            return true;
        }
    }
    return false;
}

bool Snake::eaten(Food& food) {
    if (pos.X == food.getFoodPos().X && pos.Y == food.getFoodPos().Y) {
        return true;
    }
    return false;
}

void Snake::grow() {
    len++;
}

std::vector<Point> Snake::getSnakeBody() {
    return snakeBody;
}

int Snake::getLength() {
    return len;
}

void Snake::reset(Point newPos) {
    pos = newPos;
    len = 1;
    dir = 0;
    prevDir = 0;
    snakeBody.clear();
    snakeBody.push_back(pos);
}