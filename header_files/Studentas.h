#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include "Rezultatai.h"

struct Studentas {
    std::string vardas;
    std::string pavarde;
    Rezultatai rezultatai;
};

void skaitytiIsFailo(std::vector<Studentas>& studentai, const std::string& fileName);
bool compareByLastName(const Studentas& a, const Studentas& b);

#endif // STUDENTAS_H
