#include <iostream>
#include "Tree.h"
#include <windows.h>
#include "HelpFunction.h"


//выбор типа данных
int menuStart()
{
	string choise;
	int num;
	do
	{
		cout << "Выберите тип данных для бинарного дерева:" << endl;
		cout << "1. Целочисленный" << endl;
		cout << "2. Строковый" << endl;
		cout << "3. Символьный" << endl;
		cout << "4. Своя структура" << endl;
		cout << "0. Выйти" << endl;
		cout << "-> ";
		getline(cin, choise);
		if ((num = CheckChoise(choise, 0, 4)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (num == -1);
	if (num == 0)
		exit;
	return num;
} 
//меню выбора действия с деревом
int menu(int size)
{
	int border;
	string choise;
	int num;
	do
	{
		switch (size)
		{
		case 0:
			cout << "Выберите действие:" << endl;
			cout << "1. Добавить элемент" << endl;
			cout << "0. Выйти" << endl;
			border = 1;
			break;
		default:
			cout << "Выберите действие:" << endl;
			cout << "1. Добавить элемент" << endl;
			cout << "2. Удалить элемент" << endl;
			cout << "3. Распечатать дерево" << endl;
			cout << "4. Вывести размер дерева" << endl;
			cout << "5. Вывести высоту дерева" << endl;
			cout << "6. Найти элемент" << endl;
			cout << "0. Выйти" << endl;
			border = 6;
			break;
		}
		cout << "-> ";
		getline(cin, choise);
		if ((num = CheckChoise(choise, 0, border)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (num == -1);
	return num;
}

void input(int& t)
{
	string s;
	do
	{
		cout << "Введите значение: ";
		getline(cin, s);
		if ((t = checkOnCorrect(s)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (t == -1);
}

void input(string& t)
{
	cout << "Введите значение: ";
	getline(cin, t);
}

void input(char& t)
{
	string s;
	do
	{
		if (s.length() > 1)
		{
			cout << "Введено больше одного символа. Повторите ввод" << endl;
			system("pause");
			system("cls");
		}
	} while (s.length() > 1);
	t = s[0];
}

void input(MyType& t)
{
	cin >> t;
}

template <typename T>
void mainWork(Tree<T> tree)
{
	int num;
	T t;
	while (num = menu(tree.getSize()))
	{
		system("cls");
		switch (num)
		{
			case 1:
				input(t);
				tree.addNode(t);
				break;
			case 2:
				input(t);
				tree.deleteNode(t);
				break;
			case 3:
				tree.print();
				cout << endl;
				system("pause");
				break;
			case 4:
				cout << "Размер дерева: " << tree.getSize() << endl;
				system("pause");
				break;
			case 5:
				cout << "Высота дерева: " << tree.getHeight() << endl;
				system("pause");
				break;
			case 6:
				input(t);
				cout << "Элемент " << t << " ";
				if (tree.search(t))
					cout << "найден" << endl;
				else
					cout << "не найден" << endl;
				system("pause");
				break;
		}
		system("cls");
	}
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	
	int num = menuStart();	
	system("cls");
	switch (num)
	{
		case 1:
		{
			Tree<int> tree;
			mainWork(tree);
			break;
		}
		case 2:
		{
			Tree<string> tree;
			mainWork(tree);
			break;
		}
		case 3:
		{
			Tree<char> tree;
			mainWork(tree);
			break;
		}
		case 4:
		{
			Tree<MyType> tree;
			mainWork(tree);
			break;
		}
	}
}