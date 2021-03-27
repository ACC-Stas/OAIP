#include <fstream>
#include <set>
#include <string>
#include <stdlib.h>

int detectNumeral(std::string number);

int main()
{
	std::ofstream fout("out.txt");
	std::ifstream fin("in.txt");
	std::string str;
	std::set<int> st;
	int number[101][2];
	for (int i = 0; i < 101; i++) {
		number[i][0] = -1;
	}
	int counter = 0;
	while (!fin.eof()) {
		std::getline(fin, str);
		if (str == "") {
			break;
		}
		number[counter][0] = atoi(str.c_str());
		number[counter][1] = detectNumeral(str);
		st.insert(number[counter][0]);
		counter++;
	}
	std::set <int> ::iterator it = st.begin();
	while (it != st.end()) {
		for (int i = 0; i < 101; i++) {
			if (*it == number[i][0]) {
				fout << number[i][0] << ":" << number[i][1] << "\n";
				break;
			}
		}
		it++;
	}
	fin.close();
	fout.close();
	return 0;
}

int detectNumeral(std::string number) {
	int result = -1;
	int numeralsCounter[10] = { 0 };
	for (int i = 0; i < number.length(); i++) {
		switch (number[i]) {
		case '0':
			numeralsCounter[0]++;
			break;
		case '1':
			numeralsCounter[1]++;
			break;
		case '2':
			numeralsCounter[2]++;
			break;
		case '3':
			numeralsCounter[3]++;
			break;
		case '4':
			numeralsCounter[4]++;
			break;
		case '5':
			numeralsCounter[5]++;
			break;
		case '6':
			numeralsCounter[6]++;
			break;
		case '7':
			numeralsCounter[7]++;
			break;
		case '8':
			numeralsCounter[8]++;
			break;
		case '9':
			numeralsCounter[9]++;
			break;
		default:
			break;
		}
		int mostRepetition = 0;
		for (int i = 9; i >=0; i--) {
			if (mostRepetition < numeralsCounter[i]) {
				mostRepetition = numeralsCounter[i];
				result = i;
			}
		}
	}
	return result;
}