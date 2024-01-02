#include <iostream>
#include <string>
#include <fstream>
#include <vector>


#define FILENAME "input.txt"
using namespace std;

bool hasDuplicate(char lasts[], int size) {

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (lasts[i] == lasts[j]) {
                return true;
            }
        }

    }

    return false;
}


int part1(string input) {
    char lasts[4];
    
    for (int i = 0; i < 4; i++) {
        lasts[i] = input.at(i);
    }
    if (!hasDuplicate(lasts, 4)) {
        return 4;
    }

    for (int i = 4; i < input.length(); i++) {
        //shuffle
        for (int j = 1; j < 4; j++) {
            lasts[j-1] = lasts[j];
        }
        lasts[3] = input.at(i);
        if (!hasDuplicate(lasts, 4)) {
            return i + 1;
        }
    }

    return -1;

}

int part2(string input) {
    char lasts[14];
    
    for (int i = 0; i < 14; i++) {
        lasts[i] = input.at(i);
    }
    if (!hasDuplicate(lasts, 14)) {
        return 14;
    }

    for (int i = 14; i < input.length(); i++) {
        //shuffle
        for (int j = 1; j < 14; j++) {
            lasts[j-1] = lasts[j];
        }
        lasts[13] = input.at(i);
        if (!hasDuplicate(lasts, 14)) {
            return i + 1;
        }
    }

    return -1;

}

int main() {

    ifstream myfile(FILENAME);
    string input;
    getline(myfile, input);


    myfile.close();

    cout << "Part 1: " << part1(input) << "\n";
    cout << "Part 2: " << part2(input) << "\n";

    return -1;
}