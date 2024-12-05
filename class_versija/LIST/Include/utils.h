#ifndef UTILS_H
#define UTILS_H

#pragma once
#include <list>
#include <string>
#include "Studentas.h"

void demonstruotiTrisMetodus();

void correctInvalidData(int& rezultatas, const std::string& fieldName);

void skaitytiIsFailo(std::list<Studentas>& studentai, const std::string& fileName);

double calculateMedian(std::list<double>& grades);

double calculateFinalGrade(const Studentas& studentas, int pasirinkimas);

bool compareByResultsAscending(const Studentas& a, const Studentas& b);

bool compareByResultsDescending(const Studentas& a, const Studentas& b);

void printOrSaveResults(const std::list<Studentas>& studentai, int pasirinkimas, int outputOption);

void createStudentFile(int studentCount, int gradeCount, const std::string& fileName);

void processStudentData(std::list<Studentas>& studentai);

void writeResultsToFile(const std::list<Studentas>& studentai, const std::string& filename, int pasirinkimas);

#endif // UTILS_H
