#include "hashTable.h"
#include<string>
#include <iostream>
#include <Windows.h>

using namespace std;

const string alphabet = "аоуыэяеёюибвгдйжзклмнпрстфхцчшщьъ";

int hash_1(string word)
{
	int asciisum = 0;
	int tmp;
	for (int i = 0; i < word.length(); i++)
	{
		tmp = word[i];
		asciisum += abs(tmp);
	}
	return asciisum % 10000;
}

int hash_2(string word)
{
	int asciisum = 0;
	int tmp;
	for (int i = 0; i < word.length(); i++)
	{
		tmp = word[i];
		asciisum += (abs(tmp) * 199) % 4049;
	}
	return asciisum % 10000;
}

int hash_3(string word)
{
	int asciisum = 0;
	int tmp;
	for (int i = 0; i < word.length(); i++)
	{
		asciisum *= 199;
		tmp = word[i];
		asciisum += abs(tmp);
		asciisum %= 4049;
	}
	return asciisum % 10000;
}

int CheckChoise(string s, int borderBeg, int borderEnd)
{
	int num;
	if (s.empty())
	{
		cout << "Введена пустая строка. Повторите ввод" << endl;
		return -1;
	}
	else
	{
		num = 0;
		int len = s.size();
		int i = 0;
		int n;
		while (i < len)
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				n = s[i] - '0';
				num = num * 10 + n;
				i++;
			}
			else
			{
				if (s[i] == ' ')
					i++;
				else
				{
					cout << "Введен некорректный символ: " << s[i] << " . Повторите ввод" << endl;
					return -1;
				}
			}
		if ((num < borderBeg) || (num > borderEnd))
		{
			cout << "Введенное значение некорректно. Значение должно быть в диапазоне от " << borderBeg << " до " << borderEnd << endl;
			return -1;
		}
		return num;
	}
}

void CreateFile()
{
	ofstream file("text.txt");
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			string word = "";
			for (int k = 0; k < i; k++)
				word += alphabet[rand() % 33];
			file << word << '\n';
		}
	}
	file.close();
}

bool inputFileName(string& name)
{
	cout << "Введите имя файла: ";
	getline(cin, name);
	int size = name.size();
	int i = 0;
	while (i < size)
	{
		if ((name[i] == '/') || (name[i] == '\\') || (name[i] == ':') || (name[i] == '*') || (name[i] == '?') || (name[i] == '«') || (name[i] == '<') || (name[i] == '>') || (name[i] == '|'))
		{
			cout << endl << "Введен некорректный символ " << name[i] << endl;
			return false;
		}
		else
			i++;
	}
	return true;
}

string OpenFile()
{
	string result;
	while (!inputFileName(result))
	{
		system("pause");
		system("cls");
	}
	return result;
}

string Input()
{
	string result;
	cout << "Введите элемент: ";
	getline(cin, result);
	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	int choice;
	string s;
	string fileName;
	hashTable table;
begin:
	do
	{
		cout << "1. Сгенерировать случайный файл" << endl;
		cout << "2. Подключить существующий файл" << endl;
		cout << "-> ";
		getline(cin,s);
		if ((choice = CheckChoise(s, 1, 2)) == -1)
			system("pause");
		system("cls");
	} while (choice == -1);
	switch (choice)        
	{
	case 1:
		CreateFile();
		fileName = "text.txt";
		break;
	case 2:
		fileName = OpenFile();
		break;
	}
	ifstream file(fileName);
	string word;
	while (file >> word)
		table.Push(word, hash_3);
	file.close();
	system("cls");
main_menu:
	do
	{
		cout << "1. Добавить запись" << endl;
		cout << "2. Удалить элемент" << endl;
		cout << "3. Поиск элемента" << endl;
		cout << "4. Очистить таблицу" << endl;
		cout << "5. Освновная задача" << endl;
		cout << "6. Загрузить данные из файла" << endl;
		cout << "7. Печать таблицы" << endl;
		cout << "8. Сохранить таблицу" << endl;
		cout << "0. Выход" << endl;
		cout << "-> ";
		getline(cin, s);
		if ((choice = CheckChoise(s, 0, 8)) == -1)
			system("pause");
		system("cls");
	} while (choice == -1);
	switch (choice)	
	{
	case 0:
		exit(0);
		break;
	case 1:
		table.Push(Input(), hash_3);
		break;
	case 2:
		table.Pop(Input(), hash_3);
		break;
	case 3:
		if (table.Find(Input(), hash_3))
		{
			system("cls");
			cout << "Данный элемент присутсвует в таблице" << endl;
			system("pause");
		}
		break;
	case 4:
		table.Clear();
		break;
	case 5:
	{
		cout << "Среднее число коллизий для несколькоких хеш-функций" << endl;
		cout << "hash 1 функция: " << table.Average(hash_1, fileName) << endl;
		cout << "hash 2 функция: " << table.Average(hash_2, fileName) << endl;
		cout << "hash 3 функция: " << table.Average(hash_3, fileName) << endl;
		system("pause");
		ifstream file(fileName);
		string word;
		while (file >> word)
			table.Push(word, hash_3);
		file.close();
	}
		break;
	case 6:
		goto begin;
		break;
	case 7:
		table.Print();
		break;
	case 8:
		system("cls");
		fileName = OpenFile();
		table.Save(fileName);
		break;
	}
	system("cls");
	goto main_menu;
}

