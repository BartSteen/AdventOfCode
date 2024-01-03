#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

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

int deco(string s) {
    int multiplier = 17;
    int remainder = 256;

    int val = 0;
    for (int i = 0; i < s.length(); i++) {
        val += int(s.at(i));
        //cout << "Value of " << s.at(i) << " is " << int(s.at(i)) << endl;
       // cout << "Val after add : " << val << endl;
        val *= multiplier;
       // cout << "Val after mult : " << val << endl;
        val %= remainder;
       // cout << "Val after rem : " << val << endl;
    }
    return val;
}

int part1(vector<string> input) {
    int sum = 0;
    for (string s : input) {
        int add = deco(s);
        sum += add;
        //cout << s << " - " << add << endl;
    }
    return sum;
}



int part2(vector<string> input) {
    vector<string> boxes[256];

    for (string s : input) {
        if (s.find('=') != string::npos) {
            bool added = false;
            int box = deco(s.substr(0, s.find('=')));
            for (int i = 0; i < boxes[box].size(); i++) {
                string curs = boxes[box][i];
                if (curs.substr(0, curs.find('=')) == s.substr(0, s.find('='))) {
                    boxes[box][i] = s;
                    added = true;
                }
            } 
            if (!added) {
                boxes[box].push_back(s);
            }
        } else {
            //s contains -
            int boxToDeleteFrom = deco(s.substr(0, s.length() - 1));
            for (int i = 0; i < boxes[boxToDeleteFrom].size(); i++) {
                string curs = boxes[boxToDeleteFrom][i];
                if (curs.substr(0, curs.find('=')) == s.substr(0, s.length() - 1)) {
                    boxes[boxToDeleteFrom].erase(boxes[boxToDeleteFrom].begin() + i);
                }
            } 
        }
    }

    // for (int i = 0; i < 256; i++) {
    //     if (boxes[i].size() > 0) {
    //         cout << "Box " << i << ": ";
    //     }
    //     for (int j = 0; j < boxes[i].size(); j++) {
    //         cout << boxes[i][j] << " ";
    //     }
    //     if (boxes[i].size() > 0) {
    //         cout << endl;
    //     }    
    // }

    int sum = 0;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < boxes[i].size(); j++) {
            int foc = stoi(boxes[i][j].substr(boxes[i][j].find('=') + 1));
            sum += (i+1) * (j+1) * foc;
        }
    }

    return sum;
}

int main() {

    ifstream myfile(filename);
    string line;

    vector<string> input;

    while (getline(myfile, line)) {
         input = split(line, ',');
    }

    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;

    return -1;
}