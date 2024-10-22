#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <list>
#include "Rezultatai.h"

struct Studentas {
    std::string vardas;
    std::string pavarde;
    Rezultatai rezultatai;
};

void correctInvalidData(int& rezultatas, const std::string& fieldName);
void skaitytiIsFailo(std::list<Studentas>& studentai, const std::string& fileName);

#endif // STUDENTAS_H
