#include "AntsAlgorithm.h"

void AntsAlgorithm::criticalPoints()
{
	Maze::Point dirs;
	for (int i = 1; i < _sizeMaze - 1; i++)
	{
		for (int j = 1; j < _sizeMaze - 1; j++)
		{
			if (_maze[i][j].layer_1 == Maze::empty)
			{
				int tmp = 0;
				if (_maze[i - 1][j].layer_1 == Maze::empty)
				{
					tmp++;
					dirs.y = i - 1;
					dirs.x = j;
					_addMaze[i][j].layer_2.directions.push_back(dirs);
				}
				if (_maze[i][j + 1].layer_1 == Maze::empty)
				{
					tmp++;
					dirs.y = i;
					dirs.x = j + 1;
					_addMaze[i][j].layer_2.directions.push_back(dirs);
				}
				if (_maze[i + 1][j].layer_1 == Maze::empty)
				{
					tmp++;
					dirs.y = i + 1;
					dirs.x = j;
					_addMaze[i][j].layer_2.directions.push_back(dirs);
				}
				if (_maze[i][j - 1].layer_1 == Maze::empty)
				{
					tmp++;
					dirs.y = i;
					dirs.x = j - 1;
					_addMaze[i][j].layer_2.directions.push_back(dirs);
				}
				_addMaze[i][j].layer_2.critical = tmp;
			}
		}
	}
}


vector<Maze::Point> AntsAlgorithm::GetWaysSolve(Maze* maze)
{
	_maze = maze->GetMaze();
	_sizeMaze = maze->GetSize();
	_addMaze = new AddicionalLayers * [_sizeMaze];
	for (int i = 0; i < _sizeMaze; i++)
		_addMaze[i] = new AddicionalLayers[_sizeMaze];
	for(int i = 0; i < _sizeMaze; i++)
		for (int j = 0; j < _sizeMaze; j++)
		{
			_addMaze[i][j].layer_1 = new int[_antCount];
			_addMaze[i][j].layer_2.critical = 0;
			_addMaze[i][j].layer_2.feromon = 0;
		}
	for (int k = 0; k < _sizeMaze; k++)
		for (int i = 0; i < _sizeMaze; i++)
			for (int j = 0; j < _sizeMaze; j++)
				_addMaze[i][j].layer_1[k] = _maze[i][j].layer_1;
	criticalPoints();
	Maze::Point start = maze->GetStartPoint();
	Maze::Point end = maze->GetEndPoint();
	for (int i = 0; i < antsCount; i++)
	{
		Ant* ant = new Ant(_sizeMaze, start, end);
		vector<Maze::Point> tmp = ant->GetWays(_addMaze);
		if (tmp.size() != 0)
			_antWays.push_back(tmp);
	}
	int min = _antWays[0].size();
	int index = 0;
	for(int i = 0; i < _antWays.size(); i++)
		if (_antWays[i].size() < min)
		{
			min = _antWays[i].size();
			index = i;
		}
	return _antWays[index];
}

