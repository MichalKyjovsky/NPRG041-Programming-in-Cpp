//
// Created by mkyjovsky01 on 11/23/2020.
//

#ifndef LECTURE_05_INT_WRAPPER_HPP
#define LECTURE_05_INT_WRAPPER_HPP

#include "object_type.hpp"

class IntWrapper : public ObjectType {
private:
    int self_value;

public:
    explicit IntWrapper(int value) : self_value(value) {}

    IntWrapper(const IntWrapper &IntWrapper) : self_value(IntWrapper.self_value) {}

    IntWrapper(IntWrapper &&IntWrapper) noexcept: self_value(IntWrapper.self_value) {}

    IntWrapper() {
        this->self_value = 0;
    }

    ~IntWrapper() = default;

    IntWrapper &operator=(const IntWrapper &IntWrapper) {
        this->self_value = IntWrapper.self_value;
        return *this;
    }

    IntWrapper &operator=(IntWrapper &&IntWrapper)  noexcept {
        this->self_value = IntWrapper.self_value;
    }

    void print() const override {
        std::cout << this->self_value;;
    }
    void println() const override {
        std::cout << this->self_value << std::endl;;
    }
};

#endif //LECTURE_05_INT_WRAPPER_HPP
