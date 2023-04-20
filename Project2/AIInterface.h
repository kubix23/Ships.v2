void PLAYERS_t::AIFunction() {
    save();
    cout << "[player" << this->name << ']' << endl;
    AIplaceShip(this);
    AIshoot(this); // DO ULEPSZENIA
    AImove(this);
    cout << "[player" << this->name << ']' << endl;
}