#include <fstream>
#include <string>
#include <cmath>

int sum(std::string str) {                             //У чисел есть признаки делимости
    int result = 0;                                    //2 - последнее делится на 2, 3 - сумма всех делится на 3       
    for (int i = 0; i < str.length(); i++) {           //4 - два последних делятся на 4, 5 - последнее делится на 5
        result = result + (str[i] - '0');              //8 - три последних на 8, 9 - сумма на 9, 11 - раность чётных и нечётных делится
    }                                                  //10 - последние 2 делятся, 64 - последние 6 делятся на 64
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
    std::ifstream fin;
    std::ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    std::string bigNumber;
    fin >> bigNumber;
    int arrayOfResults[10];
    //2
    if (getLastNumerals(bigNumber, 1) % 2 == 0) {
        arrayOfResults[0] = 1;
    }
    else {
        arrayOfResults[0] = 0;
    }
    //3
    if (sum(bigNumber) % 3 == 0) {
        arrayOfResults[1] = 1;
    }
    else {
        arrayOfResults[1] = 0;
    }
    //4
    if (getLastNumerals(bigNumber, 2) % 4 == 0) {
        arrayOfResults[2] = 1;
    }
    else {
        arrayOfResults[2] = 0;
    }
    //5
    if (getLastNumerals(bigNumber, 1) % 5 == 0) {
        arrayOfResults[3] = 1;
    }
    else {
        arrayOfResults[3] = 0;
    }
    //6
    if (arrayOfResults[0] == 1 && arrayOfResults[1] == 1) {
        arrayOfResults[4] = 1;
    }
    else {
        arrayOfResults[4] = 0;
    }
    //8
    if (getLastNumerals(bigNumber, 3) % 8 == 0) {
        arrayOfResults[5] = 1;
    }
    else {
        arrayOfResults[5] = 0;
    }
    //9
    if (sum(bigNumber) % 9 == 0) {
        arrayOfResults[6] = 1;
    }
    else {
        arrayOfResults[6] = 0;
    }
    //10
    if (getLastNumerals(bigNumber, 2) % 10 == 0) {
        arrayOfResults[7] = 1;
    }
    else {
        arrayOfResults[7] = 0;
    }
    //11
    if ((sumOfEven(bigNumber) - sumOfUneven(bigNumber)) % 11 == 0) {
        arrayOfResults[8] = 1;
    }
    else {
        arrayOfResults[8] = 0;
    }
    //64
    if (getLastNumerals(bigNumber, 6) % 64 == 0) {
        arrayOfResults[9] = 1;
    }
    else {
        arrayOfResults[9] = 0;
    }
    
    for (int i = 0; i < 9; i++) {
        fout << arrayOfResults[i] << ' ';
    }
    fout << arrayOfResults[9];

    fin.close();
    fout.close();
    return 0;
}
