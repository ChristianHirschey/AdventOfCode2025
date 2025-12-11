#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

struct State {
    std::string node;
    bool seenDac;
    bool seenFft;
    
    bool operator<(const State& other) const {
        if (node != other.node) return node < other.node;
        if (seenDac != other.seenDac) return seenDac < other.seenDac;
        return seenFft < other.seenFft;
    }
};

long long countPathsWithDacFft(const std::string& current, 
                               const std::string& target,
                               const std::unordered_map<std::string, std::vector<std::string>>& graph,
                               bool seenDac,
                               bool seenFft,
                               std::map<State, long long>& memo) {
    if (current == target) {
        return (seenDac && seenFft) ? 1 : 0;
    }
    
    State state = {current, seenDac, seenFft};
    auto it = memo.find(state);
    if (it != memo.end()) {
        return it->second;
    }
    
    auto graphIt = graph.find(current);
    if (graphIt == graph.end()) {
        memo[state] = 0;
        return 0;
    }
    
    bool newSeenDac = seenDac || (current == "dac");
    bool newSeenFft = seenFft || (current == "fft");
    
    long long totalPaths = 0;
    for (const std::string& neighbor : graphIt->second) {
        totalPaths += countPathsWithDacFft(neighbor, target, graph, newSeenDac, newSeenFft, memo);
    }
    
    memo[state] = totalPaths;
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
    
    std::map<State, long long> memo;
    long long paths = countPathsWithDacFft("svr", "out", graph, false, false, memo);
    std::cout << "Part 2: " << paths << "\n";
    
    return 0;
}