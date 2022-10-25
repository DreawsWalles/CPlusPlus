#pragma once

struct list
{
	int _x;
	list* _next;
};
class List
{
protected:
	list *_head;
	int _size;
public:
	List();
	~List();
	void add_beg(int x);
	void add_end(int x);
	bool add_after(int el, int x);
	void del_beg();
	void del_end();
	bool del_after(int el);
	bool search_el(int el);
	bool del_el(int el);
	void add_el_in_list(int x);
	void set_size(int size);
	int  get_size();
	int get_el(int size);
};

