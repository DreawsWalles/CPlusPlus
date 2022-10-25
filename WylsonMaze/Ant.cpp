#include "AntsAlgorithm.h"
#include <algorithm>

using namespace std;

Ant::Ant(int sizeMaze, Maze::Point start, Maze::Point end)
{
	_size = sizeMaze;
	_start = start;
	_end = end;
	_length = 1;
	_found = false;
}

Ant::~Ant()
{

}



double Ant::getRandom()
{
	return double((rand() % 101)) / 100.0;
}


void Ant::Clear()
{
	
}

//����������� ��������, ��� ��������� ��������
bool Ant::getWay(AntsAlgorithm::AddicionalLayers**& maze, Maze::Point previous, Maze::Point current, Maze::Point startPoint, Maze::Point direction)
{
	//��������, ����� �� ��������� � �����
	//�� ������ ������� ������ ��������, � ����������� � ������� �� ������ ��������, ����� � ���������� ������ ��� �����������, � ������, ���� ��� �����
	if (maze[current.y][current.x].layer_2.critical == 1)
	{
		vector<Maze::Point> dir;
		for (int i = 0; i < maze[startPoint.y][startPoint.x].layer_2.directions.size(); i++)
			if(maze[startPoint.y][startPoint.x].layer_2.directions[i] != direction)
				dir.push_back(maze[startPoint.y][startPoint.x].layer_2.directions[i]);
		maze[startPoint.y][startPoint.x].layer_2.directions = dir;
		maze[startPoint.y][startPoint.x].layer_2.critical--;
		return false;
	}
	//�������, ����� �� ����� �� �����
	if (current == _end)
	{
		//������� � ���, ��� �� � ����� ���������� �������
		_found = true;
		vector<Maze::Point> dir;
		ant_memory.push_back(current);
		//������� ��� ���������� ��� ����, ����� ������ ���������� ������� 
		for (int i = 0; i < maze[startPoint.y][startPoint.x].layer_2.directions.size(); i++)
			if (maze[startPoint.y][startPoint.x].layer_2.directions[i] != direction)
				dir.push_back(maze[startPoint.y][startPoint.x].layer_2.directions[i]);
		maze[startPoint.y][startPoint.x].layer_2.directions = dir;
		maze[startPoint.y][startPoint.x].layer_2.critical--;
		return true;
	}
	//�������, ����� �� �������� �� ������, �� ������� ���� �� ������ ��������, ��� ���� �� ������ ��� �������� ��� ��������� ����������
	else if (maze[current.y][current.x].layer_2.critical == 2 &&
		find(ant_memory.begin(), ant_memory.end(), previous) != ant_memory.end())
	{
		maze[current.y][current.x].layer_2.feromon += _length * rho;
		_length++;
		ant_memory.push_back(current);
		int i = 0;
		while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
			//i = rand() % maze[current.y][current.x].layer_2.directions.size();
			i++;
		return getWay(maze, current, maze[current.y][current.x].layer_2.directions[i], startPoint, direction);
	}
	//������� ����� �� ��������� ��������
	else
	{
		int i = 0;
		while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
			//i = rand() % maze[current.y][current.x].layer_2.directions.size();
			i++;
		ant_memory.push_back(current);
		return getWay(maze, current, maze[current.y][current.x].layer_2.directions[i], current, maze[current.y][current.x].layer_2.directions[i]);
	}
}

//�������� ��������
//� ������ ��������� ��� �������� �������� �� ������ ��������������� ��, ��� � ��� �� ���� ��� ������� ��������.
vector<Maze::Point> Ant::GetWays(AntsAlgorithm::AddicionalLayers** &maze)
{
	Maze::Point current = _start;
	Maze::Point previous = _start;
	vector<Maze::Point> result;
	//��������� ����, ��� �������, ����� �� ��������� � ������ � ��� ����� �������� �� ������
	while (!_found && maze[current.y][current.x].layer_2.critical != 0)
	{
		//���������, �� ������ �� �� � ����� ���������
		if (current == _end)
		{
			_found = true;
		}
		//�������� �� ��, ��������� �� �� ��� ������ ��� �� � ��� ���� ������� � ���������
		else if (maze[current.y][current.x].layer_2.critical == 1 || (maze[current.y][current.x].layer_2.critical == 2 && find(ant_memory.begin(), ant_memory.end(), previous) != ant_memory.end()))
		{
			//���� �� �������� � �����, � ��� ���� ��� ��������� �������, �� �� ������ ������� �� ��������� ������� ��� ��������� ����
			if (maze[current.y][current.x].layer_2.critical == 1 && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[0]) != ant_memory.end())
			{
				maze[_start.y][_start.x].layer_2.directions.clear();
				maze[_start.y][_start.x].layer_2.critical = 0;
				return result;
			}
			//����������� �� ������
			maze[current.y][current.x].layer_2.feromon += _length * rho;
			_length++;
			ant_memory.push_back(current);
			previous = current;
			int i = 0;
			while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
				//i = rand() % maze[current.y][current.x].layer_2.directions.size();
				i++;
			current = maze[current.y][current.x].layer_2.directions[i];
		}
		//�������, ����� �� ������� � ����� ��������. ����� ���������� ��������� ��������, �� �������� �� ���� ������� ���������� ����, ���� ������� � �����
		else
		{
			if (previous == _start)
				ant_memory.push_back(previous);
			int i = 0;
			while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
				//i = rand() % maze[current.y][current.x].layer_2.directions.size();
				i++;
			return getWay(maze, _start, maze[current.y][current.x].layer_2.directions[i], current, maze[current.y][current.x].layer_2.directions[i]) == false ? result :  ant_memory;
		}
	}
	return result;
}