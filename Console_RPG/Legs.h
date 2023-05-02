
#ifndef CONSOLE_RPG_LEGS_H
#define CONSOLE_RPG_LEGS_H
#include "Armor.h"
#include "Helmet.h"
#include "Gauntlet.h"
#include "Torso.h"
class Gauntlet;
class Helmet;
class Torso;

class Legs: public Armor {
private:
    int armorType;
public:
    Legs(int defence = 0, string name ="NONE", int level = 0,
           int buyValue = 0, int sellValue = 0, int rarity = 0, int armorType = 3);
    virtual ~Legs();
    Legs* clone() const;
    inline const int& getArmorType(){return this->armorType;};
    friend void debugPrintArmor(Helmet* helmet, Gauntlet* gauntlet, Torso* torso, Legs* legs);
    friend class Gauntlet;
    friend class Helmet;
    friend class Torso;
    void addAndPrintArmorTypes(Gauntlet* gauntlet, Torso* torso, Helmet* helmet) const;
};


#endif //CONSOLE_RPG_LEGS_H
