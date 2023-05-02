#include "Weapon.h"
Weapon::Weapon(int damageMin, int damageMax, std::string name, int level, int buyValue, int sellValue, int rarity)
: Item(name, level, buyValue, sellValue, rarity)
{
    this->damageMin = damageMin;
    this->damageMax = damageMax;
}
Weapon::~Weapon() {

}

string Weapon::toString() {
    string str = to_string(this->damageMin) + " " + to_string(this->damageMax);
    return str;
}
Weapon* Weapon::clone() const {
    return new Weapon(*this);
}