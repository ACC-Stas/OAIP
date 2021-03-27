#include <iostream>
#include <vector>
#include <initializer_list>
#include <iterator>

template <class T>
class Deque {
private:
	int leftIndex, rightIndex; //show first empty index
	static const int blockSize = 32;
	std::vector<T*> posHeaders;
	std::vector<T*> negHeaders;
public:
	Deque(int length = 0, T def = T()) {
		leftIndex = -length - 1;
		rightIndex = length;
		int numberOfBlocks = length / blockSize + 1;
		for (int i = 0; i < numberOfBlocks; i++) {
			posHeaders.push_back(new T[blockSize]);
			negHeaders.push_back(new T[blockSize]);
		}
		int counter = 0;
		while (counter < length) {
			posHeaders[counter / blockSize][counter % blockSize] = def;
			negHeaders[counter / blockSize][counter % blockSize] = def;
			counter++;
		}
	}
	Deque(Deque& d) {
		this->leftIndex = d.leftIndex;
		this->rightIndex = d.rightIndex;
		int numberOfRightBlocks = 0;
		if (d.rightIndex > 0) {
			numberOfRightBlocks = rightIndex / blockSize + 1;
		}
		for (int i = 1; i <= numberOfRightBlocks; i++) {
			posHeaders.push_back(new T[blockSize]);
		}
		int numberOfLeftBlocks = 0;
		if (d.leftIndex < -1) {
			numberOfLeftBlocks = (-1 * leftIndex - 1) / blockSize + 1;
		}
		for (int i = 1; i <= numberOfRightBlocks; i++) {
			negHeaders.push_back(new T[blockSize]);
		}
		int index;
		T value;
		for (int i = d.leftIndex + 1; i < d.rightIndex; i++) {
			if (i >= 0) {
				value = d[i];
				posHeaders[i / blockSize][i% blockSize] = value;
			}
			else {
				value = d[i];
				index = -1 * i - 1;
				negHeaders[index / blockSize][index % blockSize] = value;
			}
		}
	}
	Deque(const std::initializer_list<T>& list) {
		leftIndex = -1;
		rightIndex = 0;
		for (auto it : list) {
			push_back(it);
		}
	}
	class Iterator : std::iterator<std::random_access_iterator_tag,T> {
	private:
		Deque* d;
		int index;
	public:
		Iterator(Deque& d, int index) {
			this->d = &d;
			this->index = index;
		}
		Iterator(const Iterator& it) {
			this->d = it.d;
			this->index = it.index;
		}
		Iterator& operator=(const Iterator& it) {
			this->d = it.d;
			this->index = it.index;
			return *this;
		}
		Iterator& operator++() {
			index++;
			return *this;
		}
		Iterator& operator--() {
			index--;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			this->index++;
			return temp;
		}
		Iterator operator--(int) {
			Iterator temp = *this;
			this->index--;
			return temp;
		}
		Iterator operator+(int value) {
			Iterator temp = *this;
			temp.index += value;
			return temp;
		}
		Iterator operator+=(int value) {
			this->index += value;
			return *this;
		}
		Iterator operator-(int value) {
			Iterator temp = *this;
			temp.index -= value;
			return temp;
		}
		Iterator operator-=(int value) {
			this->index -= value;
			return *this;
		}
		bool operator==(const Iterator& it) {
			bool isEqualAddresses = false;
			if (d == it.d && index == it.index) {
				isEqualAddresses = true;
			}
			return isEqualAddresses;
		}
		bool operator!=(const Iterator& it) {
			bool isEqualAddresses = false;
			if (d == it.d && index == it.index) {
				isEqualAddresses = true;
			}
			return !isEqualAddresses;
		}
		bool operator<(const Iterator& it) {
			T valueThis = d->operator[](index);
			T valueIt = it.d->operator[](it.index);
			return valueThis < valueIt;
		}
		bool operator<=(const Iterator& it) {
			T valueThis = d->operator[](index);
			T valueIt = it.d->operator[](it.index);
			return valueThis <= valueIt;
		}
		bool operator>(const Iterator& it) {
			T valueThis = d->operator[](index);
			T valueIt = it.d->operator[](it.index);
			return valueThis > valueIt;
		}
		bool operator>=(const Iterator& it) {
			T valueThis = d->operator[](index);
			T valueIt = it.d->operator[](it.index);
			return valueThis >= valueIt;
		}
		T operator*() {
			return d->operator[](index);
		}
		T operator[](int value) {
			return d->operator[](index + value);
		}
		T* operator->() {
			T* ptr = &d->operator[](index);
			return ptr;
		}
	};
	Deque& operator=(Deque& d) {
		this->leftIndex = d.leftIndex;
		this->rightIndex = d.rightIndex;
		int numberOfRightBlocks = 0;
		if (d.rightIndex > 0) {
			numberOfRightBlocks = rightIndex / blockSize + 1;
		}
		for (int i = 1; i <= numberOfRightBlocks; i++) {
			posHeaders.push_back(new T[blockSize]);
		}
		int numberOfLeftBlocks = 0;
		if (d.leftIndex < -1) {
			numberOfLeftBlocks = (-1 * leftIndex - 1) / blockSize + 1;
		}
		for (int i = 1; i <= numberOfRightBlocks; i++) {
			negHeaders.push_back(new T[blockSize]);
		}
		int index;
		T value;
		for (int i = d.leftIndex + 1; i < d.rightIndex; i++) {
			if (i >= 0) {
				value = d[i];
				posHeaders[i / blockSize][i % blockSize] = value;
			}
			else {
				value = d[i];
				index = -1 * i - 1;
				negHeaders[index / blockSize][index % blockSize] = value;
			}
		}
		return *this;
	}
	T& operator[](int index) {
		if (index <= leftIndex || index >= rightIndex) {
			throw std::exception("No such index\n");
		}
		T returnValue;
		if (index >= 0) {
			returnValue = posHeaders[index / blockSize][index % blockSize];
		}
		else {
			index *= -1;
			index -= 1;
			returnValue = negHeaders[index / blockSize][index % blockSize];
		}
		return returnValue;
	}
	Iterator begin() {
		Iterator it(*this, leftIndex + 1);
		return it;
	}
	Iterator end() {
		Iterator it(*this, rightIndex);
		return it;
	}
	void push_front(T value) { //left
		if (leftIndex >= 0) {
			if (leftIndex % blockSize == (blockSize -1)) {   //need new block of memory
				posHeaders[leftIndex / blockSize] = new T[blockSize];
			}
			posHeaders[leftIndex / blockSize][leftIndex % blockSize] = value;
		}
		else {
			int negIndex = -1 * leftIndex - 1;
			if (negIndex% blockSize == 0) {
				negHeaders.push_back(new T[blockSize]);
			}
			negHeaders[negIndex / blockSize][negIndex % blockSize] = value;
		}
		leftIndex--;
	}
	void push_back(T value) {  //right
		if (rightIndex >= 0) {
			if (rightIndex % blockSize == 0) {
				posHeaders.push_back(new T[blockSize]);
			}
			posHeaders[rightIndex / blockSize][rightIndex % blockSize] = value;
		}
		else {
			int negIndex = -1 * rightIndex - 1;
			if (negIndex % blockSize == (blockSize - 1)) {
				negHeaders[negIndex / blockSize] = new T[blockSize];
			}
			negHeaders[negIndex / blockSize][negIndex % blockSize] = value;
		}
		rightIndex++;
	}
	void pop_front() {  //left
		if (leftIndex == rightIndex - 1) {
			throw std::exception("Already empty");
		}
		if (leftIndex >= 0) {
			if (leftIndex % blockSize == (blockSize - 2)) { //don't need block of memory
				delete[] posHeaders[leftIndex / blockSize];
			}
		}
		else {
			int negIndex = -1 * leftIndex - 1;
			if (negIndex % blockSize == 1) {
				delete[] negHeaders[negIndex / blockSize + 1];
				negHeaders.pop_back();
			}
		}
		leftIndex++;
	}
	void pop_back() { //right
		if (leftIndex == rightIndex - 1) {
			throw std::exception("Already empty");
		}
		if (rightIndex >= 0) {
			if (rightIndex % blockSize == 1) {
				delete[] posHeaders[rightIndex / blockSize];
			}
		}
		else {
			int negIndex = -1 * rightIndex - 1;
			if (negIndex % blockSize == (blockSize - 2)) {
				delete[] negHeaders[negIndex / blockSize];
				negHeaders.pop_back();
			}
		}
		rightIndex--;
	}
	int leftEmpty() { //can't write in it
		return leftIndex;
	}
	int rightEmpty() {
		return rightIndex;
	}
	bool empty() {
		bool isEmpty = false;
		if (leftIndex == rightIndex - 1) {
			isEmpty = true;
		}
		return isEmpty;
	}
	int size() {
		return rightIndex - 1 - leftIndex;
	}
	void clear() {
		if (leftIndex < -1) {
			int negIndex = -1 * leftIndex - 1;
			int maxBlock = negIndex / blockSize;
			for (int i = maxBlock; i > 0; i--) {
				delete[] negHeaders[i];
				negHeaders.pop_back();
			}
		}
		if (rightIndex > 0) {
			int maxBlock = rightIndex / blockSize;
			for (int i = maxBlock; i >= 0; i--) {
				delete[] posHeaders[i];
				posHeaders.pop_back();
			}
		}
		rightIndex = 0;
		leftIndex = -1;
	}
	void resize(int length, T def = T()) {
		int rightDifference = length;
		if (rightIndex > 0) {
			rightDifference = length - rightIndex;
		}
		if (rightDifference > 0) {
			for (int i = 0; i < rightDifference; i++) {
				push_back(def);
			}
		}
		else {
			for (int i = 0; i < -1 * rightDifference; i++) {
				pop_back();
			}
		}
		int leftDifference = length;
		if (leftIndex < -1) {
			leftDifference = length + leftIndex + 1;
		}
		if (leftDifference > 0) {
			for (int i = 0; i < leftDifference; i++) {
				push_front(def);
			}
		}
		else {
			for (int i = 0; i < -1*leftDifference; i++) {
				pop_front();
			}
		}
		leftIndex = -length - 1;
		rightIndex = length;
	}
	~Deque() {
		clear();
	}
};

class A {  //just test class
private:
	int variable;
public:
	void setVariable(int variable) {
		this->variable = variable;
	}
	int getVariable() {
		return variable;
	}
};

int main() {
	Deque<int> d(5, 1);
	for (int i = d.leftEmpty() + 1; i < d.rightEmpty(); i++) {
		std::cout << d[i] << " ";
	}
	std::cout << "\n LeftEmpty is " << d.leftEmpty() << "\n";
	d.push_front(4);
	std::cout << "LeftEmpty is " << d.leftEmpty() << "\n";
	std::cout << d[d.leftEmpty() + 1] << "\n";
	Deque<int> d1;
	d1.push_front(4);
	std::cout << "Is it empty? " << d1.empty() << '\n';
	std::cout << "Size is: " << d1.size() << '\n';
	std::cout << d1[-1] << "\n";
	d1.pop_front();
	std::cout << "Is it empty? " << d1.empty() << '\n';
	std::cout << "Size is: " << d1.size() << '\n';
	try {
		d1.pop_front();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	for (int i = 1; i < 47; i++) {
		d1.push_front(-i);
	}
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << '\n';
	for (int i = 0; i < 43; i++) {
		d1.pop_front();
	}
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << "\nWorking with push back\n";
	for (int i = 0; i < 46; i++) {
		d1.push_back(i);
	}
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << '\n';
	for (int i = 0; i < 43; i++) {
		d1.pop_front();
	}
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << '\n';
	for (int i = -1; i > -45; i--) {
		d1.push_front(i);
	}
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << "\nWorking with pop back\n";
	for (int i = 0; i < 43; i++) {
		d1.pop_back();
	}
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << '\n';
	d1.clear();
	d1.push_front(-1);
	d1.push_back(1);
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << "\nWorking with resize\n";
	d1.resize(3, 4);
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << '\n';
	Deque<int> d2(d1);
	std::cout << "It is d2\n";
	for (int i = d2.leftEmpty() + 1; i < d2.rightEmpty(); i++) {
		std::cout << d2[i] << " ";
	}
	std::cout << '\n';
	Deque<int> d3 { 4,6,8,10,12,14,16 };
	std::cout << "It is d3\n";
	for (int i = d3.leftEmpty() + 1; i < d3.rightEmpty(); i++) {
		std::cout << d3[i] << " ";
	}
	std::cout << '\n';
	d1 = d3;
	for (int i = d1.leftEmpty() + 1; i < d1.rightEmpty(); i++) {
		std::cout << d1[i] << " ";
	}
	std::cout << "\nWorking with iterators\n";
	Deque<int>::Iterator it3 = d3.begin();
	std::cout << *it3 << '\n';
	++it3;
	std::cout << *it3 << '\n';
	--it3;
	std::cout << *it3 << '\n';
	std::cout << *(it3++) << '\n';
	std::cout << *it3 << '\n';
	std::cout << *(it3--) << '\n';
	std::cout << *it3 << '\n';
	it3 = it3 + 2;
	std::cout << *it3 << '\n';
	it3 += 2;
	std::cout << *it3 << '\n';
	it3 = it3 - 2;
	std::cout << *it3 << '\n';
	it3 -= 2;
	std::cout << *it3 << '\n';
	Deque<int>::Iterator it31 = d3.begin();
	std::cout << (it31 == it3) << '\n';
	Deque<int>::Iterator it1 = d1.begin();
	std::cout << *it1 << '\n';
	std::cout << (it1 == it3) << '\n';
	it1 += 2;
	std::cout << "it1 - " << *it1 << '\n';
	std::cout << "it3 - " << *it3 << '\n';
	std::cout << "Is it1 < it3: " << (it1 < it3) << '\n';
	std::cout << "Is it3 < it1: " << (it3 < it1) << '\n';
	std::cout << "Is it1 > it3: " << (it1 > it3) << '\n';
	std::cout << "Is it1 <= it3: " << (it1 <= it3) << '\n';
	std::cout << "Is it1 >= it3: " << (it1 >= it3) << '\n';
	it1 -= 2;
	std::cout << "it1 - " << *it1 << '\n';
	std::cout << "it3 - " << *it3 << '\n';
	std::cout << "Is it1 <= it3: " << (it1 <= it3) << '\n';
	std::cout << "Is it1 >= it3: " << (it1 >= it3) << '\n';
	std::cout << it3[2] << '\n';
	A object;
	object.setVariable(5);
	Deque<A> da;
	da.push_back(object);
	da.push_front(object);
	Deque<A>::Iterator itA = da.begin();
	std::cout << itA->getVariable();
	std::cout << "\nTest iterator invalidation\n";
	std::cout << "it3 - " << *it3 << '\n';
	d3.resize(45, 7);
	std::cout << "it3 - " << *it3 << '\n';
	for (int i = 0; i < 30; i++) {
		std::cout << it3[i] << " ";
	}
	std::cout << '\n';
}