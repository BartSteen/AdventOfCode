#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include<iostream>

using namespace std;

#define FILENAME "inputp1.txt"

int part1(vector<vector<int>> inp) {
    int mc = 0;

    for (vector<int> elf : inp) {
        int sum = 0;
        for (int cal : elf) {
            sum += cal;
        }
        mc = max(sum, mc);
    }
    return mc;

}

int part2(vector<vector<int>> inp) {
    int topthree[4] = {0,0,0,0};

    for (vector<int> elf : inp) {
        int sum = 0;
        for (int cal : elf) {
            sum += cal;
        }
        topthree[0] = sum;
        sort(topthree, topthree+4);
    }


    return topthree[1] + topthree[2] + topthree[3];

}


int main() {
    //read in input
    ifstream myfile(FILENAME);
    string temp;
    int elfIndex = 0;
    vector<vector<int>> input;
    input.push_back({});
    while (getline(myfile, temp)) {
        if (temp.length() > 0) {
            input.back().push_back(stoi(temp));
        } else {
            input.push_back({});
        }
    }

    myfile.close();

    cout << "Part 1 result: " << part1(input) << "\n";
    cout << "Part 2 result: " << part2(input) << "\n";


    return -1;
}