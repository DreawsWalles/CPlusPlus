#include "OrderedList.h"
OrderedList::OrderedList()
{
	_head = new List();
}

void OrderedList::push(int x)
{
	_head->add_el_in_list(x);
}
void OrderedList::pop(int el)
{
	_head->del_el(el);
}

void OrderedList::add(std::string s)
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

void OrderedList::clear()
{
	while (_head->get_size() != 0)
	{
		_head->del_end();
	}
}

std::string OrderedList::ToString()
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
