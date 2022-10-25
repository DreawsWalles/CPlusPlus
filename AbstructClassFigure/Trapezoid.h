#pragma once
#include "Figure.h"
//класс, который наследует класс Figure и представл€ет работу дл€ такой фигуры как “–апеци€
class Trapezoid :
    public Figure
{
public:
    Trapezoid();
    Trapezoid(int width, int length, int height);
    double Square();
    int Perimetr();
    int GetWidth();
    int GetHeight();
    void SetWidth(int width);
    void SetHeight(int height);
    int GetLength();
    void SetLength(int length);
    void Print();
    Menu* ToMenu();
    void Update(int firstParam, int secondParam = 0, int threadParam = 0);
};

