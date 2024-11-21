#include "Rezultatai.h"
#include <iostream>
#include <sstream>

std::istream& operator>>(std::istream& is, Rezultatai& rezultatai) {
    int grade;
    while (is >> grade) {
        if (grade < 0 || grade > 10) {
            break;
        }
        rezultatai.namuDarbuRezultatai.push_back(grade);
    }

    is >> rezultatai.egzaminoRezultatas;

    return is;
}
