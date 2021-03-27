#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main()
{
    unsigned long int number, denominator;
    std::string answer = "YES";
    std::ifstream fin;
    std::ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    fin >> number;
    if (number == 1) {
        answer = "NO";
    }
    denominator = sqrt(number) + 1;
    while (denominator > 1) {
        if (number % denominator == 0) {
            answer = "NO";
        }
        denominator--;
    }
    fout << answer;
    fin.close();
    fout.close();
    return 0;
}