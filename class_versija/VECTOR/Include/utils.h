#ifndef UTILS_H
#define UTILS_H

#pragma once
#include <vector>
#include <string>
#include "Studentas.h"

void demonstruotiTrisMetodus();

void zmogusDemonstravimas();

void correctInvalidData(int& rezultatas, const std::string& fieldName);

void skaitytiIsFailo(std::vector<Studentas>& studentai, const std::string& fileName);

double calculateMedian(std::vector<double>& grades);

double calculateFinalGrade(const Studentas& studentas, int pasirinkimas);

bool compareByResultsAscending(const Studentas& a, const Studentas& b);

bool compareByResultsDescending(const Studentas& a, const Studentas& b);

void printOrSaveResults(const std::vector<Studentas>& studentai, int pasirinkimas, int outputOption);

void createStudentFile(int studentCount, int gradeCount, const std::string& fileName);

void processStudentData(std::vector<Studentas>& studentai);

void writeResultsToFile(const std::vector<Studentas>& studentai, const std::string& filename, int pasirinkimas);

#endif // UTILS_H
