#include "pch.h"

#include "C:\Users\Vartotojas\source\repos\objektinis-vector\Studentas.h"
#include <gtest/gtest.h>
#include <vector>

// Test default constructor
TEST(StudentasTests, DefaultConstructor) {
    Studentas student;
    EXPECT_EQ(student.getEgzaminoRezultatas(), 0);
    EXPECT_EQ(student.getFinalGrade(), 0);
    EXPECT_TRUE(student.getNamuDarbuRezultatai().empty());
}

// Test constructor with name and surname
TEST(StudentasTests, ConstructorWithNameAndSurname) {
    Studentas student("Jonas", "Jonaitis");

    // Test inherited properties
    EXPECT_EQ(student.getVardas(), "Jonas");
    EXPECT_EQ(student.getPavarde(), "Jonaitis");

    // Test Studentas-specific properties
    EXPECT_EQ(student.getEgzaminoRezultatas(), 0);
    EXPECT_EQ(student.getFinalGrade(), 0);
    EXPECT_TRUE(student.getNamuDarbuRezultatai().empty());
}

// Test constructor with all parameters
TEST(StudentasTests, FullConstructor) {
    std::vector<double> ndRezultatai = { 10, 8, 9 };
    Studentas student("Jonas", "Jonaitis", ndRezultatai, 9.5, 9.0);

    EXPECT_EQ(student.getEgzaminoRezultatas(), 9.5);
    EXPECT_EQ(student.getFinalGrade(), 9.0);
    EXPECT_EQ(student.getNamuDarbuRezultatai(), ndRezultatai);
}

// Test setters and getters
TEST(StudentasTests, SettersAndGetters) {
    Studentas student;

    // Set and check exam result
    student.setEgzaminoRezultatas(8.5);
    EXPECT_EQ(student.getEgzaminoRezultatas(), 8.5);

    // Set and check final grade
    student.setFinalGrade(8.0);
    EXPECT_EQ(student.getFinalGrade(), 8.0);

    // Set and check homework results
    std::vector<double> ndRezultatai = { 10, 9, 8 };
    student.setNamuDarbuRezultatai(ndRezultatai);
    EXPECT_EQ(student.getNamuDarbuRezultatai(), ndRezultatai);
}

// Test copy constructor
TEST(StudentasTests, CopyConstructor) {
    std::vector<double> ndRezultatai = { 10, 9, 8 };
    Studentas original("Jonas", "Jonaitis", ndRezultatai, 9.5, 9.0);
    Studentas copy = original;

    EXPECT_EQ(copy.getEgzaminoRezultatas(), 9.5);
    EXPECT_EQ(copy.getFinalGrade(), 9.0);
    EXPECT_EQ(copy.getNamuDarbuRezultatai(), ndRezultatai);
}

// Test copy assignment operator
TEST(StudentasTests, CopyAssignmentOperator) {
    std::vector<double> ndRezultatai = { 10, 9, 8 };
    Studentas original("Jonas", "Jonaitis", ndRezultatai, 9.5, 9.0);
    Studentas assigned;

    assigned = original;

    EXPECT_EQ(assigned.getEgzaminoRezultatas(), 9.5);
    EXPECT_EQ(assigned.getFinalGrade(), 9.0);
    EXPECT_EQ(assigned.getNamuDarbuRezultatai(), ndRezultatai);
}

// Test destructor (indirectly through memory cleanup)
TEST(StudentasTests, Destructor) {
    Studentas* student = new Studentas();
    student->setNamuDarbuRezultatai({ 10, 9, 8 });
    delete student;

    SUCCEED();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
