#pragma once
#include <iterator>
#include "linkedMap.h"

template<class keyType>
class linkedSet {
private:
	linkedMap<keyType, char> linkedBst;
public:
	linkedSet() {
		linkedBst = linkedMap<keyType, char>();
	}
	linkedSet(keyType key) {
		linkedBst = linkedMap<keyType, char>(key, 0);
	}
	linkedSet(const linkedSet& st) {
		linkedBst = st.linkedBst;
	}
	linkedSet& operator=(const linkedSet& st) {
		linkedBst = st.linkedBst;
		return *this;
	}
	class Iterator : std::iterator< std::bidirectional_iterator_tag, keyType> {
	private:
		keyType key;
		linkedMap<keyType, char>* linkedBst;
	public:
		Iterator(linkedMap<keyType, char>* linkedBst, keyType key) {
			this->key = key;
			this->linkedBst = linkedBst;
		}
		Iterator(const Iterator& it) {
			this->key = it.key;
			this->linkedBst = it.linkedBst;
		}
		Iterator& operator=(const Iterator& it) {
			this->key = it.key;
			this->linkedBst = it.linkedBst;
			return *this;
		}
		Iterator& operator++() {
			key = linkedBst->next(key);
			return *this;
		}
		Iterator& operator--() {
			key = linkedBst->previous(key);
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			key = linkedBst->next(key);
			return temp;
		}
		Iterator operator--(int) {
			Iterator temp = *this;
			key = linkedBst->previous(key);
			return temp;
		}
		bool operator==(const Iterator& it) {
			return (key == it.key && linkedBst == it.linkedBst);
		}
		bool operator!=(const Iterator& it) {
			return (key != it.key || linkedBst != it.linkedBst);
		}
		const keyType operator*() {
			return key;
		}
	};
	void insert(keyType key) {
		linkedBst.insert(key, 0);
	}
	void erase(keyType key) {
		linkedBst.erase(key);
	}
	void clear() {
		linkedBst.clear();
	}
	bool find(keyType key) {
		return linkedBst.find(key);
	}
	int Size() {
		return linkedBst.Size();
	}
	bool empty() {
		return linkedBst.empty();
	}
	keyType next(keyType key) {
		return linkedBst.next(key);
	}
	keyType previous(keyType key) {
		return linkedBst.previous(key);
	}
	Iterator begin() {
		Iterator it(&linkedBst, linkedBst.minimum());
		return it;
	}
	Iterator end() {
		Iterator it(&linkedBst, linkedBst.maximum());
		return it;
	}
};

