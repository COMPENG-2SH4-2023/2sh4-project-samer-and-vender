#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"


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
Food* myFood;

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
    myFood = new Food();

}

void GetInput(void)
{
    if (MacUILib_hasChar())
        game->setInput(MacUILib_getChar());

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
    objPos tempFood;
    string toPrint = "";

    myFood->generateFood(tempPos);//temp

    myPlayer->getPlayerPos(tempPos);
    myFood->getFoodPos(tempFood);
    

    MacUILib_printf("BoardSize: %d, %d,\nPlayer Pos: <%d, %d> + %c\n", 
    game->getBoardSizeX(), game->getBoardSizeY(), 
    tempFood.x, tempFood.y, tempFood.symbol);
    
    for(int j = 0; j < game->getBoardSizeY(); j++){
        for(int i = 0; i < game->getBoardSizeX(); i++){

            if(j == 0 || j == game->getBoardSizeY()-1 || i == 0 || i == game->getBoardSizeX()-1)
                MacUILib_printf("#");

            else if(i == tempPos.x && j == tempPos.y)
                MacUILib_printf("%c", tempPos.symbol);

            else if(i == tempFood.x && j == tempFood.y)
                MacUILib_printf("%c", tempFood.symbol);

            else MacUILib_printf(" ");
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
    delete myFood;
    MacUILib_uninit();
}
