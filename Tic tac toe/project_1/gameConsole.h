#pragma once

#include "interface.h"

using namespace std;

int gameConsole(string** &mass, const int m, int** &winCombinate);

bool checkDiagonal(string** mass, int x, int y,const int m, string symbol, int** &a);

bool checkHorizon(string** mass, int x, int y, const int m, string symbol, int** &a);

bool checkVertical(string** mass, int x, int y, const int m, string symbol, int** &a);