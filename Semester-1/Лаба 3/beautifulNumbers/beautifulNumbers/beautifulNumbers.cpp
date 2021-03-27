#include <iostream>
#include <string>

int main()
{
    int N;
    std::cin >> N;
    int NumberOfBeauty = 0;
    std::string number;
    bool isSuperPrime;
    for (int i = 0; i < N; i++) {
        std::cin >> number;
        isSuperPrime = true;
        for (int j = 1; j <= number.size(); j++) {
            if ((number[number.size() - j] % 2 == 1) && (j % 2 == 0)) {
                isSuperPrime = false;
                break;
            }
            else if ((number[number.size() - j] % 2 == 0) && (j % 2 == 1)) {
                isSuperPrime = false;
                break;
            }
        }
        if (isSuperPrime) {
            NumberOfBeauty++;
        }
        number.clear();
    }
    std::cout << NumberOfBeauty;
    return 0;
}