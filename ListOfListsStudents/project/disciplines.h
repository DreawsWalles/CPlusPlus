#pragma once
#include <string>
#include <list>
#include "menu.h"

using namespace std;

class disciplines
{
private:
	list<string>* _disciplines;
	

public :
	disciplines();
	~disciplines();
	bool Add(string value);
	bool Remove(string value);
	bool Change(string value, string change);
	int size();
	string& operator[](const int index);
	menu* getList();
};

