//
// Created by mkyjovsky01 on 11/30/2020.
//

#include "zoo_vector.hpp"

int main() {
    Lion lion("Ragnar", 10, "Beef chop");
    Monkey monkey("Dexter", 3, "Stealing keys from the guards");
    Dolphin dolphin("Terence", 6, "Pacific");

    ZooVector zooVector;

    zooVector.add_animal(lion);
    zooVector.add_animal(monkey);
    zooVector.add_animal(dolphin);

    zooVector.print_all();

    auto [first, last] = zooVector.sort_by_name();
    for(; first != last; ++first) {
        (*first)->print_animal();
    }


}