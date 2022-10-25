#include "MatrObj.h"

MatrObj::MatrObj(int size)
{
	_x = 0;
	_y = 0;
	_size = size + 1;
	_matr = (Cell**) new Cell * [_size];
	for (int i = 0; i < _size; i++)
		_matr[i] = (Cell*) new Cell[_size];
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
		{
			_matr[i][j].update_fig('0');
		}
	_size--;
	for (int i = 0; i < 5; i++)
	{
		_winCombinate[i].X = 0;
		_winCombinate[i].Y = 0;
	}
}	

MatrObj::~MatrObj()
{
	delete[_size] _matr;
}
void MatrObj::calculation(int x, int y, char fig)
{
	float weight;
	_matr[y][x].update_fig(fig);
	int x1 = getEdge(x, 0), x2 = getEdge(x, _size);
	int y1 = getEdge(y, 0), y2 = getEdge(y, _size);
	for (int i = y1; i <= y2; i++)
		for (int j = x1; j < x; j++)
		{
			if (_matr[i][j].get_weight('x') != -10)
			{
				_matr[i][j].update_weight('x', countWeight(_matr, _size, j, i, 'x'));
				_matr[i][j].update_weight('o', countWeight(_matr, _size, j, i, 'o'));
			}
		}
	for (int i = y1; i < y; i++)
	{
		if (_matr[i][x].get_weight('x') != -10)
		{
			_matr[i][x].update_weight('x', countWeight(_matr, _size, x, i, 'x'));
			_matr[i][x].update_weight('o', countWeight(_matr, _size, x, i, 'o'));
		}
	}
	for (int i = y + 1; i < y2; i++)
	{
		if (_matr[i][x].get_weight('x') != -10)
		{
			_matr[i][x].update_weight('x', countWeight(_matr, _size, x, i, 'x'));
			_matr[i][x].update_weight('o', countWeight(_matr, _size, x, i, 'o'));
		}
	}
	for (int i = y1; i <= y2; i++)
		for (int j = x + 1; j <= x2; j++)
		{
			if (_matr[i][j].get_weight('x') != -10)
			{
				_matr[i][j].update_weight('x', countWeight(_matr, _size, j, i, 'x'));
				_matr[i][j].update_weight('o', countWeight(_matr, _size, j, i, 'o'));
			}
		}
	_matr[y][x].update_weight('x', -10);
	_matr[y][x].update_weight('o', -10);
}
void MatrObj::x_vs_o()
{
	char fig;
	float max_weight = 0;
	for (int i = 0; i <= _size; i++)
		for (int j = 0; j <= _size; j++)
		{
			if ((_matr[i][j].get_weight('x') >= max_weight) && (_matr[i][j].get_weight('x') > _matr[i][j].get_weight('o')))
			{
				fig = 'x';
				max_weight = _matr[i][j].get_weight('x');
				_x = j;
				_y = i;
			}
			else
				if (_matr[i][j].get_weight('o') >= max_weight)
				{
					fig = 'o';
					max_weight = _matr[i][j].get_weight('o');
					_x = j;
					_y = i;
				}
		}
}

COORD MatrObj::get_weight()
{
	COORD a;
	x_vs_o();
	a.X = _x;
	a.Y = _y;
	return a;
}

void MatrObj::printMatr()
{
	int x = 2, y = 2;
	for (int i = 0; i <= _size; i++)
	{
		for (int j = 0; j <= _size; j++)
			if (_matr[i][j].get_fig() =='0')
				printCell(x, y);
			else
				if (_matr[i][j].get_fig() == 'x')
					printDagger(x, y);
				else
					if (_matr[i][j].get_fig() == 'o')
						printNull(x, y);
		y += 3;
		x = 2;
	}
	SetColor(9, 0);
	while (x <= ((_size + 1) * 7))
	{
		SetCursor(x, y);
		cout << "|======";
		x += 7;
	}
	y = 2;
	while (y <= ((_size + 1) * 3))
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
	if (_size <= 9)
		for (int i = 0; i <= _size; i++)
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
		for (int i = 10; i <= _size; i++)
		{
			cout << i;
			y += 3;
			SetCursor(x, y);
		}
	}
	x = 3;
	y = 1;
	SetCursor(x, y);
	for (int i = 0; i <= _size; i++)
	{
		cout << i;
		x += 7;
		SetCursor(x, y);
	}
}

void MatrObj::printMatrWin()
{
	int x = 2, y = 2;
	int n = 0;
	int k;
	for (int i = 0; i <= _size; i++)
	{
		for (int j = 0; j <= _size; j++)
		{
			if (_matr[i][j].get_fig() == '0')
				k = 0;
			else
				if (_matr[i][j].get_fig() == 'x')
					k = 1;
				else
					k = 2;
			switch (k)
			{
			case 0:printCell(x, y);
				break;
			case 1:
				if ((_winCombinate[n].X == j) && (_winCombinate[n].Y == i))
				{
					n++;
					print_WinDagger(x, y);
				}
				else
					printDagger(x, y);
				break;
			case 2:
				if ((_winCombinate[n].X == j) && (_winCombinate[n].Y == i))
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
	while (x <= ((_size + 1) * 7))
	{
		SetCursor(x, y);
		cout << "|======";
		x += 7;
	}
	y = 2;
	while (y <= ((_size + 1) * 3))
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
	if (_size <= 9)
		for (int i = 0; i <= _size; i++)
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
		for (int i = 10; i <= _size; i++)
		{
			cout << i;
			y += 3;
			SetCursor(x, y);
		}
	}
	x = 3;
	y = 1;
	SetCursor(x, y);
	for (int i = 0; i <= _size; i++)
	{
		cout << i;
		x += 7;
		SetCursor(x, y);
	}
}

void MatrObj::setWinCell(COORD a[5])
{
	for (int i = 0; i < 5; i++)
		_winCombinate[i] = a[i];
}

bool MatrObj::checkWin(int x, int y)
{
	if (CheckWin(_matr, x, y, 90, _size, _winCombinate))
	{
		sort();
		return true;
	}
	else
		if (CheckWin(_matr, x, y, 180, _size, _winCombinate))
		{
			sort();
			return true;
		}
		else
			if (CheckWin(_matr, x, y, 45, _size, _winCombinate))
			{
				sort();
				return true;
			}
			else
				if (CheckWin(_matr, x, y, 135, _size, _winCombinate))
				{
					sort();
					return true;
				}
	return false;
}

char MatrObj::get_fig(int x, int y)
{
	return _matr[y][x].get_fig();
}
void MatrObj::print_weight(char fig)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			cout << _matr[i][j].get_weight(fig) << "  ";
		}
		cout << endl;
	}
}
void MatrObj::sort()
{
	COORD key;
	int i = 0;
	for (int j = 0; j < 5; j++)
	{
		key = _winCombinate[j];
		i = j - 1;
		while ((i >= 0) && (_winCombinate[i].X > key.X))
		{
			_winCombinate[i + 1] = _winCombinate[i];
			i = i - 1;
			_winCombinate[i + 1] = key;
		}
	}
}
