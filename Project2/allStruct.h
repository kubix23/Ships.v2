struct PLAYERS_t {
    char name = '\0';
    int StartPY1 = 0;
    int StartPX1 = 0;
    int StartPY2 = 21;
    int StartPX2 = 10;
    bool isAI = false;

    struct ships_t {
        int size = -1;
        int cout = -1;
        struct ship_t {
            int number = -1;
            int size = -1;
            bool taken = false;
            int x = -1;
            int y = -1;
            char direction = ' ';
            int moveCout;
            int shootCout;
            char life[11] = { "\0" };
        }ship[MAX_SHIPS];
    }carrier, battleship, cruiser, destroyer;

    const char shipsType[4][4] = { "CAR","BAT","CRU","DES" };
    ships_t* ships[4] = { &carrier,&battleship,&cruiser,&destroyer };

    struct spyList {
        int x = -1;
        int y = -1;
        struct spyList* next = NULL;
        void add(spyList* first, int posY, int posX) {
            spyList* spy = (spyList*)malloc(sizeof(spyList));
            if (spy == NULL) { msgError("MALLOC ERROR"); }

            spy->y = posY;
            spy->x = posX;
            spy->next = first->next;
            first->next = spy;
        }
    }spyPlane;

    void execution();
    int remainingParts(int type);   
    void AIFunction();
};

struct borderSize_t {
    int y = 21;
    int x = 10;
    unsigned int seed = 0;
    struct reefList {
        int x = -1;
        int y = -1;
        struct reefList* next;
        void add(reefList* first, int posY, int posX) {
            reefList* reef = (reefList*)malloc(sizeof(reefList));
            if (reef == NULL) msgError("MALLOC ERROR");

            while (first->next != NULL) {
                first = first->next;
            }

            reef->y = posY;
            reef->x = posX;
            reef->next = first->next;
            first->next = reef;
        }
    }reefList;
};