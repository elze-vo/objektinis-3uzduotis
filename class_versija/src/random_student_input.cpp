#include "random_student_input.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void addStudentsRandomly(vector<Studentas>& studentai) {
    int numberOfStudents;

    while (true) {
        cout << "Iveskite studentu kieki (didesnis uz 0): ";
        cin >> numberOfStudents;

        if (cin.fail() || numberOfStudents <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas ivestis. Bandykite dar karta.\n";
        }
        else {
            cin.ignore();
            break;
        }
    }

    auto seed = static_cast<unsigned int>(time(nullptr) % UINT32_MAX);
    srand(seed);

    for (int i = 0; i < numberOfStudents; ++i) {
        Studentas studentas;
        studentas.setVardas("Vardas" + to_string(i + 1));  // Using setter for 'vardas'
        studentas.setPavarde("Pavarde" + to_string(i + 1));  // Using setter for 'pavarde'

        // Generate random homework results
        int numHomework = rand() % 5 + 1;  // Random number of homework grades
        vector<double> homeworkGrades;
        for (int j = 0; j < numHomework; ++j) {
            homeworkGrades.push_back(static_cast<double>(rand() % 11)); // Add random grades to vector
        }

        // Set homework grades in the student object
        studentas.getRezultatai().setNamuDarbuRezultatai(homeworkGrades);

        // Generate random exam result
        studentas.getRezultatai().setEgzaminoRezultatas(rand() % 11);  // Random exam grade

        studentai.push_back(studentas);
    }
}