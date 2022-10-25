#pragma once
#include<string>
#include <fstream>
#include <iostream>

using namespace std;
class hashTable
{
private:
	const static int n = 10000;
	int head[n];
	int next[n];
	bool isFree[n];
	string values[n];

public:
	hashTable()
	{
		for (int i = 0; i < n; i++)
		{
			head[i] = -1;
			next[i] = -1;
			isFree[i] = true;
		}
	}

	~hashTable()
	{
		Clear();
	}

	bool Find(string word, int hash(string))
	{
		int index = head[hash(word)];
		while ((index != -1) && (values[index] != word))
			index = next[index];
		return index != -1;
	}

	bool Push(string word, int hash(string))
	{
		int h = hash(word);// вычисление хеш функции
		int pred = -1; //указатель на предущее, чтобы подвязать при добавлении в цепочку
		int index = head[h];//указатель на начало цепочки
		while ((index != -1) && (values[index] != word)) // пока не дошли до конца цепочки или не встретили такое же слово
		{
			pred = index; 
			index = next[index];
		}
		if (index != -1)// если мы не дошли до ее конца(index != -1), то такой элемент в таблице уже есть и мы НЕ добавляем повторно 
			return false;
		int i = (pred + 1) % n; //индекс с короторого мы начинаем поиск свободного места
		int j = 0;
		while (j < n && !isFree[(i + j) % n]) //находим свободное место, пока что места заняты и прошли не всю таблицу
			j++;
		if (j == n) // если мы дошли до конца таблицы и не нашли свободного места, то вставлять некуда
			return false;
		if (head[h] == -1) //если цепочки до этого не было, то начинаем цепочку
			head[h] = (i + j) % n;
		else //подвязываем к концу цепочки
			next[pred] = (i + j) % n;
		isFree[(i + j) % n] = false; //говорим, что там занято
		values[(i + j) % n] = word;
		return true;
	}

	bool Pop(string word, int hash(string))
	{
		int pred = -1;
		int h = hash(word);
		int index = head[h];
		while ((index != -1) && (values[index] != word))
		{
			pred = index;
			index = next[index];
		}
		if (index == -1)
			return false;
		if (index == head[h])
			head[index] = next[index];
		else
			next[pred] = next[index];
		next[index] = -1;
		isFree[index] = true;
		return true;
	}

	int getLength(int i)
	{
		int length = 0;
		int index = head[i];
		while (index != -1)
		{
			length++;
			index = next[index];
		}
		return length;
	}

	void Clear()
	{
		for (int i = 0; i < n; i++)
		{
			head[i] = -1;
			next[i] = -1;
			isFree[i] = true;
		}
	}

	double Average(int hash(string), string fileName)
	{
		ifstream file(fileName);
		string word;
		int i = 0;
		while (file >> word )
		{
			Push(word, hash);
			i++;
		}
		file.close();
		int cnt = 0;
		int cnt_coll = 0;
		for (int i = 0; i < n; i++)
		{
			int tmp = getLength(i);
			if (tmp != 0)
			{
				cnt_coll += tmp;
				cnt++;
			}
		}
		Clear();
		return cnt_coll / static_cast<double>(cnt);
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

