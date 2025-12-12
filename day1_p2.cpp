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
        int dist = std::stoi(&line[1]);
        
        if (line[0] == 'L') {
            if (currNum > 0 && dist >= currNum) {
                zeroCount += (dist - currNum) / 100 + 1;
            } else if (currNum == 0) {
                zeroCount += dist / 100;
            }
            currNum = (currNum - dist % 100 + 100) % 100;
        } else {
            if (currNum > 0 && dist >= (100 - currNum)) {
                zeroCount += (dist - (100 - currNum)) / 100 + 1;
            } else if (currNum == 0) {
                zeroCount += dist / 100;
            }
            currNum = (currNum + dist % 100) % 100;
        }
    }

    inputFile.close();

    std::cout << "Total times at zero: " << zeroCount << "\n";

    return 0;
}