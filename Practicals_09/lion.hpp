//
// Created by mkyjovsky01 on 12/09/2020.
//

#ifndef LECTURE_09_LION_HPP
#define LECTURE_09_LION_HPP

#endif //LECTURE_09_LION_HPP

#include <utility>

#include "animal.hpp"


class Lion : public Animal {
private:
    std::string favorite_meal;

public:

    std::unique_ptr<Animal> get_animal() const override {
        return std::make_unique<Lion>(*this);
    }

    Lion (const std::string name, int age, std::string favorite_meal) : Animal{age, name}, favorite_meal{std::move(favorite_meal)}  {}

    void print_animal() const override {
        std::cout << "Hello, I am lion " + this->name + ". I am " << this->age << " old and my favorite meal is " + this->favorite_meal + "." << std::endl;
    }
};