#include "procedure.h"

using namespace std;


bool checkNum(int& code, string s, int& num)
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
		if (num <= 0)
		{
			code = 2;
			return false;
		}
		else
			return true;
	}
}

void inputSize(int& size, string message)
{
	bool ok = false;
	int num = 0;
	int code;
	string s;
	do
	{
		cout << message;
		getline(cin, s);
		if (!(ok = checkNum(code, s, num)))
		{
			cout << endl;
			switch (code)
			{
			case 0: cout << "Введена пустая строка" << endl;
				system("pause");
				break;
			case 1: cout << "Введен некорректный символ" << endl;
				system("pause");
				break;
			case 2: cout << "Введено некорректное число" << endl;
				system("pause");
				break;
			}
			system("cls");
		}
	} while (!ok);
	size = num;
}

bool checkNumOfChoiсe(int& num, string s, int& code, int rage)
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
		if ((num > rage) || (num <= 0))
		{
			code = 2;
			return false;
		}
		else
			return true;
	}
}

bool inputStack(stack& steck, string message)
{
	cout << message;
	string s;
	getline(cin, s);
	if (!steck.push(s))
		cout << endl << "Превышено количество";
	system("cls");
	bool ok = false;
	int num = 0;
	int code;
	do
	{
		cout << "1.Добавить элемент" << endl << "2.Продолжить" << endl << "3.Выйти" << endl << "Введите: ";
		getline(cin, s);
		if (!(ok = checkNumOfChoiсe(num, s, code, 3)))
		{
			cout << endl;
			switch (code)
			{
			case 0: cout << "Введена пустая строка" << endl;
				system("pause");
				break;
			case 1: cout << "Введен некорректный символ" << endl;
				system("pause");
				break;
			case 2: cout << "Введено некорректное число" << endl;
				system("pause");
				break;
			}
		}
	} while (!ok);
	system("cls");
	if (num == 3)
		exit;
	return num == 2;
}

void sizeOfStack(stack& steckOne, stack& steckTwo, int& count1, int& count2)
{
	while (!steckOne.empty())
	{
		steckTwo.push(steckOne.top());
		steckOne.pop();
		count1++;
	}while (!steckTwo.empty())
	{
		steckOne.push(steckTwo.top());
		steckTwo.pop();
		count2++;
	}
	count2 -= count1;
	for (int i = 0; i < count2; i++)
	{
		steckTwo.push(steckOne.top());
		steckOne.pop();
	}
}