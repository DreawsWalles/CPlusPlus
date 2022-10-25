#pragma once
#include"Maze.h"

class CircleMaze : public Maze
{
private:
	void solve();
public:
	CircleMaze(int size);
};

