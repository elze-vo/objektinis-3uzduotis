#include "student_input.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

void addStudentsManually(vector<Studentas>& studentai) {
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

        // Set student's name using class setter
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        string vardas;
        cin >> vardas;
        studentas.setVardas(vardas); // assuming setVardas() is a setter in Studentas

        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        string pavarde;
        cin >> pavarde;
        studentas.setPavarde(pavarde); // assuming setPavarde() is a setter in Studentas
        cin.ignore();

        cout << "Iveskite namu darbu rezultatus (spauskite Enter dukart norint baigti): " << endl;
        string input;
        vector<double> homeworkGrades;

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
                        homeworkGrades.push_back(static_cast<double>(grade)); // Add grade to vector
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

        // Set homework grades in the student object
        studentas.getRezultatai().setNamuDarbuRezultatai(homeworkGrades);

        // Set exam results using class methods
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
                    studentas.getRezultatai().setEgzaminoRezultatas(examGrade); // assuming setEgzaminoRezultatas() is a setter in Rezultatai
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