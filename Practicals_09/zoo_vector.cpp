//
// Created by mkyjovsky01 on 12/09/2020.
//

#include <sstream>
#include "zoo_vector.hpp"

void ZooVector::add_animal(std::variant<Dolphin, Lion, Monkey> animal) {
    this->zoo_db.push_back(animal);
} // add animal to db

void ZooVector::print_all() const {
    for (auto &&it : this->zoo_db) {
        std::visit([](auto x) { x.print_animal(); }, it);
    }
}

void ZooVector::export_all_to_file(const std::string &file_name) const {
    {
        std::ofstream ostrm(file_name, std::ios::binary);
        std::streambuf *coutbuf = std::cout.rdbuf(); // save old buffer
        std::cout.rdbuf(ostrm.rdbuf());

        // Store all in the buffer
        this->print_all();

        // Reset the standard output
        std::cout.rdbuf(coutbuf);
    }
}

void ZooVector::import_from_file(const std::string &file_name) {
    std::ifstream fin;

    fin.open(file_name, std::ios::in);

    std::vector<std::string> record;
    std::string line, attr, temp;

    int val;

    while(std::getline(fin, line)) {
        record.clear();

        std::stringstream ss (line);

        while (std::getline(ss, attr, ',')) {
            record.push_back(attr);
        }


        if (record.at(0) == "lion") {
            this->zoo_db.push_back(Lion (record.at(1), std::stoi(record.at(2)), record.at(3)));
        } else if (record.at(0) == "dolphin") {
            this->zoo_db.push_back(Dolphin (record.at(1), std::stoi(record.at(2)), record.at(3)));
        } else if (record.at(0) == "monkey") {
            this->zoo_db.push_back(Monkey (record.at(1), std::stoi(record.at(2)), record.at(3)));
        } else {
            fin.close();
            throw std::invalid_argument("Unsupported animal type given");
        }
    }
    fin.close();
}


std::pair<ZooVector::animal_vector::iterator, ZooVector::animal_vector::iterator>
ZooVector::get_name_range(const std::string &lower_bound, const std::string &upper_bound) {
    auto[first, last] = this->sort_by_name();

    ZooVector::animal_vector::iterator lw_b;
    ZooVector::animal_vector::iterator up_b;

    for (; first != last; ++first) {
        if (((*first).index() == 0 && std::get<Dolphin>((*first)).get_name() >= lower_bound)
            || ((*first).index() == 1 && std::get<Lion>((*first)).get_name() >= lower_bound)
            || ((*first).index() == 2 && std::get<Monkey>((*first)).get_name() >= lower_bound)) {
            lw_b = first;
            break;
        }
    }
    for (; first != last; ++first) {
        if (((*first).index() == 0 && std::get<Dolphin>((*first)).get_name() >= upper_bound)
            || ((*first).index() == 1 && std::get<Lion>((*first)).get_name() >= upper_bound)
            || ((*first).index() == 2 && std::get<Monkey>((*first)).get_name() >= upper_bound)) {
            up_b = ++first;
            break;
        }
    }
    return std::make_pair(lw_b, up_b);
}

std::pair<ZooVector::animal_vector::iterator, ZooVector::animal_vector::iterator>
ZooVector::get_age_range(unsigned int lower_bound, unsigned int upper_bound) {
    auto[first, last] = this->sort_by_age();

    ZooVector::animal_vector::iterator lw_b;
    ZooVector::animal_vector::iterator up_b;

    for (; first != last; ++first) {
        if (((*first).index() == 0 && std::get<Dolphin>((*first)).get_age() >= lower_bound)
            || ((*first).index() == 1 && std::get<Lion>((*first)).get_age() >= lower_bound)
            || ((*first).index() == 2 && std::get<Monkey>((*first)).get_age() >= lower_bound)) {
            lw_b = first;
            break;
        }
    }
    for (; first != last; ++first) {
        if (((*first).index() == 0 && std::get<Dolphin>((*first)).get_age() >= upper_bound)
            || ((*first).index() == 1 && std::get<Lion>((*first)).get_age() >= upper_bound)
            || ((*first).index() == 2 && std::get<Monkey>((*first)).get_age() >= upper_bound)) {
            up_b = ++first;
            break;
        }
    }
    return std::make_pair(lw_b, up_b);
}


