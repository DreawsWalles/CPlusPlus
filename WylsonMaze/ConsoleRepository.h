#pragma once
#include "IRepository.h"
class ConsoleRepository :
    public IRepository
{
public:
    string Input();
    void Output(string message);
    void Output(char symbol);
    void SetColor(int text, int bg);
    void Clear();
    void Pause();
};

