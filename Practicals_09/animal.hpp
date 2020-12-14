//
// Created by mkyjovsky01 on 12/9/2020.
//

#ifndef LECTURE_09_ANIMAL_HPP
#define LECTURE_09_ANIMAL_HPP

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
    Animal(const Animal & animal)  = default;

    Animal (Animal && animal)  noexcept : age(animal.age), name(std::move(animal.name)) {}

    virtual ~Animal() = default;

    Animal &operator= (const Animal & animal) {
        this->age = animal.age;
        this->name = animal.name;
        return *this;
    }

    Animal &operator= (Animal && animal)  noexcept {
        this->name = animal.name;
        this->age = animal.age;
    }

    [[nodiscard]] std::string get_name() const { return this->name;}

    [[nodiscard]] unsigned int get_age() const { return this->age;}

    virtual void print_animal() const {
        std::cout << "Hello abstract animal." << std::endl;
    };

    [[nodiscard]] virtual std::unique_ptr<Animal> get_animal() const {
        return std::make_unique<Animal>(*this);;
    }
};


#endif //LECTURE_09_ANIMAL_HPP
