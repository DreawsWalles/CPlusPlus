//!!!------------------------------------------------------------------------------------
//код программы
/*Создайте файл Телефонный справочник.Выберите и занесите в отдельный файл
по заданному адресу(улица, номер дома) сведенья об абонентах, имеющих телефоны
Файл Телефонный справочник :
Структура записи :
ФИО(40 знаков)
Адрес :
	-Улица(20 знаков)
	-номер дома(4 знака);
	-Квартира(3 знака);
номер телефона(11 знаков);
Записи упорядочены по ФИО.
Спицын А.С*/



#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <malloc.h>




# define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#pragma warning(disable : 4703)
#pragma warning(disable : 4700)


struct record
{
	char fio[40];  //ФИо
	struct adess   //адрес
	{
		char street[20]; //улица
		char NumH[4];    //номер дома
		char flat[3];    //квартира
	}adress;
	char NumPh[11]; //номер телефона
};

struct list
{
	char FIO[40]; //ФИО
	int Num; //номер в бинарном файле
	struct list* next; //указатель на следующую запись
};

list* head;

//функция для окраски цвета текста
void SetColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

//очистка списка
void cleanList()
{
	list* p;
	p = (struct list*)malloc(sizeof(struct list)); //выделение памяти под один элемент списка
	while (head != NULL)
	{
		p = head; //присваение элемента списка головы
		head = head->next; // переход основного списка на следующий элемент
		free(p); //освобождение памяти
	}
}

//добавление одного элемента
struct list* addEl(int num, char FIO[40])
{
	struct list* el;
	el = (struct list*)malloc(sizeof(struct list)); //выделение памяти под элемент списка
	strcpy(el->FIO, FIO); //копирование ФИО в элемент списка
	el->Num = num; //присваение элементу списка номера
	el->next = NULL; // присваение следующему указателю NULL
	return el;
}

//создание списка и сортировка
void CreateList(int num, char FIO[40])
{
	struct list* tmp, * q, * h;
	tmp = addEl(num, FIO);
	q = (struct list*)malloc(sizeof(struct list));  // выделение памяти под элемент списка
	h = (struct list*)malloc(sizeof(struct list));
	h = head;
	int ok = 0;
	while ((ok == 0) && (h != NULL)) //идем по циклу пока не найдем элемент, который не удовлетворяет условию либо пока список не закончится
	{
		;
		if (strcmp(h->FIO, tmp->FIO) >= 0)  //условие сортировки списка
			ok = 1;
		else
		{
			q = h;
			h = h->next;
		}
	}
	tmp->next = h;

	if (h == head)
		head = tmp;
	else
		q->next = tmp;
}

//функция для удаления лишних пробелов из текста
char* trim(char* s)
{
	int len = strlen(s);
	char str[40];
	int j = 0;
	int i = 0;
	while (j < len) //находимся в цикле пока не дойдем до конца строкм
	{ //пропускаем пробелы в конце
		if (s[j] == ' ')
		{
			while (s[j] == ' ')
				j++;
		}
		//записываем введенные символы, которые не являются проблелом
		while ((s[j] != ' ') && (j < len))
		{
			str[i] = s[j];
			j++;
			i++;
		}
		str[i] = ' ';
		i++;
	} //проверка на то, что введена пустая строка
	if (i != 0)
		str[(i - 1)] = '\0';
	else 
		str[i] = '\0'; //ставим символ конец строки в конец строки
	return str;	
}

void EditRecord(char *name, int &cnt_rec);
void CreateRecord(char *name, int &cnt_rec);
void DeleteRecord(char *name, int &cnt_rec);
void PrintRecords(char *name, int &cnt_rec);
void MainTask(char *name, int cnt_rec);
void PrintMessage(const char* s);
int menuChoise(const char* s1);
void Download();
void Hellow(char *name);
void InputFile(char *name, int& cnt_rec);
void MenuOne(char *name, int& cnt_rec);
void MenuTwo(char *name, int& cnt_rec);
void PrintRecords(char* name, int& cnt_rec);

//функции проверки имени файла
int CheckNameFile(char* name)
{
	int code = 0;
	int len = strlen(name);
	int i = 0;
	while ((code == 0) && (i < len)) //идем по циклу пока не найдем некорретный эдемент либо пока не закончится строка
	{   //проверка на корректный символ
		if ((name[i] == '+') || (name[i] == '=') || (name[i] == '[') || (name[i] == ']') || (name[i] == ':') || (name[i] == '#') || (name[i] == '%') || (name[i] == '{') || (name[i] == '}') ||
			(name[i] == '<') || (name[i] == '>') || (name[i] == '*') || (name[i] == '?') || (name[i] == '/') || (name[i] == ' ') || (name[i] == '$') || (name[i] == '!') || (name[i] == '`') ||
			(name[i] == '"') || (name[i] == '@') || (name[i] == '|'))
		{
			//вывод ошибки
			code = 1;
			while (getchar() != '\n');
			printf("\n");
			SetColor(14, 0);
			printf("                              ");
			PrintMessage("При вводе имени файла обнаружен некорректный символ ");
			SetColor(12, 0);
			printf("%c", name[i]);
			printf("\n");
			SetColor(10, 0);
			printf("                                              ");
			PrintMessage("Повторите ввод: ");
			
		}
		i++;
	}
	return code;
}

//функции анимации печати 
void PrintMessage(const char* s)
{
	int len = strlen(s);
	for (int j = 0; j < len; j++)
	{
		printf("%c", s[j]);
		if (s[j] != ' ')
			Sleep(15 + rand() % 30); //Sleep(60 + rand() % 90);
		else
			Sleep(60 + rand() % 90); //Sleep(150 + rand() % 270);
	}
}

//меню выбора да / нет 
int menuChoise(const char* s1)
{
	//вывод сообщения
	PrintMessage(s1);
	printf("\n");
	printf("                                                    ");
	SetColor(12, 0);
	PrintMessage("Y");
	SetColor(10, 0);
	PrintMessage("-да, ");
	SetColor(12, 0);
	PrintMessage("N");
	SetColor(10, 0);
	PrintMessage("-нет");
	printf("\n");
	int ok = 0;
	char c;
	while (getchar() != '\n');
	do
	{
		//проверка на корректность введенного символа
		printf("                                              ");
		PrintMessage("Введите: ");
		SetColor(2, 0);
		scanf("%c", &c);
		if ((c == 'y') || (c == 'Y') || (c == 'н') || (c == 'Н') || (c == 'N') || (c == 'n') || (c == 'т') || (c == 'Т'))
		{
			ok = 0;
			if ((c == 'y') || (c == 'Y') || (c == 'н') || (c == 'Н'))
				return 1;
			else
				return 0;
		}
		else
		{
			//вывод ошибки
			SetColor(10, 0);
			ok = 1;
			while (getchar() != '\n');
			printf("                                           ");
			PrintMessage("Введен корректный символ");
			printf("\n");
		}
	} while (ok == 1);
}

// меню анимации Download 
void Download()
{
	SetColor(11, 0);
	printf("                          ");
	printf("--------------------------------------------------------------\n");
	printf("                          ");
	SetColor(13, 0);
	printf("**************************************************************");
	SetColor(11, 0);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                            ");
	SetColor(10, 0);
	printf("Идет подключение файла... ");
	printf("\n");
	printf("                                                   ");
	printf("Download");
	SetColor(12, 0);
	printf(".");
	Sleep(200);
	printf(".");
	Sleep(200);
	printf(".");
	Sleep(200);
}

//приветсвенное меню 
void Hellow(char *name)
{
	//приветственное слово
	SetColor(11, 0);
	printf("                          ");
	printf("--------------------------------------------------------------\n");
	printf("                          ");
	SetColor(13, 0);
	printf("**************************************************************");
	SetColor(11, 0);
	printf("\n");
	printf("\n");
	printf("                                              ");
	Sleep(100);
	SetColor(10, 0);
	PrintMessage("Доброго времени суток");
	printf("\n");
	printf("                                            ");
	Sleep(1000);
	PrintMessage("Вас приветсвует программа");
	Sleep(100);
	printf("\n");
	printf("                                                   ");
	SetColor(12, 0);
	PrintMessage("Course Work");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                     ");
	Sleep(2000);
	SetColor(10, 0);
	PrintMessage("Для работы программы необходим бинарный файл");
	printf("\n");
	printf("                                 ");
	Sleep(1000);
	SetColor(12, 0);
	//печать меню для выбора что делать с именем бинарног основного файла
	PrintMessage("--1.");
	SetColor(10, 0);
	PrintMessage(" Ввести имя файла");
	printf("\n");
	printf("                                 ");
	SetColor(12, 0);
	PrintMessage("--2.");
	SetColor(10, 0);
	PrintMessage(" Оставить имя файла по умолчанию");
	SetColor(12, 0);
	PrintMessage(" (InputData)");
	printf("\n");
	int i;
	int ok;
	do
	{
		//проверка на корректно введенный символ
		SetColor(10, 0);
		printf("                                 ");
		PrintMessage("Введите: ");
		char c;
		SetColor(2, 0);
		scanf("%c", &c);
		if ((c == '1') || (c == '2'))
		{
			ok = 0;
			if (c == '1')
				i = 1;
			else
				i = 2;
		}
		else
		{
			//вывод ошибки 
			ok = 1;
			while (getchar() != '\n');
			printf("                                 ");
			SetColor(14, 0);
			PrintMessage("Введены некорректные данные");
			printf("\n");
		}
	} while (ok == 1);
	FILE* F;
	if (i == 1)
	{
		//ввод имени файла в случае, если пользователь захотел ввести свое имя
		system("cls");
		SetColor(11, 0);
		printf("                          ");
		printf("--------------------------------------------------------------\n");
		printf("                          ");
		SetColor(13, 0);
		printf("**************************************************************");
		SetColor(11, 0);
		printf("\n");
		printf("\n");
		do
		{	
			//проверка на корректный символ 
			SetColor(10, 0);
			printf("                                              ");
			PrintMessage("Введите имя файла: ");
			do
			{
				SetColor(2, 0);
				scanf("%s", name);
				ok = CheckNameFile(name); //проверка на коректное имя файла
				if ((strcmp("InputFile", name) == 0) || (strcmp("InputData(sort)", name) == 0)) //проверка на то, что пользователь не ввел некорректный символ
				{
					//вывод ошибки
					ok = 1;
					SetColor(14, 0);
					printf("                                          ");
					PrintMessage("Файл с данным именем относится к служебным");
					printf("\n");
					printf("                                          ");
					PrintMessage("Служебные имена: InputData(sort), InputFile");
				}
			} while (ok == 1);
			//проверка на существование файла с введенным именем
			F = fopen(name, "rb+");
			if (F == NULL)
			{
				ok = 1;
			}
			else
			{
				//вывод ошибки
				SetColor(14, 0);
				printf("                                          ");
				PrintMessage("Файл с таким именем уже существует");
				printf("\n");
				ok = 1;
				printf("                                            ");
				i = menuChoise("Стереть все данные из файла?");
				if (i == 0)
					ok = 0;
				fclose(F);
			}
		} while (ok == 0);
		F = fopen(name, "wb+");
		fclose(F);
	}
	else
	{
		//созданние файла с InputData  в случае если пользователь выбрать имя по умолчаниюы
		F = fopen(name, "wb+");
		fclose(F);
	}
	system("cls");
	//анимация создания файла
	for (int k = 0; k < 3; k++)
	{
		Download();
		Sleep(200);
		system("cls");
	}
	Download();
	Sleep(200);
	printf("\n");
	printf("                                             ");
	PrintMessage("Файл успешно подключен");
	printf("\n");
	Sleep(3000);
	char c;
	scanf("%c", &c);
	system("cls");
}

//печать информации для ввода из текстового файла 
void Info()
{
	system("cls");
	SetColor(11, 0);
	printf("  ||-----------------------------------------------------------------------------------------------------------------||");
	printf("\n");
	printf("    |");
	SetColor(13, 0);
	printf("|*************************************************************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                              ");
	SetColor(10, 0);
	PrintMessage("Вы выбрали метод ввода информации считывание из файла");
	printf("\n");
	printf("            ");
	PrintMessage("При выборе файла вы должны учитывать, что данные должны соответсвовать следующей структуре");
	Sleep(500);
	printf("\n");
	printf("\n");
	printf("                           ");
	SetColor(11, 0);
	printf("**************************************************************");
	printf("\n");
	SetColor(14, 0);
	printf("                                              ");
	PrintMessage("ФИО(40 знаков)");
	printf("\n");
	printf("\n");
	printf("                                              ");
	PrintMessage("Адрес :");
	printf("\n");
	printf("\n");
	printf("                                                ");
	PrintMessage("-Улица(20 знаков)");
	printf("\n");
	printf("\n");
	printf("                                                ");
	PrintMessage("-номер дома(4 знака)");
	printf("\n");
	printf("\n");
	printf("                                                ");
	PrintMessage("-Квартира(3 знака)");
	printf("\n");
	printf("\n");
	printf("                                             ");
	PrintMessage("номер телефона(11 знаков)");
	printf("\n");
	Sleep(500);
	SetColor(11, 0);
	printf("                           ");
	printf("**************************************************************");
	printf("\n");
	printf("\n");
	printf("                                 ");
	SetColor(10, 0);
	PrintMessage("Необходимо помнить, что после каждой структурированной");
	printf("\n");
	printf("                              ");
	PrintMessage("записи об абоненте необходимо оставить одну свободную строчку");
	Sleep(500);
	printf("\n");
	printf("\n");
	SetColor(11, 0);
	printf("                    ");
	printf("|");
	SetColor(13, 0);
	printf("|*******************************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                  ");
	printf("||-----------------------------------------------------------------------------------||");
	printf("\n");
	Sleep(1000);  
	printf("                  ");
	SetColor(10, 0);
	PrintMessage("Для продолжения нажмите ");
	SetColor(12, 0);
	printf("ENTER");
	SetColor(10, 0);
	printf("...");
	char c;
	SetColor(2, 0);
	scanf("%c", &c);
	scanf("%c", &c);
	system("cls");
}

//проверка записи( была ли ранее уже введена такая запись)
int CheckRecord(char* name, int cnt_rec, struct record rec1)
{
	FILE* F = fopen(name, "rb");
	struct record rec;
	int ok = 0, i = 0;
	while ((i < cnt_rec) && (ok == 0 )) //находися в цикле пока не дойдем до конца файла или не найдем совпадение по записи
	{
		fread(&rec, sizeof(struct record), 1, F);//считывание записи из файла
		ok = (!strcmp(rec1.fio, rec.fio) && !strcmp(rec1.adress.street, rec.adress.street)
			&& !strcmp(rec1.adress.NumH, rec.adress.NumH) && !strcmp(rec1.adress.flat, rec.adress.flat) && !strcmp(rec1.NumPh, rec.NumPh)); //проверка записи
		i++;
	}
	fclose(F);
	return ok;
}

//функция подключения текстового файла 
char* ConectTextFile(char *s, int &cnt_rec)
{
	system("cls");
	char* name = new char;
	printf("                     ");//печать интерфейса
	SetColor(11, 0);
	printf("||--------------------------------------------------------------------||");
	printf("\n");
	printf("                       ");
	printf("|");
	SetColor(13, 0);
	printf("|****************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	SetColor(13, 0);
	printf("                               ");
	PrintMessage("* * * * * *");
	SetColor(10, 0);
	PrintMessage("Подключение текстового файла");
	SetColor(13, 0);
	PrintMessage("* * * * * *");
	printf("\n");
	printf("\n");
	SetColor(10, 0);
	printf("                                          ");
	PrintMessage("Введите имя текстовго файла: ");
	int code = 0;
	do
	{
		//ввод имени текстового файла
		SetColor(2, 0);
		scanf("%s", name);
		int len = strlen(name);
		int i = 0;
		while ((i < len) && (code == 0)) //находимся в цикле пока не встретим некорректный символ или пока не закончится строка
		{
			if ((name[i] == '+') || (name[i] == '=') || (name[i] == '[') || (name[i] == ']') || (name[i] == ':') || (name[i] == '#') || (name[i] == '%') || (name[i] == '{') || (name[i] == '}') ||
				(name[i] == '<') || (name[i] == '>') || (name[i] == '*') || (name[i] == '?') || (name[i] == '/') || (name[i] == ' ') || (name[i] == '$') || (name[i] == '!') || (name[i] == '`') ||
				(name[i] == '"') || (name[i] == '@') || (name[i] == '|'))
			{
				//ввод ошибки
				code = 1;
				while (getchar() != '\n');
				printf("\n");
				printf("                              ");
				SetColor(14, 0);
				PrintMessage("При вводе имени файла обнаружен некорректный символ ");
				printf("%c", name[i]);
				printf("\n");
				SetColor(10, 0);
				printf("                                          ");
				PrintMessage("Повторите ввод: ");
			}
			i++;
		}
		if ((strcmp("Output", name) == 0) || (strcmp("Output.txt", name) == 0)) //проверка на то, что пользователь не ввел служебное имя файла 
		{
			printf("\n");
			printf("                              ");
			SetColor(14, 0);
			PrintMessage("Данное имя файла относится к служебным");
		}
	} while (code !=0);
	int len = strlen(name); 
	//проверка на то, что пользователь добавил расширение 'txt' // если пользователь не добавил расширение добавляем сами 
	if ((name[len - 4] != '.') && ((name[len - 3] != 't') || (name[len - 3] != 'T')) && ((name[len - 2] != 'x') || (name[len - 2] != 'X')) && ((name[len - 1] != 't') || (name[len - 3] != 'T')))
	{
		const char *s1 = ".txt";
		strcat(name, s1);
	}
	FILE* F = fopen(name, "rt+"); //проверяем на существование файла 
	if (F == NULL)                // в случае, если файл не обнаружен предлагаем либо ввести ещё раз, либо опменять формат добавления записи либо озврат к меню
	{
		char c;
		int i;
		scanf("%c", &c);
		printf("\n");
		SetColor(14, 0);
		printf("                                          ");
		PrintMessage("Файл с таким именем не обнаружен");
		printf("\n");
		SetColor(12, 0);
		printf("                                      ");
		PrintMessage("--1.");
		SetColor(10, 0);
		PrintMessage("Ввести другое имя файла ");
		printf("\n");
		SetColor(12, 0);
		printf("                                      ");
		PrintMessage("--2.");
		SetColor(10, 0);
		PrintMessage("Поменять формат ввода");
		printf("\n");
		SetColor(12, 0);
		printf("                                      ");
		PrintMessage("--3."); 
		SetColor(10, 0);
		PrintMessage("Вернутся в меню");
		int ok = 0;
		do
		{
			//проверка на корректный символ при вводе
			SetColor(10, 0);
			printf("\n");
			printf("                                          ");
			PrintMessage("Введите: ");
			SetColor(2, 0);
			scanf("%c", &c);
			if ((c == '1') || (c == '2') || (c == '3'))
			{
				if (c == '1')
					i = 1;
				else
					if (c == '2')
						i = 2;
					else
						i = 3;
			}
			else
			{
				//печать ошибки
				ok = 1;
				if (c != '\n')
					while (getchar() != '\n');
				printf("\n");
				SetColor(14, 0);
				printf("                                          ");
				PrintMessage("Введены некорректные данные");
			}
		} while (ok == 1);
		switch (i)
		{
		case 1:
			InputFile(s, cnt_rec);
			break;
		case 2: 
			CreateRecord(s, cnt_rec);
			break;
		case 3:
			if (cnt_rec == 0)
				MenuOne(s, cnt_rec);
			else
				MenuTwo(s, cnt_rec);
			break;

		}
	}
	else
	{
		//анимация подключения файла в случае если файл обнаружен
		printf("\n");
		printf("\n");
		printf("\n");
		SetColor(11, 0);
		printf("                       ");
		printf("|");
		SetColor(13, 0);
		printf("|****************************************************************|");
		SetColor(11, 0);
		printf("| ");
		printf("\n");
		printf("                     ");
		SetColor(11, 0);
		printf("||--------------------------------------------------------------------||");
		printf("\n");
		SetColor(10, 0);
		printf("                                                  ");
		PrintMessage("Подключение файла");
		printf("\n");
		printf("                                                    ");
		PrintMessage("Connection");
		Sleep(700);
		SetColor(12, 0);
		printf(".");
		Sleep(700);
		printf(".");
		Sleep(700);
		printf(".");
		Sleep(700);
		printf(".");
		Sleep(700);
		printf(".");
		Sleep(700);
		printf(".");
		Sleep(1000);
		printf("\n");
		printf("                                                      ");
		PrintMessage("Success");
		Sleep(1000);
		fclose(F);
		return name;
	}
	while (getchar() != '\n');
	system("cls");
} 

//печать заголовка для вывода на экран всех записей 
void PrintHeader()
{
	printf(" ");
	SetColor(11,0);
	for (int i = 0; i < 116; i++)
	{
		printf("_");
	}
	printf("\n");
	printf(" ");
	printf("||");
	printf("  ");
	printf(" ");
	printf("||");
	for (int i = 0; i < 44; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 24; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 15; i++)
	{
		printf(" ");
	}
	printf("||");
	printf("\n");
	printf(" ");
	printf("||");
	printf(" ");
	SetColor(14, 0);
	printf("№");
	printf(" ");
	SetColor(11, 0);
	printf("||");
	for (int i = 0; i < 11; i++)
	{
		printf(" ");
	}
	SetColor(14, 0);
	printf("Фамилия Имя и Отчество");
	for (int i = 0; i < 11; i++)
	{
		printf(" ");
	}
	SetColor(11, 0);
	printf("||");
	for (int i = 0; i < 10; i++)
	{
		printf(" ");
	}
	SetColor(14, 0);
	printf("Улица");
	for (int i = 0; i < 9; i++)
	{
		printf(" ");
	}
	SetColor(11, 0);
	printf("||");
	printf("  ");
	SetColor(14, 0);
	printf("Дом");
	printf("   ");
	SetColor(11, 0);;
	printf("||");
	SetColor(14, 0);
	printf("Квартира");
	SetColor(11, 0);
	printf("||");
	SetColor(14, 0);
	printf(" Номер телефона");
	SetColor(11, 0);
	printf("||");
	printf("\n");
	printf(" ");
	printf("||");
	printf("   ");
	printf("||");
	for (int i = 0; i < 44; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 24; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 15; i++)
	{
		printf(" ");
	}
	printf("||");
	printf("\n");
	printf(" ");
	printf("||");
	printf("===");
	printf("||");
	for (int i = 0; i < 107; i++)
	{
		printf("=");
	}
	printf("||");
}

//печать одной записи 
void PrintOneRecord(struct record rec, int N)
{
	int len;
	SetColor(11, 0);
	printf("\n");
	printf(" ");
	printf("||");
	printf("   ");
	printf("||");
	for (int i = 0; i < 44; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 24; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 15; i++)
	{
		printf(" ");
	}
	printf("||");
	printf("\n");
	printf(" ");
	printf("||");
	printf(" ");
	SetColor(14, 0);
	printf("%d", N);
	SetColor(11, 0);
	printf(" ");
	printf("||");


	SetColor(10, 0);
	len = strlen(rec.fio);
	int b;
	int a = 44 - len;
	if ((a % 2) == 0)
	{
		b = a / 2;
		for (int i = 0; i < b; i++)
			printf(" ");

		printf("%s", rec.fio);
			
		for (int i = 0; i < b; i++)
			printf(" ");
	}
	else
	{
		b = (a - 1) / 2;
		for (int i = 0; i < b + 1; i++)
			printf(" ");
		
		printf("%s", rec.fio);

		for (int i = 0; i < b; i++)
			printf(" ");
	}
	SetColor(11, 0);
	printf("||");


	SetColor(10, 0);
	len = strlen(rec.adress.street);
	a = 24 - len;
	if ((a % 2) == 0)
	{
		b = a / 2;
		for (int i = 0; i < b; i++)
			printf(" ");

		printf("%s", rec.adress.street);
		
		for (int i = 0; i < b; i++)
			printf(" ");
	}
	else
	{
		b = (a - 1) / 2;
		for (int i = 0; i < b + 1; i++)
			printf(" ");
		
		printf("%s", rec.adress.street);

		for (int i = 0; i < b; i++)
			printf(" ");
	}
	SetColor(11, 0);
	printf("||");



	SetColor(10, 0);
	len = strlen(rec.adress.NumH);
	a = 8 - len;
	if ((a % 2) == 0)
	{
		b = a / 2;
		for (int i = 0; i < b; i++)
			printf(" ");
	
		printf("%s", rec.adress.NumH);

		for (int i = 0; i < b; i++)
			printf(" ");
	}
	else
	{
		b = (a - 1) / 2;
		for (int i = 0; i < b + 1; i++)
			printf(" ");

		printf("%s", rec.adress.NumH);

		for (int i = 0; i < b; i++)
			printf(" ");
	}
	SetColor(11, 0);
	printf("||");


	SetColor(10, 0);
	len = strlen(rec.adress.flat);
	a = 8 - len;
	if ((a % 2) == 0)
	{
		b = a / 2;
		for (int i = 0; i < b; i++)
			printf(" ");

		printf("%s", rec.adress.flat);

		for (int i = 0; i < b; i++)
			printf(" ");
	}
	else
	{
		b = (a - 1) / 2;
		for (int i = 0; i < b + 1; i++)
			printf(" ");
		
		printf("%s", rec.adress.flat);

		for (int i = 0; i < b; i++)
			printf(" ");
	}
	SetColor(11, 0);
	printf("||");


	SetColor(10, 0);
	len = strlen(rec.NumPh);
	a = 15 - len;
	if ((a % 2) == 0)
	{
		b = a / 2;
		for (int i = 0; i < b; i++)
			printf(" ");

		printf("%s", rec.NumPh);
		
		for (int i = 0; i < b; i++)
			printf(" ");
	}
	else
	{
		b = (a - 1) / 2;
		for (int i = 0; i < b + 1; i++)
			printf(" ");
		
		printf("%s", rec.NumPh);
			
		for (int i = 0; i < b; i++)
			printf(" ");
	}
	SetColor(11, 0);
	printf("||");
	printf("\n");


	printf(" ");
	printf("||");
	printf("   ");
	printf("||");
	for (int i = 0; i < 44; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 24; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 8; i++)
	{
		printf(" ");
	}
	printf("||");
	for (int i = 0; i < 15; i++)
	{
		printf(" ");
	}
	printf("||");
	printf("\n");
	printf(" ");
	printf("||");
	printf("===");
	printf("||");
	for (int i = 0; i < 107; i++)
	{
		printf("=");
	}
	printf("||");
}

//проверка номера телефона на корректный ввод 
int checkNumPh(char *s, char &c)
{
	int j = 0;
	int code = 0;
	int len = strlen(s);
	if (len > 11) //проверка на то, что ввели слишком большую строку
		code = 3;
	else
		if (s[0] == '\0') //проверка на то, что пользователь не ввел пустую строку
			code = 4;
		else //находимся в цикле пока не найден не корректный символ, лиюо пока не дойдем до конца строки либо если обнаружим, что введеная строка юбольше необходимой
			while ((code == 0) && (j < 12) && (j<len))
			{
				if (((s[j] >= '0') && (s[j] <= '9')) || (s[j] == ' ') || (s[j] == '\n') || (s[j] == '-') || (s[j] == '+'))
				{
					j++;
				}
				else
				{
					code = 1;
					c = s[j];
				}
			}
	return code;
}

//проверка квартиры на корректный ввод 
int checkFlat(char *s, char &c)
{
	int code = 0;
	int j = 0;
	int len = strlen(s);
	if (len > 3) //проверка на то, что ввели слишком большую строку
		code = 3;
	else
		if (s[0] == '\0') //проверка на то, что пользователь не ввел пустую строку
			code = 4;
		else
		{    //находимся в цикле пока не найден не корректный символ, лиюо пока не дойдем до конца строки либо если обнаружим, что введеная строка юбольше необходимой
			while ((j<3) && (code == 0) && (j<len))
			{
				if (((s[j] >= '0') && (s[j] <= '9')) || (s[j] == ' ') || (s[j] == '\n'))
				{
					j++;
				}
				else
				{
					code = 1;
					c = s[j];
				}
			}
		}
	return code;
}

//проверка для улицы и ФИО на ввод букв; так же проверяется на ввод в одно поле символов из разных алфавитов 
int check(char &c, int &cnt_rus, int &cnt_eng)
{
	int code = 0;
	if ((c == ' ') || (c == '\0'))
		code = 0;
	else
		if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) //проверка что ввели английский символ
		{
			code = 0;
			cnt_eng++;
		}
		else
			if (((c >= 'А') && (c <= 'Я')) || ((c >= 'а') && (c <= 'я')))  //проверка на то, что ввели русский символ
			{
				code = 0;
				cnt_rus++;
			}
			else
				code = 1;
	if ((cnt_rus>0) && (cnt_eng>0)) //проверка на то, если введены символы из разных алфавитов
		code = 2;
	return code;
}

//проверка улицы на корректный ввод 
int checkStreet(char *s, char &c)
{
	int code = 0;
	int j = 0;
	int len = strlen(s);
	int cnt_rus = 0;
	int cnt_eng = 0;
	if (len > 20) //проверка на то, что ввели слишком большую строку
		code = 3;
	else
		if (s[0] == '\0')//проверка на то, что пользователь не ввел пустую строку
			code = 4;
		else
		{   //находимся в цикле пока не найден не корректный символ, лиюо пока не дойдем до конца строки либо если обнаружим, что введеная строка юбольше необходимой
			while ((j<len) && (code == 0) && (j < 20))
			{
				if ((code = check(c, cnt_rus, cnt_eng)) == 0)
					j++;
				else
					c = s[j];
			}
		}
	return code;
}

//1-При вводе обнаружен некорректный символ
//2-Если при вводе обнаружены символы из разных алфавитов
//3-ввели слишком много буковок
//4-введена пустая строка
//5- слишком много слов
//6-Запись не может быть добавлена т.к. обнаружен пробел между числами
//7- Запись не может быть добавлена, т.к. обнаружен некорректный символ
//8- Введено отрицательное число
//9-Введенное число. которое больше количества записей
//10- Введена пустая строка
//печать ошибки при вводе с клавиатуры; печать ошибок при добавлении в файл запись 
void PrintError(int i, char c, const int &l)
{
	switch (i)
	{
	case 1:
		SetColor(14, 0);
		printf("                                 ");
		PrintMessage("При вводе обнаружен некорректный символ: ");
		SetColor(12, 0);
		printf("%c", c);
		SetColor(10, 0);
		printf("\n");
		break;
	case 2:
		SetColor(14, 0);
		printf("                                ");
		PrintMessage("При вводе обнаружены символы из разных алфавитов");
		printf("\n");
		break;
	case 3:
		SetColor(14, 0);
		printf("                                ");
		PrintMessage("При вводе привышен лимит количества символов(допустимая норма: ");
		SetColor(12, 0);
		printf("%d", l);
		SetColor(10, 0);
		printf("\n");
		break;
	case 4:
		SetColor(14, 0);
		printf("                                ");
		PrintMessage("Введена пустая строка");
		printf("\n");
		break;
	case 5:
		SetColor(14, 0);
		printf("                                ");
		PrintMessage("При вводе было введено больше 3 слов)");
		printf("\n");
		break;
	case 6:
		SetColor(14, 0);
		printf("\n");
		printf("                     ");
		PrintMessage("Запись не может быть добавлена т.к. обнаружен пробел между числами");
		break;
	case 7:
		SetColor(14, 0);
		printf("\n");
		printf("                    ");
		PrintMessage("Запись не может быть добавлена, т.к. обнаружен некорректный символ: ");
		SetColor(12, 0);
		printf("%c", c);
		break;
	case 8:
		SetColor(14, 0);
		printf("\n");
		printf("                    ");
		PrintMessage("Введено отрицательное число");
		break;
	case 9:
		SetColor(14, 0);
		printf("\n");
		printf("                    ");
		PrintMessage("Введенное число. которое больше количества записей");
		break;
	case 10:
		SetColor(14, 0);
		printf("\n");
		printf("                    ");
		PrintMessage("Введена пустая строка");
		break;
	}
}

//-10 - При считывании данных с файла не обнаружено ни одной записи
//10- При считывании данных с файла обнаружен некорректный символ
//20- При считывании данных с файла обнаружены символы из разных алфавитов
//30-при считывании данных из файла строке привышен лимит количества символов(допустимая норма)
//40- при считывании данных из файла строчка является пустой
//50- при считывании данных из файла было считано больше 3 слов
//печать ошибок при вводе из файле 
void PrintErrorFile(int i, char c, const int& l, int j, int Nums)
{
	system("cls");
	printf("            ");
	SetColor(11, 0);
	printf("||---------------------------------------------------------------------------------------------||");
	printf("\n");
	printf("            ");
	printf("  |");
	SetColor(13, 0);
	printf("|*****************************************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                                       ");
	SetColor(13, 0);
	PrintMessage("* * * * * *");
	SetColor(10, 0);
	PrintMessage("Возникла ошибка");
	SetColor(13, 0);
	PrintMessage("* * * * * *");
	printf("\n");
	printf("                                       ");
	Sleep(400);
	SetColor(13, 0);
	printf("---------------------------------------");
	printf("\n");
	printf("\n");
	switch (i)
	{
	case -10:
		SetColor(14, 0);
		printf("                                    ");
		PrintMessage("При считывании данных с файла не обнаружено ни одной записи ");
		break;
	case 10:
		SetColor(14, 0);
		printf("                                    ");
		PrintMessage("При считывании данных с файла в ");
		SetColor(12, 0);
		printf("%d", j);
		SetColor(14, 0);
		PrintMessage(" записе в ");
		SetColor(12, 0);
		printf("%d", Nums);
		printf("\n");
		printf("                                    ");
		SetColor(14, 0);
		PrintMessage("строчке обнаружен некорректный символ ");
		SetColor(12, 0);
		printf("%c", c);
		printf("\n");
		break;
	case 20:
		SetColor(14, 0);
		printf("                                    ");
		PrintMessage("При считывании данных с файла в ");
		SetColor(12, 0);
		printf("%d", j);
		SetColor(14, 0);
		PrintMessage(" записе в ");
		SetColor(12, 0);
		printf("%d", Nums);
		printf("\n");
		printf("                                    ");
		SetColor(14, 0);
		PrintMessage("строке обнаружены символы из разных алфавитов");
		printf("\n");
		break;
	case 30:
		SetColor(14, 0);
		printf("                                    ");
		PrintMessage("При считывании данных с файла в ");
		SetColor(12, 0);
		printf("%d", j);
		PrintMessage(" записе в ");
		SetColor(14, 0);
		printf("%d", Nums);
		SetColor(12, 0);
		printf("\n");
		printf("                              ");
		SetColor(14, 0);
		PrintMessage("строке привышен лимит количества символов(допустимая норма: ");
		SetColor(12, 0);
		printf("%d", l);
		printf(")\n");
		break;
	case 40:
		SetColor(14, 0);
		printf("                          ");
		PrintMessage("При считывании данных с файла в ");
		SetColor(12, 0);
		printf("%d", j);
		SetColor(14, 0);
		PrintMessage(" записе строчка ");
		SetColor(12, 0);
		printf("%d", Nums);
		SetColor(14, 0);
		PrintMessage(" является пустой");
		printf("\n");
		break;
	case 50:
		SetColor(14, 0);
		printf("                                    ");
		PrintMessage("При считывании данных с файла в ");
		SetColor(12, 0);
		printf("%d", j);
		SetColor(14, 0);
		PrintMessage(" записе в ");
		SetColor(12, 0);
		printf("%d", Nums);
		printf("\n");
		printf("                                         ");
		SetColor(14, 0);
		PrintMessage("строчке было считано больше 3 слов");
		printf("\n");
		break;
	}

}

//меню, которое вызывается при подключении текстового файла 
void MenuTextFile(char *name, int& cnt_rec)
{
	//печать интерфейса
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(600);
	printf("                             ");
	SetColor(11, 0);
	printf("||********************************************************||");
	printf("\n");
	printf("                           ");
	SetColor(11, 0);
	printf("|");
	SetColor(13, 0);
	printf("|----------------------------------------------------------|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                                       ");
	SetColor(12, 0);
	PrintMessage("--1.");
	SetColor(10, 0);
	PrintMessage("Считать информацию с другого файла");
	printf("\n");
	printf("                                       ");
	SetColor(12, 0);
	PrintMessage("--2.");
	SetColor(10, 0);
	PrintMessage("Выбрать другой формат ввода");
	printf("\n");
	printf("                                       ");
	SetColor(12, 0);
	PrintMessage("--3.");
	SetColor(10, 0);
	PrintMessage("Вернутся в меню");
	printf("\n");
	printf("                                  ");
	SetColor(11, 0);
	printf("||*****************************************||");
	printf("\n");
	char c;
	int ok = 0;
	int i;
	do
	{ //проверка на корректный ввод символа
		SetColor(10, 0);
		printf("                                    ");
		PrintMessage("Введите: ");
		SetColor(2, 0);
		scanf("%c", &c);
		if ((c == '1') || (c == '2') || (c == '3'))
		{
			ok = 0;
			if (c == '1')
				i = 1;
			else
				if (c == '2')
					i = 2;
				else
					i = 3;
		}
		else
		{ //вывод ошибки
			ok = 1;
			SetColor(14, 0);
			printf("\n");
			printf("                                    ");
			PrintMessage("Введены некорректные данные");
			while (getchar() != '\n');
			printf("\n");
		}
	} while (ok == 1);
	switch (i)
	{
	case 1:
		InputFile(name, cnt_rec);
		break;
	case 2:
		CreateRecord(name, cnt_rec);
		break;
	case 3:
		if (cnt_rec == 0)
			MenuOne(name, cnt_rec);
		else
			MenuTwo(name, cnt_rec);
		break;
	}
}

//проверка ФИО на корректность ввода 
int checkFIO(char *s, char &c)
{
	int code = 0;
	int cnt_rus = 0;
	int cnt_eng = 0;
	int cnt_word = 1;
	int j = 0;
	int len = strlen(s);
	if (len > 40) // проверка на то, что пользователь не ввел слишком большую строку
		code = 3;
	else
		if (s[0] == '\0') //проверка на то, что пользователь не ввел пустую строку
			code = 4;
		else
		{ //находимся в цикле пока не найден некорректный символ или пока строка не станет слишком большой или пока строка не закончится
			while ((j < len) && (code == 0) && (j < 40))
			{
				if (s[j] == ' ')
				{
					cnt_word++;
					while (s[j] == ' ')
						j++;
				}
				else
					if ((code = check(c, cnt_rus, cnt_eng)) == 0)
						j++;
					else
						c = s[j];
			}
		}
			if (cnt_word > 3)
				code = 5;
	return code;
}

//проверка номера дома на корректность ввода 
int checkNumH(char *s, char &c)
{
	
	int code = 0;
	int j = 0;
	int len = strlen(s);
	if (len > 4) // проверка на то, что пользователь не ввел слишком большую строку
		code = 3;
	else
		if (s[0] == '\0') //проверка на то, что пользователь не ввел пустую строку
			code = 4;
		else
		{   //находимся в цикле пока не найден некорректный символ или пока строка не станет слишком большой или пока строка не закончится
			while ((j<len) && (code == 0) && (j < 4))
				if ((((s[j] >= 'A') && (s[j] <= 'Z')) || ((s[j] >= 'a') && (s[j] <= 'z'))) ||
					(((s[j] >= 'А') && (s[j] <= 'Я')) || ((s[j] >= 'а') && (s[j] <= 'я'))) ||
					(((s[j] >= '0') && (s[j] <= '9')) || (s[j] == ' ') || (s[j] == '\n') || (s[j] == '-')))
					j++;
				else
				{
					code = 1;
					c = s[j];
				}
		}
	return code;
}

//Анимация Success 
void Success()
{
	printf("                                                   ");
	printf("Create");
	SetColor(12, 0);
	printf(".");
	Sleep(200);
	printf(".");
	Sleep(200);
	printf(".");
	Sleep(200);
}

//Анимация Success 
void Addsuccess()
{
	system("cls");
	printf("                          ");
	SetColor(11, 0);
	printf("--------------------------------------------------------------\n");
	printf("                          ");
	SetColor(13, 0);
	printf("**************************************************************");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                            ");
	SetColor(10, 0);
	PrintMessage("Идет создание записи");
	printf("\n");
	Success();
	Sleep(200);

}

//информация при добавлении записией из файла 
void Text()
{
	printf("\n \n \n \n");
	printf("            ");
	SetColor(13, 0);
	printf("||===============================================================================================||");
	printf("\n");
	printf("\n");
	SetColor(11, 0);
	printf("                                              *****************************");
	printf("\n");
	printf("\n");
	printf("                            ");
	SetColor(10, 0);
	PrintMessage("На экране список записей, которые мы считали из текстового файла");
	printf("\n");
	Sleep(200);
	printf("\n");
	SetColor(11, 0);
	printf("                                              *****************************");
	printf("\n");
	printf("\n");
	printf("                          ");
	SetColor(10, 0);
	PrintMessage("Вы можете выбрать одну или несколько записей или все элементы сразу");
	printf("\n");
	printf("                                        ");
	PrintMessage("для внесения в основной бинарный файл");
	printf("\n");
	Sleep(200);
	printf("\n");
	SetColor(11, 0);
	printf("                                              *****************************");
	printf("\n");
	printf("\n");
	printf("                  ");
	SetColor(14, 0);
	printf("||=====================================================================================||");
	printf("\n");
	printf("                    ");
	SetColor(10, 0);
	PrintMessage("Для внесения всех записей введите ");
	SetColor(12, 0);
	PrintMessage("+");
	printf("\n");
	printf("                    ");
	SetColor(10, 0);
	PrintMessage("Для выхода из режима добавления записей и возврата в меню введите ");
	SetColor(12, 0);
	PrintMessage("0");
	printf("\n");
	SetColor(10, 0);
	printf("                    ");
	PrintMessage("Введите: ");
	
}

//ввод с клавиатуры /++
void InputKeyboard(char *name, int &cnt_rec)
{    //печать интерфейса
	struct record rec;
	system("cls");
	printf("          ");
	SetColor(11, 0);
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("          ");
	printf("||");
	SetColor(13, 0);
	printf("***************************************************************************************************");
	SetColor(11, 0);
	printf("|| ");
	printf("\n");
	printf("\n");
	printf("          ");
	SetColor(13, 0);
	printf("              * * * * * * * * * * * *      ");
	SetColor(10, 0);
	printf("Добавление записи");
	SetColor(13, 0);
	printf("      * * * * * * * * * * * *");
	printf("\n");
	printf("\n");
	printf("                                ");
	SetColor(10, 0);
	PrintMessage("Введите фамилию имя и отчество человека");
	printf("\n");
	printf("                                ");
	PrintMessage("для внесения в телефонную книгу: ");
	int code = 0;
	getchar();
	char c = ' ';

	do
	{   //проверка введенных данных 
		char data[40];
		SetColor(2, 0);
  		gets_s(data);		
		strcpy(rec.fio, trim(data)); //удаление лишних пробелов
		if ((code = checkFIO(rec.fio, c)) != 0) //проверка на корректность символов
		{
			PrintError(code,c,40);
			printf("\n");
			SetColor(10, 0);
			printf("                                ");
			PrintMessage("Повторите ввод фамилии имени и отчества: ");
		}
	} while (code != 0);
	printf("\n");
	printf("                                ");
	SetColor(10, 0);
	PrintMessage("Введите улицу проживания: ");
	do
	{//проверка введенных данных 
		char data[20];
		SetColor(2, 0);
		gets_s(data);
		strcpy(rec.adress.street, trim(data)); //удаление лишних пробелов
		if ((code = checkStreet(rec.adress.street, c)) != 0) //проверка на корректность символов
		{
			PrintError(code, c, 20);
			printf("\n");
			printf("                                ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод улицы: ");
		}
	} while (code != 0);
	printf("\n");
	printf("                                ");
	SetColor(10, 0);
	PrintMessage("Введите номер дома: ");
	do
	{ //проверка введенных данных 
		char data[4];
		SetColor(2, 0);
		gets_s(data);
		strcpy(rec.adress.NumH, trim(data)); //удаление лишних пробелов
		if ((code = checkNumH(rec.adress.NumH, c)) != 0) //проверка на корректность символов
		{
			PrintError(code, c, 4);
			printf("\n");
			printf("                                ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод номера дома: ");
		}
	} while (code != 0);
	printf("\n");
	SetColor(10, 0);
	printf("                                ");
	PrintMessage("Введите квартиру: ");
	do
	{  //проверка введенных данных 
		char data[3];
		SetColor(2, 0);
		gets_s(data);
		strcpy(rec.adress.flat, trim(data)); //удаление лишних пробелов
		if ((code = checkNumPh(rec.adress.flat,c)) != 0) //проверка на корректность символов
		{
			PrintError(code, c, 3);
			printf("\n");
			SetColor(10, 0);
			printf("                                ");
			PrintMessage("Повторите ввод номера дома");
		}
	} while (code != 0);
	printf("\n");
	SetColor(10, 0);
	printf("                                ");
	PrintMessage("Введите номер телефона");
	printf("\n");
	printf("                                ");
	PrintMessage("(если номер телефона отсутсвует введите -): ");
	do
	{  //проверка введенных данных 
		char data[12];
		gets_s(data);
		SetColor(2, 0);
		strcpy(rec.NumPh, trim(data));  //удаление лишних пробелов
		if ((code=checkNumPh(rec.NumPh,c)) != 0)  //проверка на корректность символов
		{
			PrintError(code, c, 12);
			printf("\n");
			SetColor(10, 0);
			printf("                                ");
			PrintMessage("Повторите ввод номера телефона: ");
		}
	} while (code != 0);
	if (cnt_rec == 0)
	{
		FILE* F = fopen(name, "ab");
		fwrite(&rec, sizeof(struct record), 1, F); //записываем запись в бинарный файл
		cnt_rec++;
		head = addEl((cnt_rec - 1), rec.fio); //добавление ФИО записи в список
		fclose(F);
	}
	else
		if (CheckRecord(name, cnt_rec, rec) != 1) //проверка записи на то, что мы ее ранее уже не вводили
		{
			FILE* F = fopen(name, "ab");
			fwrite(&rec, sizeof(struct record), 1, F);
			cnt_rec++;
			CreateList((cnt_rec - 1), rec.fio); ///добавление ФИО записи в список и сортировка списка
			fclose(F);
		}
		else
		{   //печать интерфейса в случае если запись уже существует
			printf("\n");
			printf("\n");
			SetColor(13, 0);
			printf("                        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			printf("\n");
			printf("\n");
			printf("                                          ");
			SetColor(10, 0);
			printf("Данная запись уже существует в файле");
			printf("\n");
			printf("                                           ");
			printf("Нажмите ");
			SetColor(12, 0);
			printf("ENTER ");
			SetColor(10, 0);
			printf("чтобы продолжить...");
			getchar();
		}
}

//проверка на корректный ввод и преобразование строки в число 
int getNumber(char* s, int j)
{
	int i = 0;
	int k;
	int code = 0;
	int num = 0;
	if (s[0] == '\0') //проверяем, что строка не пустая
	{
		code = 10;
		PrintError(code, 'c', 0);
	}
	else
	{
		int len = strlen(s);
		while ((i < len) && (code == 0)) //проверяем, что пользователь не ввел некорректный символ
		{
			if (s[i] == ' ')
				code = 6;
			else
				if (((s[i] >= 'A') && (s[i] <= 'Z')) || ((s[i] >= 'a') && (s[i] <= 'z')) || ((s[i] >= 'а') && (s[i] <= 'я')) || ((s[i] >= 'А') && (s[i] <= 'Я')))
					code = 7;
				else
					i++;
		}
		if (code != 0) //если введены некоректные символы то печатем ошибку
			PrintError(code, s[i], 0);
		else
			if (s[0] == '-')
			{
				code = 8;
				PrintError(code, 'c', 0);
			}
			else
			{ //если символы нормальные, то преобразуем строку в число
				i = 0;
				while (i < len)
				{
					k = s[i] - '0';
					num = num * 10 + k;
					i++;
				}
				if (num > j)
				{
					code = 9;
					PrintError(code, 'c', 0);
				}
			}
	}
	if (code == 0)
		return num;
	else
		return -1;
}

//добавление записи в файл 
void AddRecord(char* name, int &cnt_rec, int i, int j)
{
	struct record rec;
	FILE* FileIn = fopen("InputFile", "rb"); //открываем дополнительный файл
	fseek(FileIn, i* sizeof(struct record), SEEK_SET); //ставим указатель на нудную нам запись
	fread(&rec, sizeof(struct record), 1, FileIn); //считываем эту запись
	if (CheckRecord(name, cnt_rec, rec) == 0) //если такая запись уже сущетсвует, то выводим ошибку, если не существует, то записываем ее в основной файл при этом добавляем ее в сисок и сортируем
	{
		FILE* FileOut = fopen(name, "ab");
		fwrite(&rec, sizeof(struct record), 1, FileOut);
		if (cnt_rec == 0)
			head = addEl(cnt_rec, rec.fio);
		else
			CreateList(cnt_rec, rec.fio);
		cnt_rec++;
		fclose(FileOut);
	}
	else
	{
		if (j == 0)
		{
			printf("\n");
			printf("                    ");
			SetColor(14, 0);
			PrintMessage("При добавлении всех записей не удалось добавить следующую записи:");
		}
		printf("\n");
		printf("                    ");
		for (int t = 0; t < 60; t++)
		{
			printf("*");
		}
		printf("\n");
		printf("                    ");
		SetColor(10, 0);
		PrintMessage("Запись №" );
		SetColor(12, 0);
		printf("%d", i + 1);
		printf("\n");
		printf("\n");
		printf("                    ");
		SetColor(12, 0);
		PrintMessage("ФИО: ");
		SetColor(10, 0);
		PrintMessage(rec.fio);
		printf("\n");
		printf("                    ");
		SetColor(12, 0);
		PrintMessage("Адрес.Улица: ");
		SetColor(10, 0);
		PrintMessage(rec.adress.street);
		printf("\n");
		printf("                    ");
		SetColor(12, 0);
		PrintMessage("Адрес.номер дома: ");
		SetColor(10, 0);
		PrintMessage(rec.adress.NumH);
		printf("\n");
		printf("                    ");
		SetColor(12, 0);
		PrintMessage("Адрес.Номер квартиры: ");
		SetColor(10, 0);
		PrintMessage(rec.adress.flat);
		printf("\n");
		printf("                    ");
		if (rec.NumPh[0] == '-')
		{
			SetColor(12, 0);
			PrintMessage("Номер телефона отсутсвует");
		}
		else
		{
			SetColor(12, 0);
			PrintMessage("Номер телефона: ");
			SetColor(10, 0);
			PrintMessage(rec.NumPh);
		}
		printf("\n");
		printf("\n");
		printf("                    ");
		SetColor(14, 0);
		PrintMessage("уже была добавлена ранее");
		printf("\n");
		printf("                    ");
		SetColor(13, 0);
		for (int t = 0; t < 60; t++)
		{
			printf("*");
		}
	}
	fclose(FileIn);
}

//ввод с файла 
void InputFile(char *name, int& cnt_rec)
{
	char* NameTextFile;
	struct record rec;
	NameTextFile = ConectTextFile(name, cnt_rec); //получаем имя для текстового файла
	FILE* FText = fopen(NameTextFile, "rt"); //открываем текстовый файл
	FILE* File = fopen("InputFile", "wb");   //создание вспомогательного бинарного файла
	fclose(File);
	char data[41];
	int len;
	int j=1;
	int Nums;
	int code;
	char c = ' ';
	while (not feof(FText)) //считываем из текстового файла пока он не закончит, по принципу считали одну строку, проверили ее, если все нормально идем дальше, если нет, выводим ошибку. 
	{                       //если считали запись полностью без ошибок, записываем в спомогателбный бинарный файл
		Nums = 1;
		fgets(data, 41, FText); //считываем из файла
		trim(data);//убираем лишние пробелы
		len = strlen(data);//получаем длину строки
		if (data[len - 1] != '\n')//смотрим, что у нас не слишком много символов получено
			code = 30;
		else
		{
			data[len - 1] = '\0';//ставим конец строки в последний символ
			if ((code = checkFIO(data, c)) != 0)//проерка на корректный ввод
			{
				fclose(File);
				fclose(FText);
				PrintErrorFile(code * 10, c, 40, j, Nums);
				MenuTextFile(name, cnt_rec);
			}
			else
			{
				Nums++;
				strcpy(rec.fio, data);
				fgets(data, 21, FText);
				trim(data);
				len = strlen(data);
				if (data[len - 1] != '\n')
					code = 30;
				else
				{
					data[len - 1] = '\0';
					if ((code = checkStreet(data, c)) != 0)
					{
						fclose(File);
						fclose(FText);
						PrintErrorFile(code * 10, c, 20, j, Nums);
						MenuTextFile(name, cnt_rec);
					}
					else
					{
						Nums++;
						strcpy(rec.adress.street, data);
						fgets(data, 5, FText);
						trim(data);
						len = strlen(data);
						if (data[len - 1] != '\n')
							code = 30;
						else
						{
							data[len - 1] = '\0';
							if ((code = checkNumH(data, c)) != 0)
							{
								fclose(File);
								fclose(FText);
								PrintErrorFile(code * 10, c, 4, j, Nums);
								MenuTextFile(name, cnt_rec);
							}
							else
							{
								Nums++;
								strcpy(rec.adress.NumH, data);
								fgets(data, 4, FText);
								trim(data);
								len = strlen(data);
								if (data[len - 1] != '\n')
									code = 30;
								else
								{
									data[len - 1] = '\0';
									if ((code = checkFlat(data, c)) != 0)
									{
										fclose(File);
										fclose(FText);
										PrintErrorFile(code * 10, c, 3, j, Nums);
										MenuTextFile(name, cnt_rec);
									}
									else
									{
										Nums++;
										strcpy(rec.adress.flat, data);
										fgets(data, 12, FText);
										trim(data);
										len = strlen(data);
										if ((data[len - 1] != '\n') && (not feof(FText)))
											code = 30;
										else
										{
											data[len - 1] = '\0';
											if ((len > 11) && feof(FText))
												code = 30;
											else
												if ((code = checkNumPh(data, c)) != 0)
												{
													fclose(File);
													fclose(FText);
													PrintErrorFile(code * 10, c, 11, j, Nums);
													MenuTextFile(name, cnt_rec);
												}
												else
												{
													strcpy(rec.NumPh, data);
													File = fopen("InputFile", "ab");
													fwrite(&rec, sizeof(struct record), 1, File);
													j++;
													fclose(File);
													if (not feof(FText))
													{
														fgets(data, 112, FText);
													}
												}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (feof(FText) && (j == 0))//проверяем, что файл не пустой
		PrintErrorFile(-10, 'c', 0, 0, 0);
	else
	{
		system("cls");
		PrintHeader();
		File = fopen("InputFile", "rb"); //печатем полученные данные
		for (int i = 0; i < (j - 1); i++)
		{
			fread(&rec, sizeof(struct record), 1, File);
			PrintOneRecord(rec, i + 1);
		}
		fclose(FText);
		scanf("%c", &c);
		fclose(File);
		char num[5];
		Text();//печатаем интерфейс
		int i;
		do
		{  //вводим номер строкой
			SetColor(2, 0);
			gets_s(num);
			strcpy(num, trim(num));//убираем лишние пробелы
			if (num[0] == '+') 
			{
				i = 0;
				for (int t = 0; t < j-1; t++) //добавлем все символы
				{
					AddRecord(name, cnt_rec, t, 0);
				}	
			}
			else
			{
				i = getNumber(num, (j - 1)); //получаем номер
				if (i == -1) // если при вводе обнаружена ошибка предлагаем ввести ещё раз
				{
					printf("\n");
					printf("                    ");
					SetColor(10, 0);
					PrintMessage("Введите: ");
				}
				else
				{
					if (i != 0) //если не введен символ окончания добавления записей добавляем записи
					{
						AddRecord(name, cnt_rec, i - 1, 1);
						printf("\n");
						printf("                    ");
						SetColor(10, 0);
						PrintMessage("Введите номер следующей записи для добавления ");
						SetColor(12, 0);
						PrintMessage("(Для выхода введите 0) : ");
					}
				}
			}
		} while (i != 0);

	}
	remove("InputFile");//удаляем вспомогательный файл
}

//первое меню( вызывается, если нет ни одной записи 
void MenuOne(char *name, int &cnt_rec)
{  //печать интерфейса
	SetColor(11, 0);
	printf("                               ");
	printf("----------------------------------------------------");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|                                                |");
	SetColor(11, 0);
	printf("|");
	printf("\n");
	SetColor(11, 0);
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|          ");
	SetColor(12, 0);
	printf("--1.");
	SetColor(10, 0);
	printf("Создать новую запись              ");
	SetColor(13, 0);
	printf("|");
	SetColor(11, 0);
	printf("|");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|          ");
	SetColor(12, 0);
	printf("--0.");
	SetColor(10, 0);
	printf("Выйти                             ");
	SetColor(13, 0);
	printf("|");
	SetColor(11, 0);
	printf("| ");
	SetColor(11, 0);
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|                                                |");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|                                                |");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("----------------------------------------------------");
	printf("\n");
	int ok = 1;
	int i = 1;
	do
	{ //вводим номер и проверяем его на корректность
		printf("\n");
		printf("                               ");
		SetColor(11, 0);
		printf("****************************");
		printf("\n");
		SetColor(10, 0);
		printf("                               ");
		PrintMessage("Введите: ");
		char c;
		SetColor(2, 0);
		scanf("%c", &c);
		if ((c == '1') || (c == '0'))
		{
			ok = 0;
			if (c == '0')
				i = 0;
		}
		else
		{  //печатаем ошибку
			while (getchar() != '\n');
			SetColor(14, 0);
			printf("                               ");
			PrintMessage("Введены некорректные данные");
			printf("\n");
		}

	} while (ok == 1);

	switch (i)
	{
	case 1: CreateRecord(name, cnt_rec);
		break;
	case 0: 
		SetColor(15, 0);
		exit(EXIT_SUCCESS);
		break;
	}
}

//второе меню (вызывается, если есть хотя бы одна запись /++
void MenuTwo(char *name, int &cnt_rec)
{  //печать интерфейса 
	system("cls");
	printf("               ");
	SetColor(11, 0);
	printf("---------------------------------------------------------------------------------------------\n");
	printf("               ");
	printf("|"); 
	SetColor(13, 0);
	printf("|*****************************************************************************************|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                 ");
	SetColor(12, 0);
	printf("--1.");
	SetColor(10, 0);
	printf("Редактировать запись                                              ");
	SetColor(13, 0);
	printf("*|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                 ");
	SetColor(12, 0);
	printf("--2.");
	SetColor(10, 0);
	printf("Создать новую запись                                              ");
	SetColor(13, 0);
	printf("*|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                 ");
	SetColor(12, 0);
	printf("--3.");
	SetColor(10, 0);
	printf("Удалить запись                                                    ");
	SetColor(13, 0);
	printf("*|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                 ");
	SetColor(12, 0);
	printf("--4.");
	SetColor(10, 0);
	printf("Вывести все данные                                                ");
	SetColor(13, 0);
	printf("*|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                 ");
	SetColor(12, 0);
	printf("--5.");
	SetColor(10, 0);
	printf("Выбрать и занести по заданному адресу                             ");
	SetColor(13, 0);
	printf("*|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                 ");
	SetColor(10, 0);
	printf("    (улица, номер дома) сведенья об абонентах, имеющих телефоны       "); 
	SetColor(13, 0);
	printf("*|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                 ");
	SetColor(12, 0);
	printf("--0.");
	SetColor(10, 0);
	printf("Выход                                                             ");
	SetColor(13, 0);
	printf("*|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|"); 
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*                                                                                       *|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("               ");
	printf("|");
	SetColor(13, 0);
	printf("|*****************************************************************************************|");
	SetColor(11, 0);
	printf("| \n");
	printf("               ");
	printf("---------------------------------------------------------------------------------------------");
	printf("\n");
	char c;
	int ok = 1;
	int i = 0;
	do
	{ //ввод символа и проверка на корректность
		SetColor(11, 0);
		printf("\n");
		printf("               ");
		printf("*****************************\n");
		printf("               ");
		SetColor(10, 0);
		printf("Введите: ");
		SetColor(2, 0);
		scanf("%c", &c);
		if ((c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5') || (c == '0'))
		{
			ok = 0;
			if (c == '1')
				i = 1;
			else
				if (c == '2')
					i = 2;
				else
					if (c == '3')
						i = 3;
					else
						if (c == '4')
							i = 4;
						else
							if (c == '5')
								i = 5;
							else
								if (c == '0')
									i = 0;
		}
		else
		{
			scanf("%c", &c);
			printf("\n");
			printf("               ");
			SetColor(14, 0);
			PrintMessage("Введены некорректные данные");
			printf("\n");
			ok = 1;
		}
	} while (ok == 1);
	switch (i)
	{//обратка введенного значения и вызов функции
	case 0: SetColor(15, 0);
		cleanList();
		exit(EXIT_SUCCESS);
		break;
	case 1:	EditRecord(name, cnt_rec);
		break;
	case 2: CreateRecord(name, cnt_rec);
		break;
	case 3:	DeleteRecord(name, cnt_rec);
		break;
	case 4:	PrintRecords(name, cnt_rec);
		break;
	case 5: MainTask(name, cnt_rec);
		break;
	}
}

//функция, которая сортирует записи в файле /++
void SortFile(char* name, int cnt_rec)
{
	struct record rec;
	list* h;
	h = (struct list*)malloc(sizeof(struct list)); //выделяем память под элемент списка
	FILE *FileOne = fopen(name, "rb"); //открываем основной файл
	FILE* FileTwo = fopen("InputData(sort)", "wb"); //создаем новый файл для сортировки
	fclose(FileTwo);
	int num;
	h = head;
	int i=0;
	while (h != NULL) //движемся по списку, пока не дойдем до конца
	{
		FileTwo = fopen("InputData(sort)", "ab"); //открываем файл на запись в конец
		num = h->Num; //меняем номера в списке
		fseek(FileOne, num * sizeof(struct record), SEEK_SET);//устанавливаем указатель на запись, номер которой равен номеру в структуре
		fread(&rec, sizeof(struct record), 1, FileOne);//считываем запись
		fwrite(&rec, sizeof(struct record), 1, FileTwo);//записываем запись в новый файл
		h->Num = i;
		i++;
		h = h->next;//переставляем указатель на следующий элемент списка
		fclose(FileTwo);//закрываем файл
	}
	fclose(FileOne);//закрываем файл
	remove(name);//удаляем старый файл
	rename("InputData(sort)", name);//переимовываем новый файл именем старого
}

//функция редактирования определенной записи 
void EditRecord(char* name, int& cnt_rec)
{
	system("cls");
	FILE* F = fopen(name, "rb");
	struct record rec;
	PrintHeader(); //печаатем записи которые у нас есть в бинарном файле
	for (int i = 0; i < cnt_rec; i++)
	{
		fread(&rec, sizeof(struct record), 1, F);
		PrintOneRecord(rec, i + 1);
	}//печатем интерфейс
	fclose(F);
	printf("\n");
	printf("\n");
	printf("\n");
	SetColor(11, 0);
	printf("                     ");
	printf("||===========================================================================||");
	printf("\n");
	SetColor(11, 0);
	printf("                       ");
	printf("|");
	SetColor(13, 0);
	printf("|***********************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	int k;
	int ok = 0;
	int i;
	do
	{	//вводим номер записи для редакции и проверяем на корректность
		printf("\n");
		printf("                                          ");
		SetColor(10, 0);
		PrintMessage("Введите номер записи для редактирования: ");

		char num[5];
		char c;
		scanf("%c", &c);
		do
		{
			SetColor(2, 0);
			gets_s(num);
			strcpy(num, trim(num));
			i = getNumber(num, cnt_rec);
			if (i == -1)
			{
				printf("\n");
				printf("                                          ");
				SetColor(10, 0);
				PrintMessage("Введите заново: ");
			}
		} while (i == -1);
		printf("\n");
		printf("                           ");
		SetColor(10, 0);//спрашиваем у пользователя разрешение на редактирование записи
		PrintMessage("Вы уверены, что хотите редактировать данную запись?(");
		SetColor(12, 0);
		PrintMessage("Y(Н)");
		SetColor(10, 0);
		PrintMessage("-ДА, ");
		SetColor(12, 0);
		PrintMessage("N(Т)");
		SetColor(10, 0);
		PrintMessage ("- НЕТ) ? ");
		printf("\n");
		printf("                                                      ");
		PrintMessage("Введите: ");
		do
		{//вводим чисвол и проверяем на корректность
			SetColor(2, 0);
			scanf("%c", &c);
			if ((c == 'y') || (c == 'Y') || (c == 'н') || (c == 'Н') || (c == 'N') || (c == 'n') || (c == 'т') || (c == 'Т'))
			{
				ok = 0;
				if ((c == 'y') || (c == 'Y') || (c == 'н') || (c == 'Н'))
					k = 1;
				else
					k = 0;
			}
			else
			{
				ok = 1;
				while (getchar() != '\n');
				printf("                                   ");
				SetColor(14, 0);
				PrintMessage("Введен корректный символ");
				printf("\n");
				printf("                                                      ");
				SetColor(10, 0);
				PrintMessage("Введите: ");
			}
		} while (ok == 1);
	} while (k == 0);

	list* h, * p;
	p = (struct list*)malloc(sizeof(struct list));//выделяем память под элемент списка
	h = (struct list*)malloc(sizeof(struct list));
	ok = 0;
	if (i == 1)//если нужно редактировать первый элемент то удаляем голову списка
	{
		p = head;
		head = head->next;
		free(p);
		h = head;
		h->Num = (h->Num - 1);
		if (h->next != NULL) //изменяем в остальных элементах списка номер записи
			while (h->next != NULL)
			{
				h = h->next;
				h->Num = (h->Num - 1);
			}
		fclose(F);
		cnt_rec = cnt_rec - 1;
		FILE* FileOne = fopen(name, "rb");//открываем бинарный файл
		FILE* FileTwo = fopen("InputData(sort)", "wb");//создаем ещё один бинарный файл
		fclose(FileTwo);
		fseek(FileOne, i * sizeof(struct record), SEEK_SET);//ставим указаьтель на следующую запись нам запись
		for (int j = 0; j < cnt_rec; j++)
		{
			FileTwo = fopen("InputData(sort)", "ab");// записываем все записи, котоыре идут выше заданной
			fread(&rec, sizeof(struct record), 1, FileOne);
			fwrite(&rec, sizeof(struct record), 1, FileTwo);
			fclose(FileTwo);
		}
		fclose(FileOne);
	}
	else//в случае если нужно поменять не первый элемент
	{
		h = head;
		while (ok == 0)//ищем этот элемент в списке
		{
			p = h->next;
			if (p->Num == (i - 1))
				ok = 1;
			else
				h = h->next;

		}
		h->next = p->next; //перекидываем указатель на следующий
		free(p);//удаляем нужный нам элемент списка
		if (h->next != NULL) //идем до конца списка и уменьшаем номер в элементе списка на 1
			while (h->next != NULL)
			{
				h = h->next;
				h->Num = (h->Num - 1);
			}
		fclose(F);
		cnt_rec = cnt_rec - 1;//уменьшаем количество записей
		FILE* FileOne = fopen(name, "rb");//открываем бинарный файл
		FILE* FileTwo = fopen("InputData(sort)", "wb");//создаем новый бинарный файл
		fclose(FileTwo);
		for (int j = 0; j <= i - 1; j++)//записываем в новый файл записи до нужной нам записи
		{
			FileTwo = fopen("InputData(sort)", "ab");
			fread(&rec, sizeof(struct record), 1, FileOne);
			fwrite(&rec, sizeof(struct record), 1, FileTwo);
			fclose(FileTwo);
		}
		fseek(FileOne, (i + 1) * sizeof(struct record), SEEK_SET);//пропускаем одну запись
		while (i < cnt_rec)//записываем в новый файл записи после нужной нам записи
		{
			FileTwo = fopen("InputData(sort)", "ab");
			fread(&rec, sizeof(struct record), 1, FileOne);
			fwrite(&rec, sizeof(struct record), 1, FileTwo);
			fclose(FileTwo);
			i++;
		}
		fclose(FileOne);//закрываем файл
	}
	remove(name);//удаляем старый файл
	rename("InputData(sort)", name);//меняем имя нового файла на имя старого файла
	system("cls"); //печать интерфейса
	printf("          ");
	SetColor(11, 0);
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("          ");
	printf("|");
	SetColor(13, 0);
	printf("|***************************************************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("\n");
	printf("          ");
	SetColor(13, 0);
	printf("          * * * * * * * * * * * *      ");
	SetColor(10, 0);
	printf("Редактирование записи");
	SetColor(13, 0);
	printf("      * * * * * * * * * * * *");
	printf("\n");
	printf("\n");
	printf("                                ");
	SetColor(10, 0);
	PrintMessage("Введите фамилию имя и отчество человека");
	printf("\n");
	printf("                                ");
	PrintMessage("для редактирования записи в телефонной книге: ");
	int code = 0;
	getchar();
	char c = ' ';

	do
	{
		SetColor(2, 0);
		char data[40];
		gets_s(data);//ввод данных
		strcpy(rec.fio, trim(data));//удаление лишних пробелов
		if ((code = checkFIO(rec.fio, c)) != 0) //проверка на коректность
		{
			PrintError(code, c, 40);
			printf("\n");
			printf("                                ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод фамилии имени и отчества: ");
		}
	} while (code != 0);
	printf("\n");
	printf("                                ");
	SetColor(10, 0);
	PrintMessage("Введите улицу проживания: ");
	do
	{
		SetColor(2, 0);
		char data[20];
		gets_s(data);//ввод данных
		strcpy(rec.adress.street, trim(data));//удаление лишних пробелов
		if ((code = checkStreet(rec.adress.street, c)) != 0)//проверка на коректность
		{
			PrintError(code, c, 20);
			printf("\n");
			printf("                                ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод улицы: ");
		}
	} while (code != 0);
	printf("\n");
	SetColor(10, 0);
	printf("                                ");
	PrintMessage("Введите номер дома: ");
	do
	{
		SetColor(2, 0);
		char data[4];
		gets_s(data);//ввод данных
		strcpy(rec.adress.NumH, trim(data));//удаление лишних пробелов
		if ((code = checkNumH(rec.adress.NumH, c)) != 0)//проверка на коректность
		{
			PrintError(code, c, 4);
			printf("\n");
			printf("                                ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод номера дома: ");
		}
	} while (code != 0);
	printf("\n");
	printf("                                ");
	SetColor(10, 0);
	PrintMessage("Введите квартиру: ");
	do
	{
		SetColor(2, 0);
		char data[3];
		gets_s(data);//ввод данных
		strcpy(rec.adress.flat, trim(data));//удаление лишних пробелов
		if ((code = checkNumPh(rec.adress.flat, c)) != 0)//проверка на коректность
		{
			PrintError(code, c, 3);
			printf("\n");
			printf("                                ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод номера дома");
		}
	} while (code != 0);
	printf("\n");
	printf("                                ");
	SetColor(10, 0);
	PrintMessage("Введите номер телефона");
	printf("\n");
	printf("                                ");
	PrintMessage("(если номер телефона отсутсвует введите -): ");
	do
	{
		SetColor(2, 0);
		char data[12];
		gets_s(data);//ввод данных
		strcpy(rec.NumPh, trim(data));//удаление лишних пробелов
		if ((code = checkNumPh(rec.NumPh, c)) != 0)//проверка на коректность
		{
			PrintError(code, c, 12);
			if ((code != 4) || (code != 3))
				while (getchar() != '\n');
			printf("\n");
			printf("                                ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод номера телефона: ");
		}
	} while (code != 0);
	if (cnt_rec == 0) //если ни одной записи не было, то добавляем ее в бинарный файл и создаем список
	{
		F = fopen(name, "ab");
		fwrite(&rec, sizeof(struct record), 1, F);
		cnt_rec++;
		head = addEl((cnt_rec - 1), rec.fio);
		fclose(F);
	}
	else
		if (CheckRecord(name, cnt_rec, rec) != 1) //проверяем запись на то, что не вводили ее уже ранее
		{
			F = fopen(name, "ab");
			fwrite(&rec, sizeof(struct record), 1, F);//печаем ее в бинарный файл
			cnt_rec++;
			CreateList((cnt_rec - 1), rec.fio);//добавляем ФИО в список и спортируем 
			fclose(F);
			SortFile(name, cnt_rec);//сортируем файл
		}
		else
		{//печатаем интерфейс в случае, если такая запись уже существует
			printf("\n");
			printf("\n");
			SetColor(11, 0);
			printf("                        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			printf("\n");
			printf("\n");
			printf("                                          ");
			SetColor(10, 0);
			printf("Данная запись уже существует в файле");
			printf("\n");
			printf("                                           ");
			printf("Нажмите ");
			SetColor(12, 0);
			printf("ENTER");
			SetColor(10, 0);
			printf("чтобы продолжить...");
			getchar();
			fclose(F);
		}
	system("cls");
	MenuTwo(name, cnt_rec);
}

//меню для создания записи. вызывает функции для ввода из файла/ с клавиатуры данных 
void CreateRecord(char *name, int &cnt_rec)									
{//печать интерфейса
	system("cls");
	SetColor(11, 0);
	printf("                               ");
	printf("----------------------------------------------------");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|                                                |");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|     ");
	SetColor(12, 0);
	printf("--1.");
	SetColor(10, 0);
	printf(" Ввести данные с клавиатуры            ");
	SetColor(13, 0);
	printf("|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|     ");
	SetColor(12, 0);
	printf("--2.");
	SetColor(10, 0);
	printf(" Ввести данные из текстового файла     ");
	SetColor(13, 0);
	printf("|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|                                                |");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|                                                |");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	printf("----------------------------------------------------");
	printf("\n");
	int ok = 1;
	int i = 1;
	char c;
	scanf("%c", &c);
	do
	{//ввод символа и обработка на корректность
		SetColor(11, 0);
		printf("\n");
		printf("                               ");
		printf("****************************");
		printf("\n");
		SetColor(10, 0);
		printf("                               ");
		PrintMessage("Введите: ");
		SetColor(2, 0);
		scanf("%c", &c);
		if ((c == '1') || (c == '2'))
		{
			ok = 0;
			if (c == '2')
				i = 2;
		}
		else
		{//печать ошибки если символ ен корректный 
			SetColor(14, 0);
			while (getchar() != '\n');
			printf("                               ");
			PrintMessage("Введены некорректные данные");
			printf("\n");
		}

	} while (ok == 1);

	switch (i)
	{
	case 1: InputKeyboard(name, cnt_rec);
		break;
	case 2: Info();
		InputFile(name, cnt_rec);
		break;
	}
	SortFile(name, cnt_rec);
	system("cls");
	for (int j = 0; j < 3; j++)
	{
		Addsuccess();
	}
	system("cls");
	MenuTwo(name, cnt_rec);
}

//функция удаления записи 
void DeleteRecord(char *name, int &cnt_rec)
{
	system("cls");
	FILE* F = fopen(name, "rb");
	struct record rec;
	PrintHeader();//печать записей из бинарного файла 
	for (int i = 0; i < cnt_rec; i++)
	{
		fread(&rec, sizeof(struct record), 1, F);
		PrintOneRecord(rec, i + 1);
	}//печать интерфейса
	fclose(F);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                     ");
	SetColor(11, 0);
	printf("||===========================================================================||");
	printf("\n");
	printf("                       ");
	printf("|");
	SetColor(13, 0);
	printf("|***********************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	int k;
	int ok = 0;
	int i;
	do
	{//просим у пользователя номер записи для удаления и проверяем его
		printf("\n");
		printf("                                          ");
		SetColor(10, 0);
		PrintMessage("Введите номер записи для удаления: ");

		char num[5];
		char c;
		scanf("%c", &c);
		do
		{
			SetColor(2, 0);
			gets_s(num);//вводим номер
			strcpy(num, trim(num));//обрезаем пробелы
			i = getNumber(num, cnt_rec);//получаем номер
			if (i == -1)
			{
				printf("\n");
				printf("                                          ");
				SetColor(10, 0);
				PrintMessage("Введите заново: ");
			}
		} while (i == -1);
		printf("\n");
		printf("                           ");
		SetColor(10, 0);//запрашиваем подтверждение на удаление
		PrintMessage("Вы уверены, что хотите удалить данную запись?(");
		SetColor(12, 0);
		PrintMessage("Y(Н)");
		SetColor(10, 0);
		PrintMessage("-ДА, ");
		SetColor(12, 0);
		PrintMessage("N(Т)");
		SetColor(10, 0);
		PrintMessage("-НЕТ) ? ");
		printf("\n");
		printf("                                                      ");
		PrintMessage("Введите: ");
		do
		{//ввод и проверка на корректность ввода
			SetColor(2, 0);
			scanf("%c", &c);
			if ((c == 'y') || (c == 'Y') || (c == 'н') || (c == 'Н') || (c == 'N') || (c == 'n') || (c == 'т') || (c == 'Т'))
			{
				ok = 0;
				if ((c == 'y') || (c == 'Y') || (c == 'н') || (c == 'Н'))
					k = 1;
				else
					k = 0;
			}
			else
			{//печать ошибки
				ok = 1;
				while (getchar() != '\n');
				printf("                                   ");
				SetColor(14, 0);
				PrintMessage("Введен корректный символ");
				printf("\n");
				printf("                                                      ");
				SetColor(10, 0);
				PrintMessage("Введите: ");
			}
		} while (ok == 1);
	} while (k == 0);
	
	list* h, *p;
	p = (struct list*)malloc(sizeof(struct list));//выделение память под элемент списка
	h = (struct list*)malloc(sizeof(struct list));
	ok = 0;
	if (i == 1)//если нужно удалить первый элемент из списка
	{
		p = head;//берем первый элемент
		head = head->next;//перебрасываем в основном списке указатель на следующий элемент
		free(p);//чистм первый элемент
		h = head;
		h->Num = (h->Num - 1);//для последующих элемент уменьшаем номер на 1
		if (h->next != NULL)
			while (h->next != NULL)
			{
				h = h->next;
				h->Num = (h->Num - 1);
			}
		fclose(F);
		cnt_rec = cnt_rec - 1;
		FILE* FileOne = fopen(name, "rb");//открываем бинарный файл
		FILE* FileTwo = fopen("InputData(sort)", "wb");//создаем новый бинарный файл
		fclose(FileTwo);
		fseek(FileOne, i  * sizeof(struct record), SEEK_SET);//ставим указатель на вторую запись
		for (int j = 0; j < cnt_rec; j++)//записываем в новый файл все записи из первого начинай со второго
		{
			FileTwo = fopen("InputData(sort)", "ab");
			fread(&rec, sizeof(struct record), 1, FileOne);
			fwrite(&rec, sizeof(struct record), 1, FileTwo);
			fclose(FileTwo);
		}
		fclose(FileOne);
	}
	else//если нужно удалить непервый элемент
	{
		h = head;
		while (ok == 0)
		{
			p = h->next;//находим этот элемент
			if (p->Num == (i - 1))
				ok = 1;
			else
				h = h->next;

		}
		h->next = p->next;//перебрасываем указатель на слеудющий
		free(p);//удаляем нужный элемент список
		if (h->next != NULL) //в последующих элементах уменьшаем номер на 1
			while (h->next != NULL)
			{
				h = h->next;
				h->Num = (h->Num - 1);
			}
		fclose(F);
		cnt_rec = cnt_rec - 1;
		FILE* FileOne = fopen(name, "rb");//открываем бинарный файл
		FILE* FileTwo = fopen("InputData(sort)", "wb");//создаем новый бинарный файл
		fclose(FileTwo);
		for (int j = 0; j <= i - 1; j++)//печатем в новый файл записи до нужной нам записи
		{
			FileTwo = fopen("InputData(sort)", "ab");
			fread(&rec, sizeof(struct record), 1, FileOne);
			fwrite(&rec, sizeof(struct record), 1, FileTwo);
			fclose(FileTwo);
		}
		fseek(FileOne, (i + 1) * sizeof(struct record), SEEK_SET);//пропускаем одну запись
		while (i < cnt_rec)//печатаем последующие записи
		{
			FileTwo = fopen("InputData(sort)", "ab");
			fread(&rec, sizeof(struct record), 1, FileOne);
			fwrite(&rec, sizeof(struct record), 1, FileTwo);
			fclose(FileTwo);
			i++;
		}
		fclose(FileOne);
	}
	remove(name);//удаляем старый файл
	rename("InputData(sort)", name);//переименовываем новый файл именем старого
	system("cls");//печатаем интерфейс
	printf("                          ");
	SetColor(11, 0);
	printf("--------------------------------------------------------------\n");
	printf("                          ");
	SetColor(13, 0);
	printf("**************************************************************");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                             ");
	SetColor(10, 0);
	PrintMessage("Запись успешна удалена");
	Sleep(800);
	system("cls");
	char c;
	scanf("%c", &c);
	if (cnt_rec == 0)
		MenuOne(name, cnt_rec);
	else
		MenuTwo(name, cnt_rec);
}

// функция печать всех записей из файла
void PrintRecords(char *name, int &cnt_rec)
{
	system("cls");
	char c;
	scanf("%c", &c);
	FILE* F = fopen(name, "rb");
	struct record rec;
	PrintHeader();//печатаем записи из бинарного файла
	for (int i = 0; i < cnt_rec; i++)
	{
		fread(&rec, sizeof(struct record), 1, F);
		PrintOneRecord(rec, i + 1);
	}
	fclose(F);
	printf("\n");
	SetColor(10, 0);
	PrintMessage("Для продолжения нажмите ");
	SetColor(12, 0);
	PrintMessage("ENTER");
	SetColor(10, 0);
	PrintMessage("...");
	SetColor(2, 0);
	scanf("%c", &c);
	MenuTwo(name, cnt_rec);
}

//функция, которая формирует текстовый файл для основной задачи 
int OutputHelp(char* name, int cnt_rec, struct record rec)
{
	FILE* FileIn = fopen("Output.txt", "wt");//создаем вспомогательный текстовый файл
	FILE* FileOut = fopen(name, "rb");//открываем бинарный файл
	struct record rec1;
	int k = 0;
	for (int i = 0; i < cnt_rec - 1; i++)//ищем записи, которые удовлетворяют условию и печатаем их в бинарный файл
	{
		fread(&rec1, sizeof(struct record), 1, FileOut);
		if ((strcmp("-", rec1.NumPh) != 0) && (strcmp(rec.adress.street, rec1.adress.street) == 0) && (strcmp(rec.adress.NumH, rec1.adress.NumH) == 0))
		{
			fprintf(FileIn, "ФИО: ");
			fprintf(FileIn, rec1.fio);
			fprintf(FileIn, "\n");
			fprintf(FileIn, "Адрес");
			fprintf(FileIn, "\n");
			fprintf(FileIn, "Улица: ");
			fprintf(FileIn, rec1.adress.street);
			fprintf(FileIn, "\n");
			fprintf(FileIn, "Номер дома: ");
			fprintf(FileIn, rec1.adress.NumH);
			fprintf(FileIn, "\n");
			fprintf(FileIn, "Квартира: ");
			fprintf(FileIn, rec1.adress.flat);
			fprintf(FileIn, "\n");
			fprintf(FileIn, "Номер телефона: ");
			fprintf(FileIn, rec1.NumPh);
			fprintf(FileIn, "\n");
			fprintf(FileIn, "\n");
			k++;
		}
	}
	fclose(FileIn);//закрываем файлы
	fclose(FileOut);
	return k;
}

//функция вывода на экран для основной задачи
void OutPutScreen(char* name, int cnt_rec, struct record rec)
{
	printf("           ");
	SetColor(11, 0);
	printf("||----------------------------------------------------------------------------------------||");
	printf("\n");
	printf("             ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	if (OutputHelp(name, cnt_rec, rec) == 0)//создаем текстовый файл и смотрим сколько добавилось записей
	{//если ни одной не добавилось
		
		printf("                                           ");
		SetColor(14, 0);
		PrintMessage("Ни одной задписи не найдено");
	}
	else
	{//если записи добавились
		FILE* FileIn = fopen("Output.txt", "rt");//открываем файл
		char s[40];
		SetColor(14, 0);
		while (!feof(FileIn))//печатаем из файла на экран
		{
			printf("                                               ");
			fgets(s, 50, FileIn);
			printf("%s", s);
			if (!feof(FileIn))
				fgets(s, 50, FileIn);
		}
	}
	char c;
	printf("\n");//выводим интерфейс для продолжения
	printf("                                               ");
	SetColor(10, 0);
	PrintMessage("Нажмите ");
	SetColor(12, 0);
	PrintMessage("Enter");
	SetColor(10, 0);
	PrintMessage("чтобы продолжить...");
	scanf("%c", &c);
}

// функция печати в файл для основной задачи
void OutPutFile(char* name, int cnt_rec, struct record rec)
{
	printf("           ");
	SetColor(11, 0);//печатаем интерфейс
	printf("||----------------------------------------------------------------------------------------||");
	printf("\n");
	printf("             ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("                               ");
	SetColor(13, 0);
	PrintMessage("* * * * * *");
	SetColor(10, 0);
	PrintMessage("Подключение текстового файла");
	SetColor(13, 0);
	PrintMessage("* * * * * * ");
	printf("\n");
	printf("\n");
	SetColor(10, 0);
	printf("                                          ");
	PrintMessage("Введите имя текстовго файла: ");
	int code = 0;
	char nameOut[50];
	do
	{//вводим имя файла и проверяем его на корректность
		SetColor(2, 0);
		scanf("%s", nameOut);
		int len = strlen(nameOut);
		int i = 0;
		while ((i < len) && (code == 0))
		{
			if ((nameOut[i] == '+') || (nameOut[i] == '=') || (nameOut[i] == '[') || (nameOut[i] == ']') || (nameOut[i] == ':') || (nameOut[i] == '#') || 
				(nameOut[i] == '%') || (nameOut[i] == '{') || (nameOut[i] == '}') ||
				(nameOut[i] == '<') || (nameOut[i] == '>') || (nameOut[i] == '*') || (nameOut[i] == '?') || (nameOut[i] == '/') || (nameOut[i] == ' ') || (nameOut[i] == '$') || 
				(nameOut[i] == '!') || (nameOut[i] == '`') ||
				(nameOut[i] == '"') || (nameOut[i] == '@') || (nameOut[i] == '|'))
			{
				code = 1;
				while (getchar() != '\n');
				printf("\n");
				printf("                              ");
				SetColor(14, 0);
				PrintMessage("При вводе имени файла обнаружен некорректный символ ");
				SetColor(12, 0);
				printf("%c", nameOut[i]);
				printf("\n");
				printf("                                          ");
				SetColor(12-0, 0);
				PrintMessage("Повторите ввод: ");
			}
			i++;
		}
	} while (code != 0);
	int len = strlen(nameOut);//проверяем ввел ли пользователь расширение 'txt'
	if ((nameOut[len - 4] != '.') && ((nameOut[len - 3] != 't') || (nameOut[len - 3] != 'T')) && ((nameOut[len - 2] != 'x') || (nameOut[len - 2] != 'X')) && 
		((nameOut[len - 1] != 't') || (nameOut[len - 3] != 'T')))
	{
		const char* s1 = ".txt";
		strcat(nameOut, s1);
	}
	if (OutputHelp(name, cnt_rec, rec) == 0)//добавляем в текстовый файл необходимые записи
	{
		FILE* FileIn = fopen("Output.txt", "wt");
		fscanf(FileIn, "Ни одной записи не обнаружено");
	}
	rename("Output.txt", nameOut);//переименовываем файл со служебного имени на введеное
	printf("\n");
	SetColor(14, 0);
	printf("                                          ");//печатаем интерфейс
	PrintMessage("Результат находится в файле");
	Sleep(600);
}

//основная задача
void MainTask(char *name, int cnt_rec)
{//печатаем интерфейс
	system("cls");
	printf("           ");
	SetColor(11, 0);
	printf("||----------------------------------------------------------------------------------------||");
	printf("\n");
	printf("             ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************************************************|");
	SetColor(10, 0);
	printf("| ");
	printf("\n");
	printf("\n");
	printf("                           ");
	SetColor(13, 0);
	PrintMessage("* * * * * * * ");
	SetColor(10, 0);
	PrintMessage("Ввод адреса для выполнения запроса ");
	SetColor(13, 0);
	PrintMessage("* * * * * * *");
	printf("\n");
	printf("\n");
	printf("                                             ");
	SetColor(10, 0);
	PrintMessage("Введите улицу проживания: ");
	char c ;
	scanf("%c", &c);
	c = ' ';
	int code;
	struct record rec;

	do
	{//водим адрес и улицу для сравнения
		SetColor(2, 0);
		char data[20];
		gets_s(data);//водим
		strcpy(rec.adress.street, trim(data));//убираем лишние пробелы
		if ((code = checkStreet(rec.adress.street, c)) != 0)//проверяем на корректность
		{
			printf("                         ");
			PrintError(code, c, 20);
			printf("\n");
			printf("	                                     ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод улицы: ");
		}
	} while (code != 0);
	printf("\n");
	printf("                                             ");
	SetColor(10, 0);
	PrintMessage("Введите номер дома: ");
	do
	{
		SetColor(2, 0);
		char data[4];
		gets_s(data);//вводим
		strcpy(rec.adress.NumH, trim(data));//убираем лишние пробелы
		if ((code = checkNumH(rec.adress.NumH, c)) != 0)//проверяем на корректность
		{
			printf("                       ");
			PrintError(code, c, 4);
			printf("\n");
			printf("	                                     ");
			SetColor(10, 0);
			PrintMessage("Повторите ввод номера дома: ");
		}
	} while (code != 0);
	system("cls");
	printf("           ");//печатаем интерфейс
	SetColor(11, 0);
	printf("||----------------------------------------------------------------------------------------||");
	printf("\n");
	printf("             ");
	printf("|");
	SetColor(13, 0);
	printf("|************************************************************************************|");
	SetColor(11, 0);
	printf("| ");
	printf("\n");
	printf("\n");
	printf("                                        ");
	SetColor(12, 0);
	PrintMessage("--1.");
	SetColor(10, 0);
	PrintMessage("Вывести сведенья на экран");
	printf("\n");
	printf("\n");
	printf("                                        ");
	SetColor(12, 0);
	PrintMessage("--2.");
	SetColor(10, 0);
	PrintMessage("Вывести сведенья в текстовый файл");
	printf("\n");
	printf("\n");
	printf("                                        ");
	int ok;
	int i;
	do
	{//вводим символ и проверяем его на корректность
		SetColor(10, 0);
		printf("\n");
		printf("                                        ");
		PrintMessage("Введите: ");
		SetColor(2, 0);
		scanf("%c", &c);
		if ((c == '1') || (c == '2'))
		{
			ok = 0;
			if (c == '1')
				i = 1;
			else
				i = 2;
		}
		else
		{//вводим ошибку если неправильный ввод
			ok = 1;
			printf("\n");
			printf("                                        ");
			SetColor(14, 0);
			PrintMessage("Введены некорректные данные");
			if ( c != '\n')
				while (getchar() != '\n');
		}
	} while (ok == 1);
	system("cls");
	switch (i)
	{
	case 1: 
		OutPutScreen(name, cnt_rec,rec);
		break;
	case 2:
		OutPutFile(name, cnt_rec,rec);
		break;
	}
	scanf("%c", &c);
	MenuTwo(name, cnt_rec);

}


//основная функция
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");


	char name[50] = {"InputData"};
	int cnt_rec = 0;
	

	Hellow(name);
	MenuOne(name, cnt_rec);
}


