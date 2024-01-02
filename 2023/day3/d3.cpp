#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define filename "input.txt"

bool isNum(char c) {
    return (int('0') <= int(c) && int(c) <= int('9'));
}

bool hasNbPart(vector<string> input, int i, int j1, int j2) {
    if (j1 == -1) {
        cout << "ERROR\n";
        return false;
    }
        char neut = '.';

    int startcol = max(0, j1-1);
    int endcol = min((int) input[i].length() - 1, j2+1);
    int startrow = max(0, i-1);
    int endrow = min((int) input.size() - 1, i+1);
    
    for (int il = startrow; il <= endrow; il++) {
        for (int j = startcol; j <= endcol; j++) {
            if (!isNum(input[il][j]) && input[il][j] != neut) {
                return true;
            }
        }
    }

    return false;
}




int part1(vector<string> input) {
    int sum = 0;
    
    for (int i = 0; i < input.size(); i++) {
        string curLine = input[i];
        int curNum = 0;
        int numStart = -1;
        for (int j = 0; j < curLine.length(); j++) {
            if (curNum != 0 && !isNum(curLine[j])) {
                //end of number
                if (hasNbPart(input, i, numStart, j-1)) {
                    sum += curNum;
                   // cout << curNum << " has a nb part" << endl;
                } else {
                    //cout << curNum << " does not have a nb part" << endl;

                }
                numStart = -1;
                curNum = 0;
            } else if (isNum(curLine[j])) {
                curNum *= 10;
                curNum += curLine[j] - '0';
                if (numStart == -1) {
                    numStart = j;
                }
            } 
        }

        if (curNum != 0) {
            //eol but number 
            if (hasNbPart(input, i, numStart, curLine.length())) {
                sum += curNum;
               // cout << curNum << " has a nb part" << endl;
            } else {
                //cout << curNum << " does not have a nb part" << endl;

            }
            numStart = -1;
            curNum = 0;
        }
    }
    return sum;
}

bool hasNbPart2(vector<string> input, int curNum, vector<vector<vector<int>>>* pc, int i, int j1, int j2) {
    if (j1 == -1) {
        cout << "ERROR\n";
        return false;
    }
        char neut = '.';
        char gear = '*';

    int startcol = max(0, j1-1);
    int endcol = min((int) input[i].length() - 1, j2+1);
    int startrow = max(0, i-1);
    int endrow = min((int) input.size() - 1, i+1);

    bool answer = false;
    
    for (int il = startrow; il <= endrow; il++) {
        for (int j = startcol; j <= endcol; j++) {
            if (!isNum(input[il][j]) && input[il][j] != neut) {
                answer = true;
                if (input[il][j] == gear) {
                   // cout << "YP " << curNum;
                    (*pc)[il][j].push_back(curNum);
                    //cout << " - size now: " << (*pc)[il][j].size() << endl;
                }
            }
        }
    }

    return answer;
}

long part2(vector<string> input) {
    vector<vector<vector<int>>> gearNbs; 
    for (int i = 0; i < input.size(); i++) {
        vector<vector<int>> t;
        for (int j = 0; j < input[i].length(); j++) {
            vector<int> t2;
            t.push_back(t2);
        }
        gearNbs.push_back(t);
    }
    
    for (int i = 0; i < input.size(); i++) {
        string curLine = input[i];
        int curNum = 0;
        int numStart = -1;
        for (int j = 0; j < curLine.length(); j++) {
            if (curNum != 0 && !isNum(curLine[j])) {
                //end of number
                hasNbPart2(input, curNum, &gearNbs, i, numStart, j-1);
                numStart = -1;
                curNum = 0;
            } else if (isNum(curLine[j])) {
                curNum *= 10;
                curNum += curLine[j] - '0';
                if (numStart == -1) {
                    numStart = j;
                }
            } 
        }

        if (curNum != 0) {
            //eol but number 
            hasNbPart2(input, curNum, &gearNbs, i, numStart, curLine.length());

            numStart = -1;
            curNum = 0;
        }
    }
    long sum = 0;
    for (int i = 0; i < gearNbs.size(); i++) {
        for (int j = 0; j < gearNbs[i].size(); j++) {
            if (gearNbs[i][j].size() == 2) {
                sum += gearNbs[i][j][0] * gearNbs[i][j][1];
            }
            //cout << gearNbs[i][j].size();
        }
       // cout << endl;
    }


    gearNbs.clear();
    return sum;
}

int main() {
    vector<string> input;

    ifstream myFile(filename);
    string line;

    while (getline(myFile, line)) {
        input.push_back(line);
    }

    std::cout << "Part 1: " << part1(input) <<std::endl;
    std::cout << "Part 2: " << part2(input) <<std::endl;

    input.clear();

    return 0;
}