#include "utils.h"
#include <iomanip>
#include <numeric>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Studentas.h"

using namespace std;

void demonstruotiTrisMetodus() {
    Studentas a;
    cin >> a;
    Studentas b;
    b = a;
    Studentas c(b);
    cout << a << "\n" << b << "\n" << c << endl;
}

void zmogusDemonstravimas() {
    cout << "\n";

    // Bandyti sukurti tiesiogini Zmogaus objekta yra neimanoma, nes klase abstrakti:
    //Zmogus zmogus;  // Sukelia kompiliavimo klaida

    // Sukuriamas Zmogaus tipo rodykles objektas, kuris rodo i Studento objekta
    Zmogus* zmogus = new Studentas("Vardenis", "Pavardenis");

    // Isvedami vardo ir pavardes duomenys naudojant getterius
    cout << zmogus->getVardas() << " " << zmogus->getPavarde() << endl;

    // Iskvieciamas virtualus metodas
    zmogus->printInfo();

    delete zmogus;
}

void correctInvalidData(int& rezultatas, const string& fieldName) {
    while (cin.fail() || rezultatas < 0 || rezultatas > 10 || rezultatas != static_cast<int>(rezultatas)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Neteisingas " << fieldName << ": " << rezultatas << ". Iveskite sveikaji skaiciu tarp 0 ir 10: ";
        cin >> rezultatas;
    }
}

void skaitytiIsFailo(std::vector<Studentas>& studentai, const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cout << "Nepavyko atidaryti failo: " << fileName << std::endl;
        return;
    }

    std::string line;
    getline(file, line);

    std::istringstream headerStream(line);
    std::string headerWord;
    int numHomework = 0;

    while (headerStream >> headerWord) {
        if (headerWord.find("ND") != std::string::npos) {
            numHomework++;
        }
    }

    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        std::istringstream studentStream(line);
        Studentas studentas;

        studentStream >> studentas;

        if (studentStream.fail()) {
            std::cout << "Klaida skaitant studento duomenis: " << line << std::endl;
            continue;
        }

        studentai.push_back(studentas);
    }

    file.close();
}

double calculateMedian(std::vector<double>& grades) {
    size_t size = grades.size();
    if (size == 0) return 0.0;

    size_t mid = size / 2;
    std::nth_element(grades.begin(), grades.begin() + mid, grades.end());

    if (size % 2 == 0) {
        double midValue1 = grades[mid];
        std::nth_element(grades.begin(), grades.begin() + mid - 1, grades.end());
        double midValue2 = grades[mid - 1];
        return (midValue1 + midValue2) / 2.0;
    }

    return grades[mid];
}

double calculateFinalGrade(const Studentas& studentas, int pasirinkimas) {
    if (pasirinkimas == 1) {
        const auto& grades = studentas.getNamuDarbuRezultatai();
        if (grades.empty()) return 0.0;
        double average = std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
        return 0.4 * average + 0.6 * studentas.getEgzaminoRezultatas();
    }
    else {
        auto grades = studentas.getNamuDarbuRezultatai();
        double median = calculateMedian(grades);
        return 0.4 * median + 0.6 * studentas.getEgzaminoRezultatas();
    }
}

bool compareByResultsAscending(const Studentas& a, const Studentas& b) {
    return a.getFinalGrade() < b.getFinalGrade();
}

bool compareByResultsDescending(const Studentas& a, const Studentas& b) {
    return a.getFinalGrade() > b.getFinalGrade();
}

void writeResultsToFile(const std::vector<Studentas>& studentai, const std::string& filename, int pasirinkimas) {
    std::ofstream outFile(filename);
    if (!outFile) {
        cout << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

    outFile << std::setw(15) << std::left << "Vardas"
        << std::setw(15) << "Pavarde"
        << std::setw(25) << "Vieta atmintyje"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    outFile << std::string(70, '-') << endl;

    for (const auto& studentas : studentai) {
        outFile << studentas << endl;
    }

    outFile.close();
}

void printOrSaveResults(const vector<Studentas>& studentai, int pasirinkimas, int outputOption) {
    vector<Studentas> islaike, neislaike;

    for (const auto& studentas : studentai) {
        if (studentas.getFinalGrade() >= 5.0) {
            islaike.push_back(studentas);
        }
        else {
            neislaike.push_back(studentas);
        }
    }

    if (!islaike.empty()) {
        if (outputOption == 1 || outputOption == 3) {
            cout << "Islaike studentai:" << endl;
            cout << std::setw(15) << std::left << "Vardas"
                << std::setw(15) << "Pavarde"
                << std::setw(25) << "Vieta atmintyje"
                << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
            cout << std::string(70, '-') << endl;

            for (const auto& studentas : islaike) {
                cout << studentas << endl;
            }
        }

        if (outputOption == 2 || outputOption == 3) {
            writeResultsToFile(islaike, "islaike.txt", pasirinkimas);
        }
    }

    if (!neislaike.empty()) {
        if (outputOption == 1 || outputOption == 3) {
            cout << "Neislaike studentai:" << endl;
            cout << std::setw(15) << std::left << "Vardas"
                << std::setw(15) << "Pavarde"
                << std::setw(25) << "Vieta atmintyje"
                << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
            cout << std::string(70, '-') << endl;

            for (const auto& studentas : neislaike) {
                cout << studentas << endl;
            }
        }

        if (outputOption == 2 || outputOption == 3) {
            writeResultsToFile(neislaike, "neislaike.txt", pasirinkimas);
        }
    }
}

void createStudentFile(int studentCount, int gradeCount, const std::string& fileName) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    ofstream outFile(fileName);
    if (!outFile) {
        cout << "Nepavyko sukurti failo: " << fileName << endl;
        return;
    }

    outFile << std::setw(15) << std::left << "Vardas"
        << std::setw(15) << "Pavarde";

    for (int i = 1; i <= gradeCount; ++i) {
        outFile << std::setw(8) << ("ND" + to_string(i));
    }
    outFile << std::setw(8) << "Egz." << endl;

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 1; i <= studentCount; ++i) {
        outFile << std::setw(15) << ("Vardas" + to_string(i))
            << std::setw(15) << ("Pavarde" + to_string(i));

        for (int j = 0; j < gradeCount; ++j) {
            outFile << std::setw(8) << (rand() % 10 + 1);
        }
        outFile << std::setw(8) << (rand() % 10 + 1) << endl;
    }

    outFile.close();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "Failas sukurtas: " << fileName << endl;
    cout << "Failo kurimo laikas: " << duration << " ms" << endl;
}

void processStudentData(vector<Studentas>& studentai) {
    int pasirinkimas, sortOption, outputOption;

    do {
        cout << "Pasirinkite balu skaiciavimo metoda\n1 - Vidurkis\n2 - Mediana\n";
        cin >> pasirinkimas;
    } while (pasirinkimas < 1 || pasirinkimas > 2);

    do {
        cout << "Pasirinkite rikiavimo buda:\n1 - Didejimo tvarka\n2 - Mazejimo tvarka\n";
        cin >> sortOption;
    } while (sortOption < 1 || sortOption > 2);

    do {
        cout << "Pasirinkite isvedimo buda:\n1 - Spausdinti\n2 - Issaugoti\n3 - Spausdinti ir issaugoti\n";
        cin >> outputOption;
    } while (outputOption < 1 || outputOption > 3);

    for (auto& studentas : studentai) {
        studentas.setFinalGrade(calculateFinalGrade(studentas, pasirinkimas));
    }

    if (sortOption == 1) {
        sort(studentai.begin(), studentai.end(), compareByResultsAscending);
    }
    else {
        sort(studentai.begin(), studentai.end(), compareByResultsDescending);
    }

    printOrSaveResults(studentai, pasirinkimas, outputOption);
}
