
bool inRange(int posY, int posX, int centerY, int centerX, double sizeShip) {
	if (posY >= 0 && posX >= 0 && posX < borderSize.x && posY < borderSize.y) {
		if (sizeShip >= sqrt(pow(abs(centerX - posX), 2) + pow(abs(centerY - posY), 2))) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void addToFogBorder(char** tempBorder, int x, int y, double sizeShip) {
	for (int posY = y - (int)sizeShip; posY <= y + (int)sizeShip; posY++) {
		for (int posX = x - (int)sizeShip; posX <= x + (int)sizeShip; posX++) {
			if (inRange(posY, posX, y, x, sizeShip)) {
				if (border[posY][posX] != NULL) {
					tempBorder[posY][posX] = *border[posY][posX];
				}
				else {	
					tempBorder[posY][posX] = ' ';
				}
			}

		}
	}
}

void addShipToTable(struct PLAYERS_t* player, int type, char* shipLife, int x, int y, int i) {
	if ((x >= 0 && y >= 0 && x < borderSize.x && y < borderSize.y) && border[y][x] != NULL) {
		if (*border[y][x] == '#') {
			msgError("PLACING SHIP ON REEF");
		}
	}
	for (int z = y - 1; z < y + 1;z++) {
		for (int j = x - 1; j < x + 1;j++) {
			if (j >= 0 && z >= 0 && j < borderSize.x && z < borderSize.y) {
				if ((z != y || j != x) && border[z][j] != NULL && *border[z][j] != '#' && border[z][j] != &shipLife[i - 1]) {
					msgError("PLACING SHIP TOO CLOSE TO OTHER SHIP");
				}
			}
		}
	}

	if (type == 0) {// FOR PLACE_SHIP
		if ((x >= player->StartPX1 && x <= player->StartPX2 && y >= player->StartPY1 && y <= player->StartPY2)) {
			if (shipLife[i]) {
				border[y][x] = &(shipLife[i]);
			}
		}
		else {
			msgError("NOT IN STARTING POSITION");
		}
	}
	else if (type == 1) { // FOR SHIP
		if (!(cin.get() - '0')) {
			shipLife[i] = 'x';
		}
		border[y][x] = &(shipLife[i]);

	}
	else if (type == 2) { // FOR MOVE
		if (x >= 0 && y >=	 0 && x < borderSize.x && y < borderSize.y) {
			border[y][x] = &(shipLife[i]);
		}
		else {
			msgError("SHIP WENT FROM BOARD");
		}
	}
}

void addShipToTable_Direction(struct PLAYERS_t* player, int type, char* shipLife, int x, int y, int shipSize, char direction) {
	switch (direction) {
	case 'N':
		for (int i = 0; i < shipSize; i++) {
			addShipToTable(player, type, shipLife, x, y + i, i);
		}
		break;
	case 'E':
		for (int i = 0; i < shipSize; i++) {
			addShipToTable(player, type, shipLife, x - i, y, i);

		}
		break;
	case 'S':
		for (int i = 0; i < shipSize; i++) {
			addShipToTable(player, type, shipLife, x , y - i, i);

		}
		break;
	case 'W':
		for (int i = 0; i < shipSize; i++) {
			addShipToTable(player, type, shipLife, x + i, y, i);
		}
		break;
	}
}

void place_ship(struct PLAYERS_t* player,int type , char direction,char shipClass[4], int x,int y,int number) {
	int shipSize = 0;
	const char shipClassType[][4] = { "CAR","BAT","CRU","DES" };
	
	char* shipLife = NULL;	
	cin.ignore(1);


	for (int i = 0; i < sizeof(shipClassType) / sizeof(shipClassType[0]); i++) {
		if (!strcmp(shipClassType[i], shipClass)) {
			player->ships[i]->ship[number].x = x;
			player->ships[i]->ship[number].y = y;
			player->ships[i]->ship[number].direction = direction;

			shipSize = player->ships[i]->size;

			if (player->ships[i]->ship[number].taken) {
				msgError("SHIP ALREADY PRESENT");
			}else{
				if (player->ships[i]->ship[number].number >= 0) {
					player->ships[i]->ship[number].taken = true;
					player->ships[i]->ship[number].moveCout = i == 0 ? 2 : 3;
					player->ships[i]->ship[number].shootCout = shipSize;
					shipLife = player->ships[i]->ship[number].life;
					break;
				}
				else {
					msgError("ALL SHIPS OF THE CLASS ALREADY SET");
				}
			}
		}
	}
	
	

	addShipToTable_Direction(player, type, shipLife, x, y, shipSize, direction);
}

void shoot(int x,int y,int number, char type[4], struct PLAYERS_t* player) {
	
	//EXTENDED SHIP LOGIC
	
	if (player != NULL) {
		for (int i = 0; i < sizeof(player->shipsType) / sizeof(player->shipsType[0]);i++) {
			if (!strcmp(player->shipsType[i],type)) {
				struct PLAYERS_t::ships_t::ship_t *ship = &player->ships[i]->ship[number];
				int shipCannonX = ship->x;
				int shipCannonY = ship->y;

				switch (ship->direction) {
				case'N':
					shipCannonY++;
					break;
				case'W':
					shipCannonX++;
					break;
				case'E':
					shipCannonX--;
					break;
				case'S':
					shipCannonY--;
					break;
				}
				if (ship->life[1] == 'x') {
					msgError("SHIP CANNOT SHOOT");
				}

				if (ship->shootCout > 0) {
					ship->shootCout--;
				}
				else {
					msgError("TOO MANY SHOOTS");
				}

				if (!inRange(y, x, shipCannonY, shipCannonX, ship->size)) {
					msgError("SHOOTING TOO FAR");
				}
				break;
			}
		}
	}
	//END EXTENDED SHIP LOGIC


	for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
		for (int j = 0; j < sizeof(players[i]->ships) / sizeof(players[i]->ships[0]); j++) {
			for (int k = 0; k < players[i]->ships[j]->cout; k++) {
				if (!players[i]->ships[j]->ship[k].taken && players[i]->ships[j]->ship[k].number >= 0) {
					msgError("NOT ALL SHIPS PLACED");
				}
			}
		}
	}

	if (x >= 0 && y >= 0 && x < borderSize.x && y < borderSize.y) {
		if (border[y][x]) {
			if (*border[y][x] != 'x') {
				*border[y][x] = 'x';
			}
		}		
	}
	else {
		msgError("FIELD DOES NOT EXIST");
	}
	 
}

void move(struct PLAYERS_t* player,int number,char type[4],char moveSide) {
	

	for (int i = 0; i < sizeof(player->shipsType)/sizeof(player->shipsType[0]);i++) {
		if (!strcmp(player->shipsType[i], type)) {
			struct PLAYERS_t::ships_t::ship_t* selectShip = &player->ships[i]->ship[number];

			if (selectShip->moveCout == 0) {
				msgError("SHIP MOVED ALREADY");
			}

			selectShip->moveCout--;
			char* shipDirectionAfter = &selectShip->direction;
			switch (selectShip->direction) {
			case 'N':
				for (int j = 0; j < player->ships[i]->size; j++) {
					border[selectShip->y + j][selectShip->x] = NULL;
				}
				break;
			case 'E':
				for (int j = 0; j < player->ships[i]->size; j++) {
					border[selectShip->y][selectShip->x - j] = NULL;
				}
				break;
			case 'S':
				for (int j = 0; j < player->ships[i]->size; j++) {
					border[selectShip->y - j][selectShip->x] = NULL;
				}
				break;
			case 'W':
				for (int j = 0; j < player->ships[i]->size; j++) {
					border[selectShip->y][selectShip->x + j] = NULL;
				}
				break;
			}

			switch (moveSide) {
			case 'F':
				switch (selectShip->direction) {
				case 'N':
					selectShip->y -= 1;
					break;
				case 'W':
					selectShip->x -= 1;
					break;
				case 'E':
					selectShip->x += 1;
					break;
				case 'S':
					selectShip->y += 1;
					break;
				}
				addShipToTable_Direction(player, 2, selectShip->life, selectShip->x, selectShip->y, player->ships[i]->size, selectShip->direction);
				break;
			case 'L':
				switch (selectShip->direction) {
				case 'N':
					*shipDirectionAfter = 'W';
					selectShip->x -= player->ships[i]->size - 1;
					selectShip->y -= 1;
					break;
				case 'W':
					*shipDirectionAfter = 'S';
					selectShip->x -= 1;
					selectShip->y += player->ships[i]->size - 1;
					break;
				case 'E':
					*shipDirectionAfter = 'N';
					selectShip->x += 1;
					selectShip->y -= player->ships[i]->size - 1;
					break;
				case 'S':
					*shipDirectionAfter = 'E';
					selectShip->x += player->ships[i]->size - 1;
					selectShip->y += 1;
					break;
				}
				addShipToTable_Direction(player, 2, selectShip->life, selectShip->x, selectShip->y, player->ships[i]->size, *shipDirectionAfter);
				break;
			case 'R':
				switch (selectShip->direction) {
				case 'N':
					*shipDirectionAfter = 'E';
					selectShip->x += player->ships[i]->size - 1;
					selectShip->y -= 1;
					break;
				case 'W':
					*shipDirectionAfter = 'N';
					selectShip->x -= 1;
					selectShip->y -= player->ships[i]->size - 1;
					break;
				case 'E':
					*shipDirectionAfter = 'S';
					selectShip->x += 1;
					selectShip->y += player->ships[i]->size - 1;
					break;
				case 'S':
					*shipDirectionAfter = 'W';
					selectShip->x -= player->ships[i]->size - 1;
					selectShip->y += 1;
					break;
				}
				addShipToTable_Direction(player, 2, selectShip->life, selectShip->x, selectShip->y, player->ships[i]->size, *shipDirectionAfter);
				break;
			default:
				msgError("INVALID DIRECTION");
			}
			
			break;
		}
	}
}



void playerPrint(struct PLAYERS_t* player) {
	int x, y , type;
	double sizeShip;
	cin >> type;

	//temp2 BORDER FOR FOG OF WAR
	char** temp2 = (char**)malloc(borderSize.y * sizeof(char*));
	for (int i = 0; i < borderSize.y; i++) {
		temp2[i] = (char*)malloc(borderSize.x * sizeof(char));
	}

	//ASSIGNMENT VALUE
	for (int i = 0; i < borderSize.y; i++) {
		for (int j = 0; j < borderSize.x; j++) {
			temp2[i][j] = '?';
		}
	}

	for (int i = 0; i < sizeof(player->ships) / sizeof(player->ships[0]);i++) {
		for (int j = 0; j < player->ships[i]->cout; j++) {
			if (player->ships[i]->ship[j].taken){
				x = player->ships[i]->ship[j].x;
				y = player->ships[i]->ship[j].y;
				sizeShip = player->ships[i]->ship[j].life[0] == '@' ? player->ships[i]->ship[j].size : 1.5;

				addToFogBorder(temp2, x, y, sizeShip);

			}
		}
	}

	struct PLAYERS_t::spyList* nextSpy = player->spyPlane.next;
	while (nextSpy != NULL) {
		addToFogBorder(temp2, nextSpy->x, nextSpy->y,1.5);
		nextSpy = nextSpy->next;
	}

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
				cout << temp2[i][j];
			}
			else if (type == 0) {
				if (temp2[i][j] == ' ') {
					cout << ' ';
				}
				else if (temp2[i][j] == 'x') {
					cout << 'x';
				}
				else if (temp2[i][j] == '#') {
					cout << '#';
				}
				else if (temp2[i][j] == '?') {
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

	//DELETE OLD BORDER
	for (int i = 0; i < borderSize.y; i++) {
		free(temp2[i]);
	}
	free(temp2);
}

void spy(struct PLAYERS_t* player) {
	int number, y, x;
	cin >> number >> y >> x;
	if (player->carrier.ship[number].life[1] == 'x') {
		msgError("CANNOT SEND PLANE");
	}
	if (player->carrier.ship[number].shootCout <= 0) {
		msgError("ALL PLANES SENT");
	}
	player->carrier.ship[number].shootCout--;
	if (x >= 0 && y >= 0 && x < borderSize.x && y < borderSize.y) {
		player->spyPlane.add(&player->spyPlane, y, x);
	}
	else {
		msgError("PLANE WENT FROM BOARD");
	}
}


int PLAYERS_t::remainingParts(int type) {
	int allLife = 0;
	for (int j = 0; j < sizeof(this->shipsType) / sizeof(this->shipsType[0]); j++) {
		for (int k = 0; k < this->ships[j]->cout; k++) {
			for (int z = 0; z < this->ships[j]->size; z++) {
				if (this->ships[j]->ship[k].life[z] == '+' || this->ships[j]->ship[k].life[z] == '%' || this->ships[j]->ship[k].life[z] == '!' || this->ships[j]->ship[k].life[z] == '@') {
					if (this->ships[j]->ship[k].taken && type == 0) {
						allLife++;
					}
					else if (type == 1) {
						allLife++;
					}
				}
			}
		}
	}
	return allLife;
}