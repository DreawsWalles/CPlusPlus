#include "Maze.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <malloc.h>
#include <algorithm>

using namespace std;
Maze::Maze(int size)
{
	this->_size = size;
	_mainMaze = new MazeStruct * [size];
	for (int i = 0; i < size; i++)
		_mainMaze[i] = new MazeStruct[size];
	_start = CalculationStartPoint();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			_mainMaze[i][j].layer_1 = wall;
			_mainMaze[i][j].layer_2 = unmarked;
		}
	Point tmp;
	for(int i = 1; i < size - 1; i += 2)
		for (int j = 1; j < size - 1; j += 2)
		{
			_mainMaze[i][j].layer_1 = empty;
			_mainMaze[j][i].layer_1 = empty;
			tmp.x = j;
			tmp.y = i;
			_cells.push_back(tmp);
			_count++;
		}
	_end = CalculationEndPoint();
	_mainMaze[_start.x][_start.y].layer_2 = marked;
	_count--;
	_countDefault = _count;
	for (int i = 0; i < _cells.size(); i++)
		if (_cells[i].x == _start.x && _cells[i].y == _start.y)
			_cells.erase(_cells.begin() + i);
	_cellsDefault = _cells;
}

Maze::Point Maze::pickRandom()
{
	Point res;
	int k = rand() % (_cells.size());
	res = _cells[k];
	_cells.erase(_cells.begin() + k);
	return res;
}

Maze::Point Maze::dir(Point current, Point prev, MazeStruct** M)
{
	bool is_valid = false;
	int direction;
	Point res;
	while (!is_valid)
	{
		direction = (rand() % 4000) / 1000; //0 - up, 1 - right, 2 - down, 3 - left;
		switch (direction)
		{
		case 0: {
			if (current.y - 2 > 0 && current.y - 2 != prev.y && M[current.x][current.y - 2].layer_2 != inactive)
			{
				is_valid = true;
				res.x = current.x;
				res.y = current.y - 2;
			}
			break; }

		case 1: {
			if (current.x + 2 < _size - 1 && current.x + 2 != prev.x && M[current.x + 2][current.y].layer_2 != inactive)
			{
				is_valid = true;
				res.x = current.x + 2;
				res.y = current.y;
			}
			break; }

		case 2: {
			if (current.y + 2 < _size - 1 && current.y + 2 != prev.y && M[current.x][current.y + 2].layer_2 != inactive)
			{
				is_valid = true;
				res.x = current.x;
				res.y = current.y + 2;
			}
			break;
		}
		case 3: {
			if (current.x - 2 > 0 && current.x - 2 != prev.x && M[current.x - 2][current.y].layer_2 != inactive)
			{
				is_valid = true;
				res.x = current.x - 2;
				res.y = current.y;
			}
		}
		}
	}
	return res;
}

void Maze::copy(MazeStruct** src, MazeStruct** dest)
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			dest[i][j] = src[i][j];
}

void Maze::mazeClear(MazeStruct** maze)
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
		{
			maze[i][j].layer_1 = wall;
			maze[i][j].layer_2 = unmarked;
		}
	for (int i = 1; i < _size - 1; i += 2)
		for (int j = 1; j < _size - 1; j += 2)
		{
			maze[i][j].layer_1 = maze[j][i].layer_1 = empty;
		}
	maze[_start.x][_start.y].layer_2 = marked;
}

void Maze::Wilson(MazeStruct** _maze)
{
	MazeStruct** maze = new MazeStruct * [_size];
	for (int i = 0; i < _size; i++)
		maze[i] = new MazeStruct[_size];
	copy(_maze, maze);
	Point direction;
	Point cursor;
	Point previous = { 0,0 };
	bool error = false;
	Point first;
	vector<Point> memory;

	while (!_cells.empty())
	{
		memory.clear();
		bool branch_found = false;
		int counter = 0;
		first = pickRandom();
		cursor = first;
		previous.x = 0; previous.y = 0;
		maze[cursor.x][cursor.y].layer_2 = temporary;
		memory.push_back(first);
		while (!branch_found)
		{
			direction = dir(cursor, previous, maze); 
			if (maze[direction.x][direction.y].layer_2 == unmarked)
			{
				previous = cursor;
				cursor = direction;
				maze[direction.x][direction.y].layer_2 = temporary;
				memory.push_back(cursor);
				counter++;
			}
			else if (maze[direction.x][direction.y].layer_2 == temporary)
			{
				cursor = direction;
				bool border = false;
				for (int i = memory.size() - 1; i > -1 && !border; i--)
				{
					if (i > 0)
						if (memory[i - 1].x == direction.x && memory[i - 1].y == direction.y) 
							border = true;
					maze[memory[i].x][memory[i].y].layer_2 = unmarked;
					memory.pop_back();
					counter--;
				}
				if (memory.size() > 1)
					previous = memory[memory.size() - 2];
				else previous = { 0,0 };
			}
			else if (maze[direction.x][direction.y].layer_2 == marked)
			{
				memory.push_back(direction);
				maze[memory[0].x][memory[0].y].layer_2 = marked;
				for (int i = 1; i < memory.size(); i++)
				{
					maze[(memory[i - 1].x + memory[i].x) / 2][(memory[i - 1].y + memory[i].y) / 2].layer_1 = empty;
					maze[memory[i].x][memory[i].y].layer_2 = marked;
				}
				for (int i = 0; i < memory.size(); i++)
				{
					for (int k = 0; k < _cells.size(); k++)
					{
						if (memory[i].x == _cells[k].x && memory[i].y == _cells[k].y)
							_cells.erase(_cells.begin() + k);
					}
				}
				_count -= (counter + 1);
				branch_found = true;
				memory.clear();
			}
		}
	}
	copy(maze, _maze);
	for (int i = 0; i < _size; i++)
		delete[]maze[i];
}

void Maze::Print(IRepository* repository)
{
	if (repository != nullptr)
	{
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
				if (_mainMaze[i][j].layer_1 == wall)
				{
					repository->SetColor(10, 0);
					repository->Output(static_cast<char>(219));
				}
				else if (i == _end.y && j == _end.x)
				{
					repository->SetColor(4, 0);
					repository->Output(static_cast<char>(219));
				}
				else if (i == _start.y && j == _start.x)
				{
					repository->SetColor(4, 0);
					repository->Output(static_cast<char>(219));
				}
				else
				{
					repository->SetColor(15, 0);
					repository->Output(static_cast<char>(219));
				}
			repository->Output("\r\n");
		}
		repository->SetColor(15, 0);
	}
	else
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
				if (_mainMaze[i][j].layer_1 == wall)
					cout << static_cast<char>(219);
				else
					cout << " ";
			cout << "\r\n";
		}
}

Maze::MazeStruct** Maze::GetMaze()
{
	return _mainMaze;
}

int Maze::GetSize()
{
	return _size;
}

Maze::Point Maze::GetStartPoint()
{
	return _start;
}

Maze::Point Maze::GetEndPoint()
{
	return _end;
}

bool Maze::check(vector<Maze::Point> vec, Maze::Point point)
{
	int i = 0;
	while (i < vec.size())
	{
		if (vec[i] == point)
			return true;
		i++;
	}
	return false;
}

void Maze::PrintWaysSolve(vector<Point> solve, IRepository* repository)
{
	if (repository != nullptr)
	{
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				Point tmp;
				tmp.y = i;
				tmp.x = j;
				if (check(solve, tmp))
				{
					repository->SetColor(5, 0);
					repository->Output(static_cast<char>(219));
				}
				else if (_mainMaze[i][j].layer_1 == wall)
				{
					repository->SetColor(10, 0);
					repository->Output(static_cast<char>(219));
				}
				else
				{
					repository->SetColor(15, 0);
					repository->Output(static_cast<char>(219));
				}
			}
			repository->Output("\r\n");
		}
		repository->SetColor(15, 0);
	}
	else
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				Point tmp;
				tmp.y = i;
				tmp.x = j;
				if (check(solve, tmp))
					cout << "*";
				else if (_mainMaze[i][j].layer_1 == wall)
					cout << static_cast<char>(219);
				else
					cout << " ";
			}
			cout << "\r\n";
		}
}

Maze::Point Maze::CalculationStartPoint()
{
	Maze::Point result;
	result.y = 1;
	result.x = 1;
	for(int i = 0; i < _size; i++)
		for(int j = 0; j <_size; j++)
			if (_mainMaze[i][j].layer_1 == Maze::empty)
			{
				result.x = j;
				result.y = i;
				return result;
			}
	return result;
}

Maze::Point Maze::CalculationEndPoint()
{
	Maze::Point result;
	result.x = _size - 1;
	result.y = _size - 1;
	for(int i = _size - 1; i >= 0; i--)
		for(int j = _size - 1; j >= 0; j--)
			if (_mainMaze[i][j].layer_1 == Maze::empty)
			{
				result.y = i;
				result.x = j;
				return result;
			}
	return result;
}

void Maze::ChangeStartPoint(Maze::Point point)
{
	if (point.x >= _size || point.y >= _size || point.x < 0 || point.y < 0)
		throw exception("Точка с данными координатами находится вне лабиринта");
	if (_mainMaze[point.y][point.x].layer_1 == Maze::wall)
		throw exception("Точка с данными координатами не может быть началом лабиринта");
	if (point == _end)
		throw exception("Точка с данными координатами совпадает с концом лабиринта");
	_start = point;
}

void Maze::ChangeEndPoint(Maze::Point point)
{
	if (point.x >= _size || point.y >= _size || point.x < 0 || point.y < 0)
		throw exception("Точка с данными координатами находится вне лабиринта");
	if (_mainMaze[point.y][point.x].layer_1 == Maze::wall)
		throw exception("Точка с данными координатами не может быть началом лабиринта");
	if (point == _start)
		throw exception("Точка с данными координатами совпадает с началом лабиринта");
	_end = point;
}