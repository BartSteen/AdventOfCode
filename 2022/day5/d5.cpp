#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define FILENAME "input.txt"


vector<string> split(string str, char delim) {
    vector<string> res;
    int oldIndex = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == delim) {
            res.push_back(str.substr(oldIndex, i-oldIndex));
            oldIndex = i+1;
        }
    }
    res.push_back(str.substr(oldIndex));
    return res;
}

int indexToId(int index) {
    return (index - 1) / 4;
}

string part1(vector<vector<char>> stacks, vector<vector<int>> moves, int n) {

    for (vector<int> move : moves) {
        int amount = move[0];
        int from = move[1] - 1;
        int to = move[2] - 1;

        while  (amount > 0) {
            char c = stacks[from].back();
            stacks[from].pop_back();
            stacks[to].push_back(c);
            amount--;
        }
    //         for (vector<char> stack : stacks) {
    //     for (char c : stack) {
    //         cout << " " << c;
    //     }
    //     cout << "\n";
    // } 
    }
    string result = "";
    for (vector<char> stack : stacks) {
        if (stack.size() > 0)  {
            result += stack.back();
        }

    } 
    return result;
}

string part2(vector<vector<char>> stacks, vector<vector<int>> moves, int n) {

    for (vector<int> move : moves) {
        int amount = move[0];
        int from = move[1] - 1;
        int to = move[2] - 1;

        for (int i = stacks[from].size() - amount; i < stacks[from].size(); i++) {
            stacks[to].push_back(stacks[from][i]);
        }
        for (int i = 0; i < amount; i++) {
            stacks[from].pop_back();
        }
        
    //         for (vector<char> stack : stacks) {
    //     for (char c : stack) {
    //         cout << " " << c;
    //     }
    //     cout << "\n";
    // } 
    }
    string result = "";
    for (vector<char> stack : stacks) {
        if (stack.size() > 0)  {
            result += stack.back();
        }

    } 
    return result;
}

//+2:30
int main() {

    ifstream myfile(FILENAME);
    vector<pair<int, char>> input;
    vector<vector<int>> moves;
    int n = 0;
    bool moveMode = false;

    // vector<string> res = split("Hello This weird world j f", ' ');
    // for (auto str : res) {
    //     cout << str << "\n";
    // }
    string temp;
    while (getline(myfile, temp)) {
        if (temp.size() == 0) { //(temp.find('[') == string::npos) {
            moveMode = true;
            //skip blank line
            continue;
        } 
        if (!moveMode) {
            int index = -1;
            //cout << index << " < " << temp.length() << " : " << (index < temp.length()) << "\n";
            while (index + 1 < temp.length()) {
                index = temp.find('[', index+1);
                if (index == string::npos) {
                    break;
                }
                input.push_back(make_pair(indexToId(index + 1), temp.at(index+1)));
                n = max(n, indexToId(index+1) + 1);
            }
        } else {
            vector<string> res = split(temp, ' ');
            moves.push_back({stoi(res[1]), stoi(res[3]), stoi(res[5])});
        }

    }
    myfile.close();

    // for (vector<int> v : moves) {
    //     cout << v[0] << " - " << v[1] << " - " << v[2] << "\n";
    // }
    // for (pair<int, char> p : input) {
    //     cout << p.first << " - " << p.second << "\n";
    // }


    //input to stacks
    vector<vector<char>> stacks(n);
    for (pair<int, char> p : input) {
        stacks[p.first].insert(stacks[p.first].begin(), p.second);
    }

    // for (vector<char> stack : stacks) {
    //     for (char c : stack) {
    //         cout << " " << c;
    //     }
    //     cout << "\n";
    // } 

    cout << "Part 1: " << part1(stacks, moves, n) << "\n";
    cout << "Part 2: " << part2(stacks, moves, n) << "\n";

    return -1;
}