#include "gameConsole.h"

bool checkVertical(string** mass, int x, int y, const int m, string symbol, int** &a)
{
	bool ok = true;
	int y1 = y;
	y--;
	int n = 0;
	int k = 0;
	int up[4];
	int down[4];
	int l;
	while (ok && (y >= 0) && (n < 4))
		if (mass[y][x] != symbol)
			ok = false;
		else
		{
			up[n] = y;
			y--;
			n++;
		}
	if (n != 4)
	{
		ok = true;
		y = y1;
		y++;
		while (ok && (y <= m) && (k <= 4))
			if (mass[y][x] != symbol)
				ok = false;
			else
			{
				down[k] = y;
				y++;
				k++;
			}
	}
		if (n == 4)
		{
			ok = true;
			l = n - 1;
			for (int i = 0; i < 4; i++)
			{
				a[0][i] = x;
				a[1][i] = up[l];
				l--;
			}
			a[0][4] = x;
			a[1][4] = y1;
		}
		else if (k== 4)
		{
			ok = true;
			a[0][0] = x;
			a[1][0] = y1;
			for (int i = 1; i < 5; i++)
			{
				a[0][i] = x;
				a[1][i] = down[i - 1];
			}
		}
	else
		if ((n + k) == 4)
		{
			ok = true;
			l = n - 1;
			for (int i = 0; i < n; i++)
			{
				a[0][i] = x;
				a[1][i] = up[l];
				l--;
			}
			a[0][n] = x;
			a[1][n] = y1;
			for (int i = 0; i < k; i++)
			{
				a[0][5 - k + i] = x;
				a[1][5 - k + i] = down[i];
			}
		}
	return ok;
}

bool checkHorizon(string** mass, int x, int y, const int m, string symbol, int** &a)
{
	bool ok = true;
	int x1 = x;
	x--;
	int n = 0;
	int k = 0;
	int left[4];
	int right[4];
	int l;
	while (ok && (x >= 0) && (n < 4))
		if (mass[y][x] != symbol)
			ok = false;
		else
		{
			left[n] = x;
			x--;
			n++;
		}
	if (n != 4)
	{
		ok = true;
		x = x1;
		x++;
		while (ok && (x <= m) && (k < 4))
			if (mass[y][x] != symbol)
				ok = false;
			else
			{
				right[k] = x;
				x++;
				k++;
			}
	}
		if (n == 4)
		{
			ok = true;
			l = n - 1;
			for (int i = 0; i < 4; i++)
			{
				a[0][i] = left[l];
				a[1][i] = y;
				l--;
			}
			a[0][4] = x1;
			a[1][4] = y;
		}
		else if (k == 4)
		{
			ok = true;
			a[0][0] = x1;
			a[1][0] = y;
			for (int i = 1; i < 5; i++)
			{
				a[0][i] = right[i - 1];
				a[0][i] = y;
			}
		}
	else
		if ((n + k) == 4)
		{
			ok = true;
			l = n - 1;
			for (int i = 0; i < n; i++)
			{
				a[0][i] = left[i];
				a[1][i] = y;
				l--;
			}
			a[0][n] = x1;
			a[1][n] = y;
			for (int i = 0; i < k; i++)
			{
				a[0][5 - k + i] = right[i];
				a[1][5 - k + i] = y;
			}
		}

	return ok;
}

bool checkDiagonal(string** mass, int x, int y, const int m, string symbol, int** &a)
{
	bool ok = true;
	int x1 = x;
	x--;
	int y1 = y;
	y--;
	int n = 0;
	int k = 0;
	int l;
	int up[2][4];
	int down[2][4];
	while (ok && (x >= 0) && (y>=0) && (n < 4))
		if (mass[y][x] != symbol)
			ok = false;
		else
		{
			up[0][n] = x;
			up[1][n] = y;
			x--;
			y--;
			n++;
		}
	if (n != 4)
	{
		ok = true;
		x = x1;
		x++;
		y = y1;
		y++;
		while (ok && (x <= m) && (y<=m) && (k < 4))
			if (mass[y][x] != symbol)
				ok = false;
			else
			{
				down[0][k] = x;
				down[1][k] = y;
				x++;
				y++;
				k++;
			}
	}
		if (n == 4)
		{
			ok = true;
			l = n - 1;
			for (int i = 0; i < 4; i++)
			{
				a[0][i] = up[0][l];
				a[1][i] = up[1][l];
				l--;
			}
			a[0][4] = x1;
			a[1][4] = y1;
		}
		else if (k == 4)
		{
			ok = true;
			a[0][0] = x1;
			a[1][0] = y;
			for (int i = 1; i < 5; i++)
			{
				a[0][i] = down[0][i];
				a[1][i] = down[1][i];
			}
		}
	else
		if ((n + k) == 4)
		{
			ok = true;
			l = n - 1;
			for (int i = 0; i < n; i++)
			{
				a[0][i] = up[0][l];
				a[1][i] = up[1][l];
				l--;
			}
			a[0][n] = x1;
			a[1][n] = y;
			for (int i = 0; i < k-1; i++)
			{
				a[0][5 - k + i] = down[0][i];
				a[1][5 - k + i] = down[1][i];
			}
		}
	if (!ok)
	{
		ok = true;
		x = x1;
		y = y1;
		x++;
		y--;
		n = 0;
		k = 0;
		while (ok && (x <= m) && (y>=0) && (n < 4))
			if (mass[y][x] != symbol)
				ok = false;
			else
			{
				up[0][n] = x;
				up[1][n] = y;
				x--;
				y++;
				n++;
			}
		if (n != 4)
		{
			ok = true;
			x = x1;
			y = y1;
			x--;
			y++;
			while (ok && (x >= 0) && (y<=m) && (k < 4))
				if (mass[y][x] != symbol)
					ok = false;
				else
				{
					down[0][k] = x;
					down[1][k] = y;
					x++;
					y--;
					k++;
				}
		}
			if (n == 4)
			{
				ok = true;
				l = n - 1;
				for (int i = 0; i < 4; i++)
				{
					a[0][i] = up[0][l];
					a[1][i] = up[1][l];
				}
				a[0][4] = x1;
				a[1][4] = y1;
				l--;
			}
			else if (k== 4)
			{
				ok = true;
				a[0][0] = x1;
				a[1][0] = y;
				for (int i = 1; i < 5; i++)
				{
					a[0][i] = down[0][i];
					a[1][i] = down[1][i];
				}
			}
		else
			if ((n + k) == 4)
			{
				ok = true;
				l = n - 1;
				for (int i = 0; i < n; i++)
				{
					a[0][i] = up[0][l];
					a[1][i] = up[1][l];
					l--;
				}
				a[0][n] = x1;
				a[1][n] = y;
				for (int i = 0; i < k; i++)
				{
					a[0][5 - k + i] = down[0][i];
					a[1][5 - k + i] = down[1][i];
				}
			}
	}
	return ok;
}

int gameConsole(string**& mass, const int m, int** &winCombinate)
{
	int x, y;
	int n = 0;
	bool ok = false;
	int count = 0;
	int k = (m-1) * (m-1);
	do
	{
		while (!inputCoordCell(mass, m, x, y, n, "Ход игрока крестик"))
			n++;
		mass[y][x] = "x";
		if (count >= 8)
			if (checkVertical(mass, x, y, m, "x", winCombinate))
				return 0;
			else
				if (checkHorizon(mass, x, y, m, "x", winCombinate))
					return 0;
				else
					if (checkDiagonal(mass, x, y, m, "x", winCombinate))
						return 0;
		n = 0;
		count++;
		while (!inputCoordCell(mass, m, x, y, n, "Ход игрока нолик"))
			n++;
		mass[y][x] = "o";
		if (count >= 9)
			if (checkVertical(mass, x, y, m, "o", winCombinate))
				return 1;
			else
				if (checkHorizon(mass, x, y, m, "o", winCombinate))
					return 1;
				else
					if (checkDiagonal(mass, x, y, m, "o", winCombinate))
						return 1;
		n = 0;
		count++;
		if (count == k)
			return 2;
	} while (!ok);
}