#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#define filename "input.txt"
#define roundRock 'O'
#define cubeRock '#'
#define noRock '.'

void tiltNorth(vector<string> &field) {
    int width = field[0].length();
    int height = field.size();
    for (int i = 0; i < width; i++) {
        int prevObstacle = -1;
        for (int j = 0; j < height; j++) {
            if (field[j].at(i) == roundRock) {
                prevObstacle++;
                field[j][i] = noRock;
                field[prevObstacle][i] = roundRock;
            } else if (field[j].at(i) == cubeRock) {
                prevObstacle = j;
            }
        }
    }
}

int calculateNorthLoad(vector<string> &field) {
    int load = 0;
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[i].length(); j++) {
            if (field[i].at(j) == roundRock) {
                load += (field.size() - i);
            }
        }
    }
    return load;
}

void tiltSouth(vector<string> &field) {
    int width = field[0].length();
    int height = field.size();
    for (int i = 0; i < width; i++) {
        int prevObstacle = height;
        for (int j = height-1; j >= 0; j--) {
            if (field[j].at(i) == roundRock) {
                prevObstacle--;
                field[j][i] = noRock;
                field[prevObstacle][i] = roundRock;
            } else if (field[j].at(i) == cubeRock) {
                prevObstacle = j;
            }
        }
    }
}

void tiltWest(vector<string> &field) {
    int width = field[0].length();
    int height = field.size();
    for (int j = 0; j < height; j++) {
        int prevObstacle = -1;
        for (int i = 0; i < width; i++) {
            if (field[j].at(i) == roundRock) {
                prevObstacle++;
                field[j][i] = noRock;
                field[j][prevObstacle] = roundRock;
            } else if (field[j].at(i) == cubeRock) {
                prevObstacle = i;
            }
        }
    }
}

void tiltEast(vector<string> &field) {
    int width = field[0].length();
    int height = field.size();
    for (int j = 0; j < height; j++) {
        int prevObstacle = width;
        for (int i = width-1; i >= 0; i--) {
            if (field[j].at(i) == roundRock) {
                prevObstacle--;
                field[j][i] = noRock;
                field[j][prevObstacle] = roundRock;
            } else if (field[j].at(i) == cubeRock) {
                prevObstacle = i;
            }
        }
    }
}

int part1(vector<string> input) {
    tiltNorth(input);
    // for (auto s : input) {
    //     cout << s << endl;
    // }
    return calculateNorthLoad(input);
}

bool testForCycle(vector<int> &history, int index) {
    int pot = history.size() - index;
    if (pot > index) {
        return false;
    }

    for (int disp = 0; disp < pot; disp++) {
        if (history[index-disp] != history[history.size()-1-disp]) {
            return false;
        }
    }
    return true;
}

int potentialCycleLengthAtEnd(vector<int> &history, int threshold) {
    for (int i = 0; i < history.size() - 1; i++) {
        if (history.size() - 1- 1 > threshold && testForCycle(history, i)) {
            return history.size() - 1 - i;
        }
    }
    return -1;
}

int part2(vector<string> input) {
    vector<int> history;
    long cyclesToMake = 1000000000;
    for (long i = 0; i < cyclesToMake; i++) {
        tiltNorth(input);
        tiltWest(input);
        tiltSouth(input);
        tiltEast(input);
        history.push_back(calculateNorthLoad(input));
        cout << i << ": " << calculateNorthLoad(input) << endl;
        int t = potentialCycleLengthAtEnd(history, 5);
        if (t != -1) {
            cout << "POTENTIAL CYCLE: " << t << endl; 
            cyclesToMake = min(cyclesToMake, i + ((1000000000 - i) % t));
        }
    }
    return history[history.size()-1];
}

int main() {

    ifstream myfile(filename);
    string line;

    vector<string> input;

    while (getline(myfile, line)) {
         input.push_back(line);
    }

    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;

    return -1;
}