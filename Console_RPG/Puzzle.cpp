//
// Created by R4V3N on 14.12.2022.
//

#include "Puzzle.h"
Puzzle::Puzzle(string fileName) {
    this->correntAnswer = 0;
    ifstream inFile(fileName);
    int nrOfAns = 0;
    string answer = "";
    int correctAns = 0;
    if(inFile.is_open())
    {
        getline(inFile, this->question);
        inFile >> nrOfAns;
        inFile.ignore();
        for(size_t i = 0; i< nrOfAns; i++){
            getline(inFile, answer);
            this->answers.push_back(answer);
        }
        inFile >> correctAns;
        this->correntAnswer = correctAns;
        inFile.ignore();
    }
    else{
        throw("Could not open puzzle!");
    }
    inFile.close();
}
Puzzle::~Puzzle() {

}
string Puzzle::getAsString() {
    string answers = "";
    for(size_t i = 0; i<this->answers.size(); i++)
    {
        answers+= to_string(i) + ": " + this->answers[i] + "\n";
    }
    /*return this->question + '\n' + '\n' +
    answers + "\n" + to_string(this->correntAnswer) + "\n";*/
    return this->question + '\n' + '\n' +
           answers;

}
