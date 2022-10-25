// BinSearch.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("input.txt");//подключения файла на ввод

//определяем структуру
struct Product {
    string name;
    int price;
    int count;
};

void input(Product products[], const int n)//ввод структуры с файла
{
    cout << "Считанные данные из файла" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Товар № " << i + 1 << ": " << endl;
        fin >> products[i].name;
        fin >> products[i].price;
        fin >> products[i].count;
        cout << "Название: " << products[i].name << endl;
        cout << "Цена: " << products[i].price << endl;
        cout << "Количество: " << products[i].count << endl;
        cout << endl << endl;
    }
}

void search(Product products[], const int n, int key)
{
    int left = 0;
    int right = n;
    bool flag = false;
    while (!flag && left <= right) {
        int mid = (left + right) / 2;
        if (products[mid].price == key) {
            cout << "Данные о продукте" << endl;
            cout << "Название: " << products[mid].name << endl;
            cout << "Количество" << products[mid].count << endl;
            flag = true;
        }
        if (products[mid].price < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

}
int main()
{
    system("chcp 65001");
    const int n = 10;
    Product products[n];
    input(products, n);
    cout << "Введите цену для поиска: ";
    int param;
    cin >> param;
    search(products, n, param);
}
