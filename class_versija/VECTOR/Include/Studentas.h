#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<double> namuDarbuRezultatai;
    double egzaminoRezultatas;
    double finalGrade;

public:
    // Constructors
    Studentas() : egzaminoRezultatas(0), finalGrade(0) {}

    Studentas(const std::string& vardas, const std::string& pavarde,
        const std::vector<double>& ndRezultatai, double egzRezultatas, double finalGrade)
        : vardas(vardas), pavarde(pavarde), namuDarbuRezultatai(ndRezultatai),
        egzaminoRezultatas(egzRezultatas), finalGrade(finalGrade) {}

    // Copy Constructor
    Studentas(const Studentas& other)
        : vardas(other.vardas), pavarde(other.pavarde),
        namuDarbuRezultatai(other.namuDarbuRezultatai),
        egzaminoRezultatas(other.egzaminoRezultatas), finalGrade(other.finalGrade) {}

    // Copy Assignment Operator
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas = other.vardas;
            pavarde = other.pavarde;
            namuDarbuRezultatai = other.namuDarbuRezultatai;
            egzaminoRezultatas = other.egzaminoRezultatas;
            finalGrade = other.finalGrade;
        }
        return *this;
    }

    // Destructor
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        namuDarbuRezultatai.clear();
    }

    // Accessor and Mutator Methods for Student Information
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    void setVardas(const std::string& vardas) { this->vardas = vardas; }
    void setPavarde(const std::string& pavarde) { this->pavarde = pavarde; }

    // Accessor and Mutator Methods for Results
    std::vector<double>& getNamuDarbuRezultatai() { return namuDarbuRezultatai; }
    const std::vector<double>& getNamuDarbuRezultatai() const { return namuDarbuRezultatai; }
    double getEgzaminoRezultatas() const { return egzaminoRezultatas; }
    void setNamuDarbuRezultatai(const std::vector<double>& ndRezultatai) {
        this->namuDarbuRezultatai = ndRezultatai;
    }
    void setEgzaminoRezultatas(double egzRezultatas) { this->egzaminoRezultatas = egzRezultatas; }

    // Accessor and Mutator Methods for Final Grade
    double getFinalGrade() const { return finalGrade; }
    void setFinalGrade(double finalGrade) { this->finalGrade = finalGrade; }

    // Input and Output Operators
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
};

#endif // STUDENTAS_H
