#pragma once
#include "stack.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string.h>
#include <windows.h>

using namespace std;

bool checkNum(int& code, string s, int& num);
void inputSize(int& size, string message);
bool inputStack(stack& steck, string message);
bool checkNumOfChoiñe(int& num, string s, int& code, int rage);
void sizeOfStack(stack& steckOne, stack& steckTwo, int& count1, int& count2);