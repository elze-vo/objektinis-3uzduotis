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

using namespace std;


double calculateMedian(std::list<double>& grades) {
    grades.sort();
    size_t size = grades.size();
    if (size == 0) return 0.0;

    auto it = std::next(grades.begin(), size / 2);

    if (size % 2 == 0) {
        auto itPrev = std::prev(it);
        return (*it + *itPrev) / 2.0;
    }
    return *it;
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
        std::list<double> namuDarbuCopy = studentas.rezultatai.namuDarbuRezultatai;
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

void printOrSaveResults(std::list<Studentas>& studentai, int pasirinkimas, int outputOption) {
    if (pasirinkimas == 1) {
        studentai.sort(compareByResultsAscending);
    }
    else {
        studentai.sort(compareByResultsDescending);
    }

    std::ofstream neislaikeFile("neislaike.txt");
    std::ofstream islaikeFile("islaike.txt");

    neislaikeFile << "\n" << std::setw(15) << std::left << "Vardas"
        << std::setw(15) << std::left << "Pavarde"
        << std::setw(20) << std::left << "Vieta atmintyje"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;
    neislaikeFile << std::string(70, '-') << std::endl;

    islaikeFile << "\n" << std::setw(15) << std::left << "Vardas"
        << std::setw(15) << std::left << "Pavarde"
        << std::setw(20) << std::left << "Vieta atmintyje"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;
    islaikeFile << std::string(70, '-') << std::endl;

    if (outputOption == 1 || outputOption == 3) {
        std::cout << "\n" << std::setw(15) << std::left << "Vardas"
            << std::setw(15) << std::left << "Pavarde"
            << std::setw(20) << std::left << "Vieta atmintyje"
            << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;
        std::cout << std::string(70, '-') << std::endl;
    }

    for (const auto& studentas : studentai) {
        double galutinisVid = calculateFinalGrade(studentas, pasirinkimas);

        if (galutinisVid < 5.0) {
            neislaikeFile << std::setw(15) << std::left << studentas.vardas
                << std::setw(15) << std::left << studentas.pavarde
                << std::setw(20) << std::left << &studentas
                << fixed << setprecision(2) << galutinisVid << std::endl;

            if (outputOption == 1 || outputOption == 3) {
                std::cout << std::setw(15) << std::left << studentas.vardas
                    << std::setw(15) << std::left << studentas.pavarde
                    << std::setw(20) << std::left << &studentas
                    << fixed << setprecision(2) << galutinisVid << std::endl;
            }
        }
        else {
            islaikeFile << std::setw(15) << std::left << studentas.vardas
                << std::setw(15) << std::left << studentas.pavarde
                << std::setw(20) << std::left << &studentas
                << fixed << setprecision(2) << galutinisVid << std::endl;

            if (outputOption == 1 || outputOption == 3) {
                std::cout << std::setw(15) << std::left << studentas.vardas
                    << std::setw(15) << std::left << studentas.pavarde
                    << std::setw(20) << std::left << &studentas
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

void processStudentData(list<Studentas>& studentai) {
    int gradeCalculationOption;
    do {
        cout << "Pasirinkite, kaip skaiciuoti galutini bala:\n";
        cout << "1 - Vidurkis\n";
        cout << "2 - Mediana\n";
        cout << "Iveskite pasirinkima: ";
        cin >> gradeCalculationOption;

        if (cin.fail() || (gradeCalculationOption < 1 || gradeCalculationOption > 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
        else {
            break;
        }
    } while (true);

    int sortOption;
    do {
        cout << "Pasirinkite rezultatu rikiavimo tvarka:\n";
        cout << "1 - Rikiuoti didejimo tvarka\n";
        cout << "2 - Rikiuoti mazejimo tvarka\n";
        cout << "Iveskite pasirinkima: ";
        cin >> sortOption;

        if (cin.fail() || (sortOption < 1 || sortOption > 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
        else {
            break;
        }
    } while (true);

    int outputOption;
    do {
        cout << "Pasirinkite isvedimo buda:\n";
        cout << "1 - Spausdinti i ekrana\n";
        cout << "2 - Issaugoti i failus\n";
        cout << "3 - Spausdinti i ekrana ir issaugoti i failus\n";
        cout << "Iveskite pasirinkima: ";
        cin >> outputOption;

        if (cin.fail() || (outputOption < 1 || outputOption > 3)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
        else {
            if (outputOption == 2 || outputOption == 3) {
                cout << "Rezultatai issaugoti failuose islaike.txt ir neislaike.txt.\n";
            }
            break;
        }
    } while (true);

    if (sortOption == 1) {
        studentai.sort(compareByResultsDescending);
    }
    else {
        studentai.sort(compareByResultsAscending);
    }

    printOrSaveResults(studentai, gradeCalculationOption, outputOption);
}
