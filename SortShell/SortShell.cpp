// SortShell.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
using namespace std;

//функция замены значений
void Swap(double& a, double& b)
{
	double t = a;
	a = b;
	b = t;
}

void SortShell(double Array[], int n)
{
	int step = (n + 2) / 3;//Берем изначальный шаг для проверки двух значений
	while (step > 0)
	{
		for (int i = step; i < n; i++)
			for (int j = i - step; j >= 0; j -= step)
				if (Array[j] < Array[j + step])
				{
					Swap(Array[j], Array[j + step]);
				}
		if (step != 1 && step <= 3)
			step = 1;
		else
			step = (step - 1) / 3;
	}
}

ifstream fin("input.txt");//Подключение файлов
ofstream fout("output.txt");

void input(double mas[], int n)//Функция запсии в массив из файла
{
	cout << "Считанный массив:" << endl;
	for (int i = 0; i < n; i++)
	{
		fin >> mas[i];
		cout << mas[i] << " ";
	}
	cout << endl;
}

void output(double mas[], int n)
{
	fout << "Отсортированный массив:" << endl;
	cout << "Отсортированный массив:" << endl;
	for (int i = 0; i < n; i++) {
		cout << mas[i] << ' ';
		fout << mas[i] << ' ';
	}
}

int main()
{
	system("chcp 65001");
	int N;
	fin >> N;
	double Mas[N];
	input(Mas, N);

	SortShell(Mas, N);

	output(Mas, N);
	return 0;
}