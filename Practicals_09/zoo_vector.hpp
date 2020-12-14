//
// Created by mkyjovsky01 on 12/09/2020.
//

#ifndef LECTURE_09_ZOO_VECTOR_HPP
#define LECTURE_09_ZOO_VECTOR_HPP


#include <memory>
#include "animal.hpp"
#include "lion.hpp"
#include "monkey.hpp"
#include "dolphin.hpp"
#include <iterator>
#include <vector>
#include <algorithm>
#include <variant>
#include <fstream>

class ZooVector {

public:
    using animal_vector = std::vector<std::variant<Dolphin, Lion, Monkey>>;
    animal_vector zoo_db;

    ZooVector() = default;

    ZooVector(const ZooVector &zooVector) = default;

    ZooVector(ZooVector &&zooVector) = default;

    ~ZooVector() = default;

    void add_animal(std::variant<Dolphin, Lion, Monkey> animal); // add animal to db

    void print_all() const;

    void export_all_to_file(const std::string &file_name) const;

    void import_from_file(const std::string &file_name);

    static bool
    my_comparator_age(const std::variant<Dolphin, Lion, Monkey> &a, const std::variant<Dolphin, Lion, Monkey> &b) {
        std::vector<unsigned int> results;

        std::vector<std::variant<Dolphin, Lion, Monkey>> in_variants = {a, b};

        for (auto const &var : in_variants)
            switch (var.index()) {
                case 0:
                    results.push_back(std::get<Dolphin>(var).get_age());
                    break;
                case 1:
                    results.push_back(std::get<Lion>(var).get_age());
                    break;
                case 2:
                    results.push_back(std::get<Monkey>(var).get_age());
                    break;
            }
        return results.at(0) < results.at(1);
    }


    static bool
    my_comparator_name(const std::variant<Dolphin, Lion, Monkey> &a, const std::variant<Dolphin, Lion, Monkey> &b) {
        std::vector<std::string> results;

        std::vector<std::variant<Dolphin, Lion, Monkey>> in_variants = {a, b};

        for (auto const &var : in_variants)
            switch (var.index()) {
                case 0:
                    results.push_back(std::get<Dolphin>(var).get_name());
                    break;
                case 1:
                    results.push_back(std::get<Lion>(var).get_name());
                    break;
                case 2:
                    results.push_back(std::get<Monkey>(var).get_name());
                    break;
            }
        return results.at(0) < results.at(1);
    }

    std::pair<animal_vector::iterator, animal_vector::iterator> sort_by_name() {
        std::sort(this->zoo_db.begin(), this->zoo_db.end(), my_comparator_name);
        return std::make_pair(this->zoo_db.begin(), this->zoo_db.end());
    }

    std::pair<animal_vector::iterator, animal_vector::iterator> sort_by_age() {
        std::sort(this->zoo_db.begin(), this->zoo_db.end(), my_comparator_age);
        return std::make_pair(this->zoo_db.begin(), this->zoo_db.end());
    }

    std::pair<animal_vector::iterator, animal_vector::iterator>
    get_name_range(const std::string &upper_bound, const std::string &lower_bound);

    std::pair<animal_vector::iterator, animal_vector::iterator>
    get_age_range(unsigned int upper_bound, unsigned int lower_bound);


};


#endif //LECTURE_09_ZOO_VECTOR_HPP
