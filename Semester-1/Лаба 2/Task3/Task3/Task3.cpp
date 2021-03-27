#include <iostream>
#include <fstream>

int main()
{
	std::ifstream fin;
	std::ofstream fout; 
	fout.open("output.txt");
	fin.open("input.txt");
	long int number;
	bool isFirst = true;
	fin >> number;
	for (int i = 2; i*i <= number; i++) {
		while (number % i == 0) {
			if (isFirst) {
				isFirst = false;
				fout << i;
				number /= i;
				continue;
			}
			fout << " " << i;
			number /= i;
		}
	}
	if (number > 1 && isFirst) {
		fout << number;
	}
	else if (number > 1) {
		fout << " " << number;
	}
	fout.close();
	fin.close();
}