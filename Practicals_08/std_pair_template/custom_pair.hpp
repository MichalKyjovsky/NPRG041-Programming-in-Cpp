//
// Created by mkyjovsky01 on 12/2/2020.
//

#ifndef KYJOVSKY_CUSTOM_PAIR_HPP
#define KYJOVSKY_CUSTOM_PAIR_HPP

#include <iostream>

template< typename T1, typename T2>
class CustomPair {
protected:

    typedef T1 _first_type;
    typedef T2 _second_type;

public:
    T1 _first;
    T2 _second;

    CustomPair() {};
    CustomPair(T1 _first, T2 _second) : _first{_first}, _second{_second} {}
    CustomPair(const  CustomPair<T1, T2> & pair) : _first{pair._first}, _second{pair._second} {}
    CustomPair( CustomPair<T1, T2> && pair)  noexcept : _first{std::move(pair._first)}, _second{std::move(pair._second)} {}

    //TODO: Might needs to be implemented
    ~CustomPair()=default;

    CustomPair &operator= (const CustomPair & customPair) {
        this->_first = customPair._first;
        this->_second = customPair._second;
        return *this;
    }

    CustomPair &operator= (CustomPair && customPair) {
        this->_first = std::move(customPair._first);
        this->_second = std::move(customPair._second);
    }

    CustomPair make_pair(T1 && first_param, T2 && second_param) {
        this->_first = first_param;
        this->_second = second_param;
    }

};


#endif //KYJOVSKY_CUSTOM_PAIR_HPP
