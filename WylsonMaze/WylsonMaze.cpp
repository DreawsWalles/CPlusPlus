#include <iostream>
#include "menu.h"
#include "ConsoleRepository.h"
#include "RandomMaze.h"
#include "Maze.h"
#include "CircleMaze.h"
#include "ModifyMaze.h"
#include "SolveMaze.h"
#include "AntsAlgorithm.h"


IRepository* _repository;


int ConvertToInt(string param)
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
			_repository->Output("Считан некорректный символ: " + param.substr(i, 1) + "\r\n");
			return -1;
		}
	}
	return num;
}

int CheckChoice(int param, int borderBeg, int borderEnd)
{
	if (param == -1)
		return -1;
	if (param < borderBeg || param > borderEnd)
	{
		_repository->Output("Считанное значение некорректно. Значение должно быть в диапазоне от " + to_string(borderBeg) + " до " + to_string(borderEnd) + "\r\n");
		return -1;
	}
	return param;
}

int ConvertToIntConsole(string param)
{
	int num;
	if (param.empty())
	{
		cout << "Считана пустая строка. Повторите ввод" << endl;
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
			cout << "Считан некорректный символ: " + param.substr(i, 1) << endl;
			return -1;
		}
	}
	return num;
}

int CheckChoiceConsole(int param, int borderBeg, int borderEnd)
{
	if (param == -1)
		return -1;
	if (param < borderBeg || param > borderEnd)
	{
		cout << "Считанное значение некорректно. Значение должно быть в диапазоне от " + to_string(borderBeg) + " до " + to_string(borderEnd) << endl;
		return -1;
	}
	return param;
}

Menu* InitStartMenu()
{
	Menu* menu = new Menu("Выберите действие:", _repository);
	menu->Add("Инициализировать лабиринт");
	menu->Add("Завершить работу программы", true);
	return menu;
}

Menu* InitMainMenu()
{
	Menu* menu = new Menu("Выберите действие:", _repository);
	menu->Add("Инициализировать лабиринт");
	menu->Add("Найти пути решения лабиринта");
	menu->Add("Напечатать лабиринт");
	menu->Add("Изменить начало лабиринта");
	menu->Add("Изменить конец лабиринта");
	menu->Add("Завершить работу программы", true);
	return menu;
}

Maze* InitMaze()
{
	_repository->Clear();
	int size = -1;
	string s;
	while (size == -1)
	{
		_repository->Output("Введите размер лабиринта: ");
		s = _repository->Input();
		if ((size = CheckChoice(ConvertToInt(s), 30, 1000)) == -1)
		{
			_repository->Output("\r\n");
			_repository->Pause();
			_repository->Clear();
		}
	}
	_repository->Clear();
	return new RandomMaze(size);
}

IRepository* InitRepository()
{
	int choice;
	string s;
	while (true)
	{
		cout << "Выберите репозиторий:" << endl;
		cout << "1. Консольный репозиторий" << endl;
		cout << "<--0. Завершить работу программы" << endl;
		cout << "->";
		getline(cin, s);
		if ((choice = CheckChoiceConsole(ConvertToIntConsole(s), 0, 1)) == -1)
		{
			system("pause");
			system("cls");
		}
		switch (choice)
		{
		case 1:
			return new ConsoleRepository();
		case 0:
			return nullptr;
		}
	}
}

SolveMaze* InitSolve()
{
	Menu* menu = new Menu("Выберите алгоритм для решения лабиринта", _repository);
	menu->Add("Муравьиный алгоритм");
	menu->Add("Вернуться в главное меню", true);
	int choice;
	while (true)
	{
		menu->Print();
		choice = menu->Choice();
		_repository->Clear();
		switch (choice)
		{
		case 1:
			return new AntsAlgorithm();
		case 0:
			return nullptr;
		}
	}
}

void ChangeStartPoint(Maze* maze)
{
	int x = -1;
	int y;
	while (true)
	{
		_repository->Clear();
		setlocale(LC_ALL, "C");
		maze->Print(_repository);
		_repository->Output("\n\r");
		setlocale(LC_ALL, "Russian");
		if (x == -1)
		{
			_repository->Output("Введите координату x: ");
			if ((x = CheckChoice(ConvertToInt(_repository->Input()), 0, maze->GetSize())) == -1)
			{
				_repository->Output("\r\n");
				_repository->Pause();
				_repository->Clear();
				continue;
			}
		}
		else
			_repository->Output("Координата x: " + to_string(x) + "\r\n");
		_repository->Output("Введите координату y: ");
		if ((y = CheckChoice(ConvertToInt(_repository->Input()), 0, maze->GetSize())) == -1)
		{
			_repository->Output("\r\n");
			_repository->Pause();
			_repository->Clear();
			continue;
		}
		try
		{
			Maze::Point tmp;
			tmp.y = y;
			tmp.x = x;
			Maze::Point oldPoint = maze->GetStartPoint();
			maze->ChangeStartPoint(tmp);
			while (true)
			{
				_repository->Clear();
				setlocale(LC_ALL, "C");
				maze->Print(_repository);
				_repository->Output("\n\r");
				setlocale(LC_ALL, "Russian");
				_repository->Output("Применить значение координат?(Y/N)");
				char ans = _repository->Input()[0];
				switch (ans)
				{
					case 'Y':
						return;
					case 'y':
						return;
					case 'N':
						maze->ChangeStartPoint(oldPoint);
						return;
					case 'n':
						maze->ChangeStartPoint(oldPoint);
						return;
					default:
						_repository->Output("Считан некорректный символ: \"");
						_repository->Output(ans);
						_repository->Output('\"');
						_repository->Output("\r\n");
						_repository->Output("Повторите ввод\r\n");
						_repository->Pause();
						break;
				}
			}
		}
		catch (exception e)
		{
			_repository->Output(e.what());
			_repository->Output("\r\n");
			_repository->Pause();
			_repository->Clear();
			y = -1;
			x = -1;
		}
	}
}

void ChangeEndPoint(Maze* maze)
{
	int x = -1;
	int y;
	while (true)
	{
		_repository->Clear();
		setlocale(LC_ALL, "C");
		maze->Print(_repository);
		_repository->Output("\n\r");
		setlocale(LC_ALL, "Russian");
		if (x == -1)
		{
			_repository->Output("Введите координату x: ");
			if ((x = CheckChoice(ConvertToInt(_repository->Input()), 0, maze->GetSize())) == -1)
			{
				_repository->Output("\r\n");
				_repository->Pause();
				_repository->Clear();
				continue;
			}
		}
		else
			_repository->Output("Координата x: " + to_string(x) + "\r\n");
		_repository->Output("Введите координату y: ");
		if ((y = CheckChoice(ConvertToInt(_repository->Input()), 0, maze->GetSize())) == -1)
		{
			_repository->Output("\r\n");
			_repository->Pause();
			_repository->Clear();
			continue;
		}
		try
		{
			Maze::Point tmp;
			tmp.y = y;
			tmp.x = x;
			Maze::Point oldPoint = maze->GetEndPoint();
			maze->ChangeEndPoint(tmp);
			while (true)
			{
				_repository->Clear();
				setlocale(LC_ALL, "C");
				maze->Print(_repository);
				_repository->Output("\n\r");
				setlocale(LC_ALL, "Russian");
				_repository->Output("Применить значение координат?(Y/N)");
				char ans = _repository->Input()[0];
				switch (ans)
				{
					case 'Y':
						return;
					case 'y':
						return;
					case 'N':
						maze->ChangeEndPoint(oldPoint);
						return;
					case 'n':
						maze->ChangeEndPoint(oldPoint);
						return;
					default:
						_repository->Output("Считан некорректный символ: \"");
						_repository->Output(ans);
						_repository->Output('\"');
						_repository->Output("\r\n");
						_repository->Output("Повторите ввод\r\n");
						_repository->Pause();
						break;
				}
			}
		}
		catch (exception e)
		{
			_repository->Output(e.what());
			_repository->Output("\r\n");
			_repository->Pause();
			_repository->Clear();
			y = -1;
			x = -1;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Maze* maze = nullptr;
	int choice;
	Menu* menu;
	_repository = InitRepository();
	if (_repository == nullptr)
		exit(0);
	_repository->Clear();
	do
	{
		menu = maze == nullptr ? InitStartMenu() : InitMainMenu();
		menu->Print();
		choice = menu->Choice();
		switch (choice)
		{
			case 1:
				maze = InitMaze();
				break;
			case 2:
			{
				_repository->Clear();
				SolveMaze* solve = InitSolve();
				if (solve != nullptr)
					try
					{						
						vector<Maze::Point> tmp = solve->GetWaysSolve(maze);	
						if (tmp.size() != 0)
						{
							_repository->Clear();
							setlocale(LC_ALL, "C");
							maze->PrintWaysSolve(tmp, _repository);
							setlocale(LC_ALL, "Russian");
							_repository->Output("\n\r");
							_repository->Pause();
						}
						else
						{
							_repository->Output("В данном лабиринте нет решений\r\n");
							_repository->Pause();
						}
					}
					catch(exception e){	}
			}
				break;
			case 3:
				_repository->Clear();
				setlocale(LC_ALL, "C");
				maze->Print(_repository);
				_repository->Output("\n\r");
				setlocale(LC_ALL, "Russian");
				_repository->Pause();
				break;
			case 4:
				ChangeStartPoint(maze);
				break;
			case 5:
				ChangeEndPoint(maze);
				break;
		}
		_repository->Clear();
	} while (choice != 0);
	return 0;
}

