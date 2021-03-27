#include <iostream>
#include <fstream>

int main()
{
	std::ofstream fout("out.txt");
	std::ifstream fin("in.txt");
	int n, number, zeros = 0, ones = 0, twos = 0;
	fin >> n;
	if (n != 0) {
		for (int i = 0; i < n - 1; i++) {
			fin >> number;
			if (number % 3 == 0) {
				zeros++;
			}
			else if (number % 3 == 1) {
				ones++;
			}
			else if (number % 3 == 2) {
				twos++;
			}
			fout << number << " ";
		}
		fin >> number;
		if (number % 3 == 0) {
			zeros++;
		}
		else if (number % 3 == 1) {
			ones++;
		}
		else if (number % 3 == 2) {
			twos++;
		}
		fout << number << "\n";
		fout << zeros << " " << ones << " " << twos;
	}

	fin.close();
	fout.close();
	return 0;
}