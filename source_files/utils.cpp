#include "utils.h"
#include <iomanip>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

double calculateMedian(vector<int>& grades) {
    sort(grades.begin(), grades.end());
    size_t size = grades.size();
    if (size == 0) return 0.0;
    if (size % 2 == 0) {
        return (grades[size / 2 - 1] + grades[size / 2]) / 2.0;
    }
    return grades[size / 2];
}

bool compareByLastName(const Studentas& a, const Studentas& b) {
    return a.pavarde < b.pavarde;
}


void printOrSaveResults(const std::vector<Studentas>& studentai, int pasirinkimas, std::ostream& out) {
    out << "\n" << std::setw(15) << std::left << "Vardas"
        << std::setw(15) << std::left << "Pavarde"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;

    out << std::string(50, '-') << std::endl;

    out << std::fixed << std::setprecision(2);
    for (const auto& studentas : studentai) {
        double galutinisVid;
        if (pasirinkimas == 1) {
            double namuDarbuVidurkis = std::accumulate(studentas.rezultatai.namuDarbuRezultatai.begin(), studentas.rezultatai.namuDarbuRezultatai.end(), 0.0) / studentas.rezultatai.namuDarbuRezultatai.size();
            galutinisVid = 0.4 * namuDarbuVidurkis + 0.6 * studentas.rezultatai.egzaminoRezultatas;
        }
        else {
            std::vector<int> namuDarbuCopy = studentas.rezultatai.namuDarbuRezultatai;
            double namuDarbuMediana = calculateMedian(namuDarbuCopy);
            galutinisVid = 0.4 * namuDarbuMediana + 0.6 * studentas.rezultatai.egzaminoRezultatas;
        }

        out << std::setw(15) << std::left << studentas.vardas
            << std::setw(15) << std::left << studentas.pavarde
            << galutinisVid << std::endl;
    }
}
