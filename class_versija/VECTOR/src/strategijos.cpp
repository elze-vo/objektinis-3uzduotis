#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "Studentas.h"
#include "utils.h"

size_t calculateMemoryUsage(const std::vector<std::vector<Studentas>>& vectors) {
    size_t totalMemory = 0;

    for (const auto& vec : vectors) {
        totalMemory += sizeof(std::vector<Studentas>) + vec.capacity() * sizeof(Studentas);
        for (const auto& student : vec) {
            totalMemory += student.getVardas().capacity() * sizeof(char);
            totalMemory += student.getPavarde().capacity() * sizeof(char);
            totalMemory += student.getNamuDarbuRezultatai().capacity() * sizeof(double);
            totalMemory += sizeof(student.getEgzaminoRezultatas());
            totalMemory += sizeof(student.getFinalGrade());
        }
    }
    return totalMemory;
}

void strategija1(const std::vector<Studentas>& studentai, std::vector<Studentas>& neislaike, std::vector<Studentas>& islaike) {
    neislaike.clear();
    islaike.clear();

    neislaike.reserve(studentai.size());
    islaike.reserve(studentai.size());

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

void strategija2(std::vector<Studentas>& studentai, std::vector<Studentas>& neislaike) {
    neislaike.clear();
    size_t validCount = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < studentai.size(); ++i) {
        if (studentai[i].getFinalGrade() < 5.0) {
            neislaike.push_back(studentai[i]);
        }
        else {
            studentai[validCount] = studentai[i];
            ++validCount;
        }
    }

    studentai.resize(validCount);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double durationInMilliseconds = duration / 1'000'000.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Strategija 2 laikas: " << durationInMilliseconds << " ms\n";
    std::cout << "Strategija 2 atmintis: "
        << calculateMemoryUsage({ studentai, neislaike }) << " bytes\n";
}

void strategija3(std::vector<Studentas>& studentai, std::vector<Studentas>& neislaike) {
    neislaike.clear();
    neislaike.reserve(studentai.size());

    auto start = std::chrono::high_resolution_clock::now();

    auto partitionPoint = std::stable_partition(studentai.begin(), studentai.end(), [](const Studentas& student) {
        return student.getFinalGrade() >= 5.0;
        });

    std::move(partitionPoint, studentai.end(), std::back_inserter(neislaike));

    studentai.resize(std::distance(studentai.begin(), partitionPoint));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double durationInMilliseconds = duration / 1'000'000.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Strategija 3 laikas: " << durationInMilliseconds << " ms\n";
    std::cout << "Strategija 3 atmintis: "
        << calculateMemoryUsage({ studentai, neislaike }) << " bytes\n";
}
