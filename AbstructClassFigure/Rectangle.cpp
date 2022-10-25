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
		throw "������ �� ������";
	return _height * _width;
}
int MyRectangle::Perimetr()
{
	if (_height == -1 && _width == -1)
		throw "������ �� ������";
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
	cout << "������: " << GetFirstParametr() << endl;
	cout << "������: " << GetSecondParametr() << endl;
}

Menu* MyRectangle::ToMenu()
{
	Menu* result = new Menu("�������� ���� ��� ���������:");
	result->Add("������: " + GetFirstParametr());
	result->Add("������: " + GetSecondParametr());
	return result;
}
void MyRectangle::Update(int firstParam, int secondParam, int threadParam)
{
	if (firstParam != 0)
		SetFirstParametr(firstParam);
	if (secondParam != 0)
		SetSecondParametr(secondParam);
}