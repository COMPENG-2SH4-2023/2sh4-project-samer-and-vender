#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
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

void Player::movePlayer()
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    

    switch(myDir){
        case(LEFT):
            currentHead.x--;
            break;
        
        case(RIGHT):
            currentHead.x++;
            break;

        case(UP):
            currentHead.y--;
            break;

        case(DOWN):
            currentHead.y++;
            break;

        default:
            break;
    }

    if(currentHead.y >= mainGameMechsRef->getBoardSizeY()){
        currentHead.y = 1;
    }

    if(currentHead.y < 1){
        currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    }

    if (currentHead.x >= mainGameMechsRef->getBoardSizeX()-1){
        currentHead.x = 1;
    }

    if(currentHead.x < 1){
        currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    }

    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}

