#include "Torso.h"

Torso::~Torso() {

}

Torso::Torso(int defence, string name, int level, int buyValue, int sellValue, int rarity, int armorType)
    :  Armor(defence, name, level, buyValue, sellValue, rarity)
{
    this->armorType = armorType;
}

Torso* Torso::clone() const {
    return new Torso(*this);
}

void Torso::addAndPrintArmorTypes(Gauntlet *gauntlet, Helmet* helmet, Legs *legs) const{
    int sum = this->armorType + gauntlet->armorType + helmet->armorType + legs->armorType;
    cout<<"Sum: "<<sum<<"\n";
}