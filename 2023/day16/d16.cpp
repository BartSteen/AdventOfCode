#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define filename "input.txt"


const vector<int> vup = {-1, 0};
const vector<int> vdown = {1,0};
const vector<int> vleft = {0,-1};
const vector<int> vright = {0,1};

bool posContainsDir(vector<vector<int>> &vec, vector<int> &test) {
    for (vector<int> v : vec) {
        if (v == test) {
            return true;
        }
    }
    return false;
}

int simulate(vector<string> &input, vector<vector<int>> start) {
    int height = input.size();
    int width = input[0].length();

    bool energised[height][width];
    vector<vector<int>> visited[height][width]; //visited[i][j] contains the direction vectors with which point (i,j) was visited

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            energised[i][j] = false;
        }
    }

    queue<vector<vector<int>>> q; //queue will contain 2-element vectors noting {{x,y}, {dira, dirb}} where (x,y) is pos and (dira, dirb) is direction vector

    q.push(start);

    while (!q.empty()) {
        vector<int> pos = q.front()[0];
        vector<int> dir = q.front()[1];
        q.pop();
        if (pos[0] < 0 || pos[0] >= height || pos[1] < 0 || pos[1] >= width) {
            continue;
        }
        if (posContainsDir(visited[pos[0]][pos[1]], dir)) {
            continue;
        }

      //  printf("(%d, %d) in direction (%d, %d)\n", pos[0], pos[1], dir[0], dir[1]);

        visited[pos[0]][pos[1]].push_back(dir);
        energised[pos[0]][pos[1]] = true;

        vector<int> newPos;

        if (input[pos[0]][pos[1]] == '.') {
            newPos = {pos[0] + dir[0], pos[1] + dir[1]};
        } else if (input[pos[0]][pos[1]] == '/') {
            
            if (dir == vup) {
                newPos = {pos[0], pos[1] + 1};
            } else if (dir == vright) {
                newPos = {pos[0] - 1, pos[1]};
            } else if (dir == vdown) {
                newPos = {pos[0], pos[1] - 1};
            } else {
                //dir == left
                newPos = {pos[0] + 1, pos[1]};
            }


        } else if (input[pos[0]][pos[1]] == '\\') {

             if (dir == vup) {
                newPos = {pos[0], pos[1] - 1};
            } else if (dir == vright) {
                newPos = {pos[0] + 1, pos[1]};
            } else if (dir == vdown) {
                newPos = {pos[0], pos[1] + 1};
            } else {
                //dir == left
                newPos = {pos[0] - 1, pos[1]};
            }

        } else if (input[pos[0]][pos[1]] == '|') {

            if (dir == vup || dir == vdown) {
                newPos = {pos[0] + dir[0], pos[1] + dir[1]};
            } else {
                //dir == right or left
                //need to go in two directions now (up and down)
                //do one through newPos (up) and one through hand (down)
                newPos = {pos[0] - 1, pos[1]};
                q.push({{pos[0] + 1, pos[1]}, vdown});
            }


        } else if (input[pos[0]][pos[1]] == '-') {

            if (dir == vleft || dir == vright) {
                newPos = {pos[0] + dir[0], pos[1] + dir[1]};
            } else {
                // dir == down or up
                //need to go in two directions now (left and right)
                //do one through newPos (left) and one through hand (right)
                newPos = {pos[0], pos[1] - 1};
                q.push({{pos[0], pos[1]+1}, vright});
            }

        }


        vector<int> newDir = {newPos[0] - pos[0], newPos[1] - pos[1]};
        q.push({newPos, newDir});
    }

    int result = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (energised[i][j]) {
                ++result;
               // cout << "#";
            } else {
              //  cout << ".";
            }
            // if (input[i][j] != '.') {
            //     cout << input[i][j];
            // } else {
            //     if (visited[i][j].size() == 0) {
            //         cout << '.';
            //     } else {
            //         if (visited[i][j][0] == vup) {
            //             cout << '^';
            //         } else if (visited[i][j][0] == vleft) {
            //             cout << '<';
            //         } else if (visited[i][j][0] == vright) {
            //             cout << '>';
            //         } else if (visited[i][j][0] == vdown) {
            //             cout << 'V';
            //         }
            //     }

            // }
        }
       // cout << endl;
    }

    return result;
}

int part1(vector<string> &input) {
    return simulate(input, {{0,0}, vright});
}

int part2(vector<string> &input) {
    int maxv = 0;
    int height = input.size();
    int width = input[0].length();
    for (int i = 0; i < height; i++) {
        int cs = simulate(input, {{i,0}, vright});
        //printf("(%d, %d) dir > scores %d\n", i, 0, cs);
        maxv = max(maxv, cs);
        //maxv = max(maxv, simulate(input, {{i,0}, vright}));
        maxv = max(maxv, simulate(input, {{i, width-1}, vleft}));
    }

    for (int j = 0; j < width; j++) {
        maxv = max(maxv, simulate(input, {{0,j}, vdown}));
        maxv = max(maxv, simulate(input, {{height-1, j}, vup}));
    }

    return maxv;
}

int main() {

    ifstream myfile(filename);
    string line;

    vector<string> input;

    while (getline(myfile, line)) {
        input.push_back(line);
    }   


    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;


    return -1;
}