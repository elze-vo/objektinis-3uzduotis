#ifndef REZULTATAI_H
#define REZULTATAI_H

#include <list>
#include <iostream>

class Rezultatai {
private:
    std::list<double> namuDarbuRezultatai;
    double egzaminoRezultatas;

public:
    Rezultatai() : egzaminoRezultatas(0) {}
    Rezultatai(const std::list<double>& ndRezultatai, double egzRezultatas)
        : namuDarbuRezultatai(ndRezultatai), egzaminoRezultatas(egzRezultatas) {}
    ~Rezultatai() {}

    std::list<double>& getNamuDarbuRezultatai() { return namuDarbuRezultatai; }
    const std::list<double>& getNamuDarbuRezultatai() const { return namuDarbuRezultatai; }
    double getEgzaminoRezultatas() const { return egzaminoRezultatas; }

    void setNamuDarbuRezultatai(const std::list<double>& ndRezultatai) {
        this->namuDarbuRezultatai = ndRezultatai;
    }

    void setEgzaminoRezultatas(double egzRezultatas) {
        this->egzaminoRezultatas = egzRezultatas;
    }

    friend std::istream& operator>>(std::istream& is, Rezultatai& rezultatai);
};

#endif // REZULTATAI_H