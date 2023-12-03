#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Food.h"


Food::Food(){
    foodBucket = new objPosArrayList();
    powerFood = new objPosArrayList();

    objPos tempFood;

    //shrink board size
    tempFood.setObjPos(0, 0, '!');
    powerFood->insertTail(tempFood);

    //size - 3
    tempFood.setObjPos(0, 0, '/');
    powerFood->insertTail(tempFood);

    //increase score by 5
    tempFood.setObjPos(0, 0, '$');
    powerFood->insertTail(tempFood);
}

Food::~Food(){
    delete foodBucket;
    delete powerFood;
}

void Food::clearFood(){
    while(foodBucket->getSize() != 0)
        foodBucket->removeTail();
}

void Food::generateFood(objPosArrayList* blockOff, GameMechs* gameRef){
    srand((unsigned) time(NULL));

    int x , y, i = 0;
    bool gen;

    objPos tempPos;
    objPos compPos;

    clearFood();

    while(foodBucket->getSize() < FOOD_COUNT){
        //gen food type
        if(i < 2) powerFood->getElement(tempPos, rand()%3);
        else tempPos.symbol = 'O';

        //gen food pos
        tempPos.x = (rand()%(gameRef->getBoardSizeX()-2)) + 1;
        tempPos.y = (rand()%(gameRef->getBoardSizeY()-2)) + 1;
        
        //check player overlap
        gen = !checkOvelap(blockOff->getSize(), tempPos, blockOff);
       
        //check food overlap
        gen = !checkOvelap(i, tempPos, foodBucket);
        
        if(gen){
            foodBucket->insertTail(tempPos);
            i++;
        }
    }

}

void Food::getFoodPos(objPos &returnPos, int index){
    foodBucket->getElement(returnPos, index);
}

objPosArrayList* Food::getFoodList(){
    return foodBucket;
}

bool Food::checkOvelap(int size, objPos compObj, objPosArrayList* compList){
    objPos tempPos;

    for(int j = 0; j < size; j++){
        compList->getElement(tempPos, j);
        if(compObj.x == tempPos.x, compObj.y == tempPos.y)
            return true;
    }
    return false;
}

