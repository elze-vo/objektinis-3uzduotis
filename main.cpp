#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namuDarbuRezultatai;
    int egzaminoRezultatas;
};

double calculateMedian(vector<int>& grades) {
    sort(grades.begin(), grades.end());
    size_t size = grades.size();
    if (size == 0) return 0.0;
    if (size % 2 == 0) {
        return (grades[size / 2 - 1] + grades[size / 2]) / 2.0;
    }
    return grades[size / 2];
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
        istringstream iss(line);
        Studentas studentas;
        int rezultatas;

        iss >> studentas.vardas >> studentas.pavarde;

        for (int i = 0; i < numHomework; ++i) {
            if (iss >> rezultatas) {
                studentas.namuDarbuRezultatai.push_back(rezultatas);
            }
        }

        if (iss >> rezultatas) {
            studentas.egzaminoRezultatas = rezultatas;
        }

        studentai.push_back(studentas);
    }

    file.close();
}

int main() {
    vector<Studentas> studentai;
    int pasirinkimas;
    string failoPavadinimas;

    cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
    cin >> failoPavadinimas;

    skaitytiIsFailo(studentai, failoPavadinimas);

    if (studentai.empty()) {
        cout << "Failas tuscias arba nesugebeta nuskaityti studentu." << endl;
        return 1;
    }

    cout << "Pasirinkite (1 - Vidurkis, 2 - Mediana): ";
    cin >> pasirinkimas;

    cout << "\n" << setw(15) << left << "Vardas"
        << setw(15) << left << "Pavarde"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;

    cout << string(50, '-') << endl;

    cout << fixed << setprecision(2);
    for (const auto& studentas : studentai) {
        double galutinisVid;
        if (pasirinkimas == 1) {
            double namuDarbuVidurkis = accumulate(studentas.namuDarbuRezultatai.begin(), studentas.namuDarbuRezultatai.end(), 0.0) / studentas.namuDarbuRezultatai.size();
            galutinisVid = 0.4 * namuDarbuVidurkis + 0.6 * studentas.egzaminoRezultatas;
        }
        else {
            vector<int> namuDarbuCopy = studentas.namuDarbuRezultatai;
            double namuDarbuMediana = calculateMedian(namuDarbuCopy);
            galutinisVid = 0.4 * namuDarbuMediana + 0.6 * studentas.egzaminoRezultatas;
        }

        cout << setw(15) << left << studentas.vardas
            << setw(15) << left << studentas.pavarde
            << galutinisVid << endl;
    }

    return 0;
}
