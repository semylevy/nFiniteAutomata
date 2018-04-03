#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

unordered_map<string, unordered_multimap<string, string> > automata;
vector<string> states; vector<string> alphabet; string startState; vector<string> finalStates;

//Reading line string to vector
vector<string> readToVector(string line) {
    vector<string> myVec;
    int i = 0;
    string thing;
    while(line[i]) {
        if(line[i] == ',') {
            unordered_multimap<string, string> empty;
            automata.emplace(thing, empty);
            //myVec.push_back(thing);
            thing = "";
            i++;
        }
        else {
            thing = thing + line[i];
            if(line[i+1] == NULL) {
                unordered_multimap<string, string> empty;
                automata.emplace(thing, empty);
                //myVec.push_back(thing);
                thing = "";
            }
            i++;
        }
    }
    return myVec;
}

void readTransition(string line){
    int i = 0;
    string initialState, symbol, nextState;
    while(line[i] != ','){
        initialState = initialState + line[i];
        i++;
    }
    i++;
    while(line[i] != ':'){
        symbol = symbol + line[i];
        i++;
    }
    i++;
    while(line[i]){
        nextState = nextState + line[i];
        i++;
    }
    unordered_multimap<string, string> current = automata[initialState];
    current.emplace(symbol, nextState);
    automata[initialState] = current;

}
// Puts state transitions into matrix


bool isFinal(string state) {
    return true;
}

// Checks possible transistions and recursively calls next state
bool traverse(string word, int count, string state) {
    if(count >= word.size()) {
        return isFinal(state);
    }
    string symbol = word.substr(count, 1);

    // Look for for epsilon
    auto range_e = automata[state].equal_range("&");
    for (auto it = range_e.first; it != range_e.second; ++it) {
        string nextState = it->second;
        traverse(word, count, nextState);
    }

    // Every possible transition for given state
    auto range = automata[state].equal_range(symbol);
    for (auto it = range.first; it != range.second; ++it) {
        string nextState = it->second;
        traverse(word, count+1, nextState);
    }
}

int main() {
    //Reading Text File
    string firstLine,secondLine,thirdLine,fourthLine,nextLine;
    ifstream myReadFile;
    string line;
    myReadFile.open("text.txt");
    if(myReadFile.is_open()){
        myReadFile >> firstLine;
        myReadFile >> secondLine;
        myReadFile >> thirdLine;
        myReadFile >> fourthLine;
    }
    states = readToVector(firstLine);
    alphabet = readToVector(secondLine);
    finalStates = readToVector(fourthLine);
    if(myReadFile.is_open()){
        while(getline(myReadFile,nextLine)){
            
        }
    }

    if(traverse("ab", 0, "q0")) {
        cout << "true";
    }
    return 1;
}