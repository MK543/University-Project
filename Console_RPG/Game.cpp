#include "Game.h"

Game::Game() {
    activeCharacter = 0;
    choice = 0;
    playing = true;
    fileName = "characters.txt";
}
Game::~Game() {

}
void Game::initGame(){
    /*Enemy e(rand()% 10 +1);
    cout << e.getAsString() << endl;*/
   /* Inventory inv;
    inv.addItem(Weapon(0,0,"Wep1"));
    inv.addItem(Weapon(0,0,"Wep2"));
    inv.addItem(Weapon(0,0,"Wep3"));
    inv.addItem(Armor(0,0,"Arm1"));
    inv.addItem(Armor(0,0,"Arm2"));
    inv.addItem(Armor(0,0,"Arm3"));
    for(size_t i = 0; i <inv.size(); i++){
        std::cout<<inv[i].debugPrint()<<std::endl;
    }*/
    //Puzzle puzzle("Puzzles/1.txt");
    //cout<<puzzle.getAsString();
    createNewCharacters();
    //Puzzle p(".txt");
    //cout << p.getAsString() << '\n';
    /*dArray<int> ints(5);
    for(size_t i=0; i<20; i++){
        ints.push(rand()%10);
        cout<<ints[i]<<"\n";
    }*/
}
    //Functions
void Game::mainMenu() {

   /* cout<<"ENTER to continue...\n";
    cin.get();
    system("CLS");*/
    cout << "MAIN MENU\n"<< endl;
    cout << "Active character: "<< characters[activeCharacter].getName()<< endl;
    cout << "0: Quit" << endl;
    cout << "1: Travel" << endl;
    cout << "2: Shop" << endl;
    cout << "3: Level up" << endl;
    cout << "4: Rest" << endl;
    cout << "5: Character sheet" << endl;
    cout << "6: Create new character" << endl;
    cout << "7: Save character" << endl;
    cout << "8: Load character" << endl;
    cout << "9: Select character" <<endl;
    cout << "Your choice: ";
    cin >> choice;
    while(cin.fail()){
        cout<<"Faulty input!"<<"\n";
        cin.clear();
        cin.ignore(100,'\n');
        cout<<endl<<"Your choice: ";
        cin >> choice;
    }
    cin.ignore(100,'\n');
    cout << "\n";
    switch(choice){
        case 0: //QUIT
            playing = false;
            break;
        case 1: //TRAVEL
            Travel();
            break;
        case 2: //ITEM SHOP
            cout<<"No item shop in game for you!\n";
            break;
        case 3: //LEVEL UP
            this->levelUpCharacter();
            break;
        case 4://REST
            rest();
            break;
        case 5: //CHARACTER SHEET
            characters[activeCharacter].printStats();
            break;
        case 6: //NEW CHARACTER
            createNewCharacters();
            saveCharacters();
            break;
        case 7: //SAVE CHARACTER
            saveCharacters();
            break;
        case 8: //LOAD CHARACTER
            LoadCharacters();
            break;
        case 9: //SELECT CHARACTER
           selectCharacter();
            break;
        default:
            break;
    }
}
void Game::createNewCharacters() {
    //cin.ignore();
    string name = "";
    cout << "Enter name for character: ";
    getline(cin, name);
    bool exists = false;
    for(size_t i = 0; i<this->characters.size(); i++){
        while (name == this->characters[i].getName()){
            cout<<"Character already exists!\n";
            cout <<"Character name: ";
            getline(cin, name);
       }
    }
    characters.push_back(Character());
    activeCharacter = characters.size() - 1;
    characters[activeCharacter].initialize(name);
}
void Game::saveCharacters(){
    ofstream outFile(fileName);
    if(outFile.is_open()){
        for(size_t i = 0; i< characters.size(); i++){
            outFile << characters[i].getAsString() << "\n";
        }
    }
    outFile.close();
};
void Game::levelUpCharacter() {
    this->characters[activeCharacter].levelUp();
    if( this->characters[activeCharacter].getStatPoints() > 0){
        cout << "You have "<<this->characters[activeCharacter].getStatPoints()<<" statpoints to allocate!\n\n";
        cout << "0: Strength \n";
        cout << "1: Vitality \n";
        cout << "2: Dexterity \n";
        cout << "3: Intelligence \n";
        cout << "Stat to increase: ";
        cin >> this->choice;
        while(cin.fail() || this->choice > 3){
            cout<<"Faulty input!"<<"\n";
            cin.clear();
            cin.ignore(100,'\n');
            cout<<endl<<"Stat to increase: ";
            cin >> this->choice;
        }
        cin.ignore(100,'\n');
        cout << "\n";
        switch(this->choice){
            case 0://STRENGTH
                this->characters[activeCharacter].addToStat(0, 1);
                break;
            case 1://VITALITY
                this->characters[activeCharacter].addToStat(1, 1);
                break;
            case 2://DEXTERITY
                this->characters[activeCharacter].addToStat(2, 1);
                break;
            case 3://INTELLIGENCE
                this->characters[activeCharacter].addToStat(3, 1);
                break;
            default:
                break;
        }
    }


}
void Game::LoadCharacters(){
    ifstream inFile(fileName);
    this->characters.clear();
    string name = "";
    int distanceTravelled = 0, gold = 0, level = 0, exp = 0, strength = 0, vitality = 0, dexterity = 0,
    intelligence = 0, hp = 0, stamina = 0, statPoints = 0, skillPoints = 0;
    string line = "";
    stringstream str;
    if(inFile.is_open())
    {
        while(getline(inFile,line))
        {
            str.str(line);
            str >> name;
            str >> distanceTravelled;
            str >> gold;
            str >> level;
            str >> exp;
            str >> strength;
            str >> vitality;
            str >> dexterity;
            str >> intelligence;
            str >> hp;
            str >> stamina;
            str >> statPoints;
            str >> skillPoints;

            Character temp(name, distanceTravelled, gold, level, exp, strength, vitality, dexterity, intelligence, hp, stamina,
                           statPoints, skillPoints);
            this->characters.push_back(Character(temp));
            //cout<< this->characters[0].getAsString() <<"\n";
            //cout<< str.str() <<"\n";
            cout<<"Character " << name << " loaded!\n";
            str.clear();
        }
    }
    inFile.close();
    if(this->characters.size()<=0){
        throw "Error!";
    }
};
void Game::Travel(){
    this->characters[activeCharacter].travel();
    Events ev;
    ev.generateEvent(this->characters[activeCharacter], this->enemies);
}
void Game::selectCharacter() {
    cout << "Select character: \n";
    for(size_t i = 0; i<this->characters.size(); i++){
        cout<<"Index: "<< i << " = "<< this->characters[i].getName() << " Level: "<<this->characters[i].getLevel()<< "\n";
    }
    cout << "\n Choice: ";
    cin >> this->choice;
    while(cin.fail() || this->choice >= this->characters.size() || this->choice < 0){
        cout<<"Faulty input!"<<"\n";
        cin.clear();
        cin.ignore(100,'\n');
        cout<<endl<<"Select character: \n";
        cin >> this->choice;
    }
    cin.ignore(100,'\n');
    cout << "\n";
    this->activeCharacter = choice;
    cout<<this->characters[this->activeCharacter].getName() << "is selected! \n";
}
void Game::rest() {
    cout << "HP: " << this->characters[this->activeCharacter].getHP() << " / " << this->characters[this->activeCharacter].getHPMax() << "\n";
    characters[activeCharacter].resetHP();
    cout << "You have rested well!\n";
}
