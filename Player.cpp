#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList->objPosArrayList();
    //playerPosList.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');

}


Player::~Player()
{
    
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPosList->insertHead(aList));
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
    switch(myDir){
        case(LEFT):
            playerPosList[0].x--;
            break;
        
        case(RIGHT):
            playerPosList[0].x++;
            break;

        case(UP):
            playerPosList[0].y--;
            break;

        case(DOWN):
            playerPosList[0].y++;
            break;

        default:
            break;
    }

    if(playerPosList[0].y >= mainGameMechsRef->getBoardSizeY()){
        playerPosList[0].y = 1;
    }

    if(playerPosList[0].y < 1){
        playerPosList[0].y = mainGameMechsRef->getBoardSizeY() - 2;
    }

    if (playerPosList[0].x >= mainGameMechsRef->getBoardSizeX()-1){
        playerPosList[0].x = 1;
    }

    if(playerPosList[0].x < 1){
        playerPosList[0].x = mainGameMechsRef->getBoardSizeX() - 2;
    }
}

