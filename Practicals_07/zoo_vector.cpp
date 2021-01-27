//
// Created by mkyjovsky01 on 11/25/2020.
//

#include "zoo_vector.hpp"

void ZooVector::add_animal(const Animal& animal) {
    this->zoo_db.push_back(std::move(animal.get_animal()));
} // add animal to db

void ZooVector::delete_animal(ZooVector::animal_vector::iterator iterator) {
    auto it = std::find(this->zoo_db.begin(), this->zoo_db.end(), *iterator);
    this->zoo_db.erase(it);
}

void ZooVector::print_all() {
    for (auto && it : this->zoo_db){
        it->print_animal();
    }
}

static bool my_comparator(const std::unique_ptr<Animal>& a , const std::unique_ptr<Animal>& b ) {
    return a->get_name() < b->get_name();
}
std::pair<ZooVector::animal_vector::iterator, ZooVector::animal_vector::iterator> ZooVector::sort_by_name() {
    std::sort(this->zoo_db.begin(), this->zoo_db.end(), my_comparator);
    return std::make_pair(this->zoo_db.begin(), this->zoo_db.end());
}

static bool my_comparator_age(const std::unique_ptr<Animal>& a , const std::unique_ptr<Animal>& b ) {
    return a->get_age() < b->get_age();
}

std::pair<ZooVector::animal_vector::iterator, ZooVector::animal_vector::iterator> ZooVector::sort_by_age() {
    std::sort(this->zoo_db.begin(), this->zoo_db.end(), my_comparator_age);
    return std::make_pair(this->zoo_db.begin(), this->zoo_db.end());
}

std::pair<ZooVector::animal_vector::iterator, ZooVector::animal_vector::iterator>
ZooVector::get_name_range(const std::string& lower_bound, const std::string& upper_bound) {
    auto [first, last] = this->sort_by_name();

    ZooVector::animal_vector::iterator lw_b;
    ZooVector::animal_vector::iterator up_b;

    for(; first != last; ++first) {
        if ((*first)->get_name() >= lower_bound) {
            lw_b = first;
            break;
        }
    }
    for(; first != last; ++first) {
        if ((*first)->get_name() >= upper_bound) {
            up_b = ++first;
            break;
        }
    }
    return std::make_pair(lw_b, up_b);
}

std::pair<ZooVector::animal_vector::iterator, ZooVector::animal_vector::iterator>
ZooVector::get_age_range(unsigned int lower_bound, unsigned int upper_bound) {
    auto [first, last] = this->sort_by_age();

    ZooVector::animal_vector::iterator lw_b;
    ZooVector::animal_vector::iterator up_b;

    for(; first != last; ++first) {
        if ((*first)->get_age() >= lower_bound) {
            lw_b = first;
            break;
        }
    }
    for(; first != last; ++first) {
        if ((*first)->get_age() >= upper_bound) {
            up_b = ++first;
            break;
        }
    }
    return std::make_pair(lw_b, up_b);}
