#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

int main() {
    std::ifstream inputFile("day9.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::vector<int> tiles_x;
    std::vector<int> tiles_y;
    
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) continue;
        
        int x = std::stoi(line.substr(0, commaPos));
        int y = std::stoi(line.substr(commaPos + 1));
        tiles_x.push_back(x);
        tiles_y.push_back(y);
        
    }
    inputFile.close();

    int tile_count = tiles_x.size();
    std::cout << "Read " << tile_count << " red tiles\n";

    // store edges as [x1, x2, y1, y2] where x1 <= x2
    // for vertical lines (x1 == x2), ensure y1 <= y2
    std::vector<std::vector<int>> lines;
    
    for (int i = 0; i < tile_count; ++i) {
        int next = (i + 1) % tile_count;
        int x1 = tiles_x[i];
        int y1 = tiles_y[i];
        int x2 = tiles_x[next];
        int y2 = tiles_y[next];
        
        std::vector<int> edge(4);
        if (x1 == x2) {
            // vertical line
            edge[0] = x1;
            edge[1] = x2;
            edge[2] = std::min(y1, y2);
            edge[3] = std::max(y1, y2);
        } else {
            // horizontal line
            if (x1 < x2) {
                edge[0] = x1;
                edge[1] = x2;
                edge[2] = y1;
                edge[3] = y2;
            } else {
                edge[0] = x2;
                edge[1] = x1;
                edge[2] = y1;
                edge[3] = y2;
            }
        }
        lines.push_back(edge);
    }

    uint64_t area = 0;

    for (int i = 0; i < tile_count; ++i) {
        for (int j = i + 1; j < tile_count; ++j) {
            int x1 = tiles_x[i];
            int y1 = tiles_y[i];
            int x2 = tiles_x[j];
            int y2 = tiles_y[j];

            area = std::max(area, (uint64_t)(std::abs(x2 - x1) + 1) * (std::abs(y2 - y1) + 1));
        }
    }

    std::cout << "Part 1: " << area << "\n";
    return 0;
}