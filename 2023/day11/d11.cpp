#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#define filename "input.txt"

#define galaxy '#'
#define empty '.'

void expand(vector<string> &input) {
    //first row expansion
    for (int i = 0; i < input.size(); i++) {

        bool isEmpty = true;
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == galaxy) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
            string emptyLine = string(input[i].size(), empty);
            input.insert(input.begin() + i, emptyLine);
            i++;
        }
    }

    //then column expansion
    for (int j = 0; j < input[0].size(); j++) {
        bool isEmpty = true;
        for (int i = 0; i < input.size(); i++) {
            if (input[i][j] == galaxy) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
            for (int i = 0; i < input.size(); i++) {
                input[i].insert(input[i].begin() + j, empty);
            }
            j++;
        }
    }
}

vector<vector<int>> findGalaxies(vector<string> &input) {
    vector<vector<int>> result;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == galaxy) {
                result.push_back({i,j});
            }
        }
    }
    return result;
}

int distance(vector<int> &a, vector<int> &b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

int part1(vector<string> input) {
    expand(input);
    // for (string in : input) {
    //     cout << in << endl;
    // }

    //find coordinates of galaxies
    vector<vector<int>> coords = findGalaxies(input);

    int sum = 0;
    for (int i = 0; i < coords.size(); i++) {
        for (int j = i+1; j < coords.size(); j++) {
            int d = distance(coords[i], coords[j]);
            sum += d;
        }
    }

    return sum;
}

long long part2(vector<string> input) {
    const long magnifier = 1000000;

    vector<int> emptyRows;
    vector<int> emptyCols;

    for (int i = 0; i < input.size(); i++) {
        bool isEmpty = true;
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == galaxy) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
            emptyRows.push_back(i);
        }
    }

    //then column expansion
    for (int j = 0; j < input[0].size(); j++) {
        bool isEmpty = true;
        for (int i = 0; i < input.size(); i++) {
            if (input[i][j] == galaxy) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
            emptyCols.push_back(j);
        }
    }

    vector<vector<int>> coords = findGalaxies(input);

    long long sum = 0;
    for (int i = 0; i < coords.size(); i++) {
        for (int j = i+1; j < coords.size(); j++) {
            long long d = distance(coords[i], coords[j]);
            sum += d;

            for (int r : emptyRows) {
                if (min(coords[i][0], coords[j][0]) <= r && r <= max(coords[i][0], coords[j][0])) {
                    sum += magnifier-1;
                }
            }
            for (int c : emptyCols) {
                if (min(coords[i][1], coords[j][1]) <= c && c <= max(coords[i][1], coords[j][1])) {
                    sum += magnifier-1;
                }
            }

        }
    }


    return sum;
}

int main() {
    string line;
    ifstream myfile(filename);

    vector<string> input;
    while (getline(myfile, line)) {
        input.push_back(line);
    }


    cout << "Part 1: " << part1(input) <<endl;
    cout << "Part 2: " << part2(input) <<endl;

    return -1;
}