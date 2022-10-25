#include "gameConsoleBot.h"

bool inputCoordOfCell(MatrObj& matr, const int m, int& x1, int& y1, const int kol, string message)
{
	system("cls");
	matr.printMatr();
	int x = 2;
	int y = (m + 1) * 3 + 5;
	SetCursor(x, y - 1);
	SetColor(14, 0);
	printMessage(message);
	SetCursor(x, y);
	SetColor(10, 0);
	if (kol == 0)
	{
		printMessage("¬ведите номера €чеек в последовательности ");
		SetColor(12, 0);
		printMessage("X, Y");
		SetColor(10, 0);
		cout << ": ";
	}
	else
	{
		cout << "¬ведите номера €чеек в последовательности ";
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
		case 0: printMessage("¬ведена пуста€ строка");
			break;
		case 1: printMessage("¬веден некореектный символ");
			break;
		case 2: printMessage("¬ведено некорректное число");
			break;
		}
		return false;
	}
	else
	{
		if (matr.get_fig(x1, y1) == '0')
			return true;
		else
		{
			SetColor(14, 0);
			SetCursor(x, y + 1);
			printMessage("ƒанна€ €чейка уже зан€та");
			return false;
		}
	}
}

int gameConsoleBot(MatrObj& matr, const int m, int fig)
{
	system("cls");
	int x, y;
	int k = m * m;
	int n = 0;
	int count = 0;
	COORD a;
	if (fig == 2)//выбрали играть ноликом
	{
		if ((m % 2) == 0)
		{
			x = m / 2;
			y = m / 2;
		}
		else
		{
			x = (m + 1) / 2;
			y = (m + 1) / 2;
		}
		matr.calculation(x, y, 'x');
		count++;
		while (count != k)
		{
			while (!inputCoordOfCell(matr, m, x, y, n, "¬аш ход"))
				n++;
			matr.calculation(x, y, 'o');
			if ((count >= 8) && (matr.checkWin(x, y)))
				return 1;
			count++;
			a = matr.get_weight();
			matr.calculation(a.X, a.Y, 'x');
			/*system("cls");
			matr.print_weight('x');
			system("cls");
			matr.print_weight('o');*/
			count++;
			if ((count >= 8) && (matr.checkWin(a.X, a.Y)))
				return 0;
			n = 0;
		}
	}
	else
	{
		while (count != k)
		{
			while (!inputCoordOfCell(matr, m, x, y, n, "¬аш ход"))
				n++;
			matr.calculation(x, y, 'x');
			if ((count >= 8) && (matr.checkWin(x, y)))
				return 0;
			count++;
			a = matr.get_weight();
			/*system("cls");
			matr.print_weight('x');
			system("cls");
			matr.print_weight('o');*/
			matr.calculation(a.X, a.Y, 'o');
			count++;
			if ((count >= 8) && (matr.checkWin(a.X, a.Y)))
				return 1;
			n = 0;
		}
	}
}
