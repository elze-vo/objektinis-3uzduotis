#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include "Studentas.h"

using namespace std;

std::istream& operator>>(std::istream& is, Studentas& studentas) {
    if (&is == &std::cin) {
        // Manual input handling
        cout << "Iveskite studento varda: ";
        string vardas;
        cin >> vardas;
        studentas.setVardas(vardas);

        cout << "Iveskite studento pavarde: ";
        string pavarde;
        cin >> pavarde;
        studentas.setPavarde(pavarde);
        cin.ignore();

        cout << "Iveskite namu darbu rezultatus (dukart spauskite Enter norint baigti): " << endl;
        vector<double> homeworkGrades;
        string input;

        while (true) {
            cout << "Namu darbas: ";
            getline(cin, input);

            if (input.empty()) {
                if (!homeworkGrades.empty()) break;
                cout << "Namu darbu rezultatai negali buti tusti. Bandykite dar karta." << endl;
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
        studentas.setNamuDarbuRezultatai(homeworkGrades);

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
                    studentas.setEgzaminoRezultatas(examGrade);
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
    }
    else {
        // File input handling
        string vardas, pavarde;
        is >> vardas >> pavarde;

        if (is.fail()) return is;

        std::vector<double> homeworkGrades;
        double grade;

        for (int i = 0; i < 5; ++i) {
            if (is >> grade) {
                if (grade < 0 || grade > 10) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                homeworkGrades.push_back(grade);
            }
            else {
                is.setstate(std::ios::failbit);
                return is;
            }
        }

        double egzaminas;
        if (is >> egzaminas) {
            if (egzaminas < 0 || egzaminas > 10) {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
        else {
            is.setstate(std::ios::failbit);
            return is;
        }

        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);
        studentas.setNamuDarbuRezultatai(homeworkGrades);
        studentas.setEgzaminoRezultatas(egzaminas);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    os << std::setw(15) << std::left << studentas.getVardas()
        << std::setw(15) << std::left << studentas.getPavarde()
        << std::setw(25) << std::left << &studentas
        << std::fixed << std::setprecision(2) << studentas.getFinalGrade();
    return os;
}
