#pragma once
#include <string>
#include "MyType.h"

using namespace std;

template <typename T>
class Node
{
private:
	Node* _left;
	Node* _right;
	T _inf;
public:
	Node();
	Node(T x);
	~Node();
	T& getInf();
	void setInf(T x);
	Node<T>* getRight();
	Node<T>* getLeft();
	void setLeft(Node<T>* x);
	void setRight(Node<T>* x);
	void addNode(T x);
	bool search(T x);
	friend istream& operator>>(istream& in, MyType& ex);
};

template <typename T>
Node<T>::Node()
{
	_inf = 0;
	_left = nullptr;
	_right = nullptr;
}

template <typename T>
Node<T>::~Node()
{
	delete _left;
	delete _right;
}
template <typename T>
Node<T>::Node(T x)
{
	_inf = x;
	_left = nullptr;
	_right = nullptr;
}

template <typename T>
T& Node<T>::getInf()
{
	return _inf;
}

template <typename T>
Node<T>* Node<T>::getLeft()
{
	return _left;
}

template <typename T>
Node<T>* Node<T>::getRight()
{
	return _right;
}

template <typename T>
void Node<T>::setInf(T x)
{
	_inf = x;
}
template <typename T>
void Node<T>::setLeft(Node<T>* x)
{
	_left = x;
}

template <typename T>
void Node<T>::setRight(Node<T>* x)
{
	_right = x;
}

template <typename T>
void Node<T>::addNode(T x)
{
	if (_inf > x)
	{
		if (_left != nullptr)
			_left->addNode(x);
		else
			_left = new Node<T>(x);
	}
	else if (_inf < x)
	{
		if (_right != nullptr)
			_right->addNode(x);
		else
			_right = new Node<T>(x);
	}
}



template <typename T>
bool Node<T>::search(T x)
{
	if (_inf == x)
		return true;
	if (_inf > x)
	{
		return _left != nullptr && _left->search(x);
	}
	else
	{
		return _right != nullptr && _right->search(x);
	}
}

