#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define filename "input.txt"

vector<string> spelled{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int firstDigit(string str) {
    // cout << str << "\n";
    for (int i =0; i < str.length(); ++i) {
        int asc = int(str[i]);
        // cout << asc << "\n";
        if (int('0') <= asc && asc <= int('9')) {
            //cout << str[i] << " - ";
            return asc - int('0');
        }
    }
    return -1;
}

int firstDigitReal(string str) {
    // cout << str << "\n";
    for (int i =0; i < str.length(); ++i) {
        int asc = int(str[i]);
        // check for digit
        if (int('0') <= asc && asc <= int('9')) {
            return asc - int('0');
        }

        //check for spelled number
        vector<string> ins;
        if (str.length() - i - 1 >= 3) {
            ins.push_back(str.substr(i, 3));
        }
        if (str.length() - i - 1 >= 4) {
            ins.push_back(str.substr(i, 4));
        }
        if (str.length() - i - 1 >= 5) {
            ins.push_back(str.substr(i, 5));
        }

        for (string t : ins) {
            for (int i = 0; i < spelled.size(); i++) {
                if (t == spelled[i]) {
                    return i+1;
                    ins.clear();
                }
            }
        }

        ins.clear();

    }
    return -1;
}


int lastDigit(string str) {
    for (int i =str.length()-1; i >= 0; --i) {
        int asc = int(str[i]);
        if (int('0') <= asc && asc <= int('9')) {
            //cout << str[i] << " \n";
            return asc - int('0');
        }
    }
    return -1;
}

int lastDigitReal(string str) {
    for (int i =str.length()-1; i >= 0; --i) {
        int asc = int(str[i]);
        if (int('0') <= asc && asc <= int('9')) {
            //cout << str[i] << " \n";
            return asc - int('0');
        }

        //check for spelled number
        vector<string> ins;
        if (i - 2 >= 0) {
            ins.push_back(str.substr(i-2, 3));
        }
        if (i - 3 >= 0) {
            ins.push_back(str.substr(i-3, 4));
        }
        if (i-4 >= 0) {
            ins.push_back(str.substr(i-4, 5));
        }

        for (string t : ins) {
            for (int i = 0; i < spelled.size(); i++) {
                if (t == spelled[i]) {
                    return i+1;
                    ins.clear();
                }
            }
        }

        ins.clear();

    }
    return -1;
}

int part1(vector<string> input) {
    int sum = 0;
    for (string s : input) {
        //cout << s << "\n";
        sum += firstDigit(s) * 10 + lastDigit(s);
    }
    return sum;
}

int part2(vector<string> input) {
    int sum = 0;
    for (string s : input) {
        //cout << s << "\n";
        sum += firstDigitReal(s) * 10 + lastDigitReal(s);
    }
    return sum;
}

int main() {
    ifstream myFile(filename);
    string line;

    vector<string> input;

    while (getline(myFile, line)) {
        input.push_back(line);
    }
    myFile.close();
    
    cout << "Part 1: " << part1(input) <<"\n";
    cout << "Part 2: " << part2(input) <<"\n";

    input.clear();
}


