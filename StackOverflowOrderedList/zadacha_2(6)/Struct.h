#pragma once
#include "List.h"
#include <string>
class Struct
{
private:
    List* _head;
    int _size;
public:
    Struct();
    void virtual push(int x) = 0;
    void virtual pop(int el = 0) = 0;
    void virtual clear() = 0;
    void virtual add(std::string s) = 0;
    std::string ToString();

};

