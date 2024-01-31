#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <queue>

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

enum pulse {low, high};

struct Module {
    vector<string> input;
    string name;
    vector<string> output;

    Module() {}

    Module(string nam, vector<string> out) {
        name = nam;
        output = out;
    }

    virtual void addInput(string inp) {
        input.push_back(inp);
    }

    virtual vector<pair<pulse, string>> receivePulse(pulse p, string source) {}; //process pulse and return pulses that should be send as consequence

    virtual void reset() {};
};

struct Broadcaster : Module {

    Broadcaster(string nam, vector<string> out) : Module(nam, out) {
    }
    

    vector<pair<pulse, string>> receivePulse(pulse p, string source) {
        vector<pair<pulse, string>> out;
        for (string o : output) {
            out.push_back(pair(p, o));
        }
        return out;
    }
};

struct FlipFlop : Module {
    bool isOn;

    FlipFlop(string nam, vector<string> out) : Module(nam, out) {
        isOn = false;
    }
    
    vector<pair<pulse, string>> receivePulse(pulse p, string source) {
        vector<pair<pulse, string>> out;
        if (p == low) {
            isOn = !isOn;
            pulse toSend = isOn ? high : low;
            for (string o : output) {
                out.push_back(pair(toSend, o));
            }            
        } 
        return out;
    }

    void reset() {
        isOn = false;
    }
};

struct Conjunction : Module {
    vector<pulse> geheugen;

    Conjunction(string nam, vector<string> out) : Module(nam, out) {
    }

    void addInput(string inp) {
        input.push_back(inp);
        geheugen.push_back(low);
    }
    
    vector<pair<pulse, string>> receivePulse(pulse p, string source) {
        vector<pair<pulse, string>> out;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == source) {
                geheugen[i] = p;
                break;
            }
        }

        bool allHigh = true;
        for (pulse pin : geheugen) {
            allHigh = allHigh && pin ==high;
        }

        pulse toSend = allHigh ? low : high;
        for (string o : output) {
            out.push_back(pair(toSend, o));
        }    
        return out;
    }

    void reset() {
        for (int i = 0; i < geheugen.size(); i++) {
            geheugen[i] = low;
        }
    }
};

struct Config {
    map<string, Module*> nameToMod;
    int buttonPresses;

    Config(map<string, Module*> m) {
        nameToMod = m;
        buttonPresses = 0;
    }

    //returns first low pulses count and then high pulses count
    pair<long long, long long> pressButton() {
        buttonPresses++;
        long long pulsesSentLow = 0;
        long long pulsesSentHigh = 0;

        queue<tuple<string, pulse, string>> q; //stores tuples (source, type of pulse, target)
        q.push(make_tuple("button", low, "broadcaster"));

        while (!q.empty()) {
            tuple<string, pulse, string> cur = q.front();
            q.pop();
            string source = get<0>(cur);
            pulse p = get<1>(cur);
            string target = get<2>(cur);

            if (p == low) {\
                //cout << source << " -- low --> " << target << endl;
                pulsesSentLow++;
            } else {
                //cout << source << " -- high --> " << target << endl;
                pulsesSentHigh++;
            }

            if (nameToMod.count(target) == 0) {
                continue;
            }
            vector<pair<pulse, string>> toSend = (*nameToMod.at(target)).receivePulse(p, source);

            for (pair<pulse, string> pa : toSend) {
                q.push(make_tuple(target, pa.first, pa.second));
            }
        }

        return pair(pulsesSentLow, pulsesSentHigh);
    }

        //returns first low pulses count and then high pulses count
    bool pressButtonPart2() {
        buttonPresses++;

        queue<tuple<string, pulse, string>> q; //stores tuples (source, type of pulse, target)
        q.push(make_tuple("button", low, "broadcaster"));

        while (!q.empty()) {
            tuple<string, pulse, string> cur = q.front();
            q.pop();
            string source = get<0>(cur);
            pulse p = get<1>(cur);
            string target = get<2>(cur);

            if (p == low && target == "rx") {
                return true;
            }

            if (p == high && target == "dd") {
                cout << buttonPresses << " - " << source << endl;
            }

            if (nameToMod.count(target) == 0) {
                continue;
            }
            vector<pair<pulse, string>> toSend = (*nameToMod.at(target)).receivePulse(p, source);

            for (pair<pulse, string> pa : toSend) {
                q.push(make_tuple(target, pa.first, pa.second));
            }
        }

        return false;
    }

    void setInputs() {
        for (auto i = nameToMod.begin(); i != nameToMod.end(); i++) {
            Module* cur = i-> second;
            for (string t : (*cur).output) {
                if (nameToMod.count(t) > 0) {
                    (*nameToMod.at(t)).addInput((*cur).name);
                }
            }
        }
    }

    void resetStates() {
        for (auto i = nameToMod.begin(); i != nameToMod.end(); i++) {
           (*(i-> second)).reset();
        }
    }

    ~Config() {
        for (auto i = nameToMod.begin(); i != nameToMod.end(); i++) {
            delete i->second;
        }
    }

};

long long part1(Config* config) {
    long long pulsesLow = 0;
    long long pulsesHigh = 0;
    for (int i = 0; i < 1000; i++) {
        pair<long long, long long> inc = (*config).pressButton();
        pulsesLow += inc.first;
        pulsesHigh += inc.second;
        //printf("\nLows sent: %d ------- highs sent: %d\n", inc.first, inc.second);
    }

    return pulsesLow * pulsesHigh;
}

long long part2(Config* config) {
    bool rxReceived = false;
    long long i = 0;
    while (!rxReceived) {
        rxReceived = (*config).pressButtonPart2();
        i++;

    }

    return i;
}

int main() {

    ifstream myfile(filename);
    string line;

    map<string, Module*> ma;

    while (getline(myfile, line)) {
        if (line[0] == '%') {
            string name = line.substr(1, line.find(" ") - 1);
            string outputList = line.substr(line.find(">") + 1);
            vector<string> outputSplit = split(outputList, ',');
            vector<string> outputs;
            for (string s : outputSplit) {
                outputs.push_back(s.substr(1));
            }
            ma.insert(pair<string, Module*>(name, new FlipFlop(name, outputs)));
        } else if (line[0] == '&') {
            string name = line.substr(1, line.find(" ") - 1);
            string outputList = line.substr(line.find(">") + 1);
            vector<string> outputSplit = split(outputList, ',');
            vector<string> outputs;
            for (string s : outputSplit) {
                outputs.push_back(s.substr(1));
            }
            ma.insert(pair<string, Module*>(name, new Conjunction(name, outputs)));
        } else {
            //is broadcaster
            string name = line.substr(0, line.find(" "));
            string outputList = line.substr(line.find(">") + 1);
            vector<string> outputSplit = split(outputList, ',');
            vector<string> outputs;
            for (string s : outputSplit) {
                outputs.push_back(s.substr(1));
            }
            ma.insert(pair<string, Module*>(name, new Broadcaster(name, outputs)));
        }
    }
    Config* config = new Config(ma);
    (*config).setInputs();



    cout << "Part 1: " << part1(config) << endl;
    (*config).resetStates();
    cout << "Part 2: " << part2(config) << endl;

    delete config;

    return -1;
}