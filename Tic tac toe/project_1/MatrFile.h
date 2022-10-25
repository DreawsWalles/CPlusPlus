#pragma once

#include "workWithFile.h"

using namespace std;


class MatrFile
{
private:
	struct positions
	{
		int x1;
		int x2;
		int x3;
		int x4;
	};
	positions* _pos;
	string** _matr;
	COORD _winCombinate[5];
	int _size;
	string _filename;
public:
	MatrFile(int size);
	void setFileName(string filename);
	void printMatr();
	COORD get_coord();
	void printWinMatr();
	void update_fig();
	void checkWin(int x, int y);
};

