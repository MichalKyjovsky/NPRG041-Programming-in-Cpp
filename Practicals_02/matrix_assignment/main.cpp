#include <iostream>
#include "matrix.hpp"

int main() {
    Matrix matrix;

    matrix.set(0,0,1);
    matrix.set(0,1,2);
    matrix.set(0,2,3);

    matrix.set(1,0,4);
    matrix.set(1,1,-5);
    matrix.set(1,2,6);

    matrix.set(2,0,7);
    matrix.set(2,1,8);
    matrix.set(2,2,9);

    matrix.set(3,2,10);

    matrix.print();
//    for (auto && elm : matrix.get_column(1)) {
//        std::cout << elm << std::endl;
//    }

    matrix.reverse();
    matrix.print();

//    std::cout << matrix.is_negative() << std::endl;
}
