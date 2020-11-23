//
// Created by mkyjovsky01 on 11/23/2020.
//

#ifndef LECTURE_05_OBJECT_TYPE_HPP
#define LECTURE_05_OBJECT_TYPE_HPP

#include <string>
#include <typeinfo>
#include <iostream>


class ObjectType {
public:
    virtual void print() const {
        std::cout << "ObjectType" << std::endl;
    }
    virtual void println() const {
        std::cout << "ObjectType" << std::endl;
    }
};


#endif //LECTURE_05_OBJECT_TYPE_HPP
