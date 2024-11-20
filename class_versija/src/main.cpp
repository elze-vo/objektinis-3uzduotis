#include <iostream>
#include <numeric>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include <chrono>
#include <cmath>
#include "Studentas.h"
#include "Rezultatai.h"
#include "utils.h"
#include "student_input.h"
#include "strategijos.h"
#include "random_student_input.h"

using namespace std;
using namespace chrono;

int main() {
    vector<Studentas> studentai;
    int pasirinkimas;

    do {
        cout << "Pasirinkite veiksmus:\n";
        cout << "1 - Prideti studentus is failo\n";
        cout << "2 - Prideti studentus ranka\n";
        cout << "3 - Generuoti studentus atsitiktinai\n";
        cout << "4 - Sukurti studentu faila\n";
        cout << "5 - Testuoti programos greiti\n";
        cout << "Iveskite pasirinkima: ";
        cin >> pasirinkimas;

        if (cin.fail() || (pasirinkimas < 1 || pasirinkimas > 5)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
        else {
            cin.ignore();
            break;
        }
    } while (true);

    switch (pasirinkimas) {
    case 1: {
        string failoPavadinimas;
        ifstream inputFile;

        do {
            cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
            cin >> failoPavadinimas;

            inputFile.open(failoPavadinimas);
            if (!inputFile.is_open()) {
                cout << "Nepavyko atidaryti failo. Bandykite dar karta.\n";
            }
            else {
                inputFile.close();
                skaitytiIsFailo(studentai, failoPavadinimas);  // Assuming this uses getters/setters
                processStudentData(studentai);  // Process student data with proper getters/setters
                break;
            }
        } while (true);

        system("pause");

        break;
    }
    case 2: {
        addStudentsManually(studentai);  // Add students manually using setter methods
        processStudentData(studentai);   // Process the student data accordingly

        system("pause");
        break;
    }
    case 3: {
        addStudentsRandomly(studentai);  // Random student generation using getter/setter methods
        processStudentData(studentai);

        system("pause");
        break;
    }
    case 4: {
        int studentuKiekis, pazymiuKiekis;
        string failoPavadinimas;

        cout << "Iveskite studentu kieki: ";
        cin >> studentuKiekis;

        cout << "Iveskite pazymiu kieki: ";
        cin >> pazymiuKiekis;

        cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
        cin >> failoPavadinimas;

        createStudentFile(studentuKiekis, pazymiuKiekis, failoPavadinimas);

        system("pause");
        return 0;
    }
    case 5: {
        std::string failoPavadinimas;
        char pasirinkimasTestuoti;

        std::vector<Studentas> neislaike;
        std::vector<Studentas> islaike;

        do {
            std::cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
            std::cin >> failoPavadinimas;

            int gradeCalculationOption;
            do {
                std::cout << "Pasirinkite, kaip skaiciuoti galutini bala:\n";
                std::cout << "1 - Vidurkis\n";
                std::cout << "2 - Mediana\n";
                std::cout << "Iveskite pasirinkima: ";
                std::cin >> gradeCalculationOption;

                if (std::cin.fail() || (gradeCalculationOption < 1 || gradeCalculationOption > 2)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
                }
                else {
                    break;
                }
            } while (true);

            int strategyOption;
            do {
                std::cout << "Pasirinkite, kuria strategija naudoti studentu skaidymui:\n";
                std::cout << "1 - Strategija 1 (kopijuojant i du naujus vektorius)\n";
                std::cout << "2 - Strategija 2 (perkeliant 'neislaike' ir trinant is originalaus vektoriaus)\n";
                std::cout << "3 - Strategija 3 (naudojant std::partition)\n";
                std::cout << "4 - Lyginti visas strategijas\n";
                std::cout << "Iveskite pasirinkima: ";
                std::cin >> strategyOption;

                if (std::cin.fail() || (strategyOption < 1 || strategyOption > 4)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
                }
                else {
                    break;
                }
            } while (true);

            std::vector<Studentas> studentai;

            skaitytiIsFailo(studentai, failoPavadinimas);  // Uses the new getters/setters for data

            int sortOption;
            do {
                std::cout << "Pasirinkite rezultatu rikiavimo tvarka:\n";
                std::cout << "1 - Rikiuoti didejimo tvarka\n";
                std::cout << "2 - Rikiuoti mazejimo tvarka\n";
                std::cout << "Iveskite pasirinkima: ";
                std::cin >> sortOption;

                if (std::cin.fail() || (sortOption < 1 || sortOption > 2)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
                }
                else {
                    break;
                }
            } while (true);

            if (strategyOption == 4) {
                std::vector<Studentas> temp;

                for (auto& studentas : studentai) {
                    studentas.setFinalGrade(calculateFinalGrade(studentas, pasirinkimas));  // Set final grade using setter
                }

                for (int i = 1; i < 4; ++i) {
                    temp = studentai;

                    switch (i) {
                    case 1: strategija1(temp, neislaike, islaike); break;
                    case 2: strategija2(temp, neislaike); break;
                    case 3: strategija3(temp, neislaike); break;
                    }
                }
            }

            else {
                for (auto& studentas : studentai) {
                    studentas.setFinalGrade(calculateFinalGrade(studentas, pasirinkimas));  // Set final grade using setter
                }

                if (strategyOption == 1) {
                    strategija1(studentai, neislaike, islaike);
                    writeResultsToFile(neislaike, "neislaike.txt", pasirinkimas, sortOption);
                    writeResultsToFile(islaike, "islaike.txt", pasirinkimas, sortOption);
                }
                else if (strategyOption == 2) {
                    strategija2(studentai, neislaike);
                    writeResultsToFile(neislaike, "neislaike.txt", pasirinkimas, sortOption);
                    writeResultsToFile(studentai, "islaike.txt", pasirinkimas, sortOption);
                }
                else if (strategyOption == 3) {
                    strategija3(studentai, neislaike);
                    writeResultsToFile(neislaike, "neislaike.txt", pasirinkimas, sortOption);
                    writeResultsToFile(studentai, "islaike.txt", pasirinkimas, sortOption);
                }

            }

            std::cout << "Ar norite atidaryti kita faila greicio testavimui? (y/n): ";
            std::cin >> pasirinkimasTestuoti;

            while (pasirinkimasTestuoti != 'y' && pasirinkimasTestuoti != 'n') {
                std::cout << "Neteisingas pasirinkimas. Iveskite 'y' arba 'n': ";
                std::cin >> pasirinkimasTestuoti;
            }
            if (pasirinkimasTestuoti == 'y') {
                studentai.clear();
            }
        } while (pasirinkimasTestuoti == 'y');
        return 0;
    }
    }
    return 0;
}