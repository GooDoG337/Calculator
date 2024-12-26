#ifndef CALCULATOR_CALCULATE_H
#define CALCULATOR_CALCULATE_H
#include <string>
struct SecondFraction
{
    std::string message = "Число не может иметь несколько дробных частей.";
};
struct WrongSymbol
{
    std::string message = "Какой-то символ тут явно не подходит.";
};
struct WhereIsNum
{
    std::string message = "А где число?";
};
struct DivideToZero
{
    std::string message = "Некорректное деление";
};
struct TooManySigns {
    std::string message = "Проснитесь и отпустите кнопку, пожалуйста";
};
void Calculate(std::string& expression);


#endif //CALCULATOR_CALCULATE_H
