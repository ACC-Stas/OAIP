#include <iostream>
#include <string>

int main()
{
	std::string str[50];
	int k = 15;
	for (int i = 0; i < k+10; i++) {
		str[i] = '(';
		str[49 - i] = ')';
	}
	for (int i = 0; i < 50; i++) {
		std::cout << str[i];
	}
}
