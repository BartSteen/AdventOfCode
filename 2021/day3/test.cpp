#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v1;
    
    v1.push_back(5);
    v1.push_back(13);
    v1.push_back(123);

    cout << "Grootte van v1: " << v1.size() << "\n";

    for (auto i = v1.begin(); i != v1.end(); ++i) {
        cout << *i << "\n";
    } 
}