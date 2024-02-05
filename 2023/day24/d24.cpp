#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cfloat>
#include <cmath>
#include <format>

#define filename "input.txt"
using namespace std;

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

struct Trajectory {
    long long startx;
    long long starty;
    long long startz;

    int vx;
    int vy;
    int vz;

    Trajectory(long long sx, long long sy, long long sz, int vvx, int vvy, int vvz) {
        startx = sx;
        starty = sy;
        startz = sz;

        vx = vvx;
        vy = vvy;
        vz = vvz;
    }

    vector<long double> posAtTime(long double time) {
        return {startx + vx * time, starty + vy * time, startz + vz * time};
    }
};

pair<long double, long double> findIntersectionxy(Trajectory* a, Trajectory* b) {
    //returns pair (x,y) where trajectories a and b cross when negeren z axis

    //x_a = a.startx + a.vx * t
    //x_b = b.startx + b.vx * t
    // x_a = x_b
    // a.startx + a.vx * t = b.startx + b.vx * t
    // -> t = (a.startx - b.startx) / (b.vx - a.vx)
    // if ((*b).vx == (*a).vx) {
    //     return pair(-1,-1);
    // }
    // long double t = ((*a).startx - (*b).startx) / ((*b).vx - (*a).vx);
    // return pair((*a).posAtTime(t)[0], (*a).posAtTime(t)[1]);


    //x_a = a.startx + a.vx * t
    //y_a = a.starty + a.vy * t
    // t = (x_a - a.startx) / a.vx

    //y_a = a.starty + a.vy * ((x_a - a.startx) / a.vx)
    // y_a = (a.starty - ((a.vy * a.startx)/(a.vx)) ) + (a.vy/a.vx) * x
    // y_b = (b.starty - ((b.vy * b.startx)/(b.vx)) ) + (b.vy/b.vx) * x

    if ((*a).vx == 0 || (*b).vx == 0) {
        return pair(-1,-1); //exception, handle later
    }

    long double ac = (*a).starty - (1.0 * (*a).vy * (*a).startx) / (*a).vx;
    long double axf = 1.0 * (*a).vy / (*a).vx;

    long double bc = (*b).starty - (1.0 * (*b).vy * (*b).startx) / (*b).vx;
    long double bxf = 1.0 * (*b).vy / (*b).vx;

    //ac + x * axf = bc + x * bxf
    // x = (ac - bc) / (bxf - axf)
    long double x = (ac - bc) / (1.0 * bxf - axf);
    long double y = ac + x * axf;

    if (isfinite(x)) {
        //check for t >= 0
        // t = (x_a - a.startx) / a.vx
        long double ta = 1.0 * (x - (*a).startx) / (*a).vx;
        long double tb = 1.0 * (x - (*b).startx) / (*b).vx;
        if (ta < 0 || tb < 0) {
            return pair(-1,-1);
        }
    }

    return pair(x,y);
}

int part1(vector<Trajectory*> &input) {
    long long minbox = 200000000000000;
    long long maxbox = 400000000000000;

    int answer = 0;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < i; j++) {
            pair<long double, long double> ins = findIntersectionxy(input[i], input[j]);
            if (minbox <= ins.first && ins.first <= maxbox && minbox <= ins.second && ins.second <= maxbox) {
                	answer++;
            }
        }
    }

    return answer;
}

int part2(vector<Trajectory*> input) {

    
    //int n = input.size()
    int n = min(100, (int) input.size());
    ofstream fil;
    fil.open("part2-tr");
    fil << fixed;
    
    fil << "(declare-fun xpos (Int Real) Real)\n";
    fil << "(declare-fun ypos (Int Real) Real)\n";
    fil << "(declare-fun zpos (Int Real) Real)\n";
    fil << "(declare-fun t (Int) Real)\n";

    fil << "(declare-const sx Int)\n";
    fil << "(declare-const sy Int)\n";
    fil << "(declare-const sz Int)\n";
    fil << "(declare-const vx Int)\n";
    fil << "(declare-const vy Int)\n";
    fil << "(declare-const vz Int)\n";

    //assert all t values greater than 0
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(>= (t "<< i << ") 0) ";
    }
    fil << "))\n";

    //set positions
    //x
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (xpos "<< i << " (t " << i << ")) ";
        fil << "(+ " << (*input[i]).startx << " (* " << (*input[i]).vx << " (t " << i << ")" << "))) ";
    }
    fil << "))\n";
    
    //y
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (ypos "<< i << " (t " << i << ")) ";
        fil << "(+ " << (*input[i]).starty << " (* " << (*input[i]).vy << " (t " << i << ")" << "))) ";
    }
    fil << "))\n";

    //y
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (zpos "<< i << " (t " << i << ")) ";
        fil << "(+ " << (*input[i]).startz << " (* " << (*input[i]).vz << " (t " << i << ")" << "))) ";
    }
    fil << "))\n";

    //intersection with rock line
    //x
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (xpos "<< i << " (t " << i << ")) ";
        fil << "(+ sx (* vx (t " << i << ") ) ) ) ";
    }
    fil << "))\n";

    //y
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (ypos "<< i << " (t " << i << ")) ";
        fil << "(+ sy (* vy (t " << i << ") ) ) ) ";
    }
    fil << "))\n";

    //z
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (zpos "<< i << " (t " << i << ")) ";
        fil << "(+ sz (* vz (t " << i << ") ) ) ) ";
    }
    fil << "))\n";



    fil << "(check-sat)\n(get-value (sx sy sz vx vy vz))";

    fil.close();


    return -1;
}

int part2Opt(vector<Trajectory*> input) {

    
    //int n = input.size()
    int n = min(100, (int) input.size());
    ofstream fil;
    fil.open("part2opt-tr");
    fil << fixed;
    
    // fil << "(declare-fun xpos (Int Int) Int)\n";
    // fil << "(declare-fun ypos (Int Int) Int)\n";
    // fil << "(declare-fun zpos (Int Int) Int)\n";
    fil << "(declare-fun t (Int) Real)\n";

    fil << "(declare-const sx Int)\n";
    fil << "(declare-const sy Int)\n";
    fil << "(declare-const sz Int)\n";
    fil << "(declare-const vx Int)\n";
    fil << "(declare-const vy Int)\n";
    fil << "(declare-const vz Int)\n";

    //assert all t values greater than 0
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(>= (t "<< i << ") 0) ";
    }
    fil << "))\n";

    //set positions
    //x
    // fil << "(assert (and ";
    // for (int i = 0; i < n; i++) {
    //     fil << "(= (xpos "<< i << " (t " << i << ")) ";
    //     fil << "(+ " << (*input[i]).startx << " (* " << (*input[i]).vx << " (t " << i << ")" << "))) ";
    // }
    // fil << "))\n";
    
    // //y
    // fil << "(assert (and ";
    // for (int i = 0; i < n; i++) {
    //     fil << "(= (ypos "<< i << " (t " << i << ")) ";
    //     fil << "(+ " << (*input[i]).starty << " (* " << (*input[i]).vy << " (t " << i << ")" << "))) ";
    // }
    // fil << "))\n";

    // //y
    // fil << "(assert (and ";
    // for (int i = 0; i < n; i++) {
    //     fil << "(= (zpos "<< i << " (t " << i << ")) ";
    //     fil << "(+ " << (*input[i]).startz << " (* " << (*input[i]).vz << " (t " << i << ")" << "))) ";
    // }
    // fil << "))\n";

    //intersection with rock line
    //x
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (+ " << (*input[i]).startx << " (* " << (*input[i]).vx << " (t " << i << ")" << ")) ";
        fil << "(+ sx (* vx (t " << i << ") ) ) ) ";
    }
    fil << "))\n";

    //y
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (+ " << (*input[i]).starty << " (* " << (*input[i]).vy << " (t " << i << ")" << ")) ";
        fil << "(+ sy (* vy (t " << i << ") ) ) ) ";
    }
    fil << "))\n";

    //z
    fil << "(assert (and ";
    for (int i = 0; i < n; i++) {
        fil << "(= (+ " << (*input[i]).startz << " (* " << (*input[i]).vz << " (t " << i << ")" << ")) ";
        fil << "(+ sz (* vz (t " << i << ") ) ) ) ";
    }
    fil << "))\n";



    fil << "(check-sat)\n(get-value (sx sy sz vx vy vz))";

    fil.close();


    return -1;
}

int main() {

    ifstream myfile(filename);
    string line;

    vector<Trajectory*> input;
    
    while (getline(myfile, line)) {
        vector<string> initsplit = split(line, '@');
        vector<string> starts = split(initsplit[0], ',');
        vector<string> vs = split(initsplit[1], ',');

        long long sx = stoll(starts[0]);
        long long sy = stoll(starts[1]);
        long long sz = stoll(starts[2]);

        int vx = stoi(vs[0]);
        int vy = stoi(vs[1]);
        int vz = stoi(vs[2]);

        input.push_back(new Trajectory(sx, sy, sz, vx, vy, vz));
    }


    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;
    cout << "Part 2 opt: " << part2Opt(input) << endl;

    for (Trajectory* tp : input) {
        delete tp;
    }

    return -1;
}