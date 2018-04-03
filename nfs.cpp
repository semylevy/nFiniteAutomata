#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, unordered_multimap<string, string> > automata;

// Puts state transitions into matrix
void fillDataMatrix() {
    // For every state in the machine
    int states = 3;
    int lines = 2;
    for(int i = 0; i < states; i++) {
        string state;
        cout << "State\n";
        getline(cin, state);
        unordered_multimap<string, string> empty;
        automata.emplace(state, empty);
    }
    // For every transition function
    for(int i = 0; i < lines; i++) {
        string initialState, symbol, nextState;
        cout << "Initial state\n";
        getline(cin, initialState);
        cout << "Symbol\n";
        getline(cin, symbol);
        cout << "Next state\n";
        getline(cin, nextState);
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
    // Every possible transition for given state
    auto range = automata[state].equal_range(symbol);
    for (auto it = range.first; it != range.second; ++it) {
        cout << "traverse called on count " << count << "and wcount" << word.size() << endl;
        string nextState = it->second;
        std::cout << it->first << ' ' << it->second << '\n';
        return traverse(word, count+1, nextState);
    }
    return false;
}

int main() {
    fillDataMatrix();
    if(traverse("ab", 0, "q0")) {
        cout << "true";
    }
    return 1;
}