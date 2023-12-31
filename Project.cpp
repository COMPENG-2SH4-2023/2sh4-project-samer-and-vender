#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"


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

    myFood->generateFood(myPlayer->getPlayerPos(), game);

}

void GetInput(void)
{
    if (MacUILib_hasChar())
        game->setInput(MacUILib_getChar());

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(myFood);
    game->clearInput();

    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPosArrayList* foodList = myFood->getFoodList();
    
    objPos tempBody;
    objPos tempFood;
    
    //MacUILib_printf("BoardSize: %d, %d,\nPlayer Pos: <%d, %d> + %c\n", 
    //game->getBoardSizeX(), game->getBoardSizeY(), 
    //tempFood.x, tempFood.y, tempFood.symbol);
    
    for(int j = 0; j < game->getBoardSizeY(); j++){
        for(int i = 0; i < game->getBoardSizeX(); i++){
            drawn = false;
            for(int k = 0; k < playerBody->getSize(); k++){
                playerBody->getElement(tempBody, k);
                if(tempBody.x == i && tempBody.y == j){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;
            for(int k = 0; k < foodList->getSize(); k++){
                foodList->getElement(tempFood, k);
                if(tempFood.x == i && tempFood.y == j){
                    MacUILib_printf("%c", tempFood.symbol);
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;

            if(j == 0 || j == game->getBoardSizeY()-1 || i == 0 || i == game->getBoardSizeX()-1){
                MacUILib_printf("#");
            }
            else if(i == tempFood.x && j == tempFood.y){
                MacUILib_printf("%c", tempFood.symbol);

            }else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", game->getScore());
    //MacUILib_printf("Player Size: %d\n", playerBody->getSize());

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 
    if(game->getLoseFlagStatus())
        MacUILib_printf("\n\nGame Over!\nYou had %d points.\n\n", game->getScore());   
    delete game;
    delete myPlayer;
    delete myFood;
    MacUILib_uninit();
}
