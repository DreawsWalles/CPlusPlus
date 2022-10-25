#include "RandomMaze.h"

RandomMaze::RandomMaze(int size) : Maze(size)
{
	_mazeAdd = new MazeStruct * [size];
	_addMaze = new int* [size];
	for (int i = 0; i < size; i++)
	{
		_mazeAdd[i] = new MazeStruct[size];
		_addMaze[i] = new int[size];
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			_mazeAdd[i][j].layer_1 = wall;
			_mazeAdd[i][j].layer_2 = unmarked;
		}
	Point tmp;
	for (int i = 1; i < size - 1; i += 2)
		for (int j = 1; j < size - 1; j += 2)
		{
			_mazeAdd[i][j].layer_1 = Cell::empty;
			_mazeAdd[j][i].layer_1 = Cell::empty;
		}
	_mazeAdd[_start.x][_start.y].layer_2 = marked;
	solve();
	_end = CalculationEndPoint();
}



bool RandomMaze::backtracking(int k, int x, int y, MazeStruct** maze)
{
	int j = -1;
	int u, v;
	bool q = false;
	do
	{
		j++;
		u = x + p[j]; v = y + z[j];
		if (((u >= 0 && u <= _size - 1) && (v >= 0 && v <= _size - 1)) && maze[u][v].layer_1 == empty && _addMaze[u][v] == 0)
		{
			Point tmp = { u,v };
			_way.push_back(tmp);
			if (u != _end.x || v != _end.y)
			{
				q = backtracking(k + 1, u, v, maze);
				if (!q)
					_way.pop_back();
			}
			else return true;
		}
	} while (!q && j != 3);
	return q;
}


void RandomMaze::solve()
{
	Wilson(_mainMaze);
	if (backtracking(2, _start.x, _start.y, _mainMaze))
	{
		mazeClear(_mainMaze);
		for (int i = 0; i < _way.size(); i++)
		{
			_mainMaze[_way[i].x][_way[i].y].layer_1 = empty;
			if (_way[i].x % 2 == 1 && _way[i].y % 2 == 1)
				_mainMaze[_way[i].x][_way[i].y].layer_2 = marked;
		}
	}
	length_1 = _way.size() + 1;
	_way.clear();
	_cells = _cellsDefault;
	Wilson(_mazeAdd);
	if (backtracking(2, _start.x, _start.y, _mazeAdd))
	{
		for (int i = 0; i < _way.size(); i++)
		{
			_mainMaze[_way[i].x][_way[i].y].layer_1 = empty;
			if (_way[i].x % 2 == 1 && _way[i].y % 2 == 1)
				_mainMaze[_way[i].x][_way[i].y].layer_2 = marked;
		}
	}
	mazeClear(_mazeAdd);
	_cells.clear();
	length_2 = _way.size() + 1;
	Point tmp;
	for (int i = 1; i < _size - 1; i += 2)
		for (int j = 1; j < _size - 1; j += 2)
		{
			if (_mainMaze[i][j].layer_2 == unmarked)
			{
				tmp.x = i; 
				tmp.y = j; 
				_cells.push_back(tmp);
			}
		}
	_way.clear();
	_count = _countDefault;
	Wilson(_mainMaze);
	//_mainMaze[_start.y][_start.x - 1].layer_1 = empty;
	//_mainMaze[_end.y][_end.x + 1].layer_1 = empty;
}

