#include "CheckWin.h"
//проверяет линию на выигрыш в одном направлении 
bool CheckWinLine(Cell** matr, int x, int y, const int dx, const int dy, COORD(&a)[5], int& count, const int m)//параметр count должен иметь изначально значение 0
{
	bool ok = true;
	char fig = matr[y][x].get_fig();
	while ((count < 5) && (y >= 0) && (x >= 0) && (y <= m) && (x <= m) && ok)
	{
		if (fig == matr[y][x].get_fig())
		{
			a[count].X = x;
			a[count].Y = y;
			count++;
		}
		else
			ok = false;
		y += dy;
		x += dx;
	}
	return count == 5;
}

//преобразует градусную меру в координаты для изменения
COORD ToCoord(const int deg)
{
//90-против оси ОY
//-90- по оси OY
//180- по оси OX
//-180-против оси OX
//45- по побочной диагонали
//-45- против побочной диагонали
//135- по главной диагонали
//-135- против главной диагонали
	COORD a;
	switch (deg)
	{
	case 90: 
		a.X = 0;
		a.Y = 1;
		return a;
	case -90:
		a.X = 0;
		a.Y = -1;
		return a;
	case 180:
		a.X = 1;
		a.Y = 0;
		return a;
	case -180:
		a.X = -1;
		a.Y = 0;
		return a;
	case 45:
		a.X = 1;
		a.Y = -1;
		return a;
	case -45:
		a.X = -1;
		a.Y = 1;
		return a;
	case 135:
		a.X = 1;
		a.Y = 1;
		return a;
	case - 135:
		a.X = -1;
		a.Y = -1;
		return a;
	}
}

//проверяет линию на выигрыш в двух направлениях
bool CheckWin(Cell** matr, const int x, const int y, const int line, const int m, COORD (&winCombinate)[5])
{
	COORD a;
	COORD WinCombinate1[5], WinCombinate2[5];
	int count1 = 0, count2 = 0;
	a = ToCoord(line);
	if (!CheckWinLine(matr, x, y, a.X, a.Y, WinCombinate1, count1, m))
	{
		a = ToCoord(-line);
		if (CheckWinLine(matr, x, y, a.X, a.Y, WinCombinate2, count2, m))
			for (int i = 0; i < count2; i++)
			{
				winCombinate[i] = WinCombinate2[i];
				return true;
			}
		else
			if ((count1 + count2) >= 6)
			{
				int n;
				for (n = 0; n < count2; n++)
					winCombinate[n] = WinCombinate2[n];
				for (int i = 0; i < count1; i++)
				{
					winCombinate[n] = WinCombinate1[n];
					n++;
				}
				return true;
			}
	}
	else
	{
		for (int i = 0; i < count1; i++)
			winCombinate[i] = WinCombinate1[i];
		return true;
	}
	return false;
}
