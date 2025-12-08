#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_set>

int numSplits(const std::string& line, std::unordered_set<int>& splitIndices) {
    int splits = 0;
    std::unordered_set<int> originalIndices = splitIndices;
    for (int index : originalIndices) {
        if (index >= 0 && index < line.size() && line[index] == '^') {
            splits++;
            splitIndices.insert(index + 1);
            splitIndices.insert(index - 1);
            splitIndices.erase(index);
        }
    }
    return splits;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream inputFile("test.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::string line;
    uint64_t splits = 0;
    std::unordered_set<int> splitIndices;

    getline(inputFile, line);

    splitIndices.insert(line.find('S'));

    while (getline(inputFile, line)) {
        splits += numSplits(line, splitIndices);
    }

    inputFile.close();

    std::cout << "Total Splits (Part 1): " << splits << "\n";

    return 0;
}