#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;

unordered_map<string, unordered_multimap<string, string> > automata;
string initialState;
unordered_set<string> finalStates;

//Reading line string to vector, type 0 is states, type 1 is final states
void readToMap(string line, int type) {
    int i = 0;
    string current;
    while(line[i]) {
        if(line[i] == ',' || line[i+1] == NULL) {
            if(type == 0) { // If filling out states
                unordered_multimap<string, string> empty;
                automata.emplace(current, empty);
            } else if (type == 1) { // If filling out final states
                finalStates.emplace(current);
            }
            current = "";
            i++;
        }
        else {
            current = current + line[i];
            i++;
        }
    }
}
// Puts state transitions into matrix
void fillDataMatrix() {
    // For every state in the machine
    int numStates = int(states.size()) ;
    int lines = 2;
    for(int i = 0; i < numStates; i++) {
        string state;
        state = states[i];
        unordered_multimap<string, string> empty;
        automata.emplace(state, empty);
    }
    // For every transition function
    for(int i = 0; i < lines; i++) {
        string initialState, symbol, nextState;
        unordered_multimap<string, string> current = automata[initialState];
        current.emplace(symbol, nextState);
        automata[initialState] = current;
    }
}

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
    readToMap(firstLine, 0);
    readToMap(fourthLine, 1);
    if(myReadFile.is_open()){
        while(!myRead)
    }

    if(traverse("ab", 0, "q0")) {
        cout << "true";
    }
    return 1;
}