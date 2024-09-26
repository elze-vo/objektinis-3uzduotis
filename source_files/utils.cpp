#include <vector>
#include <algorithm>
#include "utils.h"

using namespace std;

double calculateMedian(vector<int>& grades) {
    sort(grades.begin(), grades.end());
    size_t size = grades.size();
    if (size == 0) return 0.0;
    if (size % 2 == 0) {
        return (grades[size / 2 - 1] + grades[size / 2]) / 2.0;
    }
    return grades[size / 2];
}

bool compareByLastName(const Studentas& a, const Studentas& b) {
    return a.pavarde < b.pavarde;
}

