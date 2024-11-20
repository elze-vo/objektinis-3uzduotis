#ifndef UTILS_H
#define UTILS_H

#pragma once
#include <vector>
#include <string>
#include "Studentas.h"

// Function to calculate the median of a list of grades
double calculateMedian(std::vector<double>& grades);

// Function to calculate the final grade for a student
double calculateFinalGrade(const Studentas& studentas, int pasirinkimas);

// Comparison function to sort by results in ascending order
bool compareByResultsAscending(const Studentas& a, const Studentas& b);

// Comparison function to sort by results in descending order
bool compareByResultsDescending(const Studentas& a, const Studentas& b);

// Function to print or save results
void printOrSaveResults(std::vector<Studentas>& studentai, int pasirinkimas, int outputOption);

// Function to create a student file with random data
void createStudentFile(int studentCount, int gradeCount, const std::string& fileName);

// Function to process student data (calculate grades, etc.)
void processStudentData(std::vector<Studentas>& studentai);

// Function to write results to a file
void writeResultsToFile(std::vector<Studentas>& studentai, const std::string& filename, int pasirinkimas, int sortOption);

#endif // UTILS_H
