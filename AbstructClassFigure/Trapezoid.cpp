#include "Trapezoid.h"
#include <iostream>
using namespace std;

Trapezoid::Trapezoid()
{
	_width = -1;
	_length = -1;
	_height = -1;
}
Trapezoid::Trapezoid(int width, int length, int height) 
{
	_width = width;
	_length = length;
	_height = height;
}
double Trapezoid::Square()
{
	return (_width + _length) * _height / 2;
}
int Trapezoid::Perimetr()
{
	return 2 * (_width + _length);
}
int Trapezoid::GetWidth()
{
	return GetFirstParametr();
}
int Trapezoid::GetHeight()
{
	return GetSecondParametr();
}
void Trapezoid::SetHeight(int height)
{
	SetSecondParametr(height);
}
void Trapezoid::SetWidth(int width)
{
	SetFirstParametr(width);
}
int Trapezoid::GetLength()
{
	return GetThreadParametr();
}
void Trapezoid::SetLength(int length)
{
	SetThreadParametr(length);
}
void Trapezoid::Print()
{
	cout << "Ширина: " << GetFirstParametr() << endl;
	cout << "Длина: " << GetThreadParametr() << endl;
	cout << "Высота: " << GetSecondParametr() << endl;
}
Menu* Trapezoid::ToMenu()
{
	Menu* result = new Menu("Выберите поле для изменения:");
	result->Add("Ширина: " + to_string(GetFirstParametr()));
	result->Add("Длина: " + to_string(GetThreadParametr()));
	result->Add("Высота: " + to_string(GetSecondParametr()));
	return result;
}
void Trapezoid::Update(int firstParam, int secondParam, int threadParam)
{
	if (firstParam != 0)
		SetFirstParametr(firstParam);
	if (secondParam != 0)
		SetThreadParametr(secondParam);
	if (threadParam != 0)
		SetSecondParametr(threadParam);
}