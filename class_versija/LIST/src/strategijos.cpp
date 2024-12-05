#include <list>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "Studentas.h"
#include "utils.h"

size_t calculateMemoryUsage(const std::list<std::list<Studentas>>& lists) {
    size_t totalMemory = 0;

    for (const auto& lst : lists) {
        totalMemory += sizeof(std::list<Studentas>);

        for (const auto& student : lst) {
            totalMemory += student.getVardas().capacity() * sizeof(char);
            totalMemory += student.getPavarde().capacity() * sizeof(char);
            totalMemory += student.getNamuDarbuRezultatai().size() * sizeof(double);
            totalMemory += sizeof(student.getEgzaminoRezultatas());
            totalMemory += sizeof(student.getFinalGrade());
        }
    }

    return totalMemory;
}

void strategija1(const std::list<Studentas>& studentai, std::list<Studentas>& neislaike, std::list<Studentas>& islaike) {
    neislaike.clear();
    islaike.clear();

    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& student : studentai) {
        if (student.getFinalGrade() < 5.0) {
            neislaike.push_back(student);
        }
        else {
            islaike.push_back(student);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double durationInMilliseconds = duration / 1'000'000.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Strategija 1 laikas: " << durationInMilliseconds << " ms\n";
    std::cout << "Strategija 1 atmintis: "
        << calculateMemoryUsage({ studentai, neislaike, islaike }) << " bytes\n";
}

void strategija2(std::list<Studentas>& studentai, std::list<Studentas>& neislaike) {
    neislaike.clear();

    auto start = std::chrono::high_resolution_clock::now();

    for (auto it = studentai.begin(); it != studentai.end(); ) {
        if (it->getFinalGrade() < 5.0) {
            neislaike.push_back(*it);
            it = studentai.erase(it);
        }
        else {
            ++it;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double durationInMilliseconds = duration / 1'000'000.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Strategija 2 laikas: " << durationInMilliseconds << " ms\n";
    std::cout << "Strategija 2 atmintis: "
        << calculateMemoryUsage({ studentai, neislaike }) << " bytes\n";
}

void strategija3(std::list<Studentas>& studentai, std::list<Studentas>& neislaike) {
    neislaike.clear();

    auto start = std::chrono::high_resolution_clock::now();

    for (auto it = studentai.begin(); it != studentai.end();) {
        if (it->getFinalGrade() < 5.0) {
            neislaike.splice(neislaike.end(), studentai, it++);
        }
        else {
            ++it;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double durationInMilliseconds = duration / 1'000'000.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Strategija 3 laikas: " << durationInMilliseconds << " ms\n";
    std::cout << "Strategija 3 atmintis: "
        << calculateMemoryUsage({ studentai, neislaike }) << " bytes\n";
}
