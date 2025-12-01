#ifndef SNAKE_H
#define SNAKE_H
#include "Food.h"
#include<vector>

class Snake {
    Point pos;
    int len;
    int dir;
    int prevDir;  // Track previous direction to prevent 180-degree turns
    std::vector<Point> snakeBody;
public:
    Snake(Point pos);
    Point getPos();
    void setDir(int d);
    void moveSnake();
    bool collided();
    bool selfCollided();  // New: Check if snake hits itself
    bool eaten(Food& food);
    void grow();
    std::vector<Point> getSnakeBody();
    int getLength();
    void reset(Point pos);  // New: Reset snake for restart
};

#endif