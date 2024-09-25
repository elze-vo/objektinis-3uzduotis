#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Rezultatai {
    vector<int> namuDarbuRezultatai;
    int egzaminoRezultatas;
};

struct Studentas {
    string vardas;
    string pavarde;
    Rezultatai rezultatai;
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
                studentas.rezultatai.namuDarbuRezultatai.push_back(rezultatas);
            }
        }

        if (iss >> rezultatas) {
            studentas.rezultatai.egzaminoRezultatas = rezultatas;
        }

        studentai.push_back(studentas);
    }

    file.close();
}

bool compareByLastName(const Studentas& a, const Studentas& b) {
    return a.pavarde < b.pavarde;
}

void addStudentsManually(vector<Studentas>& studentai) {
    int numberOfStudents;
    cout << "Iveskite studentu kieki: ";
    cin >> numberOfStudents;
    cin.ignore();

    for (int i = 0; i < numberOfStudents; ++i) {
        Studentas studentas;
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        cin >> studentas.vardas;
        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        cin >> studentas.pavarde;
        cin.ignore();

        cout << "Iveskite namu darbu rezultatus (spauskite Enter dukart norint baigti): " << endl;
        string input;

        while (true) {
            cout << "Namu darbas: ";
            getline(cin, input);

            if (input.empty()) {
                if (!studentas.rezultatai.namuDarbuRezultatai.empty()) {
                    break;
                }
            }
            else {
                try {
                    int grade = stoi(input);
                    if (grade < 0 || grade > 10) {
                        cout << "Namu darbas turi buti tarp 0 ir 10. Bandykite dar karta." << endl;
                    }
                    else {
                        studentas.rezultatai.namuDarbuRezultatai.push_back(grade);
                    }
                }
                catch (invalid_argument&) {
                    cout << "Ivedete neteisinga reiksme. Bandykite dar karta." << endl;
                }
                catch (out_of_range&) {
                    cout << "Ivedete reiksme, kuri yra per didele. Bandykite dar karta." << endl;
                }
            }
        }

        cout << "Iveskite egzamino rezultata: ";
        while (true) {
            cin >> studentas.rezultatai.egzaminoRezultatas;

            if (studentas.rezultatai.egzaminoRezultatas < 0 || studentas.rezultatai.egzaminoRezultatas > 10) {
                cout << "Egzamino rezultatas turi buti tarp 0 ir 10. Bandykite dar karta: ";
            }
            else {
                cin.ignore();
                break;
            }
        }

        studentai.push_back(studentas);
    }
}

void addStudentsRandomly(vector<Studentas>& studentai) {
    int numHomework;
    cout << "Iveskite namu darbu kieki: ";
    cin >> numHomework;

    int numberOfStudents;
    cout << "Iveskite studentu kieki: ";
    cin >> numberOfStudents;

    for (int i = 0; i < numberOfStudents; ++i) {
        Studentas studentas;
        studentas.vardas = "Vardas" + to_string(i + 1);
        studentas.pavarde = "Pavarde" + to_string(i + 1);

        for (int j = 0; j < numHomework; ++j) {
            int randomGrade = rand() % 11;
            studentas.rezultatai.namuDarbuRezultatai.push_back(randomGrade);
        }

        studentas.rezultatai.egzaminoRezultatas = rand() % 11;
        studentai.push_back(studentas);
    }
}

int main() {
    vector<Studentas> studentai;
    int pasirinkimas;

    cout << "Pasirinkite veiksmus:\n";
    cout << "1 - Prideti studentus is failo\n";
    cout << "2 - Prideti studentus ranka\n";
    cout << "3 - Generuoti studentus atsitiktinai\n";
    cout << "Iveskite pasirinkima: ";
    cin >> pasirinkimas;
    cin.ignore();

    switch (pasirinkimas) {
    case 1: {
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
        cin >> failoPavadinimas;
        skaitytiIsFailo(studentai, failoPavadinimas);
        break;
    }
    case 2: {
        addStudentsManually(studentai);
        break;
    }
    case 3: {
        addStudentsRandomly(studentai);
        break;
    }
    default:
        cout << "Neteisingas pasirinkimas.\n";
        return 1;
    }

    if (studentai.empty()) {
        cout << "Nera studentu.\n";
        return 1;
    }

    cout << "Pasirinkite (1 - Vidurkis, 2 - Mediana): ";
    cin >> pasirinkimas;

    sort(studentai.begin(), studentai.end(), compareByLastName);

    cout << "\n" << setw(15) << left << "Vardas"
        << setw(15) << left << "Pavarde"
        << (pasirinkimas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;

    cout << string(50, '-') << endl;

    cout << fixed << setprecision(2);
    for (const auto& studentas : studentai) {
        double galutinisVid;
        if (pasirinkimas == 1) {
            double namuDarbuVidurkis = accumulate(studentas.rezultatai.namuDarbuRezultatai.begin(), studentas.rezultatai.namuDarbuRezultatai.end(), 0.0) / studentas.rezultatai.namuDarbuRezultatai.size();
            galutinisVid = 0.4 * namuDarbuVidurkis + 0.6 * studentas.rezultatai.egzaminoRezultatas;
        }
        else {
            vector<int> namuDarbuCopy = studentas.rezultatai.namuDarbuRezultatai;
            double namuDarbuMediana = calculateMedian(namuDarbuCopy);
            galutinisVid = 0.4 * namuDarbuMediana + 0.6 * studentas.rezultatai.egzaminoRezultatas;
        }

        cout << setw(15) << left << studentas.vardas
            << setw(15) << left << studentas.pavarde
            << galutinisVid << endl;
    }

    return 0;
}
