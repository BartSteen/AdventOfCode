#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define FILENAME "input.txt"

using namespace std;

bool isContained(vector<int> input) {
    return (input[0] <= input[2] && input[3] <= input[1]) || (input[2] <= input[0] && input[1] <= input[3]);
}


int part1(vector<vector<int>> input) {
    int score = 0;

    for (vector<int> line : input) {
        if (isContained(line)) {
            score++;
        }
    }
    return score;
}

bool doesOverlap(vector<int> input) {
    return ((input[2] <= input[0] && input[0] <= input[3]) || (input[2] <= input[1] && input[1] <= input[3]) || (input[0] <= input[2] && input[2] <= input[1]) || (input[0] <= input[3] && input[3] <= input[1]));
    //return (input[0] <= input[2] && input[3] <= input[1]) || (input[2] <= input[0] && input[1] <= input[3]);
}


int part2(vector<vector<int>> input) {
    int score = 0;

    for (vector<int> line : input) {
        if (doesOverlap(line)) {
            score++;
        //             for (int val : line) {
        //     cout << " " << val;
        // }
        // cout <<"\n";
        }
    }
    return score;
}

int main() {
    //read in input
    ifstream myfile(FILENAME);
    vector<vector<int>> input;
    string temp;

    while (getline(myfile, temp)) {
        int l1 = stoi(temp.substr(0, temp.find('-')));
        int u1 = stoi(temp.substr(temp.find('-')+1, temp.find(',')));
        int l2 = stoi(temp.substr(temp.find(',')+1, temp.find('-', temp.find(',')+1)));
        int u2 = stoi(temp.substr(temp.find('-', temp.find(',')+1) + 1));
        input.push_back({l1, u1, l2, u2});
    }

    // for (vector<int> line : input) {
    //     for (int val : line) {
    //         cout << " " << val;
    //     }
    //     cout <<"\n";
    // }

    cout << "Part 1: " << part1(input) << "\n";
    cout << "Part 2: " << part2(input) << "\n";



    return -1;
}