//
// Created by mkyjovsky01 on 11/7/2020.
//

#ifndef ARGUMENTS_CALC_NUM_VECTOR_HPP
#define ARGUMENTS_CALC_NUM_VECTOR_HPP

#include <memory>
#include <iostream>

template<typename T>
class NumVector {
    // This is known to the user
    std::size_t current_size;
    // This is allocated on the background
    std::size_t current_capacity;
    std::unique_ptr<T[]> vec_ptr;

public:

    NumVector(std::size_t capacity) : current_capacity(2 * capacity),
                                      vec_ptr(std::make_unique<T[]>(this->current_capacity)),
                                      current_size(capacity) { }

    NumVector() : current_size(0) , current_capacity(0), vec_ptr(std::make_unique<T[]>(this->current_capacity)) { }

    T &operator[](std::size_t idx) {
        if (idx < this->current_size) {
            return vec_ptr[idx];
        } else {
            throw std::out_of_range("Index out of bound of range!");
        }
    }

    const T &operator[](std::size_t idx) const {
        if (idx < this->current_size) {
            return vec_ptr[idx];
        } else {
            throw std::out_of_range("Index out of bound of range!");
        }
    }

    std::size_t capacity() const {
        return this->current_capacity;
    }

    std::size_t size() const {
        return this->current_size;
    }

    void reserve(std::size_t new_cap) {
        if (new_cap > this->current_size) {
            this->current_capacity = 2 * new_cap;
            std::unique_ptr<T[]> resized_num_vector = std::make_unique<T[]>(this->current_capacity);

            for (int i = 0; i < this->current_size; i++) {
                resized_num_vector[i] = this->vec_ptr[i];
            }

            this->current_size = new_cap;
            this->vec_ptr = std::move(resized_num_vector);
        } else {
            std::cerr << "**ERROR**: Attempt to allocate less than you actually have!" << std::endl;
        }


    }

    void push_back(const T & value) {
        if (this->current_size == this->current_capacity) {
            this->reserve(this->current_capacity);
        }
        this->vec_ptr[this->current_size] = value;
        this->current_size++;
    }

    void resize(std::size_t count) {
        if (count < this->current_size) {
            this->current_capacity = 2 * count;
            std::unique_ptr<T[]> temp = std::make_unique<T[]>( this->current_capacity);

            for (int i = 0; i < count; i++) {
                temp[i] = this->vec_ptr[i];
            }
            this->current_size = count;
            this->vec_ptr = std::move(temp);
        } else if (count > this->current_size) {
            this->reserve(count);
        }
        /*
         * If the current size and the provided size are equal, let's take
         * a break.
         * */

    }
    void print() const {
        for (int i = 0; i < this->current_size; i++) {
            std::cout << this->vec_ptr[i] << std::endl;
        }
    }
};


#endif //ARGUMENTS_CALC_NUM_VECTOR_HPP
