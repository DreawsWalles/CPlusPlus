#pragma once
#include "disciplines.h"
#include "menu.h"
#include "Record.h"
#include "Journal.h"
#include <string>
#include "Guide.h"

using namespace std;

void AddDiscipline(disciplines& dis);

void ChangeDiscipline(disciplines& dis);

void DeleteDiscipline(disciplines& dis);

void PrintDiscipline(disciplines dis);

void CorrectDisciplines(disciplines& dis);

menu* getmenuDis(int size);

void InputElement(disciplines& dis, Guide& list);

Journal InputFile(disciplines& dis);

Record InputKeyboard(disciplines& dis);

bool inputFileName(string& name);

void PrintOnScreen(Guide list);

void PrintInFile(Guide list);

void Print(Guide list);

int CheckChoise(string s, int borderBeg, int borderEnd);

void Change(Guide& list);

Journal ChangeElement(Journal tmp);

void Delete(Guide& list);

Journal DeleteElement(Journal tmp);

void PrintResultSessions(Guide list, disciplines dis);

Guide Sort_dis(Guide tmp, int sort, disciplines dis);

Guide Sort_group(Guide tmp, int sort);

Guide Sort_curs(Guide tmp, int sort);

void Print_With_Filter(Guide list, disciplines dis);

Guide Sort_AverangeMark(Guide list);

Guide Sort_mark(Guide list, int sort);

Guide Sort_number(Guide list, int sort);

