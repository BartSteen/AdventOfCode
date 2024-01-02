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

int part1(vector<int> time, vector<int> dis) {
    int res = 1;
    
    for (int i = 0; i < time.size(); i++) {
        for (int k = 0; k <= time[i]; k++) {
            if (k * (time[i] - k) > dis[i]) {
                res *= (time[i] - k - k) + 1;
                //printf("race  %d answer %d due to vals k:%d and time[i]:%d\n", i, (time[i] - k - k) + 1, k, time[i]);
                break;
            }
        }
    }
    return res;
}

long long combine(vector<int> vals) {
    stringstream build;
    for (int v : vals) {
        build << v;
    }
    return stoll(build.str());
}

long long part2(vector<int> time, vector<int> dis) {
    long long totTime = combine(time);
    long long totDis = combine(dis);

        for (long long k = 0; k <= totTime; k++) {
            if (k * (totTime - k) > totDis) {
                return (totTime - k - k) + 1;
                //printf("race  %d answer %d due to vals k:%d and time[i]:%d\n", i, (time[i] - k - k) + 1, k, time[i]);
            }
        }

    return -1;
}

int main() {

    vector<int> time;
    vector<int> dis;

    ifstream myfile(filename);
    string line;
    getline(myfile, line);
    //times
    line = line.substr(line.find_first_not_of(' ', 5));
    vector<string> strput = split(line, ' ');
    for (string s : strput) {
        if (s != "") {
            //cout << s << endl;
            time.push_back(stoi(s));
        }
    }
    getline(myfile, line);
    strput.clear();
    //distances
    line = line.substr(line.find_first_not_of(' ', 9));
    strput = split(line, ' ');
    for (string s : strput) {
        if (s != "") {
            //cout << s << endl;
            dis.push_back(stoi(s));
        }
    }
    myfile.close();
    
    cout << "Part 1: " << part1(time, dis) <<endl;
    cout << "Part 2: " << part2(time, dis) <<endl;

    return 0;
}