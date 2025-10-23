#include "edacal/calculator.hpp"

#include <iostream>

int main() {
    edacal::Calculator calculator;
    std::string line;
    std::cout << ">> " << std::flush;
    while (std::getline(std::cin, line)) {
        if (!calculator.processLine(line, std::cout)) {
            break;
        }
        std::cout << ">> " << std::flush;
    }
    return 0;
}
