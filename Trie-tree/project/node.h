#pragma once
#include <string>
#include <list>
#include <iostream>

using namespace std;

class node
{
private:
	bool FPoint; 
	node* Next[26];
public:
	node();
	~node();
	bool Add(string str);
	bool Delete(string& str);
	bool IsEmpty();
	bool CheckWord(string str);
	void Print_Node(node* node, int h);
	list<string> GetAllWords();
};

