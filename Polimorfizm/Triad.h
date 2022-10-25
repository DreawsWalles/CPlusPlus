#pragma once
#include <iostream>

using namespace std;

class Triad
{
protected:
	int _firstField;
	int _secondField;
	int _threadField;
public:
    Triad();
    Triad(int first, int second, int thread);
	int GetFirstField();
	int GetSecondField();
	int GetThreadField();
	void IncFirstField();
	void IncSecondField();
	void IncThreadField();
	void Print();
};

