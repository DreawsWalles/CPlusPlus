#pragma once
#include <list>
#include <string>
#include <list>

using namespace std;

//--------
//������ ��� �������
struct LinkNode
{
	string _node;
	LinkNode* next;
};
//����� ������� ������������ ����� ����, � ������� �� ����� ��������� �����, �������� �� � ����� ������, ������� ��� ������ � ��������
class Menu
{
private:
	LinkNode* _head;
	int _size;
	bool haveEnd;
	string themeMenu;
public:
	void ChangeTheme(string  newTheme);
	Menu(string theme);
	~Menu();
	void Add(string s, bool isEnd = false);
	int Count();
	Menu& operator=(Menu other);
	void Delete(int index);
	void DeleteFirst();
	void DeleteLast();
	void DeleteExit();
	void Print();
	int Choice();
	list<string> ToList();
	void ChangeField(int index, string value);
	string GetField(int index);
};

