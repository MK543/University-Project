#include "Character.h"
#include "Inventory.h"
#include <math.h>
Character::Character() {
    this->name ="";
    this->level = 1;
    this->exp = 0;
    this->expNext = 0;
    this->hp = 0;
    this->hpMax = 0;
    this->stamina = 0;
    this->staminaMax = 0;
    this->damageMin = 0;
    this->damageMax = 0;
    this->defence = 0;
    this->vitality = 0;
    this->dexterity = 0;
    this->strength = 0;
    this->intelligence = 0;
    this->accuracy = 0;
    this->luck = 0;
    this->statPoints = 0;
    this->skillPoints = 0;
    this->gold = 0;
    this->distanceTravelled = 0;
    this->armorHead = nullptr;
    this->armorChest = nullptr;
    this->armorArms = nullptr;
    this->armorLegs = nullptr;
    this->armorRate = 0;
    this->weapon = nullptr;
}

Character::Character(string name, int distanceTravelled,int gold,int level,int exp,int strength,int vitality,
                     int dexterity, int intelligence, int hp, int stamina, int statPoints, int skillPoints) {
    this->name =name;
    this->level = level;
    this->exp = exp;
    this->expNext = 0;
    this->hp = hp;
    this->hpMax = 0;
    this->stamina = stamina;
    this->staminaMax = 0;
    this->damageMin = 0;
    this->damageMax = 0;
    this->defence = 0;
    this->vitality = vitality;
    this->dexterity = dexterity;
    this->strength = strength;
    this->intelligence = intelligence;
    this->accuracy = 0;
    this->luck = 0;
    this->statPoints = statPoints;
    this->skillPoints = skillPoints;
    this->gold = gold;
    this->distanceTravelled = distanceTravelled;
    this->updateStats();
}
Character::~Character() {

}
//(int level, string name, int exp, int expNext, int hp, int hpMax, int stamina, int damageMin, int DamageMax, int defence)
void Character::initialize(const string name) {
    this->name = name;
    this->level = 1;
    this->exp = 0;
    this->expNext = static_cast<int>(50/3)*(pow(level,3)-6*pow(level,2)+(17*level)-11);
    this->vitality = 5;
    this->dexterity = 5;
    this->strength = 5;
    this->intelligence = 5;
    this->hpMax = (this->vitality*5) + (this->strength/2);
    this->hp = this->hpMax;
    this->staminaMax = 10;
    this->stamina = this->staminaMax;
    this->damageMin = this->strength;
    this->damageMax = this-> strength +2;
    this->defence = this->dexterity + this->intelligence/2;
    this->statPoints= 0;
    this->skillPoints= 0;
    this->accuracy = this->dexterity/2 + intelligence;
    this->gold = 100;
    this->statPoints = 0;
    this->skillPoints = 0;
    this->luck = this->intelligence;
    this->distanceTravelled = 0;
    this->armorHead = new Helmet(10, "Leather Helmet", 1, 100, 50, 0);
    this->armorChest = new Torso(25, "Leather Chest", 1, 100, 50, 0);
    this->armorArms = new Gauntlet(5, "Leather Gauntlets", 1, 100, 50, 0);
    this->armorLegs = new Legs(10, "Leather Shoes", 1, 100, 50, 0);
    this->armorRate = this->armorHead->getDefence() + this->armorChest->getDefence()
            + this->armorArms->getDefence() + this->armorLegs->getDefence();
    this->weapon = new Weapon(2, 4, "Iron Sword", 1, 100, 50, 0);
}
void Character::printStats() const {
    cout << "Character Sheet =" << std::endl;
    cout << "Name: " << this->name<< std::endl;
    cout << "Level: " << this->level<< std::endl;
    cout << "Exp: " << this->exp<< std::endl;
    cout << "Exp to next lv: = " << this->expNext<< std::endl;
    cout << "Strength: " << this->strength<< std::endl;
    cout << "Vitality: " << this->vitality<< std::endl;
    cout << "Dexterity: " << this->dexterity<< std::endl;
    cout << "Intelligence: " << this->intelligence<< std::endl;
    cout << "HP: " << this->hp<<"/"<<this->hpMax<< std::endl;
    cout << "Stamina: " << this->stamina<<"/"<<this->staminaMax<< std::endl;
    cout << "Damage: " << this->damageMin<<"-"<<this->damageMax<< std::endl;
    cout << "Defence: " << this->defence<<std::endl;
    cout << "Luck: " << this->luck<<std::endl;
    cout << "Accuracy: " << this->accuracy<<std::endl;
    cout << endl;
    cout << "Gold: " << this->gold<<std::endl;
    cout << "Distance Travelled: " << this->distanceTravelled<<std::endl;
    cout << endl;

    cout<<"\nArmor:\n";
    cout<<"Helmet: \n";
    cout<< "Name: "<<this->armorHead->getName()<<"\n";
    cout<<"Defense: "<<this->armorHead->getDefence()<<"\n";
    cout<<"Buy Value: "<<this->armorHead->getBuyValue()<<"\n";
    cout<<"Sell Value: "<<this->armorHead->getSellValue()<<"\n\n";

    cout<<"Gauntlets: \n";
    cout<< "Name: "<<this->armorArms->getName()<<"\n";
    cout<<"Defense: "<<this->armorArms->getDefence()<<"\n";
    cout<<"Buy Value: "<<this->armorArms->getBuyValue()<<"\n";
    cout<<"Sell Value: "<<this->armorArms->getSellValue()<<"\n\n";

    cout<<"Torso: \n";
    cout<< "Name: "<<this->armorChest->getName()<<"\n";
    cout<<"Defense: "<<this->armorChest->getDefence()<<"\n";
    cout<<"Buy Value: "<<this->armorChest->getBuyValue()<<"\n";
    cout<<"Sell Value: "<<this->armorChest->getSellValue()<<"\n\n";

    cout<<"Legs: \n";
    cout<< "Name: "<<this->armorLegs->getName()<<"\n";
    cout<<"Defense: "<<this->armorLegs->getDefence()<<"\n";
    cout<<"Buy Value: "<<this->armorLegs->getBuyValue()<<"\n";
    cout<<"Sell Value: "<<this->armorLegs->getSellValue()<<"\n\n";

    cout<<"Weapon: \n";
    cout<< "Name: "<<this->weapon->getName()<<"\n";
    cout<<"Damage: "<<this->weapon->getDamageMin()<<"-"<<this->weapon->getDamageMax()<<"\n";
    cout<<"Buy Value: "<<this->weapon->getBuyValue()<<"\n";
    cout<<"Sell Value: "<<this->weapon->getSellValue()<<"\n\n";

}
void Character::levelUp() {
    if(this->exp >= this->expNext){
        std::cout<<"Level Up!\n";
        this->level++;
        this->exp -= expNext;
        this->expNext = static_cast<int>(50/3)*(pow(level,3)-6*pow(level,2)+(17*level)-11);
        this->statPoints++;
        this->skillPoints++;
        this->updateStats();
        std::cout<<"You are now "<<this->level<<" !\n";
    }
    else
    {
        std::cout<<"Not enough exp to level up!\n";
    }
}
void Character::addToStat(int stat, int value) {
    if(this->statPoints < value){
        cout<<"Not enough statpoints!\n";
    }
    else{
        switch(stat){
            case 0:
                this->strength+= value;
                cout<<"Strength increased!\n";
                break;
            case 1:
                this->vitality+= value;
                cout<<"Vitality increased!\n";
                break;
            case 2:
                this->dexterity+= value;
                cout<<"Dexterity increased!\n";
                break;
            case 3:
                this->intelligence+= value;
                cout<<"Intelligence increased!\n";
                break;
            default:
                cout<<"No such stat!\n";
                break;
        }
        this->statPoints -= value;
    }
}
string Character::getAsString() const {
    return this->name + " "
        + to_string(this->distanceTravelled) + " "
        + to_string(this->gold) + " "
        + to_string(this->level) + " "
        + to_string(this->exp) + " "
        + to_string(this->strength) + " "
        + to_string(this->vitality) + " "
        + to_string(this->dexterity) + " "
        + to_string(this->intelligence) + " "
        + to_string(this->hp) + " "
        + to_string(this->stamina) + " "
        + to_string(this->statPoints) + " "
        + to_string(this->skillPoints) + " ";

    /*return this->name + "\n"
           + to_string(this->distanceTravelled) + "\n"
           + to_string(this->gold) + "\n"
           + to_string(this->level) + "\n"
           + to_string(this->exp) + "\n"
           + to_string(this->strength) + "\n"
           + to_string(this->vitality) + "\n"
           + to_string(this->dexterity) + "\n"
           + to_string(this->intelligence) + "\n"
           + to_string(this->hp) + "\n"
           + to_string(this->stamina) + "\n"
           + to_string(this->statPoints) + "\n"
           + to_string(this->skillPoints) + "\n";*/
}

void Character::updateStats() {
    this->expNext = static_cast<int>(50/3)*(pow(level,3)-6*pow(level,2)+(17*level)-11);
    this->hpMax = (this->vitality*2) + (this->strength/2);
    this->staminaMax = 10;
    this->damageMin = this->strength;
    this->damageMax = this-> strength +2;
    this->defence = this->dexterity + this->intelligence/2;
    this->accuracy = this->dexterity/2;
    this->luck = this->intelligence;
}

void Character::takeDamage(const int damage) {
    this->hp -= damage;
    if(this->hp <= 0){
        this->hp = 0;
    }
}

const int Character::getDamage() const {
    return (rand()%(this->damageMax-damageMin+1) + damageMin +
    rand()%(this->weapon->getDamageMax()-this->weapon->getDamageMin()+1) + damageMin);
}
