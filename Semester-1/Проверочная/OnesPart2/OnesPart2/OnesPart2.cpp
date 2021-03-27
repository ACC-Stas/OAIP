#include <iostream>

int factMod(int number, int mode);
long long binaryPowerMod(long long number, long long mode, long long power);

int main()
{
	int n, mode = 7 + 1000000000, k, q;
	std::cin >> n >> k;
	q = n - k;
	long long factModN, factModK, factModQ;
	factModN = factMod(n, mode);
	factModK = factMod(k, mode);
	factModQ = factMod(q, mode);
	long long combinations, temp;
	temp = (factModK * factModQ) % mode;
	temp = binaryPowerMod(temp, mode, mode - 2);
	combinations = (factModN * temp) % mode;
	std::cout << combinations;
}

int factMod(int number, int mode) {
	long long result = 1;
	for (int i = 1; i <= number; i++) {
		result = (result * i) % mode;
	}
	return result;
}

long long binaryPowerMod(long long number, long long mode, long long power) {
	long long result;
	if (power != 1 && power%2==0) {
		result = binaryPowerMod(number, mode, power / 2);
		result = (result * result) % mode;
	}
	else if (power != 1 && power % 2 == 1) {
		result = number * binaryPowerMod(number, mode, power - 1);
		result = result % mode;
	}
	else {
		result = number % mode;
	}
	return result;
}