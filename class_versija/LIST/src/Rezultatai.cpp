#include "Rezultatai.h"
#include <iostream>
#include <sstream>

std::istream& operator>>(std::istream& is, Rezultatai& rezultatai) {
    double grade;
    while (is >> grade) {
        if (grade < 0 || grade > 10) {
            break;
        }
        rezultatai.getNamuDarbuRezultatai().push_back(grade);
    }

    double egzaminas;
    is >> egzaminas;
    rezultatai.setEgzaminoRezultatas(egzaminas);

    return is;
}