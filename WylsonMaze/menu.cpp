#include "menu.h"
#include <iostream>
#include <string>
#include <list>

Menu::Menu(IRepository* _rep)
{
	_repository = _rep;
	_list = new list<string>;
	_count = 0;
	_haveEnd = false;
}

Menu::Menu(string theme, IRepository* _rep)
{
	_repository = _rep;
	_list = new list<string>;
	_count = 0;
	_themeMenu = theme;
}

void Menu::ChangeTheme(string theme)
{
	_themeMenu = theme;
}

void Menu::Add(string item, bool isEnd)
{
	if (_haveEnd && isEnd)
		throw "Пункт меню для возврата уже добавлен";
	if (!isEnd)
	{
		_list->push_back(item);
		_count++;
	}
	else
	{
		_list->push_front(item);
		_haveEnd = true;
		_count++;
	}
}

void Menu::Remove(int index)
{
	if (index >= _count)
		throw "Введен некорректный индекс";
	auto iter = _list->cbegin();
	int i = 0;
	while (i < index)
		iter++;
	_list->erase(iter);
	_count--;
}

void Menu::RemoveExit()
{
	_list->pop_front();
	_count--;
}

void Menu::Print()
{
	if (_count == 0)
		throw "В меню нет ни одного пункта";
	_repository->Output(_themeMenu + "\r\n");
	if (_haveEnd)
	{
		int i = 1;
		auto iter = _list->begin();
		string end = *iter;
		iter++;
		while (iter != _list->end())
		{
			_repository->Output(to_string(i) + ". " + *iter + "\r\n");
			i++;
			iter++;
		}
		_repository->Output("<--0. " + end);
	}
	else
	{
		int i = 1;
		for (auto iter = _list->begin(); iter != _list->end(); iter++, i++)
			_repository->Output(to_string(i) + ". " + *iter + "\r\n");
	}
	_repository->Output("\r\n-->");
}

int Menu::Choice()
{
	int result;
	string s;
	do
	{
		s = _repository->Input();
		result = _haveEnd ? CheckChoice(ConvertToInt(s), 0, _count) : CheckChoice(ConvertToInt(s), 1, _count);
		if (result == -1)
		{
			_repository->Pause();
			_repository->Clear();
			Print();
		}
	} while (result == -1);
	return result;
}

int Menu::ConvertToInt(string param)
{
	int num;
	if (param.empty())
	{
		_repository->Output("Считана пустая строка. Повторите ввод" + '\r\n');
		return -1;
	}
	num = 0;
	int length = param.length();
	int i = 0;
	int n;
	while (i < length)
	{
		if (param[i] >= '0' && param[i] <= '9')
		{
			n = param[i] - '0';
			num = num * 10 + n;
			i++;
		}
		else
		{
			_repository->Output("Считан некорректный символ: " + param.substr(i,1) + "\r\n");
			return -1;
		}
	}
	return num;
}
int Menu::CheckChoice(int param, int borderBeg, int borderEnd)
{
	if(param == -1)
		return -1;
	if (param < borderBeg || param > borderEnd)
	{
		_repository->Output("Считанное значение некорректно. Значение должно быть в диапазоне от " + to_string(borderBeg) + " до " + to_string(borderEnd) + "\r\n");
		return -1;
	}
	return param;
}
Menu::~Menu()
{
	delete _list;
}
