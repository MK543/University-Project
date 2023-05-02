//
// Created by R4V3N on 04.12.2022.
//

#ifndef CONSOLE_RPG_ENEMY_H
#define CONSOLE_RPG_ENEMY_H
#include <stdlib.h>
#include <string>
using namespace std;
class Enemy {
private:
    int hp;
    int hpMax;
    int level;
    int damageMin;
    int damageMax;
    float dropChance;
    int defence;
    int accuracy;

public:
    Enemy(int level = 0);
    ~Enemy();
    inline bool isAlive(){return this-> hp > 0;};
    string getAsString()const;
    inline const int getDamage()const {return (rand()%(this->damageMax-damageMin+1) + damageMin);}
    void takeDamage(int damage);
    inline int getHp()const {return this->hp;}
    inline int getHpMax()const {return this->hpMax;}
    inline int getLv()const {return this->level;}
    inline int getExp()const {return this->level*100;};
    inline int getGold()const {return this->level*50;};
    inline int getDefense()const {return this->defence;};
    inline int getAccuracy()const {return this->accuracy;};
};


#endif //CONSOLE_RPG_ENEMY_H
