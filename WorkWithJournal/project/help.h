#pragma once
#include "Journal.h"
#include "Record.h"

int CompareToCourse(const Record a, int b);

int CompareToGroup(const Record a, int b);

int CompareToFio(const Record a, string b);

int CompareToNumber(const Record a, int b);

int CompareToDiscipline(const Record a, string b);

int CompareToMark(const Record a, int b);

int CompareToCourse(const Record a, const Record b);

int CompareToGroup(const Record a, const Record b);

int CompareToFio(const Record a, const Record b);

int CompareToNumber(const Record a, const Record b);

int CompareToDiscipline(const Record a, const Record b);

int CompareToMark(const Record a, const Record b);
