#include "utils.h"
#include <iomanip>
#include <numeric>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Studentas.h"

using namespace std;

double calculateMedian(const list<double>& grades) {
    if (grades.empty()) return 0.0;

    list<double> sortedGrades = grades;
    sortedGrades.sort();
    size_t size = sortedGrades.size();
    auto it = sortedGrades.begin();
    advance(it, size / 2);

    if (size % 2 == 0) {
        auto itPrev = prev(it);
        return (*itPrev + *it) / 2.0;
    }
    return *it;
}

double calculateFinalGrade(const Studentas& studentas, int pasirinkimas) {
    const auto& ndRezultatai = studentas.getRezultatai().getNamuDarbuRezultatai();
    double egzRezultatas = studentas.getRezultatai().getEgzaminoRezultatas();

    if (pasirinkimas == 1) {
        if (ndRezultatai.empty()) return 0.0;
        double vidurkis = accumulate(ndRezultatai.begin(), ndRezultatai.end(), 0.0) / ndRezultatai.size();
        return 0.4 * vidurkis + 0.6 * egzRezultatas;
    }
    else {
        double mediana = calculateMedian(ndRezultatai);
        return 0.4 * mediana + 0.6 * egzRezultatas;
    }
}

bool compareByResultsAscending(const Studentas& a, const Studentas& b) {
    return a.getFinalGrade() < b.getFinalGrade();
}

bool compareByResultsDescending(const Studentas& a, const Studentas& b) {
    return a.getFinalGrade() > b.getFinalGrade();
}

void writeResultsToFile(list<Studentas>& studentai, const string& filename, int sortOption) {
    if (sortOption == 1) {
        studentai.sort(compareByResultsAscending);
    }
    else {
        studentai.sort(compareByResultsDescending);
    }

    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Nepavyko sukurti failo: " << filename << endl;
        return;
    }

    outFile << setw(15) << left << "Vardas"
        << setw(15) << left << "Pavarde"
        << "Galutinis (Vid./Med.)" << endl;
    outFile << string(50, '-') << endl;

    for (const auto& studentas : studentai) {
        outFile << setw(15) << left << studentas.getVardas()
            << setw(15) << left << studentas.getPavarde()
            << fixed << setprecision(2) << studentas.getFinalGrade() << endl;
    }

    outFile.close();
    cout << "Rezultatai issaugoti faile: " << filename << endl;
}


void printOrSaveResults(list<Studentas>& studentai, int sortOption, int outputOption) {
    if (sortOption == 1) {
        studentai.sort(compareByResultsAscending);
    }
    else if (sortOption == 2) {
        studentai.sort(compareByResultsDescending);
    }

    if (outputOption == 1 || outputOption == 3) {
        cout << setw(15) << left << "Vardas"
            << setw(15) << left << "Pavarde"
            << setw(15) << left << "Adresas atmintyje"
            << "Galutinis (Vid./Med.)" << endl;
        cout << string(50, '-') << endl;

        for (const auto& studentas : studentai) {
            cout << setw(15) << left << studentas.getVardas()
                << setw(15) << left << studentas.getPavarde()
                << setw(20) << left << &studentas
                << fixed << setprecision(2) << studentas.getFinalGrade() << endl;
        }
    }

    if (outputOption == 2 || outputOption == 3) {
        writeResultsToFile(studentai, "rezultatai.txt", sortOption);
    }
}


void createStudentFile(int studentCount, int gradeCount, const string& fileName) {
    using namespace chrono;

    auto start = high_resolution_clock::now();
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Nepavyko sukurti failo: " << fileName << endl;
        return;
    }

    outFile << setw(20) << left << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= gradeCount; ++i) {
        outFile << "ND" << i << " ";
    }
    outFile << "Egz." << endl;

    srand(static_cast<unsigned>(time(0)));
    for (int i = 1; i <= studentCount; ++i) {
        outFile << setw(20) << left << "Vardas" + to_string(i)
            << setw(20) << "Pavarde" + to_string(i);
        for (int j = 0; j < gradeCount; ++j) {
            outFile << rand() % 10 + 1 << " ";
        }
        outFile << rand() % 10 + 1 << endl;
    }

    outFile.close();
    auto end = high_resolution_clock::now();
    cout << "Failas sukurtas: " << fileName << endl;
    cout << "Failo kurimo laikas: "
        << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
}

void processStudentData(list<Studentas>& studentai) {
    int sortOption, outputOption;

    do {
        cout << "Pasirinkite rikiavimo tvarka (1 - Didejimo, 2 - Mazejimo): ";
        cin >> sortOption;
    } while (sortOption < 1 || sortOption > 2);

    do {
        cout << "Pasirinkite isvedimo buda (1 - Ekranas, 2 - Failas, 3 - Abu): ";
        cin >> outputOption;
    } while (outputOption < 1 || outputOption > 3);

    printOrSaveResults(studentai, sortOption, outputOption);
}
