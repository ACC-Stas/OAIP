#pragma once
#include <iterator>
#include "Map.h"

template<class keyType>
class Set {
private:
	Map<keyType, char> bst;
public:
	Set() {
		bst = Map<keyType, char>();
	}
	Set(keyType key) {
		bst = Map<keyType, char>(key, 0);
	}
	Set(const Set& st) {
		bst = st.bst;
	}
	Set& operator=(const Set& st) {
		bst = st.bst;
		return *this;
	}
	class Iterator : std::iterator< std::bidirectional_iterator_tag, keyType> {
	private:
		keyType key;
		Map<keyType, char>* bst;
	public:
		Iterator(Map<keyType, char>* bst, keyType key) {
			this->key = key;
			this->bst = bst;
		}
		Iterator(const Iterator& it) {
			this->key = it.key;
			this->bst = it.bst;
		}
		Iterator& operator=(const Iterator& it) {
			this->key = it.key;
			this->bst = it.bst;
			return *this;
		}
		Iterator& operator++() {
			key = bst->next(key);
			return *this;
		}
		Iterator& operator--() {
			key = bst->previous(key);
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			key = bst->next(key);
			return temp;
		}
		Iterator operator--(int) {
			Iterator temp = *this;
			key = bst->previous(key);
			return temp;
		}
		bool operator==(const Iterator& it) {
			return (key == it.key && bst == it.bst);
		}
		bool operator!=(const Iterator& it) {
			return (key != it.key || bst != it.bst);
		}
		const keyType operator*() {
			return key;
		}
	};
	void insert(keyType key) {
		bst.insert(key, 0);
	}
	void erase(keyType key) {
		bst.erase(key);
	}
	void clear() {
		bst.clear();
	}
	bool find(keyType key) {
		return bst.find(key);
	}
	int Size() {
		return bst.Size();
	}
	bool empty() {
		return bst.empty();
	}
	keyType next(keyType key) {
		return bst.next(key);
	}
	keyType previous(keyType key) {
		return bst.previous(key);
	}
	Iterator begin() {
		Iterator it(&bst, bst.minimum());
		return it;
	}
	Iterator end() {
		Iterator it(&bst, bst.maximum());
		return it;
	}
};

