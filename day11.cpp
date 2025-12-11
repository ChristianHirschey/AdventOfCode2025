#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

int countPaths(const std::string& current, const std::string& target, const std::unordered_map<std::string, std::vector<std::string>>& graph) {
    if (current == target) {
        return 1;
    }
    
    auto it = graph.find(current);
    if (it == graph.end()) {
        return 0;
    }
    
    int totalPaths = 0;
    for (const std::string& neighbor : it->second) {
        totalPaths += countPaths(neighbor, target, graph);
    }
    
    return totalPaths;
}

int main() {
    std::ifstream inputFile("day11.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }
    
    std::unordered_map<std::string, std::vector<std::string>> graph;
    
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;
        
        std::string device = line.substr(0, colonPos);
        std::string outputsStr = line.substr(colonPos + 1);
        
        std::istringstream ss(outputsStr);
        std::string output;
        std::vector<std::string> outputs;
        while (ss >> output) {
            outputs.push_back(output);
        }
        
        graph[device] = outputs;
    }
    inputFile.close();
    
    int paths = countPaths("you", "out", graph);
    std::cout << "Part 1: " << paths << "\n";
    
    return 0;
}
