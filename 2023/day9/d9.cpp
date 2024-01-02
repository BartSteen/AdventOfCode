#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
#define filename "input.txt"

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

long findNext(vector<long> input) {
    vector<vector<long>> ana;
    ana.push_back(input);
    while (true) {
        bool allZeros = true;
        for (int v : ana[ana.size()-1]) {
            allZeros = allZeros && v == 0;
        }
        if (allZeros) {
            break;
        }

        //add difference sequence below it
        vector<long> newSeq;
        for (int i = 0; i < ana[ana.size()-1].size() - 1; i++) {
            newSeq.push_back(ana[ana.size()-1][i+1] - ana[ana.size()-1][i]);
        }        
        ana.push_back(newSeq);
    }
    // for (vector<long> vec : ana) {
    //     for (long v : vec) {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }

    //find return
    long c = 0;
    for (int i = ana.size()-2; i >= 0; i--) {
        c += ana[i][ana[i].size()-1];
    }

    return c;
}

long part1(vector<vector<long>> input) {
    long sum = 0;
    for (vector<long> seq : input) {
        sum += findNext(seq);
    }
    return sum;
}

long part2(vector<vector<long>> input) {


    for (int j = 0; j < input.size(); j++) {
        // for (int i : v) {
        //     cout << i << " ";
        // }
        // cout << endl;

        reverse(input[j].begin(), input[j].end());

    }
    return part1(input);
}

int main() {
    ifstream myfile(filename);
    string line;
    vector<vector<long>> input;
    while (getline(myfile, line)) {
        vector<string> nums = split(line, ' ');
        vector<long> t;
        for (string s : nums) {
            t.push_back(stol(s));
        }
        input.push_back(t);
    }

    cout << "Part 1: " << part1(input) <<endl;
    //cout << "Part 1: " << part1(hands, bids) <<endl;
    cout << "Part 2: " << part2(input) <<endl;

    return -1;
}