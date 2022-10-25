#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "menu.h"

using namespace std;
	

int CheckData(string s)
{
	int num;
	if (s.empty())
	{
		cout << "Введена пустая строка. Повторите ввод" << endl;
		return -1;
	}
	else
	{
		num = 0;
		int len = s.size();
		int i = 0;
		int n;
		while (i < len)
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				n = s[i] - '0';
				num = num * 10 + n;
				i++;
			}
			else
			{
				cout << "Введен некорректный символ: " << s[i] << " . Повторите ввод" << endl;
				return -1;
			}
		return num;
	}
}

bool CheckInputData(string s, int& result)
{
	int num;
	if (s.empty())
	{
		cout << "Введена пустая строка. Повторите ввод" << endl;
		return false;
	}
	else
	{
		num = 0;
		int len = s.size();
		int i = 0;
		int n;
		bool ok = true;
		if (s[i] == '-')
		{
			ok = false;
			i++;
		}
		while (i < len)
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				n = s[i] - '0';
				num = num * 10 + n;
				i++;
			}
			else
			{
				cout << "Введен некорректный символ: " << s[i] << " . Повторите ввод" << endl;
				return false;
			}
		if (ok)
			result = num;
		else
			result = num * (-1);
		return true;
	}
}

bool inputFileName(string& name)
{
	cout << "Введите имя файла: ";
	getline(cin, name);
	int size = name.size();
	int i = 0;
	while (i < size)
	{
		if ((name[i] == '/') || (name[i] == '\\') || (name[i] == ':') || (name[i] == '*') || (name[i] == '?') || (name[i] == '«') || (name[i] == '<') || (name[i] == '>') || (name[i] == '|'))
		{
			cout << endl << "Введен некорректный символ " << name[i] << endl;
			return false;
		}
		else
			i++;
	}
	return true;
}

void ArrayGenarete(string fileName, int n, int m)
{
	ofstream file(fileName);
	int count = 0;
	while (count <= n) 
	{
		count++;
		file << rand() % (2 * m + 1) - m << '\n';
	}
	file.close();
}

void randGenerate(string fileName, int n, int m)
{
	ofstream file(fileName);
	vector<int> vec(n);
	generate(vec.begin(), vec.end(), [&]() {return rand() % (2 * m + 1) - m; });
	for (auto element : vec)
		file << element << '\n';
	file.close();
}

ifstream FillToTheFile(int n, int m)
{
	string filename;
	while (!inputFileName(filename))
	{
		system("pause");
		system("cls");
	}
	menu* menu_choice = new menu();
	menu_choice->Add("Генерация чисел в цикле");
	menu_choice->Add("Генераация чисел с использовнием алгоритма generate");
	menu_choice->Print();
	int choice = menu_choice->Choice("");
	switch (choice)
	{
	case 1:
		ArrayGenarete(filename, n, m);
		break;
	case 2:
		randGenerate(filename, n, m);
		break;
	}
	delete menu_choice;
	ifstream result(filename);
	return result;	
}

vector<int> FillToTheContainer(ifstream& file)
{
	vector<int> result;
	if (!file.eof())
	{
		string line;
		int num;
		bool ok = false;
		do
		{
			getline(file, line);
			if (line != "")
			{
				if ((ok = CheckInputData(line, num)))
					result.push_back(num);
				else
				{
					system("pause");
					system("cls");
					result.clear();
					return result;
				}
			}
		} while (!file.eof() && ok);
		system("cls");
		cout << "Данные с файла успешно добавлены!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		system("cls");
		cout << "Данного файла не существует или он пуст" << endl;
		system("pause");
	}
	return result;
}

int GetSumOtr(vector<int>::iterator begin, vector<int>::iterator end)
{
	vector<int>::iterator element = begin;
	int result = 0;
	while (element != end)
	{
		if (*element < 0)
			result += *element;
		element++;
	}
	return result / 2;
}

void Modify(vector<int>::iterator begin, vector<int>::iterator end)
{
	int x = GetSumOtr(begin, end);
	vector<int> result;
	vector<int>::iterator element = begin;
	while (element != end)
	{
		*element += x;
		element++;
	}
}

vector<int> Modify(vector<int> vec)
{
	vector<int> result = vec;
	Modify(result.begin(), result.end());
	return result;
}

vector<int> Modify_transform(vector<int> vec)
{
	int x = GetSumOtr(vec.begin(), vec.end());
	transform(vec.begin(), vec.end(), vec.begin(), [&](int element) {return element + x; });
	return vec;
}

vector<int> Modify_For_each(vector<int> vec)
{
	int x = GetSumOtr(vec.begin(), vec.end());
	for_each(vec.begin(), vec.end(), [&](int& element) { element += x; });
	return vec;
}

void Print(vector<int> vec)
{
	menu* menu_print = new menu();
	int choice;
	menu_print->Add("Вывести содержимое контейнера в файл");
	menu_print->Add("Вывести содержимое контейнера на экран");
	menu_print->Print();
	choice = menu_print->Choice("");
	system("cls");
	switch (choice)
	{
	case 1:
	{
		string fileName;
		while (!inputFileName(fileName))
		{
			system("pause");
			system("cls");
		}
		ofstream file(fileName);
		for (auto element : vec)
			file << element << '\n';
		file.close();
	}
		break;
	case 2:
		for (auto element : vec)
			cout << element << ' ';
		break;
	}
	cout << endl << "Контейнер сохранен" << endl;
	system("pause");
	system("cls");
}

int Amount(vector<int> vec)
{
	int result = 0;
	for (auto element : vec)
		result += element;
	return result;
}

double Averadge(vector<int> vec)
{
	return Amount(vec) / vec.size();
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	ifstream file;
	int n, m;
	string s;
	do
	{
		cout << "Заполнение файла количеством чисел N из диапазона [-m; m]" << endl;
		cout << "Введите количество чисел N для записи в файл: ";
		getline(cin, s);
		if ((n = CheckData(s)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (n == -1);
	system("cls");
	do
	{
		cout << "Заполнение файла количеством чисел N из диапазона [-m; m]" << endl;
		cout << "Введите число m для диапазона [-m; m]: ";
		getline(cin, s);
		if ((m = CheckData(s)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (m == -1);
	system("cls");
	file = FillToTheFile(n, m);
	vector<int> vec = FillToTheContainer(file);
	menu menu_main;
	menu_main.Add("Заполнение контейнера из файла");
	menu_main.Add("Модифицировать контейнер");
	menu_main.Add("Вывести содержимое контейнера");
	menu_main.Add("Вывести среднее арифметическое элементов контейнера");
	menu_main.Add("Вывести сумму элементов контейнера");
	menu_main.Add("Выход");
	int choice = 0;
	do
	{
		menu_main.Print();
		choice = menu_main.Choice("");
		system("cls");
		switch (choice)
		{
		case 1:
		{
			menu* menu_input = new menu();
			menu_input->Add("Сгенерировать файл");
			menu_input->Add("Считать из существующего");
			menu_input->Print();
			int n = menu_input->Choice("");
			system("cls");
			switch (n)
			{
			case 1:
				do
				{
					cout << "Заполнение файла количеством чисел N из диапазона [-m; m]" << endl;
					cout << "Введите количество чисел N для записи в файл: ";
					getline(cin, s);
					if ((n = CheckData(s)) == -1)
					{
						system("pause");
						system("cls");
					}
				} while (n == -1);
				system("cls");
				do
				{
					cout << "Заполнение файла количеством чисел N из диапазона [-m; m]" << endl;
					cout << "Введите число m для диапазона [-m; m]: ";
					getline(cin, s);
					if ((m = CheckData(s)) == -1)
					{
						system("pause");
						system("cls");
					}
				} while (m == -1);
				system("cls");
				file = FillToTheFile(n, m);
				vec = FillToTheContainer(file);
				break;
			case 2:
			{
				string filename;
				while (!inputFileName(filename))
				{
					system("pause");
					system("cls");
				}
				file.open(filename);
				vec.clear();
				vec = FillToTheContainer(file);
			}
				break;
			}
			delete menu_input;
		}
			break;
		case 2:
		{
			menu* menu_modify = new menu();
			menu_modify->Add("Модицифировать контейнер");
			menu_modify->Add("Модифицировать контейнер с указаниями границ");
			menu_modify->Add("Модифицировать контейнер с помощью transform");
			menu_modify->Add("Модифицировать котнейнер с помощью for each");
			menu_modify->Print();
			int n = menu_modify->Choice("");
			system("cls");
			switch (n)
			{
			case 1:
			{
				vec = Modify(vec);
			}
				break;
			case 2:
			{
				int beg, end;
				string s;
				do
				{
					cout << "Введите границу от 1 до " << vec.size() << " :";
					cout << "Введите нижнюю границу: ";
					getline(cin, s);
					if ((beg = menu_modify->CheckChoise(s, 0, vec.size() - 1)) == -1)
					{
						system("pause");
						system("cls");
					}
				} while (beg == -1);
				system("cls");
				do
				{
					cout << "Введите границу от " << beg + 1 << " до " << vec.size() << " :";
					cout << "Введите верхнюю границу: ";
					getline(cin, s);
					if ((end = menu_modify->CheckChoise(s, beg + 1, vec.size())) == -1)
					{
						system("pause");
						system("cls");
					}
				} while (end == -1);
				vector<int>::iterator iter_beg = vec.begin();
				vector<int>::iterator iter_end = iter_beg;
				advance(iter_beg, beg - 1);
				advance(iter_end, end);
				Modify(iter_beg, iter_end);
			}
				break;
			case 3:
			{
				vec = Modify_transform(vec);
			}
			case 4:
			{
				vec = Modify_transform(vec);
			}
				break;
			}
			delete menu_modify;
		}
			break;
		case 3:
			Print(vec);
			break;
		case 4:
			cout << "Среднее арифметическое элементов контейнера: " << Averadge(vec) << endl;
			system("pause");
			system("cls");
			break;
		case 5:
			cout << "Сумма элементов контейнера: " << Amount(vec) << endl;
			system("pause");
			system("cls");
			break;
		}
	} while (choice != 0);
	return 0;

}

