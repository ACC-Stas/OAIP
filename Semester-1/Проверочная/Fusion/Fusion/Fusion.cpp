#include <vector>
#include <fstream>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	std::vector<std::vector<int>> numbers;
	int val;
	for (int i = 0; i < n; i++) {
		numbers.push_back(std::vector<int>());
		for (int j = 0; j < m; j++) {
			fin >> val;
			numbers[i].push_back(val);
		}
	}
	std::vector<std::vector<int>> fusion;
	int counter1, counter2;
	while (numbers.size() != 1) {
		for (int i = 0; i < numbers.size() - 1; i += 2) {
			counter1 = 0;
			counter2 = 0;
			fusion.push_back(std::vector<int>());
			while (counter1 < numbers[i].size() || counter2 < numbers[i + 1].size()) {
				if (counter1 == numbers[i].size()) {
					fusion[fusion.size() - 1].push_back(numbers[i + 1][counter2]);
					counter2++;
				}
				else if (counter2 == numbers[i + 1].size()) {
					fusion[fusion.size() - 1].push_back(numbers[i][counter1]);
					counter1++;
				}
				else {
					if (numbers[i][counter1] >= numbers[i + 1][counter2]) {
						fusion[fusion.size() - 1].push_back(numbers[i + 1][counter2]);
						counter2++;
					}
					else {
						fusion[fusion.size() - 1].push_back(numbers[i][counter1]);
						counter1++;
					}
				}
			}
		}
		if (numbers.size() % 2 == 1) {
			fusion.push_back(std::vector<int>());
			for (int i = 0; i < numbers[numbers.size() - 1].size(); i++) {
				fusion[fusion.size() - 1] = numbers[numbers.size() - 1];
			}
		}
		numbers = fusion;
		fusion.clear();
	}
	for (int i = 0; i < numbers[0].size() - 1; i++) {
		fout << numbers[0][i] << " ";
	}
	fout << numbers[0][numbers[0].size() - 1];
	fin.close();
	fout.close();
	return 0;
}