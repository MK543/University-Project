#include "Armor.h"

Armor::Armor(int defence, std::string name, int level, int buyValue, int sellValue, int rarity)
        : Item(name, level, buyValue, sellValue, rarity)
{
    this->defence = defence;
}

Armor::~Armor() {

}

string Armor::toString() {
    string str = to_string(this->defence);
    return str;
}
