#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;
#define filename "test.txt"

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
    vector<vector<int>> space;


    Block(vector<int> a, vector<int> b) {
        vector<int> left;
        vector<int> right;
        int dirIndex;
        if (a[0] != b[0]) {
            dirIndex = 0;
        } else if (a[1] != b[1]) {
            dirIndex = 1;
        } else {
            dirIndex = 2;
        }
        if (a[dirIndex] <= b[dirIndex]) {

            left = a;
            right = b;
        } else {

            left = b;
            right = a;
        }

        for (int i = a[dirIndex]; i <= b[dirIndex]; i++) {
            vector<int> toPush = {a[0], a[1], a[2]};
            toPush[dirIndex] = i;
            space.push_back(toPush);
        }

    }

    int zPos() {
        return space[0][2];
    }

    int lastzPos() {
        return space[space.size()-1][2];
    }

    void moveDown(int amount) {
        for (int i = 0; i < space.size(); i++) {
            space[i][2] -= amount;
        }
    }

    bool isGrounded() {
        return space[0][2] == 1;
    }

};

bool compareBlockPointers(Block* first, Block* second) {
    return (*first).zPos() < (*second).zPos();
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

    //returns true if b1 and b2 overlap if you disregard z coord
    bool overlapsIgnoringZ(Block* b1, Block* b2) {
        for (vector<int> v1 : (*b1).space) {
            for (vector<int> v2 : (*b2).space) {
                if (v1[0] == v2[0] && v1[1] == v2[1]) {
                    return true;
                }
            }
        }
        return false;
    }

    //figures out if block b1 is below block b2
    bool isBelow(Block* b1, Block* b2) {
        if ((*b1).lastzPos() >= (*b2).zPos()) {
            //b1 has higher zPos so can never be below b2
            return false;
        }
        //b1 is entirely below b2 in z coord, now check x and y
        return overlapsIgnoringZ(b1, b2);

    }

    //return how much we can move the given block down
    int findHowMuchCanDown(Block* block) {
        int down = (*block).zPos() - 1;
        for (Block* b2 : state) {
            if (isBelow(b2, block)) {
                down = min(down, (*block).zPos() - (*b2).lastzPos() - 1);
            }
        }
        return down;
    }

    void applyGravity() {
        for (Block* block : state) {
            int d = findHowMuchCanDown(block);
            (*block).moveDown(d);
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
            Block* b1 = state[i];
            for (int j = 0; j < i; j++) {
                Block* b2 = state[j];
                //check if b1 leans on b2
                if ((*b1).zPos() == (*b2).lastzPos() + 1 && overlapsIgnoringZ(b1, b2)) {
                    isLeanedOn[j].push_back(i);
                    leansOn[i].push_back(j);
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

    int countChainReactions() {
        vector<vector<int>> leansOn;
        vector<vector<int>> isLeanedOn;
        for (int i = 0; i < state.size(); i++) {
            leansOn.push_back({});
            isLeanedOn.push_back({});
        }

        for (int i = 0; i < state.size(); i++) {
            Block* b1 = state[i];
            for (int j = 0; j < i; j++) {
                Block* b2 = state[j];
                //check if b1 leans on b2
                if ((*b1).zPos() == (*b2).lastzPos() + 1 && overlapsIgnoringZ(b1, b2)) {
                    isLeanedOn[j].push_back(i);
                    leansOn[i].push_back(j);
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
        
        int answer = 0;
        for (int i = 0; i < state.size(); i++) {
            bool isSafe = true;
            for (int j : isLeanedOn[i]) {
                if (leansOn[j].size() == 1) {
                    isSafe = false;
                }
            }
            if (!isSafe) {
                //count chain reactions caused by deleting i
                int wouldCause = 0;
                vector<bool> hasFallen(state.size(), false);
                queue<int> toAdd;
                toAdd.push(i);
                hasFallen[i] = true;

                while (!toAdd.empty()) {
                    int c = toAdd.front();
                    toAdd.pop();

                    for (int nex : isLeanedOn[c]) {
                        bool predsHaveFallen = true;
                        for (int pred : leansOn[nex]) {
                            predsHaveFallen = predsHaveFallen && hasFallen[pred];
                        }
                        if (!hasFallen[nex] && predsHaveFallen) {
                            hasFallen[nex] = true;
                            wouldCause++;
                            toAdd.push(nex);
                        }

                    }
                                        
                }
                //cout << "disintegrating " << i << " would case to fall: " << wouldCause << endl;

                answer += wouldCause;
            }
        }

        return answer;
    }

    void printState() {
        for (Block* block : state) {
            for (vector<int> v : (*block).space) {
            printf("(%d, %d, %d), ", v[0], v[1], v[2]);

            }
            cout << endl;

        }
    }

};

int part1(Field* field) {
    //(*field).printState();
    (*field).applyGravity();
    //(*field).printState();
    return (*field).countDisintegrable();
}

int part2(Field* field) {
    //(*field).printState();
    (*field).applyGravity();
    //(*field).printState();
    return (*field).countChainReactions();}

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