#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;
#define filename "input.txt"
#define dr 0
#define dd 1
#define dl 2
#define du 3

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

int dirToInt(string c) {
    if (c == "R") {
        return dr;
    }
    if (c == "D") {
        return dd;
    }
    if (c == "L") {
        return dl;
    }
    if (c == "U") {
        return du;
    }
    return -1;
}

bool isValidPos(int y, int x, int width, int height) {
    return 0 <= y && y < height && 0 <= x && x < width;
}

vector<int> findBoundingBox(vector<vector<int>> &input) {
    int maxx = 0;
    int maxy = 0;
    int minx = 0;
    int miny = 0;

    int curx = 0;
    int cury = 0;
    for (vector<int> v : input) {
        if (v[0] == du) {
            cury -= v[1];
        } else if (v[0] == dd) {
            cury += v[1];
        } else if (v[0] == dl) {
            curx -= v[1];
        } else if (v[0] == dr) {
            curx += v[1];
        }
        minx = min(minx, curx);
        miny = min(miny, cury);
        maxx = max(maxx, curx);
        maxy = max(maxy, cury);
    }

    return {minx, miny, maxx, maxy};
}

vector<vector<bool>> simulateWalk(vector<vector<int>> &input) {
    vector<int> bb = findBoundingBox(input);
    int curx = -bb[0];
    int cury = -bb[1];
    int height = 1 + bb[3] - bb[1];
    int width = 1 + bb[2] - bb[0];

    vector<vector<bool>> field;
    for (int i = 0; i < height; i++) {
        vector<bool> t;
        for (int j = 0; j < width; j++) {
            t.push_back(false);
        }
        field.push_back(t);
    }
    field[cury][curx] = true;
    for (vector<int> v : input) {
        for (int i = 1; i <= v[1]; i++) {
            if (v[0] == du) {
                cury -= 1;
            } else if (v[0] == dd) {
                cury += 1;
            } else if (v[0] == dl) {
                curx -= 1;
            } else if (v[0] == dr) {
                curx += 1;
            }
            field[cury][curx] = true;
        }
    }

    return field;
}


int computeArea(vector<vector<bool>> field) {
    int area = 0;
    int width = field[0].size();
    int height = field.size();

    vector<vector<bool>> outside;
    for (int i = 0; i < height; i++) {
        vector<bool> t;
        for (int j = 0; j < width; j++) {
            t.push_back(false);
        }
        outside.push_back(t);
    }

    for (int i = 0; i < height; i++) {
        if (!field[i][0] && !outside[i][0]) {
            queue<vector<int>> q;
            q.push({i,0});
            while (!q.empty()) {
                vector<int> t = q.front();
                q.pop();
                
                if (isValidPos(t[0]-1, t[1], width, height)) {
                    if (!field[t[0]-1][t[1]] && !outside[t[0]-1][t[1]]) {
                        outside[t[0]-1][t[1]] = true;
                        q.push({t[0]-1, t[1]});
                    }
                }
                if (isValidPos(t[0]+1, t[1], width, height)) {
                    if (!field[t[0]+1][t[1]] && !outside[t[0]+1][t[1]]) {
                        outside[t[0]+1][t[1]] = true;
                        q.push({t[0]+1, t[1]});
                    }
                }
                if (isValidPos(t[0], t[1]-1, width, height)) {
                    if (!field[t[0]][t[1]-1] && !outside[t[0]][t[1]-1]) {
                        outside[t[0]][t[1]-1] = true;
                        q.push({t[0], t[1]-1});
                    }
                }
                if (isValidPos(t[0], t[1]+1, width, height)) {
                    if (!field[t[0]][t[1]+1] && !outside[t[0]][t[1]+1]) {
                        outside[t[0]][t[1]+1] = true;
                        q.push({t[0], t[1]+1});
                    }
                }
            }
        }

        if (!field[i][width-1] && !outside[i][width-1]) {
            queue<vector<int>> q;
            q.push({i,width-1});
            while (!q.empty()) {
                vector<int> t = q.front();
                q.pop();
                
                if (isValidPos(t[0]-1, t[1], width, height)) {
                    if (!field[t[0]-1][t[1]] && !outside[t[0]-1][t[1]]) {
                        outside[t[0]-1][t[1]] = true;
                        q.push({t[0]-1, t[1]});
                    }
                }
                if (isValidPos(t[0]+1, t[1], width, height)) {
                    if (!field[t[0]+1][t[1]] && !outside[t[0]+1][t[1]]) {
                        outside[t[0]+1][t[1]] = true;
                        q.push({t[0]+1, t[1]});
                    }
                }
                if (isValidPos(t[0], t[1]-1, width, height)) {
                    if (!field[t[0]][t[1]-1] && !outside[t[0]][t[1]-1]) {
                        outside[t[0]][t[1]-1] = true;
                        q.push({t[0], t[1]-1});
                    }
                }
                if (isValidPos(t[0], t[1]+1, width, height)) {
                    if (!field[t[0]][t[1]+1] && !outside[t[0]][t[1]+1]) {
                        outside[t[0]][t[1]+1] = true;
                        q.push({t[0], t[1]+1});
                    }
                }
            }
        }
    }

    for (int j = 0; j < width; j++) {
        if (!field[0][j] && !outside[0][j]) {
            queue<vector<int>> q;
            q.push({0,j});
            while (!q.empty()) {
                vector<int> t = q.front();
                q.pop();
                
                if (isValidPos(t[0]-1, t[1], width, height)) {
                    if (!field[t[0]-1][t[1]] && !outside[t[0]-1][t[1]]) {
                        outside[t[0]-1][t[1]] = true;
                        q.push({t[0]-1, t[1]});
                    }
                }
                if (isValidPos(t[0]+1, t[1], width, height)) {
                    if (!field[t[0]+1][t[1]] && !outside[t[0]+1][t[1]]) {
                        outside[t[0]+1][t[1]] = true;
                        q.push({t[0]+1, t[1]});
                    }
                }
                if (isValidPos(t[0], t[1]-1, width, height)) {
                    if (!field[t[0]][t[1]-1] && !outside[t[0]][t[1]-1]) {
                        outside[t[0]][t[1]-1] = true;
                        q.push({t[0], t[1]-1});
                    }
                }
                if (isValidPos(t[0], t[1]+1, width, height)) {
                    if (!field[t[0]][t[1]+1] && !outside[t[0]][t[1]+1]) {
                        outside[t[0]][t[1]+1] = true;
                        q.push({t[0], t[1]+1});
                    }
                }
            }
        }

        if (!field[height-1][j] && !outside[height-1][j]) {
            queue<vector<int>> q;
            q.push({height-1,j});
            while (!q.empty()) {
                vector<int> t = q.front();
                q.pop();
                
                if (isValidPos(t[0]-1, t[1], width, height)) {
                    if (!field[t[0]-1][t[1]] && !outside[t[0]-1][t[1]]) {
                        outside[t[0]-1][t[1]] = true;
                        q.push({t[0]-1, t[1]});
                    }
                }
                if (isValidPos(t[0]+1, t[1], width, height)) {
                    if (!field[t[0]+1][t[1]] && !outside[t[0]+1][t[1]]) {
                        outside[t[0]+1][t[1]] = true;
                        q.push({t[0]+1, t[1]});
                    }
                }
                if (isValidPos(t[0], t[1]-1, width, height)) {
                    if (!field[t[0]][t[1]-1] && !outside[t[0]][t[1]-1]) {
                        outside[t[0]][t[1]-1] = true;
                        q.push({t[0], t[1]-1});
                    }
                }
                if (isValidPos(t[0], t[1]+1, width, height)) {
                    if (!field[t[0]][t[1]+1] && !outside[t[0]][t[1]+1]) {
                        outside[t[0]][t[1]+1] = true;
                        q.push({t[0], t[1]+1});
                    }
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!outside[i][j]) {
                area++;
            }
        }
    }

    return area;
}

int part1(vector<vector<int>> &input) {
    vector<vector<bool>> field = simulateWalk(input);

    return computeArea(field);
}

vector<vector<long long>> findCoordinates(vector<vector<long long>> &input) {
    vector<vector<long long>> coords;
    long long curx = 0;
    long long cury = 0;

    for (vector<long long> v : input) {
        coords.push_back({curx, cury});
        if (v[0] == du) {
            cury -= v[1];
        } else if (v[0] == dd) {
            cury += v[1];
        } else if (v[0] == dl) {
            curx -= v[1];
        } else if (v[0] == dr) {
            curx += v[1];
        }
    }


    return coords;
}

long long shoelaceArea(vector<vector<long long>> &coords) {


    long long answer = 0;
    for (int i = 0; i < coords.size(); i++) {
        int nei = (i+1) % coords.size();

        answer += (coords[i][0] * coords[nei][1]) - (coords[nei][0] * coords[i][1]);
    }

    return answer / 2;
}

long long findBoundaryLength(vector<vector<long long>> &input) {
    long long boundary = 0;
    for (vector<long long> v : input) {
        boundary += v[1];
    }
    return boundary;
}


long long part2(vector<vector<long long>> &input) {
    vector<vector<long long>> coords = findCoordinates(input);
    //reverse(coords.begin(), coords.end());
    return shoelaceArea(coords) + findBoundaryLength(input) / 2 + 1;
}

int main() {

    ifstream myfile(filename);
    string line;

    vector<vector<int>> input;
    vector<vector<long long>> input2;
    vector<vector<long long>> input3;


    while (getline(myfile, line)) {
        vector<string> spl = split(line, ' ');
        input.push_back({dirToInt(spl[0]), stoi(spl[1])});
        input3.push_back({(long long) input[input.size()-1][0], (long long) input[input.size()-1][1]});

        string code = spl[2];
        string dis = code.substr(2, 5);
        char dir = code[7];
        long long hexc;


        input2.push_back({(long long) (dir - '0'), stoll(dis, 0, 16)});
    }

    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input2) << endl;

    // for (vector<long long> v : input2) {
    //     cout << v[0] << " - " << v[1] << endl;
    // }

    return -1;
}