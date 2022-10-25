#include "menu.h"
#include <iostream>
#include <string>
#include "HelpClasses.h"
#include <list>

//класс который представляет собой меню, в котором мы можем добавлять пукты, печатать их в стиле списка, удалять эти пункты и выбирать
Menu::Menu(string theme)
{
	_size = 0;
	_head = new LinkNode;
	haveEnd = false;
	themeMenu = theme;
}

Menu::~Menu()
{
	delete _head;
	_size = 0;
}

int Menu::Count()
{
	return _size;
}

void Menu::Add(string s, bool isEnd)
{
	if (haveEnd && isEnd)
		throw "Пункт меню для возврата уже добавлен";
	if (isEnd)
	{
		haveEnd = true;
		_head->_node = s;
	}
	else if (_size == 0)
	{
		LinkNode* current = new LinkNode;
		current->_node = s;
		current->next = nullptr;
		_head->next = current;
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

void Menu::Print()
{
	if (_size == 0)
		throw "В меню нет ни одного пункта";
	LinkNode* current = new LinkNode;
	current= _head;
	int i;
	cout << themeMenu << endl;
	if (haveEnd)
	{
		i = 1;
		string end = current->_node;
		current = current->next;
		while (current != nullptr)
		{
			cout << i << ". " << current->_node << endl;
			i++;
			current = current->next;
		}
		cout << "<---0. " << end << endl;
	}
	else
	{
		i = 0;
		current = current->next;
		while (current != nullptr)
		{
			cout << i << ". " << current->_node << endl;
			i++;
			current = current->next;
		}
	}
}

int Menu::Choice()
{
	int result;
	string s;
	do
	{
		getline(cin, s);
		if ((result = HelpClasses::CheckChoise(s, 0, _size - 1)) == -1)
		{
			system("pause");
			system("cls");
			Print();
		}
	} while (result == -1);
	return result;
}

void Menu::ChangeTheme(string newThemeMenu)
{
	themeMenu = newThemeMenu;
}

void Menu::Delete(int index)
{
	if (index >= _size)
		throw "Введен некорректный индекс";
	if (_size == 1)
	{
		_head = new LinkNode;
		_size = 0;
		return;
	}
	LinkNode* current = _head;
	if (_size == index)
	{
		while (current->next->next != nullptr)
			current = current->next;
		current->next = nullptr;
		_size--;
		return;
	}
	int currentIndex = 0;
	while (currentIndex < index - 1)
	{
		current = current->next;
		currentIndex++;
	}
	current->next = current->next->next;
	_size--;
}

Menu& Menu::operator=(Menu other)
{
	delete _head;
	_size = 0;
	_head = new LinkNode;
	LinkNode* tmp = other._head;
	while (tmp->next != nullptr)
		Add(tmp->_node);
	return *this;
}

void Menu::DeleteFirst()
{
	Delete(1);
}

void Menu::DeleteLast()
{
	Delete(_size);
}

void Menu::DeleteExit()
{
	Delete(0);
}

list<string> Menu::ToList()
{
	list<string> result;
	LinkNode* current = _head;
	while (current != nullptr)
	{
		result.push_back(current->_node);
		current = current->next;
	}
	return result;
}
void Menu::ChangeField(int index, string value)
{
	if (index >= _size)
		throw "Введен некорректный индекс";
	int currentIndex = 0;
	LinkNode* current = _head;
	while (currentIndex < index)
	{
		currentIndex++;
		current = current->next;
	}
	current->_node = value;
}
string Menu::GetField(int index)
{
	if (index >= _size)
		throw "Введен некорректный индекс";
	int currentIndex = 0;
	LinkNode* current = _head;
	while (currentIndex < index)
	{
		currentIndex++;
		current = current->next;
	}
	return current->_node;
}
