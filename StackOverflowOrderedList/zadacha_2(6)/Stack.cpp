#include "Stack.h"

Stack::Stack()
{
	_head = new List();
}

void Stack::push(int x)
{
	_head->add_beg(x);
}
void Stack::pop(int el)
{
	_head->del_beg();
}

int Stack::top()
{
	return _head->get_el(1);
}

void Stack::add(std::string s)
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

void Stack::clear()
{
	while (_head->get_size() != 0)
	{
		_head->del_end();
	}
}

std::string Stack::ToString()
{
	std::string s = "";
	int size = _head->get_size();
	for (int i = 0; i < size; i++)
	{
		s += std::to_string(_head->get_el(i));
		s += " ";
	}
	return s;
}
