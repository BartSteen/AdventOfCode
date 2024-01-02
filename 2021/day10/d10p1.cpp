#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#define FILENAME "inputp1.txt"


using namespace std;

int charToIndex(char c) {
    if (c == '(' || c == ')') {
        return 0;
    } else if (c == '[' || c == ']') {
        return 1;
    } else if (c == '{' || c == '}') {
        return 2;
    } else if (c == '<' || c == '>') {
        return 3;
    }
}

char indexToChar(int index) {
    if (index == 0) {
        return ')';
    } else if (index == 1) {
        return ']';
    } else if (index == 2) {
        return '}';
    } else if (index == 3) {
        return '>';
    }
    return 'E';
}

bool isOpening(char c) {
    return c == '(' || c == '[' || c == '{' || c == '<';
}

//-1 if it is actually valid, otherwise index of first invalid char
char findInvalid(string inp) {
    // ( = 0, [ = 1, { = 2, > = 3
    //int occ [4] = {0,0,0,0};
    vector<int> inds [4]; //indices of opening chars


    for (int i = 0; i < inp.length(); i++) {
        char c = inp[i];
        int ind = charToIndex(c);
        if (isOpening(c)) {
            inds[ind].push_back(i);
        } else {
            if (inds[ind].empty()) {
                return c;
            } else {
                int bArea = inds[ind].back();
                inds[ind].pop_back();

                for (int j = 0; j < 4; j++) {
                    if (j == ind) {
                        continue;
                    } else {
                        if (!inds[j].empty() && inds[j].back() > bArea) {
                            return c;
                        }
                    }
                }
            }
        }
    }

    return ' ';
}

//-1 if it is actually valid, otherwise index of first invalid char
long computeIncompleteScore(string inp) {
    // ( = 0, [ = 1, { = 2, > = 3
    //int occ [4] = {0,0,0,0};
    vector<int> inds [4]; //indices of opening chars


    for (int i = 0; i < inp.length(); i++) {
        char c = inp[i];
        int ind = charToIndex(c);
        if (isOpening(c)) {
            inds[ind].push_back(i);
        } else {
            if (inds[ind].empty()) {
                return 0;
            } else {
                int bArea = inds[ind].back();
                inds[ind].pop_back();

                for (int j = 0; j < 4; j++) {
                    if (j == ind) {
                        continue;
                    } else {
                        if (!inds[j].empty() && inds[j].back() > bArea) {
                            //string is corrupt
                          //  cout << "this string is corrupt: " << inp << "\n";
                            return 0;
                        }
                    }
                }
            }
        }
    }
                          //  cout << "this string is incomplete: " << inp << "\n";

    //string is incomplete, now complete it 
    long score = 0;
    int amount = inds[0].size() + inds[1].size() + inds[2].size() + inds[3].size();
    string debugger  = "";

    for (int i = 0; i < amount; i++) {
        //delete highest index
        int charToRemove = -1;
        int latestIndex = -1;

        for (int j = 0; j < 4; j++) {
            if (!inds[j].empty() && inds[j].back() > latestIndex) {
                latestIndex = inds[j].back();
                charToRemove = j;
            }
        }

        inds[charToRemove].pop_back();
        score = score * 5 + charToRemove + 1;
        debugger += indexToChar(charToRemove);

    }
    
        //cout << "found ending: " << debugger << "\n";


    return score;
}

int p1(vector<string> input) {
    int score = 0;
    for (string str : input) {
        char c = findInvalid(str);
        if (c != ' ') {
            //cout << "found a " << c << "\n";
            if (c == '(' || c == ')') {
                score += 3;
            } else if (c == '[' || c == ']' ) {
                score += 57;
            } else if (c == '{' || c == '}') {
                score += 1197;
            } else if (c == '<' || c == '>') {
                score += 25137;
            }
        }
    }
    return score;
}

long p2(vector<string> input) {
    vector<long> scores;
    for (string str : input) {
        long score = computeIncompleteScore(str);
        //cout << "line score: " << score <<"\n";
        if (score > 0) {
            scores.push_back(score);
        }
    }

    sort(scores.begin(), scores.end());
    int middle = (scores.size() - 1) / 2;

    // for (int i = 0; i < scores.size(); i++) {
    //     cout << i << " - " << scores[i] << "\n";
    // }

    return scores[middle];
}

int main() {
    //read in input
    vector<string> input;

    ifstream myfile(FILENAME);
    string temp;
    while (getline(myfile, temp)) {
        input.push_back(temp);
    }
    myfile.close();



    cout << "Part 1 score: " << p1(input) << "\n";
    cout << "Part 2 score: " << p2(input) << "\n";

    return 0;
}

