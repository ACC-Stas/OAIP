#include <iostream>

int main()
{
	int N, K, remainderN, remainderK;
	int repeatingDecimal1[6] = { 7,1,4,2,8,5 };
	int repeatingDecimal2[6] = { 4,2,8,5,7,1 };
	int repeatingDecimal3[6] = { 1,4,2,8,5,7 };
	int repeatingDecimal4[6] = { 8,5,7,1,4,2 };
	int repeatingDecimal5[6] = { 5,7,1,4,2,8 };
	int repeatingDecimal6[6] = { 2,8,5,7,1,4 };
	std::cin >> N >> K;
	remainderK = K % 7;
	remainderN = N % 6;
	switch (remainderK) {
	case (1): {
		std::cout << repeatingDecimal1[remainderN];
		break;
	}
	case (2): {
		std::cout << repeatingDecimal2[remainderN];
		break;
	}
	case (3): {
		std::cout << repeatingDecimal3[remainderN];
		break;
	}
	case (4): {
		std::cout << repeatingDecimal4[remainderN];
		break;
	}
	case (5): {
		std::cout << repeatingDecimal5[remainderN];
		break;
	}
	case (6): {
		std::cout << repeatingDecimal6[remainderN];
		break;
	}
	default: {
		std::cout << 0;
		break;
	}
	}
}