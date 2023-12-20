#pragma once

#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
template<typename T>
class queue
{
public:
	template<typename T>
	struct Node
	{
		T data = 0;
		Node* next = nullptr;

		Node() {};
		~Node() {};
	};

	Node<T>* head;
	Node<T>* tail;
	size_t queuesize;
	std::mutex mut;

	void push(T x);
	T front();
	bool pop();
	bool empty();
	size_t size();
	void printQueue();
	queue();
	~queue();
};

template <typename T>
bool queue<T>::pop()
{
	std::lock_guard<std::mutex> guard(mut);
	
	if (this->empty())
	{
		return false;
	};
	
	Node<T>* temp = this->head;
	this->head = this->head->next;
	
	delete temp;

	queuesize = queuesize - 1;
	
	return true;
}

template <typename T>
T queue<T>::front()
{
	std::lock_guard<std::mutex> guard(mut);

	return this->head->data;

	if (this->empty()) throw ("err front (empty queue)");
}

template <typename T>
void queue<T>::push(T x)
{
	Node<T>* temp = new Node<T>;
	temp->data = std::move(x);

	std::lock_guard<std::mutex> guard(mut);

	if (this->head == nullptr)
	{
		this->head = temp;
		this->tail = temp;
		++this->queuesize;
		return;
	}

	this->tail->next = temp;
	this->tail = this->tail->next;

	++this->queuesize;
}

template <typename T>
bool queue<T>::empty()
{
	return (this->head == nullptr);
}

template<typename T>
size_t queue<T>::size()
{
	return queuesize;
}

template <typename T>
queue<T>::queue() : head(nullptr), tail(nullptr) {}

template <typename T>
queue<T>::~queue()
{
	std::lock_guard<std::mutex> guard(mut);

	while (this->head != nullptr)
	{
		Node<T>* temp = this->head;
		this->head = this->head->next;

		delete temp;
	}
}
template<typename T>
void queue<T>::printQueue()
{
	std::lock_guard<std::mutex> guard(mut);

	Node<T>* current = head;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}