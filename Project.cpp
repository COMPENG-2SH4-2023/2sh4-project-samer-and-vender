#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs* myGM;
Player myPlayer;

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    
    myGm = new GameMechs();
    myPlayer = new(Player(myGM))

}

void GetInput(void)
{
    
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    objPos tempPos;
    myPlayer.getPlayerPos(temPos);
    MacUILib_printf("BoardSize: %d%d, Player Pos: <%d, %d> + %c\n", 
    myGM->getBoardSizeX(), myGM->getBoardSizeY(), 
    tempPos.x, tempPos.y, tempPos.symbol){

    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
