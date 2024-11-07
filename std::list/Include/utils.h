#ifndef UTILS_H
#define UTILS_H

#include <list>
#include <string>
#include "Studentas.h"

double calculateMedian(std::list<int>& grades);
double calculateFinalGrade(const Studentas& studentas, int pasirinkimas);
bool compareByResultsAscending(const Studentas& a, const Studentas& b);
bool compareByResultsDescending(const Studentas& a, const Studentas& b);
void printOrSaveResults(std::list<Studentas>& studentai, int pasirinkimas, int outputOption);
void createStudentFile(int studentCount, int gradeCount, const std::string& fileName);
void processStudentData(std::list<Studentas>& studentai);
void writeResultsToFile(std::list<Studentas>& studentai, const std::string& filename, int pasirinkimas, int sortOption);

#endif // UTILS_H
