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
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

class ZooVector {
public:
    using animal_vector = std::vector<std::shared_ptr<Animal>>;
     animal_vector zoo_db;

    using animal_iterator = std::iterator<std::forward_iterator_tag , Animal>;
    ZooVector() = default;
    ZooVector(const ZooVector & zooVector) = default;
    ZooVector(ZooVector && zooVector) = default;
    ~ZooVector() = default;

    void add_animal(const Animal& animal); // add animal to db
//    void delete_animal(animal_iterator);
    void print_all();
    std::pair<animal_vector::iterator, animal_vector::iterator> sort_by_name(); // return iterator to animals ordered by the name # proposal: output iterator
//    std::pair<animal_vector::iterator, animal_vector::iterator> sort_by_age(); // return iterator to animals ordered by the age # proposal: output iterator
//    animal_iterator  get_name_range(); // return name range iterator # proposal: output iterator
//    animal_iterator  get_age_range(); // return age range iterator # proposal: output iterator
};


#endif //LECTURE_07_ZOO_VECTOR_HPP
