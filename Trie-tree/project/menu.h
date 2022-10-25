#pragma once
#include <list>
#include <string>


using namespace std;

//--------
//Список для менюшки
struct LinkNode
{
	string _node;
	LinkNode* next;
};





class menu
{
private:
	LinkNode* _head;
	int _size;
public:
	int CheckChoise(string s, int borderBeg, int borderEnd);
	menu();
	~menu();
	void Add(string s);
	void Print();
	int Count();
	int Choice(string theme);
	menu& operator=(menu other);
	
};

