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
    // Read student's name and surname (assuming they are space-separated)
    std::string vardas, pavarde;
    is >> vardas >> pavarde;
    studentas.setVardas(vardas);  // Use setter to assign values
    studentas.setPavarde(pavarde);

    // Read the student's results (Rezultatai)
    Rezultatai rezultatai;
    is >> rezultatai;  // Assuming you have implemented operator>> for Rezultatai

    // Set the results for the student
    studentas.setRezultatai(rezultatai);

    return is;
}

void correctInvalidData(int& rezultatas, const string& fieldName) {
    // Ensure valid results: if invalid (not between 0 and 10), set default to 0
    if (rezultatas < 0 || rezultatas > 10) {
        cout << "Invalid " << fieldName << ": " << rezultatas << ". Using default value 0." << endl;
        rezultatas = 0;  // Default to 0 for invalid results
    }
}

void skaitytiIsFailo(vector<Studentas>& studentai, const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cout << "Nepavyko atidaryti failo: " << fileName << endl;
        return;
    }

    string line;
    // Skip the header line (assumes first line is a header)
    getline(file, line);

    // Count the number of homework columns (assumes columns are named "ND")
    istringstream headerStream(line);
    string headerWord;
    int numHomework = 0;
    while (headerStream >> headerWord) {
        if (headerWord.find("ND") != string::npos) {
            numHomework++;
        }
    }

    // Read each student's data
    while (getline(file, line)) {
        // Trim leading and trailing whitespace from the line
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        istringstream studentStream(line);
        Studentas studentas;

        // Read name and surname
        string vardas, pavarde;
        if (!(studentStream >> vardas >> pavarde)) {
            cout << "Klaida skaitant studento varda ir pavarde" << endl;
            continue;  // Skip this student if name/surname is not valid
        }
        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);

        vector<double> namuDarbai;
        namuDarbai.reserve(numHomework);  // Reserve memory for homework grades

        // Read homework grades
        for (int i = 0; i < numHomework; ++i) {
            string temp;
            if (!(studentStream >> temp)) {
                cout << "Klaida skaitant namu darbo rezultata" << endl;
                break;  // Stop reading this student's homework if error occurs
            }
            try {
                double rezultatas = stod(temp);  // Convert to double
                if (rezultatas < 0 || rezultatas > 10) {
                    throw out_of_range("Invalid value");
                }
                namuDarbai.push_back(rezultatas);  // Valid homework grade, add to vector
            }
            catch (const exception&) {
                cout << "Netinkamas namu darbo rezultatas: " << temp << endl;
                namuDarbai.push_back(0.0);  // Default to 0 in case of invalid grade
            }
        }

        // Set the homework results to the student's results object
        studentas.getRezultatai().setNamuDarbuRezultatai(namuDarbai);

        // Read exam result
        string tempExam;
        if (studentStream >> tempExam) {
            try {
                double egzaminas = stod(tempExam);  // Convert to double
                if (egzaminas < 0 || egzaminas > 10) {
                    throw out_of_range("Invalid value");
                }
                studentas.getRezultatai().setEgzaminoRezultatas(egzaminas);  // Valid exam grade
            }
            catch (const exception&) {
                cout << "Netinkamas egzamino rezultatas: " << tempExam << endl;
                studentas.getRezultatai().setEgzaminoRezultatas(0.0);  // Default to 0 if invalid
            }
        }

        // Add the student object to the vector
        studentai.push_back(studentas);
    }

    file.close();  // Close the file after reading
}
