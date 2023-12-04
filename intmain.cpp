#include <iostream>
#include "matrix.hpp"

int main() {
    Matrix matrix1(3, 3);
    matrix1.set_element(0, 0, 1);
    matrix1.set_element(0, 1, 2);
    matrix1.set_element(0, 2, 2);
    matrix1.set_element(1, 0, 10);
    matrix1.set_element(1, 1, 2);
    matrix1.set_element(1, 2, 4);
    matrix1.set_element(2, 0, 3);
    matrix1.set_element(2, 1, 7);
    matrix1.set_element(2, 2, 1);
    matrix1.Output();
    Matrix matrix2 = matrix1.InverseMatrix();
    matrix2.Output();
    return 0;
}
