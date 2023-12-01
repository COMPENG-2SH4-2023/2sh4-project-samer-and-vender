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

    myFood->generateFood(myPlayer->getPlayerPos());

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

    if(game->getLoseFlagStatus()){
        MacUILib_printf("You Lost :(");
        game->setExitTrue();
    }

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempFood;
    string toPrint = "";
    objPos tempBody;

    myFood->getFoodPos(tempFood);
    
    MacUILib_printf("%d", playerBody->getSize());
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

            if(j == 0 || j == game->getBoardSizeY()-1 || i == 0 || i == game->getBoardSizeX()-1){
                MacUILib_printf("#");
            }
            
            //else if(i == tempBody.x && j == tempBody.y)
                //MacUILib_printf("%c", tempBody.symbol);

            else if(i == tempFood.x && j == tempFood.y){
                MacUILib_printf("%c", tempFood.symbol);

            }else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");

    //MacUILib_printf("Score: %d\n", game->getScore());
    //MacUILib_printf("Food Pos: <%d, %d>\n", tempFood.x, tempFood.y); 
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
