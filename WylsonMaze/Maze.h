#pragma once
#include <vector>
#include "IRepository.h"

using namespace std;

class Maze
{
public:
	struct MazeStruct
	{
		int layer_1;
		int layer_2;
	};
	enum Cell
	{
		empty = 0,
		wall = 1,
		way = 2,
		marked = 3,
		unmarked = 4,
		temporary = 5,
		inactive = 6,
		add_wall = 7,
		mark = 8
	};
	struct Point
	{
		int x;
		int y;
		bool operator==(const Point& b)
		{
			return x == b.x && y == b.y;
		}

		bool operator!= (const Point& b)
		{
			return x != b.x || y != b.y;
		}
	};
	Maze(int size);
	void Print(IRepository* repository = nullptr);
	MazeStruct** GetMaze();
	int GetSize();
	Point GetStartPoint();
	Point GetEndPoint();
	void PrintWaysSolve(vector<Point> solve, IRepository* repository = nullptr);
	void ChangeStartPoint(Point point);
	void ChangeEndPoint(Point point);
protected:
	bool check(vector<Point> vec, Point point);
	long int _count = 0;
	long int _countDefault;
	vector<Point> _cells; 
	vector<Point> _cellsDefault;
	MazeStruct** _mainMaze;
	int _size;
	Point _start;
	Point _end;
	Point pickRandom();
	Point dir(Point current, Point prev, MazeStruct** M);
	void copy(MazeStruct** src, MazeStruct** dest);
	void mazeClear(MazeStruct** maze);
	int length_1;
	int length_2;

	int p[4] = { 1, 0, -1, 0 }, z[4] = { 0, 1, 0, -1 };
	void Wilson(MazeStruct** maze);

	Point CalculationStartPoint();
	Point CalculationEndPoint();
};

