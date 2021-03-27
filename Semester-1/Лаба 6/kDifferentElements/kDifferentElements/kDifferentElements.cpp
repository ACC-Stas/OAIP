#include <iostream>

int main()
{
    char str[100];
    int k = 0;  //additional counter
    for (int i = 0; i < 100; i++) {  
        str[i] = k + 33;
        k++;
        if (k == 15) {   //15 elements are required
            k = 0;
        }
    }
    for (int i = 0; i < 100; i++) {
        std::cout << str[i] << std::endl;
    }
}