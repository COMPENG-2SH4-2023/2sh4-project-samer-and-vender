#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"

class Food
{
    public:
        Food();

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);

    private:
        objPos foodPos;

};

#endif