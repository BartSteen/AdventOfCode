#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


#define red 0
#define green 1
#define blue 2

#define filename "input.txt"

std::vector<int> bound{12, 13, 14};

std::vector<std::string> split(std::string str, char del) {
    std::stringstream ss(str);
    std::string part;
    std::vector<std::string> res;
    while (!ss.eof()) {
        getline(ss, part, del);
        res.push_back(part);        
    }
    return res;
}

int colToIndx(std::string col) {
    if (col == "red") {
        return 0;
    }
    if (col == "green") {
        return 1;
    }
    if (col == "blue") {
        return 2;
    }
    std::cout << "ERROR" << std::endl;
    return -1;
}


int part1(std::vector<std::vector<std::pair<std::string, int>>> inp) {
    int gamesum = 0;
    for (int i = 0; i < inp.size(); i++) {
        std::vector<std::pair<std::string, int>> game = inp[i];
        bool valid = true;
        for (std::pair<std::string, int> pull : game) {
            valid = valid && pull.second <= bound[colToIndx(pull.first)];
        }
        if (valid) {
            gamesum += i+1;
        }
        game.clear();
    }
    return gamesum;
}

int part2(std::vector<std::vector<std::pair<std::string, int>>> inp) {
    int cubesum = 0;
    for (int i = 0; i < inp.size(); i++) {
        std::vector<std::pair<std::string, int>> game = inp[i];
        std::vector<int> mins{0, 0, 0};
        for (std::pair<std::string, int> pull : game) {
            mins[colToIndx(pull.first)] = std::max(pull.second, mins[colToIndx(pull.first)]);
        }

        cubesum += mins[0] * mins[1] * mins[2];
        mins.clear();
    }
    return cubesum;
}

int main() {
    //list of games
    std::vector<std::vector<std::pair<std::string, int>>> inp;

    std::ifstream myFile(filename);
    std::string line;

    while (getline(myFile, line)) {
        int colIndx = line.find(':');
        line = line.substr(colIndx+1, line.size() - colIndx);
        std::vector<std::string> games = split(line, ';');
        std::vector<std::pair<std::string, int>> game;
        for (std::string gameline : games) {
            std::vector<std::string> pulls = split(gameline, ',');
            for (std::string pull : pulls) {
                std::vector<std::string> fin = split(pull, ' ');
                std::pair<std::string, int> curPull;
                curPull.first = fin[2];
                curPull.second = stoi(fin[1]);
                game.push_back(curPull);
                fin.clear();
            }
            pulls.clear();
        }
        inp.push_back(game);
        games.clear();
    }


    std::cout << "Part 1: " << part1(inp) <<std::endl;
    std::cout << "Part 2: " << part2(inp) <<std::endl;

    inp.clear();
}