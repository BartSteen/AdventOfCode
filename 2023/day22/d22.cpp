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

struct Block {
    vector<int> a;
    vector<int> b;
    int dirIndex;

    Block(vector<int> a, vector<int> b) {
        if (a[0] != b[0]) {
            if (a[0] <= b[0]) {
                this->a = a;
                this->b = b;
            } else {
                this->a = b;
                this->b = a;
            }
            dirIndex = 0;
        } else if (a[1] != b[1]) {
            if (a[1] <= b[1]) {
                this->a = a;
                this->b = b;
            } else {
                this->a = b;
                this->b = a;
            }
            dirIndex = 1;
        } else {
            if (a[2] <= b[2]) {
                this->a = a;
                this->b = b;
            } else {
                this->a = b;
                this->b = a;
            }
            dirIndex = 2;
        }
    }

    int sortingVal() {
        return a[2];
    }

    bool occupies(vector<int> coordinate) {
        for (int i = 0; i <= 2; i++) {
            if (i != dirIndex) {
                if (coordinate[i] != a[i]) {
                    return false;
                }
            } else {
                //i == dirIndex
                if (!( a[i] <= coordinate[i] && coordinate[i] <= b[i])) {
                    return false;
                }
            }
        }
        return true;
    }

    vector<vector<int>> findBelowCoords() {
        vector<vector<int>> below;
        if (dirIndex == 2) {
            below = {{a[0], a[1], a[2]-1}};
        } else if (dirIndex == 0) {
            for (int i = a[0]; i <= b[0]; i++) {
                below.push_back({i, a[1], a[2]-1});
            }
        } else {
            //dirIndex == 1
            for (int i = a[1]; i <= b[1]; i++) {
                below.push_back({a[0], i, a[2]-1});
            }
        }

        return below;
    }

    void moveDownOne() {
        a[2]--;
        b[2]--;
    }

    bool isGrounded() {
        return a[2] == 1;
    }

};

bool compareBlockPointers(Block* first, Block* second) {
    return (*first).sortingVal() < (*second).sortingVal();
}

struct Field {

    vector<Block*> state;

    Field(vector<Block*> start) {
        state = start;
        sortState();
    }

    ~Field() {
        for (Block* b : state) {
            delete b;
        }
    }

    void sortState() {
        sort(state.begin(), state.end(), compareBlockPointers);
    }

    bool isOccupied(vector<int> coordinate) {
        for (Block* block : state) {
            if ((*block).occupies(coordinate)) {
                return true;
            }
        }
        return false;
    }

    void applyGravity() {
        for (int i = 0; i < state.size(); i++) {
            Block* block = state[i];
            while (!(*block).isGrounded()) {
                vector<vector<int>> belows = (*block).findBelowCoords();
                bool allFree = true;
                for (vector<int> coord : belows) {
                    for (int j = 0; j < i; j++) {
                        Block* b2 = state[j];
                        if ((*b2).occupies(coord)) {
                            allFree = false;
                            break;
                        }
                    }
                    if (!allFree) {
                        break;
                    }
                }
                if (allFree) {
                    (*block).moveDownOne();
                } else {
                    break;
                }

            }
        }
        sortState();
    }

    int countDisintegrable() {
        int answer = 0;
        vector<vector<int>> leansOn;
        vector<vector<int>> isLeanedOn;
        for (int i = 0; i < state.size(); i++) {
            leansOn.push_back({});
            isLeanedOn.push_back({});
        }
        for (int i = 0; i < state.size(); i++) {
            Block cur = *state[i];
            vector<vector<int>> belows = cur.findBelowCoords();
            for (vector<int> coord : belows) {
                for (int j = 0; j < i; j++) {
                    if ((*state[j]).occupies(coord)) {
                        isLeanedOn[j].push_back(i);
                        leansOn[i].push_back(j);
                    }
                }
            }

        }
        // for (int i = 0; i < state.size(); i++) {
        //     cout << i << endl;
        //     cout << "Leans on: ";
        //     for (int v : leansOn[i]) {
        //         cout << v << ", ";
        //     }
        //     cout << endl << "Is leaned on by: ";
        //     for (int v : isLeanedOn[i]) {
        //         cout << v << ", ";
        //     }
        //     cout << endl;
        // }

        for (int i = 0; i < state.size(); i++) {
            bool isSafe = true;
            for (int j : isLeanedOn[i]) {
                if (leansOn[j].size() == 1) {
                    isSafe = false;
                }
            }
            if (isSafe) {
                answer++;
            }
        }

        return answer;
    }

    void printState() {
        for (Block* block : state) {
            vector<int> a = (*block).a;
            vector<int> b = (*block).b;

            printf("(%d, %d, %d) -> (%d, %d, %d)\n", a[0], a[1], a[2], b[0], b[1], b[2]);
        }
    }

};

int part1(Field* field) {
    //(*field).printState();
    (*field).applyGravity();
    (*field).printState();
    return (*field).countDisintegrable();
}

int part2(Field* field) {
    return -1;
}

int main() {
    ifstream myfile(filename);
    string line;

    vector<Block*> input;
    while (getline(myfile, line)) {
        vector<string> parts = split(line, '~');

        vector<string> p1spl = split(parts[0], ',');
        vector<string> p2spl = split(parts[1], ',');

        vector<int> a;
        vector<int> b;
        for (int i = 0; i < 3; i++) {
            a.push_back(stoi(p1spl[i]));
            b.push_back(stoi(p2spl[i]));
        }

        input.push_back(new Block(a, b));
    }

    Field* field = new Field(input);

    cout << "Part 1: " << part1(field) << endl;
    cout << "Part 2: " << part2(field) << endl;

    delete field;

    return -1;
}