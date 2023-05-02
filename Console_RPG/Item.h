#ifndef CONSOLE_RPG_ITEM_H
#define CONSOLE_RPG_ITEM_H
#include<string>
#include<iomanip>
#include<iostream>

using namespace std;
class Item {
private:
    int level;
    int rarity;
    string name;
    int buyValue;
    int sellValue;
public:
    Item(string name ="NONE", int level = 0, int buyValue = 0, int sellValue = 0, int rarity = 0);
    ~Item();
    inline string debugPrint() const
    {
        return this->name;
    }
    virtual Item* clone() const = 0;
    //Accesors
    inline const string& getName(){return this->name;}
    inline const int& getLevel(){return this->level;}
    inline const int& getRarity(){return this->rarity;}
    inline const int& getBuyValue(){return this->buyValue;}
    inline const int& getSellValue(){return this->sellValue;}
    //Modifiers
};


#endif
