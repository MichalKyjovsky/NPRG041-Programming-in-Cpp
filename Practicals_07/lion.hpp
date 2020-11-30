//
// Created by mkyjovsky01 on 11/25/2020.
//

#ifndef LECTURE_07_LION_HPP
#define LECTURE_07_LION_HPP

#endif //LECTURE_07_LION_HPP

#include <utility>

#include "animal.hpp"


class Lion : public Animal {
private:
    std::string favorite_meal;
    std::shared_ptr<Lion> lion_ptr;
public:


    std::shared_ptr<Animal> get_animal() const override {
        return this->lion_ptr;
    }

    Lion (const std::string name, int age, std::string favorite_meal) : Animal{age, name}, favorite_meal{std::move(favorite_meal)}, lion_ptr{std::make_shared<Lion>(*this)}  {}

    void print_animal() const override {
        std::cout << "Hello, I am lion " + this->name + ". I am " << this->age << " old and my favorite meal is " + this->favorite_meal + "." << std::endl;
    }
};