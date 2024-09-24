#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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
    if (size % 2 == 0) {
        return (grades[size / 2 - 1] + grades[size / 2]) / 2.0;
    }
    return grades[size / 2];
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<Studentas> studentai;
    int studentuSkaicius;
    int laikinasRezultatas;
    int pasirinkimas;

    cout << "Iveskite studentu skaiciu: ";
    cin >> studentuSkaicius;
    cin.ignore();

    cout << "Pasirinkite, kaip ivesti rezultatus:\n";
    cout << "1 - Rankiniu budu\n";
    cout << "2 - Atsitiktinai sugeneruoti\n";
    cin >> pasirinkimas;
    cin.ignore();

    for (int i = 0; i < studentuSkaicius; i++) {
        Studentas studentas;
        cout << "\nIveskite " << i + 1 << "-ojo studento varda: ";
        getline(cin, studentas.vardas);

        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        getline(cin, studentas.pavarde);

        cout << "Iveskite namu darbu rezultatus (spauskite ENTER, kai baigsite): " << endl;
        if (pasirinkimas == 1) {
            while (true) {
                cout << "Namu darbo rezultatas: ";
                string input;
                getline(cin, input);
                if (input.empty()) {
                    break;
                }
                try {
                    laikinasRezultatas = stoi(input);
                    studentas.namuDarbuRezultatai.push_back(laikinasRezultatas);
                }
                catch (const invalid_argument& e) {
                    cout << "Ivestas netinkamas rezultatas. Bandykite dar karta." << endl;
                }
            }
        }
        else {
            int namuDarbaiKiekis;
            cout << "Iveskite namu darbu kieki: ";
            cin >> namuDarbaiKiekis;
            cin.ignore();
            for (int j = 0; j < namuDarbaiKiekis; j++) {
                laikinasRezultatas = rand() % 11;
                studentas.namuDarbuRezultatai.push_back(laikinasRezultatas);
            }
        }

        if (pasirinkimas == 1) {
            cout << "Iveskite egzamino rezultata: ";
            cin >> studentas.egzaminoRezultatas;
            cin.ignore();
        }
        else {
            studentas.egzaminoRezultatas = rand() % 11;
        }

        studentai.push_back(studentas);
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
