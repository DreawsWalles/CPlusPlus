#include <iostream>
#include "Circle.h"
#include "Menu.h"
#include <windows.h>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "HelpClasses.h"

int InputValue(string message)
{
	int result;
	string field;
	Menu* menu = new Menu("Ввести данные ещё раз?");
	menu->Add("Да");
	menu->Add("Нет", true);
	do
	{
		cout << message << endl;
		cout << "->";
		getline(cin, field);
		if ((result = HelpClasses::CheckChoise(field, 1)) == -1)
		{
			menu->Print();
			if (menu->Choice() == 0)
			{
				delete menu;
				return -1;
			}
			system("cls");
		}
		return result;
	} while (true);
}

Figure* InitCircle()
{
	int radius;
	if ((radius = InputValue("Введите радиус:")) == -1)
		return nullptr;
	return new Circle(radius);
}

Figure* InitRectangle()
{
	int width;
	int height;
	if ((width = InputValue("Введите ширину:")) == -1)
		return nullptr;
	if ((height = InputValue("Введите высоту:")) == -1)
		return nullptr;
	return new MyRectangle(height, width);
}

Figure* InitTrapezoid()
{
	int width;
	int height;
	int length;
	if ((width = InputValue("Введите ширину:")) == -1)
		return nullptr;
	if ((height = InputValue("Введите высоту:")) == -1)
		return nullptr;
	if ((length = InputValue("Введите длинну:")) == -1)
		return nullptr;
	return new Trapezoid(width, length, height);
}

Figure* CorrectionCircle(Figure* oldFigure)
{
	int choice;
	do
	{
		Menu* menu = oldFigure->ToMenu();
		menu->Add("Выход из редактирования", true);
		int field;
		menu->Print();
		choice = menu->Choice();
		system("cls");
		string s;
		switch (choice)
		{
		case 0:
			delete menu;
			return oldFigure;
		case 1:
			if ((field = InputValue("Выведите радиус:")) != -1)
				oldFigure->Update(field);
			break;
		}
	} while (true);
}

Figure* CorrectionRectangle(Figure* oldFigure)
{
	int choice;
	do
	{
		Menu* menu = oldFigure->ToMenu();
		menu->Add("Выход из редактирования", true);
		int field;
		menu->Print();
		choice = menu->Choice();
		system("cls");
		string s;
		switch (choice)
		{
		case 0:
			delete menu;
			return oldFigure;
		case 1:
			if ((field = InputValue("Выведите ширину:")) != -1)
				oldFigure->Update(0, field);
			break;
		case 2:
			if ((field = InputValue("Выведите высоту:")) != -1)
				oldFigure->Update(field, 0);
		}
	} while (true);
}

Figure* CorrectionTrapezoid(Figure* oldFigure)
{
	int choice;
	do
	{
		Menu* menu = oldFigure->ToMenu();
		menu->Add("Выход из редактирования", true);
		int field;
		menu->Print();
		choice = menu->Choice();
		system("cls");
		string s;
		switch (choice)
		{
		case 0:
			delete menu;
			return oldFigure;
		case 1:
			if ((field = InputValue("Выведите ширину:")) != -1)
				oldFigure->Update(field);
			break;
		case 2:
			if ((field = InputValue("Выведите длину:")) != -1)
				oldFigure->Update(0,field);
			break;
		case 3:
			if ((field = InputValue("Выведите выстоу:")) != -1)
				oldFigure->Update(0, 0, field);
			break;
		}
		system("cls");
	} while (true);
}

void WorkWithFigure(Figure* (*InitFugure)(), Figure* (*CorrectionFugure)(Figure* oldFilure))
{
	int choice;
	Figure* fig;
	if ((fig = InitFugure()) == nullptr)
		return;
	Menu* menu = new Menu("Выберите действие: ");
	menu->Add("Посчитать периметр фигуры");
	menu->Add("Посчитать площадь фигуры");
	menu->Add("Изменить значения сторон фигуры");
	menu->Add("Выйти в главное меню", true);
	do
	{
		menu->Print();
		choice = menu->Choice();
		system("cls");
		switch (choice)
		{
			case 1:
				cout << "Периметр данной фигуры: " << fig->Perimetr() << endl;
				system("pause");
			break;
			case 2:
				cout << "Площадь фигуры: " << fig->Square() << endl;
				system("pause");
				break;
			case 3:
				fig = CorrectionFugure(fig);
				break;
		}
		system("cls");
	} while (choice != 0);
	delete menu;
	delete fig;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    Menu* menu = new Menu("Выберите фигуру:");
    menu->Add("Круг");
    menu->Add("Трапеция");
    menu->Add("Прямоугольник");
    menu->Add("Выход", true);
    int choice;
    do
    {
        menu->Print();
        choice = menu->Choice();
		system("cls");
        switch (choice)
        {
			case 1:
				WorkWithFigure(&InitCircle, &CorrectionCircle);
				break;
			case 2:
				WorkWithFigure(&InitTrapezoid, &CorrectionTrapezoid);
				break;
			case 3:
				WorkWithFigure(&InitRectangle, &CorrectionRectangle);
				break;
        }
    } while (choice != 0);
	delete menu;
}

