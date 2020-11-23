#include <iostream>
#include "complex_number.hpp"

using namespace std;

void fn_copy(ComplexNumber) {}

void fn_cref(const ComplexNumber&) {}

int main() {
    ComplexNumber complexNumber(1, 2);
    fn_copy(complexNumber);
    fn_cref(complexNumber);
    fn_copy(move(complexNumber));
    return 0;
}
