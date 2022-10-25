#pragma once
#include <list>
#include <string>
#include "IRepository.h"

using namespace std;





class Menu
{
private:
	list<string>* _list;
	int _count;
	bool _haveEnd;
	string _themeMenu;
	int ConvertToInt(string param);
	int CheckChoice(int param, int borderBeg, int borderEnd);
	IRepository* _repository;
public:
	~Menu();
	Menu(IRepository* _rep);
	Menu(string theme, IRepository* _rep);
	void ChangeTheme(string theme);
	void Add(string item, bool isEnd = false);
	void Remove(int index);
	void RemoveExit();
	void Print();
	int Choice();
};

