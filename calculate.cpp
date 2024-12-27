#include "calculate.h"

#include <algorithm>
#include <exception>
#include <iostream>

double RightValue(const std::string& expression, size_t& sign_indx) {
    double num = 0;
    bool isItNum = false;
    bool isPositive = true;
    if(sign_indx == expression.size()-1)    //Проверка, является ли знак последним элементом
    {
        throw WhereIsNum();
    }
    sign_indx++;                    //Отходим от знака на символ направо
    if(expression[sign_indx] == '-' && sign_indx < expression.size()-1) {
        if(expression[sign_indx+1] <= '9' && expression[sign_indx+1] >= '0') {
            isPositive = false;
        }
        else {
            throw WrongSymbol();    //*-a
        }
        sign_indx++;
    }
    while (expression[sign_indx] <= '9' && expression[sign_indx] >= '0') {
        isItNum = true;
        num *= 10;
        num += expression[sign_indx++] - 48;
    }       //Справа от знака число, если есть хотя бы одна цифра.
    if ((expression[sign_indx] > '9' && expression[sign_indx < '0']) && expression[sign_indx] != '*' && expression[sign_indx] != '/' && expression[sign_indx] != '+' && expression[sign_indx] != '-') {
        throw WrongSymbol();
    }
    if (!isItNum && expression[sign_indx] != '.') {
        throw TooManySigns();
    }
    if (expression[sign_indx] == '.') {
            double afterDot = 0.1;          //Если в числе оказалась точка.
        sign_indx++;                    //Отходим от точки направо
        while (expression[sign_indx] <= '9' && expression[sign_indx] >= '0' && sign_indx < expression.size()) {
            num += (expression[sign_indx++] - 48) * afterDot;
            afterDot /= 10;             //Вычисляем дробную часть числа
        }
        if (expression[sign_indx] == '.' ) {
            throw WrongSymbol();         //Выдаём ошибку, если посреди дробной часть появилаьс дробь
        }
    }
    if(isPositive) {
        return num;
    } return -num;
}

double LeftValue(const std::string& expression, size_t& sign_indx) {
    char sign = expression[sign_indx];
    double num=0;
    bool isPositive = true;
    if(sign_indx == 0)
    {
        throw WhereIsNum();         //Если знак в начале строки, откуда взяться числу
    }
    sign_indx--;                    //Листнули налево от знака
    if (sign_indx > 0) {            //Дошли до конца числа если == 0
        while (((expression[sign_indx] <= '9' && expression[sign_indx] >= '0') || (expression[sign_indx] == '.')) && sign_indx > 0)  {
            sign_indx--;
        }   //Если не первый символ - цифра, листаем дальше налево
    }

    size_t read_Indx;
    if (expression[sign_indx] == '-') {
        isPositive = false;
        read_Indx = sign_indx+1;
    }
    else if(expression[sign_indx] == '+') {
        read_Indx = ++sign_indx;
    }else if (expression[sign_indx] <= '9' && expression[sign_indx] >= '0')
    {
        read_Indx = sign_indx;
    } else {
        read_Indx = sign_indx+1;
        sign_indx++;
    }
    bool StartFraction = false;
    if (sign_indx > 0) {
        if (expression[sign_indx-1] == '.') {
            read_Indx--;
            sign_indx--;
            StartFraction = true;
        }
    }
    if (!StartFraction) {
        while (expression[read_Indx] <= '9' && expression[read_Indx] >= '0' && expression[read_Indx] != sign ) {
            num *= 10;
            num += expression[read_Indx++] - 48;
        } //находим целую часть пока не дойдём до знака выражения
    }
    if (expression[read_Indx] == '.') {
        double afterDot = 0.1;
        read_Indx++;
        while (expression[read_Indx] <= '9' && expression[read_Indx] >= '0' && expression[read_Indx] != sign ) {
            num += afterDot*(expression[read_Indx++] - 48);
            afterDot /= 10;
        }
    }
    if (expression[read_Indx] != sign) {
        throw WrongSymbol();
    }
    if(isPositive) {
        return num;
    } return -num;
}

void Calculate(std::string& expression) {
    Validize(expression);
    size_t RightEnd = expression.find('*');
    size_t LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double b = RightValue(expression, RightEnd);
        //std::cout << "b = " << b << std::endl;
        double a = LeftValue(expression, LeftStart);
        //std::cout << "a = " << a << std::endl;
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a * b));
        RightEnd = expression.find('*');
        LeftStart = RightEnd;
        //std::cout << expression << std::endl;
    }
    RightEnd = expression.find('/');
    size_t minuses = expression.find("--");
    while(minuses != std::string::npos) {
        expression.replace(minuses, 2, "+");
        minuses = expression.find("--");
    }
    LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double b = RightValue(expression, RightEnd);
        //std::cout << "b = " << b << std::endl;
        double a = LeftValue(expression, LeftStart);
        //std::cout << "a = " << a << std::endl;
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a / b));
        if (b == 0) {
            throw DivideToZero();
        }
        RightEnd = expression.find('/');
        LeftStart = RightEnd;
        //std::cout << expression << std::endl;

    }
    RightEnd = expression.find('+');
    LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double b = RightValue(expression, RightEnd);
        //       std::cout << b << std::endl;
        double a = LeftValue(expression, LeftStart);
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a + b));
        RightEnd = expression.find('+');
        LeftStart = RightEnd;
    }
    bool isItNum = false;
    for (const auto& c : expression) {
        if (c != '-' && c != '.' && (c < '0' || c > '9')) {
            throw WrongSymbol();
        }
    }
    if(expression[0] == '-') {
        isItNum = true;
        for(int i = 1; i < expression.size(); i++) {
            if ((expression[i] > '9' || expression[i] < '0') && expression[i] != '.')
            {
                isItNum = false;
                break;
            }
        }
    } if (isItNum) {return; }
    RightEnd = expression.find('-');
    if (RightEnd == 0) {
        RightEnd = expression.find('-', 1);
    }
    LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double b = RightValue(expression, RightEnd);
        //std::cout <<"b == " << b << std::endl;
        double a = LeftValue(expression, LeftStart);
        //std::cout << "a = " << a << std::endl;
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a - b));
        //std::cout << expression << std::endl;
        if(expression[0] == '-') {
            for(int i = 1; i < expression.size(); i++) {
                if ((expression[i] <= '9' && expression[i] >= '0' ) || expression[i] == '.')
                {
                    isItNum = true;
                }
                else {
                    isItNum = false;
                    break;
                }
            }
            if (isItNum) {return; }
        }
        RightEnd = expression.find('-',1);
        LeftStart = RightEnd;;
    }

}

void Validize(std::string& expression) {
    if (expression.empty()) {
        throw EmptyExpression();
    }
    for(int i = 2; i < expression.size(); i++) {
        if((expression[i] <= '9' && expression[i] >= '0') && (expression[i-1] == ' ') && (expression[i-2] <= '9' && expression[i-2] >= '0'))
        {
            expression[i-1] = '*';
        }
    }
    if (expression.find('*') == std::string::npos &&
    expression.find('/') == std::string::npos &&
    expression.find('+') == std::string::npos &&
    expression.find('-',1) == std::string::npos) {
        throw NoSigns();
    }
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
    auto Minuses = expression.find("--");
    while (Minuses != std::string::npos) {
        expression.replace(Minuses, 2, "+");
        Minuses = expression.find("--", Minuses);
    }
}