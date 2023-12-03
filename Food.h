#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

#define FOOD_COUNT 5

class Food
{
    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList* blockOff, GameMechs* gameRef);
        void getFoodPos(objPos &returnPos, int index);
        objPosArrayList* getFoodList();

        void clearFood();
        bool checkOvelap(int size, objPos compObj, objPosArrayList* compList);

    private:
        objPosArrayList* foodBucket;
        objPosArrayList* powerFood;

};

#endif