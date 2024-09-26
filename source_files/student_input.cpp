#include "student_input.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

void addStudentsManually(vector<Studentas>& studentai) {
    int numberOfStudents;
    cout << "Iveskite studentu kieki: ";
    cin >> numberOfStudents;
    cin.ignore();

    for (int i = 0; i < numberOfStudents; ++i) {
        Studentas studentas;
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        cin >> studentas.vardas;
        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        cin >> studentas.pavarde;
        cin.ignore();

        cout << "Iveskite namu darbu rezultatus (spauskite Enter dukart norint baigti): " << endl;
        string input;

        while (true) {
            cout << "Namu darbas: ";
            getline(cin, input);

            if (input.empty()) {
                if (!studentas.rezultatai.namuDarbuRezultatai.empty()) {
                    break;
                }
            }
            else {
                try {
                    int grade = stoi(input);
                    if (grade < 0 || grade > 10) {
                        cout << "Namu darbas turi buti tarp 0 ir 10. Bandykite dar karta." << endl;
                    }
                    else {
                        studentas.rezultatai.namuDarbuRezultatai.push_back(grade);
                    }
                }
                catch (invalid_argument&) {
                    cout << "Ivedete neteisinga reiksme. Bandykite dar karta." << endl;
                }
                catch (out_of_range&) {
                    cout << "Ivedete reiksme, kuri yra per didele. Bandykite dar karta." << endl;
                }
            }
        }

        cout << "Iveskite egzamino rezultata: ";
        while (true) {
            string examInput;
            cin >> examInput;

            try {
                studentas.rezultatai.egzaminoRezultatas = stoi(examInput);
                if (studentas.rezultatai.egzaminoRezultatas < 0 || studentas.rezultatai.egzaminoRezultatas > 10) {
                    cout << "Egzamino rezultatas turi buti tarp 0 ir 10. Bandykite dar karta: ";
                }
                else {
                    break;
                }
            }
            catch (invalid_argument&) {
                cout << "Ivedete neteisinga reiksme. Bandykite dar karta." << endl;
            }
            catch (out_of_range&) {
                cout << "Ivedete reiksme, kuri yra per didele. Bandykite dar karta." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        studentai.push_back(studentas);
    }
}
