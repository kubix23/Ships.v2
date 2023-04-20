
void state() {
    char commend[30];
    int type;

    const char commandsName[][30] = {
        "PRINT",
        "SET_FLEET",
        "NEXT_PLAYER",
        "BOARD_SIZE",
        "INIT_POSITION",
        "REEF",
        "SHIP",
        "EXTENDED_SHIPS",
        "SET_AI_PLAYER",
        "SRAND",
        "SAVE"
    };
    while (true) {

        cin >> commend;
        if (!strcmp(commend, "[state]")) {
            return;
        }

        for (int i = 0; i < (sizeof(commandsName) / sizeof(commandsName[0])); i++) {
            if (!strcmp(commandsName[i], commend)) {
                switch (i) {

                case 0:
                    cin >> type;
                    print(type);
                    break;
                case 1:
                    set_fleet();
                    break;
                case 2:
                    next_player();
                    break;
                case 3:
                    board_size();
                    break;
                case 4:
                    init_position();
                    break;
                case 5:
                    reef();
                    break;
                case 6:
                    ship();
                    break;
                case 7:
                    extendedShips = true;
                    break;
                case 8:
                    setAIPlayer();
                    break;
                case 9:
                    srand();
                    break;
                case 10:
                    save();
                    break;

                default:
                    msgError("INVALID FUNCTION");
                }
                break;
            }
        }

    }

}