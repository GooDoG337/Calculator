#include <iostream>
#include "calculate.h"

int main() {
    std::string expression;
    while(true) {
        std::cout << "Enter the expression: ";
        std::getline(std::cin, expression);
        if (expression != ":q") {
            try {
                Calculate(expression);
                std::cout << expression << '\n';
            } catch(const std::exception& ex)
            {
                std::cout << ex.what()<< '\n';
            }
        } else {
            return 0;
        }
    }
}