#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define LANG 12

int amount;

string* getInput() {
    int i = 0;

    cout << "Geef grootte:\n";
    cin >> amount;
    string* input = new string[amount];
    cout << "Geef input:\n";
    for (int i = 0; i < amount; i++) {
        string curinput;
        cin >> curinput;
        //cout << curinput << "-- regel\n";
        input[i] = curinput;
    }
    return input;
}

void printArray(string* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << "\n";
    }
}

//solve part 1 of the puzzle
int gamepscalc(string* input) {
    int count0[LANG] = {0};
    int count1[LANG] = {0};

    for (int i = 0; i < amount; i++) {
        string cur = input[i];
        for (int j = 0; j < LANG; j++) {
            if (cur[j] == '0') {
                count0[j]++;
            } else {
                count1[j]++;
            }
        }
    }

    int gambin[LANG];
    int epsbin[LANG];
    for (int i = 0; i < LANG; i++) {
        if (count0[i] > count1[i]) {
            gambin[i] = 0;
            epsbin[i] = 1;
        } else {
            gambin[i] = 1;
            epsbin[i] = 0;
        }
    }

    int gamma = 0;
    int epsilon = 0;

    for (int i = LANG - 1; i >= 0; i--) {
        gamma += gambin[i] * pow(2, LANG - i - 1);
        epsilon += epsbin[i] * pow(2, LANG - i - 1);
    }
    cout << "gamma: " << gamma << "\nepsilon: " << epsilon << "\n";
    return gamma * epsilon;
}

string* filterOnBitMost(string* input, int bit, int &size) {
    //do the counting
    int count0 = 0;
    int count1 = 0;
    for (int i = 0; i < size; i++) {
        if (input[i][bit] == '0') {
            count0++;
        } else {
            count1++;
        }
    }
    char toKeep;
    int nToKeep;
    if (count0 > count1) {
        toKeep = '0';
        nToKeep = count0;
    } else {
        toKeep = '1';
        nToKeep = count1;
    }

    //filtering step
    string* result = new string[nToKeep];
    int ind = 0;
    for (int i = 0; i < size; i++) {
        if (input[i][bit] == toKeep) {
            result[ind] = input[i];
            ind++;
        }
    }
    size = nToKeep;

    return result;

}

string* filterOnBitLeast(string* input, int bit, int &size) {
    //do the counting
    int count0 = 0;
    int count1 = 0;
    for (int i = 0; i < size; i++) {
        if (input[i][bit] == '0') {
            count0++;
        } else {
            count1++;
        }
    }
    char toKeep;
    int nToKeep;
    if (count0 > count1) {
        toKeep = '1';
        nToKeep = count1;
    } else {
        toKeep = '0';
        nToKeep = count0;
    }

    //filtering step
    string* result = new string[nToKeep];
    int ind = 0;
    for (int i = 0; i < size; i++) {
        if (input[i][bit] == toKeep) {
            result[ind] = input[i];
            ind++;
        }
    }
    size = nToKeep;

    return result;

}

int part2calc(string* input) {
    string* oxres = input;
    int oxressize = amount;

    for (int i = 0; i < LANG; i++) {
        oxres = filterOnBitMost(oxres, i, oxressize);
        //cout << "oxy\n";
        //printArray(oxres, oxressize);
        if (oxressize <= 1) {
            break;
        }
    }

    string* cores = input;
    int coressize = amount;

    for (int i = 0; i < LANG; i++) {
        cores = filterOnBitLeast(cores, i, coressize);
        //cout << "co2\n";
        //printArray(cores, coressize);
        if (coressize <= 1) {
            break;
        }
    }

    int oxy = 0;
    int co2 = 0;

    cout << "oxy: " << oxres[0] << "\nco2: " << cores[0] << "\n";


    for (int i = LANG - 1; i >= 0; i--) {
        if (oxres[0][i] == '1') {
            oxy += pow(2, LANG - i - 1);
        } 
        if (cores[0][i] == '1') {
            co2 += pow(2, LANG - i - 1);
        }
    }
    cout << "oxy: " << oxy << "\nco2: " << co2 << "\n";
    return oxy * co2;

    return 0;
}

int main() {
    string* input = getInput();
    //cout << "elem 0:" << input[0];
    //printArray(input, amount);
    //gamepscalc(input);
    cout << "part2 result: " << part2calc(input);

    delete[] input;


    return 0;
}
