#ifndef CONSOLE_RPG_INVENTORY_H
#define CONSOLE_RPG_INVENTORY_H
#include "Armor.h"
#include "Weapon.h"
class Inventory {
private:
    int capacity;
    int nrOfItems;
    Item **itemArr;
    void expand();
    void initialize(const int from = 0);
public:
    Inventory();
    ~Inventory();
    Inventory(const Inventory &obj);
    void addItem(const Item &item);
    void removeItem(int index);
    void operator=(const Inventory &obj);
    inline int size()const {return  this->nrOfItems;};
    Item& operator[](const int index);
    inline void debugPrint() const{
        for(size_t i = 0; i<nrOfItems; i++){
            cout <<this->itemArr[i]->debugPrint() <<endl;
        }
    }
};


#endif //CONSOLE_RPG_INVENTORY_H
