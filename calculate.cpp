#include "calculate.h"

#include <algorithm>
#include <iostream>
#include <regex>
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
    double afterDot = 0.1;
    if (expression[sign_indx] == '.') {         //Если в числе оказалась точка.
        sign_indx++;                    //Отходим от точки направо
        while (expression[sign_indx] <= '9' && expression[sign_indx] >= '0' && sign_indx < expression.size()) {
            num += (expression[sign_indx++] - 48) * afterDot;
            afterDot /= 10;             //Вычисляем дробную часть числа
        }
        if (expression[sign_indx] == '.' ) {
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

double LeftValue2(const std::string& expression) {
    std::smatch result;
    std::regex_search(expression, result, std::regex{R"(^[\-]?\d*[\.]?\d*)"});
    double lvalue = 0;
    bool dotdigits = false;
    double drob = 0.1;
    bool positive = true;
    for (const auto& i : result.str())
    {
        if (i == '.')
        {
            dotdigits = true;
        }
        else if(i == '-') {
            positive = false;
        }
        else
        {
            if (!dotdigits)
            {
                lvalue*=10;
                lvalue += i-48;
            }
            if (dotdigits)
            {
                lvalue += (i-48)*drob;
                drob/=10;
            }
        }
    }
    if(!positive) lvalue*=-1;
    return lvalue;
}

double RightValue2(const std::string& expression) {
    std::smatch result;
    std::regex_search(expression, result, std::regex{R"([\-]?\d*[\.]?\d*$)"});
    std::cout << "result = " << result.str() << '\n';
    double lvalue = 0;
    bool dotdigits = false;
    double drob = 0.1;
    bool positive = true;
    for (const auto& i : result.str())
    {
        if (i == '.')
        {
            dotdigits = true;
        }
        else if(i == '-') {
            positive = false;
        }
        else
        {
            if (!dotdigits)
            {
                lvalue*=10;
                lvalue += i-48;
            }
            if (dotdigits)
            {
                lvalue += (i-48)*drob;
                drob/=10;
            }
        }
    }
    if(!positive) lvalue*=-1;
    return lvalue;
}
double RightValue3(const std::string& expression) {
    std::smatch result;
    std::regex_search(expression, result, std::regex{R"(\d*[\.]?\d*$)"});
    std::cout << "result = " << result.str() << '\n';
    double lvalue = 0;
    bool dotdigits = false;
    double drob = 0.1;
    bool positive = true;
    for (const auto& i : result.str())
    {
        if (i == '.')
        {
            dotdigits = true;
        }
        else if(i == '-') {
            positive = false;
        }
        else
        {
            if (!dotdigits)
            {
                lvalue*=10;
                lvalue += i-48;
            }
            if (dotdigits)
            {
                lvalue += (i-48)*drob;
                drob/=10;
            }
        }
    }
    if(!positive) lvalue*=-1;
    return lvalue;
}

void Validize(std::string& expression) {
    if (expression.empty()) {
        throw std::exception();
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
        throw std::exception();
    }
    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
    auto Minuses = expression.find("--");
    while (Minuses != std::string::npos) {
        expression.replace(Minuses, 2, "+");
        Minuses = expression.find("--", Minuses);
    }
}

void Calculate(std::string& expression) {
    Validize(expression);
    auto Minuses = expression.find("--");
    while (Minuses != std::string::npos) {
        expression.replace(Minuses, 2, "+");
        Minuses = expression.find("--", Minuses);
    }
    std::regex r {R"([\-]?\d*[\.]?\d* *\* *[\-]?\d*[\.]?\d* *)"};
    std::smatch result;
    std::regex_search(expression, result, r);
    while(!result.str().empty()) {
        double b = RightValue2(result.str());
        double a = LeftValue2(result.str());
        expression.replace(expression.find(result.str()), result.str().length(), std::to_string(a * b));
        std::regex_search(expression, result, r);
    }
    size_t minuses = expression.find("--");
    while(minuses != std::string::npos) {
        expression.replace(minuses, 2, "+");
        minuses = expression.find("--");
    }
    r = {R"([\-]?\d*[\.]?\d* *\/ *[\-]?\d*[\.]?\d* *)"};
    std::regex_search(expression, result, r);
    while(!result.str().empty()) {
        double b = RightValue2(result.str());
        double a = LeftValue2(result.str());
        expression.replace(expression.find(result.str()), result.str().length(), std::to_string(a / b));
        std::regex_search(expression, result, r);
    }

    r = {R"([\-]?\d*[\.]?\d* *\+ *[\-]?\d*[\.]?\d* *)"};
    std::regex_search(expression, result, r);
    while(!result.str().empty()) {
        double b = RightValue2(result.str());
        std::cout << "b = " << b << '\n';
        double a = LeftValue2(result.str());
        std::cout << "a= " << a << '\n';
        std::cout << "expr = " << expression << '\n';
        expression.replace(expression.find(result.str()), result.str().length(), std::to_string(a + b));
        std::regex_search(expression, result, r);
    }
    Minuses = expression.find("--");
    while (Minuses != std::string::npos) {
        expression.replace(Minuses, 2, "+");
        Minuses = expression.find("--", Minuses);
    }
    bool isItNum = false;
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
    size_t RightEnd = expression.find('-');
    if (RightEnd == 0) {
        RightEnd = expression.find('-', 1);
    }
    size_t LeftStart = RightEnd;
    while(RightEnd != std::string::npos) {
        double b = RightValue(expression, RightEnd);
        double a = LeftValue(expression, LeftStart);
        expression.replace(LeftStart, RightEnd - LeftStart, std::to_string(a - b));
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
   /* r = {R"([\-]?\d*[\.]?\d* *\- *\d*[\.]?\d* *)"};
    std::regex_search(expression, result, r);
    while(!result.str().empty()) {
        double b = RightValue3(result.str());
        std::cout << "b = " << b << '\n';
        double a = LeftValue2(result.str());
        std::cout << "a = " << a << '\n';
        expression.replace(expression.find(result.str()), result.str().length(), std::to_string(a - b));
        std::regex_search(expression, result, r);
    }
    if(!std::regex_match(expression,std::regex{"[\\-]?\\d*[\\.]?\\d*"})) {
        throw std::exception();
    }
}*/
