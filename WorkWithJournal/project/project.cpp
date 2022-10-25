#include <iostream>
#include "Journal.h"
#include <Windows.h>
#include "Record.h"
#include "help.h"
#include "menu.h"
#include "functions.h"

menu* getMenu(int size)
{
	menu* result = new menu;
	result->Add("Добавить данные");
	if (size != 0)
	{
		result->Add("Изменить данные");
		result->Add("Удалить данные");
		result->Add("Печать");
		result->Add("Вывести средние баллы");
		result->Add("Поиск элементов");
	}
	result->Add("Выход");
	return result;
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	
	Journal list;
	menu* menu_main = new menu;
	int choice;
	do
	{
		menu_main = getMenu(list.size());
		menu_main->Print();
		cout << "Выберите дейтсвие" << endl;
		choice = menu_main->Choice("Выберите действие");
		system("cls");
		switch (choice)
		{
		case 1:
			Add(list);
			break;
		case 2:
			Change(list);
			break;
		case 3:
			Delete(list);
			break;
		case 4:
			Print(list);
			break;
		case 5:
			AverangeValue(list);
			break;
		case 6:
			Search(list);
			break;
		}
	} while (choice != 0);
}
