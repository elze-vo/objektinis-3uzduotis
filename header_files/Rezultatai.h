#ifndef REZULTATAI_H
#define REZULTATAI_H

#include <vector>

struct Rezultatai {
    std::vector<double> namuDarbuRezultatai;
    double egzaminoRezultatas;

    Rezultatai() : egzaminoRezultatas(0) {}
};

#endif //REZULTATAI_H
