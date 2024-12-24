#include <iostream>
#include "calculate.h"
int main() {
    std::string expression;
    while(true) {
        std::cout << "Enter the expression: ";
        std::getline(std::cin, expression);
        try {
            Calculate(expression);
            std::cout << expression << '\n';
        } catch(const SecondFraction& ex)
        {
            std::cout << ex.message << '\n';
        } catch(const WrongSymbol& ex)
        {
            std::cout << ex.message << '\n';
        } catch(const WhereIsNum& ex) {
            std::cout << ex.message << '\n';
        } catch(const DivideToZero& ex)
        {
            std::cout << ex.message << '\n';
        }
    }
    return 0;
}
