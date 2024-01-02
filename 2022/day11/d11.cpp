#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
#define FILENAME "input.txt"


class Monkey {
    public:
    vector<long long> items;
    int testDivisor;
    int trueMonkey;
    int falseMonkey;
    bool opIsPlus; //true for +, false for *
    string otherTerm; //integer for constant, "old" for old
    long inspectCount;
    
    Monkey(vector<long long> it, int td, int tm, int fm, bool op, string ot) {
        items = it;
        testDivisor = td;
        trueMonkey = tm;
        falseMonkey = fm;
        opIsPlus = op;
        otherTerm = ot;
        inspectCount = 0;

    }

    bool test(long long item) {
        return (item % testDivisor) == 0;
    }

    long long applyOp(long long item) {
        if (otherTerm == "old") {
            if (opIsPlus) {
                return item + item;
            } else {
                return item * item;
            }
        } else {
            long long oth = stol(otherTerm);
            if (opIsPlus) {
                return item + oth;
            } else {
                return item * oth;
            }
        }
    }

    bool hasItem() {
        return items.size() > 0;
    }

    void addItem(long long item) {
        items.push_back(item);
    }

    //removes first element from list and return pair <item val, monkey to pass to> or <-1, -1> if no items
    pair<long long, int> throwItem(bool isPart1) {
        if (items.size() == 0) {
            return make_pair(-1, -1);
        }
        inspectCount++;

        long long olditem = items[0];

        long long item = items[0];
        items.erase(items.begin());

        item = applyOp(item);
        if (isPart1) {
            item = item/3;
        }
        if (item < 0) {
            cout << "problem value " << item << " from " << olditem << " and "; 
            cout << " operation: new = old" << (opIsPlus ? " + " : " * ") << otherTerm << "\n";
        }

        if (test(item)) {
            return make_pair(item, trueMonkey);
        } else {
            return make_pair(item, falseMonkey);
        }
    }
};

vector<string> split(string str, char delim) {
    vector<string> res;
    int oldIndex = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == delim) {
            res.push_back(str.substr(oldIndex, i-oldIndex));
            oldIndex = i+1;
        }
    }
    res.push_back(str.substr(oldIndex));
    return res;
}

int part1(vector<Monkey *> monkeys) {
    int numOfRounds = 20;

    for (int i = 0; i < numOfRounds; i++) {
        for (Monkey * monk : monkeys) {
            while (monk->hasItem()) {
                pair<int, int> ni = monk->throwItem(true);

                monkeys[ni.second]->addItem(ni.first);
            }
        }
    }

    int largest = 0;
    int largest2 = 0;
    for (Monkey * monk : monkeys) {
        if (monk->inspectCount > largest) {
            largest2 = largest;
            largest = monk->inspectCount;
        } else if (monk->inspectCount > largest2) {
            largest2 = monk->inspectCount;
        }
    }
    return largest * largest2;
}

long long part2(vector<Monkey *> monkeys, long long comMult) {
    int numOfRounds = 10000;

    for (int i = 1; i <= numOfRounds; i++) {
        for (Monkey * monk : monkeys) {
            while (monk->hasItem()) {
                pair<long long, int> ni = monk->throwItem(false);
                if (ni.first < 0) {
                    cout << "Problem item value: " << ni.first << "\n";
                }
                monkeys[ni.second]->addItem(ni.first % comMult);
            }
        }

    // for (int j = 0; j < monkeys.size(); j++) {
    //     Monkey monk = *monkeys[j];
    //     cout << "monkey " << j << " has items: ";
    //     for (long long it : monk.items) {
    //         cout <<  it << " , ";
    //     }
    //     cout << "\n";
    // }

    if (i == 20 || i == 1 || i % 1000 == 0) {
        cout << "iteration " << i << "\n";
        for (int j = 0; j < monkeys.size(); j++) {
            Monkey monk = *monkeys[j];
            cout << "monkey " << j << " inspected " << monk.inspectCount << " times\n";
        }
    }


    }

    long long largest = 0;
    long long largest2 = 0;
    for (Monkey * monk : monkeys) {
        //cout << monk->inspectCount << "\n";
        if (monk->inspectCount > largest) {
            largest2 = largest;
            largest = monk->inspectCount;
        } else if (monk->inspectCount > largest2) {
            largest2 = monk->inspectCount;
        }
    }
    return largest * largest2;
}

int main() {

    ifstream myfile(FILENAME);
    string temp;

    vector<Monkey *> monkeys;
    long long comMult = 1;

    vector<long long> items;
    bool op = false;
    int testVal = 1;
    int trueMonk = 0;
    int falseMonk = 0;
    string other = "0";
    

    while (getline(myfile, temp)) {
        if (temp.size() == 0) {
            //add monkey
            monkeys.push_back(new Monkey(items, testVal, trueMonk, falseMonk, op, other));
            comMult *= testVal;
        } else if (temp.find("Starting") != string::npos) {
            items.clear();
            string vals = temp.substr(18);
            vector<string> valssplit = split(vals, ',');
            for (string val : valssplit) {
                items.push_back(stol(val));
            }
        } else if (temp.find("Operation") != string::npos) {
            if (temp.at(23) == '+') {
                op = true;
            } else {
                op = false;
            }

            other = temp.substr(25);
        } else if (temp.find("Test") != string::npos) {
            testVal = stoi(temp.substr(21));
        } else if (temp.find("true") != string::npos) {
            trueMonk = stoi(&temp.back());
        } else if (temp.find("false") != string::npos) {
            falseMonk = stoi(&temp.back());
        }

    }
    comMult *= testVal;
    monkeys.push_back(new Monkey(items, testVal, trueMonk, falseMonk, op, other));
    cout << "commult val: " << comMult << "\n";
    // for (Monkey * monk : monkeys) {
    //     cout << "items: ";
    //     for (int it : (*monk).items) {
    //         cout << it << " ,";
    //     }
    //     cout << " test divisor: " << (*monk).testDivisor << " true/false monkey: " << (*monk).trueMonkey << " / " << (*monk).falseMonkey;
    //     cout << " operation: new = old" << ((*monk).opIsPlus ? " + " : " * ") << (*monk).otherTerm << "\n";
    // }

    //cout << "Part 1: " << part1(monkeys) << "\n";
    cout << "Part 2: " << part2(monkeys, comMult) << "\n";
    // long long val1 = 58558;
    // long long val2 = 96577;
    // cout << val1 * val1 << "\n";
    // cout << val2 * val2 << "\n";


    return -1;
}
