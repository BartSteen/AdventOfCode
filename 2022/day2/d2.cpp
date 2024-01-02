#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define FILENAME "input.txt"


int calcRoundScore(char opponent, char me) {
    int res = 0;
    if (me == 'X') {
        res += 1;
        if (opponent == 'C') {
            res += 6;
        } else if (opponent == 'A') {
            res += 3;
        }
    } else if (me == 'Y') {
        res += 2;
        if (opponent == 'A') {
            res += 6;
        } else if (opponent == 'B') {
            res += 3;
        }
    } else if (me == 'Z') {
        res += 3;
        if (opponent == 'B') {
            res += 6;
        } else if (opponent == 'C') {
            res += 3;
        }
    }

   // cout << opponent << " " << me << " " << res << "\n";
    return res;
}

int part1(vector<string> input) {
    int score = 0;
    for (string str : input) {
        char opp = str.at(0);
        char me = str.at(2);

        score += calcRoundScore(opp, me);
    }

    return score;
}

int part2(vector<string> input) {
    int score = 0;
    for (string str : input) {
        char opp = str.at(0);
        char out = str.at(2);
        char me;
        if (out == 'X') {
            switch(opp) {
                case 'A':
                me = 'Z';
                break;
                
                case 'B':
                me = 'X';
                break;
                
                case 'C':
                me = 'Y';
                break;
            }
        } else if (out == 'Y') {
            switch(opp) {
                case 'A':
                me = 'X';
                break;
                
                case 'B':
                me = 'Y';
                break;
                
                case 'C':
                me = 'Z';
                break;
            } 
            } else if (out == 'Z') {
                switch(opp) {
                    case 'A':
                    me = 'Y';
                    break;
                    
                    case 'B':
                    me = 'Z';
                    break;
                    
                    case 'C':
                    me = 'X';
                    break;
                }
        }
        

        score += calcRoundScore(opp, me);
    }

    return score;
}

int main() {

    ifstream myfile(FILENAME);
    vector<string> inp;
    string temp;
    while (getline(myfile, temp)) {
        inp.push_back(temp);
    }
    myfile.close();

    cout << "Part 1: " << part1(inp) << "\n";
    cout << "Part 2: " << part2(inp) << "\n";

    return -1;
}