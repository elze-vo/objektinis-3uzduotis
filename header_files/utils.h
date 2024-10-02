#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Studentas.h"

double calculateMedian(std::vector<int>& grades);
bool compareByLastName(const Studentas& a, const Studentas& b);
void printOrSaveResults(const std::vector<Studentas>& studentai, int pasirinkimas, std::ostream& out);

#endif // UTILS_H
