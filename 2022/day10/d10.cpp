#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
#define FILENAME "input.txt"


long part1(vector<int> input) {
    long current = 1;
    int cyclenum = 0;
    // long prev1 = 0;
    // long prev2 = 0;
    long answer = 0;

    for (int i = 0; i < input.size() ;i++) {
            // prev1 = prev2;
            // prev2 = input[i];
            cyclenum++;
        if ((cyclenum - 20) % 40 == 0) {
            //cout << "iteration " << cyclenum << " : " << answer << " <- ans | cur -> " << current << "\n";
                answer += cyclenum * current;
        }
        if (input[i] != 0) {
            cyclenum++; 
            if ((cyclenum - 20) % 40 == 0) {
               // cout << "iteration " << cyclenum << " : " << answer << " <- ans | cur -> " << current << "\n";
                answer += cyclenum * current;
            }
        }
        current += input[i];
        //cout << "adding " << input[i] << " at cycle " << cyclenum << "\n";
    }

    return answer;
}

string part2(vector<int> input) {
    long current = 1;
    int cyclenum = 0;

    string answer = "";

    for (int i = 0; i < input.size() ;i++) {
            cyclenum++;
            //draw pixel
            if (abs(((cyclenum - 1) % 40) - current) <= 1) {
                answer += "#";
            } else {
                answer += ".";
            }

            if (cyclenum % 40 == 0) {
                answer += "\n";
            }

        if (input[i] != 0) {
            cyclenum++; 
            //draw pixel
            if (abs(((cyclenum - 1) % 40) - current) <= 1) {
                answer += "#";
            } else {
                answer += ".";
            }

            if (cyclenum % 40 == 0) {
                answer += "\n";
            }

        }
        
        current += input[i];
        //cout << "adding " << input[i] << " at cycle " << cyclenum << "\n";
    }

    return answer;
}

int main() {

    ifstream myfile(FILENAME);

    string temp;
    vector<int> input;

    while (getline(myfile, temp)) {
        if (temp.find(' ') != string::npos) {
            int val = stoi(temp.substr(temp.find(' ') + 1));
            input.push_back(val);
        } else {
            //is noop
            input.push_back(0);
        }
    }
    // for (auto v : input) {
    //     cout << v << "\n";
    // }

    cout << "Part 1: " << part1(input) << "\n";
    cout << "Part 2: \n" << part2(input) << "\n";

    return -1;
}