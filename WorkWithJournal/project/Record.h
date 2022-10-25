#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct Record
{
public:
	int _course;
	int _group;
	string _fio;
	int _number;
	string _discipline;
	int _mark;
	Record(int course, int group, string fio, int number, string discipline, int mark)
	{
		_course = course;
		_group = group;
		_fio = fio;
		_number = number;
		_discipline = discipline;
		_mark = mark;
	}
	Record() 
	{
		_course = 0;
		_group = 0;
		_number = 0;
		_mark = 0;
		_discipline = "";
		_fio = "";
	}

	Record& operator =(const Record other)
	{
		_course = other._course;
		_group = other._group;
		_fio = other._fio;
		_number = other._number;
		_discipline = other._discipline;
		_mark = other._mark;
		return *this;
	}

	int CompareTo(Record other)
	{
		if (_number == other._number)
			return 0;
		if (_number < other._number)
			return -1;
		return 1;
	}
	void print(ostream& os)
	{
		os << '\t'<< _course << '\t';
		os << _group << '\t';
		os << _fio << "\t\t\t\t";
		os << _number << "\t\t";
		os << _discipline << "\t\t";
		os << _mark;
	}
};

istream& operator>>(istream& is, Record& e);

ostream& operator<<(ostream& os, const Record& e);
