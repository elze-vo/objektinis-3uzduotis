#ifndef UTILS_H
#define UTILS_H

#pragma
#include <vector>
#include <string>
#include "Studentas.h"

double calculateMedian(std::vector<int>& grades);
bool compareByResultsAscending(const Studentas& a, const Studentas& b);
bool compareByResultsDescending(const Studentas& a, const Studentas& b);
void printOrSaveResults(std::vector<Studentas>& studentai, int pasirinkimas, int outputOption);
void createStudentFile(int studentCount, int gradeCount, const std::string& fileName);
void processStudentData(std::vector<Studentas>& studentai);


#endif // UTILS_H
