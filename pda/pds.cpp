#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

unordered_map<char,vector<string>> automata;

void lineToAutomata(string line) {
    string current;
    vector<string> states;
    char state = line[0];
    if(line[1] != '-' && line[2] != '>') return;
    for(int i = 3; i <= line.size(); i++) {
        if(i == line.size() || line[i] == '|') {
            states.push_back(current);
            current.clear();
        } else {
            current += line[i];
        }
    }
    automata.emplace(state, states);
}

string automataFromFile(string fileName) {
    ifstream file;
    string dummy, initialState, line;
    file.open(fileName);
    if(file.is_open()){
        file >> dummy;
        file >> dummy;
        file >> initialState;
        while(file >> line){
            lineToAutomata(line);
        }
    }
    return initialState;
}

vector<string> getMatchStates(char currentState, char terminal) {
    auto search = automata.find(currentState);
    vector<string> states, result;
    if(search != automata.end()) {
        states = search->second;
    }
    else {
        std::cout << "Not found\n";
    }
    for(int i = 0; i < states.size(); i++) {
        if(states[i][0] == terminal || states[i][0] == '&') {
            result.push_back(states[i]);
        }
    }
    return result;
}

bool isState(char current) {
    if(automata.find(current) != automata.end()) {
        return true;
    }
    return false;
}

void traverse(string push, string input, int index, vector<string> visited, stack<char> s) {
    visited.push_back(push);
    for(int i = push.size()-1; i >= 0; i--) {
        s.push(push[i]);
    }
    while(s.size() > 0) {
        char current = s.top();
        if (!isState(current)) {
            if (current == input[index]) {
                s.pop();
                index++;
            } else if(current == '&') {
                s.pop();
            } else {
                return;
            }
        } else {
            vector<string> possibleStates = getMatchStates(current, input[index]);
            if(possibleStates.size() == 0) return;
            s.pop();
            for(int i = 0; i < possibleStates.size(); i++) {
                traverse(possibleStates[i], input, index, visited, s);
            }
        }
    }
    if(index == input.size() && push == "&") {
        for(int i = 0; i < visited.size(); i++) {
            cout << visited[i] << " ";
        }
        cout << '\n';
        return;
    }
}

int main() {
    stack<char> stack;
    vector<string> visited;
    string initialState = automataFromFile("data.txt");
    cout << "Type your input.\n\"exit\" quits the program.\n";
    string input;
    while(input != "exit") {
        cin >> input;
        traverse(initialState, input, 0, visited, stack);
    }
    return 0;
}