#ifndef CONSOLE_RPG_CHARACTER_H
#define CONSOLE_RPG_CHARACTER_H
#include <string>
#include <iostream>
#include "Inventory.h"
#include "Enemy.h"
#include "Helmet.h"
#include "Gauntlet.h"
#include "Torso.h"
#include "Legs.h"
using namespace std;
class Character {
private:
    Inventory inventory;
    Weapon* weapon;
    Helmet* armorHead;
    Torso* armorChest;
    Gauntlet* armorArms;
    Legs* armorLegs;
    string name;
    int gold;
    int distanceTravelled;
    int level;
    int exp;
    int expNext;
    int hp;
    int hpMax;
    int stamina;
    int staminaMax;
    int damageMin;
    int damageMax;
    int defence;
    int accuracy;
    int statPoints;
    int skillPoints;
    int strength;
    int vitality;
    int dexterity;
    int intelligence;
    int luck;
    int armorRate;
public:
    Character();
    Character(string name, int distanceTravelled,int gold,int level,int exp,int strength,int vitality,
              int dexterity, int intelligence, int hp, int stamina, int statPoints, int skillPoints);
    ~Character();
    //Functions
    void printStats() const;
    void initialize(const string name);
    void levelUp();
    string getAsString() const;
    void updateStats();
    void addToStat(int stat, int value);
    //Accesors
    inline const string& getName() const {return this->name;}
    inline const int& getLevel() const {return this->level;}
    inline const int& getExp() const {return this->exp;}
    inline const int& getExpNext() const {return this->expNext;}
    inline const int& getHP() const {return this->hp;}
    inline const int& getHPMax() const {return this->hpMax;}
    inline const int& getStamina() const {return this->stamina;}
    inline const int& getDamageMin() const {return this->damageMin;}
    inline const int& getDamageMax() const {return this->damageMax;}
    inline const int& getDefence() const {return this->defence;}
    inline const int& getAccuracy() const {return this->accuracy;}
    inline const int& getDistanceTravelled() const {return this->distanceTravelled;}
    inline const int& getStatPoints() const {return this->statPoints;};
    inline const bool isAlive() {return this->hp > 0;};
    inline const void resetHP() {this->hp = this->hpMax;};
    const int getDamage()const;
    void takeDamage (const int damage);
    inline const int& getArmorRate(){return this->armorRate;};
    //Modifiers
    inline void setDistanceTravelled(const int& distance){ this->distanceTravelled = distance;}
    inline void travel(){ this->distanceTravelled++;}
    inline void gainExp(const int& exp){this->exp += exp;};
    friend void debugPrintCharacter(Character& character);
};


#endif //CONSOLE_RPG_CHARACTER_H
