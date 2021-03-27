#include <iostream>
#include <iterator>
#include <initializer_list>
#include "List.h"

int main() {
	List<int> l;
	l.push_back(5);
	l.push_back(10);
	l.push_back(15);
	l.push_font(20);
	std::cout << l.size() << '\n';
	l.print();
	l.pop_front();
	l.print();
	l.pop_back();
	l.print();
	l.pop_front();
	l.print();
	l.pop_front();
	l.print();
	try {
		l.pop_front();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	l.push_back(40);
	l.print();
	List<int> l1 { 4,5,6,7,8,9,10 };
	l1.print();
	List<int>::Iterator it1 = l1.begin();
	List<int>::Iterator it2 = it1;
	List<int>::Iterator it3;
	it3 = it1;
	std::cout << *it1 << " " << *it2 << " " << *it3 << '\n';
	it1++;
	++it1;
	std::cout << *it1 << '\n';
	it1--;
	--it1;
	std::cout << *it1 << '\n';
	for (auto t0 : l1) {
		std::cout << t0 << " ";
	}
	std::cout << '\n';
	List<int> l2 = l1;
	l2.print();
	List<int> l3;
	l3 = l2;
	l3.print();
}