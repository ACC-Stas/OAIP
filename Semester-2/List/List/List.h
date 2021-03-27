#include <iostream>
#include <iterator>
#include <initializer_list>

template<class T>
class List {
public:
	class Iterator;
	List();
	List(List<T>& list);
	List(const std::initializer_list<T>& list);
	~List();
	List<T>& operator=(List<T>& list);
	void push_back(T data);
	void pop_back();
	void push_font(T data);
	void pop_front();
	void print();
	int size();
	bool empty();
	Iterator begin();
	Iterator end();
private:
	template <class T>
	class Node {
	public:
		Node* next;
		Node* previous;
		T data;
		Node(T data, Node* next = nullptr, Node* previous = nullptr) {
			this->data = data;
			this->next = next;         //next leads to head
			this->previous = previous;      //previous - tail
		}
	};
	int length;
	Node<T>* head;
	Node<T>* tail;
};
template<class T>
class List<T>::Iterator : std::iterator <std::bidirectional_iterator_tag, Node<T>> {
private:
	Node<T>* ptr;
public:
	Iterator();
	Iterator(Node<T>* node);
	Iterator(const Iterator& it);
	~Iterator();
	Iterator& operator=(const Iterator& it);
	bool operator==(const Iterator& it);
	bool operator!=(const Iterator& it);
	Iterator& operator++();
	Iterator& operator--();
	Iterator operator++(int);
	Iterator operator--(int);
	T operator*();
	T* operator->();
};
template<class T>
List<T>::List() {
	length = 0;
	head = nullptr;
	tail = nullptr;
}
template<class T>
List<T>::List(List<T>& list) {
	length = 0;
	head = nullptr;
	tail = nullptr;
	for (auto it : list) {
		push_back(it);
	}
}
template<class T>
List<T>::List(const std::initializer_list<T>& list) {
	length = 0;
	head = nullptr;
	tail = nullptr;
	for (auto it : list) {
		push_back(it);
	}
}
template<class T>
List<T>::~List() {
	while (!empty()) {
		pop_front();
	}
}
template<class T>
List<T>& List<T>::operator=(List<T>& list) {
	length = 0;
	head = nullptr;
	tail = nullptr;
	for (auto it : list) {
		push_back(it);
	}
	return *this;
}
template<class T>
void List<T>::push_back(T data) {         //to tail
	Node<T>* temp = new Node<T>(data);
	if (length == 0) {
		head = tail = temp;
	}
	else {
		tail->previous = temp;
		temp->next = tail;
		tail = temp;
	}
	length++;
}
template<class T>
void List<T>::pop_back() {
	if (length == 0) {
		throw std::exception("List is already empty");
	}
	else if (length == 1) {
		head = nullptr;
		delete tail;
		tail = nullptr;
	}
	else {
		Node<T>* ptr = tail->next;
		ptr->previous = nullptr;
		delete tail;
		tail = ptr;
	}
	length--;
}
template<class T>
void List<T>::push_font(T data) {
	Node<T>* temp = new Node<T>(data);
	if (length == 0) {
		head = tail = temp;
	}
	else {
		head->next = temp;
		temp->previous = head;
		head = temp;
	}
	length++;
}
template<class T>
void List<T>::pop_front() {
	if (length == 0) {
		throw std::exception("List is already empty");
	}
	else if (length == 1) {
		tail = nullptr;
		delete head;
		head = nullptr;
	}
	else {
		Node<T>* ptr = head->previous;
		ptr->next = nullptr;
		delete head;
		head = ptr;
	}
	length--;
}
template<class T>
void List<T>::print() {
	Node<T>* ptr = head;
	while (ptr != nullptr) {
		std::cout << ptr->data << " ";
		ptr = ptr->previous;
	}
	std::cout << '\n';
}
template<class T>
int List<T>::size()
{
	return length;
}
template<class T>
bool List<T>::empty() {
	bool isEmpty = false;
	if (length == 0) {
		isEmpty = true;
	}
	return isEmpty;
}
template<class T>
typename List<T>::Iterator List<T>::begin() {
	return Iterator(head);
}
template<class T>
typename List<T>::Iterator List<T>::end() {
	return Iterator();
}
template<class T>
List<T>::Iterator::Iterator() {
	ptr = nullptr;
}
template<class T>
List<T>::Iterator::Iterator(Node<T>* node) {
	ptr = node;
}
template<class T>
List<T>::Iterator::Iterator(const Iterator& it) {
	ptr = it.ptr;
}
template<class T>
List<T>::Iterator::~Iterator() {
	ptr = nullptr;
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& it) {
	ptr = it.ptr;
	return *this;
}
template <class T>
bool List<T>::Iterator::operator==(const Iterator& it) {
	return ptr == it.ptr;
}
template <class T>
bool List<T>::Iterator::operator!=(const Iterator& it) {
	return ptr != it.ptr;
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
	ptr = ptr->previous;
	return *this;
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
	ptr = ptr->next;
	return *this;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
	Iterator temp = *this;
	++(*this);
	return temp;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
	Iterator temp = *this;
	--(*this);
	return temp;
}
template<class T>
typename T List<T>::Iterator::operator*() {
	return ptr->data;
}
template<class T>
typename T* List<T>::Iterator::operator->() {
	return ptr;
}