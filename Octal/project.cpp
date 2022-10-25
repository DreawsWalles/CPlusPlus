#include <iostream>
#include "Octal.h"
#include <vector>
#include <windows.h>

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
			cout << "Введенное значение некорректно. Значение должно быть в диапазоне от " << borderBeg <<" до " << borderEnd << endl;
			return -1;
		}
		return num;
	}
}

Octal* incMass(Octal*& arr1, int &size)
{
	Octal* arr2 = new Octal[20 + size];
	for (int i = 0; i < size; i++)
		arr2[i] = arr1[i];
	delete[] arr1;
	size += 20;
	return arr2;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	int count = 0;
	int border;
	int size = 20;
	Octal* vec = new Octal[size];
menu:
	cout << "Выберите действие: " << endl;
	switch (count)
	{
	case 1:
		cout << "1. Ввести число" << endl;
		cout << "2. Вывести число на экран" << endl;
		cout << "3. Удалить число" << endl;
		cout << "0. Выйти" << endl;
		border = 3;
		break;
	default:
		cout << "1. Ввести число" << endl;
		cout << "2. Вывести числа на экран" << endl;
		cout << "3. Удалить число" << endl;
		cout << "4. Арифметические операции" << endl;
		cout << "5. Логические операции" << endl;
		cout << "0. Выйти" << endl;
		border = 5;
		break;
	case 0:
		cout << "1. Ввести число" << endl;
		cout << "0. Выйти" << endl;
		border = 1;
		break;
	}
	string choise;
	int num;
	cout << "-> ";
	getline(cin, choise);
	if ((num = CheckChoise(choise, 0, border)) == -1)
	{
		system("pause");
		system("cls");
		goto menu;
	}
	system("cls");
	switch (num)
	{
	case 0:
		exit;
		break;
	case 1:
	{
input:
		bool ok;
		if (count >= size)
			vec = incMass(vec, size);
		do
		{
			cout << "Введите число: ";
			if (!(ok = vec[count].Read()))
			{
				cout << endl << "Выберите действие:" << endl;
				cout << "1. Ввести заново" << endl;
				cout << "0. Вернуться в меню" << endl;
				cout << "-> ";
				getline(cin, choise);
				if ((num = CheckChoise(choise, 0, 1)) == -1)
				{
					system("pause");
					system("cls");
				}
				else
				{
					if (num == 0)
					{
						system("cls");
						goto menu;
					}
				}
			}
			else
			{
				count++;
				system("cls");
				goto menu;
			}
			system("cls");
		} while (!ok);
	}
	case 2:
print:
	{
		for (int i = 0; i < count; i++)
		{
			cout << i + 1 << ". ";
			vec[i].Display();
			cout << endl;
		}
		switch (num)
		{
		case 2:
			cout << endl;
			system("pause");
			system("cls");
			goto menu;
			break;
		case 3:
			goto del;
			break;
		}
		break;
	}
	case 3:
	{
		goto print;
		int k;
	del:
		cout << endl << "Введите число для удаления" << endl << "-> ";
		getline(cin, choise);
		if ((k = CheckChoise(choise, 1, count)) == -1)
		{
			cout << endl;
			system("pause");
			system("cls");
			goto print;
		}
		for (int i = k - 1; i < count - 1; i++)
			vec[i] = vec[i + 1];
		count--;
		system("cls");
		goto menu;
		break;
	}
	case 4:
	{
		bool ok;
		int n; //номер числа для записи результата(-1 если просто выводим на экран)
		Octal tern1;//первое число
		Octal tern2;//второе число
		do
		{
			cout << "Куда записать результат?" << endl;
			cout << "1. Записать результат операции в новое число" << endl;
			cout << "2. Записать результат операции в уже существующее число" << endl;
			cout << "3. Вывести на экран" << endl;
			cout << "0. Вернуться в меню" << endl;
			cout << "-> ";
			getline(cin, choise);
			if ((n = CheckChoise(choise, 0, 3)) == -1)
			{
				do
				{
					system("pause");
					system("cls");
					cout << "1. Ввести заново" << endl;
					cout << "0. Вернуться в меню" << endl;
					cout << "-> ";
					getline(cin, choise);
					if ((n = CheckChoise(choise,0, 1)) == -1)
						ok = false;
					else
						ok = true;
				} while (!ok);
				if (n == 0)
				{
					system("cls");
					goto menu;
				}
				ok = false;
				system("cls");
			}
			else
				ok = true;
		} while (!ok);
		switch (n)//выбор для записи результата
			{
			case 0:
				goto menu;
				break;
			case 1:
			{
				n = count;
				if (count >= size)
					vec = incMass(vec, size);
				break;
			}
			case 2:
			print_arifm:
			{
				system("cls");
				for (int i = 0; i < count; i++)
				{
					cout << i + 1 << ". ";
					vec[i].Display();
					cout << endl;
				}
				cout << endl << "Выберите число куда записывать результат" << endl;
				cout << "-> ";
				getline(cin, choise);
				if ((n = CheckChoise(choise, 1, count)) == -1)
				{
					cout << endl;
					system("pause");
					system("cls");
					goto print_arifm;
				}
				n -= 1;
				break;
			}
			case 3:
				n = -1;
				break;
		}
		do
		{
			system("cls");
			cout << "Первое число для операции:" << endl;
			cout << "1. Ввести с клавиатуры" << endl;
			cout << "2. Выбрать из раннее введенных" << endl;
			cout << "0. Вернуться в меню" << endl;
			cout << "-> ";
			getline(cin, choise);
			if ((num = CheckChoise(choise, 0, 2)) == -1)
			{
				system("pause");
				system("cls");
				ok = false;
			}
			else
				ok = true;
		} while (!ok);
		switch (num)
		{
		case 0:
			goto menu;
			break;
		case 1:
			do
			{
				system("cls");
				cout << "Введите число: ";
				if (!(ok = tern1.Read()))
				{
					cout << endl << "Выберите действие:" << endl;
					cout << "1. Ввести заново" << endl;
					cout << "0. Вернуться в меню" << endl;
					cout << "-> ";
					getline(cin, choise);
					if ((num = CheckChoise(choise, 0, 1)) == -1)
					{
						system("pause");
						system("cls");
					}
					else
					{
						if (num == 0)
						{
							system("cls");
							goto menu;
						}
					}
				}
			} while (!ok);
			break;
		case 2:
			do
			{
				system("cls");
				for (int i = 0; i < count; i++)
				{
					cout << i + 1 << ". ";
					vec[i].Display();
					cout << endl;
				}
				cout << endl << "Выберите число: ";
				getline(cin, choise);
				if ((num = CheckChoise(choise,1, count)) == -1)
				{
					ok = false;
					system("pause");
					system("cls");
				}
				else
					ok = true;
			} while (!ok);
			tern1 = vec[num - 1];
			break;
		}
		do
		{
			system("cls");
			cout << "Второе число для операции:" << endl;
			cout << "1. Ввести с клавиатуры" << endl;
			cout << "2. Выбрать из раннее введенных" << endl;
			cout << "0. Вернуться в меню" << endl;
			cout << "-> ";
			getline(cin, choise);
			if ((num = CheckChoise(choise, 0, 2)) == -1)
			{
				system("pause");
				system("cls");
				ok = false;
			}
			else
				ok = true;
		} while (!ok);
		switch (num)
		{
		case 0:
			goto menu;
			break;
		case 1:
			do
			{
				system("cls");
				cout << "Введите число: ";
				if (!(ok = tern2.Read()))
				{
					cout << endl << "Выберите действие:" << endl;
					cout << "1. Ввести заново" << endl;
					cout << "0. Вернуться в меню" << endl;
					cout << "-> ";
					getline(cin, choise);
					if ((num = CheckChoise(choise, 0, 1)) == -1)
					{
						system("pause");
						system("cls");
					}
					else
					{
						if (num == 0)
						{
							system("cls");
							goto menu;
						}
					}
				}
			} while (!ok);
			break;
		case 2:
			do
			{
				system("cls");
				for (int i = 0; i < count; i++)
				{
					cout << i + 1 << ". ";
					vec[i].Display();
					cout << endl;
				}
				cout << endl << "Выберите число: ";
				getline(cin, choise);
				if ((num = CheckChoise(choise, 1, count)) == -1)
				{
					ok = false;
					system("pause");
					system("cls");
				}
				else
					ok = true;
			} while (!ok);
			tern2 = vec[num - 1];
			break;
		}
		do
		{
			system("cls");
			cout << "1. Сложение двух чисел" << endl; 
			cout << "2. Вычетание двух чисел" << endl;
			cout << "3. Умножение двух чисел" << endl;
			cout << "0. Вернуться в меню" << endl;
			cout << "-> ";
			getline(cin, choise);
			if ((num = CheckChoise(choise, 0, 3)) == -1)
			{
				system("pause");
				system("cls");
				ok = false;
			}
			else
				ok = true;
		} while (!ok);
		switch (num)
		{
		case 0:
			goto menu;
			break;
		case 1:
			if (n == -1)
			{
				Octal res;
				res = tern1 + tern2;
				cout << "Результат сложения числел ";
				tern1.Display();
				cout << " и ";
				tern2.Display();
				cout << ": ";
				res.Display();
				cout << endl;
			}
			else
			{
				vec[n] = tern1 + tern2;
				count++;
				cout << "Результат сложения числел ";
				tern1.Display();
				cout << " и ";
				tern2.Display();
				cout << ": ";
				vec[n].Display();
			}
			system("cls");
			goto menu;
			break;
		case 2:
			if (n == -1)
			{
				Octal res;
				if (tern1 >= tern2)
				{
					res = tern1 - tern2;
					cout << "Результат вычитания числел ";
					tern1.Display();
					cout << " и ";
					tern2.Display();
					cout << ": ";
					res.Display();
					cout << endl;
				}
				else
				{
					res = tern2 - tern1;
					cout << "Результат вычитания числел ";
					tern2.Display();
					cout << " и ";
					tern1.Display();
					cout << ": ";
					res.Display();
					cout << endl;
				}
			}
			else
			{
				if (tern1 >= tern2)
				{
					vec[n] = tern1 - tern2;
					count++;
					cout << "Результат вычитания числел ";
					tern1.Display();
					cout << " и ";
					tern2.Display();
					cout << ": ";
					vec[n].Display();
				}
				else
				{
					vec[n] = tern2 - tern1;
					count++;
					cout << "Результат вычитания числел ";
					tern2.Display();
					cout << " и ";
					tern1.Display();
					cout << ": -";
					vec[n].Display();
				}
			}
			system("pause");
			system("cls");
			goto menu;
			break;
		case 3:
			if (n == -1)
			{
				Octal res;
				res = tern1 * tern2;
				cout << "Результат умножения числел ";
				tern1.Display();
				cout << " и ";
				tern2.Display();
				cout << ": ";
				res.Display();
				cout << endl;
			}
			else
			{
				vec[n] = tern1 * tern2;
				count++;
				cout << "Результат умножения числел ";
				tern1.Display();
				cout << " и ";
				tern2.Display();
				cout << ": ";
				vec[n].Display();
			}
			system("cls");
			goto menu;
			break;
		}
		break;
	}
	case 5:
		bool ok;
		Octal tern1;
		Octal tern2;
		do
		{
			system("cls");
			cout << "Первое число для операции:" << endl;
			cout << "1. Ввести с клавиатуры" << endl;
			cout << "2. Выбрать из раннее введенных" << endl;
			cout << "0. Вернуться в меню" << endl;
			cout << "-> ";
			getline(cin, choise);
			if ((num = CheckChoise(choise, 0, 2)) == -1)
			{
				system("pause");
				system("cls");
				ok = false;
			}
			else
				ok = true;
		} while (!ok);
		switch (num)
		{
		case 0:
			goto menu;
			break;
		case 1:
			do
			{
				system("cls");
				cout << "Введите число: ";
				if (!(ok = tern1.Read()))
				{
					cout << endl << "Выберите действие:" << endl;
					cout << "1. Ввести заново" << endl;
					cout << "0. Вернуться в меню" << endl;
					cout << "-> ";
					getline(cin, choise);
					if ((num = CheckChoise(choise, 0, 1)) == -1)
					{
						system("pause");
						system("cls");
					}
					else
					{
						if (num == 0)
						{
							system("cls");
							goto menu;
						}
					}
				}
			} while (!ok);
			break;
		case 2:
			do
			{
				system("cls");
				for (int i = 0; i < count; i++)
				{
					cout << i + 1 << ". ";
					vec[i].Display();
					cout << endl;
				}
				cout << endl << "Выберите число: ";
				getline(cin, choise);
				if ((num = CheckChoise(choise, 1, count)) == -1)
				{
					ok = false;
					system("pause");
					system("cls");
				}
				else
					ok = true;
			} while (!ok);
			tern1 = vec[num - 1];
			break;
		}
		do
		{
			system("cls");
			cout << "Второе число для операции:" << endl;
			cout << "1. Ввести с клавиатуры" << endl;
			cout << "2. Выбрать из раннее введенных" << endl;
			cout << "0. Вернуться в меню" << endl;
			cout << "-> ";
			getline(cin, choise);
			if ((num = CheckChoise(choise, 0, 2)) == -1)
			{
				system("pause");
				system("cls");
				ok = false;
			}
			else
				ok = true;
		} while (!ok);
		switch (num)
		{
		case 0:
			goto menu;
			break;
		case 1:
			do
			{
				system("cls");
				cout << "Введите число: ";
				if (!(ok = tern2.Read()))
				{
					cout << endl << "Выберите действие:" << endl;
					cout << "1. Ввести заново" << endl;
					cout << "0. Вернуться в меню" << endl;
					cout << "-> ";
					getline(cin, choise);
					if ((num = CheckChoise(choise, 0, 1)) == -1)
					{
						system("pause");
						system("cls");
					}
					else
					{
						if (num == 0)
						{
							system("cls");
							goto menu;
						}
					}
				}
			} while (!ok);
			break;
		case 2:
			do
			{
				system("cls");
				for (int i = 0; i < count; i++)
				{
					cout << i + 1 << ". ";
					vec[i].Display();
					cout << endl;
				}
				cout << endl << "Выберите число: ";
				getline(cin, choise);
				if ((num = CheckChoise(choise, 1, count)) == -1)
				{
					ok = false;
					system("pause");
					system("cls");
				}
				else
					ok = true;
			} while (!ok);
			tern2 = vec[num - 1];
			break;
		}
		do
		{
			system("cls");
			cout << "Доступные операции:" << endl;
			cout << "1. >" << endl;
			cout << "2. <" << endl;
			cout << "3. ==" << endl;
			cout << "4. !=" << endl;
			cout << "5. >=" << endl;
			cout << "6. <=" << endl;
			cout << "0. Вернуться в меню" << endl;
			cout << "-> ";
			getline(cin, choise);
			if ((num = CheckChoise(choise, 0, 6)) == -1)
			{
				system("pause");
				system("cls");
				ok = false;
			}
			else
				ok = true;
		} while (!ok);
		cout << "Функция сравнения вернула результат: ";
		switch (num)
		{
		case 0:
			goto menu;
			break;
		case 1:
			ok = tern1 > tern2;
			break;
		case 2:
			ok = tern1 < tern2;
			break;
		case 3:
			ok = tern1 == tern2;
			break;
		case 4:
			ok = tern1 != tern2;
			break;
		case 5:
			ok = tern1 >= tern2;
			break;
		case 6:
			ok = tern1 <= tern2;
			break;
		}
		if (ok)
			cout << "true" << endl;
		else
			cout << "false" << endl;
		system("pause");
		system("cls");
		goto menu;
		break;
	}
}

