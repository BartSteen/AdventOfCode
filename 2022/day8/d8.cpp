#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
#define FILENAME "input.txt"

int part1(vector<vector<int>> hm) {
    int tally = 0;
    for (int i = 0; i < hm.size(); i++) {
        for (int j = 0; j < hm[i].size(); j++) {
            bool visible = true;

            for (int k = 0; k < i; k++) {
                if (hm[k][j] >= hm[i][j]) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
             //   cout << i  << " - " << j << " Is visible\n";

                tally++;
                continue;
            }

            visible = true;

            for (int k = i+1; k < hm.size(); k++) {
                if (hm[k][j] >= hm[i][j]) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
               //             cout << i  << " - " << j << " Is visible\n";

                tally++;
                continue;
            }

            visible = true;

            for (int k = 0; k < j; k++) {
                if (hm[i][k] >= hm[i][j]) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                //            cout << i  << " - " << j << " Is visible\n";

                tally++;
                continue;
            }

            visible = true;

            for (int k = j+1; k < hm[i].size(); k++) {
                if (hm[i][k] >= hm[i][j]) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
               //             cout << i  << " - " << j << " Is visible\n";

                tally++;
                continue;
            }

        }
    }
    return tally;
}

int part2(vector<vector<int>> hm) {
    int highestScore = 0;
    for (int i = 0; i < hm.size(); i++) {
        for (int j = 0; j < hm[i].size(); j++) {
            int score = 1;

            bool early = false;
            for (int k = i-1; k > 0; k--) {
                if (hm[k][j] >= hm[i][j]) {
                    score *= (i-k);
                    early = true;
                    break;
                }
            }

            if (!early) {
                score *= i;
            }
        

            early = false;
            for (int k = i+1; k < hm.size(); k++) {
                if (hm[k][j] >= hm[i][j]) {
                    score *= (k-i);
                    early = true;

                    break;
                }
            }
            if (!early) {
                score *= hm.size() - 1 -  i;
            }


            early = false;

            for (int k = j-1; k >0; k--) {
                if (hm[i][k] >= hm[i][j]) {
                    score *= (j-k);
                    early = true;

                    break;
                }
            }
            if (!early) {
                score *= j;
            }

        early = false;

            for (int k = j+1; k < hm[i].size(); k++) {
                if (hm[i][k] >= hm[i][j]) {
                    score *= (k-j);
                    early = true;

                    break;
                }
            }
            if (!early) {
                score *= hm[i].size() - 1- j;
            }

            //cout << "score of [" << i << " " << j << "] is " << score << "\n";

            highestScore = max(score, highestScore);

        }
    }
    return highestScore;
}

int main() {

    ifstream myfile(FILENAME);
    vector<vector<int>> hm;

    string temp;
    while (getline(myfile, temp)) {
        vector<int> line;
        for (char & c : temp) {
            line.push_back(int(c) - 48);
        }
        hm.push_back(line);
    }

    myfile.close();

    cout << "Part 1: " << part1(hm) << "\n";
    cout << "Part 2: " << part2(hm) << "\n";

    // for (vector<int> vec : hm) {
    //     for (int i : vec) {
    //         cout << i;
    //     }
    //     cout <<"\n";
    // }

    return -1;
}