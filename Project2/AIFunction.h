void AIplaceShip(struct PLAYERS_t* player) {
    char shipDirection, * shipType, direction[4] = { 'N','W','E','S' };
    int y1 = player->StartPY1;
    int y2 = player->StartPY2;
    int x1 = player->StartPX1;
    int x2 = player->StartPX2;
    int shipNumber, shipX, shipY, shipSize;
    bool test = true;

    for (int i = 0; i < sizeof(player->ships) / sizeof(player->ships[0]); i++) {
        for (int j = 0; j < player->ships[i]->cout; j++) {
            struct PLAYERS_t::ships_t::ship_t ship = player->ships[i]->ship[j];
            if (ship.taken) { break; };

            shipNumber = j;
            shipType = (char*)player->shipsType[i];
            shipSize = player->ships[i]->size;

            while (test) {
                shipX = x1 + (rand() % (x2 - x1));
                shipY = y1 + (rand() % (y2 - y1));
                shipDirection = direction[rand() % 4];

                switch (shipDirection) {
                case 'N':
                    if (shipY + shipSize <= y2) {
                        test = false;
                    }
                    break;
                case 'W':
                    if (shipX + shipSize <= x2) {
                        test = false;
                    }
                    break;
                case 'E':
                    if (shipX - shipSize >= x1) {
                        test = false;
                    }
                    break;
                case 'S':
                    if (shipY - shipSize >= y1) {
                        test = false;
                    }
                    break;
                }
            }
            test = true;

            player->ships[i]->ship[j].x = shipX;
            player->ships[i]->ship[j].y = shipY;

            cout << "PLACE_SHIP "
                << shipY << ' '
                << shipX << ' '
                << shipDirection << ' '
                << shipNumber << ' '
                << shipType << endl;
        }
    }
}

void AIshoot(struct PLAYERS_t* player) {
    int xShoot, yShoot, xShip, yShip, sizeShip;
    for (int i = 0; i < sizeof(player->ships) / sizeof(player->ships[0]); i++) {
        for (int j = 0; j < player->ships[i]->cout; j++) {
            xShip = player->ships[i]->ship[j].x;
            yShip = player->ships[i]->ship[j].y;
            sizeShip = player->ships[i]->size;

            for (int i = 0; i < sizeShip; i++) {

                do {
                    xShoot = rand() % borderSize.x;
                    yShoot = rand() % borderSize.y;
                    if (extendedShips && !inRange(yShoot, xShoot, yShip, xShip, sizeShip)) continue;
                } while (border[yShoot][xShoot] == (char*)'#');//UTAT EWENTUALNE SPRAWDZANIE CZY TO NIE SWÓJ

                for (int y = yShip - sizeShip; y < yShip + sizeShip; y++) {
                    for (int x = xShip - sizeShip; x < xShip + sizeShip; x++) {
                        if (x >= 0 && y >= 0 && x < borderSize.x && y < borderSize.y) {
                            if (border[y][x] != NULL && *border[y][x] != '#') {
                                if (!inRange(y, x, yShip, xShip, sizeShip) && extendedShips) {
                                    xShoot = x;
                                    yShoot = y;
                                }
                                else if (!extendedShips) {
                                    xShoot = x;
                                    yShoot = y;
                                }
                                break;
                            }
                        }
                    }
                }

                if (extendedShips) {
                    cout << "SHOOT " << j << ' ' << player->shipsType[i] << ' ' << yShoot << ' ' << xShoot << endl;
                }
                else {
                    cout << "SHOOT " << yShoot << ' ' << xShoot << endl;
                }
            }
        }
    }
}

void AImove(struct PLAYERS_t* player) {
    char moveSide, side[3] = { 'F','L','R' };
    for (int i = 0; i < sizeof(player->ships) / sizeof(player->ships[0]); i++) {
        for (int j = 0; j < player->ships[i]->cout && 0 != player->ships[i]->cout; j++) {
                
            for (int k = 0; k < 3; k++) {//EWENTUALNY DEFINE DO ILOŒCI RUCHU
                if (i == 0 && k == 2) break;
                moveSide = side[rand() % 3];
                cout << "MOVE " << j << ' ' << player->shipsType[i] << ' ' << moveSide << endl;
            }
        }
    }
}
