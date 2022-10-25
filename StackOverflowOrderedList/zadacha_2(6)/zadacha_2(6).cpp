// zadacha_2(6).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Overflow.h"
#include "OrderedList.h"
#include "Stack.h"
#include <algorithm> 
#include <cctype>
#include <locale>
#include <functional> 
#include <windows.h>

using namespace std;

bool inputNumOfChoiсe(int& num, int& code, string s, int leftVal, int rightVal)
{
	if (s.empty())
	{
		code = 0;
		return false;
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
					if (s[i] == '-')
						code = 2;
					else
						code = 1;
					return false;
				}
			}
	}
	if ((num > rightVal) || (num < leftVal))
	{
		code = 2;
		return false;
	}
	return true;
}

int choiseStruct()
{
    bool ok = false;
	int num;
	string s;
	int code;
    do
    {
        cout << "Выберите структуру, с которой хотите работать" << endl;
        cout << "1.Стэк" << endl;
        cout << "2.Очередь" << endl;
        cout << "3.Упорядоченный список" << endl;
        cout << "Введите: ";
		getline(cin, s);
		if (!(ok = inputNumOfChoiсe(num, code, s, 1, 3)))
		{
			switch (code)
			{
			case 0:
				cout << endl << "Введена пустая строка" << endl;
				break;
			case 2:
				cout << endl << "Введено некорректное число " << endl;
				break;
			case 1:
				cout << endl << "Введен некорректный символ" << endl;
				break;
			}
			system("pause");
			system("cls");
		}
    } while (!ok);
	return num;
}

bool check_el(string s, string &num)
{
	int i;
	bool ok = true;
	int size = s.size();
	if (s[0] == '-')
	{
		num += '-';
		i = 1;
	}
	else
		i = 0;
	while (i < size)
		if ((s[i] >= '0') && (s[i] <= '9'))
			i++;
		else
		{
			cout << endl << "Введен некорректный символ: " << s[i] << endl;
			return false;
		}
	if (ok)
	{
		num += s;
		num += ' ';
	}
	return true;
}

string input_str()
{
	string s;
	bool ok;
	string num="";
	do
	{
		ok = true;
		cout << "Введите строку элементов: ";
		cin >> s;
		if (!s.empty())
			ok = check_el(s, num);
			while ((cin.peek() != '\n') && ok)
			{
				cin >> s;
				if (!(ok = check_el(s, num)))
					while (getchar() != '\n');
			}
		if ((num == "") && ok)
		{
			ok = false;
			cout << endl << "Введена пустая строка" << endl;
		}
		system("pause");
		system("cls");
	} while (!ok);
	return num;
}

int menu_doing()
{
	bool ok = false;
	int num;
	string s;
	int code;
	do
	{
		cout << "Выберите действие:" << endl;
		cout << "1.Добавить элемент" << endl;
		cout << "2.Удалить элемент" << endl;
		cout << "3.Очистить структуру данных" << endl;
		cout << "4.Заполнение структуры данных из строки" << endl;
		cout << "5.Преобразование данных в строку текста" << endl;
		cout << "6.Выйти" << endl;
		cout << "Введите: ";
		getline(cin, s);
		if (!(ok = inputNumOfChoiсe(num, code, s, 1, 6)))
		{
			switch (code)
			{
			case 0:
				cout << endl << "Введена пустая строка" << endl;
				break;
			case 2:
				cout << endl << "Введено некорректное число " << endl;
				break;
			case 1:
				cout << endl << "Введен некорректный символ" << endl;
				break;
			}
			system("pause");
			system("cls");
		}
	} while (!ok);
	return num;
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	string s;
	string numS;
	int num;
	bool ok = true;
	switch (choiseStruct())
	{
		system("cls");
	case 1:
	{
		Stack st;
		do
		{
			system("cls");
			switch (menu_doing())
			{
			case 1:
				do
				{
					system("cls");
					cout << "Введите элемент: ";
					cin >> s;
					if (!s.empty())
					{
						if (ok = check_el(s, numS))
						{
							num = stoi(numS);
							st.push(num);
						}
						else
							while (getchar() != '\n');
					}
					else
					{
						cout << endl << "Введена пустая строка" << endl;;
						ok = false;
					}
					system("pause");
				} while (!ok);
				break;
			case 2:
				st.pop();
				break;
			case 3:
				st.clear();
				break;
			case 4:
				system("cls");
				st.add(input_str());
				break;
			case 5:
				system("cls");
				s = st.ToString();
				cout << s << endl;
				system("pause");
				break;
			case 6:
				ok = false;;
			}
		} while (ok);
	}
		break;
	case 2:
	{
		Overflow fl;
		do
		{
			system("cls");
			switch (menu_doing())
			{
			case 1:
				do
				{
					system("cls");
					cout << "Введите элемент: ";
					cin >> s;
					if (!s.empty())
					{
						if (ok = check_el(s, numS))
						{
							num = stoi(numS);
							fl.push(num);
						}
						else
							while (getchar() != '\n');
					}
					else
					{
						cout << endl << "Введена пустая строка" << endl;;
						ok = false;
					}
					system("pause");
				} while (!ok);
				break;
			case 2:
				fl.pop();
				break;
			case 3:
				fl.clear();
				break;
			case 4:
				system("cls");
				fl.add(input_str());
				break;
			case 5:
				system("cls");
				s = fl.ToString();
				cout << s << endl;
				system("pause");
				break;
				break;
			case 6:
				ok = false;
			}
		} while (ok);
	}
		break;
	case 3:
	{
		OrderedList l;
		do
		{
			system("cls");
			switch (menu_doing())
			{
			case 1:
				do
				{
					system("cls");
					cout << "Введите элемент: ";
					cin >> s;
					if (!s.empty())
					{
						if (ok = check_el(s, numS))
						{
							num = stoi(numS);
							l.push(num);
						}
						else
							while (getchar() != '\n');
					}
					else
					{
						cout << endl << "Введена пустая строка" << endl;;
						ok = false;
					}
					system("pause");
				} while (!ok);
				break;
			case 2:
				do
				{
					system("cls");
					cout << "Введите элемент: ";
					cin >> s;
					if (!s.empty())
					{
						if (ok = check_el(s, numS))
						{
							num = stoi(numS);
							l.pop(num);
						}
						else
							while (getchar() != '\n');
					}
					else
					{
						cout << endl << "Введена пустая строка" << endl;;
						ok = false;
					}
					system("pause");
				} while (!ok);
				break;
			case 3:
				l.clear();
				break;
			case 4:
				system("cls");
				l.add(input_str());
				break;
			case 5:
				system("cls");
				s = l.ToString();
				cout << s << endl;
				system("pause");
				break;
				break;
			case 6:
				ok = false;
			}
		} while (ok);
	}
		break;
	}
}


