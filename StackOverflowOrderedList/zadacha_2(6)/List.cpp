#include "List.h"


List::List()
{
	_head = new list;
	_size = 0;
}
List::~List()
{
	delete _head;
}
void List::add_beg( int x)
{
	if (_size == 0)
	{
		_head = new list;
		_head->_x = x;
		_head->_next = nullptr;
	}
	else
	{
		list* tptr = new list;
		tptr->_next = _head;
		tptr->_x = x;
		_head = tptr;
	}
	_size++;
}
void List::add_end(int x)
{
	if (_size == 0)
	{
		_head = new list;
		_head->_x = x;
		_head->_next = nullptr;
	}
	else
	{
		list* tptr = new list;
		tptr = _head;
		while (tptr->_next != nullptr)
			tptr = tptr->_next;
		list* p = new list;
		p->_x = x;
		p->_next = nullptr;
		tptr->_next = p;
	}
	_size++;
}

bool List::add_after(int el, int x)
{
	if (_size == 0)
	{
		_head = new list;
		_head->_x = x;
		_head->_next = nullptr;
	}
	else
	{
		list* tptr = new list;
		tptr = _head;
		while ((tptr->_x != el) && (tptr->_next != nullptr))
			tptr = tptr->_next;
		if ((tptr->_x != el) && (tptr->_next == nullptr))
			return false;
		else
		{
			list* p = new list;
			list* q = new list;
			q = tptr->_next;
			p->_x = x;
			p->_next = q;
			tptr->_next = p;
			_size++;
			return true;
		}
	}
}

void List::del_beg()
{
	if (_size != 0)
	{
		list* tptr = new list;
		tptr = _head->_next;
		delete _head;
		_head = tptr;
		_size--;
	}
}

void List::del_end()
{
	if (_size != 0)
	{
		list* tptr = new list;
		list* p = new list;
		tptr = _head;
		while (tptr->_next != nullptr)
		{
			p = tptr;
			tptr = tptr->_next;
		}
		delete tptr;
		p->_next = nullptr;
		_size--;
	}
}
bool List::del_after(int el)
{
	if (_size >= 2)
	{
		list* tptr = new list;
		tptr = _head;
		while ((tptr->_x != el) && (tptr->_next != nullptr))
			tptr = tptr->_next;
		if ((tptr->_x != el) && (tptr->_next == nullptr))
			return false;
		else
		{
			list* p = new list;
			list* q = new list;
			q = tptr->_next;
			p = q->_next;
			tptr->_next = p;
			delete q;
			_size--;
			return true;
		}
	}
}

bool List::search_el(int el)
{
	list* tptr = new list;
	tptr = _head;
	while ((tptr->_x != el) && (tptr->_next != nullptr))
		tptr = tptr->_next;
	if ((tptr->_x != el) && (tptr->_next == nullptr))
		return false;
	return true;
}

bool List::del_el(int el)
{
	if (_size != 0)
	{
		list* tptr = new list;
		list* p = new list;
		tptr = _head;
		while ((tptr->_x != el) && (tptr->_next != nullptr))
		{
			p = tptr;
			tptr = tptr->_next;
		}
		if ((tptr->_x != el) && (tptr->_next == nullptr))
			return false;
		else
		{
			list* q = new list;
			q = tptr->_next;
			p->_next = q;
			delete tptr;
			_size--;
			return true;
		}
	}
}

void List::add_el_in_list(int x)
{
	if (_size == 0)
		_head->_x = x;
	else
	{
		list* tptr = new list;
		list* p = new list;
		tptr = _head;
		while ((tptr->_x <= x) && (tptr->_next != nullptr))
		{
			p = tptr;
			tptr = tptr->_next;
		}
		list* q = new list;
		if ((tptr->_x <= x) && (tptr->_next == nullptr))
		{
			q->_x = x;
			q->_next = nullptr;
			tptr->_next = q;
		}
		else
		{
			q->_x = x;
			q->_next = tptr;
			p->_next = q;
		}
	}
	_size++;
}

int List::get_size()
{
	return _size;
}

int List::get_el(int size)
{
	list *tptr = new list;
	tptr = _head;
	for (int i = 0; i < size; i++)
		tptr = tptr->_next;
	return tptr->_x;
}
void List::set_size(int size) 
{
	_size = size;
}