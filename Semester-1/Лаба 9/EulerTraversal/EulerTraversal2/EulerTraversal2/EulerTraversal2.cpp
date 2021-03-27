#include <iostream>
#include <vector>
#pragma comment(linker, "/STACK:16777216")

std::vector <int> nodes[100002];
std::vector <int> resultLine;
bool visited[100002];


void getChildren(int currentParent) {
	if (!visited[currentParent]) {
		resultLine.push_back(currentParent);
		visited[currentParent] = true;
		for (int i = 0; i < nodes[currentParent].size(); i++) {
			if (!visited[nodes[currentParent][i]]) {
				getChildren(nodes[currentParent][i]);
				resultLine.push_back(currentParent);
			}
		}
	}
}

int main()
{
	int n;
	std::cin >> n;
	int parent, child;
	for (int i = 0; i < n - 1; i++) {
		std::cin >> parent >> child;
		nodes[parent].push_back(child);
		nodes[child].push_back(parent);
	}
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}
	getChildren(1);
	for (int i = 0; i < resultLine.size() - 1; i++) {
		std::cout << resultLine[i] << ' ';
	}
	std::cout << resultLine[resultLine.size() - 1];
}