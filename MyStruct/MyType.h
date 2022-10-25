#pragma once
#include<string>
#include <iostream>

using namespace std;

class MyType
{
private:
	string _name;
	int _price;
public:
	MyType();
	void SetName(const string s);
	void SetPrice(const int n);
	string GetName();
	int GetPrice();
	friend ostream& operator<<(ostream& out, const MyType& ex);
	friend istream& operator>>(istream& in, MyType& ex);
	friend bool operator==(MyType a, MyType b);
	friend bool operator!=(MyType a, MyType b);
	friend bool operator>(MyType a, MyType b);
	friend bool operator<(MyType a, MyType b);
private:
	int checkOnCorrect(string s);
};

