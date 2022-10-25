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

int CompareToCourse_jr( Journal a, Record b);

int CompareToGroup_jr(Journal a, Record b);

int CompareToFio_jr(Journal a, Record b);

int CompareToNumber_jr(Journal a, Record b);

int CompareToDiscipline_jr(Journal a, Record b);

int CompareToMark_jr(Journal a, Record b);

int CompareToCourse_jj( Journal a,  Journal b);

int CompareToGroup_jj(Journal a, Journal b);

int CompareToFio_jj(Journal a, Journal b);

int CompareToNumber_jj(Journal a, Journal b);

int CompareToDiscipline_jj(Journal a, Journal b);

int CompareToMark_jj(Journal a, Journal b);