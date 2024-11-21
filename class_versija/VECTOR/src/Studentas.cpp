#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include "Studentas.h"
#include "utils.h"

using namespace std;

std::istream& operator>>(std::istream& is, Studentas& studentas) {
    std::string vardas, pavarde;
    is >> vardas >> pavarde;
    studentas.setVardas(vardas);
    studentas.setPavarde(pavarde);

    Rezultatai rezultatai;
    is >> rezultatai;

    studentas.setRezultatai(rezultatai);

    return is;
}

void correctInvalidData(int& rezultatas, const string& fieldName) {
    if (rezultatas < 0 || rezultatas > 10) {
        cout << "Invalid " << fieldName << ": " << rezultatas << ". Using default value 0." << endl;
        rezultatas = 0;
    }
}

void skaitytiIsFailo(vector<Studentas>& studentai, const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cout << "Nepavyko atidaryti failo: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line);

    istringstream headerStream(line);
    string headerWord;
    int numHomework = 0;
    while (headerStream >> headerWord) {
        if (headerWord.find("ND") != string::npos) {
            numHomework++;
        }
    }

    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        istringstream studentStream(line);
        Studentas studentas;

        string vardas, pavarde;
        if (!(studentStream >> vardas >> pavarde)) {
            cout << "Klaida skaitant studento varda ir pavarde" << endl;
            continue;
        }
        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);

        vector<double> namuDarbai;
        namuDarbai.reserve(numHomework);

        for (int i = 0; i < numHomework; ++i) {
            string temp;
            if (!(studentStream >> temp)) {
                cout << "Klaida skaitant namu darbo rezultata" << endl;
                break;
            }
            try {
                double rezultatas = stod(temp);
                if (rezultatas < 0 || rezultatas > 10) {
                    throw out_of_range("Invalid value");
                }
                namuDarbai.push_back(rezultatas);
            }
            catch (const exception&) {
                cout << "Netinkamas namu darbo rezultatas: " << temp << endl;
                namuDarbai.push_back(0.0);
            }
        }

        studentas.getRezultatai().setNamuDarbuRezultatai(namuDarbai);

        string tempExam;
        if (studentStream >> tempExam) {
            try {
                double egzaminas = stod(tempExam);
                if (egzaminas < 0 || egzaminas > 10) {
                    throw out_of_range("Invalid value");
                }
                studentas.getRezultatai().setEgzaminoRezultatas(egzaminas);
            }
            catch (const exception&) {
                cout << "Netinkamas egzamino rezultatas: " << tempExam << endl;
                studentas.getRezultatai().setEgzaminoRezultatas(0.0);
            }
        }

        studentai.push_back(studentas);
    }

    file.close();
}
