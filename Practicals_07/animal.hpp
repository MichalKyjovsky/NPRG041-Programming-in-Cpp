//
// Created by mkyjovsky01 on 11/25/2020.
//

#ifndef LECTURE_07_ANIMAL_HPP
#define LECTURE_07_ANIMAL_HPP

#include <string>
#include <iostream>
#include <utility>


class Animal {
protected:
    unsigned int age;
    std::string name;

public:

    Animal(int age, std::string name) : age(age), name(std::move(name)) {}
    // Might be replaced by default ctor
    Animal(const Animal & animal) : age(animal.age), name(animal.name) {}

    Animal (Animal && animal) : age(animal.age), name(std::move(animal.name)) {}

    virtual ~Animal() = default;

    Animal &operator= (const Animal & animal) {
        this->age = animal.age;
        this->name = animal.name;
        return *this;
    }

    Animal &operator= (Animal && animal) {
        this->name = animal.name;
        this->age = animal.age;
    }

    std::string get_name() { return this->name;}

    unsigned int get_age() { return this->age;}

    virtual void print_animal() const {
        std::cout << "Hello abstract animal." << std::endl;
    };

    virtual std::unique_ptr<Animal> get_animal() const {
        return std::make_unique<Animal>(*this);;
    }
};


#endif //LECTURE_07_ANIMAL_HPP
