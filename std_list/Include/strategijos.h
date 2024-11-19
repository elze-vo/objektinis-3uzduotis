#ifndef STRATEGIJOS_H
#define STRATEGIJOS_H

#include <list>
#include "Studentas.h"

void strategija1(const std::list<Studentas>& studentai, std::list<Studentas>& neislaike, std::list<Studentas>& islaike);

void strategija2(std::list<Studentas>& studentai, std::list<Studentas>& neislaike);

void strategija3(std::list<Studentas>& studentai, std::list<Studentas>& neislaike);

size_t calculateMemoryUsage(const std::list<Studentas>& studentai);

#endif // STRATEGIJOS_H
