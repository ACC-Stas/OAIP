#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
#include <set>

int main()
{
	int n;
	std::cin >> n;
	int minimumNumber = INT_MAX;

	std::string command;
	std::deque<int> list;
	std::multiset<int> multSet;
	int number;
	for (int i = 0; i < n; i++) {
		std::cin >> command;
		if (command == "+L") {
			std::cin >> number;
			list.push_front(number);
			multSet.insert(number);
			if (number < minimumNumber) {
				minimumNumber = number;
			}
			std::cout << minimumNumber << "\n";
		}
		else if (command == "+R") {
			std::cin >> number;
			list.push_back(number);
			multSet.insert(number);
			if (number < minimumNumber) {
				minimumNumber = number;
			}
			std::cout << minimumNumber << "\n";
		}
		else if (command == "-L") {
			if (list.size() == 1) {
				multSet.erase(multSet.find(list.front()));
				list.pop_front();
				minimumNumber = INT_MAX;
				std::cout << -1 << "\n";
			}
			else if (list.size() == 0) {
				minimumNumber = INT_MAX;
				std::cout << -1 << "\n";
			}
			else {
				multSet.erase(multSet.find(list.front()));
				if (list.front() == minimumNumber) {
					list.pop_front();
					minimumNumber = *multSet.begin();
				}
				else {
					list.pop_front();
				}
				std::cout << minimumNumber << "\n";
			}
		}
		else if (command == "-R") {
			if (list.size() == 1) {
				multSet.erase(multSet.find(list.back()));
				list.pop_back();
				minimumNumber = INT_MAX;
				std::cout << -1 << "\n";
			}
			else if (list.size() == 0) {
				minimumNumber = INT_MAX;
				std::cout << -1 << "\n";
			}
			else {
				multSet.erase(multSet.find(list.back()));
				if (list.back() == minimumNumber) {
					list.pop_back();
					minimumNumber = *multSet.begin();
				}
				else {
					list.pop_back();
				}
				std::cout << minimumNumber << "\n";
			}
		}
	}
}
