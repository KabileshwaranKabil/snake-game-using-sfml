#ifndef FOOD_H
#define FOOD_H

// Cross-platform coordinate structure
struct Point {
    int X;
    int Y;
    
    Point() : X(0), Y(0) {}
    Point(int x, int y) : X(x), Y(y) {}
    
    bool operator==(const Point& other) const {
        return X == other.X && Y == other.Y;
    }
};

class Food
{
    Point foodPos;
public:
    Food();
    void genFood();
    Point getFoodPos();
};

#endif