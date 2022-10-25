#pragma once
#include "Struct.h"
class Overflow :
    public Struct
{
private:
    List* _head;
public:
    Overflow();
    void virtual push(int x) override;
    void virtual pop(int el = 0) override;
    int top();
    void virtual add(std::string s) override;
    void virtual clear();
    std::string virtual ToString();
};

