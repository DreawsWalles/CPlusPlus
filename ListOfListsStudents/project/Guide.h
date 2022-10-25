#pragma once
#include "Journal.h"
#include <vector>

using namespace std;

class Guide :
    public Journal
{
    typedef vector<Journal> Vector;
private:
    Vector _list;
public:
    Guide()
    {

    }
    ~Guide()
    {
        _list.clear();
    }
    void Add(Record element)
    {
        Journal tmp;
        tmp.Add(element);
        Vector::iterator it = _list.begin();
        if (!Search(it, tmp))
            _list.push_back(tmp);
        else
            (*it).Add(element);
    }

    void Add(Journal element)
    {
        int size = element.size();
        for (int i = 0; i < size; i++)
            Add(element.getRecord(i));
    }

    bool Search(Vector::iterator& it, Journal element)
    {
        while (it != _list.end() && (*it).CompareTo(element) != 0)
            it++;
        if (it == _list.end())
            return false;
        else
            return true;
    }

    int size()
    {
        return _list.size();
    }

    void Print()
    {
        int i = 1;
        cout << "\tКурс\tГруппа\tФамилия Имя Отчество\tНомер заченой книги\tДисциплина\tОценка\n";
        for (Vector::iterator it = _list.begin(); it != _list.end(); it++)
        {
            cout << '\t';
            for (int i = 0; i < 86; i++)
                cout << '_';
            cout << endl;
            (*it).PrintList(i);
            i++;
        }
        cout << '\t';
        for (int i = 0; i < 86; i++)
            cout << '_';
    }

    Journal& operator[](const int index)
    {
        Vector::iterator it = _list.begin();
        int i = 0;
        while (i != index)
        {
            it++;
            i++;
        }
        return (*it);
    }

    void PrintFile(string filename)
    {
        ofstream file;
        file.open(filename);
        file << "Курс\tГруппа\tФамилия Имя Отчество\tНомер заченой книги\tДисциплина\tОценка\n";
        for (Vector::iterator it = _list.begin(); it != _list.end(); it++)
            (*it).PrintListInFile(file);
        file.close();
    }

    bool Change(Journal element, Journal change)
    {
        if (element.CompareTo(change) == 0)
            return false;
        Vector::iterator it = _list.begin();
        Search(it, element);
        (*it) = change;
        return true;
    }

    bool Remove(Journal element)
    {
        Vector::iterator it = _list.begin();
        if (!Search(it, element))
            return false;
        _list.erase(it);
        return true;
    }

    template <class T> Guide Search(int check(Record, T), T checkVar)
    {
        Guide result;
        for (Vector::iterator it = _list.begin(); it != _list.end(); it++)
            if (check((*it).getRecord(0), checkVar))
                result.Add(*it);
        return result;
    }
    Guide& operator=(Guide other)
    {
        _list.clear();
        int size = other.size();
        for (int i = 0; i < size; i++)
            Add(other[i]);
        return *this;
    }  
    Guide Search_bin(int Compare(Journal, Journal), const Record check, int CompareTo(Journal, Record))
    {
        Guide result;
        Vector new_list = _list;
        sort(new_list.begin(), new_list.end(), [&](Journal& a, Journal& b) {return Compare(a, b) == -1; });
        Vector::iterator it = lower_bound(new_list.begin(), new_list.end(), check, [&](Journal a, Record b) {return CompareTo(a, b) == -1; });
        while (it != new_list.end() && CompareTo((*it), check) == 0)
        {
            result.Add(*it);
            it++;
        }
        return result;
    }
    Guide AverangeValue(int check)
    {
        Guide result;
        int sum;
        int size;
        for (Vector::iterator it = _list.begin(); it != _list.end(); it++)
        {
            sum = 0;
            size = (*it).size();
            for (int i = 0; i < size; i++)
                sum += (*it).getRecord(i)._mark;
            if ((sum / size) == check)
                result.Add(*it);
        }
        return result;
    }
};

