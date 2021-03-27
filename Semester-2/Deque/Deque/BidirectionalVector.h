#pragma once
#include "Vector.h"

template<typename T>
class BidirectionalVector {      //just for using in Deque
private:
	Vector<T> pos;
	Vector<T> neg;
public:
	BidirectionalVector(int posLength = 0, int negLength = 0, T def = T()) {
		pos = Vector<T>(posLength, def);
		neg = Vector<T>(negLength, def);
	}
	BidirectionalVector(const BidirectionalVector& bv) {
		this->pos = bv.pos;
		this->neg = bv.neg;
	}
	void push_front(T value) {
		pos.push_back(value);
	}
	void push_back(T value) {
		neg.push_back();
	}
	void pop_front() {
		pos.pop_back();
	}
	void pop_back() {
		neg.pop_back();
	}
	T& operator[](int index) {
		T output;
		if (index >= 0) {
			output = pos[index];
		}
		else {
			output = neg[-index - 1];
		}
		return output;
	}
};

