int deleteNegative(int number) {
    if (number > 0) {
        return number;
    }
    else {
        return 0;
    }
}

void set_fleet() {
    for (int i = 5; i >= 2; i--) {
        player_A.ships[5 - i]->size = i;
        player_B.ships[5 - i]->size = i;
    }
    char player;
    cin >> player;
    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {

        if (player == (*players[i]).name) {
            for (int j = 0, size; j < 4; j++) {              
                cin >> size;
                players[i]->ships[j]->cout = size ? size : -1;
            }
            break;
        }

    }
}

void printTable(int type,char*** table) {
    if (type == 1) {
        for (int j = 0; j < (int)log10(borderSize.x) + 1; j++) {
            cout << ' ';
        }
        for (int j = 0; j < (int)log10(borderSize.x - 1); j++) {
            cout << '0';
        }
        for (int i = 0; i < borderSize.x; i++) {
            for (int j = 0; j < (int)log10(borderSize.x - 1) - (int)log10(i); j++) {
                cout << '0';
            }
            cout << i;
        }
        cout << endl;
        for (int j = 0; j < (int)log10(borderSize.y - 1); j++) {
            cout << '0';
        }
    }

    for (int i = 0; i < borderSize.y; i++) {
        if (type == 1) {
            for (int j = 0; j < (int)log10(borderSize.y - 1) - (int)log10(i); j++) {
                cout << '0';
            }
            cout << i;
            for (int j = 0; j < (int)log10(borderSize.x - 1); j++) {
                cout << ' ';
            }
        }
        for (int j = 0; j < borderSize.x; j++) {
            if (type == 1) {
                if (table[i][j] == NULL) {
                    cout << ' ';
                }
                else {
                    cout << table[i][j][0];
                }
            }
            else if (type == 0) {
                if (table[i][j] == NULL) {
                    cout << ' ';
                }
                else if (table[i][j][0] == 'x') {
                    cout << 'x';
                }
                else if (table[i][j][0] == '#') {
                    cout << '#';
                }
                else if (table[i][j][0] == '?') {
                    cout << '?';
                }
                else {
                    cout << '+';
                }
            }
            if (type == 1) {
                for (int i = 0; i < (int)log10(borderSize.x - 1); i++) {
                    cout << ' ';
                }
            }
        }
        cout << endl;
    }

}

void next_player() {
    cin >> playerRound;
    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
        if ((players[i]->name) == playerRound) {
            tour = i;
        }
    }
}

void print(int type) {

    printTable(type, border);
    cout << "PARTS REMAINING:: A : " << player_A.remainingParts(0) << " B : " << player_B.remainingParts(0) << endl;
    }

void board_size() {
    int x, y;
    cin >> y >> x;

    //KILL OUT BORDER SHIP PARTS
    for (int i = 0; i < borderSize.y; i++) {
        for (int j = 0; j < borderSize.x; j++) {
            if ((i >= y || j >= x) && border[i][j] != NULL) {
                if (*border[i][j] == '+') {
                    *border[i][j] = 'x';
                }
            }
        }
    }

    //REALLOC TABLE
    border = (char***)realloc(border, sizeof(char**) * y);
    for (int i = 0; i < borderSize.y && i < y; i++) {
        border[i] = (char**)realloc(border[i], sizeof(char**) * x);
    }
    for (int i = borderSize.y; i < y; i++) {
        border[i] = (char**)malloc(sizeof(char**) * x);
    }

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if(i >= borderSize.y || j >= borderSize.x){
                border[i][j] = NULL;
            }
        }
    }

    borderSize.y = y;
    borderSize.x = x;
}

void init_position() {
    char player;
    int y1, x1, y2, x2;
    cin >> player >> y1 >> x1 >> y2 >> x2;
    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
        if (players[i]->name == player) {
            players[i]->StartPX1 = x1;
            players[i]->StartPY1 = y1;
            players[i]->StartPX2 = x2;
            players[i]->StartPX2 = y2;
        }
    }
}

void reef() {
    int y, x;
    cin >> y >> x;
    if (!(x >= 0 && y >= 0 && x < borderSize.x && y < borderSize.y)) {
        msgError("REEF IS NOT PLACED ON BOARD");
    }
    borderSize.reefList.add(&borderSize.reefList, y, x);
    static char reefs = '#';
    border[y][x] = &reefs;
}

void ship() {
    char player;
    char direction, shipClass[4];
    int x, y, number;
    cin >> player;
    cin >> y >> x >> direction >> number >> shipClass;
    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
        if (player == players[i]->name) {
            place_ship(players[i], 1,direction,shipClass,x,y,number);
        }
    }
}

void setAIPlayer() {
    char name;
    cin >> name;
    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
        if (players[i]->name == name) {
            players[i]->isAI = true;  
            break;
        }
    }
}

void srand() {
    unsigned int randomSeed;
    cin >> randomSeed;
    srand(randomSeed);
    borderSize.seed = randomSeed;
}

void save() {
    PLAYERS_t* player;
    cout << "[state]" << endl;
    cout << "BOARD_SIZE " << borderSize.y << ' ' << borderSize.x << endl;
    cout << "NEXT_PLAYER " << players[(tour % (sizeof(players) / sizeof(players[0])))]->name << endl;
    if (borderSize.seed) {
        cout << "SRAND " << borderSize.seed + 1 << endl;
    }   
    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
        player = players[i];
        cout << "INIT_POSITION " << player->name << ' ' << player->StartPY1 << ' ' << player->StartPX1 << ' ' << player->StartPY2 << ' ' << player->StartPX2 << endl;
        cout << "SET_FLEET " << player->name << ' ';
        for (int j = 0; j < sizeof(player->ships) / sizeof(player->ships[0]); j++) {
            cout << deleteNegative(player->ships[j]->cout) << ' ';
        }
        cout << endl;
        for (int j = 0; j < sizeof(player->ships) / sizeof(player->ships[0]); j++) {
            for (int k = 0; k < player->ships[j]->cout;k++) {
                if (player->ships[j]->ship[k].taken) {
                    cout << "SHIP " << player->name << ' ';
                    cout << player->ships[j]->ship[k].y << ' ' << player->ships[j]->ship[k].x << ' ' << player->ships[j]->ship[k].direction << ' ' << player->ships[j]->ship[k].number << ' ' << player->shipsType[j] << ' ';
                    for (int l = 0; l < player->ships[j]->size; l++) {
                        if (player->ships[j]->ship[k].life[l] != 'x') {
                            cout << 1;
                        }
                        else {
                            cout << 0;
                        }
                    }
                    cout << endl;
                }
            }

        }
    }

    cout << "[state]" << endl;

}