//
// Created by mkyjovsky01 on 11/23/2020.
//

#ifndef LECTURE_05_STRING_WRAPPER_HPP
#define LECTURE_05_STRING_WRAPPER_HPP

#include <utility>

#include "object_type.hpp"

class StringWrapper : public ObjectType {
private:
    std::string self_value;

public:
    explicit StringWrapper(std::string value) : self_value(std::move(value)) {}
    StringWrapper(const StringWrapper & stringWrapper) : self_value(stringWrapper.self_value) {}
    StringWrapper(StringWrapper && stringWrapper)  noexcept : self_value(std::move(stringWrapper.self_value)) {}

    StringWrapper() = default;
    ~StringWrapper() = default;

    StringWrapper &operator= (const StringWrapper & stringWrapper) {
            this->self_value = stringWrapper.self_value;
            return *this;
    }
    StringWrapper &operator=(StringWrapper && stringWrapper)  noexcept {
            this->self_value = stringWrapper.self_value;
    }

    void print() const override {
        std::cout << this->self_value;
    }
    void println() const override {
        std::cout << this->self_value << std::endl;
    }
};


#endif //LECTURE_05_STRING_WRAPPER_HPP
