#include "student_input.h"
#include <iostream>
#include <string>
#include <list>
#include <stdexcept>
#include <limits>
using namespace std;

void addStudentsManually(list<Studentas>& studentai) {
    int numberOfStudents;
    while (true) {
        cout << "Iveskite studentu kieki (didesnis uz 0): ";
        cin >> numberOfStudents;
        if (cin.fail() || numberOfStudents <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas ivestis. Bandykite dar karta.\n";
        }
        else {
            cin.ignore();
            break;
        }
    }

    for (int i = 0; i < numberOfStudents; ++i) {
        Studentas studentas;
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        string vardas;
        cin >> vardas;
        studentas.setVardas(vardas);

        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        string pavarde;
        cin >> pavarde;
        studentas.setPavarde(pavarde);

        cin.ignore();
        cout << "Iveskite namu darbu rezultatus (spauskite Enter dukart norint baigti): " << endl;
        string input;
        list<double> homeworkGrades;

        while (true) {
            cout << "Namu darbas: ";
            getline(cin, input);
            if (input.empty()) {
                if (!homeworkGrades.empty()) {
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
                        homeworkGrades.push_back(static_cast<double>(grade));
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

        studentas.getRezultatai().setNamuDarbuRezultatai(homeworkGrades);

        cout << "Iveskite egzamino rezultata: ";
        while (true) {
            string examInput;
            cin >> examInput;
            try {
                int examGrade = stoi(examInput);
                if (examGrade < 0 || examGrade > 10) {
                    cout << "Egzamino rezultatas turi buti tarp 0 ir 10. Bandykite dar karta: ";
                }
                else {
                    studentas.getRezultatai().setEgzaminoRezultatas(examGrade);
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