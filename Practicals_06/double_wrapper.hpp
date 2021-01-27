//
// Created by mkyjovsky01 on 11/23/2020.
//

#ifndef LECTURE_05_DOUBLE_WRAPPER_HPP
#define LECTURE_05_DOUBLE_WRAPPER_HPP

#include "object_type.hpp"

class DoubleWrapper : public ObjectType {
private:
    double self_value;

public:
    explicit DoubleWrapper(double value) : self_value(value) {}

    DoubleWrapper(const DoubleWrapper &DoubleWrapper) : self_value(DoubleWrapper.self_value) {}

    DoubleWrapper(DoubleWrapper &&DoubleWrapper) noexcept: self_value(DoubleWrapper.self_value) {}

    DoubleWrapper() {
        this->self_value = 0;
    };

    ~DoubleWrapper() = default;

    DoubleWrapper &operator=(const DoubleWrapper &DoubleWrapper) {
        this->self_value = DoubleWrapper.self_value;
        return *this;
    }

    DoubleWrapper &operator=(DoubleWrapper &&DoubleWrapper)  noexcept {
        this->self_value = DoubleWrapper.self_value;
    }

    void print() const override {
        std::cout << this->self_value;
    }
    void println() const override {
        std::cout << this->self_value << std::endl;
    }
};


#endif //LECTURE_05_DOUBLE_WRAPPER_HPP
