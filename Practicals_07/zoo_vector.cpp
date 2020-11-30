//
// Created by mkyjovsky01 on 11/25/2020.
//

#include "zoo_vector.hpp"

void ZooVector::add_animal(const Animal& animal) {
    this->zoo_db.push_back(animal.get_animal());
} // add animal to db

//void ZooVector::delete_animal(ZooVector::animal_iterator iterator) {
//    auto it = std::find(this->zoo_db.begin(), this->zoo_db.end(), iterator);
//    this->zoo_db.erase(it);
//}

void ZooVector::print_all() {
    // TODO: iterate over the vector of animals and call custom print
    for (auto & i : this->zoo_db){
        i->print_animal();
    }
}

static bool my_comparator(const std::shared_ptr<Animal>& a , const std::shared_ptr<Animal>& b ) {
    std::cout << "my_less\n";
    return a->get_name() < b->get_name();
}

std::pair<ZooVector::animal_vector::iterator, ZooVector::animal_vector::iterator> ZooVector::sort_by_name() {
    std::sort(this->zoo_db.begin(), this->zoo_db.end(), my_comparator);
    return std::make_pair(this->zoo_db.begin(), this->zoo_db.end());
}

//ZooVector::animal_iterator  ZooVector::sort_by_name() {
//    // TODO: use <algorithm> for instance heap sort with the appropriate container
//    return
//} // return iterator to animals ordered by the name
//ZooVector::animal_iterator  sort_by_age() {
//    // TODO: use <algorithm> for instance heap sort with the appropriate container
//} // return iterator to animals ordered by the age
//ZooVector::animal_iterator  get_name_range() {
//    // TODO: return range by name
//} // return name range iterator
//ZooVector::animal_iterator  get_age_range() {
//    // TODO: return range by age
//} // return age range iterator