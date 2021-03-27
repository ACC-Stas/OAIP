#include <iostream>
#include <fstream>
#include <string>
#include <set>

bool isPrime(int number);

int main()
{
	std::ofstream fout("out.txt");
	std::ifstream fin("in.txt");
	std::set<int> st;
    int n, number;
    fin >> n;

    for (int i = 0; i < n; i++) {
        fin >> number;
        st.insert(number);
    }
    std::set <int> ::iterator it = st.end();
    if (n != 0) {
        it--;
        while (it != st.begin()) {
            if (isPrime(*it)) {
                fout << *it << ":prime\n";
            }
            else {
                fout << *it << ":composite\n";
            }
            it--;
        }
        it = st.begin();
        if (isPrime(*it)) {
            fout << *it << ":prime\n";
        }
        else {
            fout << *it << ":composite\n";
        }
    }
	fin.close();
	fout.close();
	return 0;
}

bool isPrime(int number) {
    bool answer = true;
    if (number == 1) {
        answer = false;
    }
    int denominator;
    denominator = sqrt(number);
    while (denominator > 1) {
        if (number % denominator == 0) {
            answer = false;
        }
        denominator--;
    }
    return answer;
}