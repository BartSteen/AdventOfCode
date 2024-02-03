#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define filename "input.txt"

#define path '.'
#define forest '#'
#define slopeleft '<'
#define slopeup '^'
#define slopedown 'v'
#define sloperight '>'

bool isValidCord(int i, int j, vector<string> &input) {
    return 0 <= i && i < input.size() && 0 <= j && j < input[i].size();
}

char neededSlope(int fromi, int fromj, int toi, int toj) {
    if (fromi < toi) {
        return slopedown;
    }
    if (fromi > toi) {
        return slopeup;
    }
    if (fromj < toj) {
        return sloperight;
    }
    if (fromj > toj) {
        return slopeleft;
    }
    return path;
}

bool canMoveFromTo(int fromi, int fromj, int toi, int toj, vector<string> &input) {
    if (!isValidCord(fromi, fromj, input) || !isValidCord(toi, toj, input)) {
        return false;
    }
    if (abs(toi - fromi) + abs(toj - fromj) != 1) {
        return false;
    }
    if (input[toi][toj] == forest) {
        return false;
    }

    char slope = neededSlope(fromi, fromj, toi, toj);
    return input[fromi][fromj] == path || input[fromi][fromj] == slope;
}

int part1(vector<string> &input) {
    int startj = 0;
    int endj = 0;
    int height = input.size();
    int width = input[0].size();
    for (int i = 0; i < width; i++) {
        if (input[0][i] == path) {
            startj = i;
        }
        if (input[height-1][i] == path) {
            endj = i;
        }
    }
    

    vector<vector<int>> pathLength;
    for (int i = 0; i < height; i++) {
        vector<int> t(width, -2);
        pathLength.push_back(t);
    }

    queue<vector<int>> q; //vector is (i,j)
    q.push({height-1, endj});
    pathLength[height-1][endj] = 0;

    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        int curd = pathLength[cur[0]][cur[1]];
        
        //up
        if (canMoveFromTo(cur[0]-1, cur[1], cur[0], cur[1], input)) {
            if (curd > pathLength[cur[0]-1][cur[1]] + 1) {
                pathLength[cur[0]-1][cur[1]] = curd + 1;
                q.push({cur[0]-1, cur[1]});
            }
        }   
        //down
        if (canMoveFromTo(cur[0]+1, cur[1], cur[0], cur[1], input)) {
            if (curd > pathLength[cur[0]+1][cur[1]] + 1) {
                pathLength[cur[0]+1][cur[1]] = curd + 1;
                q.push({cur[0]+1, cur[1]});
            }
        }
        //left
        if (canMoveFromTo(cur[0], cur[1]-1, cur[0], cur[1], input)) {
            if (curd > pathLength[cur[0]][cur[1]-1] + 1) {
                pathLength[cur[0]][cur[1]-1] = curd + 1;
                q.push({cur[0], cur[1]-1});
            }
        }
        //right
        if (canMoveFromTo(cur[0], cur[1]+1, cur[0], cur[1], input)) {
            if (curd > pathLength[cur[0]][cur[1]+1] + 1) {
                pathLength[cur[0]][cur[1]+1] = curd + 1;
                q.push({cur[0], cur[1]+1});
            }
        }
    }

    return pathLength[0][startj];
}

bool isKruising(int i, int j, vector<string> &input) {
    if (!isValidCord(i,j,input) || input[i][j] == forest) {
        return false;
    }
    int paths = 0;
    if (isValidCord(i-1,j,input) && input[i-1][j] != forest) {
        paths++;
    }
    if (isValidCord(i+1,j,input) && input[i+1][j] != forest) {
        paths++;
    }
    if (isValidCord(i,j-1,input) && input[i][j-1] != forest) {
        paths++;
    }
    if (isValidCord(i,j+1,input) && input[i][j+1] != forest) {
        paths++;
    }
    return paths > 2;
}

vector<vector<int>> findPotentialNext(int i, int j, vector<string> &input, vector<vector<bool>> &visited) {
    vector<vector<int>> next;
    if (isValidCord(i-1, j, input) && !visited[i-1][j] && input[i-1][j] != forest) {
        next.push_back({i-1,j});
    }
    if (isValidCord(i+1, j, input) && !visited[i+1][j] && input[i+1][j] != forest) {
        next.push_back({i+1,j});
    }
    if (isValidCord(i, j-1, input) && !visited[i][j-1] && input[i][j-1] != forest) {
        next.push_back({i,j-1});
    }
    if (isValidCord(i, j+1, input) && !visited[i][j+1] && input[i][j+1] != forest) {
        next.push_back({i,j+1});
    }
    return next;
}

int dfs(int i, int j, int d, vector<string> &input, vector<vector<bool>> &visited) {
    if (i == input.size() - 1) {
        //we are at bottom row so supposedly target, return max dis found
        return d;
    }
    //we are not at target yet
    vector<vector<int>> nexts = findPotentialNext(i, j, input, visited);
    int longestd = -1;
    visited[i][j] = true;
    for (int k = 0; k < nexts.size(); k++) {
        longestd = max(longestd, dfs(nexts[k][0], nexts[k][1], d+1, input, visited));
    }
    visited[i][j] = false;
    return longestd;
}

int part2(vector<string> &input) {
    int startj = 0;
    int endj = 0;
    int height = input.size();
    int width = input[0].size();
    for (int i = 0; i < width; i++) {
        if (input[0][i] == path) {
            startj = i;
        }
        if (input[height-1][i] == path) {
            endj = i;
        }
    }

    //do dfs like searching from (0, startj) with brute forcing which way we take 
    vector<vector<bool>> visited;
    for (int i = 0; i < height; i++){
        vector<bool> t(width, false);
        visited.push_back(t);
    }
    return dfs(0, startj, 0, input, visited);
}

struct Graph {
    //vector<int> vertices;
    vector<vector<pair<int, int>>> neighbours; //adjacency list with first element of pair vertex id and second weight
    int n;

    Graph(vector<vector<pair<int, int>>> nb) {
        neighbours = nb;
        n = nb.size();
    }

    int dfs(int curv, int cd, int target, vector<bool> &visited) {
        if (curv == target) {
            return cd;
        }
        //we are not at target yet
        int longestd = -1;
        visited[curv] = true;
        for (int k = 0; k < neighbours[curv].size(); k++) {
            if (!visited[neighbours[curv][k].first]) {
                longestd = max(longestd, dfs(neighbours[curv][k].first, cd+neighbours[curv][k].second, target, visited));
            }
        }
        visited[curv] = false;
        return longestd;
    }

    int maxDistance(int source, int target) {
        vector<bool> visited(n, false);
        return dfs(source, 0, target, visited);
    }
};

bool isKnoop(int i, int j, vector<string> &input) {
    return isKruising(i,j, input) || i == 0 || i == input.size() - 1;

}

vector<vector<int>> findMovableNext(int i, int j, vector<string> &input) {
    vector<vector<int>> next;
    if (isValidCord(i-1, j, input) && input[i-1][j] != forest) {
        next.push_back({i-1,j});
    }
    if (isValidCord(i+1, j, input) && input[i+1][j] != forest) {
        next.push_back({i+1,j});
    }
    if (isValidCord(i, j-1, input) && input[i][j-1] != forest) {
        next.push_back({i,j-1});
    }
    if (isValidCord(i, j+1, input) && input[i][j+1] != forest) {
        next.push_back({i,j+1});
    }
    return next;
}

vector<int> findKnoop(int ci, int cj, int fi, int fj, int cd, vector<string> &input) {
    //(ci, cj) is huidige loc, (fi,fj) is verboden loc om naar toe te gaan, cd is huidige afstand
    if (isKnoop(ci, cj, input)) {
        return {ci, cj, cd};
    }
    vector<vector<int>> next = findMovableNext(ci, cj, input);
    for (vector<int> v : next) {
        if (v[0] == fi && v[1] == fj) {
            continue;
        } else {
            return findKnoop(v[0], v[1], ci, cj, cd+1, input);
        }

    }
    return {};

}

vector<vector<int>> findEdges(int i, int j, vector<string> &input) {
    //should return vector with elements (a,b,c) where (a,b) is y,x of neighbour kruising and c is distance to it
    vector<vector<int>> res;
    vector<vector<int>> nexts = findMovableNext(i,j, input);

    for (vector<int> next : nexts) {
        vector<int> toAdd = findKnoop(next[0], next[1], i, j, 1, input);
        bool needToAdd = true;
        for (int k = 0; k < res.size(); k++) {
            if (res[k][0] == toAdd[0] && res[k][1] == toAdd[1]) {
                res[k][2] = max(res[k][2], toAdd[2]);
                needToAdd = false;
            }
        }
        if (needToAdd) {
            res.push_back(toAdd);
        }
    }

    return res;
}

int findIndex(vector<vector<int>> vec, vector<int> el) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == el) {
            return i;
        }
    }
    return -1;
}

Graph* buildGraph(vector<string> &input) {
   int startj = 0;
    int endj = 0;
    int height = input.size();
    int width = input[0].size();
    for (int i = 0; i < width; i++) {
        if (input[0][i] == path) {
            startj = i;
        }
        if (input[height-1][i] == path) {
            endj = i;
        }
    }

    vector<vector<int>> graphPoints;

    graphPoints.push_back({0, startj});
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (isKruising(i,j, input)) {
                graphPoints.push_back({i,j});
            }
        }
    }
    graphPoints.push_back({height-1,endj});


    //now do edges
    vector<vector<pair<int, int>>> neighbours;
    for (int k = 0; k < graphPoints.size(); k++) {
        vector<int> curPoint = graphPoints[k];

        vector<vector<int>> nb = findEdges(curPoint[0], curPoint[1], input); //return vector of triple (a, b, w) with (a,b) being neighbour point and w distance to it
        vector<pair<int, int>> cnb;
        for (vector<int> v : nb) {
            if (v.size() > 0) {
                cnb.push_back(pair(findIndex(graphPoints, {v[0], v[1]}), v[2]));
            }
        }
        neighbours.push_back(cnb);
    }

    return new Graph(neighbours);
}

int part2Graph(vector<string> &input) {
    Graph* g = buildGraph(input);
    int answer = (*g).maxDistance(0, (*g).n-1);
    delete g;
    return answer;
}


int main() {

    ifstream myfile(filename);
    string line;
    vector<string> input;
    while (getline(myfile, line)) {
        input.push_back(line);
    }

    cout << "Part 1: " << part1(input) << endl;
    //cout << "Part 2: " << part2(input) << endl;
    cout << "Part 2 Graph: " << part2Graph(input) << endl;
    return -1;
}