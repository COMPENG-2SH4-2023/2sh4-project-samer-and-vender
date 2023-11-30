#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Food.h"

Food::Food(){
    
}

void Food::generateFood(objPos blockOff){
    srand((unsigned) time(NULL));

    int x = blockOff.x, y = blockOff.y;
    while(x == blockOff.x && y == blockOff.y){
        x = (rand()%(30-2)) + 1;
        y = (rand()%(15-2)) + 1;
    } 
    
    foodPos.setObjPos(x, y, 'o');

    
}

void Food::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}