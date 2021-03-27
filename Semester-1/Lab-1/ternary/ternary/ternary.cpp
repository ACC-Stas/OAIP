#include <iostream>
#include <string>

int main()
{
    long long N, ones = 0, twos = 0, threes = 0, newOnes = 0, newTwos = 0, newThrees = 0;
    std::string f;
    std::cin >> f;
    std::cin >> N;
    for (int i = 0; i < f.size(); i++) {
        switch (f[i])
        {
        case('1'): {
            ones++;
            break;
        }
        case('2'): {
            twos++;
            break;
        }
        case('3'): {
            threes++;
            break;
        }
        default: 
            break;
        }
    }
    for (int i = 0; i < N; i++) {
        newOnes = twos;
        newTwos = ones + threes;
        newThrees = ones;
        ones = newOnes;
        twos = newTwos;
        threes = newThrees;
    }
    std::cout << newOnes << " " << newTwos << " " << newThrees;
}