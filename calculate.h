#ifndef CALCULATOR_CALCULATE_H
#define CALCULATOR_CALCULATE_H
#include <string>
struct WrongSymbol:std::exception
{
    const char *what() const noexcept override {
        return "Обнаружен неподходящий символ.";
    }
};
struct WhereIsNum:std::exception
{
    const char *what() const noexcept override {
        return "Одно или оба числа не были найдены.";
    }
};
struct DivideToZero:std::exception
{
    const char *what() const noexcept override {
        return "Некорректное деление";
    }
};
struct TooManySigns:std::exception {
    const char *what() const noexcept override {
        return "Обнаружено несколько знаков операций подряд.";
    }
};
struct NoSigns:std::exception {
    const char *what() const noexcept override {
        return "Нет знаков, которые надо вычислять.";
    }
};
struct EmptyExpression:std::exception {
    const char *what() const noexcept override {
        return "Выражение пустое.";
    }
};
void Calculate(std::string& expression);
void Validize(std::string& expression);

#endif //CALCULATOR_CALCULATE_H
