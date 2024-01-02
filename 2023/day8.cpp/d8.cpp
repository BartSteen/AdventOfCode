#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;
#define filename "input.txt"

class Node {
    public:
        string content;
        Node* left;
        Node* right;
        // string leftContent;
        // string rightContent;

        Node() {
            left = nullptr;
            right = nullptr;
        }

        Node(string a) {
            content = a;
            left = nullptr;
            right = nullptr;
        }

        ~ Node() {
            if (left) {
                delete left;
            }
            if (right) {
                delete right;
            }
        }

    bool isGoal() {
        return content == "ZZZ";
    }

    Node* makeMove(char c) {
        if (c == 'L') {
            return left;
        } 
        if (c == 'R') {
            return right;
        }
        return this;
    }

    Node* findContent(string goal) {
        if (content == goal) {
            return this;
        } 
        if (left) {
            if ((*left).findContent(goal)) {
                return (*left).findContent(goal);
            }
        }
        if (right) {
            if ((*right).findContent(goal)) {
                return (*right).findContent(goal);
            }
        }
        return nullptr;
    }

    string stringTree() {
        string result = "";
        if (left) {
            result += (*left).stringTree();
        }
        result += " - " + content +  " - ";
        if (right) {
            result += (*right).stringTree();
        }
        return result;
    }
};


int part1(Node* root, string directions) {
    int index = 0;
    Node* current = root;
    while (!(*current).isGoal()) {
        //cout << (*current).content << endl;
        current = (*current).makeMove(directions[index % directions.length()]);
        index++;
    }
    //cout << (*current).content << endl;
    return index;
}

string content(string node) {
    return node.substr(0,3);
}

string left(string node) {
    return node.substr(7,3);
}

string right(string node) {
    return node.substr(12,3);
}

int alt1(vector<string> &input, string directions) {
    //find starting index
    int dirIndex = 0;
    int nodeIndex = 0;
    for (; nodeIndex < input.size(); nodeIndex++) {
        if (content(input[nodeIndex]) == "AAA") {
            break;
        }
    }

    while (content(input[nodeIndex]) != "ZZZ") {
        string goal;
        if (directions[dirIndex % directions.length()] == 'L') {
            //go left
            goal = left(input[nodeIndex]);

        } else {
            //go right
            goal = right(input[nodeIndex]);
        }
        //cout << "GOAL IS " << goal << endl;
        for (int i = 0; i < input.size(); i++) {
            if (content(input[i]) == goal) {
                nodeIndex = i;
                break;
            }
        }

        dirIndex++;
    }
    return dirIndex;
}

bool allGoaled(vector<string> &input, vector<int> &nodeIndices) {
    for (int ind : nodeIndices) {
        if (content(input[ind])[2] != 'Z') {
            return false;
        }
    }
    return true;
}

long alt2(vector<string> &input, string directions) {
    //find starting index
    long dirIndex = 0;
    vector<int> nodeIndices;
    for (int i = 0; i < input.size(); i++) {
        if (content(input[i])[2] == 'A') {
            nodeIndices.push_back(i);
            //cout << " " << i;
        }
    }
    //cout << endl;

    while (!allGoaled(input, nodeIndices)) {
        for (int j = 0; j < nodeIndices.size(); j++) {
            int nodeIndex = nodeIndices[j];
            string goal;
            if (directions[dirIndex % directions.length()] == 'L') {
                //go left
                goal = left(input[nodeIndex]);

            } else {
                //go right
                goal = right(input[nodeIndex]);
            }
            //cout << "GOAL IS " << goal << endl;
            for (int i = 0; i < input.size(); i++) {
                if (content(input[i]) == goal) {
                    nodeIndices[j] = i;
                    break;
                }
            }
        }

        dirIndex++;
    }
    return dirIndex;
}

long alt1WithStart(vector<string> &input, string directions, int start) {
    //find starting index
    long dirIndex = 0;
    int nodeIndex = start;

    while (content(input[nodeIndex])[2] != 'Z') {
        string goal;
        if (directions[dirIndex % directions.length()] == 'L') {
            //go left
            goal = left(input[nodeIndex]);

        } else {
            //go right
            goal = right(input[nodeIndex]);
        }
        //cout << "GOAL IS " << goal << endl;
        for (int i = 0; i < input.size(); i++) {
            if (content(input[i]) == goal) {
                nodeIndex = i;
                break;
            }
        }

        dirIndex++;
    }
    return dirIndex;
}

long long alt2alter(vector<string> &input, string directions) {
    //find starting index
    vector<int> nodeIndices;
    for (int i = 0; i < input.size(); i++) {
        if (content(input[i])[2] == 'A') {
            nodeIndices.push_back(i);
            //cout << " " << i;
        }
    }
    //cout << endl;
    vector<long> results;
    for (int s : nodeIndices) {
        results.push_back(alt1WithStart(input, directions, s));
    }

    long long result = results[0];
    for (int i = 1; i < results.size(); i++) {
        result = lcm(result, results[i]);
        cout << result << endl;
    }
    return result;

}

int part2(Node* root, string directions) {
    return -1;
}


int main() {
    ifstream myfile(filename);
    string directions;
    //first line
    getline(myfile, directions);

    //tree
    string line;
    //whiteline
    getline(myfile, line);
    //Node* root = nullptr;
    vector<string> input;
    while (getline(myfile, line)) {
        // Node* cur;
        // if (!root) {
        //     root = new Node(line.substr(0,3));
        //     cur = root;
        // } else {
        //     cur = (*root).findContent(line.substr(0,3));
        // }
        // (*cur).left = new Node(line.substr(7,3));
        // (*cur).right = new Node(line.substr(12,3));
        input.push_back(line);
    }

    //cout << (*root).stringTree() << endl;

    // for (string in : input) {
    //     cout << in << endl;
    // }
    //cout << "Part 1: " << alt1(input, directions) <<endl;
    cout << "Part 2: " << alt2alter(input, directions) <<endl;

    // cout << "Part 1: " << part1(root, directions) <<endl;
    // //cout << "Part 1: " << part1(hands, bids) <<endl;
    // cout << "Part 2: " << part2(root, directions) <<endl;

    //delete root;
    return -1;
}