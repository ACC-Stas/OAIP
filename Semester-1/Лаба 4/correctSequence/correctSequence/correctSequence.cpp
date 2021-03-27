#include <iostream>
#include <string>

int main()
{
    std::string str;
    std::cin >> str;
    int k = 0, m = 0, result = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(') {
            m++;
        }
        else {
            k++;
        }
        if (k > m) {
            result += (k-m);
            k = 0;
            m = 0;
        }
        else if (k < m) {
            m = m - k;
            k = 0;
        }
        else if (k == m) {
            k = 0;
            m = 0;
        }
    }
    result += abs(m - k);
    std::cout << result;
}
