#pragma once
#include <iostream>
#include "Triad.h"

using namespace std;

class DataTime :
    public Triad
{
public:
	DataTime();
	DataTime(int day, int month, int year);
	void IncData(int countDays);
	int GetFirstField();
	int GetSecondField();
	int GetThreadField();
	void IncFirstField();
	void IncSecondField();
	void IncThreadField();
	void Print();
};

