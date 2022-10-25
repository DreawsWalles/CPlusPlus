#include "interface.h"



using namespace std;

void SetColor(const int text,const int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void SetCursor(const int x,const int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void printMessage(string s)
{
	int len = s.size();
	for (int j = 0; j < len; j++)
	{
		cout << s[j];
		if (s[j] != ' ')
			Sleep(15 + rand() % 30);
		else
			Sleep(60 + rand() % 90);
	}
}

int start(const int n)
{

	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	int w = rc.right;
	int h = rc.bottom;
	w = w / 8;
	h = h / 8;
	int x1 = floor(w / 3);
	SetCursor(x1, 7);
	SetColor(2, 0);
	cout << "||";
	SetColor(13, 0);
	for (int i = 0; i < x1 - 4; i++)
		cout << "=";
	SetColor(2, 0);
	cout << "||" << endl;
	SetCursor(x1, 8);
	cout << "||";
	SetCursor(2 * x1 - 2, 8);
	cout << "||" << endl;
	SetCursor(x1, 9);
	cout << "||";
	SetCursor(2 * x1 - 2, 9);
	cout << "||";
	SetCursor(x1, 10);
	cout << "||";
	SetCursor(2 * x1 - 2, 10);
	cout << "||";
	SetCursor(x1, 11);
	cout << "||";
	SetCursor(2 * x1 - 2, 11);
	cout << "||" << endl;
	SetCursor(x1, 12);
	cout << "||";

	SetCursor(x1 + (x1 / 3.5), 12);
	SetColor(11, 0);
	for (int i = 0; i < 26; i++)
		cout << "*";
	SetColor(2, 0);
	SetCursor(2 * x1 - 2, 12);
	cout << "||" << endl;
	SetCursor(x1, 13);
	cout << "||";
	SetCursor(2 * x1 - 2, 13);
	cout << "||" << endl;
	SetCursor(x1, 14);
	cout << "||";
	SetCursor(2 * x1 - 2, 14);
	cout << "||" << endl;
	SetCursor(x1, 15);
	cout << "||";
	SetCursor(2 * x1 - 2, 15);
	cout << "||" << endl;
	SetCursor(x1, 16);
	cout << "||";
	SetCursor(x1 + (x1 / 3.5), 16);
	SetColor(11, 0);
	for (int i = 0; i < 26; i++)
		cout << "*";
	SetColor(2, 0);
	SetCursor(2 * x1 - 2, 16);
	cout << "||" << endl;
	SetCursor(x1, 17);
	cout << "||";
	SetCursor(2 * x1 - 2, 17);
	cout << "||" << endl;
	SetCursor(x1, 18);
	cout << "||";
	SetCursor(2 * x1 - 2, 18);
	cout << "||" << endl;
	SetCursor(x1, 19);
	cout << "||";
	SetCursor(2 * x1 - 2, 19);
	cout << "||" << endl;
	SetCursor(x1, 20);
	cout << "||";
	SetColor(13, 0);
	for (int i = 0; i < x1 - 4; i++)
		cout << "=";
	SetCursor(2 * x1 - 2, 20);
	SetColor(2, 0);
	cout << "||" << endl;
	if (n == 1)
	{
		SetCursor(x1 + floor(x1 / 2.5), 11);
		SetColor(14, 0);
		printMessage("TIC TAC TOE");
		SetCursor(x1 + (x1 / 2.9), 13);
		SetColor(12, 0);
		printMessage("1. ");
		SetColor(10, 0);
		printMessage("Одиночная игра");
		SetCursor(x1 + (x1 / 2.9), 14);
		SetColor(12, 0);
		printMessage("2. ");
		SetColor(10, 0);
		printMessage("Совместная игра");
		SetCursor(x1 + (x1 / 2.9), 15);
		SetColor(12, 0);
		printMessage("3. ");
		SetColor(10, 0);
		printMessage("Выход");
		SetCursor(x1 + (x1 / 3.5), 17);
		SetColor(10, 0);
		printMessage("Введите: ");
		SetCursor(x1, 21);
	}
	else
		if (n != 0)
		{
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			cout << "TIC TAC TOE";
			SetCursor(x1 + (x1 / 2.9), 13);
			SetColor(12, 0);
			cout << "1. ";
			SetColor(10, 0);
			cout << "Одиночная игра";
			SetCursor(x1 + (x1 / 2.9), 14);
			SetColor(12, 0);
			cout << "2. ";
			SetColor(10, 0);
			cout << "Совместная игра";
			SetCursor(x1 + (x1 / 2.9), 15);
			SetColor(12, 0);
			cout << "3. ";
			SetColor(10, 0);
			cout << "Выход";
			SetCursor(x1 + (x1 / 3.5), 17);
			SetColor(10, 0);
			cout << "Введите: ";
			SetCursor(x1, 21);
		}
	return x1;
}

bool inputNumOfChoiсe(int& num, string s, int& code)
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
		if ((num > 3) || (num <= 0))
		{
			code = 2;
			return false;
		}
		else
			return true;
	}
}

void printDagger(int& x, int& y)  //
{
	SetCursor(x, y);
	SetColor(9, 0);
	cout << "|======";
	SetCursor(x, y + 1);
	cout << '|';
	SetColor(11, 0);
	cout << "  \\/  ";
	SetCursor(x, y + 2);
	SetColor(9, 0);
	cout << '|';
	SetColor(11, 0);
	cout << "  /\\  ";
	x += 7;
}

void printCell(int& x, int& y)
{
	SetCursor(x, y);
	SetColor(9, 0);
	cout << "|======";
	SetCursor(x, y + 1);
	cout << "|       ";
	SetCursor(x, y + 2);
	cout << "|       ";
	x += 7;
}

void printNull(int& x, int& y)
{
	SetCursor(x, y);
	SetColor(9, 0);
	cout << "|======";
	SetCursor(x, y + 1);
	cout << '|';
	SetColor(10, 0);
	cout << "  /\\  ";
	SetCursor(x, y + 2);
	SetColor(9, 0);
	cout << '|';
	SetColor(10, 0);
	cout << "  \\/  ";
	x += 7;
}

bool checkScreen(const int m, int& code)
{
		HWND hWnd = GetConsoleWindow();
		RECT rc;
		GetClientRect(hWnd, &rc);
		int w = floor(rc.right / 8);
		int h = floor(rc.bottom / 8);
		if (((3 + m * 7) >= w) || ((8 + 7 * m) >= h))
		{
			if ((3 + m * 7) >= w)
				code = 1;
			else
				code = 2;
			return false;
		}
		else
			return true;
}

bool checkEdge(string s, int& code, int& num)
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
		if (num <= 4)
		{
			code = 2;
			return false;
		}
		else
		{
			HANDLE hStdout;
			CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
			COORD MaxSize;
			GetConsoleScreenBufferInfo(&hStdout, &csbiInfo);
			MaxSize = csbiInfo.dwMaximumWindowSize;
			if ((abs(MaxSize.X) >= 61 * (3 + num * 7)) && (abs(MaxSize.Y) >= 40 * (8 + 7 * num)))
				return true;
			code = 3;
			return false;
		}
	}
}

void inputEdge(const int x1, int& m)
{
	string s;
	bool ok;
	int n = 1;
	do
	{
		if (n == 1)
		{
			start(0);
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			cout << "TIC TAC TOE";
			SetCursor(x1 + (x1 / 9), 13);
			SetColor(10, 0);
			printMessage("Ввод размеров поля ");
			SetColor(12, 0);
			printMessage("m");
			SetColor(10, 0);
			printMessage(" x ");
			SetColor(12, 0);
			printMessage("m ");
			SetColor(10, 0);
			printMessage("для игры в крестики нолики");
			cout << endl;
			SetCursor(x1 + (x1 / 3.2), 14);
			printMessage("Введите границу ");
			SetColor(12, 0);
			printMessage("m");
			SetColor(10, 0);
			printMessage(": ");
		}
		else
		{
			start(0);
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			cout << "TIC TAC TOE";
			SetCursor(x1 + (x1 / 9), 13);
			SetColor(10, 0);
			cout << "Ввод размеров поля ";
			SetColor(12, 0);
			cout << "m";
			SetColor(10, 0);
			cout << " x ";
			SetColor(12, 0);
			cout << "m ";
			SetColor(10, 0);
			cout << "для игры в крестики нолики";
			cout << endl;
			SetCursor(x1 + (x1 / 3.2), 14);
			cout << "Введите границу ";
			SetColor(12, 0);
			cout << "m";
			SetColor(10, 0);
			cout << ": ";
		}
		SetColor(15, 0);
		getline(cin, s);
		int code;
		if (!checkEdge(s, code, m))
		{
			n++;
			ok = false;
			SetColor(14, 0);
			cout << endl;
			SetCursor(x1 + (x1 / 3.5), 15);
			switch (code)
			{
			case 0:printMessage("Введена пустая строка");
				break;
			case 1:printMessage("Введен некорректный символ");
				break;
			case 2: printMessage("Введено маленькое чесло");
				break;
			case 3: SetCursor(x1 + (x1 / 13), 15);
				printMessage("Введено недопустимое количество ячеек для вашего экрана");
				break;
			}
		}
		else
		{
			ok = true;

			if (!checkScreen(m, code))
			{
				HWND hWnd = GetConsoleWindow();
				RECT rc;
				GetClientRect(hWnd, &rc);
				int x = rc.right;
				int y = rc.bottom;
				HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
				switch (code)
				{
				case 1:  x = (7 * m + 3) * 9;
					break;
				case 2:  y = (7 * m + 8) * 8;
					break;
				}
				COORD crd = { x, y };
				SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
				SetConsoleWindowInfo(out_handle, true, &src);
				SetConsoleScreenBufferSize(out_handle, crd);
				SetWindowPos(GetConsoleWindow(), NULL, 200, 0, crd.X, crd.Y, NULL);
			}
		}
		Sleep(300);
		system("cls");
	} while (!ok);
}

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
		if ((num <= 0) || (num > 2))
		{
			code = 2;
			return false;
		}
		else
			return true;
	}
}

bool checkNumCell(string s, int& code, int& i, const int m, int& k, const int len)
{
	int n = 0;
	int num = 0;
	while (s[i] == ' ')
		i++;
	while ((s[i] != ' ') && (s[i] != '.') && (s[i] != ',') && (s[i] != '/') && (i < len))
	{
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
	if ((num < 0) || (num > m))
	{
		code = 2;
		return false;
	}
	else
	{
		k = num;
		return true;
	}
}

bool getNumCell(string s, int& code, int& x, int& y, const int m)
{
	int len = s.size();
	int i = 0;
	int num = 0;
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
		if (checkNumCell(s, code, i, m, x, len))
		{
			i++;
			if (checkNumCell(s, code, i, m, y, len))
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

bool inputCoordCell(string** mass,const int m, int& x1, int& y1,const int kol, string message)
{
	system("cls");
	printMatr(mass, m);
	int x = 2;
	int y = (m+1) * 3 + 5;
	SetCursor(x, y - 1);
	SetColor(14, 0);
	printMessage(message);
	SetCursor(x, y);
	SetColor(10, 0);
	if (kol == 0)
	{
		printMessage("Введите номера ячеек в последовательности ");
		SetColor(12, 0);
		printMessage("X, Y");
		SetColor(10, 0);
		cout << ": ";
	}
	else
	{
		cout << "Введите номера ячеек в последовательности ";
		SetColor(12, 0);
		cout << "X, Y";
		SetColor(10, 0);
		cout << ": ";
	}
	SetColor(15, 0);
	string s;
	getline(cin, s);
	int code;
	if (!getNumCell(s, code, x1, y1, m))
	{
		SetColor(14, 0);
		SetCursor(x, y + 1);
		switch (code)
		{
		case 0: printMessage("Введена пустая строка");
			break;
		case 1: printMessage("Введен некореектный символ");
			break;
		case 2: printMessage("Введено некорректное число");
			break;
		}
		return false;
	}
	else
	{
		if (mass[y1][x1] == "0")
			return true;
		else
		{
			SetColor(14, 0);
			SetCursor(x, y + 1);
			printMessage("Данная ячейка уже занята");
			return false;
		}
	}
}

void initMass(string** mass,const int m)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			mass[i][j] = "0";
}

int gameChoice(int x1)
{
	x1 = start(0);
	int code, num;
	bool ok;
	string s;
	int n = 1;
	do
	{
		if (n == 1)
		{
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			cout << "TIC TAC TOE";
			SetCursor(x1 + (x1 / 3), 13);
			SetColor(10, 0);
			printMessage("Выберите среду игры");
			SetCursor(x1 + (x1 / 3.5), 14);
			SetColor(12, 0);
			printMessage("1.");
			SetColor(10, 0);
			printMessage("Использовать консоль");
			SetCursor(x1 + (x1 / 3.5), 15);
			SetColor(12, 0);
			printMessage("2.");
			SetColor(10, 0);
			printMessage("Использовать текстовые файлы");
			SetCursor(x1 + (x1 / 3.5), 17);
			SetColor(10, 0);
			printMessage("Введите: ");
		}
		else
		{
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			cout << "TIC TAC TOE";
			SetCursor(x1 + (x1 / 3), 13);
			SetColor(10, 0);
			cout << "Выберите среду игры";
			SetCursor(x1 + (x1 / 3.5), 14);
			SetColor(12, 0);
			cout << "1.";
			SetColor(10, 0);
			cout << "Использовать консоль";
			SetCursor(x1 + (x1 / 3.5), 15);
			SetColor(12, 0);
			cout << "2.";
			SetColor(10, 0);
			cout << "Использовать текстовые файлы";
			SetCursor(x1 + (x1 / 3.5), 17);
			SetColor(10, 0);
			cout << "Введите: ";
		}
		SetColor(15, 0);
		getline(cin, s);
		if (!checkNum(code, s, num))
		{
			n++;
			ok = false;
			SetColor(14, 0);
			cout << endl;
			SetCursor(x1 + (x1 / 3.5), 18);
			switch (code)
			{
			case 0:printMessage("Введена пустая строка");
				break;
			case 1:printMessage("Введен некорректный символ");
				break;
			case 2: printMessage("Введено некорретное чесло");
				break;
			}
		}
		else
			ok = true;
		system("cls");
	} while (!ok);
	return num;
}

void printMatr(string** mass,const int m)
{
	int x = 2, y = 2;
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= m; j++)
			if (mass[i][j] == "0")
				printCell(x, y);
			else
				if (mass[i][j] == "x")
					printDagger(x, y);
				else
					if (mass[i][j] == "o")
						printNull(x, y);
		y += 3;
		x = 2;
	}
	SetColor(9, 0);
	while (x <= ((m + 1) * 7))
	{
		SetCursor(x, y);
		cout << "|======";
		x += 7;
	}
	y = 2;
	while (y <= ((m + 1) * 3))
	{
		int i = 0;
		while (i < 3)
		{
			SetCursor(x, y);
			cout << '|';
			y++;
			i++;
		}
	}
	SetCursor(x, y);
	cout << '|';
	x = 1;
	y = 3;
	SetCursor(x, y);
	SetColor(15, 0);
	if (m <= 9)
	for (int i = 0; i <= m; i++)
	{
		cout << i;
		y += 3;
		SetCursor(x, y);
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			cout << i;
			y += 3;
			SetCursor(x, y);
		}
		x--;
		SetCursor(x, y);
		for (int i = 10; i <= m; i++)
		{
			cout << i;
			y += 3;
			SetCursor(x, y);
		}
	}
	x = 3;
	y = 1;
	SetCursor(x, y);
	for (int i = 0; i <= m; i++)
	{
		cout << i;
		x += 7;
		SetCursor(x, y);
	}
}

int choiceDaggerNull(int x1)
{
	system("cls");
	int num;
	int n = 0;
	bool ok;
	string s;
	int code;
	do
	{
		if (n == 0)
		{
			x1 = start(0);
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			printMessage("TIC TAC TOE");
			SetCursor(x1 + (x1 / 3.6), 13);
			SetColor(10, 0);
			printMessage("Выберите кем выхотите играть");
			SetCursor(x1 + (x1 / 2.9), 14);
			SetColor(12, 0);
			printMessage("1. ");
			SetColor(10, 0);
			printMessage("Крестик");
			SetCursor(x1 + (x1 / 2.9), 15);
			SetColor(12, 0);
			printMessage("2. ");
			SetColor(10, 0);
			printMessage("Нолик");
			SetCursor(x1 + (x1 / 3.5), 17);
			SetColor(10, 0);
			printMessage("Введите: ");
		}
		else
		{
			start(0);
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			cout << "TIC TAC TOE";
			SetCursor(x1 + (x1 / 3.6), 13);
			SetColor(10, 0);
			cout << "Выберите кем выхотите играть";
			SetCursor(x1 + (x1 / 2.9), 14);
			SetColor(12, 0);
			cout << "1. ";
			SetColor(10, 0);
			cout << "Крестик";
			SetCursor(x1 + (x1 / 2.9), 15);
			SetColor(12, 0);
			cout << "2. ";
			SetColor(10, 0);
			cout << "Нолик";
			SetCursor(x1 + (x1 / 3.5), 17);
			SetColor(10, 0);
			cout << "Введите: ";
		}	SetColor(15, 0);
		getline(cin, s);
		if (!checkNum(code, s, num))
		{
			n++;
			ok = false;
			SetColor(14, 0);
			cout << endl;
			SetCursor(x1 + (x1 / 3.5), 18);
			switch (code)
			{
			case 0:printMessage("Введена пустая строка");
				break;
			case 1:printMessage("Введен некорректный символ");
				break;
			case 2: printMessage("Введено некорретное чесло");
				break;
			}
		}
		else
			ok = true;
		system("cls");
	} while (!ok);

	return num;
}

void print_W(int& x, int& y)
{
	int i = y + 4;
	while (y <= i)
	{
		SetCursor(x, y);
		cout << "\\\\";
		x++;
		y++;
	}
	cout << "//";
	x += 2;
	y -= 2;
	SetCursor(x, y);
	cout << "//";
	cout << "\\\\";
	x += 3;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	cout << "//";
	x += 3;
	y--;
	while (y >= (i - 4))
	{
		SetCursor(x, y);
		cout << "//";
		x++;
		y--;
	}
	y = i - 4;
}

void print_I(int& x, int& y)
{
	int k = y;
	SetCursor(x, y);
	cout << "==";
	y++;
	for (int i = y; y <= (i + 4); y++)
	{
		SetCursor(x, y);
		cout << "||";
	}
	SetCursor(x, y);
	cout << "==";
	y = k;
}

void print_n(int& x, int& y)
{
	int i = y;
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);  //буква n
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	x += 2;
	y = i;
	SetCursor(x, y);
	cout << "_____";
	x += 4;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y = i;
}

void print_e(int& x, int& y)
{
	int i = y;
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "==";
	y = i + 1;
	x += 2;
	SetCursor(x, y);
	y += 2;
	cout << "=======";
	SetCursor(x, y);
	cout << "=======";
	y += 2;
	SetCursor(x, y);
	cout << "=======";
	y = i;
}

void print_r(int& x, int& y)
{
	int i = y;
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	x += 2;
	y = i + 2;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "____";
	y++;
	x += 3;
	SetCursor(x, y);
	cout << "\\\\";
	y = i;
}

void print_c(int& x, int& y)
{
	int i = y;
	y += 2;
	SetCursor(x, y);
	cout << "//";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y = i + 1;
	SetCursor(x, y);
	cout << "//";
	y += 4;
	SetCursor(x, y);
	cout << "\\\\";
	x += 2;
	y = i;
	SetCursor(x, y);
	cout << "____";
	y += 5;
	SetCursor(x, y);
	cout << "____";
	cout << "//";
	x += 4;
	y = i + 1;
	SetCursor(x, y);
	cout << "\\\\";
	y++;
	SetCursor(x, y);
	cout << "||";
	y = i;
}

void print_h(int& x, int& y)
{
	int i = y;
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y -= 2;
	x += 2;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "____";
	y++;
	x += 3;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y = i;
}

void print_k(int& x, int& y)
{
	int i = y;
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	x += 2;
	y -= 2;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x -= 2;
	y -= 3;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "//";
	y = i;
}

void print_d(int& x, int& y)
{
	int i = y;
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y = i;
	x += 2;
	SetCursor(x, y);
	cout << "_______";
	x += 6;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	x--;
	y++;
	SetCursor(x, y);
	cout << "//";
	x--;
	y++;
	SetCursor(x, y);
	cout << "//";
	x -= 6;
	SetCursor(x, y);
	cout << "______";
	y = i;
}

void print_WWCD(int X, int Y)//min: x=0, y=1;
{
	int i = X;
	print_W(X, Y);
	X += 3;
	Y--;
	print_I(X, Y);
	Y++;
	X += 4;
	print_n(X, Y);
	X += 3;
	print_n(X, Y);
	X += 4;
	Y--;
	print_e(X, Y);
	X += 10;
	Y++;
	print_r(X, Y);
	X += 12;
	print_W(X, Y);
	X += 3;
	Y--;
	print_I(X, Y);
	Y++;
	X += 4;
	print_n(X, Y);
	X += 3;
	print_n(X, Y);
	X += 4;
	Y--;
	print_e(X, Y);
	X += 10;
	Y++;
	print_r(X, Y);
	Y += 9;
	X = i;
	print_c(X, Y);
	X += 3;
	Y -= 2;
	print_h(X, Y);
	X += 3;
	Y++;
	print_I(X, Y);
	X += 5;
	Y++;
	print_c(X, Y);
	X += 3;
	Y -= 2;
	print_k(X, Y);
	X += 5;
	Y += 2;
	print_e(X, Y);
	Y++;
	X += 9;
	print_n(X, Y);
	X += 12;
	Y -= 3;
	print_d(X, Y);
	X += 11;
	Y += 2;
	print_I(X, Y);
	Y++;
	X += 5;
	print_n(X, Y);
	X += 3;
	print_n(X, Y);
	X += 4;
	Y--;
	print_e(X, Y);
	Y++;
	X += 10;
	print_r(X, Y);
}

void print_u(int& x, int y)
{
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x += 2;
	SetCursor(x, y);
	cout << "______";
	x += 4;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "//";
	y--;
	SetCursor(x, y);
	cout << "||";
	y--;
	SetCursor(x, y);
	cout << "||";
	y--;
	SetCursor(x, y);
	cout << "||";
	y--;
	SetCursor(x, y);
	cout << "==";
}

void print_g(int& x, int y)
{
	y += 4;
	SetCursor(x, y);
	cout << "||";
	y--;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "________";
	y++;
	x += 7;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x -= 10;
	y += 2;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	cout << "_______";
	cout << "//";
	x += 6;
	y--;
	SetCursor(x, y);
	cout << "|";
	x++;
	y--;
	SetCursor(x, y);
	cout << "____";
	x += 2;
	y++;
	SetCursor(x, y);
	cout << "||";
}

void print_a(int& x, int y)
{
	y += 3;
	SetCursor(x, y);
	cout << "||";
	y--;
	SetCursor(x, y);
	cout << "//";
	y--;
	x++;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "_______";
	x += 6;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	y++;
	cout << "\\\\";
	SetCursor(x, y);
	cout << "||";
	y++;
	x -= 9;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	cout << "_____";
	x += 7;
	SetCursor(x, y);
	cout << "//";
	x++;
	y--;
	SetCursor(x, y);
	cout << "//";
	x++;
	y -= 4;
	SetCursor(x, y);
	cout << "__";
	y++;
	SetCursor(x, y);
	cout << "||";
	x++;
	y++;
	SetCursor(x, y);
	cout << "|";
	y++;
	SetCursor(x, y);
	cout << "|";
	y++;
	SetCursor(x, y);
	cout << "|";
	x--;
	y++;
	SetCursor(x, y);
	cout << "||";
}

void print_dag(int& X, int Y)
{
	Y--;
	print_d(X, Y);
	X += 11;
	Y += 2;
	print_a(X, Y);
	X += 5;
	Y -= 2;
	print_g(X, Y);
	X += 3;
	print_g(X, Y);
	X += 4;
	Y += 2;
	print_e(X, Y);
	X += 10;
	Y++;
	print_r(X, Y);
}

void print_N(int& x, int y)
{
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	x += 2;
	y -= 5;
	SetCursor(x, y);
	cout << "\\";
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\\\";
	x++;
	y++;
	SetCursor(x, y);
	cout << "\\";
	x++;
	y -= 6;
	SetCursor(x, y);
	cout << "==";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
	y++;
	SetCursor(x, y);
	cout << "||";
}

void print_l(int& x, int y)
{
	SetCursor(x, y);
	cout << "==";
	for (int i = 1; i <= 7; i++)
	{
		SetCursor(x, y);
		cout << "||";
		y++;
	}
	y--;
	x += 2;
	SetCursor(x, y);
	cout << "________";
	x += 6;
	SetCursor(x, y);
	cout << "||";
	x -= 8;
	y++;
	SetCursor(x, y);
	for (int i = 0; i < 10; i++)
	{
		cout << '=';
	}
}

void print_NULL(int X, int Y)
{
	print_N(X, Y);
	X += 4;
	Y += 2;
	print_u(X, Y);
	X += 5;
	Y -= 2;
	print_l(X, Y);
	X += 13;
	print_l(X, Y);
}

void print_win(int X, int Y)
{
	print_W(X, Y);
	X += 4;
	Y--;
	print_I(X, Y);
	X += 4;
	Y++;
	print_n(X, Y);
}

void print_WinDagger(int& x, int& y)
{
	SetCursor(x, y);
	SetColor(9, 0);
	cout << "|======";
	SetCursor(x, y + 1);
	cout << '|';
	SetColor(11, 4);
	cout << "  \\/  ";
	SetCursor(x, y + 2);
	SetColor(9, 0);
	cout << '|';
	SetColor(11, 4);
	cout << "  /\\  ";
	x += 7;
}

void print_WinNull(int& x, int& y)
{
	SetCursor(x, y);
	SetColor(9, 0);
	cout << "|======";
	SetCursor(x, y + 1);
	cout << '|';
	SetColor(10, 4);
	cout << "  /\\  ";
	SetCursor(x, y + 2);
	SetColor(9, 0);
	cout << '|';
	SetColor(10, 4);
	cout << "  \\/  ";
	x += 7;
}

void print_WinMatr(string** mass, int** winCombinate, const int m)
{
	int x = 2, y = 2;
	int n = 0;
	int k;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (mass[i][j] == "0")
				k = 0;
			else
				if (mass[i][j] == "x")
					k = 1;
				else
					k = 2;
			switch (k)
			{
			case 0:printCell(x, y);
				break;
			case 1:
				if ((winCombinate[0][n] == j) && (winCombinate[1][n] == i))
				{
					n++;
					print_WinDagger(x, y);
				}
				else
					printDagger(x, y);
				break;
			case 2:
				if ((winCombinate[0][n] == j) && (winCombinate[1][n] == i))
				{
					n++;
					print_WinNull(x, y);
				}
				else
					printNull(x, y);
				break;
			}
		}

		y += 3;
		x = 2;
	}
	SetColor(9, 0);
	while (x <= (m * 7))
	{
		SetCursor(x, y);
		cout << "|======";
		x += 7;
	}
	y = 2;
	while (y <= (m * 3))
	{
		int i = 0;
		while (i < 3)
		{
			SetCursor(x, y);
			cout << '|';
			y++;
			i++;
		}
	}
	SetCursor(x, y);
	cout << '|';
	x = 1;
	y = 3;
	SetCursor(x, y);
	SetColor(15, 0);
	if (m < 9)
		for (int i = 0; i < m; i++)
		{
			cout << i;
			y += 3;
			SetCursor(x, y);
		}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			cout << i;
			y += 3;
			SetCursor(x, y);
		}
		x--;
		SetCursor(x, y);
		for (int i = 10; i < m; i++)
		{
			cout << i;
			y += 3;
			SetCursor(x, y);
		}
	}
	x = 3;
	y = 1;
	SetCursor(x, y);
	for (int i = 0; i < m; i++)
	{
		cout << i;
		x += 7;
		SetCursor(x, y);
	}
}

void print_draw(int& X, int Y)
{
	print_d(X, Y);
	X += 11;
	Y += 3;
	print_r(X, Y);
	X += 4;
	Y--;
	print_a(X, Y);
	X += 4;
	Y++;
	print_W(X, Y);
}

bool repeatOrexit(const int n, int x1, int& num)
{
	bool ok = false;
	do
	{
		start(0);
		if (n == 0)
		{
			SetCursor(x1 + floor(x1 / 2.5), 11);
			SetColor(14, 0);
			printMessage("TIC TAC TOE");
			SetCursor(x1 + (x1 / 2.9), 13);
			SetColor(12, 0);
			printMessage("1. ");
			SetColor(10, 0);
			printMessage("Запустить ещё раз");
			SetCursor(x1 + (x1 / 2.9), 14);
			SetColor(12, 0);
			printMessage("2. ");
			SetColor(10, 0);
			printMessage("Выход");
			SetCursor(x1 + (x1 / 3.5), 17);
			SetColor(10, 0);
			printMessage("Введите: ");
			SetColor(15, 0);
		}
		else
			if (n != 0)
			{
				SetCursor(x1 + floor(x1 / 2.5), 11);
				SetColor(14, 0);
				cout << "TIC TAC TOE";
				SetCursor(x1 + (x1 / 2.9), 13);
				SetColor(12, 0);
				cout << "1. ";
				SetColor(10, 0);
				cout << "Запустить ещё раз";
				SetCursor(x1 + (x1 / 2.9), 14);
				SetColor(12, 0);
				cout << "0. ";
				SetColor(10, 0);
				cout << "Выход";
				SetCursor(x1 + (x1 / 3.5), 17);
				SetColor(10, 0);
				cout << "Введите: ";
				SetColor(15, 0);
			}
		string s;
		getline(cin, s);
		int code;
		if (checkNum(code, s, num))
			ok = true;
		else
		{
			SetCursor(x1 + (x1 / 3.5), 18);
			SetColor(14, 0);
			switch (code)
			{
				printMessage("Введена пустая строка");
			case 0:
				break;
			case 1:
				printMessage("Введен некорректный символ");
				break;
			case 2:
				printMessage("Введены некорректное число");
				break;
			}
			Sleep(200);
			system("cls");
		}
	} while (!ok);
	return num == 1;
}
