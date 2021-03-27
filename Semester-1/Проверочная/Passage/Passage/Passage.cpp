#include <iostream>
#include <algorithm>
#include <fstream>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	int** penalty = new int* [n];
	for (int i = 0; i < n; i++) {
		penalty[i] = new int[m];
		for (int j = 0; j < m; j++) {
			fin >> penalty[i][j];
		}
	}

	int min = 0;
	if (m == 1) {
		for (int i = 0; i < n; i++) {
			min += penalty[i][0];
		}
	}
	else {
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (j == 0) {
					penalty[i][j] = penalty[i][j] + std::min(penalty[i - 1][j], penalty[i - 1][j + 1]);
					std::cout << penalty[i][j] << " ";
				}
				else if (j == m - 1) {
					penalty[i][j] = penalty[i][j] + std::min(penalty[i - 1][j - 1], penalty[i - 1][j]);
					std::cout << penalty[i][j] << " ";
				}
				else {
					penalty[i][j] = penalty[i][j] + std::min(penalty[i - 1][j - 1], std::min(penalty[i - 1][j], penalty[i - 1][j + 1]));
					std::cout << penalty[i][j] << " ";
				}
			}
		}

		min = INT_MAX;
		for (int i = 0; i < m; i++) {
			if (min > penalty[n - 1][i]) {
				min = penalty[n - 1][i];
			}
		}
	}

	fout << min;
	fin.close();
	fout.close();
	for (int i = 0; i < n; i++) {
		delete[] penalty[i];
	}
	delete[] penalty;
	return 0;
}