#pragma once
#include "interface.h"
#include "MatrObj.h"

int gameConsoleBot(MatrObj& matr, const int m, int fig);
bool inputCoordOfCell(MatrObj& matr, const int m, int& x1, int& y1, const int kol, string message);