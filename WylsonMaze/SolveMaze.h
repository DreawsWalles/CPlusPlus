#pragma once
#include <vector>
#include "Maze.h"

using namespace std;
class SolveMaze
{
protected:
	Maze::MazeStruct** _maze;
	int _sizeMaze;
	const int _antCount = 200;
public:
	virtual vector<Maze::Point> GetWaysSolve(Maze* maze) = 0;
};

