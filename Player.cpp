#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');

    

    // more actions to be included
}


Player::~Player()
{
    
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
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
            playerPos.x--;
            break;
        
        case(RIGHT):
            playerPos.x++;
            break;

        case(UP):
            playerPos.y--;
            break;

        case(DOWN):
            playerPos.y++;
            break;

        default:
            break;
    }

    if(playerPos.y >= mainGameMechsRef->getBoardSizeY()){
        playerPos.y = 1;
    }

    if(playerPos.y < 1){
        playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
    }

    if (playerPos.x >= mainGameMechsRef->getBoardSizeX()-1){
        playerPos.x = 1;
    }

    if(playerPos.x < 1){
        playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
}

