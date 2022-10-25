#include "Circle.h"
#include <math.h>
#include<iostream>

using namespace std;

Circle::Circle()
{
	_width = -1;
}
Circle::Circle(int radius)
{
	_width = radius;
}
void Circle::SetRadius(int radius)
{
	SetFirstParametr(radius);
}
int Circle::GetRadius()
{
	return GetFirstParametr();
}
double Circle::Square()
{
	if (_width == -1)
		throw "Фигура не задана";
	return 3.14 * pow(_width, 2);
}
int Circle::Perimetr()
{
	if (_width == -1)
		throw "Фигура не задана";
	return 3.14 * 2 * _width;
}
void Circle::Print()
{
	cout << "Радиус: " << GetFirstParametr() << endl;
}

Menu* Circle::ToMenu()
{
	Menu* result = new Menu("Выберите поле для изменения:");
	result->Add("Радиус: " + GetFirstParametr());
	return result;
}
void Circle::Update(int firstParam, int secondParam, int threadParam)
{
	if (firstParam != 0)
		SetFirstParametr(firstParam);
}