#include <iostream>
#include "journal.h"
#include <Windows.h>
#include "Record.h"
#include "help.h"
#include "menu.h"
#include "Record.h"
#include "disciplines.h"
#include "Guide.h"
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
		result->Add("Напечатать справочник с использованием фильтра");
		result->Add("Вывести результаты сессии");
	}
	result->Add("Выход");
	return result;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");


	Guide list;
	menu* main_menu = new menu;
	disciplines dis;
	int choice;
	int size;
	do
	{
		size = list.size();
		main_menu = getMenu(size);
		main_menu->Print();
		choice = main_menu->Choice("Выберите действие: ");
		system("cls");
		switch (choice)
		{
		case 1:
			CorrectDisciplines(dis);
			break;
		case 2:
			InputElement(dis, list);
			break;
		case 3:
			Change(list);
			break;
		case 4:
			Delete(list);
			break;
		case 5:
			Print(list);
			break;
		case 6:
			Print_With_Filter(list, dis);
			break;	
		case 7:
			PrintResultSessions(list, dis);
			break;
		}
	} while (choice != 0);	
	delete main_menu;
}
