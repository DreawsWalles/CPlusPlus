#pragma once
#include <string>
#include "node.h"



class trie_tree
{
private:
	node* root;
public:
	trie_tree();
	~trie_tree();
	bool Add(string str);
	bool IsEmpty();
	bool Delete(string str);
	void Print();
	int getCountWordByCheck(bool check(string));
};

