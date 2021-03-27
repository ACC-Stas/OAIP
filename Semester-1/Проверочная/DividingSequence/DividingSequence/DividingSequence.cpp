#include <iostream>

int main()
{
	int n;
	std::cin >> n;
	int* elements = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> elements[i];
	}
	int* dividingLength = new int[n];
	dividingLength[0] = 1;
	for (int i = 1; i < n; i++) {
		dividingLength[i] = 1;
		for (int j = i - 1; j >= 0; j--) {
			if (elements [j] != 0 && elements[i] % elements[j] == 0 && dividingLength[i] < dividingLength[j] + 1) {
				dividingLength[i] = dividingLength[j] + 1;
			}
		}
	}
	int maxLength = 0;
	for (int i = 0; i < n; i++) {
		if (maxLength < dividingLength[i]) {
			maxLength = dividingLength[i];
		}
	}
	std::cout << n - maxLength;
}