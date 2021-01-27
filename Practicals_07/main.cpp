//
// Created by mkyjovsky01 on 11/30/2020.
//

#include "zoo_vector.hpp"

int main() {
    Lion lion("Ragnar", 10, "Beef chop");
    Monkey monkey("Dexter", 3, "Stealing keys from the guards");
    Dolphin dolphin1("Terence", 6, "Pacific");
    Dolphin dolphin2("Phil", 7, "Indian");

    ZooVector zooVector;

    zooVector.add_animal(lion);
    zooVector.add_animal(monkey);
    zooVector.add_animal(dolphin1);
    zooVector.add_animal(dolphin2);

    zooVector.print_all();

    auto [first, last] = zooVector.get_age_range(3, 7);

//    zooVector.delete_animal(first);
//    zooVector.print_all();

//
    for(; first != last; ++first) {
        (*first)->print_animal();
    }

}