//
// Created by mkyjovsky01 on 11/7/2020.
//

#include <iostream>
#include <vector>
#include "num_vector.hpp"

int main() {
    NumVector ax(2);
    ax[0] = 1;
    ax[1] = 1;
    ax.reserve(4);
    ax.print();

    ax.push_back(24);
    ax.print();

    ax.resize(2);
    ax.print();


}