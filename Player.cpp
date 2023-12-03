#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    
}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
    // return the reference to the playerPosList arrray list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    if(input != 0)  // if not null character
    {
        switch(input)
        {        
            case 27:
                mainGameMechsRef->setExitTrue();    
            case 'w':
            case 'W':
                if(myDir != DOWN){
                    myDir = UP;
                }
                break;

            case 'a':
            case 'A':
                if(myDir != RIGHT){
                    myDir = LEFT;
                }
                break;
             
            case 's':
            case 'S':
                if(myDir != UP){
                    myDir = DOWN;
                }
                break;

            case 'd':
            case 'D':
                if(myDir != LEFT){
                    myDir = RIGHT;
                }
                break;

        }
    }   
}

void Player::movePlayer(Food* myFood)
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    switch(myDir){
        case(LEFT):
            currentHead.x--;
            if(currentHead.x < 1)
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;
        
        case(RIGHT):
            currentHead.x++;
            if (currentHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
                currentHead.x = 1;
            break;

        case(UP):
            currentHead.y--;
            if(currentHead.y < 1)
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            break;

        case(DOWN):
            currentHead.y++;
            if(currentHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
                currentHead.y = 1;
            break;

        default:
            break;
    }

    increasePlayerLength(currentHead);
    
    if(!checkFoodConsumption(myFood, currentHead))
        playerPosList->removeTail();

    else myFood->generateFood(playerPosList, mainGameMechsRef);

    if(checkSelfCollision()){
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
    
}

bool Player::checkFoodConsumption(Food* myFood, objPos currentHead){

    objPosArrayList* foodList = myFood->getFoodList();
    objPos tempFood;
    objPos tempPos;

    for(int i = 0; i < foodList->getSize(); i++){
        myFood->getFoodPos(tempFood, i);

        if(tempFood.x == currentHead.x && tempFood.y == currentHead.y){
            switch(tempFood.symbol){
                case '!':
                    mainGameMechsRef->increaseBoardSize();
                    playerPosList->removeTail();
                    break;
                case '+':
                    mainGameMechsRef->incrementScore();
                    if (playerPosList->getSize() >= 246)
                        break;
                    for(int j = 0; j < 5; j++){
                        playerPosList->getTailElement(tempPos);
                        playerPosList->insertTail(tempPos);
                    }
                    break;
                case '$':
                    for(int j = 0; j < 5; j++)
                        mainGameMechsRef->incrementScore();
                    break;
                default:
                    mainGameMechsRef->incrementScore();
                    break;
            }
            return true;
        }
    }

    return false;
}

void Player::increasePlayerLength(objPos currentHead){
    playerPosList->insertHead(currentHead);
}

bool Player::checkSelfCollision(){
    if (playerPosList->getSize() <= 1) return false;

    objPos currentHead;
    objPos currentPos;

    playerPosList->getHeadElement(currentHead);

    for(int i = 3; i < playerPosList->getSize(); i++){
        playerPosList->getElement(currentPos, i);
        if(currentHead.x == currentPos.x && currentHead.y == currentPos.y)
            return true;
    }
    return false;

}
