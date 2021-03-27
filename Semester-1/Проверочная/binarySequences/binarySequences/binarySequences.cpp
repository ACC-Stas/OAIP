#include <iostream>
#include <string>
#include <algorithm>

int main()
{
	int size1, size2;
	std::cin >> size1 >> size2;
	std::string str1, str2;
	std::cin >> str1;
	std::cin >> str2;
	int counter = 0, counterOfZeros = 0;
	while (str1[counter] == '0') {
		counterOfZeros++;
		counter++;
	}
	str1 = str1.substr(counterOfZeros, size1);
	size1 = size1 - counterOfZeros;
	counter = 0, counterOfZeros = 0;
	while (str2[counter] == '0') {
		counterOfZeros++;
		counter++;
	}
	str2 = str2.substr(counterOfZeros, size2);
	size2 = size2 - counterOfZeros;
	std::cout << str1 << " " << size1 << "\n";
	std::cout << str2 << " " << size2 << "\n";

	int** lcs = new int* [size1+1];
	for (int i = 0; i <= size1; i++) {
		lcs[i] = new int[size2+1];
	}
	lcs[0][0] = 0;
	for (int i = 1; i <= size2; i++) {
		lcs[0][i] = 0;
	}
	for (int i = 1; i <= size1; i++) {
		lcs[i][0] = 0;
	}

	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			if (str1[i] == str2[j]) {
				lcs[i+1][j+1] = lcs[i][j] + 1;
			}
			else {
				lcs[i+1][j+1] = std::max(lcs[i][j+1], lcs[i+1][j]);
			}
			std::cout << lcs[i+1][j+1] << " ";
		}
		std::cout << "\n";
	}
	std::cout << lcs[size1][size2] << "\n";
	int resultSize, position1 = size1, position2 = size2;
	resultSize = lcs[size1][size2];
	std::string resultLine = "";
	bool reachedOne, reachedZero;
	for (int i = resultSize; i > 0; i--) {
		reachedOne = false;
		reachedZero = false;
		for (int j = position1; j > 0; j--) {
			for (int k = position1; k > 0; k--) {
				if (lcs[j][k] == i && str1[j-1] == str2[k-1] && str1[j-1] == '1') {
					reachedOne = true;
					position1 = j - 1;
					position2 = k - 1;
					resultLine = '1' + resultLine;
					break;
				}
			}
			if (reachedOne) {
				break;
			}
		}
		if (!reachedOne) {
			for (int j = position1; j > 0; j--) {
				for (int k = position1; k > 0; k--) {
					if (lcs[j][k] == i && str1[j - 1] == str2[k - 1] && str1[j - 1] == '0') {
						reachedZero = true;
						position1 = j - 1;
						position2 = k - 1;
						resultLine = '0' + resultLine;
						break;
					}
				}
				if (reachedZero) {
					break;
				}
			}
		}

	}

	std::cout << resultLine;
	return 0;
}