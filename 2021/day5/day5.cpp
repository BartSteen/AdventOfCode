#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define SIZE 1000

using namespace std;

//returns how to get from a to b, if a < b then +1 if a > b then -1 else 0
int direction(int a, int b) {
    if (a < b) {
        return 1;
    } else if (a > b) {
        return -1;
    } else {
        return 0;
    }
}

int part1() {
    //create field
    static int field[SIZE][SIZE] = {0};

    ifstream infile("input.txt");
    string line;
    while (getline(infile, line)) {
        //split the string ex: 100,977 -> 501,576
        string delim = "->";
        string firstHalf = line.substr(0, line.find(delim));
        string secondHalf = line.substr(line.find(delim) + delim.length() + 1, line.length());
        int x1, y1, x2, y2;
        x1 = stoi(firstHalf.substr(0, firstHalf.find(",")));
        y1 = stoi(firstHalf.substr(firstHalf.find(",") + 1, firstHalf.length()));
        x2 = stoi(secondHalf.substr(0, secondHalf.find(",")));
        y2 = stoi(secondHalf.substr(secondHalf.find(",") + 1, secondHalf.length()));

        //parse line
        if (x1 == x2) {
            //vertical line 
            for (int i = min(y1,y2); i <= max(y1,y2); i++) {
                field[i][x1]++; 
            }
        } else if (y1 == y2) {
            //horizontal line
            for (int i = min(x1,x2); i <= max(x1,x2); i++) {
                field[y1][i]++; 
            }
        }
    }
    //go through field
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] >= 2) {
                count++;
            }
        }
    }
    return count;
}

int part2() {
    //create field
    static int field[SIZE][SIZE] = {0};

    ifstream infile("input.txt");
    string line;
    while (getline(infile, line)) {
        //split the string ex: 100,977 -> 501,576
        string delim = "->";
        string firstHalf = line.substr(0, line.find(delim));
        string secondHalf = line.substr(line.find(delim) + delim.length() + 1, line.length());
        int x1, y1, x2, y2;
        x1 = stoi(firstHalf.substr(0, firstHalf.find(",")));
        y1 = stoi(firstHalf.substr(firstHalf.find(",") + 1, firstHalf.length()));
        x2 = stoi(secondHalf.substr(0, secondHalf.find(",")));
        y2 = stoi(secondHalf.substr(secondHalf.find(",") + 1, secondHalf.length()));

        //parse line
        if (x1 == x2) {
            //vertical line 
            for (int i = min(y1,y2); i <= max(y1,y2); i++) {
                field[i][x1]++; 
            }
        } else if (y1 == y2) {
            //horizontal line
            for (int i = min(x1,x2); i <= max(x1,x2); i++) {
                field[y1][i]++; 
            }
        } else {
            //diagonal line
            while (x1 != x2) {
                field[y1][x1]++;
                x1 += direction(x1, x2);
                y1 += direction(y1, y2);
            }
            field[y2][x2]++;
        }
    }
    //go through field
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] >= 2) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int result = part2();
    cout << "Part 2 result: " << result;
    

    return 0;
}