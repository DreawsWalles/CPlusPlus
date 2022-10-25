#pragma once

#include "MatrObj.h"

#include <string>

using namespace std;

bool checkAttackplace(const int x, const int y, const int line, const int m);
float countLine(const char fig, const int dx, const int dy, int x, int y, const int m, Cell** matr);
float countWeight(Cell** matr, const int m, const int x, const int y, const char fig);
int getEdge(const int coord, const int edge);
