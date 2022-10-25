#include <iostream>
#include "DataTime.h"
#include "Menu.h"
#include "Triad.h"
#include "HelpClasses.h"
#include <windows.h>

Triad* InitTriad()
{
	int first;
	if ((first = HelpClasses::InputValue("Введите первое число:")) == -1)
		return nullptr;
	int second;
	if ((second = HelpClasses::InputValue("Введите второе число:")) == -1)
		return nullptr;
	int thread;
	if ((thread = HelpClasses::InputValue("Введите третье число:")) == -1)
		return nullptr;
	return new Triad(first, second, thread);
}
DataTime* InitDataTime()
{
	int day;
	if ((day = HelpClasses::InputValue("Введите день:")) == -1)
		return nullptr;
	int month;
	if ((month = HelpClasses::InputValue("Введите месяц:")) == -1)
		return nullptr;
	int year;
	if ((year = HelpClasses::InputValue("Введите год:")) == -1)
		return nullptr;
	return new DataTime(day, month, year);
}

void WorkWithTriad(Triad* triad)
{
	Menu* menuDoing = new Menu("Выберите действие:");
	menuDoing->Add("Напечатать данные");
	menuDoing->Add("Увеличить первое поле");
	menuDoing->Add("Увеличить второе поле");
	menuDoing->Add("Увеличить третье поле");
	menuDoing->Add("Ввести данные ещё раз");
	menuDoing->Add("Вуернуться назад", true);
	int choice;
	do
	{
		menuDoing->Print();
		choice = menuDoing->Choice();
		system("cls");
		switch (choice)
		{
			case 1:
				triad->Print();
				system("cls");
			break;
			case 2:
				triad->IncFirstField();
				break;
			case 3:
				triad->IncSecondField();
				break;
			case 4:
				triad->IncThreadField();
				break;
			case 5:
				Triad* current;
				if ((current = InitTriad()) == nullptr)
					triad = current;
				break;

		}
	} while (choice != 0);
	delete menuDoing;
}
void WorkWithDataTime(DataTime* dt)
{
	Menu* menuDoing = new Menu("Выберите действие:");
	menuDoing->Add("Напечатать данные");
	menuDoing->Add("Увеличить день");
	menuDoing->Add("Увеличить месяц");
	menuDoing->Add("Увеличить год");
	menuDoing->Add("Ввести данные ещё раз");
	menuDoing->Add("Увеличить дату на n");
	menuDoing->Add("Вернуться назад", true);
	int choice;
	do
	{
		system("cls");
		menuDoing->Print();
		choice = menuDoing->Choice();
		system("cls");
		switch (choice)
		{
		case 1:
			dt->Print();
			system("pause");
			break;
		case 2:
			dt->IncFirstField();
			break;
		case 3:
			dt->IncSecondField();
			break;
		case 4:
			dt->IncThreadField();
			break;
		case 5:
			DataTime * current;
			if ((current = InitDataTime()) == nullptr)
				dt = current;
			break;
		case 6:
			int value;
			if ((value = HelpClasses::InputValue("Введите количество дней")) != -1)
				dt->IncData(value);
			break;
		}
	} while (choice != 0);
	delete menuDoing;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");


	Menu* menu = new Menu("Выберите тип данных:");
	menu->Add("Тройка чисел");
	menu->Add("Формат даты");
	menu->Add("Выход", true);
	DataTime* dt;
	Triad* triad;
	int choice;
	do
	{
		menu->Print();
		choice = menu->Choice();
		system("cls");
		switch (choice)
		{
		case 1:
			while ((triad = InitTriad()) == nullptr);
			WorkWithTriad(triad);
			break;
		case 2:
			while ((dt = InitDataTime()) == nullptr);
			WorkWithDataTime(dt);
			break;
		}
	} while (choice != 0);
	delete menu;
}
