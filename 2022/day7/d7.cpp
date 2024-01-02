#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
#define FILENAME "input.txt"

class Node  {
    public:
     string name;
     long size;
     vector<Node *> children;
     Node* parent;
     bool calced;

     Node(string n, long s, Node* p) {
        name = n;
        size = s;
        parent = p;
        children = {};
        calced = false;
     }
};


bool findIndex(vector<Node * > children, string name) {
    for (int i = 0; i < children.size(); i++) {
        Node child = *children[i];
        if (child.name == name) {
            return i;
        }
    }
    return -1;
}

Node findChild(const Node * cNode, const string name) {
    for (int i = 0; i < (*cNode).children.size(); i++) {
        Node child = *(*cNode).children[i];
        if (child.name == name) {
            return child;
        }
    }
}

Node* findChild2(Node* cNode, string name) {
    for (int i = 0; i < (*cNode).children.size(); i++) {
        Node * child = (*cNode).children[i];
        if ((*child).name == name) {
            //cout << child.name << " matches " << name << "\n";
            return (*cNode).children[i];
        }
    }
}


void printChildren(Node * cNode) {
    cout << "Size " << (*cNode).size << " and calced " << (*cNode).calced << " Children of " << (*cNode).name << " are: ";
    for  (Node * child : (*cNode).children) {
        cout << (*child).name << " - ";
    }
    cout << "\n";
}

void printTree(Node * cNode) {
    printChildren(cNode);
    for  (Node * child : (*cNode).children) {
        printTree(child);
    }
    
}

void calcSumSizes(Node * cNode) {
    if ((*cNode).children.size() == 0) {
        (*cNode).calced = true;
        return;
    }

    long sum = 0;
    for (Node * child : (*cNode).children) {
        if (!(*child).calced) {
            calcSumSizes(child);
        } 
        sum += (*child).size;
    }
    (*cNode).size = sum;
    (*cNode).calced = true;
}

long findAnswer(Node * cNode) {
    long sum = 0;
    for (Node * child : (*cNode).children) {
        sum += findAnswer(child);
    }
    if ((*cNode).children.size() > 0 && (*cNode).size <= 100000) {
        sum += (*cNode).size;
    }
    return sum;

}

long findAnswerP2(Node * cNode, long needed, long smallestAnswer) {
    if ((*cNode).children.size() == 0) {
        return smallestAnswer;
    }

    if ((*cNode).size > needed) {
        smallestAnswer = min(smallestAnswer, (*cNode).size);
    }

    for (Node * child : (*cNode).children) {
        smallestAnswer = findAnswerP2(child, needed, smallestAnswer);
    }
    return smallestAnswer;
    
}


int part1() {
    ifstream myfile(FILENAME);
    string temp;
    //vector<string> cpath;
    Node inNode("/", 0, nullptr);
    Node *root = &inNode;
    Node *cNode = root;


    while (getline(myfile, temp)) {
        //cout << "Processing " << temp << "\n";
         //   printChildren(*root);

        if (temp.at(0) == '$') {
            //is command
            if (temp.at(2) == 'c' && temp.at(3) == 'd') {
                string dir = temp.substr(5);
                if (dir == "..") {
                    cNode = (*cNode).parent;
                    //cout << "current node is now " << (*cNode).name << "\n";
                } else if (dir == "/") {
                    cNode = root;
                   // cout << "current node is now " << (*cNode).name << "\n";
                } else  {
                    cNode = findChild2(cNode, dir);
                    //cNode = & findChild(cNode, dir);

                    // int indexOf = findIndex((*cNode).children, dir);
                    // if (indexOf != -1) {
                    //     cNode = &((*cNode).children[indexOf]);
                    // } else {
                    //     cout << "ERROR\n";
                
                    // }
                    //cout << "current node is now " << (*cNode).name << "\n";
                }
            } else {
                //is ls

            }
        } else {
            if (temp.at(0) == 'd') {
                string dir = temp.substr(4);
                    //Node newNode(dir, 0, cNode); 
                    (*cNode).children.push_back(new Node(dir, 0, cNode));
                    //cNode = newNode;   
            //        cout << "added dir " << dir << " to children of " << (*cNode).name << "\n";
            //        printChildren((*cNode));
            } else {
                //is file
                long size = stol(temp.substr(0, temp.find(' ')));
                string name = temp.substr(temp.find(' ') + 1);
                //Node newNode(name, size, cNode); 
                (*cNode).children.push_back(new Node(name, size, cNode));
            //    cout << "added file " << name << " to children of " << (*cNode).name << "\n";
      //          printChildren((*cNode));
            }
        }
       // cout << "Current node : " << (*cNode).name << "\n";
    }

    myfile.close();

    //printTree(root);
    calcSumSizes(root);
    //printTree(root);
    cout << "Part 1: " << findAnswer(root) << "\n";

    //part 2
    long unusedSpace = 70000000 - (*root).size;
    long neededSpace = 30000000 - unusedSpace;

    cout << "Part 2: " << findAnswerP2(root, neededSpace, 70000000) << "\n";




 //   printChildren(*root);
    //cout << "root node has name: " <<(*root).name << "\n";
    //print this trash
    //printTree(*root);
}



int main() {


    part1();
    return -1;
}