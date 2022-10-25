#include "functions.h"
#include "help.h"

bool inputFileName(string& name)
{
	cout << "Введите имя файла: ";
	getline(cin, name);
	int size = name.size();
	int i = 0;
	while (i < size)
	{
		if ((name[i] == '/') || (name[i] == '\\') || (name[i] == ':') || (name[i] == '*') || (name[i] == '?') || (name[i] == '«') || (name[i] == '<') || (name[i] == '>') || (name[i] == '|'))
		{
			cout << endl << "Введен некорректный символ " << name[i] << endl;
			return false;
		}
		else
			i++;
	}
	return true;
}

void InputKeyboard(Journal& list)
{
	Record e;
	cin >> e;
	list.Add(e);
}

void InputFile(Journal& list)
{
	string fileName;
	while (!inputFileName(fileName))
	{
		system("pause");
		system("cls");
	}
	list.InputFile(fileName);
}

void Add(Journal& list)
{
	menu* menu_input = new menu;
	menu_input->Add("Считать данные из файла");
	menu_input->Add("Считать данные с клавиатуры");
	cout << "Выберите действие:" << endl;
	menu_input->Print();
	int choice = menu_input->Choice("Выберите действие:");
	switch (choice)
	{
	case 1:
		InputKeyboard(list);
		break;
	case 2:
		InputFile(list);
		break;
	}
	delete menu_input;
}

int CheckChoise(string s, int borderBeg, int borderEnd)
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

void Change(Journal& list)
{
	string n;
	int choice = 0;
	int size = list.size();
	do
	{
		list.Print();
		cout << endl << "Выберите номер записи: ";
		getline(cin, n);
		choice = CheckChoise(n, 1, size);
		if (choice == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	Record e;
	cin >> e;
	if (list.Change(list.getRecord(choice - 1), e))
		cout << "Элемент успешно изменен" << endl;
	else
		cout << "Не получилось изменить элемент" << endl;
	system("pause");
}

void Delete(Journal& list)
{
	string n;
	int choice = 0;
	int size = list.size();
	do
	{
		list.Print();
		cout << endl << "Выберите номер записи: ";
		getline(cin, n);
		choice = CheckChoise(n, 1, size);
		if (choice == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	if (list.Remove(list.getRecord(choice - 1)))
		cout << "Элемент успешно удален" << endl;
	else
		cout << "Не получилось удалить элемент" << endl;
	system("pause");
}

void Print(Journal list)
{
	menu* menu_output = new menu;
	menu_output->Add("Вывести в файл");
	menu_output->Add("Вывести на экран");
	cout << "Выберите действие:" << endl;
	menu_output->Print();
	int choice = menu_output->Choice("Выберите действие:");
	system("cls");
	delete menu_output;
	switch (choice)
	{
	case 1:
	{
		string fileName;
		while (!inputFileName(fileName))
			system("pause");
		system("cls");
		list.PrintInFile(fileName);
		break;
	}
	case 2:
		list.Print();
		cout << endl;
		system("pause");
		break;
	}
	system("cls");
}

Journal Sort_course(Journal list, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "Введите курс: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 4)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToCourse, choice);
	case 2:
		return list.Search_bin(CompareToCourse, choice, CompareToCourse);
	}
}

Journal Sort_group(Journal list, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "Введите группу: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 10)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToGroup, choice);
	case 2:
		return list.Search_bin(CompareToGroup, choice, CompareToGroup);
	}
}

Journal Sort_fio(Journal list, int sort)
{
	string field;
	cout << "Введите Фамилию Имя и Отчество: ";
	getline(cin, field);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToFio, field);
	case 2:
		return list.Search_bin(CompareToFio, field, CompareToFio);
	}
}

Journal Sort_number(Journal list, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "Введите номер зачетки: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 1000000)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToNumber, choice);
	case 2:
		return list.Search_bin(CompareToNumber, choice, CompareToNumber);
	}
}

Journal Sort_discipline(Journal list, int sort)
{
	string field;
	cout << "Введите дисциплину: ";
	getline(cin, field);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToDiscipline, field);
	case 2:
		return list.Search_bin(CompareToDiscipline, field, CompareToDiscipline);
	}
}

Journal Sort_mark(Journal list, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "Введите оценку: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 5)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToMark, choice);
	case 2:
		return list.Search_bin(CompareToMark, choice, CompareToMark);
	}
}

void Search(Journal list)
{
	menu* menu_sort = new menu;
	menu_sort->Add("Обычная");
	menu_sort->Add("Бинарная");
	cout << "Выберите тип сортировки:" << endl;
	menu_sort->Print();
	int sort = menu_sort->Choice("Выберите тип сортировку:");
	system("cls");
	delete menu_sort;
	menu* menu_choice = new menu;
	menu_choice->Add("Курс");
	menu_choice->Add("Группа");
	menu_choice->Add("Фамилия Имя Отчество");
	menu_choice->Add("Номер зачетной книги");
	menu_choice->Add("Дисциплина");
	menu_choice->Add("Оценка");
	cout << "Выберите критерий для поиска" << endl;
	menu_choice->Print();
	int choice = menu_choice->Choice("Выерите критерий для поиска:");
	system("cls");
	delete menu_choice;
	Journal result;
	switch (choice)
	{
	case 1:
		result = Sort_course(list, sort);
		break;
	case 2:
		result = Sort_group(list, sort);
		break;
	case 3:
		result = Sort_fio(list, sort);
		break;
	case 4:
		result = Sort_number(list, sort);
		break;
	case 5:
		result = Sort_discipline(list, sort);
		break;
	case 6:
		result = Sort_mark(list, sort);
		break;
	}
	system("cls");
	cout << "Результат поиска: " << endl << endl;
	result.Print();
	cout << endl << endl;
	system("pause");
	system("cls");
}

int Averange_course(Journal list)
{
	string field;
	int choice;
	do
	{
		cout << "Введите курс: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 4)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	return list.AverageValue(CompareToCourse, choice, CompareToCourse);
}

int Averange_group(Journal list)
{
	string field;
	int choice;
	do
	{
		cout << "Введите группу: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 10)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	return list.AverageValue(CompareToGroup, choice, CompareToGroup);
}

int Averange_fio(Journal list)
{
	string field;
	cout << "Введите Фамилию Имя и Отчество: ";
	getline(cin, field);
	return list.AverageValue(CompareToFio, field, CompareToFio);
}

int Averange_number(Journal list)
{
	string field;
	int choice;
	do
	{
		cout << "Введите номер зачетки: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 1000000)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	return list.AverageValue(CompareToNumber, choice, CompareToNumber);
}

int Averange_discipline(Journal list)
{
	string field;
	cout << "Введите дисциплину: ";
	getline(cin, field);
	return list.AverageValue(CompareToDiscipline, field, CompareToDiscipline);
}

void AverangeValue(Journal list)
{
	menu* menu_choice = new menu;
	menu_choice->Add("Курс");
	menu_choice->Add("Группа");
	menu_choice->Add("Фамилия Имя Отчество");
	menu_choice->Add("Номер зачетной книги");
	menu_choice->Add("Дисциплина");
	cout << "Выберите критерий:" << endl;
	menu_choice->Print();
	int choice = menu_choice->Choice("Выерите критерий:");
	system("cls");
	delete menu_choice;
	int count;
	switch (choice)
	{
	case 1:
		count = Averange_course(list);
		break;
	case 2:
		count = Averange_group(list);
		break;
	case 3:
		count = Averange_fio(list);
		break;
	case 4:
		count = Averange_number(list);
		break;
	case 5:
		count = Averange_discipline(list);
		break;
	}
	system("cls");
	cout << "Средний балл по заданному критерию: " << count << endl;
	system("pause");
	system("cls");
}