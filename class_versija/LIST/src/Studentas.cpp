#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
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
    while (cin.fail() || rezultatas < 0 || rezultatas > 10 || rezultatas != static_cast<int>(rezultatas)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Neteisingas " << fieldName << ": " << rezultatas << ". Iveskite sveikaji skaiciu tarp 0 ir 10: ";
        cin >> rezultatas;
    }
}

void skaitytiIsFailo(list<Studentas>& studentai, const string& fileName) {
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
        istringstream studentStream(line);
        Studentas studentas;

        string vardas, pavarde;
        studentStream >> vardas >> pavarde;
        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);

        list<double> namuDarbai;
        for (int i = 0; i < numHomework; ++i) {
            string temp;
            studentStream >> temp;
            try {
                double rezultatas = stod(temp);
                if (rezultatas < 0 || rezultatas > 10) {
                    throw out_of_range("Invalid value");
                }
                namuDarbai.push_back(rezultatas);
            }
            catch (const exception&) {
                cout << "Neteisingas namu darbo rezultatas: " << temp << endl;
                cout << "Iveskite teisinga sveikaji skaiciu tarp 0 ir 10: ";
                int rezultatas;
                cin >> rezultatas;
                correctInvalidData(rezultatas, "namu darbo rezultatas");
                namuDarbai.push_back(rezultatas);
            }
        }

        studentas.getRezultatai().setNamuDarbuRezultatai(namuDarbai);

        string tempExam;
        studentStream >> tempExam;
        try {
            double egzaminas = stod(tempExam);
            if (egzaminas < 0 || egzaminas > 10) {
                throw out_of_range("Invalid value");
            }
            studentas.getRezultatai().setEgzaminoRezultatas(egzaminas);
        }
        catch (const exception&) {
            cout << "Neteisingas egzamino rezultatas: " << tempExam << endl;
            cout << "Iveskite teisinga sveikaji skaiciu tarp 0 ir 10: ";
            int egzaminas;
            cin >> egzaminas;
            correctInvalidData(egzaminas, "egzamino rezultatas");
            studentas.getRezultatai().setEgzaminoRezultatas(egzaminas);
        }

        studentai.push_back(studentas);
    }

    file.close();
}
