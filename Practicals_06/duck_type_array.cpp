//
// Created by mkyjovsky01 on 11/23/2020.
//

#include "duck_type_array.hpp"


void DuckTypeArray::push_back(std::string value) {
    this->various_type_vector.push_back(new StringWrapper(std::move(value)));
}

void DuckTypeArray::push_back(int value) {
    this->various_type_vector.push_back(new IntWrapper(value));
}

void DuckTypeArray::push_back(double value) {
    this->various_type_vector.push_back(new DoubleWrapper(value));
}

void DuckTypeArray::print(size_t ith_element) {
    this->various_type_vector.at(ith_element)->println();
}

void DuckTypeArray::print_all() {
    for (const ObjectType* objectType : this->various_type_vector) {
        objectType->print();
        std::cout << " ";
    }
    std::cout << std::endl;
}
