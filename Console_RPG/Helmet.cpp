#include "Helmet.h"
Helmet::~Helmet() {

}

Helmet::Helmet(int defence, string name, int level, int buyValue, int sellValue, int rarity, int armorType)
    : Armor(defence, name, level, buyValue, sellValue, rarity)
{
    this->armorType = armorType;
}

Helmet* Helmet::clone() const {
    return new Helmet(*this);
}

void Helmet::addAndPrintArmorTypes(Gauntlet *gauntlet, Torso *torso, Legs *legs) const{
    int sum = this->armorType + gauntlet->armorType + torso->armorType + legs->armorType;
    cout<<"Sum: "<<sum<<"\n";
}