#include <iostream>
#include <iomanip>

int main()
{
	double a, b, c, result;
	std::cin >> a >> b >> c;
	result = b + c - a;
	std::cout << std::setprecision(4) << result;
	return 0;
}