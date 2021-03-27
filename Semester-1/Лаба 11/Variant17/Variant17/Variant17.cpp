#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ofstream fout("out.txt");
	std::ifstream fin("in.txt");
	std::string line, firstWord, lastWord;
	char lastCh;
	int counter = 0;
	while (std::getline(fin, line)) {
		counter = 0;
		while (line[counter] != ' ') {
			firstWord += line[counter];
			counter++;
		}
		lastCh = firstWord[firstWord.length() - 1];
		counter = line.length() - 1;
		while (line[counter] != ' ') {
			line[counter] = lastCh;
			counter--;
		}
		fout << line << "\n";
	}
	fin.close();
	fout.close();
	return 0;
}