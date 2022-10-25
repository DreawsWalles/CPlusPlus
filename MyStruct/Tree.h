#pragma once
#include "Node.h"
#include <iostream>
#include <string>
#include "MyType.h"


template <typename T>
class Tree
{
private:
	Node<T>* _root;
public:
	Tree();
	~Tree();
	void addNode(T x);
	void deleteNode(T value);
	bool search(T x);
	int getSize();
	int getHeight();
	void print();
private:
	int getSize(Node<T>* tmp);
	int getHeight(Node<T>* tmp);
	void printNode(Node<T>* node, int h);
};

template <typename T>
Tree<T>::Tree()
{
	_root = nullptr;
}

template <typename T>
Tree<T>::~Tree()
{
	delete _root; 
}

template <typename T>
void Tree<T>::addNode(T x)
{
	if (_root == nullptr)
	{
		_root = new Node<T>(x);
	}
	else
	{
		_root->addNode(x);
	}
}


template <typename T>
bool Tree<T>::search(T x)
{
	if (_root == nullptr)
		return false;
	return _root->search(x);
}

template <typename T>
void Tree<T>::deleteNode(T value) {
	Node<T>* parent = nullptr;
	Node<T>* tmp = _root;
	while (tmp != nullptr && tmp->getInf() != value) {
		parent = tmp;
		if (tmp->getInf() > value)
			tmp = tmp->getLeft();
		else
			tmp = tmp->getRight();
	}
	if (tmp == nullptr)
		return;

	if (tmp->getRight() == nullptr) {
		if (_root == tmp)
			_root = tmp->getLeft();
		else if (parent->getInf() < value)
			parent->setRight(tmp->getLeft());
		else
			parent->setLeft(tmp->getLeft());
		tmp->setLeft(nullptr);
		delete tmp;
	}
	else if (tmp->getLeft() == nullptr) {
		if (_root == tmp)
			_root = tmp->getRight();
		else if (parent->getInf() < value)  
			parent->setRight(tmp->getRight());
		else
			parent->setLeft(tmp->getRight());
		tmp->setRight(nullptr);
		delete tmp;
	}
	else {
		Node<T>* rootToDelete = tmp;
		parent = tmp;
		tmp = tmp->getLeft();
		while (tmp->getRight() != nullptr) {
			parent = tmp;
			tmp = tmp->getRight();
		}
		rootToDelete->setInf(tmp->getInf());
		if (parent->getInf() < tmp->getInf())
			parent->setRight(tmp->getLeft());
		else
			parent->setLeft(tmp->getLeft());
		tmp->setLeft(nullptr);
		delete tmp;
	}
}

template <typename T>
int Tree<T>::getSize(Node<T>* tmp)
{
	if (tmp != nullptr)
	{
		return 1 + getSize(tmp->getLeft()) + getSize(tmp->getRight());
	}
	return 0;
}

template <typename T>
int Tree<T>::getSize()
{
	int size;
	size = getSize(_root);
	return size;
}

template <typename T>
int Tree<T>::getHeight(Node<T>* tmp)
{
	if (tmp != nullptr)
	{
		return 1 + std::max(getHeight(tmp->getLeft()), getHeight(tmp->getRight()));
	}
	return 0;
}

template <typename T>
int Tree<T>::getHeight()
{
	int height;
	height = getHeight(_root);
	return height;
}

template <typename T>
void Tree<T>::print()
{
	if (_root == NULL)
		cout << "Дерево пусто" << endl;
	else
		printNode(_root, 0);
}

template <typename T>
void Tree<T>::printNode(Node<T>* node, int h)
{
	if (node != NULL)
	{
		printNode(node->getLeft(), h + 1);
		for (int i = 1; i <= h; i++)

			cout << "\t";

		cout << node->getInf() << endl;

		printNode(node->getRight(), h + 1);

	}

}


