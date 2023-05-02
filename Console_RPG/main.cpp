#include <iostream>
#include "Game.h"
#include <math.h>
#include "Inventory.h"
using namespace std;

void debugPrintCharacter(Character& character){
    cout<<"Gold: "<<character.gold<<"\n";
    cout<<"Distance Travelled: "<<character.distanceTravelled<<"\n";
    cout<<"Level: "<<character.level<<"\n";
    cout<<"Exp: "<<character.exp<<"\n";
    cout<<"ExpNext:"<<character.expNext<<"\n";
    cout<<"Stamina:"<<character.hp<<"\n";
    cout<<"StaminaMax: "<<character.hpMax<<"\n";
    cout<<"DamageMin: "<<character.damageMin<<"\n";
    cout<<"DamageMax: "<<character.damageMax<<"\n";
    cout<<"Defence: "<<character.defence<<"\n";
    cout<<"Accuracy: "<<character.accuracy<<"\n";
    cout<<"Stat Points: "<<character.statPoints<<"\n";
    cout<<"Strength: "<<character.strength<<"\n";
    cout<<"Vitality: "<<character.vitality<<"\n";
    cout<<"Dexterity: "<<character.dexterity<<"\n";
    cout<<"Intelligence: "<<character.intelligence<<"\n";
    cout<<"Luck: "<<character.luck<<"\n";
    cout<<"Armor Rate: "<<character.armorRate<<"\n";
}
void debugPrintPuzzle(Puzzle& puzzle){
    cout<<"Gold: "<<puzzle.question<<"\n";
    for(auto & element: puzzle.question){
        cout<<"Question: "<<element<<"\n";
    }
    cout<<"Correct answer: "<<puzzle.correntAnswer<<"\n";
}
void debugPrintWeapon(Weapon* weapon){
    cout<<"Damage min: "<<weapon->damageMin<<"\n";
    cout<<"Damage max: "<<weapon->damageMax<<"\n";
    cout<<"Name: "<<weapon->getName()<<"\n";
    cout<<"Name: "<<weapon->getLevel()<<"\n";
    cout<<"Name: "<<weapon->getRarity()<<"\n";
    cout<<"Name: "<<weapon->getBuyValue()<<"\n";
    cout<<"Name: "<<weapon->getSellValue()<<"\n";
}
void debugPrintArmor(Helmet* helmet, Gauntlet* gauntlet, Torso* torso, Legs* legs){
    int choice = 0;
    std::cout<<"0: Helmet\n";
    std::cout<<"1: Gauntlets\n";
    std::cout<<"2: Torso\n";
    std::cout<<"3: Legs\n";
    std::cout<<"\n Your choice: \n";
    std::cin>>choice;

    while(cin.fail()){
        cout<<"Faulty input!"<<"\n";
        cin.clear();
        cin.ignore(100,'\n');
        cout<<endl<<"Your answer: \n";
        cin >> choice;
    }
    cin.ignore(100,'\n');
    cout << "\n";
    switch(choice){
        case 0:
            cout<<"Defence : "<<helmet->getDefence()<<"\n";
            cout<<"Name : "<<helmet->getName()<<"\n";
            cout<<"Level : "<<helmet->getLevel()<<"\n";
            cout<<"Buy Value : "<<helmet->getBuyValue()<<"\n";
            cout<<"Sell Value : "<<helmet->getSellValue()<<"\n";
            cout<<"Rarity : "<<helmet->getRarity()<<"\n";
            cout<<"Armor Type : "<<helmet->armorType<<"\n";
            break;
        case 1:
            cout<<"Defence : "<<gauntlet->getDefence()<<"\n";
            cout<<"Name : "<<gauntlet->getName()<<"\n";
            cout<<"Level : "<<gauntlet->getLevel()<<"\n";
            cout<<"Buy Value : "<<gauntlet->getBuyValue()<<"\n";
            cout<<"Sell Value : "<<gauntlet->getSellValue()<<"\n";
            cout<<"Rarity : "<<gauntlet->getRarity()<<"\n";
            cout<<"Armor Type : "<<gauntlet->armorType<<"\n";
            break;
        case 2:
            cout<<"Defence : "<<torso->getDefence()<<"\n";
            cout<<"Name : "<<torso->getName()<<"\n";
            cout<<"Level : "<<torso->getLevel()<<"\n";
            cout<<"Buy Value : "<<torso->getBuyValue()<<"\n";
            cout<<"Sell Value : "<<torso->getSellValue()<<"\n";
            cout<<"Rarity : "<<torso->getRarity()<<"\n";
            cout<<"Armor Type : "<<torso->armorType<<"\n";
            break;
        case 3:
            cout<<"Defence : "<<legs->getDefence()<<"\n";
            cout<<"Name : "<<legs->getName()<<"\n";
            cout<<"Level : "<<legs->getLevel()<<"\n";
            cout<<"Buy Value : "<<legs->getBuyValue()<<"\n";
            cout<<"Sell Value : "<<legs->getSellValue()<<"\n";
            cout<<"Rarity : "<<legs->getRarity()<<"\n";
            cout<<"Armor Type : "<<legs->armorType<<"\n";
            break;
        default:
            break;
    }
}
int main() {
    srand(time(NULL));
//    int level = 2;
//    int i = static_cast<int>(50/3)*(pow(level,3)-6*pow(level,2)+(17*level)-11);
//    cout<< i << endl;
//    Inventory inv;
//    for(int i = 0; i<10; i++){
//        inv.addItem(Item());
//    }
//    inv.debugPrint();
    Game game;
    game.initGame();
    while(game.getPlaying()){
        game.mainMenu();
    }
    return 0;
}
