#include "stack.h"

stack::stack(int count)
{
	size = 0;
	n = count;
	if (n > 1000)
		n = 1000;
}
bool stack::empty()
{
	return size == 0;
}

string stack::top()
{
	if (size)
		return mass[size - 1];
	return "";
}
bool stack::push(string s)
{
	if (size < n)
	{
		mass[size] = s;
		size++;
		return true;
	}
	return false;
}

bool stack::pop()
{
	if (size)
	{
		size--;
		return true;
	}
	return false;
}

void stack::clear()
{
	size = 0;
}
