//
// Created by mkyjovsky01 on 12/09/2020.
//

#ifndef LECTURE_09_MONKEY_HPP
#define LECTURE_09_MONKEY_HPP


#include "animal.hpp"


class Monkey : public Animal {
private:
    std::string preferred_activity;

public:

    Monkey (const std::string name, int age, std::string preferred_activity) : Animal{age, name}, preferred_activity{std::move(preferred_activity)} {}


    std::unique_ptr<Animal> get_animal() const override {
        return std::make_unique<Monkey>(*this);
    }

    void print_animal() const override {
        std::cout << "Hello, I am monkey " + this->name + ". I am " << this->age << " old and I like to " + this->preferred_activity + "." << std::endl;
    }
};


#endif //LECTURE_09_MONKEY_HPP
