#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Studentas.h"
#include "utils.h"

using namespace std;

void skaitytiIsFailo(vector<Studentas>& studentai, const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cout << "Nepavyko atidaryti failo: " << fileName << endl;
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();

    file.close();

    istringstream iss(fileContent);
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
            if (studentStream >> temp) {
                try {
                    double rezultatas = stod(temp);
                    if (rezultatas >= 0 && rezultatas <= 10) {
                        studentas.rezultatai.namuDarbuRezultatai.push_back(rezultatas);
                    }
                    else {
                        throw out_of_range("Namu darbo rezultatas turi buti tarp 0 ir 10.");
                    }
                }
                catch (const invalid_argument&) {
                    cout << "Neteisingas namu darbo rezultatas: " << temp << endl;
                }
            }
        }

        string temp;
        if (studentStream >> temp) {
            try {
                double rezultatas = stod(temp);
                if (rezultatas >= 0 && rezultatas <= 10) {
                    studentas.rezultatai.egzaminoRezultatas = rezultatas;
                }
                else {
                    throw out_of_range("Egzamino rezultatas turi buti tarp 0 ir 10.");
                }
            }
            catch (const invalid_argument&) {
                cout << "Neteisingas egzamino rezultatas: " << temp << endl;
            }
        }

        studentai.push_back(studentas);
    }
}
