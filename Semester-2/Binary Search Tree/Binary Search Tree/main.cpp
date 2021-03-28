#include <iostream>
#include "BST.h"

int main() {
	BST<int, int> bst1;
	std::cout << bst1.Size() << '\n';
	std::cout << bst1.empty() << '\n';
	std::cout << "Test insert\n";
	bst1.insert(0, 0);
	bst1.insert(4, 5);
	try {
		bst1.insert(4, 6);
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
	std::cout << bst1.at(0) << '\n';
	bst1.insert(-4, 5);
	std::cout << bst1.at(-4) << '\n';
	bst1.insert(10, 8);
	std::cout << bst1.at(10) << '\n';
	bst1.insert(11, 9);
	std::cout << bst1.at(11) << '\n';
	std::cout << bst1.Size() << '\n';
	bst1.erase(0);
	try {
		std::cout << bst1.at(0) << '\n';
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
	bst1.insert(0, 5);
	std::cout << "Test erase\n";
	std::cout << bst1.at(0) << '\n';
	std::cout << bst1.at(-4) << '\n';
	std::cout << bst1.at(10) << '\n';
	std::cout << bst1.at(11) << '\n';
	bst1.erase(10);
	std::cout << '\n';
	std::cout << bst1.at(0) << '\n';
	std::cout << bst1.at(-4) << '\n';
	std::cout << bst1.at(11) << '\n';
	bst1.at(0) = 200;
	std::cout << "Test at\n";
	std::cout << bst1.at(0) << '\n';
	std::cout << "Test find\n";
	std::cout << bst1.find(-4) << '\n';
	std::cout << bst1.find(1) << '\n';
	std::cout << "Test []\n";
	std::cout << bst1[0] << '\n';
	std::cout << bst1[1] << '\n';
	bst1[1] = 15;
	std::cout << bst1[1] << '\n';
	bst1.clear();
	std::cout << bst1[1] << '\n';
	bst1.insert(5, 100);
	bst1.insert(-4, 8);
	bst1.insert(10, 5);
	bst1.insert(11, 9);
	std::cout << "Test next\n";
	std::cout << bst1.next(10) << '\n';
	std::cout << "Test previous\n";
	std::cout << bst1.previous(10) << '\n';
	std::cout << "Test copy constructor\n";
	BST<int, int> bst2(bst1);
	std::cout << "bst1:\n";
	std::cout << bst1.at(5) << '\n';
	std::cout << bst1.at(-4) << '\n';
	std::cout << bst1.at(10) << '\n';
	std::cout << bst1.at(11) << '\n';
	std::cout << "bst2:\n";
	std::cout << bst2.at(5) << '\n';
	std::cout << bst2.at(-4) << '\n';
	std::cout << bst2.at(10) << '\n';
	std::cout << bst2.at(11) << '\n';
	bst1.at(5) = 0;
	bst1.at(-4) = 0;
	bst1.at(10) = 0;
	bst1.at(11) = 0;
	std::cout << "bst1:\n";
	std::cout << bst1.at(5) << '\n';
	std::cout << bst1.at(-4) << '\n';
	std::cout << bst1.at(10) << '\n';
	std::cout << bst1.at(11) << '\n';
	std::cout << "bst2:\n";
	std::cout << bst2.at(5) << '\n';
	std::cout << bst2.at(-4) << '\n';
	std::cout << bst2.at(10) << '\n';
	std::cout << bst2.at(11) << '\n';
	std::cout << "Test operator=\n";
	BST<int, int> bst3;
	bst3 = bst2;
	std::cout << "bst2:\n";
	std::cout << bst2.at(5) << '\n';
	std::cout << bst2.at(-4) << '\n';
	std::cout << bst2.at(10) << '\n';
	std::cout << bst2.at(11) << '\n';
	std::cout << "bst3:\n";
	std::cout << bst3.at(5) << '\n';
	std::cout << bst3.at(-4) << '\n';
	std::cout << bst3.at(10) << '\n';
	std::cout << bst3.at(11) << '\n';
	bst2.at(5) = 0;
	bst2.at(-4) = 0;
	bst2.at(10) = 0;
	bst2.at(11) = 0;
	std::cout << "bst2:\n";
	std::cout << bst2.at(5) << '\n';
	std::cout << bst2.at(-4) << '\n';
	std::cout << bst2.at(10) << '\n';
	std::cout << bst2.at(11) << '\n';
	std::cout << "bst3:\n";
	std::cout << bst3.at(5) << '\n';
	std::cout << bst3.at(-4) << '\n';
	std::cout << bst3.at(10) << '\n';
	std::cout << bst3.at(11) << '\n';
}