#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

long long part1(vector<long long> seeds, vector<vector<vector<long long>>> mapping) {
    long long minLoc = LONG_LONG_MAX;
    for (long long seed : seeds) {
        long long curV = seed;
        for (int i = 0; i < mapping.size(); i++) {
            //find range that it falls in
            //printf("%llu -> ", curV);
            for (vector<long long> range : mapping[i]) {
                if (curV - range[1] < range[2] && curV >= range[1]) {
                    //printf("valt in %d, [%d, %d]\n", range[0], range[1], range[2]);
                    //printf("%llu -> ", curV);
                    curV += range[0] - range[1];
                    //printf("%llu\n", curV);
                    break;
                }
            }
            //printf("%llu\n", curV);
        }
        //cout << endl;
       // printf("%llu -> %llu\n", seed, curV);
        minLoc = min(minLoc, curV);
    }


    return minLoc;
}

long long part2(vector<long long> seeds, vector<vector<vector<long long>>> mapping) {
    long long minLoc = LONG_LONG_MAX;
    for (int j = 0; j < seeds.size(); j+=2) {
        for (long long seed = seeds[j]; seed <= seeds[j]+ seeds[j+1];) {
            long long curV = seed;
            long long minToNext = LONG_LONG_MAX;
            for (int i = 0; i < mapping.size(); i++) {
                //find range that it falls in
                //printf("%llu -> ", curV);
                for (vector<long long> range : mapping[i]) {
                    if (curV - range[1] < range[2] && curV >= range[1]) {
                        //printf("valt in %d, [%d, %d]\n", range[0], range[1], range[2]);
                        //printf("%llu -> ", curV);
                        minToNext = min(minToNext, range[1] + range[2] - curV);
                        curV += range[0] - range[1];
                        //printf("%llu\n", curV);
                        break;
                    }
                }
                //printf("%llu\n", curV);
            }
            //cout << endl;
        // printf("%llu -> %llu\n", seed, curV);
            minLoc = min(minLoc, curV);
            seed += minToNext;
        }
    }


    return minLoc;
}

int main() {
    vector<long long> seeds;
    //list of categories of ranges
    vector<vector<vector<long long>>> mapping;

    ifstream myfile(filename);
    string line;

    //read seeds line
    getline(myfile, line);
    vector<string> stvals = split(line.substr(7), ' ');
    for (string s : stvals) {
        seeds.push_back(stoll(s));
    }
    //cout << "all good" << endl;
    //skip whiteline
    getline(myfile, line);
    vector<vector<long long>> curmap;

    while (getline(myfile, line)) {
        if (line == "") {
            //close category
            mapping.push_back(curmap);
            curmap.clear();
        } else {
            if (line.find('m') == string::npos) {
                //is numbers
                //cout << line << endl;
                vector<string> t = split(line, ' ');

                curmap.push_back({stoll(t[0]), stoll(t[1]), stoll(t[2])});
            }
        }
    }
    //last category
    mapping.push_back(curmap);
    curmap.clear();
    // for (vector<vector<long long>> cat : mapping) {
    //     cout << "NEW CATEGORY\n";
    //     for (vector<long long> range : cat) {
    //         printf("valt in %llu, [%llu, %llu]\n", range[0], range[1], range[2]);
    //     }
    //     cout << endl;
    // }

    cout << "Part 1: " << part1(seeds, mapping) <<endl;
    cout << "Part 2: " << part2(seeds, mapping) <<endl;
//26273516 p1
//84931146
    return 0;
}