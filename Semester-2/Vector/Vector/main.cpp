#include <iostream>
#include <iterator>
#include <vector>
#include <initializer_list>
#include "Vector.h"

class A {
private:
	int val;
public:
	A() {
		val = 5;
	}
	int getVal() {
		return val;
	}
};

int main() {
	Vector<int> v1(2);
	std::cout << v1[0] << "    " << v1[1] << '\n';
	Vector<int> v2{ 3 };
	std::cout << v2[0] << '\n';
	v2[0] = 15;
	std::cout << v2[0] << '\n';
	try {
		v2[4] = 8;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	for (int i = 0; i < 20; i++) {
		v1.push_back(10 + i);
		std::cout << v1.size() << " ";
	}
	std::cout << '\n';
	for (int i = 0; i < v1.size(); i++) {
		std::cout << v1[i] << " ";
	}
	std::cout << '\n';
	for (int i = 0; i < 14; i++) {
		v1.pop_back();
		std::cout << v1.size() << " ";
	}
	std::cout << '\n';
	for (int i = 0; i < v1.size(); i++) {
		std::cout << v1[i] << " ";
	}
	std::cout << '\n';
	try {
		for (int i = 0; i < 100; i++) {
			v1.pop_back();
		}
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	v1.push_back(14);
	std::cout << v1.size() << " " << v1[0] << '\n';
	v1.resize(25);
	for (int i = 0; i < v1.size(); i++) {
		std::cout << v1[i] << ' ';
	}
	std::cout << '\n';
	v1.resize(3);
	for (int i = 0; i < v1.size(); i++) {
		std::cout << v1[i] << ' ';
	}
	std::cout << '\n';
	v1.clear();
	std::cout << v1.empty() << ' ' << '\n';
	v1.push_back(64);
	std::cout << v1.empty() << ' ' << v1[0] << ' ' << v1.size() << '\n';
	v1.push_back(76);
	v1.push_back(100);
	v1.push_back(14);
	v1.push_back(5);
	Vector<int> v3 = Vector<int>(5);
	Vector<int> v4;
	v4 = v3 = v1;
	v1.clear();
	for (int i = 0; i < v4.size(); i++) {
		std::cout << v4[i] << " ";
	}
	std::cout << '\n';

	Vector<int>::Iterator it1 = v4.begin();
	Vector<int>::Iterator it2 = v1.begin();
	std::cout << *it1 << '\n';
	if (it1 == it2) {
		std::cout << "Equal1\n";
	}
	if (it1 != it2) {
		std::cout << "Anequal1\n";
	}
	if (it2 < it1) {
		std::cout << "it2 < it1\n";
		std::cout << *it2 << " < " << *it1 << '\n';
	}
	if (it1 > it2) {
		std::cout << "it1 > it2\n";
		std::cout << *it1 << " > " << *it2 << '\n';
	}
	if (it1 >= it2) {
		std::cout << "it1 >= it2\n";
		std::cout << *it1 << " >= " << *it2 << '\n';
	}
	it1 = it2;
	if (it1 == it2) {
		std::cout << "Equal2\n";
	}
	if (it1 <= it2) {
		std::cout << "it1 <= it2\n";
		std::cout << *it1 << " <= " << *it2 << '\n';
	}
	if (it1 != it2) {
		std::cout << "Anequal\n";
	}
	Vector<A> av(3);
	Vector<A>::Iterator it3 = av.begin();
	std::cout << it3->getVal() << '\n';
	Vector<double> v7;
	for (int i = 0; i < 15; i++) {
		v7.push_back(i + 1.7);
	}
	Vector<double>::Iterator it7 = v7.begin();
	for (it7 = v7.begin(); it7 != v7.end(); it7++) {
		std::cout << *it7 << " ";
	}
	std::cout << '\n';
	for (auto i : v7) {
		std::cout << i << " ";
	}
	std::cout << '\n';
	it7 = v7.begin();
	it7 = 5 + it7;
	std::cout << *it7 << '\n';
	it7 - 5;
	std::cout << *it7 << '\n';
	it7 = it7 - 5;
	std::cout << *it7 << '\n';
	it7 += 5;
	std::cout << *it7 << '\n';
	it7 -= 5;
	std::cout << *it7 << '\n';
	std::cout << it7[4] << '\n';

	std::cout << "New block\n";
	it7 = v7.begin();

	std::cout << *it7 << " ";
	std::cout << *it7++ << " ";
	std::cout << *it7 << '\n';
}