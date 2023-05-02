#include "Legs.h"

Legs::~Legs() {

}

Legs::Legs(int defence, string name, int level, int buyValue, int sellValue, int rarity, int armorType)
        : Armor(defence, name, level, buyValue, sellValue, rarity)
{
    this->armorType = armorType;
}

Legs* Legs::clone() const {
    return new Legs(*this);
}
void Legs::addAndPrintArmorTypes(Gauntlet *gauntlet, Torso *torso, Helmet* helmet) const{
    int sum = this->armorType + gauntlet->armorType + torso->armorType + helmet->armorType;
    cout<<"Sum: "<<sum<<"\n";
}