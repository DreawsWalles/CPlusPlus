#pragma once
#include <string>
#include <vector>
#include "Record.h"
#include <algorithm>


using namespace std;


class Journal
{
private:
	typedef vector<Record> Vector;
	Vector _list;
public:
	Journal();

	Record getRecord(int number);

	~Journal();
	int size();

	void Add(Record element);

	bool Change(Record element, Record change);

	bool Remove(Record element);

	void Print();

	void PrintInFile(string fileName);

	void PrintList(int n);

	void PrintListInFile(ofstream& file);

	bool InputFile(string fileName);

	template <class T>
	Journal Search(int check(Record, T), T checkVar)
	{
		Vector::iterator it;
		Journal result;
		for (it = _list.begin(); it != _list.end(); it++)
			if (check(*it, checkVar) == 0)
				result.Add(*it);
		return result;
	}

	template<class T>
	Journal Search_bin(int Compare(Record, Record), const T check, int CompareTo(Record, T))
	{
		Journal result;
		Vector new_list = _list;
		sort(new_list.begin(), new_list.end(), [&](Record& a, Record& b) {return Compare(a, b) == -1; });
		Vector::iterator it = lower_bound(new_list.begin(), new_list.end(), check, [&](Record a, T b) {return CompareTo(a, b) == -1; });
		while (it != new_list.end() && CompareTo((*it), check) == 0)
		{
			result.Add(*it);
			it++;
		}
		return result;
	}

	template<class T>
	double AverageValue(int Compare(Record, Record), T check, int CompareTo(Record, T))
	{
		int sum = 0;
		Journal list = Search_bin(Compare, check, CompareTo);
		for (Record element : list)
			sum += element._mark;
		return sum / list.size;
	}

	int CompareTo(Journal other);

	void Clear();

	Journal& operator=(Journal other);
};

