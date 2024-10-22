#include <iostream>
#include <numeric>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include <chrono>
#include "Studentas.h"
#include "Rezultatai.h"
#include "utils.h"
#include "student_input.h"
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
                skaitytiIsFailo(studentai, failoPavadinimas);
                processStudentData(studentai);
                break;
            }
        } while (true);

        break;
    }
    case 2: {
        addStudentsManually(studentai);
        processStudentData(studentai);
        break;
    }
    case 3: {
        addStudentsRandomly(studentai);
        processStudentData(studentai);
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
        return 0;
    }
    case 5: {
        string failoPavadinimas;
        char pasirinkimasTestuoti;

        do {
            cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
            cin >> failoPavadinimas;

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
                cout << "1 - Rikiuoti mazejimo tvarka\n";
                cout << "2 - Rikiuoti didejimo tvarka\n";
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

            auto startTotal = high_resolution_clock::now();

            auto startReading = high_resolution_clock::now();
            skaitytiIsFailo(studentai, failoPavadinimas);
            auto endReading = high_resolution_clock::now();
            auto readingDuration = duration_cast<milliseconds>(endReading - startReading).count();

            auto startSorting = high_resolution_clock::now();
            if (sortOption == 1) {
                sort(studentai.begin(), studentai.end(), compareByResultsDescending);
            }
            else {
                sort(studentai.begin(), studentai.end(), compareByResultsAscending);
            }
            auto endSorting = high_resolution_clock::now();
            auto sortingDuration = duration_cast<milliseconds>(endSorting - startSorting).count();

            auto startWriting = high_resolution_clock::now();
            printOrSaveResults(studentai, gradeCalculationOption, 2);
            auto endWriting = high_resolution_clock::now();
            auto writingDuration = duration_cast<milliseconds>(endWriting - startWriting).count();

            auto endTotal = high_resolution_clock::now();
            auto totalDuration = duration_cast<milliseconds>(endTotal - startTotal).count();

            cout << "Failas atidarytas: " << failoPavadinimas << "\n";
            cout << "Laikas nuskaitant faila: " << readingDuration << " ms\n";
            cout << "Laikas rikiuojant: " << sortingDuration << " ms\n";
            cout << "Laikas issaugant rezultatus: " << writingDuration << " ms\n";
            cout << "Bendras laikas: " << totalDuration << " ms\n";

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
    }

    return 0;
}
