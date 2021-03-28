#pragma once

template<class keyType, class T>
class BST {
	struct Node {
		keyType key;
		T value;
		Node* rightChild; //bigger
		Node* leftChild;  //smaller
		Node(keyType key, T value, Node* rightChild = nullptr, Node* leftChild = nullptr) : key(key) {
			this->value = value;
			this->rightChild = rightChild;
			this->leftChild = leftChild;
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
					if (ptr->rightChild == nullptr && ptr->leftChild == nullptr) {
						delete ptr;
						root = nullptr;
					}
					else if (ptr->rightChild == nullptr && ptr->leftChild != nullptr) {
						root = ptr->leftChild;
						delete ptr;
					}
					else if (ptr->rightChild != nullptr && ptr->leftChild == nullptr) {
						root = ptr->rightChild;
						delete ptr;
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
						delete ptr;
					}
				}
				else {
					if (ptr->rightChild == nullptr && ptr->leftChild == nullptr) {
						if (ptrParent->rightChild == ptr) {
							ptrParent->rightChild = nullptr;
						}
						else {
							ptrParent->leftChild = nullptr;
						}
						delete ptr;
					}
					else if (ptr->rightChild == nullptr && ptr->leftChild != nullptr) {
						if (ptrParent->rightChild == ptr) {
							ptrParent->rightChild = ptr->leftChild;
						}
						else {
							ptrParent->leftChild = ptr->leftChild;
						}
						delete ptr;
					}
					else if (ptr->rightChild != nullptr && ptr->leftChild == nullptr) {
						if (ptrParent->rightChild == ptr) {
							ptrParent->rightChild = ptr->rightChild;
						}
						else {
							ptrParent->leftChild = ptr->rightChild;
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
	~BST() {
		clear();
		delete root;
	}
};
