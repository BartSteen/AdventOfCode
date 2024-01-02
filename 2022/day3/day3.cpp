#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define FILENAME "input.txt"


int charToPrio(char c) {
    if (isupper(c)) {
        return ((int) c) - 64 + 26;
    } else {
        return ((int) c)  - 96;
    }
}

int part1(vector<string> input) {
    int res = 0;

    for (string str : input) {
        string comp1 = str.substr(0, str.length()/2);
        string comp2 = str.substr(str.length()/2);

        bool contains[52] = {false};

        for (char c : comp1) {
            contains[charToPrio(c)-1] = true;
        } 

        for (char c : comp2) {
            if (contains[charToPrio(c)-1]) {
                res += charToPrio(c);
                
                //cout << "found char " << c << "\n";
                break;
            }
        } 
    }

    return res;
}

int part2(vector<string> input) {
    int res = 0;

    for (int i = 0; i < input.size(); i+=3) {
        string str1 = input[i];
        string str2 = input[i+1];
        string str3 = input[i+2];

        int occurs[52] = {false};

        for (int j = i; j < i + 3; j++) {
            bool contains[52] = {false};
            for (char c : input[j]) {
                if (!contains[charToPrio(c)-1]) {
                    occurs[charToPrio(c)-1]++;
                    if (occurs[charToPrio(c)-1] == 3) {
                        res += charToPrio(c);
                        break;
                    }
                }
                contains[charToPrio(c)-1] = true;
            } 
        }
    }

    return res;
}



int main() {

    vector<string> inp;
    ifstream myfile(FILENAME);

    string temp;
    while (getline(myfile, temp)) {
        inp.push_back(temp);
    }
    myfile.close();

    cout << "part 1: " << part1(inp) << "\n";
    cout << "part 2: " << part2(inp) << "\n";

    return -1;
}