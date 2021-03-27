#include <iostream>
#include <map>

int main() {
	std::map<std::string, int> mp;
	mp["four"] = 4;
	mp["five"] = 5;
	std::string g;
	std::cin >> g;
	if (mp.find(g) != mp.end()) {
		std::cout << mp[g] << std::endl;
	}
	std::cout << mp["five"] << std::endl;
	return 0;
}
