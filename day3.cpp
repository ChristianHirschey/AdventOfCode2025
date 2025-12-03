#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int getMaxJoltage(std::string bank) {
    char leftMax = '0';
    char rightMax = '0';

    for (size_t i = 0; i < bank.length(); ++i) {
        if (bank[i] > leftMax && i < bank.length() - 1) {
            leftMax = bank[i];
            rightMax = '0';
        }
        else if (bank[i] > rightMax) {
            rightMax = bank[i];
        }
    }
    return (leftMax - '0') * 10 + (rightMax - '0');
}

int main() {
    std::ios::sync_with_stdio(false);
    std::ifstream inputFile("day3.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::string bank;
    int sum = 0;

    while (getline(inputFile, bank)) {
        if (!bank.empty()) {
            sum += getMaxJoltage(bank);
        }
    }

    inputFile.close();

    std::cout << "Total sum of max joltage values: " << sum << "\n";
    return 0;
}