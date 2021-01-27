//
// Created by mkyjovsky01 on 11/23/2020.
//

#ifndef LECTURE_05_DUCK_TYPE_ARRAY_HPP
#define LECTURE_05_DUCK_TYPE_ARRAY_HPP

#include "object_type.hpp"
#include "string_wrapper.hpp"
#include "int_wrapper.hpp"
#include "double_wrapper.hpp"
#include <vector>
#include <iostream>

class DuckTypeArray {
private:
    std::vector<ObjectType *> various_type_vector;
public:
    void push_back(int value);
    void push_back(std::string value);
    void push_back(double value);
    void print(size_t ith_element);
    void print_all();
};


#endif //LECTURE_05_DUCK_TYPE_ARRAY_HPP
