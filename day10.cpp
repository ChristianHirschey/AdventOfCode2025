#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <z3++.h>

struct Machine {
    std::string pattern;
    std::vector<std::vector<int>> buttons;
    std::vector<int> joltages;
};

std::vector<int> parseButton(const std::string& str) {
    std::vector<int> result;
    size_t start = 0;
    while (start < str.size()) {
        size_t comma = str.find(',', start);
        if (comma == std::string::npos) {
            comma = str.size();
        }
        result.push_back(std::stoi(str.substr(start, comma - start)));
        start = comma + 1;
    }
    return result;
}

std::vector<int> parseJoltage(const std::string& str) {
    std::vector<int> result;
    size_t start = 0;
    while (start < str.size()) {
        size_t comma = str.find(',', start);
        if (comma == std::string::npos) {
            comma = str.size();
        }
        result.push_back(std::stoi(str.substr(start, comma - start)));
        start = comma + 1;
    }
    return result;
}

std::vector<Machine> readMachines(const std::string& filename) {
    std::vector<Machine> machines;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return machines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        Machine m;
        std::istringstream ss(line);
        std::string token;
        
        ss >> token;
        m.pattern = token.substr(1, token.size() - 2);
        
        while (ss >> token) {
            if (token[0] == '(') {
                m.buttons.push_back(parseButton(token.substr(1, token.size() - 2)));
            } else {
                m.joltages = parseJoltage(token.substr(1, token.size() - 2));
            }
        }
        
        machines.push_back(m);
    }
    
    file.close();
    return machines;
}

uint64_t solvePart1(const Machine& m) {
    z3::context ctx;
    z3::optimize opt(ctx);
    
    std::vector<z3::expr> buttonVars;
    z3::expr sum = ctx.int_val(0);
    
    for (size_t i = 0; i < m.buttons.size(); ++i) {
        std::string varName = "b" + std::to_string(i);
        z3::expr x = ctx.bool_const(varName.c_str());
        buttonVars.push_back(x);
    }
    
    for (size_t lightIdx = 0; lightIdx < m.pattern.size(); ++lightIdx) {
        z3::expr lightSum = ctx.bool_val(false);
        for (size_t btnIdx = 0; btnIdx < m.buttons.size(); ++btnIdx) {
            for (int light : m.buttons[btnIdx]) {
                if (light == static_cast<int>(lightIdx)) {
                    lightSum = lightSum != buttonVars[btnIdx];
                    break;
                }
            }
        }
        
        bool targetOn = (m.pattern[lightIdx] == '#');
        opt.add(lightSum == ctx.bool_val(targetOn));
    }
    
    for (const auto& var : buttonVars) {
        sum = z3::ite(var, sum + 1, sum);
    }
    
    z3::expr totalPresses = ctx.int_const("total");
    opt.add(sum == totalPresses);
    
    z3::optimize::handle handle = opt.minimize(totalPresses);
    
    if (opt.check() == z3::sat) {
        z3::expr lower = opt.lower(handle);
        return lower.get_numeral_uint64();
    }
    
    return 0;
}

uint64_t part1(const std::vector<Machine>& machines) {
    uint64_t total = 0;
    for (const auto& machine : machines) {
        total += solvePart1(machine);
    }
    return total;
}

int main() {
    std::vector<Machine> machines = readMachines("day10.txt");
    std::cout << "Read " << machines.size() << " machines" << std::endl;
    std::cout << "Part 1: " << part1(machines) << std::endl;
    return 0;
}