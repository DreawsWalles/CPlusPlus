#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#define N 100
#define max_str 500
#define M 50
#define n 100



void zadacha1(FILE * FileIn, FILE * FileOut);
void zadacha2(FILE* FileIn, FILE* FileOut);
void zadacha3(FILE* FileIn, FILE* FileOut);
void zadacha4(FILE* FileIn, FILE* FileOut);
void zadacha5(FILE* FileIn, FILE* FileOut);
int OutputFileToConsole(const char* fileName);
void Task(char* inputFileName, char* outputFileName);
void ExecuteTask(char* inputFileName, char* outputFileName, int i);

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Rus");
    if (argc <= 1)
    {
        printf("Program arguments:\n");
        printf("--help\n");
        printf("[file name] --print\n");
        printf("[file to read] --task [file to write]\n");
        return 0;
    }
    if (!strcmp(argv[1], "--help"))
    {
        OutputFileToConsole("help.txt");
    }
    else
        if (!strcmp(argv[2], "--print"))
            OutputFileToConsole(argv[1]);
        else if (!strcmp(argv[2], "--task"))
            Task(argv[1], argv[3]);
        else
            printf("Unknown parameter: '%s'. Type %s --help for help.\n", argv[1], argv[3]);

    return 0;
}

int OutputFileToConsole(const char* fileName)
{
    FILE* file;
    char arr[N];
    file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Cannot open help file\n");
        return 0;
    }
    while (fgets(arr, N, file) != NULL)
        printf("%s", arr);
    fclose(file);
}


void Task(char* inputFileName, char* outputFileName)
{
    int i;
    printf("--1.Вывести самую длинную строку.\n");
    printf("--2.Для каждой строки вывести количество слов в ней.\n");
    printf("--3.Удвоить все гласные.\n");
    printf("--4.Посчитать и вывести количество слов таких же, как первое слово первой строки файла.\n");
    printf("--5.Заменить все вхождения первого слова первой строки файла на первую букву этого слова.\n");
    printf("--6.Завершить работу программы.\n");
    do
    {
        printf("Введите нужное действие: ");
        scanf("%d", &i);
    } while ((i < 1) || (i > 6));
        if (i != 6)
            ExecuteTask(inputFileName, outputFileName, i);
}

void ExecuteTask(char* inputFileName, char* outputFileName, int i)
{
    FILE* FileIn, * FileOut;
    FileIn = fopen(inputFileName, "r");		//открытие файла
    FileOut = fopen(outputFileName, "w+");
    if (FileIn == NULL)		//проверка на коррекность открытия файла. fopen возвращает 0, если файл не удалось открыть
        printf("Файл для чтения не найден\n");
    else
    {
        if (FileOut == NULL)
            printf("Файл для записи не найден\n");
        else
        {
            printf("Файл для чтения и записи открыты\n");
            printf("\n");
            switch (i)
            {
            case 1:
                zadacha1(FileIn, FileOut);
                break;
            case 2:
                zadacha2(FileIn, FileOut);
                break;
            case 3:
                zadacha3(FileIn, FileOut);
                break;
            case 4:
                zadacha4(FileIn, FileOut);
                break;
            case 5:
                zadacha5(FileIn, FileOut);
                break;
            }
            fclose(FileOut);
        }
        fclose(FileIn);
        printf("Файлы для чтения и записи закрыты\n");
        printf("\n");
    }
    Task(inputFileName, outputFileName);
}

void zadacha1(FILE* FileIn, FILE* FileOut) //программа на вывод самой длинной строки
{
    char line[max_str];
    int maxLen = -1;
    char ImWords[max_str] = " ";
    int strLen = 0;
    while (!feof(FileIn))
    {
        fgets(line, max_str, FileIn);
        strLen = strlen(line);
        if (strLen > maxLen)
        {
            maxLen = strLen;
            memset(ImWords, 0, max_str);
            strcpy(ImWords, line);
        }
    }
    fprintf(FileOut, "Самая длинная строка в файле: %s", ImWords);
    printf("Самая длинная строка в файле: %s", ImWords);
    printf("\n");
}


void zadacha2(FILE* FileIn, FILE* FileOut)  //Вывод количества строк в столбцах
{
    char line[max_str];
    int kol[n];
    int j = 0;
    while (!feof(FileIn) && (fgets(line, max_str, FileIn)))
    {
        char* pch = strtok(line, " ,.-\n");
        int i = 0;
        while (pch != NULL)
        {
            i++;
            pch = strtok(NULL, " ,.-\n");
        }
        kol[j] = i;
        j++;
    }
    printf("Количество слов в строчках: \n");
    for (int i = 0; i < j; i++)
    {   
        fprintf(FileOut, "%d\n", kol[i]);
        printf("%d.%d\n", i+1, kol[i]);
    }
    printf("\n");
}

void zadacha3(FILE* FileIn, FILE* FileOut)		//удвоение всех гласных
{
    char str[7] = "aeuioy";
    char str2[7] = "AEUIOY";
    char c;
    printf("Полученный текст: \n");
    while ((c = fgetc(FileIn)) && (!feof(FileIn)))
    {
        int i = 0;
        int ok = 0;
        while ((ok == 0) && (i < 6))
            if ((c == str[i]) || (c == str2[i]))
                ok = 1;
            else
                i++;
        if (ok == 0)
        {
            fputc(c, FileOut);
            printf("%c", c);
        }
        else
        {
            fputc(c, FileOut);
            fputc(c, FileOut);
            printf("%c", c);
            printf("%c", c);
        }
    }
    printf("\n");
}
void zadacha4(FILE* FileIn, FILE* FileOut)			//подсчет повторов первого слова
{
    char s1[n];
    char line[max_str];
    int i = 0;
    fscanf(FileIn, "%s", s1);
    while (!feof(FileIn))
    {
        fgets(line, max_str, FileIn);
        char* pch = strtok(line, " ,.-\n");
        while (pch != NULL)
        {
            if (strcmp(s1, pch) == 0)
            {
                i++;
                pch = strtok(NULL, " ,.-\n");
            }
            else
                pch = strtok(NULL, " ,.-\n");
        }
    }
    fprintf(FileOut, "%d", i);
    printf("Количество повторов первого слова: %d\n", i);
    printf("\n");
  
}

void zadacha5(FILE* FileIn, FILE* FileOut) //замена слов, которые равны первому, первой буквой первого слова
{
    char s1[n];
    char line[max_str];
    char c;
    fscanf(FileIn, "%s", s1);
    printf("Полученный текст: \n");
    printf("\n");
    printf("%s ", s1);
    c = s1[0];
    fprintf(FileOut, "%s", s1);
    while (!feof(FileIn))
    {
        fgets(line, max_str, FileIn);
        char* pch = strtok(line, " ,.-\n");
        while (pch != NULL)
        {
            if (strcmp(s1, pch) == 0)
            {
                fprintf(FileOut, "%c ", c);
                printf("%c ", c);
            }
                
            else
            {
                fprintf(FileOut, "%s ", pch);
                printf("%s", pch);
            }
            pch = strtok(NULL, " ,.-\n");
        }
        fprintf(FileOut, "\n");
        printf("\n");
    }
    printf("\n");
}
