#include <iostream>
#include <algorithm>

short numbers[1001][1001];

int main()
{
	short n, m;
	std::cin >> n >> m;
	int result = 0;
	for (short i = n-1; i >= 0; i--) {
		for (short j = m-1; j >= 0; j--) {
			std::cin >> numbers[i][j];
			if ((j == m - 1 || i == n -1) && numbers[i][j] == 1) {
				result++;
			}
			else if (numbers[i][j] == 1) {
				numbers[i][j] = std::min(std::min(numbers[i + 1][j + 1], numbers[i + 1][j]), numbers[i][j + 1]) + 1;
				result += numbers[i][j];
			}
		}
	}
	std::cout << result;
	return 0;
}