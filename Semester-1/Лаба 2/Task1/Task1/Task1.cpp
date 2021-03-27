#include <fstream>

int main()
{
	std::ofstream fout;
	std::ifstream fin;
	int number, kol = 0, sum = 0, remainder=0;
	fin.open("input.txt");
	fout.open("output.txt");
	fin >> number;
	do {
		remainder = number % 10;
		sum += remainder;
		kol++;
		number = (number - remainder) / 10;
	} while (number > 0);
	fout << kol << " " << sum;
	fin.close();
	fout.close();
	return 0;
}