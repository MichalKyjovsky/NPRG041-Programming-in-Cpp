//
// Created by mkyjovsky01 on 10/17/2020.
//

#ifndef COMPLEX_NUMBER_CLASS_COMPLEX_NUMBER_HPP
#define COMPLEX_NUMBER_CLASS_COMPLEX_NUMBER_HPP

#include <iostream>

class ComplexNumber {
    int complex_part;
    int imaginary_part;
public:
    ComplexNumber(int rp, int ip) : complex_part(rp), imaginary_part(ip) {
        std::cout << "Complex number has been instantiated!" << std::endl;
    }

    ComplexNumber(const ComplexNumber &complexNumber) : complex_part(complexNumber.complex_part),
                                                        imaginary_part(complexNumber.imaginary_part) {
        std::cout << "Complex number has been instantiated from the existing copy!" << std::endl;
    }

    ComplexNumber(ComplexNumber && complexNumber) : complex_part(complexNumber.complex_part),
                                                    imaginary_part(complexNumber.imaginary_part) {
        /**
         * Does not make much sense to overwrite. There is no object (so far) to be moved.
         * */
        std::cout << "Complex number has been instantiated by move ops from existing object!" << std::endl;
    }

    //Compiler will handle de-allocation process of the int values
    ~ComplexNumber() {
        std::cout << "Object is being destructed by a destructor." << std::endl;
    };

    ComplexNumber &operator=(const ComplexNumber &complexNumber) {
        this->complex_part = complexNumber.complex_part;
        this->imaginary_part = complexNumber.imaginary_part;
        return *this;
    }
    ComplexNumber &operator=(ComplexNumber &&complexNumber) {
        /**
         * This is quite redundant overwrite, since the copy operation
         * is cheap (as was said on the practicals), therefore we do not
         * have to move the int variable. Yet it is good practice to
         * reimplement all class handling methods, once we started. */
        this->complex_part = complexNumber.complex_part;
        this->imaginary_part = complexNumber.complex_part;
    }
};


#endif //COMPLEX_NUMBER_CLASS_COMPLEX_NUMBER_HPP
