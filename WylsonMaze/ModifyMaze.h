#pragma once
#include "Maze.h"


class ModifyMaze : public Maze
{
private:
	void solve();
	void firstStep();
	void secondStep();
	void threeStep();
public:
	ModifyMaze(int size);
};

