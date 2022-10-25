#include "ConsoleRepository.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void ConsoleRepository::SetColor(int text, int bg)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

string ConsoleRepository::Input()
{
	string result;
	getline(cin, result);
	return result;
}

void ConsoleRepository::Output(string message)
{
	cout << message;
}

void ConsoleRepository::Output(char symbol)
{
	cout << symbol;
}

void ConsoleRepository::Clear()
{
	system("cls");
}

void ConsoleRepository::Pause()
{
	system("pause");
}
