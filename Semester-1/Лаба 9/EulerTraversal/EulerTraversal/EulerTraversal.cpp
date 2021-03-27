#include <iostream>
#include <vector>


void getChildren(std::vector<int> *nodes, std::vector<int>* resultLine, int currentParent, bool* visited) {
	if (!visited[currentParent]) {
		resultLine->push_back(currentParent);
		visited[currentParent] = true;
		for (int i = 0; i < nodes[currentParent].size(); i++) {
			if (!visited[nodes[currentParent][i]]) {
				getChildren(nodes, resultLine, nodes[currentParent][i], visited);
				resultLine->push_back(currentParent);
			}
		}
	}
}


int main()
{


	int n;
	std::cin >> n;
	std::vector<int> *nodes = new std::vector<int>[n+1];         //массив векторов
	int parent, child;
	for (int i = 0; i <n - 1; i++) {
		std::cin >> parent >> child;
		nodes[parent].push_back(child);
		nodes[child].push_back(parent);
	}
	bool* visited = new bool[n];
	for (int i = 0; i < 2 * n; i++) {
		visited[i] = false;
	}
	std::vector<int> resultLine;
	getChildren(nodes, &resultLine, 1, visited);              //первая вершина - 1
	for (int i = 0; i < resultLine.size() - 1; i++) {
		std::cout << resultLine[i] << " ";
	}
	std::cout << resultLine[resultLine.size()-1];
}