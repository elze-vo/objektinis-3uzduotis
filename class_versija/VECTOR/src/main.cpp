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
        cout << "6 - Demonstruoti tris metodus\n";
        cout << "Iveskite pasirinkima: ";
        cin >> pasirinkimas;

        if (cin.fail() || (pasirinkimas < 1 || pasirinkimas > 6)) {
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
                skaitytiIsFailo(studentai, failoPavadinimas);
                processStudentData(studentai);
                break;
            }
        } while (true);

        system("pause");
        break;
    }

    case 2: {
        addStudentsManually(studentai);
        processStudentData(studentai);

        system("pause");
        break;
    }

    case 3: {
        addStudentsRandomly(studentai);
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
        string failoPavadinimas;
        char pasirinkimasTestuoti;

        vector<Studentas> neislaike;
        vector<Studentas> islaike;

        do {
            cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
            cin >> failoPavadinimas;

            int strategyOption;
            do {
                cout << "Pasirinkite, kuria strategija naudoti studentu skaidymui:\n";
                cout << "1 - Strategija 1 (kopijuojant i du naujus vektorius)\n";
                cout << "2 - Strategija 2 (perkeliant 'neislaike' ir trinant is originalaus vektoriaus)\n";
                cout << "3 - Strategija 3 (naudojant std::partition)\n";
                cout << "4 - Lyginti visas strategijas\n";
                cout << "Iveskite pasirinkima: ";
                cin >> strategyOption;

                if (cin.fail() || (strategyOption < 1 || strategyOption > 4)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
                }
                else {
                    break;
                }
            } while (true);

            vector<Studentas> studentai;

            skaitytiIsFailo(studentai, failoPavadinimas);

            processStudentData(studentai);

            if (strategyOption == 4) {
                std::vector<Studentas> temp;

                for (auto& studentas : studentai) {
                    studentas.setFinalGrade(calculateFinalGrade(studentas, pasirinkimas));
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
                    studentas.setFinalGrade(calculateFinalGrade(studentas, pasirinkimas));
                }

                if (strategyOption == 1) {
                    strategija1(studentai, neislaike, islaike);
                    writeResultsToFile(neislaike, "neislaike.txt", pasirinkimas);
                    writeResultsToFile(islaike, "islaike.txt", pasirinkimas);
                }
                else if (strategyOption == 2) {
                    strategija2(studentai, neislaike);
                    writeResultsToFile(neislaike, "neislaike.txt", pasirinkimas);
                    writeResultsToFile(studentai, "islaike.txt", pasirinkimas);
                }
                else if (strategyOption == 3) {
                    strategija3(studentai, neislaike);
                    writeResultsToFile(neislaike, "neislaike.txt", pasirinkimas);
                    writeResultsToFile(studentai, "islaike.txt", pasirinkimas);
                }

            }
            cout << "Ar norite atidaryti kita faila greicio testavimui? (y/n): ";
            cin >> pasirinkimasTestuoti;

            while (pasirinkimasTestuoti != 'y' && pasirinkimasTestuoti != 'n') {
                cout << "Neteisingas pasirinkimas. Iveskite 'y' arba 'n': ";
                cin >> pasirinkimasTestuoti;
            }

            if (pasirinkimasTestuoti == 'y') {
                studentai.clear();
            }
        } while (pasirinkimasTestuoti == 'y');
        return 0;
    }

    case 6: {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        demonstruotiTrisMetodus();
        system("pause");
        break;
    }
    }

    return 0;
}
