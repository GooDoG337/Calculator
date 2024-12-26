#include "calculate.h"

#include <algorithm>
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
    if (!isItNum && expression[sign_indx] != '.' && expression[sign_indx] != '+') {
        throw WrongSymbol();
    }
    double afterDot = 0.1;
    if (expression[sign_indx] == '.') {         //Если в числе оказалась точка.
        sign_indx++;                    //Отходим от точки направо
        while (expression[sign_indx] <= '9' && expression[sign_indx] >= '0' && sign_indx < expression.size()) {
            num += (expression[sign_indx++] - 48) * afterDot;
            afterDot /= 10;             //Вычисляем дробную часть числа
        }
        if (expression[sign_indx] == '.') {
            throw SecondFraction();         //Выдаём ошибку, если посреди дробной часть появилаьс дробь
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
    }else {
        read_Indx = sign_indx;
    }
    while (expression[read_Indx] <= '9' && expression[read_Indx] >= '0' && expression[read_Indx] != sign ) {
        num *= 10;
        num += expression[read_Indx++] - 48;
    } //находим целую часть пока не дойдём до знака выражения
    double afterDot = 0.1;
    if (expression[read_Indx] == '.') {
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
    for(int i = 2; i < expression.size(); i++) {
        if((expression[i] <= '9' && expression[i] >= '0') && (expression[i-1] == ' ') && (expression[i-2] <= '9' && expression[i-2] >= '0'))
        {
            expression[i-1] = '*';
        }
    }
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
    //std::cout << expression << '\n';
    size_t RightEnd = expression.find('*');
    size_t LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double b = RightValue(expression, RightEnd);
        //std::cout << "a = " << a << std::endl;
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
        std::cout << "b = " << b << std::endl;
        double a = LeftValue(expression, LeftStart);
        std::cout << "a = " << a << std::endl;
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a / b));
        if (b == 0) {
            throw DivideToZero();
        }
        RightEnd = expression.find('/');
        LeftStart = RightEnd;
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
    RightEnd = expression.find('-');
    bool isItNum = true;
    bool isPositive = true;
    if(expression[0] == '-' || (expression[0] <= '9' && expression[0] >= '0')) {
        for(int i = 1; i < expression.size(); i++) {
            if(expression[i] == '-' || expression[i] == '+' && expression[i] == '/' || expression[i] == '*')
            {
                isItNum = false;
                break;
            }
        }
    }
    if(!isItNum){
        LeftStart = RightEnd;
        while(RightEnd != std::string::npos) {
            double b = RightValue(expression, RightEnd);
            //std::cout << b << std::endl;
            double a = LeftValue(expression, LeftStart);
            expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a + b));
            RightEnd = expression.find('-');
            LeftStart = RightEnd;;
        }
    }
}
