#pragma once
#include "menu.h"
#include "Record.h"
#include "Journal.h"
#include <string>

using namespace std;

void Add(Journal& list);

void InputFile(Journal& list);

void InputKeyboard(Journal& list);

bool inputFileName(string& name);

void Delete(Journal& list);

void Change(Journal& list);

int CheckChoise(string s, int borderBeg, int borderEnd);

void Print(Journal list);

void Search(Journal list);

Journal Sort_mark(Journal list, int sort);

Journal Sort_discipline(Journal list, int sort);

Journal Sort_number(Journal list, int sort);

Journal Sort_fio(Journal list, int sort);

Journal Sort_group(Journal list, int sort);

Journal Sort_course(Journal list, int sort);

void AverangeValue(Journal list);

int Averange_discipline(Journal list);

int Averange_number(Journal list);

int Averange_fio(Journal list);

int Averange_group(Journal list);

int Averange_course(Journal list);

