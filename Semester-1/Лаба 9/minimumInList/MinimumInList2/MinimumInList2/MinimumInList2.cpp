#include <iostream>
#include <map>
#include <set>
#include <string>
#include <deque>
#include <stdio.h>

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::iostream::sync_with_stdio(0);
	std::cout.tie(0);
	std::map <int, int> quantityOfNumber;
	std::set <int> set;
	int q;
	std::cin >> q;
	std::string command;
	std::deque<int> list;
	int number;
	std::map<int, int>::iterator it;
	for (int i = 0; i < q; i++) {
		std::cin >> command;
		if (command == "+R") {
			std::cin >> number;
			list.push_back(number);
			set.insert(number);
			if (quantityOfNumber.find(number) == quantityOfNumber.end()) {
				quantityOfNumber.emplace(number, 1);
			}
			else {
				it = quantityOfNumber.find(number);
				it->second++;
			}
			std::cout << *set.begin() << "\n";
		}
		else if (command == "+L") {
			std::cin >> number;
			list.push_front(number);
			set.insert(number);
			if (quantityOfNumber.find(number) == quantityOfNumber.end()) {
				quantityOfNumber.emplace(number, 1);
			}
			else {
				it = quantityOfNumber.find(number);
				it->second++;
			}
			std::cout << *set.begin() << "\n";
		}
		else if (command == "-R") {
			if (list.size() == 1) {
				set.erase(list.back());
				quantityOfNumber.erase(quantityOfNumber.find(list.back()));
				list.pop_back();
				std::cout << -1 << "\n";
			}
			else if (list.size() == 0) {
				std::cout << -1 << "\n";
			}
			else {
				it = quantityOfNumber.find(list.back());
				if (it->second == 1) {
					set.erase(list.back());
					quantityOfNumber.erase(quantityOfNumber.find(list.back()));
					list.pop_back();
					std::cout << *set.begin() << "\n";
				}
				else {
					it->second--;
					list.pop_back();
					std::cout << *set.begin() << "\n";
				}
			}
		}
		else if (command == "-L") {
			if (list.size() == 1) {
				set.erase(list.front());
				quantityOfNumber.erase(quantityOfNumber.find(list.front()));
				list.pop_front();
				std::cout << -1 << "\n";
			}
			else if (list.size() == 0) {
				std::cout << -1 << "\n";
			}
			else {
				it = quantityOfNumber.find(list.front());
				if (it->second == 1) {
					set.erase(list.front());
					quantityOfNumber.erase(quantityOfNumber.find(list.front()));
					list.pop_front();
					std::cout << *set.begin() << "\n";
				}
				else {
					it->second--;
					list.pop_front();
					std::cout << *set.begin() << "\n";
				}
			}
		}
	}
}