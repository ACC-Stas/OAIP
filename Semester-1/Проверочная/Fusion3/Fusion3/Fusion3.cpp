#include <fstream>
#include <set>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	std::multiset<int> set;
	int val;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fin >> val;
			set.insert(val);
		}
	}
	std::multiset<int>::iterator it;
	it = set.begin();
	for (int i = 0; i < set.size() - 1; i++) {
		fout << *it << " ";
		it++;
	}
	fout << *it;
}