#include <iostream>
#include <string>
#include <cmath>

int sum(std::string str) {                             //У чисел есть признаки делимости
    int result = 0;                                        
    for (int i = 0; i < str.length(); i++) {           //4 - два последних делятся на 4
        result = result + (str[i] - '0');              //9 - сумма на 9, 11 - раность чётных и нечётных делится
    }                                                  
    return result;
}
int sumOfEven(std::string str) {
    int result = 0;
    for (int i = 0; i < str.length(); i += 2) {
        result = result + (str[i] - '0');
    }
    return result;
}
int sumOfUneven(std::string str) {
    int result = 0;
    for (int i = 1; i < str.length(); i += 2) {
        result = result + (str[i] - '0');
    }
    return result;
}
int getLastNumerals(std::string str, int amount) {
    int result = 0, lastNumber = str.size() - 1;
    for (int i = 0; i < amount; i++) {
        result = result + (str[lastNumber - i] - '0') * pow(10, i);
    }
    return result;
}

int main()
{
    bool div4, div9, div11;
    std::string bigNumber;
    std::cin >> bigNumber;
    if (getLastNumerals(bigNumber, 2) % 4 == 0) {
        div4 = true;
    }
    else {
        div4 = false;
    }
    if (sum(bigNumber) % 9 == 0) {
        div9 = true;
    }
    else {
        div9 = false;
    }
    if ((sumOfEven(bigNumber) - sumOfUneven(bigNumber)) % 11 == 0) {
        div11 = true;
    }
    else {
        div11 = false;
    }
    int category;
    if (!div4 && !div9 && !div11) {
        category = 1;
    }
    else if (div4 && !div9 && !div11) {
        category = 2;
    }
    else if (!div4 && div9 && !div11) {
        category = 3;
    }
    else if (!div4 && !div9 && div11) {
        category = 4;
    }
    else if (div4 && div9 && !div11) {
        category = 5;
    }
    else if (div4 && !div9 && div11) {
        category = 6;
    }
    else if (!div4 && div9 && div11) {
        category = 7;
    }
    else if (div4 && div9 && div11) {
        category = 8;
    }
    std::cout << category;
    return 0;
}