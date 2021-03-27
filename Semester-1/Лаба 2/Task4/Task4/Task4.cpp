#include <iostream>
#include <fstream>

long long gcd(long long a, long long b);
long long lcm(long long a, long long b);

int main(){
    std::ifstream fin;
	std::ofstream fout;
	long long greatComDiv; //greatest common divisor
	long long leastComMult; //least common multiple
	long long a, b;
    fout.open("output.txt");
    fin.open("input.txt");

	fin >> a >> b;
	greatComDiv = gcd(a, b);
	leastComMult = lcm(a, b);
	fout << greatComDiv << " " << leastComMult;
	fin.close();
	fout.close();
}

long long gcd(long long a, long long b) {
	if (a < b) {
		std::swap(a, b);
	}
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}
long long lcm(long long a, long long b) {
	return a / gcd(a, b) * b;
}