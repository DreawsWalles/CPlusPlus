#include "DataTime.h"
DataTime::DataTime()
{
	_firstField = 1;
	_secondField = 1;
	_threadField = 2021;
}
DataTime::DataTime(int day, int month, int year)
{
	_firstField = day;
	_secondField = month;
	_threadField = year;
}
int DataTime::GetFirstField()
{
	return _firstField;
}
int DataTime::GetSecondField()
{
	return _secondField;
}
int DataTime::GetThreadField()
{
	return _threadField;
}
void DataTime::IncFirstField()
{
	if (++_firstField > 31) {
		_firstField = 1;
		_secondField++;
	}

	if (_secondField > 12) {
		_secondField = 1;
		_threadField++;
	}
}
void DataTime::IncSecondField()
{
	if (++_secondField > 12) {
		_secondField = 1;
		_threadField++;
	}
}
void DataTime::IncThreadField()
{
	_threadField++;
}
void DataTime::Print()
{
	cout << "Дата: " << _firstField << "." << _secondField << "." << _threadField;
}
void DataTime::IncData(int countDays)
{
	for (int i = 0; i < countDays; i++)
		IncFirstField();
}