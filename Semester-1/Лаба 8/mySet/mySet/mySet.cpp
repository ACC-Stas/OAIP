#include <iostream>
#include <list>

class Vector
{
private:
	int length;
	int* v;
public:
	Vector(int length = 0) {
		if (length < 0) {
			throw std::exception("Length of vector can't be negative");
		}
		v = new int[length];
		this->length = length;
		for (int i = 0; i < length; i++) {
			v[i] = 0;
		}
	}
	Vector(const Vector& other) {                //конструктор копировния
		this->length = other.length;
		this->v = new int[other.length];
		for (int i = 0; i < this->length; i++) {
			this->v[i] = other.v[i];
		}
	}
	Vector& operator = (const Vector& other) {
		delete[] this->v;
		this->length = other.length;
		this->v = new int[other.length];
		for (int i = 0; i < this->length; i++) {
			this->v[i] = other.v[i];
		}
		return *this;
	}
	void push_back(int number) {
		int* vtemp = new int[length + 1];
		for (int i = 0; i < length; i++) {
			vtemp[i] = v[i];
		}
		delete[] v;
		v = vtemp;
		v[length] = number;
		length++;
	}
	int getNumber(int index) {
		return v[index];
	}
	int getLength() {
		return length;
	}
	void pushTo(int number, int index) {
		if (index < 0) {
			throw std::exception("index can't be negative");
		}
		if (index >= length) {
			throw std::exception("index is out of range");
		}
		int* vtemp = new int[length + 1];
		for (int i = 0; i < index; i++) {
			vtemp[i] = v[i];
		}
		vtemp[index] = number;
		for (int i = index + 1; i < length + 1; i++) {
			vtemp[i] = v[i - 1];
		}
		delete[] v;
		v = vtemp;
		length++;
	}
	void clear(int index) {
		int* vtemp = new int[length - 1];
		for (int i = 0; i < index; i++) {
			vtemp[i] = v[i];
		}
		for (int i = index; i < length - 1; i++) {
			vtemp[i] = v[i + 1];
		}
		delete[] v;
		v = vtemp;
		length--;
	}
	void clear() {
		delete[] v;
		v = new int[0];
		length = 0;
	}
	int detectIndex(int number) {                        //находит первый возможный индекс или выводит -1
		int index = -1;
		for (int i = 0; i < length; i++) {
			if (v[i] == number) {
				index = i;
				break;
			}
		}
		return index;
	}
	int detectNearestIndex(int number) {            //возвращает позицию, на которой находится number, или индекс большего элемента
		int index = -1;
		for (int i = 0; i < length; i++) {
			if (v[i] >= number) {
				index = i;
				break;
			}
		}
		return index;
	}
	void print() {
		for (int i = 0; i < length - 1; i++) {
			std::cout << v[i] << " ";
		}
		std::cout << v[length - 1];
	}
	~Vector() {
		delete[] v;
	}
};

class Set {
private:
	Vector elements;
public:
	Set() {
	}
	void push(int number) {
		int index;
		index = elements.detectNearestIndex(number);
		if (index == -1) {
			elements.push_back(number);
		} else if (number != elements.getNumber(index)) {
			elements.pushTo(number, index);
		}
	}
	int getNumber(int index) {
		return elements.getNumber(index);
	}
	int getLength() {
		return elements.getLength();
	}
	void clear(int index) {
		elements.clear(index);
	}
	void clear() {
		elements.clear();
	}
	void print() {
		elements.print();
	}
	~Set() {
	}
};

int main()
{
	Set set1;
	set1.push(1);
	set1.push(1);
	set1.push(3);
	set1.push(2);
	set1.push(4);
	set1.print();
	std::cout << "\n";
	set1.clear(2);
	set1.print();
}