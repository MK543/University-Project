
#ifndef CONSOLE_RPG_HELMET_H
#define CONSOLE_RPG_HELMET_H
#include "Armor.h"
#include "Gauntlet.h"
#include "Torso.h"
#include "Legs.h"
class Gauntlet;
class Torso;
class Legs;

class Helmet: public Armor{
private:
    int armorType;
public:
    Helmet(int defence = 0, string name ="NONE", int level = 0,
           int buyValue = 0, int sellValue = 0, int rarity = 0, int armorType = 0);
    virtual ~Helmet();
    Helmet* clone() const;
    inline const int& getArmorType(){return this->armorType;};
    friend void debugPrintArmor(Helmet* helmet, Gauntlet* gauntlet, Torso* torso, Legs* legs);
    friend class Gauntlet;
    friend class Torso;
    friend class Legs;
    void addAndPrintArmorTypes(Gauntlet* gauntlet, Torso* torso, Legs* legs) const;
};


#endif //CONSOLE_RPG_HELMET_H
