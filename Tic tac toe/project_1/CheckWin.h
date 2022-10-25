#pragma once
#include "MatrObj.h"

bool CheckWinLine(Cell** matr, int x, int y, const int dx, const int dy, COORD(&a)[5], int& count, const int m);
COORD ToCoord(const int deg);
bool CheckWin(Cell** matr, const int x, const int y, const int line, const int m, COORD(&winCombinate)[5]);