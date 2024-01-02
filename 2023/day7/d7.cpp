#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
#define filename "input.txt"
#define highest 14


int cardVal(char card) {
    if ('1' <= card && card <= '9') {
        return card - '0';
    }
    if (card == 'T') {
        return 10;
    }
    // if (card == 'J') {
    //     return 11;
    // }
    if (card == 'Q') {
        return 12;
    }
    if (card == 'K') {
        return 13;
    }
    if (card == 'A') {
        return 14;
    }
    if (card == 'J') {
        return 0;
    }
    return -1;
}

int handStrength(string hand) {
    int handVals[highest + 1];
    for (int i = 0; i < highest+1; i++) {
        handVals[i] = 0;
    }
    for (char card : hand) {
        handVals[cardVal(card)]++;
    } 
    // cout << hand << ": [";
    // for (int i = 1; i <= highest; i++) {
    //     cout << handVals[i] << ", ";
    // }
    // cout << "]" << endl;

    //check for five of a kind
    for (int i = highest; i >= 1; i--) {
        if (handVals[i] + handVals[0] == 5) {
            return 6;
        }
    }
    //check for four of a kind
    for (int i = highest; i >= 1; i--) {
        if (handVals[i] + handVals[0] == 4) {
            return 5;
        }
    }
    //check for full house
    for (int i = highest; i >= 1; i--) {
        for (int j = i-1; j >= 1; j--) {
            if (handVals[i] + handVals[j] + handVals[0] >= 5) {
                return 4; //CHECK
            }
        }   
    }
    
    //check for three of a kind
    for (int i = highest; i >= 1; i--) {
        if (handVals[i] + handVals[0] == 3) {
            return 3;
        }
    }

    //check for twopair 
    for (int i = highest; i >= 1; i--) {
        for (int j = i-1; j >= 1; j--) {
            if (handVals[i] + handVals[j] + handVals[0] >= 4) {
                return 2; //CHECK
            }
        }   
    }

    //check for pair
    for (int i = highest; i >= 1; i--) {
        if (handVals[i] + handVals[0] == 2) {
            return 1;
        }
    }
    //check for high card
    return 0;
}

bool comp(vector<string> h1, vector<string> h2) {
    //is h1 > h2?
    int h1Val = handStrength(h1[0]);
    int h2Val = handStrength(h2[0]);
    if (h1Val > h2Val) {
        return false;
    } else if (h1Val < h2Val) {
        return true;
    }
    //same type
    for (int i = 0; i < h1[0].length(); i++) {
        if (h1[0][i] == h2[0][i]) {
            continue;
        } else {
            return cardVal(h1[0][i]) < cardVal(h2[0][i]);
        }
    }

    //exactly the same hand
    return true;
}

//int part1(vector<string> & hands, vector<int> & bids) {
long part1(vector<vector<string>> input) {

    sort(input.begin(), input.end(), comp);
    // for (vector<string> v : input) {
    //     cout << v[0] << " - " << v[1] << " - " << handStrength(v[0])<< endl;
    
    // }

    long result = 0;
    for (int i = 0; i < input.size(); i++) {
        result += stol(input[i][1]) * (i+1);
    }

    return result;
}

// long part2(vector<vector<string>> input) {
//     sort(input.begin(), input.end(), comp);


//     long result = 0;
//     for (int i = 0; i < input.size(); i++) {
//         result += stol(input[i][1]) * (i+1);
//     }

//     return result;
// }

int main() {

    string line;
    ifstream myfile(filename);
    vector<string> hands;
    vector<int> bids;
    vector<vector<string>> input;

    while (getline(myfile, line)) {
        hands.push_back(line.substr(0, 5));
        bids.push_back(stoi(line.substr(6)));
        input.push_back({line.substr(0,5), line.substr(6)});
    }

    myfile.close();

    cout << "Part 1: " << part1(input) <<endl;
    //cout << "Part 1: " << part1(hands, bids) <<endl;
    cout << "Part 2: " << part1(input) <<endl;

    return 0;
}