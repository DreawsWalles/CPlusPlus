#include "Overflow.h"

Overflow::Overflow()
{
	_head = new List();
}
void Overflow::push(int x)
{
	_head->add_end(x);
}

void Overflow::pop(int el)
{
	_head->del_end();
}

int Overflow::top()
{
	int size = _head->get_size();
	return _head->get_el(size);
}

void Overflow::add(std::string s)
{
	int size = s.size();
	int n;
	std::string num = "";
	int i = 0;
	int j = 0;
	while (i < size)
	{
		while (s[i] != ' ')
		{
			num[j] += s[i];
			i++;
			j++;
		}
		i++;
		j = 0;
		n = std::stoi(num);
		num = "";
		push(n);
	}
}
void Overflow::clear()
{
	while (_head->get_size() != 0)
	{
		_head->del_end();
	}
}

std::string Overflow::ToString()
{
	std::string s = "";
	int size = _head->get_size();
	for (int i = 0; i < size; i++)
	{
		s += _head->get_el(i);
		s += " ";
	}
	return s;
}
