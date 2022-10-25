#pragma once
//статический класс, который хранит в себе вспомогательные методы
static class HelpClasses
{
public:
	static int CheckChoise(string s, int borderBeg, int borderEnd)
	{
		int num;
		if (s.empty())
		{
			cout << "Считана пустая строка. Повторите ввод" << endl;
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
					cout << "Считан некорректный символ: " << s[i] << " . Повторите ввод" << endl;
					return -1;
				}
			if ((num < borderBeg) || (num > borderEnd))
			{
				cout << "Считанное значение некорректно. Значение должно быть в диапазоне от " << borderBeg << " до " << borderEnd << endl;
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
			cout << "Считана пустая строка. Повторите ввод" << endl;
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
					cout << "Считан некорректный символ: " << s[i] << " . Повторите ввод" << endl;
					return -1;
				}
			if (num < borderBeg)
			{
				cout << "Считанное значение некорректно. Значение должно быть больше " << borderBeg << endl;
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
			cout << "Считана пустая строка. Повторите ввод" << endl;
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
					cout << "Считан некорректный символ: " << s[i] << " . Повторите ввод" << endl;
					return -1;
				}
			return num;
		}
	}

};

