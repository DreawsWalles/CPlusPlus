#include "help.h"

int CompareToCourse(const Record a, int b)
{
	if (a._course == b)
		return 0;
	if (a._course < b)
		return -1;
	return 1;
}

int CompareToGroup(const Record a, int b)
{
	if (a._group == b)
		return 0;
	if (a._course < b)
		return -1;
	return 1;
}

int CompareToFio(const Record a, string b)
{
	if (a._fio == b)
		return 0;
	if (a._fio < b)
		return -1;
	return 1;
}

int CompareToNumber(const Record a, int b)
{
	if (a._number == b)
		return 0;
	if (a._number < b)
		return -1;
	return 1;
}

int CompareToDiscipline(const Record a, string b)
{
	if (a._discipline == b)
		return 0;
	if (a._discipline < b)
		return -1;
	return 1;
}

int CompareToMark(const Record a, int b)
{
	if (a._mark == b)
		return 0;
	if (a._mark < b)
		return -1;
	return 1;
}

int CompareToCourse(const Record a, const Record b)
{
	if (a._course == b._course)
		return 0;
	if (a._course < b._course)
		return -1;
	return 1;
}

int CompareToGroup(const Record a, const Record b)
{
	if (a._group == b._group)
		return 0;
	if (a._course < b._group)
		return -1;
	return 1;
}

int CompareToFio(const Record a, const Record b)
{
	if (a._fio == b._fio)
		return 0;
	if (a._fio < b._fio)
		return -1;
	return 1;
}

int CompareToNumber(const Record a, const Record b)
{
	if (a._number == b._number)
		return 0;
	if (a._number < b._number)
		return -1;
	return 1;
}

int CompareToDiscipline(const Record a, const Record b)
{
	if (a._discipline == b._discipline)
		return 0;
	if (a._discipline < b._discipline)
		return -1;
	return 1;
}

int CompareToMark(const Record a, const Record b)
{
	if (a._mark == b._mark)
		return 0;
	if (a._mark < b._mark)
		return -1;
	return 1;
}
