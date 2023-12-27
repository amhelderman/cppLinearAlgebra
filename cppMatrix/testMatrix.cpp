#include <gtest/gtest.h>
#include "matrix.h"

// Define test cases here

// Example test case for matrix addition
TEST(MatrixTest, Addition) {
    // Create two matrices to add
    Matrix<int, 2, 2> mat1;
    Matrix<int, 2, 2> mat2;

    // Fill in values for mat1 and mat2 (customize as needed)
    // mat1 = [1, 2]
    //        [3, 4]
    // mat2 = [5, 6]
    //        [7, 8]
    mat1.set(0, 0, 1);
    mat1.set(0, 1, 2);
    mat1.set(1, 0, 3);
    mat1.set(1, 1, 4);

    mat2.set(0, 0, 5);
    mat2.set(0, 1, 6);
    mat2.set(1, 0, 7);
    mat2.set(1, 1, 8);

    // Perform matrix addition
    Matrix<int, 2, 2> result = mat1 + mat2;

    // Define the expected result (customize as needed)
    // expected = [6, 8]
    //            [10, 12]
    Matrix<int, 2, 2> expected;
    expected.set(0, 0, 6);
    expected.set(0, 1, 8);
    expected.set(1, 0, 10);
    expected.set(1, 1, 12);

    // Check if the result matches the expected value
    ASSERT_EQ(result, expected);
}

// Add more test cases as needed

// Test transpose 
TEST(MatrixTest, Transpose) {
    // Create a matrix to transpose
    Matrix<int, 2, 3> mat1;

    // Fill in values for mat1 (customize as needed)
    // mat1 = [1, 2, 3]
    //        [4, 5, 6]
    mat1.set(0, 0, 1);
    mat1.set(0, 1, 2);
    mat1.set(0, 2, 3);
    mat1.set(1, 0, 4);
    mat1.set(1, 1, 5);
    mat1.set(1, 2, 6);

    // Perform matrix transpose
    Matrix<int, 3, 2> result = mat1.transpose();

    // Define the expected result (customize as needed)
    // expected = [1, 4]
    //            [2, 5]
    //            [3, 6]
    Matrix<int, 3, 2> expected;
    expected.set(0, 0, 1);
    expected.set(0, 1, 4);
    expected.set(1, 0, 2);
    expected.set(1, 1, 5);
    expected.set(2, 0, 3);
    expected.set(2, 1, 6);

    // Check if the result matches the expected value
    ASSERT_EQ(result, expected);
}

// Test matrix multiplication
TEST(MatrixTest, Multiplication) {
    // Create two matrices to multiply
    Matrix<int, 2, 3> mat1;
    Matrix<int, 3, 2> mat2;

    // Fill in values for mat1 and mat2 (customize as needed)
    // mat1 = [1, 2, 3]
    //        [4, 5, 6]
    mat1.set(0, 0, 1);
    mat1.set(0, 1, 2);
    mat1.set(0, 2, 3);
    mat1.set(1, 0, 4);
    mat1.set(1, 1, 5);
    mat1.set(1, 2, 6);

    // mat2 = [7, 8]
    //        [9, 10]
    //        [11, 12]
    mat2.set(0, 0, 7);
    mat2.set(0, 1, 8);
    mat2.set(1, 0, 9);
    mat2.set(1, 1, 10);
    mat2.set(2, 0, 11);
    mat2.set(2, 1, 12);

    // Perform matrix multiplication
    Matrix<int, 2, 2> result = mat1 * mat2;

    // Define the expected result (customize as needed)
    // expected = [58, 64]
    //            [139, 154]
    Matrix<int, 2, 2> expected;
    expected.set(0, 0, 58);
    expected.set(0, 1, 64);
    expected.set(1, 0, 139);
    expected.set(1, 1, 154);

    // Check if the result matches the expected value
    ASSERT_EQ(result, expected);
}

// Test matrix multiplication with different types
TEST(MatrixTest, MultiplicationDifferentTypes) {
    // Create two matrices to multiply
    Matrix<int, 2, 3> mat1;
    Matrix<double, 3, 2> mat2;

    // Fill in values for mat1 and mat2 (customize as needed)
    // mat1 = [1, 2, 3]
    //        [4, 5, 6]
    mat1.set(0, 0, 1);
    mat1.set(0, 1, 2);
    mat1.set(0, 2, 3);
    mat1.set(1, 0, 4);
    mat1.set(1, 1, 5);
    mat1.set(1, 2, 6);

    // mat2 = [7.5, 8.5]
    //        [9.5, 10.5]
    //        [11.5, 12.5]
    mat2.set(0, 0, 7.5);
    mat2.set(0, 1, 8.5);
    mat2.set(1, 0, 9.5);
    mat2.set(1, 1, 10.5);
    mat2.set(2, 0, 11.5);
    mat2.set(2, 1, 12.5);

    // Perform matrix multiplication
    Matrix<double, 2, 2> result = mat1 * mat2;

    // Define the expected result (customize as needed)
    // expected = [58, 64]
    //            [139, 154]
    Matrix<double, 2, 2> expected;
    expected.set(0, 0, 61);
    expected.set(0, 1, 67);
    expected.set(1, 0, 146.5);
    expected.set(1, 1, 161.5);

    // Check if the result matches the expected value
    ASSERT_EQ(result, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
