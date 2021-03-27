#include <iostream>

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
			vtemp[i] = v[i-1];
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
	~Vector() {
		delete[] v;
	}
};

int main()
{
	Vector v1;
	v1.push_back(5);
	v1.push_back(15);
	v1.push_back(25);
	v1.push_back(35);
	v1.push_back(45);
	v1.push_back(55);
	v1.push_back(65);
	v1.pushTo(125, 2);
	v1.clear(6);
	std::cout << v1.detectIndex(125) << std::endl;
	std::cout << v1.detectIndex(-5) << std::endl;
	int length = v1.getLength();
	for (int i = 0; i < length; i++) {
		std::cout << v1.getNumber(i) << " ";
	}
	v1.clear();
	v1.push_back(25);
	std::cout << std::endl;
	length = v1.getLength();
	for (int i = 0; i < length; i++) {
		std::cout << v1.getNumber(i) << " ";
	}
	std::cout << std::endl;
	Vector v2(15);
	length = v2.getLength();
	for (int i = 0; i < length; i++) {
		std::cout << v2.getNumber(i) << " ";
	}
	std::cout << std::endl;
	Vector v3 = v2;                                        //использует конструктор копирования
	length = v3.getLength();
	for (int i = 0; i < length; i++) {
		std::cout << v3.getNumber(i) << " ";
	}
	Vector v4, v5;
	v5 = v4 = v3;
	std::cout << std::endl;
	length = v4.getLength();
	for (int i = 0; i < length; i++) {
		std::cout << v4.getNumber(i) << " ";
	}
	std::cout << std::endl;
	length = v5.getLength();
	for (int i = 0; i < length; i++) {
		std::cout << v5.getNumber(i) << " ";
	}
	std::cout << std::endl;
	try {
		v1.pushTo(35, 35);                                     //проверил работу throw
	}
	catch (const std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}