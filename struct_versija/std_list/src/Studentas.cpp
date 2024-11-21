#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <limits>
#include "Studentas.h"
#include "utils.h"

using namespace std;

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
        studentStream >> studentas.vardas >> studentas.pavarde;

        for (int i = 0; i < numHomework; ++i) {
            int rezultatas;
            string temp;

            studentStream >> temp;
            try {
                rezultatas = stoi(temp);
                if (rezultatas < 0 || rezultatas > 10) {
                    throw out_of_range("Invalid value");
                }
                studentas.rezultatai.namuDarbuRezultatai.push_back(rezultatas);
            }
            catch (const exception&) {
                cout << "Neteisingas namu darbo rezultatas: " << temp << endl;
                cout << "Iveskite teisinga sveikaji skaiciu tarp 0 ir 10: ";
                cin >> rezultatas;
                correctInvalidData(rezultatas, "namu darbo rezultatas");
                studentas.rezultatai.namuDarbuRezultatai.push_back(rezultatas);
            }
        }

        int egzaminas;
        string tempExam;

        studentStream >> tempExam;
        try {
            egzaminas = stoi(tempExam);
            if (egzaminas < 0 || egzaminas > 10) {
                throw out_of_range("Invalid value");
            }
            studentas.rezultatai.egzaminoRezultatas = egzaminas;
        }
        catch (const exception&) {
            cout << "Neteisingas egzamino rezultatas: " << tempExam << endl;
            cout << "Iveskite teisinga sveikaji skaiciu tarp 0 ir 10: ";
            cin >> egzaminas;
            correctInvalidData(egzaminas, "egzamino rezultatas");
            studentas.rezultatai.egzaminoRezultatas = egzaminas;
        }

        studentai.push_back(studentas);
    }

    file.close();
}
