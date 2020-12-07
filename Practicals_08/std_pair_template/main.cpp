//
// Created by mkyjovsky01 on 12/2/2020.
//

#include "custom_pair.hpp"

int main() {

    CustomPair<int,int> foo;
    CustomPair<int,int> bar;

    foo = foo.make_pair (10,20);
    bar = foo.make_pair (10.5,'A'); // TODO: implicit conversion from pair<double,char>

    std::cout << "foo: " << foo._first << ", " << foo._second << std::endl;
    std::cout << "bar: " << bar._first << ", " << bar._second << std::endl; // TODO :Yep, this is not perfect

    return 0;
}