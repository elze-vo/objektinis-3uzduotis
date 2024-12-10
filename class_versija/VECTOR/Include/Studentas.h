#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "Zmogus.h"
#include <vector>
#include <iostream>
#include <iomanip>

class Studentas : public Zmogus {
private:
    std::vector<double> namuDarbuRezultatai;
    double egzaminoRezultatas;
    double finalGrade;

public:
    // Constructors
    Studentas() : Zmogus(), egzaminoRezultatas(0), finalGrade(0) {}

    // Constructor with only vardas and pavarde
    Studentas(const std::string& vardas, const std::string& pavarde)
        : Zmogus(vardas, pavarde), egzaminoRezultatas(0), finalGrade(0) {}

    Studentas(const std::string& vardas, const std::string& pavarde,
        const std::vector<double>& ndRezultatai, double egzRezultatas, double finalGrade)
        : Zmogus(vardas, pavarde), namuDarbuRezultatai(ndRezultatai),
        egzaminoRezultatas(egzRezultatas), finalGrade(finalGrade) {}

    // Copy Constructor
    Studentas(const Studentas& other)
        : Zmogus(other), // Call the base class copy constructor
        namuDarbuRezultatai(other.namuDarbuRezultatai),
        egzaminoRezultatas(other.egzaminoRezultatas),
        finalGrade(other.finalGrade) {}

    // Copy Assignment Operator
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other); // Assign base class members
            namuDarbuRezultatai = other.namuDarbuRezultatai;
            egzaminoRezultatas = other.egzaminoRezultatas;
            finalGrade = other.finalGrade;
        }
        return *this;
    }

    // Destructor
    ~Studentas() {
        namuDarbuRezultatai.clear();
    }

    // Accessor and Mutator Methods for Results
    std::vector<double>& getNamuDarbuRezultatai() { return namuDarbuRezultatai; }
    const std::vector<double>& getNamuDarbuRezultatai() const { return namuDarbuRezultatai; }
    double getEgzaminoRezultatas() const { return egzaminoRezultatas; }
    void setNamuDarbuRezultatai(const std::vector<double>& ndRezultatai) {
        this->namuDarbuRezultatai = ndRezultatai;
    }
    void setEgzaminoRezultatas(double egzRezultatas) { this->egzaminoRezultatas = egzRezultatas; }

    double getFinalGrade() const { return finalGrade; }
    void setFinalGrade(double finalGrade) { this->finalGrade = finalGrade; }

    // Override the virtual method from Zmogus
    void printInfo() const override {
        std::cout << "Vardas: " << vardas << ", Pavarde: " << pavarde << "\n";
    }

    // Input and Output Operators
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
};

#endif // STUDENTAS_H
