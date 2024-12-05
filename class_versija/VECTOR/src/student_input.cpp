#include "student_input.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void addStudentsManually(vector<Studentas>& studentai) {
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    for (int i = 0; i < numberOfStudents; ++i) {
        Studentas studentas;
        cout << "Iveskite duomenis " << i + 1 << "-ajam studentui:\n";
        cin >> studentas;
        studentai.push_back(studentas);
    }
}
