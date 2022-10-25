#pragma once
#include "Struct.h"
class Stack :
     public Struct
{
public:
    Stack();
    void virtual push(int x) override;
    void virtual pop(int el = 0) override;
    int top();
    void virtual add(std::string s) override;
    void virtual clear();
    std::string virtual ToString();
private:
    List* _head;
};

