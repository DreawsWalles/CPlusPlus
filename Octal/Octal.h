#pragma once

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Octal
{
private:
	int _size;
	unsigned char _number[100];
public:
	int getSize();
	void setSize(int i);
	void incSize();
	unsigned char getNum(int pos);
	void SetNum(int pos, unsigned char c);
	Octal();
	~Octal();
	Octal(string s);//�����������, ��� s- �����
	Octal operator+(Octal other);
	Octal operator-(Octal other);
	Octal operator*(Octal other);
	bool operator<(Octal other);
	bool operator>(Octal other);
	bool operator== (Octal other);
	bool operator>=(Octal other);
	bool operator<=(Octal other);
	bool operator!=(Octal other);
	bool Read();//���������� ������� ���������
	string ToString(); //�������������� � string
	void Display();
};

