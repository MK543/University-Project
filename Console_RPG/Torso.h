#ifndef CONSOLE_RPG_TORSO_H
#define CONSOLE_RPG_TORSO_H
#include "Armor.h"
#include "Helmet.h"
#include "Gauntlet.h"
#include "Legs.h"
class Gauntlet;
class Helmet;
class Legs;

class Torso: public Armor{
private:
    int armorType;
public:
    Torso(int defence = 0, string name ="NONE", int level = 0,
           int buyValue = 0, int sellValue = 0, int rarity = 0, int armorType = 1);
    virtual ~Torso();
    Torso* clone() const;
    inline const int& getArmorType(){return this->armorType;};
    friend void debugPrintArmor(Helmet* helmet, Gauntlet* gauntlet, Torso* torso, Legs* legs);
    friend class Gauntlet;
    friend class Helmet;
    friend class Legs;
    void addAndPrintArmorTypes(Gauntlet* gauntlet, Helmet* helmet, Legs* legs) const;
};


#endif //CONSOLE_RPG_TORSO_H
