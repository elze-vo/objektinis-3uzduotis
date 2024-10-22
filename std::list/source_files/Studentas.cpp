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
    size_t lineCount = 0;

    getline(file, line);

    while (getline(file, line)) {
        lineCount++;
    }

    file.clear();
    file.seekg(0, ios::beg);

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
            string temp;
            studentStream >> temp;

            try {
                int rezultatas = stoi(temp);
                if (rezultatas < 0 || rezultatas > 10) {
                    throw out_of_range("Invalid value");
                }
                studentas.rezultatai.namuDarbuRezultatai.push_back(rezultatas);
            }
            catch (const exception&) {
                int validResult;
                cout << "Neteisingas namu darbo rezultatas: " << temp << endl;
                cout << "Iveskite teisinga sveikaji skaiciu tarp 0 ir 10: ";
                cin >> validResult;
                correctInvalidData(validResult, "namu darbo rezultatas");
                studentas.rezultatai.namuDarbuRezultatai.push_back(validResult);
            }
        }

        string tempExam;
        studentStream >> tempExam;

        try {
            int egzaminas = stoi(tempExam);
            if (egzaminas < 0 || egzaminas > 10) {
                throw out_of_range("Invalid value");
            }
            studentas.rezultatai.egzaminoRezultatas = egzaminas;
        }
        catch (const exception&) {
            int validExam;
            cout << "Neteisingas egzamino rezultatas: " << tempExam << endl;
            cout << "Iveskite teisinga sveikaji skaiciu tarp 0 ir 10: ";
            cin >> validExam;
            correctInvalidData(validExam, "egzamino rezultatas");
            studentas.rezultatai.egzaminoRezultatas = validExam;
        }

        studentai.push_back(studentas);
    }

    file.close();
}
