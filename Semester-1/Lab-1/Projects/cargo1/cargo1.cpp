#include <iostream>

int main()
{
    int Q1, P1, Q2, P2, A, price = 0, minPrice = INT_MAX;
    std::cin >> Q1 >> P1 >> Q2 >> P2 >> A;
    for (int x = 0; x <= 1000; x++) {
        for (int y = 0; y <= 1000; y++) {
            if (x * Q1 + y * Q2 >= A) {
                price = x * P1 + y * P2;
                if (price < minPrice) {
                    minPrice = price;
                }
            }
        }
    }
    std::cout << minPrice;
}
