#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define DAYS 256
#define BDELAY 8
#define ADELAY 6

using namespace std;

int part1() {

    vector<int> fish;

    ifstream infile("input.txt");
    string inpline;
    getline(infile, inpline);
    int curIndex = 0;

    while (curIndex != string::npos && curIndex != inpline.length() + 1) {
        int nextIndex = inpline.find(",", curIndex);
        if (nextIndex == string::npos) {
            nextIndex = inpline.length();
        }
        string str = inpline.substr(curIndex, nextIndex - curIndex);
        int num = stoi(str);
        fish.push_back(num);
        curIndex = nextIndex + 1;
    }

    for (int i = 1; i <= DAYS; i++) {
        int toAddCount = 0;
        for (int j = 0; j < fish.size(); j++) {
            if (fish[j] == 0) {
                //let a new fish be born
                fish[j] = ADELAY;
                toAddCount++;
            } else {
                fish[j]--;
            }
        }        
        //cout << "day " << i << " adding " << toAddCount << "\n";
        for (int j = 0; j < toAddCount; j++) {
            fish.push_back(BDELAY);
        }
    }

    return fish.size();
}


long long part2() {
    //
    unsigned long long fishCount[BDELAY + 1] = {0};

    ifstream infile("input.txt");
    string inpline;
    getline(infile, inpline);
    int curIndex = 0;

    while (curIndex != string::npos && curIndex != inpline.length() + 1) {
        int nextIndex = inpline.find(",", curIndex);
        if (nextIndex == string::npos) {
            nextIndex = inpline.length();
        }
        string str = inpline.substr(curIndex, nextIndex - curIndex);
        int num = stoi(str);
        fishCount[num]++;
        curIndex = nextIndex + 1;
    }

    for (int i = 1; i <= DAYS; i++) {
        unsigned long long zeroCount = fishCount[0];
        //pickle down rickenomics
        for (int j = 0; j < BDELAY ; j++) {
            fishCount[j] = fishCount[j+1];
        }        
        fishCount[BDELAY] = zeroCount;
        fishCount[ADELAY] += zeroCount;

        //print it
        cout << "day " << i << ": ";
        for (unsigned long long j : fishCount) {
            cout << j << " - ";
        }
        cout << "\n";
    }

    //sum the count
    unsigned long long count = 0;
    for (unsigned long long i : fishCount) {
        count += i;
    }
    return count;

}

int main() {

    //cout << "part 1 result: " << part1() << "\n";
    cout << "part 2 result: " << part2() << "\n";


    return 0;
}