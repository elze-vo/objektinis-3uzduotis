#include "Rezultatai.h"
#include <iostream>
#include <sstream>

std::istream& operator>>(std::istream& is, Rezultatai& rezultatai) {
    // Read homework results (assuming they're space-separated integers)
    int grade;
    while (is >> grade) {
        if (grade < 0 || grade > 10) {
            break;  // Exit when we encounter an invalid grade
        }
        rezultatai.namuDarbuRezultatai.push_back(grade);
    }

    // Read the exam result
    is >> rezultatai.egzaminoRezultatas;

    return is;
}