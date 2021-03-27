#include <algorithm>
#include <fstream>

int numbers[1000001];

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fin >> numbers[i * m + j];
		}
	}
	std::shuffle(numbers, numbers + n * m, 1);
	std::sort(numbers, numbers + n*m);
	for (int i = 0; i < n * m - 1; i++) {
		fout << numbers[i] << " ";
	}
	fout << numbers[n * m - 1];
	fin.close();
	fout.close();
	return 0;
}