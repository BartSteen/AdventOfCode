#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#define filename "input.txt"

#define rock '#'
#define garden '.'
#define start 'S'
#define option 'O'

string repeatString(string s, int n) {
    string ans = "";
    for (int i = 0; i < n; i++) {
        ans = ans + s;
    }
    return ans;
}

struct Field {
    vector<string> state;
    int stepsMade;
    vector<string> base;
    int curMag ;
    int starti;
    int startj;

    Field(vector<string> state) {
        this->state = state;
        stepsMade = 0;
        base = state;
        curMag = 1;

        for (int i = 0; i < state.size(); i++) {
            for (int j = 0; j < state[i].size(); j++) {
                if (state[i][j] == start) {
                    starti = i;
                    startj = j;
                    this->state[i][j] = option;
                    base[i][j] = garden;
                    break;
                }
            }
        }
    }

    bool isValidCord(int i, int j) {
        return 0 <= i && i < state.size() && 0 <= j && j < state[i].size();
    }

    void makeStep() {
        vector<vector<bool>> becomeOption;
        for (int i = 0; i < state.size(); i++) {
            vector<bool> t;
            for (int j = 0; j < state[i].size(); j++) {
                t.push_back(false);
            }
            becomeOption.push_back(t);
        }

        for (int i = 0; i < state.size(); i++) {
            for (int j = 0; j < state[i].size(); j++) {
                if (state[i][j] == option) {
                    if (isValidCord(i-1,j)) {
                        becomeOption[i-1][j] = true;
                    }
                    if (isValidCord(i+1,j)) {
                        becomeOption[i+1][j] = true;
                    }
                    if (isValidCord(i,j-1)) {
                        becomeOption[i][j-1] = true;
                    }
                    if (isValidCord(i,j+1)) {
                        becomeOption[i][j+1] = true;
                    }
                }
            }
        }

        for (int i = 0; i < state.size(); i++) {
            for (int j = 0; j < state[i].size(); j++) {
                if (state[i][j] != rock) {
                    state[i][j] = becomeOption[i][j] ? option : garden;
                }
            }
        }
                                
        stepsMade++;
    }

    void expand() {
        for (int i = 0; i < base.size(); i++) {
            state.insert(state.begin(), repeatString(base[base.size() - 1 - i], curMag));
            state.push_back(repeatString(base[i], curMag));
        }
        //pad left and right
        for (int i = 0; i < state.size(); i++) {
            state[i] = base[i % base.size()] + state[i] + base[i % base.size()];
        }
        curMag += 2;
    }

    void makeStepWithExtension() {
        //check if any options at border, if yes expand
        bool shouldExpand = false;
        for (int i = 0; i < state.size(); i++) { 
            shouldExpand = shouldExpand || state[i][0] == option;\
            shouldExpand = shouldExpand || state[i][state[i].size()-1] == option;
        }
        for (int j = 0; j < state[0].size(); j++) { 
            shouldExpand = shouldExpand || state[0][j] == option;\
            shouldExpand = shouldExpand || state[state.size()-1][j] == option;
        }
        if (shouldExpand) {
            expand();
        }


        makeStep();
    }

    int countOptions() {
        int answer = 0;
        for (string s : state) {
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == option) {
                    answer++;
                }
            }
        }
        return answer;
    }

    void reset() {
        state = base;
        stepsMade = 0;
        curMag = 1;
        state[starti][startj] = option;
    }

    void printField() {
        cout << "Field after " << stepsMade << " steps resulting in a magnitude of " << curMag << endl; 

        for (string s : state) {
            cout << s << endl;
        }
    }


};

int part1(Field* field) {
    for (int i = 0; i < 64; i++) {
        (*field).makeStep();
    }
    return (*field).countOptions();
}

int part2(Field* field) {
    for (int i = 0; i < 327; i++) {
        (*field).makeStepWithExtension();
    }
    //(*field).printField();

    return (*field).countOptions();
}

int main() {
    
    ifstream myfile(filename);
    string line;

    vector<string> input;
    while(getline(myfile, line)) {
        // for (int i = 0; i < line.size(); i++) {
        //     if (line[i] == start) {
        //         line[i] = option;
        //     }
        // }
        input.push_back(line);
    }


    Field* field = new Field(input);


    cout << "Part 1: " << part1(field) << endl;
    (*field).reset();
    cout << "Part 2: " << part2(field) << endl;
    delete field;

    return -1;
}