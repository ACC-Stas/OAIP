#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <initializer_list>

template <class T>
class Vector {
private:
	int length;
	int capacity;
	T* content;
public:
	class Iterator;
	Vector(int length = 0, T def = T());
	Vector(const std::initializer_list<T>& list);
	Vector(const Vector& v);
	T& operator[](int index);
	Vector<T>& operator=(const Vector& v);
	void pop_back();
	void push_back(T value);
	void resize(int length);
	void clear();
	int size();
	bool empty();
	Iterator begin();
	Iterator end();
	~Vector();
};

template <class T>
class Vector<T>::Iterator : std::iterator<std::random_access_iterator_tag, T> {
private:
	T* ptr;
public:
	Iterator();
	Iterator(T* ptr);
	Iterator(const Iterator& it);
	Iterator& operator=(const Iterator& it);
	Iterator& operator++();
	Iterator& operator--();
	Iterator operator++(int);
	Iterator operator--(int);
	Iterator operator+(int val);
	friend Iterator operator+(int val, Iterator& it) {
		Iterator temp = it;
		temp.ptr += val;
		return temp;
	}
	Iterator operator+=(int val);
	Iterator operator-(int val);
	Iterator operator-=(int val);
	bool operator==(const Iterator& it);
	bool operator!=(const Iterator& it);
	bool operator<(const Iterator& it);
	bool operator<=(const Iterator& it);
	bool operator>(const Iterator& it);
	bool operator>=(const Iterator& it);
	T operator*();
	T operator[](int index);
	T* operator->();
	~Iterator();
};

template<class T>void Vector<T>::push_back(T value) {
	length++;
	if (length > capacity) {
		capacity *= 2;
		T* temp = new T[capacity];
		for (int i = 0; i < length - 1; i++) {
			temp[i] = content[i];
		}
		delete[] content;
		content = temp;
	}
	content[length - 1] = value;
}
template<class T>void Vector<T>::pop_back() {
	if (length == 0) {
		throw std::exception("Vector is already empty");
	}
	length--;
	if (capacity / 2 > length) {
		T* temp = new T[capacity];
		for (int i = 0; i < length; i++) {
			temp[i] = content[i];
		}
		delete[] content;
		content = temp;
	}
}
template<class T>void Vector<T>::resize(int length) {
	while (length > this->length) {
		push_back(0);
	}
	while (length < this->length) {
		pop_back();
	}
}
template<class T>void Vector<T>::clear() {
	capacity = 2;
	T* temp = new T[capacity];
	temp[0] = 0;
	temp[1] = 0;
	delete[] content;
	length = 0;
	content = temp;
}
template<class T>int Vector<T>::size() {
	return length;
}
template<class T>bool Vector<T>::empty() {
	bool isEmpty = false;
	if (length == 0) {
		isEmpty = true;
	}
	return isEmpty;
}
template<class T>Vector<T>::Vector(int length, T def) {
	this->length = length;
	capacity = 2;
	while (capacity < length) {
		capacity *= 2;
	}
	content = new T[capacity];
	for (int i = 0; i < length; i++) {
		content[i] = def;
	}
}
template<class T>Vector<T>::Vector(const std::initializer_list<T>& list) {
	capacity = 2;
	while (capacity < list.size()) {
		capacity *= 2;
	}
	length = list.size();
	content = new T[capacity];
	auto it = list.begin();
	for (int i = 0; it != list.end(); i++) {
		content[i] = *it;
		it++;
	}
}
template<class T>Vector<T>::Vector(const Vector& v) {
	length = v.length;
	capacity = v.capacity;
	content = new T[capacity];
	for (int i = 0; i < length; i++) {
		content[i] = v.content[i];
	}
}
template<class T>Vector<T>::~Vector() {
	delete[] content;
}
template<class T> T& Vector<T>::operator[](int index) {
	if (index < 0 || index >= length) {
		throw std::exception("Index is out of range");
	}
	return content[index];
}
template<class T> Vector<T>& Vector<T>::operator=(const Vector& v) {
	delete[] content;
	length = v.length;
	capacity = v.capacity;
	content = new T[capacity];
	for (int i = 0; i < length; i++) {
		content[i] = v.content[i];
	}
	return *this;
}

template<class T> Vector<T>::Iterator::Iterator() {
	ptr = nullptr;
}
template<class T> Vector<T>::Iterator::Iterator(T* ptr) {
	this->ptr = ptr;
}
template<class T> Vector<T>::Iterator::Iterator(const Iterator& it) {
	ptr = it.ptr;
}
template<class T> Vector<T>::Iterator::~Iterator() {
	ptr = nullptr;
}
template<class T> typename Vector<T>::Iterator Vector<T>::begin() {
	return Iterator(content);
}
template<class T> typename Vector<T>::Iterator Vector<T>::end() {
	return Iterator(content + length);
}
template<class T> typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& it) {
	ptr = it.ptr;
	return *this;
}
template<class T> typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
	ptr++;
	return *this;
}
template<class T> typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {
	ptr--;
	return *this;
}
template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
	Iterator temp = *this;
	++(*this);
	return temp;
}
template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
	Iterator temp = *this;
	--(*this);
	return temp;
}
template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator+(int val) {
	Iterator temp = *this;
	temp.ptr += val;
	return temp;
}
template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator+=(int val) {
	this->ptr += val;
	return *this;
}
template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator-(int val) {
	Iterator temp = *this;
	temp.ptr -= val;
	return temp;
}
template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator-=(int val) {
	this->ptr -= val;
	return *this;
}
template<class T> bool Vector<T>::Iterator::operator==(const Iterator& it) {
	return this->ptr == it.ptr;
}
template<class T> bool Vector<T>::Iterator::operator!=(const Iterator& it) {
	return this->ptr != it.ptr;
}
template<class T> bool Vector<T>::Iterator::operator<(const Iterator& it) {
	return *ptr < *it.ptr;
}
template<class T> bool Vector<T>::Iterator::operator<=(const Iterator& it) {
	return *ptr <= *it.ptr;
}
template<class T> bool Vector<T>::Iterator::operator>(const Iterator& it) {
	return *ptr > *it.ptr;
}
template<class T> bool Vector<T>::Iterator::operator>=(const Iterator& it) {
	return *ptr >= *it.ptr;
}
template<class T> T Vector<T>::Iterator::operator*() {
	return *ptr;
}
template<class T> T Vector<T>::Iterator::operator[](int index) {
	return *(ptr + index);
}
template<class T> T* Vector<T>::Iterator::operator->() {
	return ptr;
}
