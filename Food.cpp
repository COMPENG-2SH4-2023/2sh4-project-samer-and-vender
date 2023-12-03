#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Food.h"

Food::Food(){
    
}

Food::~Food(){
    
}

void Food::generateFood(objPosArrayList* blockOff){
    srand((unsigned) time(NULL));

    int x , y;
    bool generated;

    objPos tempPos;
    
    while(!generated){
        x = (rand()%(30-2)) + 1;
        y = (rand()%(15-2)) + 1;
        generated = true;

        for(int i = 0; i < blockOff->getSize(); i++){
            blockOff->getElement(tempPos, i);
            if(x == tempPos.x, y == tempPos.y)
                generated = false;
        }
    }
    
    foodPos.setObjPos(x, y, 'o');
    
}

void Food::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
