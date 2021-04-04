#include <iostream>
#include "Header.h"

int main() {
	HashTable<int, int> hs;
	std::cout << "Testing insert and rehash\n";
	hs.insert(5, 5);
	try {
		hs.insert(5, 6);
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
	hs.insert(6, 10);
	hs.insert(10, 8);
	std::cout << hs.toString() << '\n';
	std::cout << "\nTesting erase\n";
	hs.erase(10);
	std::cout << hs.toString() << '\n';
	hs.erase(0);
	std::cout << hs.toString() << '\n';
	hs.erase(6);
	std::cout << hs.toString() << '\n';
	hs.erase(5);
	std::cout << hs.toString() << '\n';
	std::cout << "Testing insert after erase\n";
	hs.insert(18, 25);
	std::cout << hs.toString() << '\n';
	hs.insert(145, 14);
	std::cout << hs.toString() << '\n';
	hs.insert(6, 10);
	hs.insert(10, 8);
	hs.insert(5, 5);
	std::cout << hs.toString() << '\n';
	std::cout << "Testing clear\n";
	hs.clear();
	std::cout << hs.toString() << '\n';
	hs.insert(15, 15);
	hs.insert(10, 20);
	hs.insert(145, 25);
	hs.insert(0, 3);
	std::cout << hs.toString() << '\n';
	std::cout << "Testing containts\n";
	std::cout << hs.contains(145) << '\n';
	std::cout << hs.contains(66) << '\n';
	std::cout << "Testing operator =\n";
	HashTable<int, int> hs2;
	hs2 = hs;
	std::cout << hs2.toString() << '\n';
	std::cout << "Testing copy constructor\n";
	HashTable<int, int> hs3(hs2);
	std::cout << hs3.toString() << '\n';
	std::cout << "Testing operator[]\n";
	std::cout << hs[0] << '\n';
	std::cout << hs[8] << '\n';
	hs[8] = 15;
	std::cout << hs[8] << '\n';
	hs[202] = 43;
	std::cout << hs[202] << '\n';
}