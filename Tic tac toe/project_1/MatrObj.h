#pragma once
// класс для создания матрицы из объектов клетка. методы: вывод максимального веса, сравнение максимального веса для крестика и для нолика, перерасчет весов при появлении новой фигуры
#include "Cell.h"
#include "countWeight.h"
#include "interface.h"
#include "CheckWin.h"

class MatrObj :
    public Cell
{
private:
    Cell** _matr;
    int _size;
    int _x, _y;
    COORD _winCombinate[5];
public:
    MatrObj(int size);
    ~MatrObj();
    bool checkWin(int x, int y);
    void printMatr();  
    void printMatrWin();
    char get_fig(int x, int y);
    COORD get_weight(); //выводит координаты точки с максимальным весом 
    void calculation(int x, int y, char fig); //считает веса для области 11*11, где x и y координаты центральной клетки, которую мы поставили
    void print_weight(char);
private:
    void setWinCell(COORD a[5]);
    void x_vs_o(); //находит максимальный вес для крестика или нолика
    void sort();
};

