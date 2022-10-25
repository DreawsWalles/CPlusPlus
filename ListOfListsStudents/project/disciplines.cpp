#include "disciplines.h"

disciplines::disciplines()
{
	_disciplines = new list<string>;
}

disciplines::~disciplines()
{
	delete _disciplines;
}

bool disciplines::Add(string value)
{
	list<string>::iterator it = _disciplines->begin();
	while (it != _disciplines->end() && (*it) != value)
		it++;
	if (it != _disciplines->end() && (*it) == value)
		return false;
	_disciplines->push_back(value);
	return true;
}

bool disciplines::Remove(string value)
{
	list<string>::iterator it = _disciplines->begin();
	while (it != _disciplines->end() && (*it) != value)
		it++;
	if (it == _disciplines->end())
		return false;
	_disciplines->remove(*it);
	return true;
}

bool disciplines::Change(string value, string change)
{
	if (value == change)
		return false;
	list<string>::iterator it = _disciplines->begin();
	while (it != _disciplines->end() && (*it) != value)
		it++;
	if (it == _disciplines->end())
		return false;
	(*it) = change;
	return true;
}
int disciplines::size()
{
	return _disciplines->size();
}
string& disciplines::operator[](const int index)
{
	int n = 0;
	list<string>::iterator it = _disciplines->begin();
	while (n != index)
	{
		n++;
		it++;
	}
	return (*it);
}

menu* disciplines::getList()
{
	menu* result = new menu;
	for (list<string>::iterator it = _disciplines->begin(); it != _disciplines->end(); it++)
		result->Add((*it));
	return result;
}