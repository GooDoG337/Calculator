#ifndef CALCULATOR_CALCULATE_H
#define CALCULATOR_CALCULATE_H
#include <string>
struct SecondFraction
{
    std::string message = "Число не может иметь несколько дробных частей.";
};
struct WrongSymbol
{
    std::string message = "Ты втираешь мне какую-то дичь.";
};
struct WhereIsNum
{
    std::string message = "А где число?";
};
struct DivideToZero
{
    std::string message = "На нуль мы сегодня не делим";
};
void Calculate(std::string& expression);


#endif //CALCULATOR_CALCULATE_H
