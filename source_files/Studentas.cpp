#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include "Studentas.h"
#include "utils.h"

using namespace std;

void correctInvalidData(double& rezultatas, const string& fieldName) {
    while (cin.fail() || rezultatas < 0 || rezultatas > 10 || rezultatas != static_cast<int>(rezultatas)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Neteisingas " << fieldName << ": " << rezultatas << ". Iveskite sveikaji skaiciu tarp 0 ir 10: ";
        cin >> rezultatas;
    }
}

void skaitytiIsFailo(vector<Studentas>& studentai, const string& fileName) {
    ifstream file(fileName, ios::in | ios::binary | ios::ate);
    if (!file) {
        cout << "Nepavyko atidaryti failo: " << fileName << endl;
        return;
    }

    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);
    file.close();

    istringstream iss(string(buffer.begin(), buffer.end()));
    string line;

    getline(iss, line);
    istringstream headerStream(line);
    string headerWord;
    int numHomework = 0;

    while (headerStream >> headerWord) {
        if (headerWord.find("ND") != string::npos) {
            numHomework++;
        }
    }

    while (getline(iss, line)) {
        istringstream studentStream(line);
        Studentas studentas;
        studentStream >> studentas.vardas >> studentas.pavarde;

        studentas.rezultatai.namuDarbuRezultatai.reserve(numHomework);

        for (int i = 0; i < numHomework; ++i) {
            string temp;
            studentStream >> temp;

            try {
                double rezultatas = stod(temp);
                if (rezultatas < 0 || rezultatas > 10 || rezultatas != static_cast<int>(rezultatas)) {
                    throw out_of_range("Invalid value");
                }
                studentas.rezultatai.namuDarbuRezultatai.push_back(rezultatas);
            }
            catch (const exception&) {
                double validResult;
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
            double egzaminas = stod(tempExam);
            if (egzaminas < 0 || egzaminas > 10 || egzaminas != static_cast<int>(egzaminas)) {
                throw out_of_range("Invalid value");
            }
            studentas.rezultatai.egzaminoRezultatas = egzaminas;
        }
        catch (const exception&) {
            double validExam;
            cout << "Neteisingas egzamino rezultatas: " << tempExam << endl;
            cout << "Iveskite teisinga sveikaji skaiciu tarp 0 ir 10: ";
            cin >> validExam;
            correctInvalidData(validExam, "egzamino rezultatas");
            studentas.rezultatai.egzaminoRezultatas = validExam;
        }

        studentai.push_back(studentas);
    }
}
