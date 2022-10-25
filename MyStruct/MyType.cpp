#include "MyType.h"

MyType::MyType()
{
	_name = "";
	_price = 0;
}
void MyType::SetPrice(const int n)
{
	_price = n;
}

void MyType::SetName(const string s)
{
	_name = s;
}

int MyType::checkOnCorrect(string s)
{
	int num;
	if (s.empty())
	{
		cout << "Введена пустая строка. Повторите ввод" << endl;
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
				if (s[i] == ' ')
					i++;
				else
				{
					cout << "Введен некорректный символ: " << s[i] << " . Повторите ввод" << endl;
					return -1;
				}
			}
		return num;
	}
}

string MyType::GetName()
{
	return _name;
}

int MyType::GetPrice()
{
	return _price;
}

ostream& operator<<(ostream& out, const MyType& ex)
{
	out << ex._name << " " << ex._price;
	return out;
}

istream& operator>>(istream& in, MyType& ex)
{
	cout << endl << "Введите наименование: ";
	getline(cin, ex._name);
	string s;
	do
	{
		cout << endl << "Введите ценник: ";
		getline(cin, s);
		if ((ex._price = ex.checkOnCorrect(s)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (ex._price == -1);
	return in;
}

bool operator==(MyType a, MyType b)
{
	return a.GetPrice() == b.GetPrice();
}
bool operator!=(MyType a, MyType b)
{
	return a.GetPrice() != b.GetPrice();
}
bool operator>(MyType a, MyType b)
{
	return a.GetPrice() > b.GetPrice();
}
bool operator<(MyType a, MyType b)
{
	return a.GetPrice() < b.GetPrice();
}