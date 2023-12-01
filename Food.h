#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
    public:
        Food();

        void generateFood(objPosArrayList* blockOff);
        void getFoodPos(objPos &returnPos);

    private:
        objPos foodPos;

};

#endif