#include "menu.h"
#include <iostream>
#include <string>

menu::menu()
{
	_size = 0;
	_head = new LinkNode;
}

menu::~menu()
{
	delete _head;
	_size = 0;
}

int menu::Count()
{
	return _size;
}

void menu::Add(string s)
{
	if (_size == 0)
	{
		_head = new LinkNode;
		_head->_node = s;
		_head->next = nullptr;
	}
	else
	{
		LinkNode* current = new LinkNode;
		current = _head;
		while (current->next != nullptr)
			current = current->next;
		LinkNode* tmp = new LinkNode;
		tmp->_node = s;
		tmp->next = nullptr;
		current->next = tmp;
	}
	_size++;
}

void menu::Print()
{
	LinkNode* current = new LinkNode;
	current= _head;
	int i = 1;
	while (current != nullptr)
	{
		if (current->_node == "Выход")
			cout << 0 << ". " << current->_node << endl;
		else
			cout << i << ". " << current->_node << endl;
		i++;
		current = current->next;
	}
	cout << "-> ";
}

int menu::Choice(string theme)
{
	string s;
	int result;
	do
	{
		getline(cin, s);
		if (s == "0")
			return 0;
		if ((result = CheckChoise(s, 1, _size)) == -1)
		{
			system("pause");
			system("cls");
			cout << theme << endl;
			Print();
		}
	} while (result == -1);
	return result;
	
}

int menu::CheckChoise(string s, int borderBeg, int borderEnd)
{
	int num;
	if (s.empty())
	{
		cout << "Считана пустая строка. Повторите ввод" << endl;
		return -1;
	}
	else
	{
		num = 0;
		int len = s.size();
		int i = 0;
		int n;
		while (i < len)
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				n = s[i] - '0';
				num = num * 10 + n;
				i++;
			}
			else
			{
				cout << "Считан некорректный символ: " << s[i] << " . Повторите ввод" << endl;
				return -1;
			}
		if ((num < borderBeg) || (num > borderEnd))
		{
			cout << "Считанное значение некорректно. Значение должно быть в диапазоне от " << borderBeg << " до " << borderEnd << endl;
			return -1;
		}
		return num;
	}
}
menu& menu::operator=(menu other)
{
	delete _head;
	_size = 0;
	_head = new LinkNode;
	LinkNode* tmp = other._head;
	while (tmp->next != nullptr)
		Add(tmp->_node);
	return *this;
}

