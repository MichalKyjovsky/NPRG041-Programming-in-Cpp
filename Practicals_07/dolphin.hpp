//
// Created by mkyjovsky01 on 11/25/2020.
//

#ifndef LECTURE_07_DOPHHIN_HPP
#define LECTURE_07_DOLPHIN_HPP

#include "animal.hpp"


class Dolphin : public Animal {
private:
    std::string ocean;

public:

    Dolphin (const std::string name, int age, std::string ocean) : Animal{age, name}, ocean{std::move(ocean)}  {}


    std::unique_ptr<Animal> get_animal() const override {
        return std::make_unique<Dolphin>(*this);
    }

    void print_animal() const override {
        std::cout << "Hello, I am dolphin " + this->name + ". I am " << this->age << " old and I live in " + this->ocean + " ocean." << std::endl;
    }
};

#endif //LECTURE_07_DOLPHIN_HPP
