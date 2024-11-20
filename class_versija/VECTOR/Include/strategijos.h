#ifndef STRATEGIJOS_H
#define STRATEGIJOS_H

#include <vector>
#include "Studentas.h"

void strategija1(const std::vector<Studentas>& studentai, std::vector<Studentas>& neislaike, std::vector<Studentas>& islaike);

void strategija2(std::vector<Studentas>& studentai, std::vector<Studentas>& neislaike);

void strategija3(std::vector<Studentas>& studentai, std::vector<Studentas>& neislaike);

// Updated memory calculation function to work with class-based Studentas
size_t calculateMemoryUsage(const std::vector<Studentas>& studentai);

#endif // STRATEGIJOS_H
