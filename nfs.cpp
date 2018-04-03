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
unordered_set<string> visitedEpsilonSets;

//Reading line string to vector, type 0 is states, type 1 is final states
void readToMap(string line, int type) {
    if(line == "") return;
    int i = 0;
    string current;
    while(line[i] || line[i-1]) {
        if(line[i] == ',' || !line[i]) {
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

void readTransition(string line){
    if(line == "") return;
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

bool isFinal(string state) {
    return finalStates.find(state) != finalStates.end() ? true : false;
}

void printVector(vector<string> vec) {
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << '\n';
    }
}

// Checks possible transistions and recursively calls next state
bool traverse(string word, int count, string state, bool &finished, vector<string> visited) {
    visited.push_back(state);
    if(count >= word.size()) {
        if(isFinal(state)) {
            cout << "Possible solution\n";
            printVector(visited);
            finished = true;
        }
    }
    string symbol = word.substr(count, 1);

    // Look for for epsilon
    auto range_e = automata[state].equal_range("&");
    for (auto it = range_e.first; it != range_e.second; ++it) {
        string nextState = it->second;
        if(visitedEpsilonSets.find(nextState) != visitedEpsilonSets.end()) {
            continue;
        }
        visitedEpsilonSets.emplace(state);
        traverse(word, count, nextState, finished, visited);
    }

    // Every possible transition for given state
    auto range = automata[state].equal_range(symbol);
    for (auto it = range.first; it != range.second; ++it) {
        visitedEpsilonSets.clear();
        string nextState = it->second;
        traverse(word, count+1, nextState, finished, visited);
    }
    return finished;
}

int main() {
    //Reading Text File
    string firstLine,secondLine,thirdLine,fourthLine,nextLine;
    ifstream myReadFile;
    string line;
    myReadFile.open("text2.txt");
    if(myReadFile.is_open()){
        myReadFile >> firstLine;
        myReadFile >> secondLine;
        myReadFile >> thirdLine;
        myReadFile >> fourthLine;
        while(myReadFile >> nextLine){
            readTransition(nextLine);
        }
    }
    readToMap(firstLine, 0);
    readToMap(fourthLine, 1);
    string word;
    vector<string> visited;
    getline(cin, word);
    bool finished = false;
    if(traverse(word, 0, thirdLine, finished, visited)) {
        cout << "True!\n";
    } else {
        cout << "False\n";
    }
    return 1;
}
