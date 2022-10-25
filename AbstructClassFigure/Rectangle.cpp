#include "Rectangle.h"
#include <iostream>
using namespace std;

MyRectangle::MyRectangle()
{
	_height = -1;
	_width = -1;
}
MyRectangle::MyRectangle(int height, int width)
{
	_height = height;
	_width = width;
}
double MyRectangle::Square()
{
	if (_height == -1 && _width == -1)
		throw "Фигура не задана";
	return _height * _width;
}
int MyRectangle::Perimetr()
{
	if (_height == -1 && _width == -1)
		throw "Фигура не задана";
	return 2 * (_height + _width);
}
int MyRectangle::GetWidth()
{
	return GetFirstParametr();
}
int MyRectangle::GetHeight()
{
	return GetSecondParametr();
}
void MyRectangle::SetHeight(int height)
{
	SetSecondParametr(height);
}
void MyRectangle::SetWidth(int width)
{
	SetFirstParametr(width);
}
void MyRectangle::Print()
{
	cout << "Ширина: " << GetFirstParametr() << endl;
	cout << "Высота: " << GetSecondParametr() << endl;
}

Menu* MyRectangle::ToMenu()
{
	Menu* result = new Menu("Выберите поле для изменения:");
	result->Add("Ширина: " + GetFirstParametr());
	result->Add("Высота: " + GetSecondParametr());
	return result;
}
void MyRectangle::Update(int firstParam, int secondParam, int threadParam)
{
	if (firstParam != 0)
		SetFirstParametr(firstParam);
	if (secondParam != 0)
		SetSecondParametr(secondParam);
}