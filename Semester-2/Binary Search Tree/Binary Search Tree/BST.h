#pragma once

template<class keyType, class T>
class BST {
	struct Node {
		keyType key;
		T value;
		Node* rightChild; //bigger
		Node* leftChild;  //smaller
		Node(keyType key, T value, Node* rightChild = nullptr, Node* leftChild = nullptr) {
			this->key = key;
			this->value = value;
			this->rightChild = rightChild;
			this->leftChild = leftChild;
		}
	};
	Node* root;
	int size;
	void insertNode(Node& node) {
		bool placed = false;
		Node* ptr = root;
		while (!placed) {
			if (ptr->key < node.key) {
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					ptr->rightChild = &node;
					placed = true;
				}
			}
			else {
				if (ptr->leftChild != nullptr) {
					ptr = ptr->leftChild;
				}
				else {
					ptr->leftChild = &node;
					placed = true;
				}
			}
		}
	}
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
public:
	BST() {
		root = nullptr;
		size = 0;
	}
	BST(keyType key, T value) {
		root = new Node(key, value);
		size = 1;
	}
public:
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
					if (ptr->rightChild != nullptr) {
						root = ptr->rightChild;
						if (ptr->leftChild != nullptr) {
							insertNode(*ptr->leftChild);
						}
						delete ptr;
					}
					else {
						root = ptr->leftChild;
						delete ptr;
					}
				}
				else {
					if (ptrParent->leftChild == ptr) {
						ptrParent->leftChild = nullptr;
					}
					else {
						ptrParent->rightChild = nullptr;
					}
					if (ptr->rightChild != nullptr) {
						insertNode(*ptr->rightChild);
					}
					if (ptr->leftChild != nullptr) {
						insertNode(*ptr->leftChild);
					}
					delete ptr;
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
	keyType upper_bound(keyType key) {  //return default key value, if haven't found bigger value
		bool found = false;
		keyType requiredKey;
		Node* ptr = root;
		if (ptr == nullptr) {
			found = true;
			requiredKey = keyType();
		}
		while (!found) {
			if (ptr->key <= key) {
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					requiredKey = keyType();
					found = true;
				}
			}
			else if (ptr->key > key) {
				found = true;
				requiredKey = ptr->key;
			}
		}
		return requiredKey;
	}
	keyType lower_bound(keyType key) {
		bool found = false;
		keyType requiredKey;
		Node* ptr = root;
		if (ptr == nullptr) {
			found = true;
			requiredKey = keyType();
		}
		while (!found) {
			if (ptr->key < key) {
				if (ptr->rightChild != nullptr) {
					ptr = ptr->rightChild;
				}
				else {
					requiredKey = keyType();
					found = true;
				}
			}
			else if (ptr->key >= key) {
				found = true;
				requiredKey = ptr->key;
			}
		}
		return requiredKey;
	}
	~BST() {
		clear();
		delete root;
	}
};
