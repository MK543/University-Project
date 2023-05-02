//
// Created by R4V3N on 14.12.2022.
//

#include "Events.h"
Events::Events() {
    this->nrOfEvents = 2;
}
Events::~Events() {

}
void Events::generateEvent(Character &character, dArray<Enemy>& enemies) {
    srand(time(NULL));
    int i = rand()% this->nrOfEvents;

    switch(i)
    {
        case 0:
            //Enemy encounter
            enemyEncounter(character, enemies);
            break;
        case 1:
            //Puzzle
            puzzleEncounter(character);
            break;
        case 2:
            break;
        default:
            break;
    }
}

void Events::enemyEncounter(Character &character, dArray<Enemy>& enemies) {

    std::cout<< "Enemy encounter\n";
    bool playerTurn = false;
    int choice  = 0;

    //Decide who starts
    int coinToss = rand()% 2 + 1;
    if(coinToss == 1){
        playerTurn = true;
    }

    //End conditions
    bool escape = false;
    bool playerDefeated = false;
    bool enemiesDefeated = false;

    //Battle stuff
    int attackRoll= 0;
    int defendRoll = 0;
    int damage = 0;
    int gainExp = 0;
    int playerTotal = 0;
    int enemyTotal = 0;
    int combatTotal = 0;
    int combatRollPlayer = 0;
    int combatRollEnemy = 0;
    int enemyTotalDMG = 0;
    int enemySingleDMG = 0;
    int gainGold = 0;
    //Enemies
    int nrOfEnemies = rand() % 5 + 1;
    for(size_t i = 0; i<nrOfEnemies; i++){
        enemies.push(Enemy(rand()%character.getLevel()+1));
    }

    while (!escape && !playerDefeated && !enemiesDefeated){
        if(playerTurn && !playerDefeated){
            //Menu
            cout << "\nBATTLE MENU\n";
            cout << "0: Escape\n";
            cout << "1: Attack\n";
            cout << "2: Defend\n";
            cout << "3: Use Item\n";

            cout << "Choice: \n";
            cin >> choice;
            while(cin.fail() || choice >= 3 || choice < 0){
                cout<<"Faulty input!"<<"\n";
                cin.clear();
                system("CLS");
                cin.ignore(100,'\n');
                cout << "\nBATTLE MENU\n";
                cout << "0: Escape\n";
                cout << "1: Attack\n";
                cout << "2: Defend\n";
                cout << "3: Use Item\n";

                cout << "Choice: \n";
                cin >> choice;
            }
            cin.clear();
            cin.ignore(100,'\n');
            switch(choice)
            {
                //Moves
                case 0://ESCAPE
                    escape =  true;
                    cout << "You have escaped successfully!\n";
                    break;

                case 1://ATTACK
                    //Select enemy
                    cout << "\nSelect Enemy: \n";
                    for(size_t i=0; i< enemies.size(); i++){
                        cout << i << ": Name: ??? Level: "<<enemies[i].getLv()<<
                             " Hp: "<<enemies[i].getHp() << "/" << enemies[i].getHpMax()<<"\n";
                    }
                    cout<<"\n";
                    cout << "Choice: \n";
                    cin >> choice;
                    cout<<"\n";
                    while(cin.fail() || choice >= enemies.size() || choice < 0){
                        cout<<"Faulty input!"<<"\n";
                        cin.clear();
                        cin.ignore(100,'\n');
                        cout << "Select Enemy: \n";
                        for(size_t i=0; i< enemies.size(); i++){
                            cout << i << ": Name: ??? Level: "<<enemies[i].getLv()<<
                            " Hp: "<<enemies[i].getHp() << "/" << enemies[i].getHpMax()<<"\n";
                        }
                        cout<<"\n";
                        cout << "SelectEnemy: \n";
                        cin >> choice;
                    }
                    cin.clear();
                    cin.ignore(100,'\n');
                    //Hit
                    combatTotal = enemies[choice].getDefense() + character.getAccuracy();
                    enemyTotal = enemies[choice].getDefense() / (double)combatTotal * 100;
                    playerTotal = character.getAccuracy() / (double)combatTotal * 100;
                    combatRollPlayer = rand()%playerTotal + 1;
                    combatRollEnemy = rand()%enemyTotal + 1;
                    /*cout<< combatTotal<<"\n";
                    cout<< enemyTotal<<"\n";
                    cout<< playerTotal<<"\n";
                    cout<< combatRollPlayer<<"\n";
                    cout<< combatRollEnemy<<"\n";*/

                    cout<< "Player roll: "<<combatRollPlayer<<"\n";
                    cout<< "Enemy roll: "<<combatRollEnemy<<"\n\n";
                    if(combatRollPlayer > combatRollEnemy){
                        damage = character.getDamage();
                        enemies[choice].takeDamage(damage);
                        cout<<"You have hit enemy and dealt "<<damage<< " damage!\n";
                        if(!enemies[choice].isAlive()){
                            cout<<"You have killed enemy number "<<choice<< "!\n";
                            gainExp = enemies[choice].getExp();
                            character.gainExp(gainExp);
                            cout<<"You have gained "<<gainExp<< " Exp!\n";
                            gainGold = enemies[choice].getGold();
                            cout<<"You have gained "<<gainGold<< " Gold!\n";
                            enemies.remove(choice);
                        }
                    }
                    //Miss
                    else{
                        cout<<"You have missed!\n";
                    }

                    break;

                case 2://DEFEND
                    break;

                case 3://USE ITEM
                    break;

                default:
                    break;
            }

            //End turn
            playerTurn = false;
        }
        else if(!playerTurn && !escape && !enemiesDefeated){
            cout<<"\nEnemy attack!\n";
            enemyTotalDMG = 0;
            for(size_t i = 0; i<enemies.size(); i++){
                enemySingleDMG = enemies[i].getDamage() - (character.getDefence()/4 +  + character.getArmorRate()/25);
                enemyTotalDMG +=  enemySingleDMG;
                cout<< "Enemy: "<<i<<" dealt "<< enemySingleDMG<<" DMG!\n";
            }
            cout<<"Total DMG taken: "<<enemyTotalDMG<<"\n";
            character.takeDamage(enemyTotalDMG);
            cout << "HP: " << character.getHP() << " / " << character.getHPMax() << "\n";
            //End turn
            playerTurn = true;

        }


        //Conditions
        if(!character.isAlive()){
            playerDefeated = true;
            cout << "You have lost fight and retreated!\n";
            character.resetHP();
        }
        else if(enemies.size()<= 0){
            enemiesDefeated = true;
        }
    }
}
void Events::puzzleEncounter(Character &character) {
    bool completed = false;
    int userAns = 0;
    int chances = 3;
    int gainExp = 0;
    Puzzle puzzle("Puzzles/1.txt");
    while(!completed && chances > 0){
        gainExp = chances * character.getLevel()*(rand()% 10 + 1);
        std::cout<<"You have "<<chances <<" left\n";
        chances--;
        std::cout<<puzzle.getAsString();
        std::cout<<"\n Your answer: ";
        std::cin>>userAns;

        while(cin.fail()){
            cout<<"Faulty input!"<<"\n";
            cin.clear();
            cin.ignore(100,'\n');
            cout<<endl<<"Your answer: ";
            cin >> userAns;
        }
        cin.ignore(100,'\n');
        cout << "\n";

        std::cout<<"\n";
        if(puzzle.getCorrectAns() == userAns) {
            completed = true;
        }
        else{
            std::cout<<"Wrong!\n";
        }
    }
    if(completed){
        std::cout<<"You have guessed correctly!\n\n";
        character.gainExp(gainExp);
        std::cout<<"You gained: "<<gainExp<<" Exp!\n";
    }
    else
    {
        std::cout<<"You have failed!\n\n";
    }
}