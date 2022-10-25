#include "node.h"
node::node()
{
	FPoint = false;
	for (int i = 0; i < 26; i++)
	{
		Next[i] = nullptr;
	}
}
node::~node()
{
	for (int i = 0; i < 26; i++)
	{
		delete(Next[i]);
	}
}
bool node::Add(string str)
{
	char f;
	bool res;
	if (str == "")
	{
		res = true;
		FPoint = true;
	}
	else
	{
		f = str[0];
		str.erase(0, 1);
		if (Next[f - 'a'] == nullptr)
		{
			Next[f - 'a'] = new node();
			res = Next[f - 'a']->Add(str);
		}
		else
		{
			res = Next[f - 'a']->Add(str);
		}
	}
	return res;
}
bool node::Delete(string& str)
{

	bool res;
	if (str == "")
	{
		if (FPoint)
			res = true;
		else
			res = false;
		FPoint = false;
	}
	else
	{
		char f = str[0];
		str.erase(0, 1);
		res = (Next[f - 'a'] != nullptr && Next[f - 'a']->Delete(str));
		if (res && Next[f - 'a']->IsEmpty())
		{

			Next[f - 'a'] = nullptr;
			delete(Next[f - 'a']);
		}

	}
	return res;
}
bool node::IsEmpty()
{
	int i = 0;
	bool res = (!FPoint && Next[i] == nullptr);
	if (res)
		do {
			i++;
			res = Next[i] == nullptr;
		} while (res && i < 25);
	return res;
}
bool node::CheckWord(string str)
{
	int i = 0;
	while ((i < str.size()) && (str[i] >= 'a' && str[i] <= 'z'))
		i++;
	return (i == str.size() && (str[i - 1] >= 'a' && str[i - 1] <= 'z'));
}
char WhatLeter(int i)
{
	return 'a' + i;
}
void node::Print_Node(node* n, int h)
{
	if (n != nullptr)
	{
		for (int i = 0; i < 26; i++)
		{
			if (n->Next[i] != nullptr)
			{

				for (int i = 0; i < h; i++)
					cout << "\t";
				if (n->Next[i]->FPoint == 1)
					cout << WhatLeter(i) << "." << endl;
				else
					cout << WhatLeter(i) << endl;
				Print_Node(n->Next[i], h + 1);
			}

		}
		cout << endl;
	}


}
list<string> node::GetAllWords()
{
	list<string> tmp, res;
	if (FPoint)
	{
		res.push_back("");
	}
	for (int i = 0; i < 26; i++)
		if (Next[i] != nullptr)
		{
			tmp = Next[i]->GetAllWords();
			int count = tmp.size();
			for (int j = 0; j < count; j++)
			{
				res.push_back(WhatLeter(i) + tmp.back());
				tmp.pop_back();
			}

		}
	return res;

}