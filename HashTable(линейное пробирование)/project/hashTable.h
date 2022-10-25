#pragma once
#include<string>
#include <fstream>
#include <iostream>

using namespace std;
class hashTable
{
private:
	const static int n = 10000;
	bool isFree[n];
	int size;
	int cnt[n];
	string values[n];

public:
	hashTable()
	{
		Clear();
	}

	~hashTable()
	{
		Clear();
	}

	bool Find(string word, int hash(string))
	{
		int h = hash(word);
		int count = 0;
		while (!isFree[h] && (values[h] != word) && (count != n))
		{
			if ((h + 1) == n)
				h = 0;
			else
				h++;
			count++;
		}
		if (isFree[h])
			return false;
		return true;
 	}

	bool Push(string word, int hash(string))
	{
		if (size == n)
			return false;
		size++;
		int h = hash(word);
		cnt[h]++;
		if (isFree[h])
			values[h] = word;
		else
		{
			while (!isFree[h])
			{
				if ((h + 1) == n)
					h = 0;
				else
					h++;
			}
			values[h] = word;
		}
		isFree[h] = false;
		return true;
	}

	bool Pop(string word, int hash(string))
	{
		int h = hash(word);
		while (!isFree[h] && (values[h] != word))
			if ((h + 1) == n)
				h = 0;
			else
				h++;
		if (isFree[h])
			return false;
		cnt[h]--;
		isFree[h] = true;
		size--;
		return true;
	}



	void Clear()
	{
		for (int i = 0; i < n; i++)
		{
			isFree[i] = true;
			cnt[i] = 0;
		}
		size = 0;
		
	}

	double Average()
	{
		int sum = 0;
		int count = 0;
		for (int i = 0; i< n; i++)
			if (cnt[i] != 0)
			{
				count++;
				sum += cnt[i];
			}
		return sum / static_cast<double> (count);
	}

	void Print()
	{
		cout << "Хеш-таблица: " << endl;
		for (int i = 0; i < n; i++)
			if (!isFree[i])
				cout << values[i] << endl;
		system("pause");
	}
	void Save(string fileName)
	{
		ofstream file(fileName);
		for (int i = 0; i < n; i++)
			if (!isFree[i])
				file << values[i] << '\n';
		file.close();
	}
};

