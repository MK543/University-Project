//
// Created by R4V3N on 24.11.2022.
//

#ifndef CONSOLE_RPG_GAME_H
#define CONSOLE_RPG_GAME_H
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include "Events.h"
#include <sstream>
using namespace std;

class Game {
private:
    int choice;
    bool playing;
    int activeCharacter;
    Character character;
    vector<Character> characters;
    dArray<Enemy> enemies;
public:
    Game();
    ~Game();
    void mainMenu();
    void initGame();
    string fileName;
    inline bool getPlaying() const {return this->playing;};
    void createNewCharacters();
    void saveCharacters();
    void LoadCharacters();
    void Travel();
    void levelUpCharacter();
    void selectCharacter();
    void rest();
};


#endif //CONSOLE_RPG_GAME_H
