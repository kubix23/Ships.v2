#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <sstream>

using namespace std;
#define MAX_SHIPS 10


char inputBuffer[BUFSIZ];

bool inRange(int posY, int posX, int centerY, int centerX, double sizeShip);
void addToFogBorder(char** tempBorder, int x, int y, double sizeShip);
void addShipToTable(struct PLAYERS_t* player, int type, char* shipLife, int x, int y, int i);
void addShipToTable_Direction(struct PLAYERS_t* player, int type, char* shipLife, int x, int y, int shipSize, char direction);
void msgError(const char msgError[]);
void borderCreate();
void playerReset(struct PLAYERS_t* player);

//AI FUNCTION
void AIplaceShip(struct PLAYERS_t* player);
void AIshoot(struct PLAYERS_t* player);
void AImove(struct PLAYERS_t* player);

//PLAYER FUNCTION
void place_ship(struct PLAYERS_t* player, int type, char direction, char shipClass[4], int x, int y, int number);
void shoot(int x, int y, int number, char type[4], struct PLAYERS_t* player = NULL);
void move(struct PLAYERS_t* player, int number, char type[4], char moveSide);
void playerPrint(struct PLAYERS_t* player);
void spy(struct PLAYERS_t* player);

//STATE FUNCTION
void set_fleet();
void printTable(int type, char*** table);
void next_player();
void print(int type);
void board_size();
void init_position();
void reef();
void ship();
void setAIPlayer();
void srand();
void save();

//GLOBAL
#include "allStruct.h"
bool extendedShips = false;
char*** border;
struct borderSize_t borderSize;
struct PLAYERS_t player_A, player_B;
PLAYERS_t* players[] = { &player_A,&player_B };
int tour;
char playerRound = player_A.name;


#include "stateFunction.h"
#include "playerFunction.h"
#include "AIFunction.h"
#include "stateInterface.h"
#include "usersInterface.h"
#include "AIInterface.h"
#include "errorInterface.h"
#include "initSettings.h"







int main() {

    initial();

    char commend[30];

    while (true)
    {

        playerRound = players[(tour % (sizeof(players) / sizeof(players[0])))] -> name;
        
        for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
            if (playerRound == players[i]->name && players[i]->isAI) {
                players[i]->AIFunction();
                tour++;
                playerRound = players[(tour % (sizeof(players) / sizeof(players[0])))]->name;
                break;
            }
        }
        cin >> commend;


        if (cin.peek() == EOF) {
            exit(0);
        }

        if(!strcmp(commend,"[state]")){
            state();
        }
        else if (!strncmp(commend, "[player", 7)) {
            if (commend[7] == playerRound && commend[8] == ']' && strlen(commend) == 9) {
                players[tour % (sizeof(players) / sizeof(players[0]))]->execution();
                tour++;
            }
            else if (commend[7] != playerRound) {
                msgError("THE OTHER PLAYER EXPECTED");
            }
        }
        else {
            msgError("INVALID FUNCTION");
        }
        
    }

    return 0;
}