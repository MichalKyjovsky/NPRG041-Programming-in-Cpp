//
// Created by mkyjovsky01 on 11/7/2020.
//

#include "num_vector.hpp"

std::size_t NumVector::capacity() {
    return this->current_capacity;
}
std::size_t NumVector::size() const {
    return this->current_size;
}

void NumVector::reserve(std::size_t new_cap) {
    if (new_cap > this->current_size) {
        this->current_capacity = 2 * new_cap;
        std::unique_ptr<int[]> resized_num_vector = std::make_unique<int[]>(this->current_capacity);

        for (int i = 0; i < this->current_size; i++) {
            resized_num_vector[i] = this->vec_ptr[i];
        }

        this->current_size = new_cap;
        this->vec_ptr = std::move(resized_num_vector);
    } else {
        std::cerr << "**ERROR**: Attempt to allocate less than you actually have!" << std::endl;
    }


}

void NumVector::push_back(int value) {
    if (this->current_size == this->current_capacity) {
        this->reserve(this->current_capacity);
    }
    this->vec_ptr[this->current_size] = value;
    this->current_size++;
}

void NumVector::resize(std::size_t count) {
    if (count < this->current_size) {
        this->current_capacity = 2 * count;
        std::unique_ptr<int[]> temp = std::make_unique<int[]>( this->current_capacity);

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

void NumVector::print() {
    for (int i = 0; i < this->current_size; i++) {
        std::cout << this->vec_ptr[i] << std::endl;
    }
}
