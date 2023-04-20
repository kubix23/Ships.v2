void PLAYERS_t::execution() {
    char commend[30];
    const char commandsName[][30] = {
        "PLACE_SHIP",
        "SHOOT",
        "MOVE",
        "SPY",
        "PRINT"
    };


    while (true) {

        cin >> commend;

        if (!strncmp(commend, "[player", 7)) {
            if (commend[7] == this->name && commend[8] == ']' && strlen(commend) == 9) {
                break;
            }
            else {
                msgError("THE OTHER PLAYER EXPECTED");
            }
        }

        for (int i = 0; i < (sizeof(commandsName) / sizeof(commandsName[0])); i++) {
            if (!strcmp(commandsName[i], commend)) {

                switch (i) {

                case 0:
                    char direction, shipClass[4];
                    int x, y, number;
                    cin >> y >> x >> direction >> number >> shipClass;
                    place_ship(this, 0, direction, shipClass, x, y, number);
                    break;

                case 1:
                    if (!extendedShips) {
                        int x, y;
                        cin >> y >> x;
                        shoot(x, y, 0, 0);
                    }
                    else {
                        int x, y;
                        char type[4];
                        cin >> number >> type;
                        cin >> y >> x;
                        shoot(x, y, number, type, this);
                    }
                    break;
                case 2:
                    char type[4], moveSide;
                    cin >> number >> type >> moveSide;
                    move(this, number, type, moveSide);
                    break;
                case 3:
                    spy(this);
                    break;
                case 4:
                    playerPrint(this);
                    break;
                default:
                    msgError("Invalid commend");
                }
                break;
            }
        }
    }


    for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
        if (!players[i]->remainingParts(1)) {
            cout << this->name << " won";
            exit(this->name);
        }
    }

    playerReset(this);
}
