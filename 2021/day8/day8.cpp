#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


bool isUniq(int val) {
    int digits[] = {2,3,4,7};
    for (auto i : digits) {
        if ( i == val ) {
            return true;
        }
    }
    return false;
}

int part1() {
    ifstream inpfile("input.txt");
    int count = 0;
    string line;
    while (getline(inpfile, line)) {
        string signal = line.substr(0, line.find("|"));
        string output = line.substr(line.find("|") + 2, line.length());

        // cout << "signal: " << signal << "\n";
        // cout << "output: " << output << "\n";

        //get output values
        vector<string> numsEnc;

        int curInd = 0;
        while (output.find(" ") != string::npos) {
            string numEnc = output.substr(0, output.find(" "));
            numsEnc.push_back(numEnc);
            output.erase(0, output.find(" ") + 1);
        }
        //last word
        numsEnc.push_back(output);
        // cout << "filtered: ";
        // for (auto enc : numsEnc) {
        //     cout << enc << " - ";
        // }
        // cout << "\n";

        for (auto enc : numsEnc) {
            if (isUniq(enc.length())) {
                count++;
            }
        }

    }
    
    
    return count;
}

int main() {
    cout << "Result part 1: " << part1();
    return 0;
}