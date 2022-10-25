#pragma once
#include <string>

using namespace std;

class IRepository {
public:
	virtual string Input() = 0;
	virtual void Output(string message) = 0;
	virtual void Output(char symbol) = 0;
	virtual void SetColor(int text, int bg) = 0;
	virtual void Clear() = 0;
	virtual void Pause() = 0;
};