#pragma once

#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <windows.h>
#include <malloc.h>
#include <conio.h>
#include <algorithm>

using namespace std;

void SetColor(const int text, const int bg);
void SetCursor(const int x, const int y);
void printMessage(string s);
int start(const int n);
bool inputNumOfChoiñe(int& num, string s, int& code);
void printDagger(int& x, int& y);
void printCell(int& x, int& y);
void printNull(int& x, int& y);
bool checkScreen(const int m, int& code);
bool checkEdge(string s, int& code, int& num);
void inputEdge(int x1, int& m);
bool checkNum(int& code, string s, int& num);
void initMass(string** mass, const int m);
int gameChoice(int x1);
void printMatr(string** mass, const int m);
int choiceDaggerNull(int x1);
bool inputCoordCell(string** mass, const int m, int& x2, int& y2, const int kol, string message);
bool getNumCell(string s, int& code, int& x, int& y, const int m);
bool checkNumCell(string s, int& code, int& i, const int m, int& k, const int len);
void print_win(int X, int Y);
void print_NULL(int X, int Y);
void print_l(int& x, int y);
void print_N(int& x, int y);
void print_dag(int& X, int Y);
void print_a(int& x, int y);
void print_g(int& x, int y);
void print_u(int& x, int y);
void print_WWCD(int X, int Y);
void print_d(int& x, int& y);
void print_k(int& x, int& y);
void print_h(int& x, int& y);
void print_c(int& x, int& y);
void print_r(int& x, int& y);
void print_e(int& x, int& y);
void print_n(int& x, int& y);
void print_I(int& x, int& y);
void print_W(int& x, int& y);
void print_WinMatr(string** mass, int** winCombinate, const int m);
void print_WinNull(int& x, int& y);
void print_WinDagger(int& x, int& y);
void print_draw(int& X, int Y);
bool repeatOrexit(const int n, int x1, int& num);