#pragma once

#include <forward_list>
#include <string>

template <class KeyType, class T, class Hasher = std::hash<KeyType>>
class HashTable {
private:
	Hasher hash;
	size_t size;
	const size_t maxBatchSize;
	std::forward_list<std::pair<const KeyType, T>>* elements;
public:
	HashTable(size_t size = 1, size_t maxBatchSize = 2) : maxBatchSize(maxBatchSize) {
		if (maxBatchSize == 0) {
			throw std::exception("Batch size can't be 0\n");
		}
		if (size == 0) {
			throw std::exception("Size can't be 0\n");
		}
		this->size = size;
		elements = new std::forward_list<std::pair<const KeyType, T>>[size];
		for (int i = 0; i < size; i++) {
			elements[i] = std::forward_list<std::pair<const KeyType, T>>();
		}
	}
	HashTable(const HashTable& ht) : maxBatchSize(ht.maxBatchSize) {
		this->operator=(ht);
	}
	HashTable& operator=(const HashTable& ht) {
		size = ht.size;
		elements = new std::forward_list<std::pair<const KeyType, T>>[size];
		for (int i = 0; i < size; i++) {
			elements[i] = std::forward_list<std::pair<const KeyType, T>>();
		}
		for (int i = 0; i < ht.size; i++) {
			for (auto it : ht.elements[i]) {
				insert(it.first, it.second);
			}
		}
		return *this;
	}
	T& operator[](const KeyType key) {
		int position = hash(key) % size;
		for (auto it = elements[position].begin(); it != elements[position].end(); it++) {
			if ((*it).first == key) {
				return (*it).second;
			}
		}
		insert(key, T());
		for (auto it = elements[position].begin(); it != elements[position].end(); it++) {
			if ((*it).first == key) {
				return (*it).second;
			}
		}
	}
	T operator[](const KeyType key) const {
		int position = hash(key) % size;
		for (auto it = elements[position].begin(); it != elements[position].end(); it++) {
			if ((*it).first == key) {
				return (*it).second;
			}
		}
		throw std::exception("There is no such element\n");
	}
	void insert(const KeyType key, T value) {
		int position = hash(key) % size;
		int counter = 0;
		for (auto it : elements[position]) {
			if (it.first == key) {
				throw std::exception("Already have such key\n");
			}
			counter++;
		}
		elements[position].push_front(std::pair<const KeyType, T>(key, value));
		counter++;
		if (counter > maxBatchSize) {
			rehash(2 * size);
		}
	}
	void rehash(size_t newSize) {
		if (newSize == 0) {
			throw std::exception("Size can't be 0\n");
		}
		std::forward_list<std::pair<const KeyType, T>>* oldelements = elements;
		elements = new std::forward_list<std::pair<const KeyType, T>>[newSize];
		for (int i = 0; i < newSize; i++) {
			elements[i] = std::forward_list<std::pair<const KeyType, T>>();
		}
		int oldSize = size;
		size = newSize;
		for (int i = 0; i < oldSize; i++) {
			for (auto it : oldelements[i]) {
				insert(it.first, it.second);
			}
		}
		delete[] oldelements;
	}
	void erase(const KeyType key) {
		int position = hash(key) % size;
		auto previousIt = elements[position].end();
		for (auto it = elements[position].begin(); it != elements[position].end(); it++) {
			if ((*it).first == key) {
				if (previousIt != elements[position].end()) {
					elements[position].erase_after(previousIt);
					break;
				}
				else {
					elements[position].pop_front();
					break;
				}
			}
			previousIt = it;
		}
	}
	std::string toString() { //used for debug
		std::string b;
		for (int i = 0; i < size; i++) {
			for (auto it : elements[i]) {
				b += "first = " + std::to_string(it.first) + " second = " + std::to_string(it.second) + ", ";
			}
		}
		return b;
	}
	bool contains(KeyType key) {
		bool find = false;
		int position = hash(key) % size;
		for (auto it : elements[position]) {
			if (it.first == key) {
				find = true;
			}
		}
		return find;
	}
	void clear() {
		delete[] elements;
		size = 1;
		elements = new std::forward_list<std::pair<const KeyType, T>>[size];
	}
	~HashTable() {
		delete[] elements;
	}
};
