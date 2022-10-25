// zadacha_1(14).cpp
//


#include "procedure.h"

using namespace std;



int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
	bool ok = true;
	do
	{
		int num;
		inputSize(num, "Введите максимальное количество элементов в первом стеке: ");
		stack steckOne(num);
		inputSize(num, "Введите максимальное количество элементов во втором стеке: ");
		stack steckTwo(num);

		system("cls");

		while (!inputStack(steckOne, "Введите элемент для первого стека: "));
		while (!inputStack(steckTwo, "Введите элемент для второго стека: "));

		int count1 = 0, count2 = 0;
		sizeOfStack(steckOne, steckTwo, count1, count2);
		

		cout << "Количество элементов в первом стеке: " << count1 << endl;
		cout << "Количество элементов во втором стеке: " << count2 << endl;
		
		bool res = false;
		int code;
		string s;
		do
		{
			cout << "1.Запустить программу ещё раз" << endl << "2.Выход" << endl << "Введите: ";
			getline(cin, s);
			if (!(res = checkNumOfChoiсe(num, s, code, 2)))
			{
				cout << endl;
				switch (code)
				{
				case 0: cout << "Введена пустая строка" << endl;
					system("pause");
					break;
				case 1: cout << "Введен некорректный символ" << endl;
					system("pause");
					break;
				case 2: cout << "Введено некорректное число" << endl;
					system("pause");
					break;
				}
			}
		} while (!res);
		ok == 1;
	} while (!ok);
	system("pause");

	return 0;
}	

