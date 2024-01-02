#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
#define FILENAME "allCountries.txt"

int main() {

    ifstream myfile(FILENAME);

    string temp;
    vector<int> input;
    long i = 0;
    while (getline(myfile, temp)) {
       
        i++;
    }
    // for (auto v : input) {
    //     cout << v << "\n";
    // }    

    cout << "done " << i;

    return -1;
}