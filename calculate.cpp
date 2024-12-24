#include "calculate.h"
#include <iostream>

double RightValue(const std::string& expression, size_t& sign_indx) {
    double num = 0;
    bool isItNum = false;
    bool IsPositive = true;
    if(sign_indx == expression.size()-1)
    {
        throw WhereIsNum();
    }
    sign_indx++;
    if(expression[sign_indx] == '-' && sign_indx != expression.size()-1)
    {
        IsPositive = false;
        sign_indx++;
    } else if(expression[sign_indx] == '-' && sign_indx != expression.size()-1)
    {
        throw WhereIsNum();
    }

        while (expression[sign_indx] <= '9' && expression[sign_indx] >= '0' && sign_indx < expression.size()) {
            isItNum = true;
            num *= 10;
            num += expression[sign_indx++] - 48;
        }
    if (!isItNum) {
        throw WrongSymbol();
    }
    double afterDot = 0.1;
    if (expression[sign_indx] == '.') {
        sign_indx++;
        while (expression[sign_indx] <= '9' && expression[sign_indx] >= '0' && sign_indx < expression.size()) {
            num += (expression[sign_indx++] - 48) * afterDot;
            afterDot /= 10;
        }
        if (expression[sign_indx] == '.') {
            throw SecondFraction();
        }
    }
    else if ((expression[sign_indx] != '*' && expression[sign_indx] != '/' && expression[sign_indx] != '+' &&
               expression[sign_indx] != '-') || sign_indx == expression.size()) {
        throw WrongSymbol();
    }
    if(IsPositive)
    {
        return num;
    }
    return -num;
}

double LeftValue(const std::string& expression, size_t& sign_indx)
{
    bool isItNum = false;
    bool IsPositive = true;
    double num=0;
    if(sign_indx == 0)
    {
        throw WhereIsNum();
    }
    sign_indx--;
    while(expression[sign_indx] <= '9' && expression[sign_indx] >= '0' && sign_indx != 0)
    {
        isItNum = true;
        sign_indx--;
    }
    if(sign_indx == 0 && expression[0] <= '9' && expression[0] >= '0')
    {
        isItNum = true;
    }
    if(!isItNum)
    {
        throw WrongSymbol();
    }
    if(expression[sign_indx] == '.') {
        sign_indx--;
        while(expression[sign_indx] <= '9' && expression[sign_indx] >= '0' && sign_indx != 0) {
            sign_indx--;
        }
        if(expression[sign_indx] == '.') {
            throw SecondFraction();
        }
    }
    size_t readIndx = sign_indx;
    if(expression[sign_indx] == '-' && sign_indx == 0)
    {
        IsPositive = false;
        readIndx++;
    }
    else if(expression[sign_indx] == '-' &&  expression[sign_indx-1] >= '9' && expression[sign_indx-1] <= '0')
    {
        IsPositive = false;
        readIndx++;
    }
    else if(expression[sign_indx] == '-' && expression[sign_indx-1] <= '9' && expression[sign_indx-1] >= '0')
    {
        readIndx++;
        sign_indx++;
    }
    std::cout << expression[readIndx] << " and " << expression[sign_indx] << '\n';
    while(expression[readIndx] <= '9' && expression[readIndx] >= '0')
    {
        num*=10;
        num+=expression[readIndx++]-48;
    }
    double afterDot = 0.1;
    if(expression[readIndx] == '.')
    {
        readIndx++;
        while(expression[readIndx] <= '9' && expression[readIndx] >= '0') {
            num += (expression[readIndx++] - 48) * afterDot;
            afterDot *= 0.1;
        }
    }
    else if (expression[sign_indx] != '*' && expression[sign_indx] != '/' && expression[sign_indx] != '+' && expression[sign_indx] != '-' && sign_indx != 0)
    {
        throw WrongSymbol();
    }
    if(IsPositive) {
        return num;
    }
    return -num;
}

void Calculate(std::string& expression){
    size_t RightEnd = expression.find('*');
    size_t LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double a = RightValue(expression, RightEnd);
        double b = LeftValue(expression, LeftStart);
        std::cout << b << " & " << a << '\n';
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a * b));
        RightEnd = expression.find('*');
        LeftStart = RightEnd;
        std::cout << expression << '\n';
    }
    RightEnd = expression.find('/');
    LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double a = RightValue(expression, RightEnd);
        double b = LeftValue(expression, LeftStart);
        if(a == 0)
        {
            throw DivideToZero();
        }
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(b / a));
        RightEnd = expression.find('/');
        LeftStart = RightEnd;
    }
    RightEnd = expression.find('+');
    LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double a = RightValue(expression, RightEnd);
        double b = LeftValue(expression, LeftStart);
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(b + a));
        RightEnd = expression.find('+');
        LeftStart = RightEnd;
    }
    RightEnd = expression.find('-');
    LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double a = RightValue(expression, RightEnd);
        double b = LeftValue(expression, LeftStart);
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(b + a));
        RightEnd = expression.find('-');
        LeftStart = RightEnd;
    }
}