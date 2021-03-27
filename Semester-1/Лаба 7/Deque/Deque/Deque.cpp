#include <iostream>
#include <cmath>

class Vector
{
protected:
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
	~Vector() {
		delete[] v;
	}
};

                                                         
class Deque : public Vector {                                                          //back is at the left side, front - rigth 
private:
	Vector posV;
	Vector negV;
public:
	Deque(int positiveLength = 0, int negativeLength = 0) {
		Vector pv(abs(positiveLength));
		Vector nv(abs(negativeLength));
		posV = pv;
		negV = nv;
	}
	Deque(const Deque& other) {
		this->posV = other.posV;
		this->negV = other.negV;
	}
	Deque& operator = (const Deque& other) {
		this->posV = other.posV;
		this->negV = other.negV;
		return *this;
	}
	int getPosLength() {
		return posV.getLength();
	}
	int getNegLength() {
		return negV.getLength();
	}
	int getLength() {
		return negV.getLength() + posV.getLength();
	}
	void push_front(int number) {
		posV.push_back(number);
	}
	void push_back(int number) {
		negV.push_back(number);
	}
	void print() {                                                    //для удобства проверки
		int negativeLength = negV.getLength();
		int positiveLength = posV.getLength();
		for (int i = negativeLength - 1; i >= 0; i--) {
			std::cout << negV.getNumber(i) << " ";
		}
		std::cout << "        ";
		for (int i = 0; i < positiveLength; i++) {
			std::cout << posV.getNumber(i) << " ";
		}
		std::cout << std::endl;
	}
	void pushTo(int number, int index) {
		if (index >= 0) {
			posV.pushTo(number, index);
		} 
		else {
			index = abs(index) - 1;     //there is shift in negative Vector, becouse we can't have to 0 indexs;
			negV.pushTo(number, index);
		}
	}
	void clear(int index) {
		if (index >= 0) {
			posV.clear(index);
		}
		else {
			index = abs(index) - 1;     //there is shift in negative Vector, becouse we can't have to 0 indexs;
			negV.clear(index);
		}
	}
	void clear() {
		posV.clear();
		negV.clear();
	}
	int detectIndex(int number) {
		int result = NULL, tempresult = 0;                    //кроме NULL нечего возвращать, не выбрасывать же исключение
		bool isIndexExist = true;
		tempresult = -negV.detectIndex(number)-1; 
		if (tempresult == 0) {                                //0 says, that there were no such numbers in negative Vector (-(-1)-1 = 0)
			tempresult = posV.detectIndex(number);
			if (tempresult == -1) {                            //no matchings once again
				isIndexExist = false;
			}
		}
		if (isIndexExist) {
			result = tempresult;
		}
		return result;
	}
};

int main()
{
	Deque d1(5, -4);
	std::cout << d1.getLength() << std::endl;
	d1.push_front(15);
	d1.push_back(-15);
	d1.pushTo(-25, -1);
	d1.pushTo(25, 1);
	d1.clear(-2);
	d1.clear(2);
	d1.print();
	d1.clear();
	d1.push_back(-1);
	d1.push_front(1);
	d1.push_back(-2);
	d1.push_front(2);
	d1.print();
	std::cout << d1.detectIndex(-2) << " " << d1.detectIndex(-1) << " " << d1.detectIndex(1) << " " << d1.detectIndex(2) << std::endl;
	Deque d2;
	d2 = d1;
	d2.print();
	Deque d3 = d1;
	d3.print();
	return 0;
}