#include <fstream>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	int** numbers = new int* [n];
	for (int i = 0; i < n; i++) {
		numbers[i] = new int[m];
		for (int j = 0; j < m; j++) {
			fin >> numbers[i][j];
		}
	}

	int* fusion;
	int* addLine = new int[m];
	for (int i = 0; i < m; i++) {
		addLine[i] = numbers[0][i];
	}
	int fusionCounter, addCounter, numberCounter, addLineSize = m, fusionLineSize;
	for (int i = 1; i < n; i++) {
		fusionLineSize = addLineSize + m;
		fusion = new int[fusionLineSize];
		fusionCounter = 0;
		addCounter = 0;
		numberCounter = 0;
		while (addCounter < addLineSize || numberCounter < m) {
			if (addCounter == addLineSize) {
				fusion[fusionCounter] = numbers[i][numberCounter];
				numberCounter++;
				fusionCounter++;
			}
			else if (numberCounter == m) {
				fusion[fusionCounter] = addLine[addCounter];
				addCounter++;
				fusionCounter++;
			}
			else {
				if (addLine[addCounter] < numbers[i][numberCounter]) {
					fusion[fusionCounter] = addLine[addCounter];
					addCounter++;
					fusionCounter++;
				}
				else {
					fusion[fusionCounter] = numbers[i][numberCounter];
					numberCounter++;
					fusionCounter++;
				}
			}
		}
		delete[] addLine;
		addLineSize = fusionLineSize;
		addLine = new int[addLineSize];
		for (int j = 0; j < fusionLineSize; j++) {
			addLine[j] = fusion[j];
		}
		delete[] fusion;
	}
	for (int i = 0; i < addLineSize - 1; i++) {
		fout << addLine[i] << " ";
	}
	fout << addLine[addLineSize - 1];
	fin.close();
	fout.close();
	return 0;
}