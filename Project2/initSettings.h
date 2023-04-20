

void borderCreate() {
    border = (char***)malloc(sizeof(char**) * borderSize.y);
    for (int i = 0; i < borderSize.y; i++) {
        border[i] = (char**)malloc(sizeof(char**) * borderSize.x);
    }


    for (int i = 0; i < borderSize.y; i++) {
        for (int j = 0; j < borderSize.x; j++) {
            border[i][j] = NULL;

        }
    }
}

void initial() {
    setvbuf(stdin, inputBuffer, _IOLBF, BUFSIZ);
    borderCreate();
    //PLAYER PROPERTY
    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {

        players[i]->name = char('A' + i);
        players[i]->StartPY1 = (0 + 11 * i);
        players[i]->StartPX1 = 0;
        players[i]->StartPY2 = (9 + 11 * i);
        players[i]->StartPX2 = 9;

        //SHIP PROPERTY
        for (int j = 0; j < 4; j++) {
            players[i]->ships[j]->cout = j + 1;
            players[i]->ships[j]->size = 5 - j;

            for (int k = 0; k <= j; k++) {
                players[i]->ships[j]->ship[k].size = 5 - j;
                players[i]->ships[j]->ship[k].shootCout = players[i]->ships[j]->size;
                if (j == 0) {
                    players[i]->ships[j]->ship[k].moveCout = 2;
                }
                players[i]->ships[j]->ship[k].number = k;


                for (int z = 0; z < 5 - j; z++) {
                    char* lifeSegment = &players[i]->ships[j]->ship[k].life[z];
                    if (z == 0) {
                        *lifeSegment = '@';
                    }
                    else if (5 - j == z + 1) {
                        *lifeSegment = '%';
                    }
                    else if (z == 1) {
                        *lifeSegment = '!';
                    }
                    else {
                        *lifeSegment = '+';
                    }
                }
            }
        }
    }
}

void playerReset(struct PLAYERS_t* player) {
    for (int i = 0; i < sizeof(player->shipsType) / sizeof(player->shipsType[0]); i++) {
        for (int j = 0; j < player->ships[i]->cout; j++) {
            player->ships[i]->ship[j].shootCout = player->ships[i]->size;
            if (!strcmp(player->shipsType[i], "CAR")) {
                player->ships[i]->ship[j].moveCout = 2;
            }
            else {
                player->ships[i]->ship[j].moveCout = 3;
            }
        }
    }
}