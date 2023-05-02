//
// Created by R4V3N on 14.12.2022.
//

#ifndef CONSOLE_RPG_EVENTS_H
#define CONSOLE_RPG_EVENTS_H
#include <random>
#include <stdlib.h>
#include "Puzzle.h"
#include "Character.h"
#include "dArray.h"
class Events {
private:
    int nrOfEvents;
public:
    Events();
    ~Events();
    void generateEvent(Character &character, dArray<Enemy>& enemies);
    void enemyEncounter(Character &character, dArray<Enemy>& enemies);
    void puzzleEncounter(Character &character);
};


#endif //CONSOLE_RPG_EVENTS_H
