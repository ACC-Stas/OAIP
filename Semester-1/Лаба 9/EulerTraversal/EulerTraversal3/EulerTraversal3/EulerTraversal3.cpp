#include <iostream>
#include <vector>


class EulerTraversal {
private:
	std::vector<int>* nodes;
	bool* visited;
	int n;
	std::vector<int> resultLine;
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
public:
	EulerTraversal() {
		std::cin >> n;
	}
	void build() {
		nodes = new std::vector<int>[n + 1];
		int parent, child;
		for (int i = 0; i < n - 1; i++) {
			std::cin >> parent >> child;
			nodes[parent].push_back(child);
			nodes[child].push_back(parent);
		}
		visited = new bool[n];
		for (int i = 0; i < 2 * n; i++) {
			visited[i] = false;
		}
		getChildren(1);
		for (int i = 0; i < resultLine.size() - 1; i++) {
			std::cout << resultLine[i] << " ";
		}
		std::cout << resultLine[resultLine.size() - 1];
	}
};

int main()
{
	EulerTraversal e1;
	e1.build();
	
}