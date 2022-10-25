#include "CircleMaze.h"

CircleMaze::CircleMaze(int size) : Maze(size)
{
	solve();
	_end = CalculationEndPoint();
}

void CircleMaze::solve()
{
	_cells.clear();
	_mainMaze[_start.x][_start.y].layer_2 = unmarked;
	int width_out = _size / 8;
	if (width_out % 2 == 1) 
		width_out++;
	Point u_border;
	u_border.x = width_out;
	u_border.y = _size - width_out - 1;
	for (int i = u_border.x + 1; i < u_border.y; i++)
	{
		_mainMaze[u_border.x + 1][i].layer_1 = empty; 
		_mainMaze[i][u_border.x + 1].layer_1 = empty;
		if (i % 2 == 1)
		{
			_mainMaze[u_border.x + 1][i].layer_2 = marked; 
			_mainMaze[i][u_border.x + 1].layer_2 = marked;
		}
	}
	for (int i = u_border.y - 1; i > u_border.x; i--)
	{
		_mainMaze[u_border.y - 1][i].layer_1 = empty;
		_mainMaze[i][u_border.y - 1].layer_1 = empty;
		if (i % 2 == 1)
		{
			_mainMaze[u_border.y - 1][i].layer_2 = marked; 
			_mainMaze[i][u_border.y - 1].layer_2 = marked;
		}
	}
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
	Wilson(_mainMaze);
}