#include "trie_tree.h"
trie_tree::trie_tree() {
	root = nullptr;
}
trie_tree::~trie_tree() {
	delete(root);
}

void trie_tree::Print()
{
	root->Print_Node(root, 0);
}

bool trie_tree::Add(string str) {
	bool res = false;
	if (root->CheckWord(str))
		if (root == nullptr)
		{
			root = new node();
			res = root->Add(str);
		}
		else
			res = root->Add(str);
	return res;
}
bool trie_tree::IsEmpty()
{
	return root == nullptr;
}
bool trie_tree::Delete(string str)
{
	return (root != nullptr) && (root->CheckWord(str)) && (root->Delete(str)) && (root->IsEmpty());
}
int trie_tree::getCountWordByCheck(bool check(string))
{
	int result = 0;
	list<string> _list = root->GetAllWords();
	for (list<string>::iterator it = _list.begin(); it != _list.end(); it++)
		if (check(*it))
			result++;
	return result;
}
