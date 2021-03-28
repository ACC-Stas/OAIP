#include <iostream>
#include <vector>

template<class keyType, class T>
class BST {
	struct Node {
		keyType key;
		T value;
		Node* rightChild; //bigger
		Node* leftChild;  //smaller
		Node* previous;
		Node* next;
		Node(keyType key, T value, Node* rightChild = nullptr, Node* leftChild = nullptr, Node* previous = nullptr, Node* next = nullptr) : key(key) {
			this->value = value;
			this->rightChild = rightChild;
			this->leftChild = leftChild;
			this->previous = previous;
			this->next = next;
		}
	};
	Node* root;
	int size;
	void clear(Node* n) {
		if (n->leftChild != nullptr) {
			clear(n->leftChild);
		}
		if (n->rightChild != nullptr) {
			clear(n->rightChild);
		}
		delete n;
	}
	void copyNode(Node& newNode, Node& oldNode) { //used only for recursion in BST constructor and operator=
		if (oldNode.rightChild != nullptr) {
			newNode.rightChild = new Node(oldNode.rightChild->key, oldNode.rightChild->value);
			copyNode(*newNode.rightChild, *oldNode.rightChild);
		}
		if (oldNode.leftChild != nullptr) {
			newNode.leftChild = new Node(oldNode.leftChild->key, oldNode.leftChild->value);
			copyNode(*newNode.leftChild, *oldNode.leftChild);
		}
	}
	void simmetricTraversal(Node* current, std::vector<Node*>& visitedNodes) {
		if (current->leftChild != nullptr) {
			simmetricTraversal(current->leftChild, visitedNodes);
		}
		visitedNodes.push_back(current);
		if (current->rightChild != nullptr) {
			simmetricTraversal(current->rightChild, visitedNodes);
		}
	}
public:
	BST() {
		root = nullptr;
		size = 0;
	}
	BST(keyType key, T value) {
		root = new Node(key, value);
		size = 1;
	}
	BST(const BST& bst) {
		this->size = bst.size;
		if (bst.size == 0) {
			root = nullptr;
			return;
		}
		root = new Node(bst.root->key, bst.root->value);
		Node* bstPtr = bst.root;
		Node* ptr = root;
		copyNode(*root, *bst.root);
		std::vector<Node*> visitedNodes;
		if (root != nullptr) {
			simmetricTraversal(root, visitedNodes);
			for (int i = 1; i < size - 1; i++) {
				visitedNodes[i]->previous = visitedNodes[i - 1];
				visitedNodes[i]->next = visitedNodes[i + 1];
			}
			if (size > 1) {
				visitedNodes[size - 1]->previous = visitedNodes[size - 2];
				visitedNodes[0]->next = visitedNodes[1];
			}
		}
	}
	BST& operator=(const BST& bst) {
		this->size = bst.size;
		if (bst.size == 0) {
			root = nullptr;
			return *this;
		}
		root = new Node(bst.root->key, bst.root->value);
		Node* bstPtr = bst.root;
		Node* ptr = root;
		copyNode(*root, *bst.root);
		std::vector<Node*> visitedNodes;
		if (root != nullptr) {
			simmetricTraversal(root, visitedNodes);
			for (int i = 1; i < size - 1; i++) {
				visitedNodes[i]->previous = visitedNodes[i - 1];
				visitedNodes[i]->next = visitedNodes[i + 1];
			}
			if (size > 1) {
				visitedNodes[size - 1]->previous = visitedNodes[size - 2];
				visitedNodes[0]->next = visitedNodes[1];
			}
		}
		return *this;
	}
	void insert(keyType key, T value) {
		bool placed = false;
		Node* ptr = root;
		if (ptr == nullptr) {
			root = new Node(key, value);
			size = 1;
			placed = true;
		}
		while (!placed) {
			if (ptr->key == key) {
				throw std::exception("There is already such key\n");
			}
			if (ptr->key < key) {
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					ptr->rightChild = new Node(key, value);
					if (ptr->next != nullptr) {
						ptr->next->previous = ptr->rightChild;
						ptr->rightChild->next = ptr->next;
					}
					ptr->next = ptr->rightChild;
					ptr->rightChild->previous = ptr;
					placed = true;
					size++;
				}
			}
			else {
				if (ptr->leftChild != nullptr) {
					ptr = ptr->leftChild;
				}
				else {
					ptr->leftChild = new Node(key, value);
					if (ptr->previous != nullptr) {
						ptr->previous->next = ptr->leftChild;
						ptr->leftChild->previous = ptr->previous;
					}
					ptr->previous = ptr->rightChild;
					ptr->rightChild->next = ptr;
					placed = true;
					size++;
				}
			}
		}
	}
	void erase(keyType key) {
		bool erased = false;
		Node* ptr = root;
		Node* ptrParent = nullptr;
		if (ptr == nullptr) {
			return;
		}
		while (!erased) {
			if (ptr->key == key) {
				size--;
				erased = true;
				if (ptrParent == nullptr) {
					if (ptr->rightChild == nullptr && ptr->leftChild == nullptr) {
						delete ptr;
						root = nullptr;
					}
					else if (ptr->rightChild == nullptr && ptr->leftChild != nullptr) {
						root = ptr->leftChild;
						delete ptr;
						root->next = nullptr;
					}
					else if (ptr->rightChild != nullptr && ptr->leftChild == nullptr) {
						root = ptr->rightChild;
						delete ptr;
						root->previous = nullptr;
					}
					else {
						Node* startingNode = root;
						Node* requiredNode = nullptr;
						Node* requiredNodeParent = root;
						startingNode = startingNode->rightChild;  //can go right only once
						if (startingNode->leftChild == nullptr) {
							requiredNode = startingNode;
						}
						else {
							do {
								requiredNodeParent = startingNode;
								startingNode = startingNode->leftChild;
								requiredNode = startingNode;
							} while (startingNode->leftChild != nullptr);
						}
						if (requiredNodeParent->rightChild == requiredNode) {
							requiredNodeParent->rightChild = requiredNode->rightChild; //there is no left child in required Node
						}
						else {
							requiredNodeParent->leftChild = requiredNode->rightChild;
						}
						requiredNode->leftChild = root->leftChild;
						requiredNode->rightChild = root->rightChild;
						root = requiredNode;
						ptr->previous->next = root;
						root->previous = ptr->previous;
						delete ptr;
					}
				}
				else {
					if (ptr->rightChild == nullptr && ptr->leftChild == nullptr) {
						if (ptrParent->rightChild == ptr) {
							ptrParent->rightChild = nullptr;
							if (ptr->next != nullptr) {
								ptr->next->previous = ptrParent;
								ptrParent->next = ptr->next;
							}
						}
						else {
							ptrParent->leftChild = nullptr;
							if (ptr->previous != nullptr) {
								ptr->previous->next = ptrParent;
								ptrParent->previous = ptr->previous;
							}
						}
						delete ptr;
					}
					else if (ptr->rightChild == nullptr && ptr->leftChild != nullptr) {
						if (ptrParent->rightChild == ptr) {
							ptrParent->rightChild = ptr->leftChild;
							if (ptr->next != nullptr) {
								ptr->next->previous = ptr->previous;
								ptr->previous->next = ptr->next;
							}
						}
						else {
							ptrParent->leftChild = ptr->leftChild;
							if (ptr->previous != nullptr) {
								ptr->previous->next = ptrParent;
								ptrParent->previous = ptr->previous;
							}
						}
						delete ptr;
					}
					else if (ptr->rightChild != nullptr && ptr->leftChild == nullptr) {
						if (ptrParent->rightChild == ptr) {
							ptrParent->rightChild = ptr->rightChild;
							if (ptr->previous != nullptr) {
								ptr->previous->next = ptr->next;
								ptr->next->previous = ptr->previous;
							}
						}
						else {
							ptrParent->leftChild = ptr->rightChild;
							if (ptr->previous != nullptr) {
								ptr->previous->next = ptr->next;
								ptr->next->previous = ptr->previous;
							}
						}
						delete ptr;
					}
					else {
						Node* startingNode = ptr;
						Node* requiredNode = nullptr;
						Node* requiredNodeParent = ptr;
						startingNode = startingNode->rightChild;  //can go right only once
						if (startingNode->leftChild == nullptr) {
							requiredNode = startingNode;
						}
						else {
							do {
								requiredNodeParent = startingNode;
								startingNode = startingNode->leftChild;
								requiredNode = startingNode;
							} while (startingNode->leftChild != nullptr);
						}
						if (requiredNodeParent->rightChild == requiredNode) {
							requiredNodeParent->rightChild = requiredNode->rightChild; //there is no left child in required Node
						}
						else {
							requiredNodeParent->leftChild = requiredNode->rightChild;
						}
						if (ptrParent->rightChild == ptr) {
							ptrParent->rightChild = requiredNode;
						}
						else {
							ptrParent->leftChild = requiredNode;
						}
						requiredNode->leftChild = ptr->leftChild;
						requiredNode->rightChild = ptr->rightChild;
						if (ptr->previous != nullptr) {
							ptr->previous->next = ptr->next;
							ptr->next->previous = ptr->previous;
						}
						delete ptr;
					}
				}
			}
			else if (ptr->key < key) {
				ptrParent = ptr;
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					erased = true;
				}
			}
			else {
				ptrParent = ptr;
				if (ptr->leftChild != nullptr) {
					ptr = ptr->leftChild;
				}
				else {
					erased = true;
				}
			}
		}
	}
	void clear() {
		size = 0;
		clear(root);
		root = nullptr;
	}
	T& at(keyType key) {
		bool found = false;
		Node* ptr = root;
		if (ptr == nullptr) {
			throw std::exception("There is no such key\n");
		}
		while (!found) {
			if (ptr->key == key) {
				found = true;
			}
			else if (ptr->key < key) {
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					throw std::exception("There is no such key\n");
				}
			}
			else {
				if (ptr->leftChild != nullptr) {
					ptr = ptr->leftChild;
				}
				else {
					throw std::exception("There is no such key\n");
				}
			}
		}
		return ptr->value;
	}
	T& operator[](keyType key) {
		bool found = false;
		Node* ptr = root;
		T* value = nullptr;
		if (ptr == nullptr) {
			root = new Node(key, T());
			size = 1;
			value = &root->value;
			found = true;
		}
		while (!found) {
			if (ptr->key == key) {
				value = &ptr->value;
				found = true;
			}
			else if (ptr->key < key) {
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					ptr->rightChild = new Node(key, T());
					if (ptr->next != nullptr) {
						ptr->next->previous = ptr->rightChild;
						ptr->rightChild->next = ptr->next;
					}
					ptr->next = ptr->rightChild;
					ptr->rightChild->previous = ptr;
					found = true;
					size++;
					value = &ptr->rightChild->value;
				}
			}
			else {
				if (ptr->leftChild != nullptr) {
					ptr = ptr->leftChild;
				}
				else {
					ptr->leftChild = new Node(key, T());
					if (ptr->previous != nullptr) {
						ptr->previous->next = ptr->leftChild;
						ptr->leftChild->previous = ptr->previous;
					}
					ptr->leftChild->next = ptr;
					ptr->previous = ptr->leftChild;
					found = true;
					size++;
					value = &ptr->leftChild->value;
				}
			}
		}
		return *value;
	}
	bool find(keyType key) {
		bool found = false;
		Node* ptr = root;
		while (!found) {
			if (ptr->key == key) {
				found = true;
			}
			else if (ptr->key < key) {
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					found = false;
					break;
				}
			}
			else {
				if (ptr->leftChild != nullptr) {
					ptr = ptr->leftChild;
				}
				else {
					found = false;
					break;
				}
			}
		}
		return found;
	}
	int Size() {
		return size;
	}
	int empty() {
		bool isEmpty = false;
		if (size == 0) {
			isEmpty = true;
		}
		return isEmpty;
	}
	keyType next(keyType key) {  //return default key value, if haven't found bigger value
		keyType requiredKey = keyType();
		Node* ptr = root;
		while (ptr != nullptr) {
			if (ptr->key <= key) {
				ptr = ptr->rightChild;
			}
			else if (ptr->key > key) {
				requiredKey = ptr->key;
				ptr = ptr->leftChild;
			}
		}
		return requiredKey;
	}
	keyType previous(keyType key) {
		keyType requiredKey = keyType();
		Node* ptr = root;
		while (ptr != nullptr) {
			if (ptr->key >= key) {
				ptr = ptr->leftChild;
			}
			else if (ptr->key < key) {
				requiredKey = ptr->key;
				ptr = ptr->rightChild;
			}
		}
		return requiredKey;
	}
	keyType minimum() {
		if (root == nullptr) {
			return keyType();
		}
		Node* current = root;
		while (current->previous != nullptr) {
			current = current->previous;
		}
		return current->key;
	}
	keyType maximum() {
		if (root == nullptr) {
			return keyType();
		}
		Node* current = root;
		while (current->next != nullptr) {
			current = current->next;
		}
		return current->key;
	}
	~BST() {
		clear();
		delete root;
	}
};

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
	try {
		std::cout << bst1.at(10) << '\n';
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
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
	std::cout << "Testing minimum\n";
	std::cout << bst3.minimum() << '\n';
	std::cout << "Testing maximum\n";
	std::cout << bst3.maximum() << '\n';
}