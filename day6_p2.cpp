#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

// Simple BigInt class for addition and multiplication
class BigInt {
    std::vector<int> digits; // stored in reverse order

public:
    BigInt(long long n = 0) {
        if (n == 0) digits.push_back(0);
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }

    void add(const BigInt& other) {
        int carry = 0;
        for (size_t i = 0; i < std::max(digits.size(), other.digits.size()) || carry; ++i) {
            if (i == digits.size()) digits.push_back(0);
            int current = digits[i] + carry + (i < other.digits.size() ? other.digits[i] : 0);
            digits[i] = current % 10;
            carry = current / 10;
        }
    }

    void multiply(const BigInt& other) {
        std::vector<int> result(digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                long long current = result[i + j] + digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result[i + j] = current % 10;
                carry = current / 10;
            }
        }
        while (result.size() > 1 && result.back() == 0) result.pop_back();
        digits = result;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
        if (bi.digits.empty()) return os << "0";
        for (int i = bi.digits.size() - 1; i >= 0; --i) os << bi.digits[i];
        return os;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream inputFile("day6.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    BigInt result(0);
    std::string firstLine;
    std::string secondLine;
    std::string thirdLine;
    std::string fourthLine;
    std::string operatorLine;

    int firstOperand = 0;
    int secondOperand = 0;
    int thirdOperand = 0;
    int fourthOperand = 0;

    getline(inputFile, firstLine);
    getline(inputFile, secondLine);
    getline(inputFile, thirdLine);
    getline(inputFile, fourthLine);

    getline(inputFile, operatorLine);

    int count = 0;
    for (int i = std::max({firstLine.length(), secondLine.length(), thirdLine.length(), fourthLine.length()}) - 1; i >= 0; --i) {
        int currentVal = 0;
        bool hasDigit = false;

        if (i < firstLine.length() && isdigit(firstLine[i])) {
            currentVal += (firstLine[i] - '0');
            hasDigit = true;
        }
        if (i < secondLine.length() && isdigit(secondLine[i])) {
            currentVal *= 10;
            currentVal += (secondLine[i] - '0');
            hasDigit = true;
        }
        if (i < thirdLine.length() && isdigit(thirdLine[i])) {
            currentVal *= 10;
            currentVal += (thirdLine[i] - '0');
            hasDigit = true;
        }
        if (i < fourthLine.length() && isdigit(fourthLine[i])) {
            currentVal *= 10;
            currentVal += (fourthLine[i] - '0');
            hasDigit = true;
        }

        if (hasDigit) {
            count++;
            if (count == 1) firstOperand = currentVal;
            else if (count == 2) secondOperand = currentVal;
            else if (count == 3) thirdOperand = currentVal;
            else if (count == 4) fourthOperand = currentVal;
        }

        if (i < operatorLine.length()) {
            if (operatorLine[i] == '+') {
                BigInt term(firstOperand);
                term.add(BigInt(secondOperand));
                term.add(BigInt(thirdOperand));
                term.add(BigInt(fourthOperand));
                result.add(term);
                
                count = 0;
                firstOperand = 0; secondOperand = 0; thirdOperand = 0; fourthOperand = 0;
            }
            else if (operatorLine[i] == '*') {
                BigInt term(firstOperand);
                switch (count) {
                    case 1: 
                        break;
                    case 2:
                        term.multiply(BigInt(secondOperand));
                        break;
                    case 3:
                        term.multiply(BigInt(secondOperand));
                        term.multiply(BigInt(thirdOperand));
                        break;
                    case 4:
                        term.multiply(BigInt(secondOperand));
                        term.multiply(BigInt(thirdOperand));
                        term.multiply(BigInt(fourthOperand));
                        break;
                }
                result.add(term);

                count = 0;
                firstOperand = 0; secondOperand = 0; thirdOperand = 0; fourthOperand = 0;
            }
        }
    }

    std::cout << "Result: " << result << "\n";
    return 0;
}