//
// Created by R4V3N on 14.12.2022.
//

#ifndef CONSOLE_RPG_PUZZLE_H
#define CONSOLE_RPG_PUZZLE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Puzzle {
private:
    string question;
    vector<string> answers;
    int correntAnswer;
public:
    Puzzle(string fileName);
    ~Puzzle();
    string getAsString();
    inline const int& getCorrectAns() const {return this->correntAnswer;};
    friend void debugPrintPuzzle(Puzzle& puzzle);
};


#endif //CONSOLE_RPG_PUZZLE_H
