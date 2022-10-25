#pragma once
#include "Figure.h"
#include "Menu.h"
//класс, который наследует класс Figure и представляет работу для такой фигуры как Круг
class Circle : 
	public Figure
{
public:
	Circle();
	Circle(int radius);
	double Square();
	int Perimetr();
	int GetRadius();
	void SetRadius(int radius);
	void Print();
	Menu* ToMenu();
	void Update(int firstParam, int secondParam = 0, int threadParam = 0);
};

