#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define filename "input.txt"
#define ileft 0
#define iup 1
#define iright 2
#define idown 3

class Compare
{
    public:
    bool operator() (vector<int> a, vector<int> b) {
        return a[0] >= b[0];
    }
};

bool isValidCord(int i, int j, int height, int width) {
    return 0 <= i && i < height && 0 <= j && j < width;
}

int part1(vector<vector<int>> &input) {

    //we doen dijkstra op 4 kopiën van de 'graaf', eentje waar elke richting verboden is
    int height = input.size();
    int width = input[0].size();

    int left[height][width];
    int right[height][width];
    int up[height][width];
    int down[height][width];

    vector<vector<bool>> visleft;
    vector<vector<bool>> visright;
    vector<vector<bool>> visup;
    vector<vector<bool>> visdown;

    vector<vector<vector<vector<int>>>> pred;

    for (int i = 0; i < height; i++) {
        vector<bool> tl;
        vector<bool> tr;
        vector<bool> tu;
        vector<bool> td;

        vector<vector<vector<int>>> tpred;
        for (int j = 0; j < width; j++) {
            left[i][j] = -1;
            right[i][j] = -1;
            up[i][j] = -1;
            down[i][j] = -1;
            

            tl.push_back(false);
            tr.push_back(false);
            tu.push_back(false);
            td.push_back(false);

            tpred.push_back({{-1,-1, -1},{-1,-1, -1},{-1,-1, -1},{-1,-1, -1}});
        }
        visleft.push_back(tl);
        visright.push_back(tr);
        visdown.push_back(td);
        visup.push_back(tu);

        pred.push_back(tpred);
    }
    left[0][0] = 0;
    right[0][0] = 0;
    up[0][0] = 0;
    down[0][0] = 0;

    // visleft[0][0] = true;
    // visright[0][0] = true;
    // visup[0][0] = true;
    // visdown[0][0] = true;
    priority_queue<vector<int>, vector<vector<int>>, Compare> pq; 
    //elements of pq are vectors with first index being distance, second direction, third and fourth being i and j (height and width)


    pq.push({0, ileft, 0, 0, 0, 0, ileft});
    pq.push({0, iup, 0, 0, 0, 0, iup});


    while (!pq.empty()) {
        vector<int> cur = pq.top();
        int d = cur[0];
        int dir = cur[1];
        int h = cur[2];
        int w = cur[3];
        pq.pop();


        //extra
        int prevh = cur[4];
        int prevw = cur[5];
        int prevdir = cur[6];

        // if (dir == ileft && left[h][w] != -1 && left[h][w] < d) {
        //     continue;
        // }
        // if (dir == iup && up[h][w] != -1 && up[h][w] < d) {
        //     continue;
        // }
        // if (dir == iright && right[h][w] != -1 && right[h][w] < d) {
        //     continue;
        // }
        // if (dir == idown && down[h][w] != -1 && down[h][w] < d) {
        //     continue;
        // }

        if (dir == ileft && visleft[h][w]) {
            continue;
        }
        if (dir == iup && visup[h][w]) {
            continue;
        }
        if (dir == iright && visright[h][w]) {
            continue;
        }
        if (dir == idown && visdown[h][w]) {
            continue;
        }

        pred[h][w][dir][0] = prevh;
        pred[h][w][dir][1] = prevw;
        pred[h][w][dir][2] = prevdir;
        //printf("Now processing (%d, %d, %d, %d, %d, %d)\n", d, dir, h, w, prevh, prevw);


        //process it
        if (dir == ileft) {
            visleft[h][w] = true;
            //cannot go left
            left[h][w] = d;
            int cdu = d;
            int cdd = d;
            for (int i = 1; i <= 3; i++) {
                if (isValidCord(h-i, w, height, width)) {
                    cdu += input[h-i][w];
                    if (!visup[h-i][w]) {
                        pq.push({cdu, iup, h-i, w, h, w, dir});
                    }
                }
                if (isValidCord(h+i, w, height, width)) {
                    cdd += input[h+i][w];
                    if (!visdown[h+i][w]) {
                        pq.push({cdd, idown, h+i, w, h, w, dir});
                    }
                }
            }

        } else if (dir == iright) {
            visright[h][w] = true;
            right[h][w] = d;
            int cdu = d;
            int cdd = d;
            for (int i = 1; i <= 3; i++) {
                if (isValidCord(h-i, w, height, width)) {
                    cdu += input[h-i][w];
                    if (!visup[h-i][w]) {
                        pq.push({cdu, iup, h-i, w, h, w, dir});
                    }
                }
                if (isValidCord(h+i, w, height, width)) {
                    cdd += input[h+i][w];
                    if (!visdown[h+i][w]) {
                        pq.push({cdd, idown, h+i, w, h, w, dir});
                    }
                }
            }
        } else if (dir == iup) {
            visup[h][w] = true;
            up[h][w] = d;
            int cdr = d;
            int cdl = d;
            for (int i = 1; i <= 3; i++) {
                if (isValidCord(h, w+i, height, width)) {
                    cdr += input[h][w+i];
                    if (!visright[h][w+i]) {
                        pq.push({cdr, iright, h, w+i, h, w, dir});
                    }
                }
                if (isValidCord(h, w-i, height, width)) {
                    cdl += input[h][w-i];
                    if (!visleft[h][w-i]) {
                        pq.push({cdl, ileft, h, w-i, h, w, dir});
                    }
                }
            }
        } else if (dir == idown) {
            visdown[h][w] = true;
            down[h][w] = d;
            int cdr = d;
            int cdl = d;
            for (int i = 1; i <= 3; i++) {
                if (isValidCord(h, w+i, height, width)) {
                    cdr += input[h][w+i];
                    if (!visright[h][w+i]) {
                        pq.push({cdr, iright, h, w+i, h, w, dir});
                    }
                }
                if (isValidCord(h, w-i, height, width)) {
                    cdl += input[h][w-i];
                    if (!visleft[h][w-i]) {
                        pq.push({cdl, ileft, h, w-i, h, w, dir});
                    }
                }
            }
        }
    }

    //find answer
    int answer = left[height-1][width-1];
    if (right[height-1][width-1] != -1 && (answer == -1 || right[height-1][width-1] < answer)) {
        answer = right[height-1][width-1] ;
    }
    if (up[height-1][width-1] != -1 && (answer == -1 || up[height-1][width-1] < answer)) {
        answer = up[height-1][width-1] ;
    }
    if (down[height-1][width-1] != -1 && (answer == -1 || down[height-1][width-1] < answer)) {
        answer = down[height-1][width-1] ;
    }

    // cout << endl;
    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << left[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "-------------------------" << endl;

    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << right[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "-------------------------" << endl;

    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << up[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "-------------------------" << endl;

    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << down[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // int sdir = 0;
    // if (answer == down[height-1][width-1]) {
    //     sdir = idown;
    // } else {
    //     sdir = iright;
    // }

    // // int curh = pred[height-1][width-1][sdir][0];
    // // int curw = pred[height-1][width-1][sdir][1];
    // int curh = height-1;
    // int curw = width-1;
    
    // // printf(("(%d, %d) -> "), height-1, width-1);
    // while (curw != 0 || curh != 0) {
    //     printf("(%d, %d) -> ", curh, curw);
    //     int newh = pred[curh][curw][sdir][0];
    //     int neww = pred[curh][curw][sdir][1];
    //     sdir = pred[curh][curw][sdir][2];
    //     curh = newh;
    //     curw = neww;
    // }
    // cout << "(0, 0)\n";

    return answer;
}

int part2(vector<vector<int>> &input) {

    //we doen dijkstra op 4 kopiën van de 'graaf', eentje waar elke richting verboden is
    int height = input.size();
    int width = input[0].size();

    int left[height][width];
    int right[height][width];
    int up[height][width];
    int down[height][width];

    vector<vector<bool>> visleft;
    vector<vector<bool>> visright;
    vector<vector<bool>> visup;
    vector<vector<bool>> visdown;

    vector<vector<vector<vector<int>>>> pred;

    for (int i = 0; i < height; i++) {
        vector<bool> tl;
        vector<bool> tr;
        vector<bool> tu;
        vector<bool> td;

        vector<vector<vector<int>>> tpred;
        for (int j = 0; j < width; j++) {
            left[i][j] = -1;
            right[i][j] = -1;
            up[i][j] = -1;
            down[i][j] = -1;
            

            tl.push_back(false);
            tr.push_back(false);
            tu.push_back(false);
            td.push_back(false);

            tpred.push_back({{-1,-1, -1},{-1,-1, -1},{-1,-1, -1},{-1,-1, -1}});
        }
        visleft.push_back(tl);
        visright.push_back(tr);
        visdown.push_back(td);
        visup.push_back(tu);

        pred.push_back(tpred);
    }
    left[0][0] = 0;
    right[0][0] = 0;
    up[0][0] = 0;
    down[0][0] = 0;

    // visleft[0][0] = true;
    // visright[0][0] = true;
    // visup[0][0] = true;
    // visdown[0][0] = true;
    priority_queue<vector<int>, vector<vector<int>>, Compare> pq; 
    //elements of pq are vectors with first index being distance, second direction, third and fourth being i and j (height and width)


    pq.push({0, ileft, 0, 0, 0, 0, ileft});
    pq.push({0, iup, 0, 0, 0, 0, iup});


    while (!pq.empty()) {
        vector<int> cur = pq.top();
        int d = cur[0];
        int dir = cur[1];
        int h = cur[2];
        int w = cur[3];
        pq.pop();


        //extra
        int prevh = cur[4];
        int prevw = cur[5];
        int prevdir = cur[6];

        // if (dir == ileft && left[h][w] != -1 && left[h][w] < d) {
        //     continue;
        // }
        // if (dir == iup && up[h][w] != -1 && up[h][w] < d) {
        //     continue;
        // }
        // if (dir == iright && right[h][w] != -1 && right[h][w] < d) {
        //     continue;
        // }
        // if (dir == idown && down[h][w] != -1 && down[h][w] < d) {
        //     continue;
        // }

        if (dir == ileft && visleft[h][w]) {
            continue;
        }
        if (dir == iup && visup[h][w]) {
            continue;
        }
        if (dir == iright && visright[h][w]) {
            continue;
        }
        if (dir == idown && visdown[h][w]) {
            continue;
        }

        pred[h][w][dir][0] = prevh;
        pred[h][w][dir][1] = prevw;
        pred[h][w][dir][2] = prevdir;
        //printf("Now processing (%d, %d, %d, %d, %d, %d)\n", d, dir, h, w, prevh, prevw);


        //process it
        if (dir == ileft) {
            visleft[h][w] = true;
            //cannot go left
            left[h][w] = d;
            int cdu = d;
            int cdd = d;
            for (int i = 1; i <= 10; i++) {
                if (isValidCord(h-i, w, height, width)) {
                    cdu += input[h-i][w];
                    if (!visup[h-i][w] && i >= 4) {
                        pq.push({cdu, iup, h-i, w, h, w, dir});
                    }
                }
                if (isValidCord(h+i, w, height, width)) {
                    cdd += input[h+i][w];
                    if (!visdown[h+i][w] && i >= 4) {
                        pq.push({cdd, idown, h+i, w, h, w, dir});
                    }
                }
            }

        } else if (dir == iright) {
            visright[h][w] = true;
            right[h][w] = d;
            int cdu = d;
            int cdd = d;
            for (int i = 1; i <= 10; i++) {
                if (isValidCord(h-i, w, height, width)) {
                    cdu += input[h-i][w];
                    if (!visup[h-i][w] && i >= 4) {
                        pq.push({cdu, iup, h-i, w, h, w, dir});
                    }
                }
                if (isValidCord(h+i, w, height, width)) {
                    cdd += input[h+i][w];
                    if (!visdown[h+i][w] && i >= 4 ) {
                        pq.push({cdd, idown, h+i, w, h, w, dir});
                    }
                }
            }
        } else if (dir == iup) {
            visup[h][w] = true;
            up[h][w] = d;
            int cdr = d;
            int cdl = d;
            for (int i = 1; i <= 10; i++) {
                if (isValidCord(h, w+i, height, width)) {
                    cdr += input[h][w+i];
                    if (!visright[h][w+i] && i >= 4) {
                        pq.push({cdr, iright, h, w+i, h, w, dir});
                    }
                }
                if (isValidCord(h, w-i, height, width)) {
                    cdl += input[h][w-i];
                    if (!visleft[h][w-i] && i >= 4) {
                        pq.push({cdl, ileft, h, w-i, h, w, dir});
                    }
                }
            }
        } else if (dir == idown) {
            visdown[h][w] = true;
            down[h][w] = d;
            int cdr = d;
            int cdl = d;
            for (int i = 1; i <= 10; i++) {
                if (isValidCord(h, w+i, height, width)) {
                    cdr += input[h][w+i];
                    if (!visright[h][w+i] && i >= 4) {
                        pq.push({cdr, iright, h, w+i, h, w, dir});
                    }
                }
                if (isValidCord(h, w-i, height, width)) {
                    cdl += input[h][w-i];
                    if (!visleft[h][w-i] && i >= 4) {
                        pq.push({cdl, ileft, h, w-i, h, w, dir});
                    }
                }
            }
        }
    }

    //find answer
    int answer = left[height-1][width-1];
    if (right[height-1][width-1] != -1 && (answer == -1 || right[height-1][width-1] < answer)) {
        answer = right[height-1][width-1] ;
    }
    if (up[height-1][width-1] != -1 && (answer == -1 || up[height-1][width-1] < answer)) {
        answer = up[height-1][width-1] ;
    }
    if (down[height-1][width-1] != -1 && (answer == -1 || down[height-1][width-1] < answer)) {
        answer = down[height-1][width-1] ;
    }

    // cout << endl;
    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << left[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "-------------------------" << endl;

    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << right[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "-------------------------" << endl;

    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << up[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "-------------------------" << endl;

    // for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         cout << down[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // int sdir = 0;
    // if (answer == down[height-1][width-1]) {
    //     sdir = idown;
    // } else {
    //     sdir = iright;
    // }

    // // int curh = pred[height-1][width-1][sdir][0];
    // // int curw = pred[height-1][width-1][sdir][1];
    // int curh = height-1;
    // int curw = width-1;
    
    // // printf(("(%d, %d) -> "), height-1, width-1);
    // while (curw != 0 || curh != 0) {
    //     printf("(%d, %d) -> ", curh, curw);
    //     int newh = pred[curh][curw][sdir][0];
    //     int neww = pred[curh][curw][sdir][1];
    //     sdir = pred[curh][curw][sdir][2];
    //     curh = newh;
    //     curw = neww;
    // }
    // cout << "(0, 0)\n";

    return answer;
}


int main() {

    ifstream myfile(filename);
    string line;
    vector<vector<int>> input;

    while (getline(myfile, line)) {
        vector<int> t;
        for (char c : line) {
            t.push_back(c - '0');
        }

        input.push_back(t);
    }


    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;

    return -1;
}