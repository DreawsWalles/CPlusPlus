#include <iostream>
#include "trie_tree.h"
#include "menu.h"
#include <Windows.h>
#include <fstream>

bool check_not_odd(string word)
{
	return word.length() % 2 != 0;
}

bool check_odd(string word)
{
	return word.length() % 2 == 0;
}

bool check(string)
{
	return true;
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

bool InputKeyboard(trie_tree*& tree)
{
	int choice;
	string element;
	menu* menu_input = new menu;
	menu_input->Add("Да");
	menu_input->Add("Нет");
	do
	{
		cout << "Введите элемент: ";
		cin >> element;
		if (!tree->Add(element))
			return false;
		cout << "Добавить ещё один элемент" << endl;
		cin.get();
		menu_input->Print();
		choice = menu_input->Choice("Добавить еще один элемент?");
		if (choice == 1)
			system("cls");
	} while (choice != 2);
	return true;
}

bool InputFile(trie_tree*& tree)
{
	string fileName;
restart:
	while (!inputFileName(fileName))
	{
		system("pause");
		system("cls");
	}
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "Файл не удалось открыть. Выберите действие: " << endl;
		menu* menu_input = new menu;
		menu_input->Add("Ввести заново");
		menu_input->Add("Вернуться в галвное меню");
		menu_input->Print();
		int choice = menu_input->Choice("Файл не удалось открыть.Выберите действие :");
		switch (choice)
		{
		case 1:
			system("cls");
			goto restart;
			break;
		case 2:
			delete menu_input;
			return false;
		}
	}
	string element;
	while (file >> element)
		if (tree->Add(element))
			return false;
	return true;
}

bool AddElement(trie_tree*& tree)
{
	menu* menu_input = new menu;
	cout << "Выберите действие:" << endl;
	menu_input->Add("Ввести элемент с клавиатуры");
	menu_input->Add("Считать данные из файла");
	menu_input->Print();
	int choice = menu_input->Choice("Выберите действие:");
	system("cls");
	switch (choice)
	{
	case 1:
		delete menu_input;
		return InputKeyboard(tree);
	case 2:
		delete menu_input;
		return InputFile(tree);
	}
}

void PrintTree(trie_tree* tree)
{
	tree->Print();
	cout << endl;
	system("pause");
}

bool DeleteElement(trie_tree*& tree)
{
	tree->Print();
	cout << endl << "Введите элемент для удаления: ";
	string element;
	cin >> element;
	return tree->Delete(element);
}

int mainTask(trie_tree* tree)
{
	menu* menu_choice = new menu;
	int choice;
	cout << "Выберите действие:" << endl;
	menu_choice->Add("Вывести количество слов с нечетной длиной");
	menu_choice->Add("Вывести количество слов с четной длиной");
	menu_choice->Add("Вывести общее количество слов");
	menu_choice->Print();
	choice = menu_choice->Choice("Выберите действие");
	switch (choice)
	{
	case 1:
		return tree->getCountWordByCheck(check_not_odd);
	case 2:
		return tree->getCountWordByCheck(check_odd);
	case 3:
		return tree->getCountWordByCheck(check);
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	string s;
	trie_tree* tree = new trie_tree;
	menu* main_menu = new menu;
	int choice;
	cout << "Выберите действие:" << endl;
	main_menu->Add("Добавить элемент");
	main_menu->Add("Удалить элемент");
	main_menu->Add("Напечатать все элементы");
	main_menu->Add("Посчитать количество слов согласно критерию");
	main_menu->Add("Выход");
	do
	{
		main_menu->Print();
		choice = main_menu->Choice("Выберите действие:");
		system("cls");
		switch (choice)
		{
		case 0:
			delete main_menu;
			delete tree;
			break;
		case 1:
			if (AddElement(tree))
			{
				system("cls");
				cout << "Операция прошла успешшно" << endl;
			}
			else
			{
				system("cls");
				cout << "В ходе добавления элемента произошла ошибка" << endl;
			}
			system("pause");
			break;
		case 2:
			if (DeleteElement(tree))
			{
				system("cls");
				cout << "Элемент успешно удален" << endl;
			}
			else
			{
				system("cls");
				cout << "При удалении элемента произошла ошибка";
			}
			system("pause");
			break;
		case 3:
			PrintTree(tree);
			break;
		case 4:
		{
			int result = mainTask(tree);
			system("cls");
			cout << "Количество слов по по вашему запросу: " << result << endl;
			system("pause");
		}
			break;
		}
		system("cls");
	} while (choice != 0);
}


