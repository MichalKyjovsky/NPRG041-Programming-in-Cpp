//
// Created by mkyjovsky01 on 10/14/2020.
//

#ifndef PRACTICALS_03_C_HPP
#define PRACTICALS_03_C_HPP

#include <iostream>

class C {
    int x = 0;
    bool move_ops;
public:
    C() {
        std::cout << " 2 3 4 ";
        move_ops = false;
    }

    C(const C &c) : x(c.x) {
        std::cout << " 6 7 8 9 ";
        move_ops = true;
    }

    C(C &&c) : x(c.x) {
        std::cout << " 11 12 13 14 ";
        move_ops = true;
    }

    ~C() {
        if (move_ops) { ;
        } else {
            std::cout << " 16 17 18 19 20";
        }
    }

    C &operator=(const C &c) {
        x = c.x;
        std::cout << "copy-op\n";
        return *this;
    }
    C &operator=(C &&c) {
        x = c.x;
        std::cout << "move-op\n";
    }
};


#endif //PRACTICALS_03_C_HPP
