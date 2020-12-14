//
// Created by mkyjovsky01 on 12/09/2020.
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

    std::cout << "******************** PRINT ALL ********************" << std::endl;
    zooVector.print_all();
    std::cout << "******************** PRINT ALL ********************" << std::endl;
//    zooVector.export_all_to_file("zoo.txt");

    std::cout << "******************** SORT BY AGE ********************" << std::endl;
//    zooVector.sort_by_age();
//    zooVector.print_all();
    std::cout << "******************** SORT BY AGE ********************" << std::endl;
    std::cout << "******************** SORT BY NAME ********************" << std::endl;
    zooVector.sort_by_name();
    zooVector.print_all();
    std::cout << "******************** SORT BY NAME ********************" << std::endl;
//    std::cout << "******************** AGE RANGE ********************" << std::endl;
//
//    auto[first, last] = zooVector.get_age_range(3, 7);
//
//    for (; first != last; ++first) {
//        switch ((*first).index()) {
//            case 0:
//                std::get<Dolphin>((*first)).print_animal();
//                break;
//            case 1:
//                std::get<Lion>((*first)).print_animal();
//                break;
//            case 2:
//                std::get<Monkey>((*first)).print_animal();
//                break;
//        }
//    }
//    std::cout << "******************** AGE RANGE ********************" << std::endl;
    std::cout << "******************** NAME RANGE ********************" << std::endl;

    auto[first, last] = zooVector.get_name_range("R", "T");

    for (; first != last; ++first) {
        switch ((*first).index()) {
            case 0:
                std::get<Dolphin>((*first)).print_animal();
                break;
            case 1:
                std::get<Lion>((*first)).print_animal();
                break;
            case 2:
                std::get<Monkey>((*first)).print_animal();
                break;
        }
    }
    std::cout << "******************** NAME RANGE ********************" << std::endl;
    std::cout << "******************** FILE IMPORT ********************" << std::endl;
    zooVector.import_from_file("zoo_in.csv");
    zooVector.print_all();
    std::cout << "******************** FILE IMPORT ********************" << std::endl;

}