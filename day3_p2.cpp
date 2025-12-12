#include <iostream>
#include <vector>
#include <string>
#include <fstream>

uint64_t getMaxJoltage(std::string bank) {
    std::string result = "";
    int n = bank.length();
    int startPos = 0;
    
    for (int i = 0; i < 12; i++) {
        int remaining = 12 - i;  // how many digits we need to pick
        
        // look from startPos to position that leaves enough digits for remaining-1 picks
        int endPos = n - remaining;
        
        // find the maximum digit in this range
        char maxDigit = bank[startPos];
        int maxPos = startPos;
        for (int j = startPos + 1; j <= endPos && j < n; j++) {
            if (bank[j] > maxDigit) {
                maxDigit = bank[j];
                maxPos = j;
            }
        }
        
        result += maxDigit;
        startPos = maxPos + 1;
    }
    
    return std::stoull(result);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::ifstream inputFile("day3.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::string bank;
    uint64_t sum = 0;

    while (getline(inputFile, bank)) {
        // remove trailing whitespace
        while (!bank.empty() && (bank.back() == '\r' || bank.back() == '\n' || bank.back() == ' ')) {
            bank.pop_back();
        }
        if (!bank.empty()) {
            sum += getMaxJoltage(bank);
        }
    }

    inputFile.close();

    std::cout << "Total sum of max joltage values: " << sum << "\n";
    return 0;
}