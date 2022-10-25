#pragma once
#include "Figure.h"
#include "Menu.h"

//�����, ������� ��������� ����� Figure � ������������ ������ ��� ����� ������ ��� �������������
class MyRectangle :
    public Figure
{
public:
    MyRectangle();
    MyRectangle(int height, int width);
    double Square();
    int Perimetr();
    int GetWidth();
    int GetHeight();
    void SetWidth(int width);
    void SetHeight(int height);
    void Print();
    Menu* ToMenu();
    void Update(int firstParam, int secondParam = 0, int threadParam = 0);
};

