#include "Triad.h"

Triad::Triad()
{
	_firstField = 0;
	_secondField = 0;
	_threadField = 0;
}
Triad::Triad(int first, int second, int thread)
{
	_firstField = first;
	_secondField = second;
	_threadField = thread;
}
int Triad::GetFirstField()
{
	return _firstField;
}
int Triad::GetSecondField()
{
	return _secondField;
}
int Triad::GetThreadField()
{
	return _threadField;
}
void Triad::IncFirstField()
{
	_firstField++;
}
void Triad::IncSecondField()
{
	_secondField++;
}
void Triad::IncThreadField()
{
	_threadField++;
}
void Triad::Print()
{
	cout << "Первое число: " << _firstField << endl;
	cout << "Второе число: " << _secondField << endl;
	cout << "Третье число: " << _threadField << endl;
}