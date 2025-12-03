#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::ifstream inputFile("day1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::string line;
    int currNum = 50;
    int zeroCount = 0;

    while (inputFile >> line) {
        if (line[0] == 'L') {
            currNum -= std::stoi(&line[1]);
        } else {
            currNum += std::stoi(&line[1]);
        }
        if (currNum % 100 == 0) {
            zeroCount++;
        }
    }

    inputFile.close();

    std::cout << "Total times at zero: " << zeroCount << "\n";

    return zeroCount;
}