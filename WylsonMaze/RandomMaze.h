#pragma once
#include "Maze.h"

class RandomMaze : public Maze
{
private:
	MazeStruct** _mazeAdd;
	void solve();
	bool backtracking(int k, int x, int y, MazeStruct** maze);
	vector<Point> _way;
	int** _addMaze;
public:
	RandomMaze(int size);
};

