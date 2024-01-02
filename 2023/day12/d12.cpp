#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

bool isValid(string s, vector<int> v) {
    vector<string> splitted = split(s, '.');
    int splInd = 0;
    int vInd = 0;
    //bool justSplit = false;
    while (splInd < splitted.size() && vInd < v.size()) {
        if (splitted[splInd].length() == 0) {
            splInd++;
        //    justSplit = true;
        } else {
            if (splitted[splInd].length() != v[vInd]) {
                return false;
            }
            //size matches
            splInd++;
            //justSplit = false;
            vInd++;
        }
    }

    while (splInd < splitted.size()) {
        if (splitted[splInd].length() != 0) { 
            return false;
        }
        splInd++;
    }

    return vInd == v.size();
}

int countCombs(string s, vector<int> v) {
    if (s.find('?') == string::npos) {
        if (isValid(s, v)) {
                    //cout << s;

            //cout << " is valid" << endl;
            return 1;
        } else {
            //cout << " is invalid" << endl;
            return 0;
        }
    } else {
        //still contains ?
        int sum = 0;
        int qInd = s.find('?');
        s[qInd] = '.';
        sum += countCombs(s, v);
        s[qInd] = '#';
        sum += countCombs(s, v);
        s[qInd] = '?';
        return sum;
    }
}

long long countCombsDp(string s, vector<int> v) {
    int n = s.length() + 1;
    int m = v.size() + 1;
    long long dp[n][m]; //dp[i][j] := #combs of fitting the first j num requirements in the first i characters
    dp[0][0] = 1;
    bool hasPound = false;
    for (int i = 1; i < n; i++) {
        hasPound = hasPound || s.at(i-1) == '#';
        dp[i][0] = hasPound ? 0 : 1;
    }
    for (int j = 1; j < m; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (s.at(i-1) == '.') {
                dp[i][j] = dp[i-1][j];
            } else if (s.at(i-1) == '#') {
                dp[i][j] = 0;
                if (i - v[j-1] >= 0) {
                    //technically enough space
                    if (s.substr(i-v[j-1], v[j-1]).find('.') == string::npos) {
                        //can make a block there
                        //check if stuff before it is OK
                        if (i-v[j-1] == 0 || s.at(i-1-v[j-1]) != '#') {
                            dp[i][j] += dp[max(0,i-1-v[j-1])][j-1]; //fit block, start is either 0 or we take up v[j-1] chars plus a leading .
                        }
                    }
                }

            } else {
                //current thingy is ?
                dp[i][j] = 0;
                dp[i][j] += dp[i-1][j]; // simulate putting a . there

                //simulate putting #
                if (i - v[j-1] >= 0) {
                    //technically enough space
                    if (s.substr(i-v[j-1], v[j-1]).find('.') == string::npos) {
                        //can make a block there
                        //check if stuff before it is OK
                        if (i-v[j-1] == 0 || s.at(i-1-v[j-1]) != '#') {
                            dp[i][j] += dp[max(0,i-1-v[j-1])][j-1]; //fit block, start is either 0 or we take up v[j-1] chars plus a leading .
                        }
                    }
                }

            }
            
        }
    }

    // for (int i = 0; i < n; i++) {
    //     cout << i <<  " [ ";
    //     for (int j = 0; j < m; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "]" << endl;
    // }


    return dp[n-1][m-1];
}

int part1(vector<string> strings, vector<vector<int>> numbers) {
    int result = 0;
    for (int i = 0; i < strings.size(); i++) {
        int add = countCombs(strings[i], numbers[i]);
        result += add;
        //cout << strings[i] << " - " << add << endl;
    }
    return result;
}

long long part2(vector<string> strings, vector<vector<int>> numbers) {
    long long result = 0;
    for (int i = 0; i < strings.size(); i++) {
        long long add = countCombsDp(strings[i], numbers[i]);
        result += add;
        //cout << strings[i] << " - " << add << endl;
    }
    return result;
}

int main() {
    string line;
    ifstream myfile(filename);

    vector<string> strings;
    vector<vector<int>> nums;
    while (getline(myfile, line)) {
        vector<string> splitted = split(line, ' ');
        strings.push_back(splitted[0]);
        vector<string> numss = split(splitted[1], ',');
        vector<int> t;
        for (string n : numss) {
            t.push_back(stoi(n));
        }
        nums.push_back(t);
    }

    vector<string> strings2;
    vector<vector<int>> nums2;

    for (string s : strings) {
        string s2 = "";
        for (int i = 0; i < 5; i++) {
            s2 += s;
            if (i != 4) {
                s2 += "?";
            }
        }
        strings2.push_back(s2);
    }

    for (vector<int> n : nums) {
        vector<int> n2;
        for (int i = 0; i < 5; i++) {
            for (int j : n) {
                n2.push_back(j);
            }
        }
        nums2.push_back(n2);
    }
    // vector<string> test = split(".??..??...?##.", '.');
    // for (string s : test) {
    //     cout << s << endl;
    // }

    // for (string s : strings2) {
    //     cout << s << endl;
    // }
    //part2(strings, nums);
    //cout << "Part 1: " << part1(strings, nums) <<endl;
    cout << "Part 2: " << part2(strings2, nums2) <<endl;

    return -1;
}