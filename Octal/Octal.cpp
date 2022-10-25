#include "Octal.h"

Octal::Octal()
{
	for (int i = 0; i < 100; i++)
		_number[i] = '0';
	_size = 100;
}
Octal::~Octal()
{
	_size = NULL;
}
Octal::Octal(string s)
{
		int length = s.length();
		if (length > 100)
			throw exception("Количество цифр больше 100");
		else
		{
			_size = 0;
			for (int i = 0; i < length; i++)
			{
				if ((s[i] >= '0') && (s[i] <= '7'))
				{
					_number[length - i - 1] = s[i];
					_size++;
				}
				else
					throw exception("В введенном числе обнаружены цифры, не  подходящие для восьмиричного числа");
			}
			for (int i = _size; i < 100; i++)
				_number[i] = '0';
		}
}
int Octal::getSize()
{
	return _size;
}
unsigned char Octal::getNum(int pos)
{
	return _number[pos];
}
void Octal::SetNum(int pos, unsigned char c)
{
	_number[pos] = c;
}
Octal Octal::operator+(Octal other)
{
	Octal res;
	int num;
	int a;
	int i = 0;
	while ( i < max(_size, other.getSize()))
	{
		num = (_number[i] - '0') + (other.getNum(i) - '0');
		if (num <= 7)
			res.SetNum(i, (((res.getNum(i) - '0') + num) + '0'));
		else
		{
			a = ((res.getNum(i + 1) - '0') + 1);
			res.SetNum(i, (((num % 8) + (res.getNum(i) - '0')) + '0'));
			res.SetNum(i + 1, (a + '0'));
		}
		i++;
	}
	res.setSize(i+1);
	return res;
}
Octal Octal::operator-(Octal other)
{
	Octal res;
	int a;
	int size = max(_size, other.getSize());
	unsigned char* copyNum = new  unsigned char[size];
	copyNum[size + 1] = '\0';
	for (int i = 0; i < _size; i++)
		copyNum[i] = _number[i];
	for (int i = 0; i < size; i++)
	{
		if ((copyNum[i] - '0') >= (other.getNum(i) - '0'))
			res.SetNum(i, (((copyNum[i] - '0') - (other.getNum(i) - '0')) + '0'));
		else
		{
			a = 8 + (copyNum[i] - '0') - (other.getNum(i) - '0');
			res.SetNum(i, (a + '0'));
			if ((copyNum - '0') == 0)
				copyNum[i + 1] = '7';
			else
			{
				a = (copyNum[i+1] - '0') - 1;
				copyNum[i + 1] = (a + '0');
			}
		}
	}
	res.setSize(size);
	return res;
}

Octal multiplication(Octal a, unsigned char c)
{
	Octal res;
	int num;
	int ost = 0;
	int i = 0;
	while ( i < a.getSize())
	{
		num = (a.getNum(i) - '0') * (c - '0');
		res.SetNum(i, (((num % 8) + ost) + '0'));
		ost = num / 8;
		i++;
	}
	res.SetNum(a.getSize(), (ost + '0'));
	res.setSize(i+1);
	return res;
}

void Octal::incSize()
{
	_size++;
}
void Octal::setSize(int i)
{
	_size = i;
}

Octal shift(Octal a, int pos)
{
	for (int i = a.getSize()-1; i >= pos-1; i--)
	{
		a.SetNum((i + pos), a.getNum(i));
	}
	for (int i = 0; i < pos; i++)
		a.SetNum(i, '0');
	a.setSize(a.getSize() + pos);
	return a;
}

Octal Octal::operator*(Octal other)
{
	Octal res;
	Octal a;
	int num;
	int i = 0;
	while (i < _size)
	{
		a = multiplication(other, _number[i]);
		a = shift(a, i);
		i++;
		res = res + a;
		res.setSize(a.getSize()-1);
	}
	return res;
}
bool Octal::operator<(Octal other)
{
	for (int i = 0; i < max(_size, other.getSize()); i++)
		if (_number[i] >= other.getNum(i))
			return false;
	return true;
}
bool Octal::operator>(Octal other)
{
	for (int i = 0; i < max(_size, other.getSize()); i++)
		if (_number[i] <= other.getNum(i))
			return false;
	return true;
}
bool Octal::operator==(Octal other)
{
	for (int i = 0; i < max(_size, other.getSize()); i++)
		if (_number[i] != other.getNum(i))
			return false;
	return true;
}
bool Octal::operator<=(Octal other)
{
	for (int i = 0; i < max(_size, other.getSize()); i++)
		if (_number[i] > other.getNum(i))
			return false;
	return true;
}
bool Octal::operator>=(Octal other)
{
	for (int i = 0; i < max(_size, other.getSize()); i++)
		if (_number[i] < other.getNum(i))
			return false;
	return true;
}
bool Octal::operator!=(Octal other)
{
	for (int i = 0; i < max(_size, other.getSize()); i++)
		if (_number[i] != other.getNum(i))
			return true;
	return false;
}
bool Octal::Read()
{
	string text;
	getline(cin, text);
	if (text.empty())
	{
		cout << endl << "Введена пустая строка" << endl;
		return false;
	}
	int length = text.length();
	if (length > 100)
	{
		cout << endl << "Количество цифр больше 100" << endl;
		return false;
	}
		_size = 0;
		for (int i = 0; i < length; i++)
		{
			if ((text[i] >= '0') && (text[i] <= '7'))
			{
				_number[length - i - 1] = text[i];
				_size++;
			}
			else
			{
				cout << endl << "В введенном числе обнаружен символ "<< text[i] << " , не  подходящие для восьмиричного числа" << endl;
				return false;
			}
		}
		for (int i = _size; i < 100; i++)
			_number[i] = '0';
		return true;
}
void Octal::Display()
{
	cout << ToString();
}
string Octal::ToString()
{
	string text="";
	for (int i = _size-1; i >= 0; i--)
		text += _number[i];
	return text;
}
