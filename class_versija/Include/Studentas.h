#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include "Rezultatai.h"

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    Rezultatai rezultatai;
    double finalGrade;

public:
    Studentas() : finalGrade(0) {}

    Studentas(const std::string& vardas, const std::string& pavarde, const Rezultatai& rezultatai, double finalGrade)
        : vardas(vardas), pavarde(pavarde), rezultatai(rezultatai), finalGrade(finalGrade) {}

    ~Studentas() {
    }

    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    const Rezultatai& getRezultatai() const { return rezultatai; }
    Rezultatai& getRezultatai() { return rezultatai; }
    double getFinalGrade() const { return finalGrade; }

    void setVardas(const std::string& vardas) { this->vardas = vardas; }
    void setPavarde(const std::string& pavarde) { this->pavarde = pavarde; }
    void setRezultatai(const Rezultatai& rezultatai) { this->rezultatai = rezultatai; }
    void setFinalGrade(double finalGrade) { this->finalGrade = finalGrade; }

    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
};

void correctInvalidData(int& rezultatas, const std::string& fieldName);
void skaitytiIsFailo(std::vector<Studentas>& studentai, const std::string& fileName);

#endif // STUDENTAS_H
