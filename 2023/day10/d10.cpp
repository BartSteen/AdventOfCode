#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define filename "input.txt"

vector<int> findStart(vector<string> input) {
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == 'S') {
                return {i,j};
            }
        }
    }
    return {0,0};
}

bool isValid(vector<int> newPos, vector<string> &input) {
    if (newPos[0] < 0 || newPos[1] < 0) {
        return false;
    }   
    if (newPos[0] >= input.size() || newPos[1] >= input[newPos[0]].size()) {
        return false;
    }
    return true;
}

vector<int> determineNextTrans(vector<int> curTrans, char pipe) {
    if (pipe == '.') {
        return {0,0};
    }
    if (pipe == '-') {
        if (curTrans[0] == 0) {
            return curTrans;
        }
        return {0,0};
    }
    if (pipe == '|') {
        if (curTrans[1] == 0) {
            return curTrans;
        }
        return {0,0};
    }
    if (pipe == 'F') {
        if (curTrans[0] == 0 && curTrans[1] == -1) {
            return {1,0};
        } 
        if (curTrans[0] == -1 && curTrans[1] == 0) {
            return {0,1};
        } 
        return {0,0};
    }

    if (pipe == '7') {
        if (curTrans[0] == 0 && curTrans[1] == 1) {
            return {1,0};
        } 
        if (curTrans[0] == -1 && curTrans[1] == 0) {
            return {0,-1};
        } 
        return {0,0};
    }

    if (pipe == 'J') {
        if (curTrans[0] == 0 && curTrans[1] == 1) {
            return {-1,0};
        } 
        if (curTrans[0] == 1 && curTrans[1] == 0) {
            return {0,-1};
        } 
        return {0,0};
    }

    if (pipe == 'L') {
        if (curTrans[0] == 0 && curTrans[1] == -1) {
            return {-1,0};
        } 
        if (curTrans[0] == 1 && curTrans[1] == 0) {
            return {0,1};
        } 
        return {0,0};
    }
    return {0,0};
}

int part1(vector<string> input) {
    vector<int> startLoc = findStart(input);

    bool visited[input.size()][input[0].size()]{};
    visited[startLoc[0]][startLoc[1]] = true;

    vector<vector<int>> starters = {{0,1}, {0,-1}, {1,0},{-1,0}};
    for (vector<int> nextTrans : starters) {
        //printf("Trying (%d, %d)\n", nextTrans[0], nextTrans[1]);
        vector<int> curPos = startLoc;
        int cycleLength = 0;
        while (true) {
            vector<int> newPos = {curPos[0] + nextTrans[0], curPos[1] + nextTrans[1]};
            //printf("(%d, %d) -> (%d, %d)\n", curPos[0], curPos[1], newPos[0], newPos[1]);
            if (!isValid(newPos, input)) {
                break;
            }
            if (newPos == startLoc) {
                return (cycleLength + 1) / 2;
            }
            if (visited[newPos[0]][newPos[1]]) {
                break;
            }
            //continue
            char curSymb = input[newPos[0]][newPos[1]];
            nextTrans = determineNextTrans(nextTrans, curSymb);
            if (nextTrans[0] == 0 && nextTrans[1] == 0) {
                break;
            }
            cycleLength++;
            curPos = newPos;
            visited[curPos[0]][curPos[1]] = true;

        }
    }

    return -1;
}

bool isContained(vector<vector<bool>> &visited, int x, int y) {
    bool hasVisited = false;
    for (int i = x-1; i >= 0; i--) {
        hasVisited = hasVisited || visited[i][y];
    }
    if (!hasVisited) {
        return false;
    }

    hasVisited = false;
    for (int i = x+1; i < visited.size(); i++) {
        hasVisited = hasVisited || visited[i][y];
    }
    if (!hasVisited) {
        return false;
    }

    hasVisited = false;
    for (int j = y-1; j >= 0; j--) {
        hasVisited = hasVisited || visited[x][j];
    }
    if (!hasVisited) {
        return false;
    }

    hasVisited = false;
    for (int j = y+1; j < visited[x].size(); j++) {
        hasVisited = hasVisited || visited[x][j];
    }
    return hasVisited;
}

int part2(vector<string> input) {
    vector<int> startLoc = findStart(input);

    vector<vector<bool>> visited;
    for (int i = 0; i < input.size(); i++) {
        vector<bool> t(input[i].size(), false);
        visited.push_back(t);
    }
    visited[startLoc[0]][startLoc[1]] = true;

    vector<vector<int>> starters = {{0,1}, {0,-1}, {1,0},{-1,0}};
    for (vector<int> nextTrans : starters) {
        //reset visited array
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[0].size(); j++) {
                visited[i][j] = false;
            }
        }
        visited[startLoc[0]][startLoc[1]] = true;
        

        //printf("Trying (%d, %d)\n", nextTrans[0], nextTrans[1]);
        vector<int> curPos = startLoc;
        int cycleLength = 0;
        while (true) {
            vector<int> newPos = {curPos[0] + nextTrans[0], curPos[1] + nextTrans[1]};
            //printf("(%d, %d) -> (%d, %d)\n", curPos[0], curPos[1], newPos[0], newPos[1]);
            if (!isValid(newPos, input)) {
                break;
            }
            if (newPos == startLoc) {
                //do checking
                cout << endl;
                for (int i = 0; i < input.size(); i++) {
                    for (int j = 0; j < input[i].size(); j++) {
                        if (visited[i][j]) {
                            cout << "X";
                        } else {
                            cout << ".";
                        }
                    }
                    cout << endl;
                }
                int total = 0;
                for (int i = 0; i < input.size(); i++) {
                    for (int j = 0; j < input[i].size(); j++) {
                        if (!visited[i][j]  && isContained(visited, i, j)) { //&& input[i][j] == '.'
                            printf("(%d, %d) is good\n", i,j);
                            total++;
                        }
                    }
                }                
                return total;
            }
            if (visited[newPos[0]][newPos[1]]) {
                break;
            }
            //continue
            char curSymb = input[newPos[0]][newPos[1]];
            nextTrans = determineNextTrans(nextTrans, curSymb);
            if (nextTrans[0] == 0 && nextTrans[1] == 0) {
                break;
            }
            cycleLength++;
            curPos = newPos;
            visited[curPos[0]][curPos[1]] = true;

        }
    }

    return -1;
}

int part2alt(vector<string> input) {
    vector<int> startLoc = findStart(input);

    vector<vector<bool>> visited;
    for (int i = 0; i < input.size(); i++) {
        vector<bool> t(input[i].size(), false);
        visited.push_back(t);
    }
    visited[startLoc[0]][startLoc[1]] = true;

    vector<vector<int>> starters = {{0,1}, {0,-1}, {1,0},{-1,0}};
    for (vector<int> nextTrans : starters) {
        //reset visited array
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[0].size(); j++) {
                visited[i][j] = false;
            }
        }
        visited[startLoc[0]][startLoc[1]] = true;
        

        //printf("Trying (%d, %d)\n", nextTrans[0], nextTrans[1]);
        vector<int> curPos = startLoc;
        int cycleLength = 0;
        while (true) {
            vector<int> newPos = {curPos[0] + nextTrans[0], curPos[1] + nextTrans[1]};
            //printf("(%d, %d) -> (%d, %d)\n", curPos[0], curPos[1], newPos[0], newPos[1]);
            if (!isValid(newPos, input)) {
                break;
            }
            if (newPos == startLoc) {
                //do checking
                // cout << endl;
                // for (int i = 0; i < input.size(); i++) {
                //     for (int j = 0; j < input[i].size(); j++) {
                //         if (visited[i][j]) {
                //             cout << "X";
                //         } else {
                //             cout << ".";
                //         }
                //     }
                //     cout << endl;
                // }
                long total = 0;
                //total -= cycleLength + 1;
                vector<vector<bool>> outside;
                for (int i = 0; i < input.size(); i++) {
                    vector<bool> t(input[i].size(), false);
                    outside.push_back(t);
                }

                queue<vector<int>> q;
                for (int i = 0; i < input.size(); i++) {
                    if (!visited[i][0] && !outside[i][0]) {
                        //total--;
                        outside[i][0] = true;
                        q.push({i,0});
                    }
                    //cout << "BOber" << endl;
                    if (!visited[i][visited[i].size() - 1] && !outside[i][outside[i].size()-1]) {
                        //total--;
                        outside[i][outside[i].size() - 1] = true;
                        q.push({i,(int) visited[i].size() - 1});
                    }
                }
                for (int j = 0; j < input[0].size(); j++) {
                    // if (!visited[0][j] || !outside[0][j]) {
                    //     total--;
                    //     outside[0][j] = true;
                    //     q.push({0,j});
                    // }
                    if (!visited[visited.size()-1][j] && !outside[visited.size()-1][j]) {
                        //total--;
                        outside[visited.size()-1][j] = true;
                        q.push({(int) visited.size()-1, j});
                    }
                }
                while (!q.empty()) {
                    vector<int> cur = q.front();
                    q.pop();
                    for (vector<int> disp : starters) {
                        vector<int> nc = {cur[0] + disp[0], cur[1] + disp[1]};
                        if (!isValid(nc, input)) {
                            continue;
                        }
                        if (!visited[nc[0]][nc[1]] && !outside[nc[0]][nc[1]]) {
                            outside[nc[0]][nc[1]] = true;
                            q.push(nc);
                            //total--;
                        }
                    }
                }    
                cout << endl;
                for (int i = 0; i < input.size(); i++) {
                    for (int j = 0; j < input[i].size(); j++) {
                        if (visited[i][j]) {
                            cout << "X";
                        } else {
                            cout << ".";
                        }
                    }
                    cout << endl;
                }
                cout << endl;
                for (int i = 0; i < input.size(); i++) {
                    for (int j = 0; j < input[i].size(); j++) {
                        if (outside[i][j]) {
                            cout << "X";
                        } else {
                            cout << ".";
                        }
                    }
                    cout << endl;
                }
                                    cout << endl;

                for (int i = 0; i < input.size(); i++) {
                    for (int j = 0; j < input[i].size(); j++) {
                        if (!outside[i][j] && !visited[i][j]) {
                            total++;
                            cout << "X";
                        } else {
                            cout << ".";
                        }
                    }
                    cout << endl;
                }
                                    cout << endl;

                return total;
            }
            if (visited[newPos[0]][newPos[1]]) {
                break;
            }
            //continue
            char curSymb = input[newPos[0]][newPos[1]];
            nextTrans = determineNextTrans(nextTrans, curSymb);
            if (nextTrans[0] == 0 && nextTrans[1] == 0) {
                break;
            }
            cycleLength++;
            curPos = newPos;
            visited[curPos[0]][curPos[1]] = true;

        }
    }

    return -1;
}

vector<vector<int>> findCoords(vector<string> &input) {
    vector<int> startLoc = findStart(input);

    bool visited[input.size()][input[0].size()]{};
    visited[startLoc[0]][startLoc[1]] = true;

    vector<vector<int>> starters = {{0,1}, {0,-1}, {1,0},{-1,0}};
    for (vector<int> nextTrans : starters) {
        vector<int> curPos = startLoc;
        int cycleLength = 0;
        vector<vector<int>> coords = {startLoc};
        while (true) {
            vector<int> newPos = {curPos[0] + nextTrans[0], curPos[1] + nextTrans[1]};
            //printf("(%d, %d) -> (%d, %d)\n", curPos[0], curPos[1], newPos[0], newPos[1]);
            if (!isValid(newPos, input)) {
                break;
            }
            if (newPos == startLoc) {
                //return (cycleLength + 1) / 2;
                return coords;
            }
            if (visited[newPos[0]][newPos[1]]) {
                break;
            }
            //continue
            char curSymb = input[newPos[0]][newPos[1]];
            if (curSymb != '|' && curSymb != '-') {
                coords.push_back({curPos[0], curPos[1]});
            }
            nextTrans = determineNextTrans(nextTrans, curSymb);
            if (nextTrans[0] == 0 && nextTrans[1] == 0) {
                break;
            }
            cycleLength++;
            curPos = newPos;
            visited[curPos[0]][curPos[1]] = true;

        }
    }

    return {};
}

int shoelaceArea(vector<vector<int>> &coords) {

    int answer = 0;
    for (int i = 0; i < coords.size(); i++) {
        int nei = (i+1) % coords.size();
        answer += (coords[i][1] * coords[nei][0]) - (coords[nei][1] * coords[i][0]);
    }

    return answer / 2;
}

int part2Her(vector<string> &input) {
    vector<vector<int>> coords = findCoords(input);

    return abs(shoelaceArea(coords));
}

int part2Doh(vector<string> &input) {
    vector<int> startLoc = findStart(input);

    bool visited[input.size()][input[0].size()]{};
    visited[startLoc[0]][startLoc[1]] = true;

    vector<vector<int>> starters = {{0,1}, {0,-1}, {1,0},{-1,0}};
    for (vector<int> nextTrans : starters) {
        vector<int> curPos = startLoc;
        int cycleLength = 0;
        vector<vector<int>> coords = {startLoc};
        while (true) {
            vector<int> newPos = {curPos[0] + nextTrans[0], curPos[1] + nextTrans[1]};
            //printf("(%d, %d) -> (%d, %d)\n", curPos[0], curPos[1], newPos[0], newPos[1]);
            if (!isValid(newPos, input)) {
                break;
            }
            if (newPos == startLoc) {
                //return (cycleLength + 1) / 2;

                //print coords
                // for (vector<int> c : coords) {
                //     printf("(%d, %d)\n", c[0], c[1]);
                // }

                return abs(shoelaceArea(coords)) - cycleLength / 2;
            }
            if (visited[newPos[0]][newPos[1]]) {
                break;
            }
            //continue
            char curSymb = input[newPos[0]][newPos[1]];
            if (curSymb != '|' && curSymb != '-') {
                coords.push_back({newPos[0], newPos[1]});
            }
            nextTrans = determineNextTrans(nextTrans, curSymb);
            if (nextTrans[0] == 0 && nextTrans[1] == 0) {
                break;
            }
            cycleLength++;
            curPos = newPos;
            visited[curPos[0]][curPos[1]] = true;

        }
    }

    return {};
}

int main() {
    vector<string> input;
    string line;
    ifstream myfile(filename);

    while (getline(myfile, line)) {
        input.push_back(line);
    }

    cout << "Part 1: " << part1(input) <<endl;
    //cout << "Part 1: " << part1(hands, bids) <<endl;
    //cout << "Part 2: " << part2(input) <<endl;

    cout << "Part 2 Doh: " << part2Doh(input) <<endl;
    return -1;
}