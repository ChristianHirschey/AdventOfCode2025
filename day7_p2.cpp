#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream inputFile("day7.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();

    int cols = grid[0].size();
    
    std::unordered_map<int, uint64_t> pathsAtPosition;
    
    for (int col = 0; col < cols; col++) {
        if (grid[0][col] == 'S') {
            pathsAtPosition[col] = 1;
            break;
        }
    }

    for (size_t row = 1; row < grid.size(); row++) {
        std::unordered_map<int, uint64_t> nextPathsAtPosition;
        
        for (const auto& [position, pathCount] : pathsAtPosition) {
            if (position >= 0 && position < grid[row].length() && grid[row][position] == '^') {
                if (position - 1 >= 0) {
                    nextPathsAtPosition[position - 1] += pathCount;
                }
                if (position + 1 < cols) {
                    nextPathsAtPosition[position + 1] += pathCount;
                }
            } else {
                nextPathsAtPosition[position] += pathCount;
            }
        }
        
        pathsAtPosition = nextPathsAtPosition;
    }

    uint64_t totalPaths = 0;
    for (const auto& [position, pathCount] : pathsAtPosition) {
        totalPaths += pathCount;
    }

    std::cout << "Total Timelines: " << totalPaths << "\n";
    return 0;
}