/*10. Клеточное поле размером m x n является результатом игры в крестики-нолики.
Проверить, закончена ли игра выигрышем "крестиков" или выигрышем "ноликов". Выигрыш наступает при
образовании цепочки по горизонтали, вертикали или диагонали из 5 крестиков подряд.*/

#include "interface.h"
#include"gameConsole.h"
#include "MatrObj.h"
#include "gameConsoleBot.h"
#include "MatrFile.h"

using namespace std;




# define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4703)
	


int gameFile(MatrFile &matr, int m)
{
	string filename = "test.txt";
	matr.setFileName(filename);
	matr.printMatr();
	matr.get_coord();
	return 0;
}

void gameFileBot(MatrObj matr, int m, int &n)
{

}

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	bool play = true;
	do
	{
		HWND hWnd = GetConsoleWindow();
		RECT rc;
		GetClientRect(hWnd, &rc);
		int w = rc.right;
		int h = rc.bottom;
		if ((w <= 1800) && (h <= 1000))
		{
			SetWindowPos(GetConsoleWindow(), NULL, 200, 100, 1500, 800, NULL);
			COORD a = { 1500,800 };
			SetConsoleScreenBufferSize(GetConsoleWindow(), a);
		}
		int m, x1;
		bool ok;
		string s;
		int count = 1;
		int num;
		do
		{
			x1 = start(count);
			SetCursor(x1 + (x1 / 3.5) + 9, 17);
			SetColor(15, 0);
			getline(cin, s);
			int code;
			if (inputNumOfChoiсe(num, s, code))
				ok = true;
			else
			{
				ok = false;
				count++;
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
		system("cls");
		switch (num)
		{
		case 2:
		{
			inputEdge(x1, m);
			switch (gameChoice(x1))
			{
			case 1:
			{
				string** mass = new string * [m];
				for (int i = 0; i < m; i++)
					mass[i] = new string[m];
				int** winCombinate = new int* [5];
				for (int i = 0; i < 2; i++)
					winCombinate[i] = new int[2];
				initMass(mass, m);
				num = gameConsole(mass, m - 1, winCombinate);
				print_WinMatr(mass, winCombinate, m);
				delete[] mass;
				delete[] winCombinate;
			}
				break;
			case 2:
			{
				MatrFile matr(m);
				num = gameFile(matr, m - 1);
			}
				break;
			}
			system("cls");
		}
			break;
		case 1: inputEdge(x1, m);
		{
			MatrObj matr(m - 1);
			num = choiceDaggerNull(x1);
			switch (gameChoice(x1))
			{
			case 1: num = gameConsoleBot(matr, m-1, num);
				break;
			case 2:gameFileBot(matr, m, num);
				break;
			}
			system("cls");
			matr.printMatrWin();
		}
			break;
		case 3: exit(0);
			break;
		}
		Sleep(800);
		system("cls");
		int x = 5, y = 1;
		SetColor(11, 0);
		switch (num)
		{
		case 0: SetColor(11, 0);
			print_dag(x, y);
			x += 30;
			SetColor(12, 0);
			print_win(x, y);
			break;
		case 1: SetColor(10, 0);
			print_NULL(x, y);
			x += 50;
			SetColor(12, 0);
			print_win(x, y);
			break;
		case 2: SetColor(13, 0);
			print_draw(x, y);
			break;
		}
		y += 10;
		x = 5;
		SetColor(14, 0);
		print_WWCD(x, y);
		system("pause");
		system("cls");
		int n = 0;
		play = repeatOrexit(n, x1, num);
	}while (play);
	SetCursor(0, 23);
	SetColor(15, 0);
	system("pause");
	return 0;
}


