#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;
#define FILENAME "input.txt"


//move tpos to hpos neighbour
pair<int, int> movet(pair<int, int> hpos, pair<int, int> tpos) {
    int x = tpos.first;
    int y = tpos.second;
    if (abs(tpos.first - hpos.first) <= 1 && abs(tpos.second - hpos.second) <= 1) {
        return make_pair(x, y);
    }
    //same column
    if (tpos.first == hpos.first) {
        y += hpos.second > tpos.second ? 1 : -1;
        return make_pair(x, y);
    }
    //same row
    if (tpos.second == hpos.second) {
        x += hpos.first > tpos.first ? 1 : -1;
        return make_pair(x, y);
    }

    //diagonal move
    //not same row and not same column
    y += hpos.second > tpos.second ? 1 : -1;
    x += hpos.first > tpos.first ? 1 : -1;
    return make_pair(x, y);

}

int part1(vector<pair<char, int>> moves) {
    set<pair<int, int>> visited;
    pair<int, int> hpos = make_pair(0,0);
    pair<int, int> tpos = make_pair(0,0);

    for (pair<char, int> move : moves) {
        int amount = move.second;
        while (amount > 0) {
            if (move.first == 'U') {
                hpos.second++;
            }
            if (move.first == 'R') {
                hpos.first++;
            }
            if (move.first == 'D') {
                hpos.second--;
            }
            if (move.first == 'L') {
                hpos.first--;
            }
            //cout << move.first << "\n";

            tpos = movet(hpos, tpos);
            //cout << "hpos: [" << hpos.first << ", " << hpos.second << "]\ntpos: [" << tpos.first << ", " << tpos.second << "]\n";
            if (visited.find(tpos) == visited.end()) {
                visited.insert(make_pair(tpos.first, tpos.second));
            }
            amount--;
        }

    }
    return visited.size();
}

int part2(vector<pair<char, int>> moves) {
    set<pair<int, int>> visited;

    vector<pair<int, int>> posses;
    for (int i = 0; i < 10; i++) {
        posses.push_back(make_pair(0,0));
    }

    for (pair<char, int> move : moves) {
        int amount = move.second;
        while (amount > 0) {
            if (move.first == 'U') {
                posses[0].second++;
            }
            if (move.first == 'R') {
                posses[0].first++;
            }
            if (move.first == 'D') {
                posses[0].second--;
            }
            if (move.first == 'L') {
                posses[0].first--;
            }
            //cout << move.first << "\n";
            for (int i = 1; i < posses.size(); i++) {
                posses[i] = movet(posses[i-1], posses[i]);
            }

            // for (int i = 0; i < posses.size(); i++) {
            //     cout << " <- [" << posses[i].first << ", " << posses[i].second << "]";
            // }
            // cout << "\n";

            //cout << "tpos: [" << posses[posses.size()-1].first << ", " << posses[posses.size()-1].second << "]\n";
            if (visited.find(posses[posses.size()-1]) == visited.end()) {
                visited.insert(make_pair(posses[posses.size()-1].first, posses[posses.size()-1].second));
            }
            amount--;
        }

    }
    return visited.size();
}

int main() {

    vector<pair<char, int>> moves;

    ifstream myfile(FILENAME);
    string temp;
    while (getline(myfile, temp)) {
        moves.push_back(make_pair(temp.at(0), stoi(temp.substr(2))));
    }

    // for (pair<char, int> move : moves) {
    //     cout << move.first << " " << move.second << "\n";
    // }

    cout << "Part 1 : " << part1(moves) << "\n";
    cout << "Part 2 : " << part2(moves) << "\n";
    return -1;
}