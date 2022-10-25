#include "ModifyMaze.h"

ModifyMaze::ModifyMaze(int size) : Maze(size)
{
	solve();
	_end = CalculationEndPoint();
}

void ModifyMaze::firstStep()
{
	_cells.clear();
	int tmp = _size % 8 == 0 ? _size / 8 : (_size / 8) - 1;
	Point u_border;
	u_border.x = tmp;
	u_border.y = _size - tmp - 1;
	for (int i = u_border.x + 1; i < u_border.y; i++)
	{
		_mainMaze[u_border.x + 1][i].layer_1 = wall;
		_mainMaze[i][u_border.x + 1].layer_1 = wall;
		_mainMaze[u_border.x + 1][i].layer_2 = marked;
		_mainMaze[i][u_border.x + 1].layer_2 = marked;
	}
	for (int i = u_border.y - 1; i > u_border.x; i--)
	{
		_mainMaze[u_border.y - 1][i].layer_1 = wall;
		_mainMaze[i][u_border.y - 1].layer_1 = wall;
		_mainMaze[u_border.y - 1][i].layer_2 = marked;
		_mainMaze[i][u_border.y - 1].layer_2 = marked;
	}
	for(int i = 0; i < u_border.x; i++)
		for (int j = 0; j < u_border.y; j++)
		{
			_mainMaze[i][j].layer_2 = marked;
			_mainMaze[j][i].layer_2 = marked;
		}
	for(int i = _size - 1; i >= u_border.y - 1; i--)
		for (int j = 0 ; j < _size; j++)
		{
			_mainMaze[i][j].layer_2 = marked;
			_mainMaze[j][i].layer_2 = marked;
		}
	tmp = _size % 2 == 0 ? _size / 2 : (_size / 2) + 1;
	u_border.x = tmp - 3;
	u_border.y = _size - tmp + 3;
	for(int i = u_border.x; i < u_border.y - 1; i++)
		for(int j = u_border.x; j < u_border.y - 1; j++)
			_mainMaze[i][j].layer_2 = marked;
	Point tmpPoint;
	for (int i = 1; i < _size - 1; i += 2)
		for (int j = 1; j < _size - 1; j += 2)
		{
			if (_mainMaze[i][j].layer_2 == unmarked)
			{
				tmpPoint.x = i;
				tmpPoint.y = j;
				_cells.push_back(tmpPoint);
			}
		}
	Wilson(_mainMaze);
	for (int i = u_border.x + 1; i < u_border.y; i++)
	{
		_mainMaze[u_border.x + 1][i].layer_1 = wall;
		_mainMaze[i][u_border.x + 1].layer_1 = wall;
	}
	for (int i = u_border.y - 1; i > u_border.x; i--)
	{
		_mainMaze[u_border.y - 1][i].layer_1 = wall;
		_mainMaze[i][u_border.y - 1].layer_1 = wall;
	}
}


void ModifyMaze::secondStep()
{
	_cells.clear();
	Point u_border;
	int tmp = _size % 2 == 0 ? _size / 2 : (_size / 2) + 1;
	u_border.x = tmp - 3;
	u_border.y = _size - tmp + 3;
	for (int i = u_border.x + 1; i < u_border.y; i++)
	{
		_mainMaze[u_border.x + 1][i].layer_1 = empty;
		_mainMaze[i][u_border.x + 1].layer_1 = empty;
		_mainMaze[u_border.x + 1][i].layer_2 = marked;
		_mainMaze[i][u_border.x + 1].layer_2 = marked;
	}
	for (int i = u_border.y - 1; i > u_border.x; i--)
	{
		_mainMaze[u_border.y - 1][i].layer_1 = empty;
		_mainMaze[i][u_border.y - 1].layer_1 = empty;
		_mainMaze[u_border.y - 1][i].layer_2 = marked;
		_mainMaze[i][u_border.y - 1].layer_2 = marked;
	}
	for (int i = u_border.x; i < u_border.y - 1; i++)
		for (int j = u_border.x; j < u_border.y - 1; j++)
			_mainMaze[i][j].layer_2 = unmarked;
	Point tmpPoint;
	for (int i = 1; i < _size - 1; i += 2)
		for (int j = 1; j < _size - 1; j += 2)
		{
			if (_mainMaze[i][j].layer_2 == unmarked)
			{
				tmpPoint.x = i;
				tmpPoint.y = j;
				_cells.push_back(tmpPoint);
			}
		}
	Wilson(_mainMaze);
}

void ModifyMaze::threeStep()
{
	_cells.clear();
	int tmp = _size % 8 == 0 ? _size / 8 : (_size / 8) - 1;
	Point u_border;
	u_border.x = tmp;
	u_border.y = _size - tmp - 1;
	for (int i = u_border.x; i < u_border.y - 1; i++)
		for (int j = u_border.x; j < u_border.y - 1; j++)
			_mainMaze[i][j].layer_2 = marked;
	for (int i = 0; i <= u_border.x; i++)
		for (int j = 0; j < u_border.y; j++)
		{
			_mainMaze[i][j].layer_2 = unmarked;
			_mainMaze[j][i].layer_2 = unmarked;
		}
	for (int i = _size - 1; i >= u_border.y; i--)
		for (int j = 0; j < _size; j++)
		{
			_mainMaze[i][j].layer_2 = unmarked;
			_mainMaze[j][i].layer_2 = unmarked;
		}
	Point tmpPoint;
	for (int i = 1; i < _size - 1; i += 2)
		for (int j = 1; j < _size - 1; j += 2)
		{
			if (_mainMaze[i][j].layer_2 == unmarked)
			{
				tmpPoint.x = i;
				tmpPoint.y = j;
				_cells.push_back(tmpPoint);
			}
		}
	Wilson(_mainMaze);
}
void ModifyMaze::solve()
{
	_mainMaze[_start.x][_start.y].layer_2 = unmarked;
	firstStep();
	secondStep();
	threeStep();
}