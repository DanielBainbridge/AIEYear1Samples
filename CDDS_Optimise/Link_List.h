#pragma once
#include <iterator>
#include <cstddef>
template <typename T>
class Node {
public:
	T value;
	Node* previous;
	Node* next;
	Node() = default;
	Node(T val, Node* prev, Node* next) :value(val), previous(prev), next(next) {}
	~Node() {}
};

//dummy class for experiments
template <typename T>
class LinkedList {
public:
	struct NodeIterator {
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		Node<T>* currentNode;
		NodeIterator(Node<T>* ptr)
			: currentNode(ptr) {}
		Node<T> Current() { return currentNode; }

		//
		reference operator*() const { return currentNode->value; }
		pointer operator->() { return &currentNode->value; }
		//


		//prefix increment
		NodeIterator& operator++() {
			if (currentNode != nullptr)
				currentNode = currentNode->next; return *this;
		}
		//suffix increment
		NodeIterator operator++(int) { NodeIterator tmp = *this; ++(*this); return tmp; }
		//prefix decrement
		NodeIterator& operator--() {
			if (currentNode != nullptr)
				currentNode = currentNode->previous; return *this;
		}
		//suffix decrement
		NodeIterator operator--(int) { NodeIterator tmp = *this; --(*this); return tmp; }

		friend bool operator==(const NodeIterator& a, const NodeIterator& b) { return a.currentNode == b.currentNode; };
		friend bool operator!=(const NodeIterator& a, const NodeIterator& b) { return a.currentNode != b.currentNode; };


	};

	Node<T>* head;
	Node<T>* tail;
	int m_count;
	//default construction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}
	~LinkedList() {
		clear();
		delete head;
		delete tail;
	}


	// adds value at the head of the list
	void pushFront(T value) {
		Node<T>* newFirst = new Node<T>{ value, nullptr, head };
		if (head != nullptr)
		{
			head->previous = newFirst;
		}
		else tail = newFirst;
		head = newFirst;
		m_count++;
	}
	// adds value at the end of the list
	void pushBack(T value) {
		Node<T>* newEnd = new Node<T>{ value, tail, nullptr };
		if (tail != nullptr)
		{
			tail->next = newEnd;
		}
		else head = newEnd;
		tail = newEnd;
		m_count++;
	}

	// adds a value at a specified space in the list
	void insert(NodeIterator space, T value) {
		Node<T>* newInsert = new Node{ value, space.currentNode, space.currentNode->next };
		space.currentNode->next->previous = newInsert;
		space.currentNode->next = newInsert;
		m_count++;
	}
	// return the iterator to the first element
	NodeIterator begin() {
		if (head != nullptr)
		{
			return NodeIterator(head);
		}
		else return NodeIterator(nullptr);
	}
	// return the iterator to the last element
	NodeIterator end() {
		if (tail != nullptr)
		{
			return NodeIterator(tail->next);
		}
		else return NodeIterator(nullptr);
	}
	// return the first value in the list
	T& first() {
		return head.value;
	}
	// return the last value in the list
	T& last() {
		return tail.value;
	}
	// return the amount of elements in the array
	NodeIterator count() {
		return m_count;
	}
	// remove an element by its iterator
	NodeIterator erase(NodeIterator toErase) {
		if (toErase.currentNode->previous == nullptr) {
			head = toErase.currentNode->next;
			if (head != nullptr) {
				head->previous = nullptr;
			}
		}
		else {
			toErase.currentNode->previous->next = toErase.currentNode->next;
		}
		if (toErase.currentNode->next == nullptr) {
			tail = toErase.currentNode->previous;
			if (tail != nullptr) {
				tail->next = nullptr;
			}
		}
		else {
			toErase.currentNode->next->previous = toErase.currentNode->previous;
		}
		NodeIterator next = toErase;
		next++;
		delete toErase.currentNode;
		m_count--;
		return next;
	}
	//  remove an elements matching this value
	void remove(T value) {
		erase(find(value));
	}
	// finds element in list return position
	NodeIterator find(T value) {
		auto it = begin();
		for (; it != end(); it++)
		{
			if (*it == value) {
				break;
			}
		}
		return it;
	}
	// remove the first element
	void popFront() {
		if (head != nullptr) {
			Node<T>* oldHead = head;
			if (head->next != nullptr) {
				head = head->next;
				head->previous = nullptr;
			}
			else {
				head = nullptr; tail = nullptr;
			}
			m_count--;
			delete oldHead;
		}
	}
	// remove the last element
	void popBack() {
		if (tail != nullptr) {
			Node<T>* oldTail = tail;
			if (tail->previous != nullptr) {
				tail = tail->previous;
				tail->next = nullptr;
			}
			else {
				head = nullptr; tail = nullptr;
			}
			m_count--;
			delete oldTail;
		}
	}
	// returns true if the list is empty
	bool empty() {
		if (head == nullptr) {
			return true;
		}
	}
	// remove all elements from the list
	void clear() {
		while (head != nullptr) {
			popFront();
		}
	}
};