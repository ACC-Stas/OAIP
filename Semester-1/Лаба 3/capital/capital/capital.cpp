#include <iostream>
#include <string>

int main()
{
    int a, n;
    std::cin >> a >> n;
    std::string bStr;
    bool possible = true;
    for (int i = 0; i < n; i++) {
        if (a > 9) {
            bStr = bStr + '9';
            a -= 9;
        }
        else {
            bStr = bStr + std::to_string(a);
            a = 0;
        }
        if (a>0 && i == n-1) {
            possible = false;
            break;
        }
    }
    if (possible) {
        std::cout << bStr;
    }
    else {
        std::cout << -1;
    }
    return 0;
}
