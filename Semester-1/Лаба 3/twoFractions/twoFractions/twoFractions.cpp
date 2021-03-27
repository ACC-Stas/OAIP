#include <iostream>

int main()
{
	long long numerator1, denominator1, numerator2, denominator2, difference;
	std::cin >> numerator1 >> denominator1;
	std::cin >> numerator2 >> denominator2;
	difference = numerator1 * denominator2 - numerator2 * denominator1;
	if (denominator1 > 0 && denominator2 < 0) {
		difference = (-1) * difference;
	}
	else if (denominator1 < 0 && denominator2 > 0) {
		difference = (-1) * difference;
	}
	if (difference > 0) {
		std::cout << 1;
	}
	else if (difference < 0) {
		std::cout << -1;
	}
	else {
		std::cout << 0;
	}
	return 0;
}