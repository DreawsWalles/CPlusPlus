#pragma once
#include "Menu.h"
//����������� ����� ������
//������ � ���� ������ ���� ��������� � ��� �� ������ ��� ��������� � ��������� ���� �����, �� ������ ��� ����������� ����� ������
//������ ����� ���������� ������
//������ ����� ������ ������
//������ ����� �������� ������� � ���������
//������ ����� �������������� ������ � ������ ���� Menu
class Figure
{
protected:
	int _width;
	int _height;
	int _length;
	int GetFirstParametr()
	{
		return _width;
	}
	int GetSecondParametr()
	{
		return _height;
	}
	int GetThreadParametr()
	{
		return _length;
	}
	void SetFirstParametr(int value) 
	{
		_width = value;
	}
	void SetSecondParametr(int value)
	{
		_height = value;
	}
	void SetThreadParametr(int value)
	{
		_length = value;
	}
public:
	virtual void Update(int firstParam, int secondParam = 0, int threadParam = 0) = 0;
	virtual Menu* ToMenu() = 0;
	virtual void Print() = 0;
	virtual double Square() = 0;
	virtual int Perimetr() = 0;
};

