#include "Gauntlet.h"

Gauntlet::~Gauntlet() {

}

Gauntlet::Gauntlet(int defence, string name, int level, int buyValue, int sellValue, int rarity, int armorType)
        : Armor(defence, name, level, buyValue, sellValue, rarity)
{
    this->armorType = armorType;
}

Gauntlet* Gauntlet::clone() const {
    return new Gauntlet(*this);
}
void Gauntlet::addAndPrintArmorTypes(Helmet* helmet, Torso *torso, Legs *legs) const{
    int sum = this->armorType + helmet->armorType + torso->armorType + legs->armorType;
    cout<<"Sum: "<<sum<<"\n";
}