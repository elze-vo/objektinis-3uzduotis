#include <iostream>
#include <numeric>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include "Studentas.h"
#include "Rezultatai.h"
#include "utils.h"
#include "student_input.h"
#include "random_student_input.h"

using namespace std;

int main() {
    vector<Studentas> studentai;
    int pasirinkimas;

    do {
        cout << "Pasirinkite veiksmus:\n";
        cout << "1 - Prideti studentus is failo\n";
        cout << "2 - Prideti studentus ranka\n";
        cout << "3 - Generuoti studentus atsitiktinai\n";
        cout << "Iveskite pasirinkima: ";
        cin >> pasirinkimas;

        if (cin.fail() || (pasirinkimas < 1 || pasirinkimas > 3)) {
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
                break;
            }
        } while (true);

        break;
    }
    case 2: {
        addStudentsManually(studentai);
        break;
    }
    case 3: {
        addStudentsRandomly(studentai);
        break;
    }
    }

    if (studentai.empty()) {
        cout << "Nera studentu.\n";
        return 1;
    }

    do {
        cout << "Pasirinkite (1 - Vidurkis, 2 - Mediana): ";
        cin >> pasirinkimas;

        if (cin.fail() || (pasirinkimas != 1 && pasirinkimas != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
        else {
            break;
        }
    } while (true);

    sort(studentai.begin(), studentai.end(), compareByLastName);

    int outputOption;
    do {
        cout << "Pasirinkite rezultatu atvaizdavimo buda:\n";
        cout << "1 - Spausdinti ekrane\n";
        cout << "2 - Issaugoti faile\n";
        cout << "3 - Spausdinti ir issaugoti faile\n";
        cout << "Iveskite pasirinkima: ";
        cin >> outputOption;

        if (cin.fail() || (outputOption < 1 || outputOption > 3)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
        else {
            break;
        }
    } while (true);

    string fileName;
    ofstream outputFile;

    if (outputOption == 2 || outputOption == 3) {
        cout << "Iveskite failo pavadinima: ";
        cin >> fileName;
        outputFile.open(fileName);

        if (!outputFile.is_open()) {
            cout << "Nepavyko atidaryti failo.\n";
            return 1;
        }
    }

    if (outputOption == 1) {
        printOrSaveResults(studentai, pasirinkimas, cout);
    }
    else if (outputOption == 2) {
        printOrSaveResults(studentai, pasirinkimas, outputFile);
        outputFile.close();
        cout << "Rezultatai issaugoti faile: " << fileName << endl;
    }
    else if (outputOption == 3) {
        printOrSaveResults(studentai, pasirinkimas, cout);
        printOrSaveResults(studentai, pasirinkimas, outputFile);
        outputFile.close();
        cout << "Rezultatai issaugoti faile: " << fileName << endl;
    }

    return 0;
}
