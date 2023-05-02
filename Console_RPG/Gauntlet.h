//
// Created by R4V3N on 28.12.2022.
//

#ifndef CONSOLE_RPG_GAUNTLET_H
#define CONSOLE_RPG_GAUNTLET_H
#include "Armor.h"
#include "Helmet.h"
#include "Torso.h"
#include "Legs.h"
class Helmet;
class Torso;
class Legs;

class Gauntlet: public Armor {
private:
    int armorType;
public:
    Gauntlet(int defence = 0, string name ="NONE", int level = 0,
           int buyValue = 0, int sellValue = 0, int rarity = 0, int armorType = 2);
    virtual ~Gauntlet();
    Gauntlet* clone() const;
    inline const int& getArmorType(){return this->armorType;};
    friend void debugPrintArmor(Helmet* helmet, Gauntlet* gauntlet, Torso* torso, Legs* legs);
    friend class Helmet;
    friend class Torso;
    friend class Legs;
    void addAndPrintArmorTypes(Helmet* helmet, Torso* torso, Legs* legs) const;
};


#endif //CONSOLE_RPG_GAUNTLET_H
