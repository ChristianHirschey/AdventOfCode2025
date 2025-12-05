#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream inputFile("day5.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::string line;
    std::vector<std::pair<uint64_t, uint64_t>> ranges;
    std::vector<std::pair<uint64_t, uint64_t>> mergedRanges;
    int freshCount = 0;

    while (getline(inputFile, line)) {
        size_t dashPos = line.find('-');
        if (dashPos != std::string::npos) {
            uint64_t start = std::stoull(line.substr(0, dashPos));
            uint64_t end = std::stoull(line.substr(dashPos + 1));
            ranges.emplace_back(start, end);
        }
        else break;
    }

    std::sort(ranges.begin(), ranges.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    if (!ranges.empty()) {
        mergedRanges.push_back(ranges[0]);

        for (size_t i = 1; i < ranges.size(); ++i) {
            if (ranges[i].first <= mergedRanges.back().second + 1) {
                mergedRanges.back().second = std::max(mergedRanges.back().second, ranges[i].second);
            } else {
                mergedRanges.push_back(ranges[i]);
            }
        }
    }

    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        uint64_t number = std::stoull(line);
        for (const auto& range : mergedRanges) {
            if (number >= range.first && number <= range.second) {
                freshCount++;
                break;
            }
        }
    }

    inputFile.close();

    uint64_t freshIdCount = 0;

    for (const auto& range : mergedRanges) {
        freshIdCount += (range.second - range.first + 1);
    }

    std::cout << "Total fresh ingredients: " << freshCount << "\n";
    std:: cout << "Total fresh ingredient IDs: " << freshIdCount << "\n";
    return 0;
}