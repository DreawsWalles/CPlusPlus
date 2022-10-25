#pragma once

#include <string>
#include <iostream>

using namespace std;

class stack
{
private:
	int size;
	int n;
	string mass[1000];
public:
	stack(int count);
	bool push(string s);
	bool empty();
	string top();
	bool pop();
	void clear();
};

