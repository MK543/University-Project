//
// Created by R4V3N on 24.11.2022.
//

#ifndef CONSOLE_RPG_WEAPON_H
#define CONSOLE_RPG_WEAPON_H
#include "Item.h"

class Weapon :
        public Item{
private:
    int damageMin;
    int damageMax;
public:
    Weapon(int damageMin = 0, int damageMax = 0, string name ="NONE", int level = 0, int buyValue = 0, int sellValue = 0, int rarity = 0);
    ~Weapon();
    string toString();
    inline string debugPrint() const;
    virtual Weapon* clone() const;
    inline int getDamageMin(){return this->damageMin;};
    inline int getDamageMax(){return this->damageMax;};
    friend void debugPrintWeapon(Weapon* weapon);
};


#endif //CONSOLE_RPG_WEAPON_H
