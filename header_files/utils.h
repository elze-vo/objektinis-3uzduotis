#ifndef UTILS_H
#define UTILS_H

#pragma
#include <vector>
#include "Studentas.h"

double calculateMedian(std::vector<int>& grades);
bool compareByResultsAscending(const Studentas& a, const Studentas& b);
bool compareByResultsDescending(const Studentas& a, const Studentas& b);
void printOrSaveResults(std::vector<Studentas>& studentai, int pasirinkimas, int outputOption);


#endif // UTILS_H
