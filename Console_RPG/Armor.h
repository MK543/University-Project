
#ifndef CONSOLE_RPG_ARMOR_H
#define CONSOLE_RPG_ARMOR_H
#include "Item.h"

class Armor:
        public Item{
private:
    int defence;
public:
    Armor(int defence = 0, string name ="NONE", int level = 0, int buyValue = 0, int sellValue = 0, int rarity = 0);
    ~Armor();
    string toString();
    virtual Armor* clone() const = 0;
    inline int getDefence(){return this->defence;};
};


#endif //CONSOLE_RPG_ARMOR_H
