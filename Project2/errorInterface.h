void msgError(const char msgError[]) {
    char* actualPosition, * commend;
    
    //THIS FUNCTION HAS THE ACTUAL POSITION IN THE INPUT
    char beforeChar = (char)getchar();
    putc(666, stdin);
    actualPosition = strchr(inputBuffer, 666);

    if (actualPosition != NULL) {
        actualPosition -= 2;
        *(actualPosition + 2) = (char)beforeChar;
        do {
            actualPosition--;
        } while (*actualPosition != '\n');
        commend = strtok(actualPosition, "\n");
    }
    else {
        commend = strtok(inputBuffer, "\n");
    }
    //--------------------------------------

    if (!strcmp(commend, "[playerB]")) {
        cout << "INVALID OPERATION \"" << commend << ' ' << "\": " << msgError;
    }
    else {
        cout << "INVALID OPERATION \"" << commend << "\": " << msgError;
    }
    exit(-1);
}
