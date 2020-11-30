//
// Created by mkyjovsky01 on 11/25/2020.
//

#ifndef LECTURE_07_ZOO_VECTOR_HPP
#define LECTURE_07_ZOO_VECTOR_HPP


#include <memory>
#include "animal.hpp"
#include "lion.hpp"
#include "monkey.hpp"
#include "dolphin.hpp"
#include <iterator>
#include <vector>
#include <algorithm>

class ZooVector {
public:
    using animal_vector = std::vector<std::unique_ptr<Animal>>;
     animal_vector zoo_db;

    using animal_iterator = std::iterator<std::forward_iterator_tag , Animal>;
    ZooVector() = default;
    ZooVector(const ZooVector & zooVector) = default;
    ZooVector(ZooVector && zooVector) = default;
    ~ZooVector() = default;

    void add_animal(const Animal& animal); // add animal to db
    void delete_animal(animal_vector::iterator iterator);
    void print_all();
    std::pair<animal_vector::iterator, animal_vector::iterator> sort_by_name();
    std::pair<animal_vector::iterator, animal_vector::iterator> sort_by_age();
    std::pair<animal_vector::iterator, animal_vector::iterator>  get_name_range(const std::string& upper_bound, const std::string& lower_bound);
    std::pair<animal_vector::iterator, animal_vector::iterator>  get_age_range(unsigned int upper_bound, unsigned int lower_bound);
};


#endif //LECTURE_07_ZOO_VECTOR_HPP
