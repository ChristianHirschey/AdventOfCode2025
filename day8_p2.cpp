#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <cmath>

long double getDist(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
    long double dx = std::get<0>(a) - std::get<0>(b);
    long double dy = std::get<1>(a) - std::get<1>(b);
    long double dz = std::get<2>(a) - std::get<2>(b);
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// Union-Find - find with path compression
int find(std::vector<int>& rep, int i) {
    if (rep[i] != i) {
        rep[i] = find(rep, rep[i]);
    }
    return rep[i];
}

// Union-Find -  merge two sets
bool merge(std::vector<int>& rep, int i, int j) {
    int r1 = find(rep, i);
    int r2 = find(rep, j);
    if (r1 == r2) {
        return false;
    }
    if (r1 < r2) {
        rep[r2] = r1;
    } else {
        rep[r1] = r2;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream inputFile("day8.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::string x;
    std::string y;
    std::string z;
    std::vector<std::tuple<int, int, int>> grid;
    uint64_t splits = 0;
    
    while (getline(inputFile, x, ',') && getline(inputFile, y, ',') && getline(inputFile, z)) {
        if (!x.empty() && !y.empty() && !z.empty()) {
            grid.push_back(std::make_tuple(std::stoi(x), std::stoi(y), std::stoi(z)));
        }
    }

    inputFile.close();

    int n = grid.size();

    // initialize Union-Find
    std::vector<int> rep(n);
    for (int i = 0; i < n; ++i) {
        rep[i] = i;
    }

    // calculate all pairwise distances and store with indices
    std::vector<std::tuple<long double, int, int>> distances;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            distances.push_back({getDist(grid[i], grid[j]), i, j});
        }
    }

    // sort by distance (smallest first)
    std::sort(distances.begin(), distances.end());

    // keep merging until all junction boxes are connected
    int comps = n;  // number of circuits
    for (int t = 0; t < distances.size(); ++t) {
        int i = std::get<1>(distances[t]);
        int j = std::get<2>(distances[t]);
        
        if (merge(rep, i, j)) {
            comps--;  // successfully merged two components
            
            if (comps == 1) {
                long double x = std::get<0>(grid[i]);
                long double y = std::get<0>(grid[j]);
                
                long long ans = (long long)x * (long long)y;
                std::cout << "Answer: " << ans << '\n';
                return 0;
            }
        }
    }

    std::cerr << "Failed to connect all stars into one constellation.\n";
    return 1;
}