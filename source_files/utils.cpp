#include "utils.h"
#include <iomanip>
#include <numeric>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

double calculateMedian(vector<double>& grades) {
    sort(grades.begin(), grades.end());
    size_t size = grades.size();
    if (size == 0) return 0.0;
    if (size % 2 == 0) {
        return (grades[size / 2 - 1] + grades[size / 2]) / 2.0;
    }
    return grades[size / 2];
}

double calculateFinalGrade(const Studentas& studentas, int pasirinkimas) {
    if (pasirinkimas == 1) {
        if (studentas.rezultatai.namuDarbuRezultatai.empty()) {
            return 0.0;
        }
        double namuDarbuVidurkis = std::accumulate(studentas.rezultatai.namuDarbuRezultatai.begin(), studentas.rezultatai.namuDarbuRezultatai.end(), 0.0) / studentas.rezultatai.namuDarbuRezultatai.size();
        return 0.4 * namuDarbuVidurkis + 0.6 * studentas.rezultatai.egzaminoRezultatas;
    }
    else {
        std::vector<double> namuDarbuCopy = studentas.rezultatai.namuDarbuRezultatai;
        double namuDarbuMediana = calculateMedian(namuDarbuCopy);
        return 0.4 * namuDarbuMediana + 0.6 * studentas.rezultatai.egzaminoRezultatas;
    }
}

bool compareByResultsAscending(const Studentas& a, const Studentas& b) {
    return calculateFinalGrade(a, 1) < calculateFinalGrade(b, 1);
}

bool compareByResultsDescending(const Studentas& a, const Studentas& b) {
    return calculateFinalGrade(a, 1) > calculateFinalGrade(b, 1);
}

void printOrSaveResults(std::vector<Studentas>& studentai, int pasirinkimas, int outputOption) {
    if (pasirinkimas == 1) {
        std::sort(studentai.begin(), studentai.end(), compareByResultsAscending);
    }
    else {
        std::sort(studentai.begin(), studentai.end(), compareByResultsDescending);
    }

    std::ofstream neislaikeFile("neislaike.txt");
    std::ofstream islaikeFile("islaike.txt");

    neislaikeFile << "\n" << std::setw(15) << std::left << "Vardas"
        << std::setw(15) << std::left << "Pavarde"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;
    neislaikeFile << std::string(50, '-') << std::endl;

    islaikeFile << "\n" << std::setw(15) << std::left << "Vardas"
        << std::setw(15) << std::left << "Pavarde"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;
    islaikeFile << std::string(50, '-') << std::endl;

    for (const auto& studentas : studentai) {
        double galutinisVid = calculateFinalGrade(studentas, pasirinkimas);

        if (galutinisVid < 5.0) {
            neislaikeFile << std::setw(15) << std::left << studentas.vardas
                << std::setw(15) << std::left << studentas.pavarde
                << fixed << setprecision(2) << galutinisVid << std::endl;

            if (outputOption == 1 || outputOption == 3) {
                std::cout << std::setw(15) << std::left << studentas.vardas
                    << std::setw(15) << std::left << studentas.pavarde
                    << fixed << setprecision(2) << galutinisVid << std::endl;
            }
        }
        else {
            islaikeFile << std::setw(15) << std::left << studentas.vardas
                << std::setw(15) << std::left << studentas.pavarde
                << fixed << setprecision(2) << galutinisVid << std::endl;

            if (outputOption == 1 || outputOption == 3) {
                std::cout << std::setw(15) << std::left << studentas.vardas
                    << std::setw(15) << std::left << studentas.pavarde
                    << fixed << setprecision(2) << galutinisVid << std::endl;
            }
        }
    }

    neislaikeFile.close();
    islaikeFile.close();
}

void createStudentFile(int studentCount, int gradeCount, const std::string& fileName) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    ofstream outFile(fileName);
    if (!outFile) {
        cout << "Nepavyko sukurti failo: " << fileName << endl;
        return;
    }

    outFile << left << setw(20) << "Vardas" << setw(20) << "Pavarde";

    for (int i = 1; i <= gradeCount; ++i) {
        outFile << setw(10) << "ND" + to_string(i);
    }
    outFile << setw(10) << "Egz." << endl;

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 1; i <= studentCount; ++i) {
        outFile << left << setw(20) << ("Vardas" + to_string(i)) << setw(20) << ("Pavarde" + to_string(i));

        for (int j = 0; j < gradeCount; ++j) {
            outFile << setw(10) << (rand() % 10 + 1);
        }

        outFile << setw(10) << (rand() % 10 + 1);
        outFile << endl;
    }

    outFile.close();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "Failas sukurtas: " << fileName << endl;
    cout << "Failo kurimo laikas: " << duration << " ms" << endl;
}
