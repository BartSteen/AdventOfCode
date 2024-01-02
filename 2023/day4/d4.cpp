#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

#define filename "test.txt"

vector<string> split(string str, char del) {
    stringstream ss(str);
    string part;
    vector<string> res;
    while (!ss.eof()) {
        getline(ss, part, del);
        res.push_back(part);        
    }
    return res;
}

int part1(vector<vector<vector<int>>> input) {
    int res = 0;
    for (vector<vector<int>> card : input) {
        int cardRes = 0;
        for (int v : card[1]) {
            if (find(card[0].begin(), card[0].end(), v) != card[0].end()) {
                if (cardRes == 0) {
                    cardRes++;
                } else {
                    cardRes *= 2;
                }
            }
        }
        res += cardRes;
    }
    return res;
}

int part2(vector<vector<vector<int>>> input) {
    int n = input.size();
    int curCards[n] = {1}; 
    fill_n(curCards,n, 1);

    for (int i = 0; i < n; i++) {
        int winningNums = 0;
        vector<vector<int>> card = input[i];
        for (int v : card[1]) {
            if (find(card[0].begin(), card[0].end(), v) != card[0].end()) {
                winningNums++;
            }
        }
        for (int j = i+1; j <= min(n-1, i+winningNums); j++) {
            curCards[j]+= curCards[i];
        }

    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        res += curCards[i];
    }

    return res;
}

int main() {

    string line;
    ifstream myFile(filename);
    vector<vector<vector<int>>> input;

    while (getline(myFile, line)) {
        string numsOnly = line.substr(line.find(':') + 1);
        vector<string> numsplit = split(numsOnly, '|');
        vector<int> winning;
        vector<int> haves;
        for (string s : split(numsplit[0], ' ')) {
            if (s != "") {
                winning.push_back(stoi(s));
            }
        }
        for (string s : split(numsplit[1], ' ')) {
            if (s != "") {
                haves.push_back(stoi(s));
            }
        }

        input.push_back({winning, haves});
    }

    cout << "Part 1: " << part1(input) <<endl;
    cout << "Part 2: " << part2(input) <<endl;

    input.clear();

    return 0;
}