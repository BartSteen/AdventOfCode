#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#define filename "input.txt"

int findMirrorRow(vector<string> &input) {
    for (int i = 1; i < input.size(); i++) {
        //try putting mirror BETWEEN rows i-1 and i
        int disp = 0;
        bool isGood = true;
        while (isGood && i - 1 - disp >= 0 && i + disp < input.size()) {
            isGood = isGood && (input[i-1-disp] == input[i+disp]);
            disp++;
        }
        if (isGood) {
            return i;
        }
    }
    return -1;
}

int findMirrorCol(vector<string> &input) {
    int cols = input[0].length();
    for (int i = 1; i < cols; i++) {
        //try putting mirror BETWEEN columns i-1 and i
        int disp = 0;
        bool isGood = true;
        while (isGood && i - 1 - disp >= 0 && i + disp < cols) {
            for (int j = 0; j < input.size() && isGood; j++) {
                isGood = isGood && (input[j].at(i-1-disp) == input[j].at(i+disp));
            }
            disp++;
        }
        if (isGood) {
            return i;
        }
    }
    return -1;
}

int part1(vector<vector<string>> &input) {
    int result = 0;
    for (vector<string> field : input) {
        int colRes = findMirrorCol(field);
        int add;
        if (colRes != -1) {
            add = colRes;
        } else {
            add = findMirrorRow(field) * 100;
        }
        //int add = max(findMirrorCol(field), findMirrorRow(field));
        result += add;
        //cout << add << endl;
    }
    return result;
}

int findMirrorRowOneOf(vector<string> &input) {
    for (int i = 1; i < input.size(); i++) {
        //try putting mirror BETWEEN rows i-1 and i
        int disp = 0;
        int amountOff = 0;
        while (amountOff <= 1 && i - 1 - disp >= 0 && i + disp < input.size()) {
            for (int j = 0; j < input[i].length() && amountOff <= 1; j++) {
                if (input[i-1-disp].at(j) != input[i+disp].at(j)) {
                    amountOff++;
                }
            }
            disp++;
        }
        if (amountOff == 1) {
            return i;
        }
    }
    return -1;
}

int findMirrorColOneOf(vector<string> &input) {
    int cols = input[0].length();
    for (int i = 1; i < cols; i++) {
        //try putting mirror BETWEEN columns i-1 and i
        int disp = 0;
        int amountOff = 0;
        while (amountOff <= 1 && i - 1 - disp >= 0 && i + disp < cols) {
            for (int j = 0; j < input.size() && amountOff <= 1; j++) {
                if (input[j].at(i-1-disp) != input[j].at(i+disp)) {
                    amountOff++;
                }
            }
            disp++;
        }
        if (amountOff == 1) {
            return i;
        }
    }
    return -1;
}

int part2(vector<vector<string>> &input) {
    int result = 0;
    for (vector<string> field : input) {
        int colRes = findMirrorColOneOf(field);
        int add;
        if (colRes != -1) {
            add = colRes;
        } else {
            add = findMirrorRowOneOf(field) * 100;
        }
        //int add = max(findMirrorCol(field), findMirrorRow(field));
        result += add;
        //cout << add << endl;
    }
    return result;
}

int main() {

    ifstream myfile(filename);
    string line;

    vector<vector<string>> input;
    vector<string> field;

    while (getline(myfile, line)) {
        if (line == "") {
            input.push_back(field);
            field.clear();
        } else {
            field.push_back(line);
        }
    }
    input.push_back(field);

    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;

    return -1;
}