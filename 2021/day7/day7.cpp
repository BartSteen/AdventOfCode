#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

//find the mean of the list
int median(vector<int> nums) {
    sort(nums.begin(), nums.end());
    return nums[floor(nums.size()/2)];
}

int mean(vector<int> nums) {
    int sum = 0;
    for (int i : nums) {
        sum += i;
    }
    return round(sum/nums.size());
}

//exponential cost of moving from a to b
int expcost(int a, int b) {
    int sum = 0;
    for (int i = 1; i <= abs(b-a); i++) {
        sum += i;
    }
    return sum;
}

int part1() {
    vector<int> pos;
    ifstream inp("input.txt");
    string inpline;
    getline(inp, inpline);
    int curPos = 0;
    //read in input
    while (curPos != inpline.length() + 1) {
        int nextPos = inpline.find(",", curPos);
        if (nextPos == string::npos) {
            nextPos = inpline.length();
        }
        int num = stoi(inpline.substr(curPos, nextPos - curPos));
        pos.push_back(num);
        curPos = nextPos + 1;
    }

    int mn = median(pos);
    int fuel = 0;
    for (auto i : pos) {
        fuel += abs(i - mn);
    }

    return fuel;
}  

int part2() {
    vector<int> pos;
    ifstream inp("input.txt");
    string inpline;
    getline(inp, inpline);
    int curPos = 0;
    //read in input
    while (curPos != inpline.length() + 1) {
        int nextPos = inpline.find(",", curPos);
        if (nextPos == string::npos) {
            nextPos = inpline.length();
        }
        int num = stoi(inpline.substr(curPos, nextPos - curPos));
        pos.push_back(num);
        curPos = nextPos + 1;
    }

    int mn = mean(pos);
    int fuel = 0;
    for (auto i : pos) {
        fuel += expcost(i, mn);
    }

    return fuel;
}


int main() {
    cout << "result part 1: " << part1() <<"\n";
    cout << "result part 2: " << part2() <<"\n";
    return 0;
}