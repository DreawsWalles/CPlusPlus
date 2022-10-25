#include "Journal.h"

Journal::Journal()
{

}

Record Journal::getRecord(int number)
{
	int index = 0;
	Vector::iterator it = _list.begin();
	while (index != number)
	{
		index++;
		it++;
	}
	return *it;
}

Journal::~Journal()
{
	_list.clear();
}
int Journal::size()
{
	return _list.size();
}

void Journal::Add(Record element)
{
	_list.push_back(element);
}

bool Journal::Change(Record element, Record change)
{
	if (element.CompareTo(change) == 0)
		return false;
	Vector::iterator it = _list.begin();
	while ((*it).CompareTo(element) != 0 && it != _list.end())
		it++;
	if (it == _list.end())
		return false;
	*it = change;
	return true;
}

bool Journal::Remove(Record element)
{
	Vector::iterator it = _list.begin();
	while ((*it).CompareTo(element) != 0 && it != _list.end())
		it++;
	if (it == _list.end())
		return false;
	_list.erase(it);
	return true;
}

void Journal::Print()
{
	int i = 1;
	cout << "\tКурс\tГруппа\tФамилия Имя Отчество\tНомер заченой книги\tДисциплина\tОценка\n";
	for (Vector::iterator it = _list.begin(); it != _list.end(); it++)
	{
		cout << i << '.';
		(*it).print(cout);
		cout << endl;
		i++;
	}
}

void Journal::PrintInFile(string fileName)
{
	ofstream file;
	file.open(fileName);
	file << "Курс\tГруппа\tФамилия Имя Отчество\tНомер заченой книги\tДисциплина\tОценка\n";
	for (Vector::iterator it = _list.begin(); it != _list.end(); it++)
	{
		file << *it;
		if (it != _list.end())
			file << '\n';
	}
	file.close();
}


bool Journal::InputFile(string fileName)
{
	ifstream file;
	file.open(fileName);
	Record input;
	Record check;
	string s;
	getline(file, s);
	while (!file.eof())
	{
		file >> input;
		if (input.CompareTo(check) == 0)
			return false;
		else
			Add(input);
	}
	file.close();
	return true;
}



int Journal::CompareTo(Journal other)
{
	return getRecord(0).CompareTo(other.getRecord(0));
}

void Journal::Clear()
{
	_list.clear();
}

Journal& Journal::operator=(Journal other)
{
	Clear();
	int size = other.size();
	for (int i = 0; i < size; i++)
		Add(other.getRecord(i));
	return *this;
}