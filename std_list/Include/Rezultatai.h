#ifndef REZULTATAI_H
#define REZULTATAI_H

#include <list>

struct Rezultatai {
    std::list<double> namuDarbuRezultatai;
    double egzaminoRezultatas;

    Rezultatai() : egzaminoRezultatas(0) {}
};

#endif //REZULTATAI_H
