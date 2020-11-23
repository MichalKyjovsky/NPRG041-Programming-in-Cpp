#include <iostream>
#include "C.hpp"


void fn_copy(C) {}

void fn_cref(const C &) {}

int main(int argc, char *argv[]) {
    std::cout << "1";
    C c;
    std::cout << "5";
    fn_copy(c);
    std::cout << "10";
    fn_cref(c);
    fn_copy(std::move(c));
    std::cout << "15";
}
