//
// Created by mkyjovsky01 on 11/7/2020.
//

#ifndef ARGUMENTS_CALC_NUM_VECTOR_HPP
#define ARGUMENTS_CALC_NUM_VECTOR_HPP

#include <memory>
#include <iostream>

class NumVector {
    // This is known to the user
    std::size_t current_size;
    // This is allocated on the background
    std::size_t current_capacity;
    std::unique_ptr<int[]> vec_ptr;

public:
    NumVector(std::size_t capacity) : current_capacity(2 * capacity),
                                      vec_ptr(std::make_unique<int[]>(this->current_capacity)),
                                      current_size(capacity) { }

    NumVector() : current_size(0) , current_capacity(0), vec_ptr(std::make_unique<int[]>(this->current_capacity)) { }

    int &operator[](std::size_t idx) {
        if (idx < this->current_size) {
            return vec_ptr[idx];
        } else {
            throw std::out_of_range("Index out of bound of range!");
        }
    }

    const int &operator[](std::size_t idx) const {
        if (idx < this->current_size) {
            return vec_ptr[idx];
        } else {
            throw std::out_of_range("Index out of bound of range!");
        }
    }

    std::size_t capacity() const;

    std::size_t size() const;

    void reserve(std::size_t new_cap);

    void push_back(int value);

    void resize(std::size_t count);

    void print() const;
};


#endif //ARGUMENTS_CALC_NUM_VECTOR_HPP
