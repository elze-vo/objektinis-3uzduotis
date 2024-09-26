#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Studentas.h"
#include "utils.h"

using namespace std;

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
        istringstream iss(line);
        Studentas studentas;
        string temp;

        iss >> studentas.vardas >> studentas.pavarde;

        // Process homework grades
        for (int i = 0; i < numHomework; ++i) {
            bool validInput = false;
            while (!validInput && iss >> temp) {
                try {
                    int rezultatas = stoi(temp);
                    if (rezultatas >= 0 && rezultatas <= 10) {
                        studentas.rezultatai.namuDarbuRezultatai.push_back(rezultatas);
                        validInput = true;
                    }
                    else {
                        throw out_of_range("Namu darbo rezultatas turi buti tarp 0 ir 10.");
                    }
                }
                catch (const invalid_argument&) {
                    cout << "Klaida: '" << temp << "' nera skaicius. Iveskite tinkama namu darbo rezultata: ";
                }
                catch (const out_of_range&) {
                    cout << "Klaida: '" << temp << "' nera tinkamas namu darbo rezultatas (turi buti 0-10). Bandykite dar karta: ";
                }

                while (!validInput) {
                    cin >> temp;
                    try {
                        int validResult = stoi(temp);
                        if (validResult >= 0 && validResult <= 10) {
                            studentas.rezultatai.namuDarbuRezultatai.push_back(validResult);
                            validInput = true;
                        }
                        else {
                            cout << "Netinkamas diapazonas (0-10). Bandykite dar karta: ";
                        }
                    }
                    catch (const invalid_argument&) {
                        cout << "Netinkamas ivedimas. Bandykite dar karta: ";
                    }
                }
            }
        }

        // Process exam grade
        bool validInput = false;
        while (!validInput && iss >> temp) {
            try {
                int rezultatas = stoi(temp);
                if (rezultatas >= 0 && rezultatas <= 10) {
                    studentas.rezultatai.egzaminoRezultatas = rezultatas;
                    validInput = true;
                }
                else {
                    throw out_of_range("Egzamino rezultatas turi buti tarp 0 ir 10.");
                }
            }
            catch (const invalid_argument&) {
                cout << "Klaida: '" << temp << "' nera skaicius. Iveskite tinkama egzamino rezultata: ";
            }
            catch (const out_of_range&) {
                cout << "Klaida: '" << temp << "' nera tinkamas egzamino rezultatas (turi buti 0-10). Bandykite dar karta: ";
            }

            while (!validInput) {
                cin >> temp;
                try {
                    int validResult = stoi(temp);
                    if (validResult >= 0 && validResult <= 10) {
                        studentas.rezultatai.egzaminoRezultatas = validResult;
                        validInput = true;
                    }
                    else {
                        cout << "Netinkamas diapazonas (0-10). Bandykite dar karta: ";
                    }
                }
                catch (const invalid_argument&) {
                    cout << "Netinkamas ivedimas. Bandykite dar karta: ";
                }
            }
        }

        studentai.push_back(studentas);
    }

    file.close();
}
