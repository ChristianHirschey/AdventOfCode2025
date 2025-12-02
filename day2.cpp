#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

bool isInvalid(uint64_t num) {
    std::string numString = std::to_string(num);
    int length = numString.length();
    if (length < 2) return false;
    int i = length / 2;
    if (length % i == 0) {
        std::string subStr = numString.substr(0, i);
        if (numString == subStr + subStr) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::ifstream inputFile("day2.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string range;
    std::vector<std::pair<uint64_t, uint64_t>> ranges;
    uint64_t sum = 0;

    while (!inputFile.eof()) {
        getline(inputFile, range, ',');
        uint64_t start = std::stoull(range.substr(0, range.find('-')));
        uint64_t end = std::stoull(range.substr(range.find('-') + 1));
        ranges.push_back({start, end});   
    }

    inputFile.close();

    for (const auto& r : ranges) {
        for (uint64_t i = r.first; i <= r.second; ++i) {
            if (isInvalid(i)) {
                sum += i;
            }
        }
    }

    std::cout << "Total sum of invalid IDs: " << sum << std::endl;
    return 0;
}