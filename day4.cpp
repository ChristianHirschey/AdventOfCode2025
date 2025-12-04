#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

inline int countNeighbors(int r, int c, int rows, int cols, const std::vector<std::string>& grid) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            if (grid[nr][nc] == '@') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream inputFile("day4.txt");
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

    if (grid.empty()) return 0;

    int rows = grid.size();
    int cols = grid[0].size();
    int result = 0;
    
    std::queue<std::pair<int, int>> q;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '@') {
                if (countNeighbors(i, j, rows, cols, grid) < 4) {
                    grid[i][j] = '.';
                    result++;
                    q.push({i, j});
                }
            }
        }
    }

    while (!q.empty()) {
        std::pair<int, int> curr = q.front();
        q.pop();
        
        int r = curr.first;
        int c = curr.second;

        for (int i = 0; i < 8; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                if (grid[nr][nc] == '@') {
                    if (countNeighbors(nr, nc, rows, cols, grid) < 4) {
                        grid[nr][nc] = '.';
                        result++;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }

    std::cout << "Result: " << result << "\n";
    return 0;
}