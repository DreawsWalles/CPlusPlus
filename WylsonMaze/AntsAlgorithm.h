#pragma once
#include "SolveMaze.h"

class AntsAlgorithm :
    public SolveMaze
{
public:

	struct AntLayer
	{
		int critical;
		vector<Maze::Point> directions;
		int next_chosen_coords;
		double feromon;
	};
	struct AddicionalLayers
	{
		int* layer_1;
		AntLayer layer_2;
	};
	vector<Maze::Point> GetWaysSolve(Maze* maze);
private:
	const int antsCount = 200;
	AddicionalLayers** _addMaze;
	vector<vector<Maze::Point>> _antWays;
	void criticalPoints();
};

class Ant
{
private:
	const double rho = 1.02;
	int _size;
	int _length;
	bool _found;
	Maze::Point _start;
	Maze::Point _end;
	vector<Maze::Point> ant_memory;
	double getRandom();
	bool getWay(AntsAlgorithm::AddicionalLayers**& maze, Maze::Point previous, Maze::Point current, Maze::Point startPoint, Maze::Point direction);
public:
	Ant(int sizeMaze, Maze::Point start, Maze::Point end);
	~Ant();
	void Clear();
	vector<Maze::Point> GetWays(AntsAlgorithm::AddicionalLayers**& maze);
};

