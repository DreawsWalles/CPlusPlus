#pragma once
#include "Struct.h"
class OrderedList :
    public Struct
{
private:
    List* _head;
public:
    OrderedList();
    void virtual clear();
    std::string ToString();
    void virtual push(int x) override;
    void virtual pop(int el = 0) override;
    void virtual add(std::string s) override;
};

