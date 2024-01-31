#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
#define filename "input.txt"

#define xind 0
#define mind 1
#define aind 2
#define sind 3

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

class Workflow {
    public:
        string content;
        Workflow* left;
        Workflow* right;
        int conditionPartIndex; //otherwise the index of the part to use for comparisom
        int compareValue;
        bool ge;
        vector<vector<int>> ranges;

    Workflow(string cont) {
        content = cont;
        ranges = {{1,4000},{1,4000},{1,4000},{1,4000}};
    }

    Workflow(int condInd, int compVal, bool g) {
        conditionPartIndex = condInd;
        compareValue = compVal;
        ge = g;
        content = "";
        ranges = {{1,4000},{1,4000},{1,4000},{1,4000}};
    }

    ~Workflow() {
        if (isFinal()) {
            return;
        }
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }


    bool isFinal() {
        return content.length() > 0;
    }

    bool isAcceptOrReject() {
        return content == "A" || content == "R";
    }

    string performFlow(vector<int> &part) {
        if (isFinal()) {
            return content;
        } else {
            if (ge) {
                return part[conditionPartIndex] > compareValue ? (*left).performFlow(part) : (*right).performFlow(part);
            } else {
                return part[conditionPartIndex] < compareValue ? (*left).performFlow(part) : (*right).performFlow(part);
            }
        }
    } 

    void setRanges() {
        if (isAcceptOrReject()) {
            return;
        }
        //is a branching state
        (*left).ranges = ranges;
        (*right).ranges = ranges;
        if (ranges[conditionPartIndex][0] <= compareValue && compareValue <= ranges[conditionPartIndex][1]) {
            if (ge) {
                (*left).ranges[conditionPartIndex][0] = compareValue + 1;
                (*right).ranges[conditionPartIndex][1] = compareValue;
            } else {
                (*left).ranges[conditionPartIndex][1] = compareValue - 1;
                (*right).ranges[conditionPartIndex][0] = compareValue;
            }
        }
        (*left).setRanges();
        (*right).setRanges();
    }

};

int partScore(vector<int> &part) {
    int answer = 0;
    for (int v : part) {
        answer += v;
    }
    return answer;
}

int part1(map<string, Workflow*> &wfmap, vector<vector<int>> &parts) {
    int answer = 0;
    for (vector<int> part : parts) {
        string currentFlow = "in";
        while (currentFlow != "R" && currentFlow != "A") {
            currentFlow = (*wfmap[currentFlow]).performFlow(part);
        }
        if (currentFlow == "A") {
            answer += partScore(part);
        }
    }

    return answer;
}

void makeSingleTree(map<string, Workflow*> &wfmap, Workflow* current) {
    if ((*current).isFinal()) {
        return;
    }
    //is not final
    if ((*(*current).left).isFinal() && !(*(*current).left).isAcceptOrReject()) {
        Workflow* oldptr = (*current).left;
        (*current).left = wfmap[(*(*current).left).content];
        delete oldptr;
    }
    makeSingleTree(wfmap, (*current).left);
    if ((*(*current).right).isFinal() && !(*(*current).right).isAcceptOrReject()) {
        Workflow* oldptr = (*current).right;
        (*current).right = wfmap[(*(*current).right).content];
        delete oldptr;
    }
    makeSingleTree(wfmap, (*current).right);
}

long long partRangeCombs(Workflow* wf) {
    long long answer = 1;
    for (vector<int> r : (*wf).ranges) {
        answer *= (r[1] - r[0]) + 1;
    }
    return answer;
}

long long countAccepters(Workflow* cur) {
    if ((*cur).isAcceptOrReject()) {
        if ((*cur).content == "A") {
            return partRangeCombs(cur);
        } else {
            return 0;
        }
    }

    return countAccepters((*cur).left) + countAccepters((*cur).right);

}

long long part2(map<string, Workflow*> &wfmap) {
    long long answer = 0;
    //first go through a options
    makeSingleTree(wfmap, wfmap["in"]);
    Workflow* root = wfmap["in"];
    (*root).setRanges();



    return countAccepters(root);
}

vector<int> lineToPart(string line) {
    string tr = line.substr(1, line.length() - 2);
    vector<string> spl = split(tr, ',');
    vector<int> part;

    for (string s : spl) {
        part.push_back(stoi(s.substr(s.find('=') + 1)));
    }

    return part;

}

int charToInd(char c) {
    if (c == 'x') {
        return xind;
    }
    if (c == 'm') {
        return mind;
    }
    if (c == 'a') {
        return aind;
    }
    if (c == 's') {
        return sind;
    }
    return -1;
}

bool charToGe(char c) {
    return c == '>';
}

Workflow* lineToWorkflow(string line) {
    if (line.find(':') == string::npos) {
        return new Workflow(line);
    } else {
        //more complicated, with condition
        int cind = charToInd(line[0]);
        int ge = charToGe(line[1]);
        int compVal = stoi(line.substr(2, line.find(':') - 2));
        Workflow* wf = new Workflow(cind, compVal, ge);
        string leftPart = line.substr(line.find(':') + 1, line.find(',') - (line.find(':') + 1));
        string rightPart = line.substr(line.find(',') + 1);
        (*wf).left = lineToWorkflow(leftPart);
        (*wf).right = lineToWorkflow(rightPart);
        return wf;
    }
}


int main() {

    ifstream myfile(filename);
    string line;


    vector<vector<int>> parts;
    map<string, Workflow*> wfmap;

    bool partPart = false;
    while (getline(myfile, line)) {
        if (line.length() == 0) {
            partPart = true;
        } else if (!partPart) {
            //workflow
            string name = line.substr(0, line.find('{'));
            string wf = line.substr(line.find('{') + 1, line.length() - 1 - (line.find('{') + 1));
            wfmap.insert(pair<string, Workflow*>(name, lineToWorkflow(wf)));
        } else {
            //part parsing
            parts.push_back(lineToPart(line));
        }
    }

    cout << "Part 1: " << part1(wfmap, parts) << endl;
    cout << "Part 2: " << part2(wfmap) << endl;
    //clear stuff
    // for (auto i = wfmap.begin(); i != wfmap.end(); i++) {
    //     delete i->second;
    // }
    delete wfmap["in"];

    return -1;
}