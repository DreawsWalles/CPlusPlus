#pragma once
#include<iostream>
#include "Menu.h"

using namespace std;
//����������� �����, ������� ������ � ���� ��������������� ������
static class HelpClasses
{
public:
	static int CheckChoise(string s, int borderBeg, int borderEnd)
	{
		int num;
		if (s.empty())
		{
			cout << "������� ������ ������. ��������� ����" << endl;
			return -1;
		}
		else
		{
			num = 0;
			int len = s.size();
			int i = 0;
			int n;
			while (i < len)
				if ((s[i] >= '0') && (s[i] <= '9'))
				{
					n = s[i] - '0';
					num = num * 10 + n;
					i++;
				}
				else
				{
					cout << "������ ������������ ������: " << s[i] << " . ��������� ����" << endl;
					return -1;
				}
			if ((num < borderBeg) || (num > borderEnd))
			{
				cout << "��������� �������� �����������. �������� ������ ���� � ��������� �� " << borderBeg << " �� " << borderEnd << endl;
				return -1;
			}
			return num;
		}
	}

	static int CheckChoise(string s, int borderBeg)
	{
		int num;
		if (s.empty())
		{
			cout << "������� ������ ������. ��������� ����" << endl;
			return -1;
		}
		else
		{
			num = 0;
			int len = s.size();
			int i = 0;
			int n;
			while (i < len)
				if ((s[i] >= '0') && (s[i] <= '9'))
				{
					n = s[i] - '0';
					num = num * 10 + n;
					i++;
				}
				else
				{
					cout << "������ ������������ ������: " << s[i] << " . ��������� ����" << endl;
					return -1;
				}
			if (num < borderBeg)
			{
				cout << "��������� �������� �����������. �������� ������ ���� ������ " << borderBeg << endl;
				return -1;
			}
			return num;
		}
	}

	static int GetNumber(string s)
	{
		int num;
		if (s.empty())
		{
			cout << "������� ������ ������. ��������� ����" << endl;
			return -1;
		}
		else
		{
			num = 0;
			int len = s.size();
			int i = 0;
			int n;
			while (i < len)
				if ((s[i] >= '0') && (s[i] <= '9'))
				{
					n = s[i] - '0';
					num = num * 10 + n;
					i++;
				}
				else
				{
					cout << "������ ������������ ������: " << s[i] << " . ��������� ����" << endl;
					return -1;
				}
			return num;
		}
	}
	static int InputValue(string message)
	{
		int result;
		string field;
		Menu* menu = new Menu("������ ������ ��� ���?");
		menu->Add("��");
		menu->Add("���", true);
		do
		{
			cout << message << endl;
			cout << "->";
			getline(cin, field);
			if ((result = HelpClasses::CheckChoise(field, 1)) == -1)
			{
				menu->Print();
				if (menu->Choice() == 0)
				{
					delete menu;
					return -1;
				}
				system("cls");
			}
			return result;
		} while (true);
	}
};

