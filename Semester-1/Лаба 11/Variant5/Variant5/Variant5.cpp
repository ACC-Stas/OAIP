#include <iostream>
#include <fstream>
#include <set>
#include <string>

std::string typeOfNumber(int num);

int main()
{
	std::ofstream fout("out.txt");
	std::ifstream fin("in.txt");
	std::set<int> st;
	int number = 0, n = 0;
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> number;
		st.insert(number);
	}
	std::set <int> ::iterator it = st.begin();
	if (n != 0) {
		while (it != st.end()) {
			fout << *it << ":" << typeOfNumber(*it) << "\n";
			it++;
		}
	}
	fin.close();
	fout.close();
	return 0;
}

std::string typeOfNumber(int num) {
	std::string number, result = "palindrome";
	number = std::to_string(num);
	int begin = 0, end = number.length()-1;
	while (end > begin) {
		if (number[begin] != number[end]) {
			result = "non-palindrome";
		}
		begin++;
		end--;
	}
	return result;
}