//
// Created by mkyjovsky01 on 11/23/2020.
//

#include "duck_type_array.hpp"

int main() {
    DuckTypeArray duckTypeArray;
    duckTypeArray.push_back(1);
    duckTypeArray.push_back(2.3);
    duckTypeArray.push_back("four");

    duckTypeArray.print(0);
    duckTypeArray.print(2);
    duckTypeArray.print_all();

}