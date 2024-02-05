#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <stack>

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

struct Graph {
    vector<vector<int>> neighbours;
    int n;

    Graph(vector<vector<int>> nb) {
        neighbours = nb;
        n = nb.size();
    }

    vector<int> findPathRec(int cur, int target, vector<bool> &visited, vector<int> &path) {
        path.push_back(cur);
        if (cur == target) {
            return path;
        }
        visited[cur] = true;
        for (int next : neighbours[cur]) {
            if (!visited[next]) {
                vector<int> res = findPathRec(next, target, visited, path);
                if (res.size() > 0) {
                    return res;
                } 
            }
        }
        path.pop_back();
        return {};
    }

    //returns a path from source to target (as vector of ids) if it exists, oterwise {}
    vector<int> findPath(int source, int target) {
        //use dfs
        vector<bool> visited(n, false);
        vector<int> path; 

        return findPathRec(source, target, visited, path);
    }

    //remove the edge from a to b if it and add one from b to a if it does not exist yet
    void flipEdge(int va, int vb) {
        for (int i = 0; i < neighbours[va].size(); i++) {
            if (neighbours[va][i] == vb) {
                neighbours[va].erase(neighbours[va].begin() + i);
                break;
            }
        }        

        bool isPresent = false;
        for (int i = 0; i < neighbours[vb].size(); i++) {
            if (neighbours[vb][i] == va) {
                isPresent = true;
                break;
            }
        }

        if (!isPresent) {
            neighbours[vb].push_back(va);
        }

    }

    int reachableFrom(int source) {
        vector<bool> visited(n, false);
        stack<int> stack;

        stack.push(source);

        while (!stack.empty()) {
            int cur = stack.top();
            stack.pop();
            
            visited[cur] = true;
            for (int next : neighbours[cur]) {
                if (!visited[next]) {
                    stack.push(next);
                }
            }
        }
        
        int amountReachable = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                amountReachable++;
            }
        }

        return amountReachable;

    }
};





int minCutConnectedness(Graph* graph, int source, int sink, int cutsAllowed) {
    if (source == sink) {
        return 0;
    }

    Graph residual = Graph((*graph).neighbours);
    vector<vector<int>> flow;

    for (int i = 0; i < residual.n; i++) {
        vector<int> t(residual.n, 0);
        flow.push_back(t);
    }

    vector<int> augmenter = residual.findPath(source, sink);
    while (augmenter.size() > 0) {
        //apply path augmentation
        for (int i = 0; i < augmenter.size() - 1; i++) {
            int from = augmenter[i];
            int to = augmenter[i+1];
            residual.flipEdge(from, to);
            flow[from][to] = 1;
            flow[to][from] = 0;
        }

        augmenter = residual.findPath(source, sink);
    }

    //no more augmenting paths can be found, count connectedness from source
    int cutSize = 0;
    for (int next = 0; next < residual.n; next++) {
        cutSize += flow[source][next];
    }
    if (cutSize != cutsAllowed) {
        return -1;
    }

    //cutsize is allowed, so now find number of vertices reachable from 
    int spart = residual.reachableFrom(source);
    return spart * (residual.n - spart);
}

int part1(Graph* graph) {
    //we can find min cut by using flow theory
    //find max flow -> find residual graph of that flow -> cut consists of vertices reachable from source
    //problem: which vertex is source and which one is sink?
    //could brute force that?
    int cutsAllowed = 3;
    for (int i = 0; i < (*graph).n; i++) {
        for (int j = 0; j < i; j++) {
            int ans = minCutConnectedness(graph, i, j, 3);
            if (ans != -1) {
                return ans;
            }
        }
    }

    return -1;
}

int part2(Graph* graph) {
    return -1;
}

bool vecContains(vector<int> &vec, int check) {
    for (int v : vec) {
        if (v == check) {
            return true;
        }
    }
    return false;
}

int main() {

    ifstream myfile(filename);
    string line;

    vector<vector<int>> adj;
    map<string, int> vertToId;

    while (getline(myfile, line)) {
        string vertex = line.substr(0, line.find(':'));
        if (vertToId.count(vertex) == 0) {
            vertToId[vertex] = adj.size();
            adj.push_back({});
        }

        string nbsstring = line.substr(line.find(' ') + 1);
        vector<string> nbs = split(nbsstring, ' ');
        for (string nb : nbs) {
            if (vertToId.count(nb) == 0) {
                vertToId[nb] = adj.size();
                adj.push_back({});
            }
            //if (vertToId[vertex] < vertToId[nb]) {
                if (!vecContains(adj[vertToId[vertex]], vertToId[nb] )) {
                    adj[vertToId[vertex]].push_back(vertToId[nb]);
                    adj[vertToId[nb]].push_back(vertToId[vertex]);
                }
            //}

        }
    }

    Graph* graph = new Graph(adj);

    cout << "Part 1: " << part1(graph) << endl;
    cout << "Part 2: " << part2(graph) << endl;

    delete graph;

    return -1;
}