#ifndef REZULTATAI_H
#define REZULTATAI_H

#include <vector>
#include <iostream>

class Rezultatai {
private:
    std::vector<double> namuDarbuRezultatai;
    double egzaminoRezultatas;

public:
    // Default constructor
    Rezultatai() : egzaminoRezultatas(0) {}

    // Constructor to initialize with results
    Rezultatai(const std::vector<double>& ndRezultatai, double egzRezultatas)
        : namuDarbuRezultatai(ndRezultatai), egzaminoRezultatas(egzRezultatas) {}

    // Getters
    std::vector<double>& getNamuDarbuRezultatai() { return namuDarbuRezultatai; }
    const std::vector<double>& getNamuDarbuRezultatai() const { return namuDarbuRezultatai; }
    double getEgzaminoRezultatas() const { return egzaminoRezultatas; }

    // Setters
    void setNamuDarbuRezultatai(const std::vector<double>& ndRezultatai) {
        this->namuDarbuRezultatai = ndRezultatai;
    }

    void setEgzaminoRezultatas(double egzRezultatas) {
        this->egzaminoRezultatas = egzRezultatas;
    }

    friend std::istream& operator>>(std::istream& is, Rezultatai& rezultatai);
};

#endif // REZULTATAI_H
