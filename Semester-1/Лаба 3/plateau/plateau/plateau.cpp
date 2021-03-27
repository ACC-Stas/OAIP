#include <iostream>

int main()
{
    int N, numberOfPateus = 0, amountOfBestP = 0, amountOfWorstP = INT_MAX;
    std::cin >> N;
    int currentNum, previousNum = INT_MAX, amountOfCurrentP; //INT_MAX, because |current|<10^6;
    for (int i = 0; i < N;) {
        i++;                                                 //changed i is requred in current iteration
        std::cin >> currentNum;
        if (currentNum == previousNum) {
            numberOfPateus++;
            amountOfCurrentP = 1;
            while (currentNum == previousNum) {
                amountOfCurrentP++;
                previousNum = currentNum;
                i++;
                if (i == N+1) {
                    break;
                }
                std::cin >> currentNum;
            }
            if (amountOfBestP < amountOfCurrentP) {
                amountOfBestP = amountOfCurrentP;
            }
            if (amountOfWorstP > amountOfCurrentP) {
                amountOfWorstP = amountOfCurrentP;
            }
        }
        previousNum = currentNum;
    }
    if (numberOfPateus == 0) {
        amountOfWorstP = 0;
    }
    std::cout << numberOfPateus << " " << amountOfBestP << " " << amountOfWorstP;
    return 0;
}