#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, unsigned __int128 n) {
    if (n == 0) return os << "0";
    std::string s;
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

int pop_front(std::vector<int>& numbers) {
    if (numbers.empty()) return 0;
    int front = numbers.front();
    numbers.erase(numbers.begin());
    return front;
}

std::vector<int> parseLineToIntegers(const std::string& line, std::vector<int>& numbers) {
    int number = 0;
    for (const char& ch : line) {
        if (isdigit(ch)) { 
            number *= 10;
            number += (ch - '0');
        }
        else {
            if (number == 0) continue;
            numbers.push_back(number);
            number = 0;
        }
    }
    if (number > 0) {
        std::cout << "Other Parsed number: " << number << "\n";
        numbers.push_back(number);
    }
    return numbers;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream inputFile("day6.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    int number = 0;
    unsigned __int128 result = 0;
    std::string line;
    std::vector<int> firstOperand;
    std::vector<int> secondOperand;
    std::vector<int> thirdOperand;
    std::vector<int> fourthOperand;

    getline(inputFile, line);
    std::cout << "Processing first line: " << "\n";
    parseLineToIntegers(line, firstOperand);
    getline(inputFile, line);
    std::cout << "Processing second line: " << "\n";
    parseLineToIntegers(line, secondOperand);
    getline(inputFile, line);
    std::cout << "Processing third line: " << "\n";
    parseLineToIntegers(line, thirdOperand);
    getline(inputFile, line);
    std::cout << "Processing fourth line: " << "\n";
    parseLineToIntegers(line, fourthOperand);

    std::cout << "firstOperand size: " << firstOperand.size() << "\n";
    std::cout << "secondOperand size: " << secondOperand.size() << "\n";
    std::cout << "thirdOperand size: " << thirdOperand.size() << "\n";
    std::cout << "fourthOperand size: " << fourthOperand.size() << "\n";
    getline(inputFile, line);

    for (const char& ch : line) {
        if (ch == '+') { 
            result += ((unsigned __int128)pop_front(firstOperand) + pop_front(secondOperand) + pop_front(thirdOperand) + pop_front(fourthOperand));
        }
        else if (ch == '*') { 
            result += ((unsigned __int128)pop_front(firstOperand) * pop_front(secondOperand) * pop_front(thirdOperand) * pop_front(fourthOperand));
        }
    }

    std::cout << "Result: " << (unsigned __int128)result << "\n";
    return 0;
}