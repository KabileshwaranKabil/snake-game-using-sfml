#include "Food.h"
#include<ctime>
#include<cstdlib>

#define WIDTH 80
#define HEIGHT 50

Food::Food() {
    srand(static_cast<unsigned int>(time(NULL)));
    genFood();
}

void Food::genFood() {
    foodPos.X = rand() % WIDTH + 1;
    foodPos.Y = rand() % HEIGHT + 1;
}

Point Food::getFoodPos() {
    return foodPos;
}
