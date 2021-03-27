#include <iostream>
#include <fstream>
#include <set>
#include <string>

std::string typeOfNumber(int number);

int main()
{
	std::ofstream fout("out.txt");
	std::ifstream fin("in.txt");
	std::set<int> st;
	int number = 0;
	while (!fin.eof()) {
		fin >> number;
		st.insert(number);
	}
	std::set <int> ::iterator it = st.begin();
	if (*it != 0) {
		while (it != st.end()) {
			fout << *it << ":" << typeOfNumber(*it) << "\n";
			it++;
		}
	}
	fin.close();
	fout.close();
	return 0;
}

std::string typeOfNumber(int number) {
	int determinant = 1;
	long long sum = 0;
	std::string result;
	for (determinant; determinant * 2 <= number; determinant++) {
		if (number % determinant == 0) {
			sum += determinant;
		}
	}
	if (sum == number) {
		result = "perfect";
	}
	else if (sum < number) {
		result = "deficient";
	}
	else if (sum > number) {
		result = "abundant";
	}
	return result;
}