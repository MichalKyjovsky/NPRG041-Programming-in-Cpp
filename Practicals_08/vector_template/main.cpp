//
// Created by mkyjovsky01 on 11/7/2020.
//


#include "num_vector.hpp"

int main() {
    NumVector<float> numVector(2);
    numVector[0] = 1;
    numVector[1] = 1;
    numVector.reserve(4);
    numVector.print();

    numVector.push_back(24);
    numVector.print();

    numVector.resize(2);
    numVector.print();


}