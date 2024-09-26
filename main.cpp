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

    cout << "\n" << setw(15) << left << "Vardas"
        << setw(15) << left << "Pavarde"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;

    cout << string(50, '-') << endl;

    cout << fixed << setprecision(2);
    for (const auto& studentas : studentai) {
        double galutinisVid;
        if (pasirinkimas == 1) {
            double namuDarbuVidurkis = accumulate(studentas.rezultatai.namuDarbuRezultatai.begin(), studentas.rezultatai.namuDarbuRezultatai.end(), 0.0) / studentas.rezultatai.namuDarbuRezultatai.size();
            galutinisVid = 0.4 * namuDarbuVidurkis + 0.6 * studentas.rezultatai.egzaminoRezultatas;
        }
        else {
            vector<int> namuDarbuCopy = studentas.rezultatai.namuDarbuRezultatai;
            double namuDarbuMediana = calculateMedian(namuDarbuCopy);
            galutinisVid = 0.4 * namuDarbuMediana + 0.6 * studentas.rezultatai.egzaminoRezultatas;
        }

        cout << setw(15) << left << studentas.vardas
            << setw(15) << left << studentas.pavarde
            << galutinisVid << endl;
    }

    return 0;
}
