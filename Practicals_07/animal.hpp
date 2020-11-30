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
    std::shared_ptr<Animal> animal_ptr;

public:

    Animal(int age, std::string name) : age(age), name(std::move(name)), animal_ptr(std::make_shared<Animal>(*this)) {}
    // Might be replaced by default ctor
    Animal(const Animal & animal) : age(animal.age), name(animal.name), animal_ptr(animal.animal_ptr) {}

    Animal (Animal && animal) : age(animal.age), name(std::move(animal.name)), animal_ptr(animal.animal_ptr) {}

    virtual ~Animal() = default;

    Animal &operator= (const Animal & animal) {
        this->age = animal.age;
        this->name = animal.name;
        this->animal_ptr = animal.animal_ptr;
        return *this;
    }

    Animal &operator= (Animal && animal) {
        this->name = animal.name;
        this->age = animal.age;
        this->animal_ptr = animal.animal_ptr;
    }

    std::string get_name() { return this->name; }

    virtual void print_animal() const {
        std::cout << "Hello abstract animal." << std::endl;
    };

    virtual std::shared_ptr<Animal> get_animal() const {
        return this->animal_ptr;
    }
};


#endif //LECTURE_07_ANIMAL_HPP
