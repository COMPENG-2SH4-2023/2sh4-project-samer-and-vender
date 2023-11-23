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

GameMechs* game;
Player* myPlayer;

int main(void)
{

    Initialize();

    while(!(game->getExitFlagStatus()))  
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

    
    game = new GameMechs();
    myPlayer = new Player(game);

}

void GetInput(void)
{
    
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    objPos tempPos;

    myPlayer->getPlayerPos(tempPos);

    MacUILib_printf("BoardSize: %d, %d,\nPlayer Pos: <%d, %d> + %c\n", 
    game->getBoardSizeX(), game->getBoardSizeY(), 
    tempPos.x, tempPos.y, tempPos.symbol);
    
    for(int j = 0; j < game->getBoardSizeY(); j++){
        for(int i = 0; i < game->getBoardSizeX(); i++){
            if(j == 0 || j == game->getBoardSizeY()-1 || i == 0 || i == game->getBoardSizeX()-1){
                MacUILib_printf("#");
            }
            else if(i == tempPos.x && j == tempPos.y){
                MacUILib_printf("%c", tempPos.symbol);
            } 
            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete game;
    delete myPlayer;
    MacUILib_uninit();
}
