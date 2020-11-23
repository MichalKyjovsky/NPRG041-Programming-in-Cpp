//
// Created by mkyjovsky01 on 11/11/2020.
//

#include <iostream>
#include <vector>
#include <iomanip>
class matrix {
public:
    using value_type = int;
    using row_type = std::vector<value_type>;
    using data_type = std::vector<row_type>;
    using size_type = size_t;

    data_type data;

    // ctor
    // filling defined type with int !!! Ugly
    matrix() {
        // Using size_type instead
        data = data_type(10, row_type(10, 0));
    }

    // ctor
    // using value_type() ctor -> that the hek
    matrix(int width, int height, value_type init_value = value_type()) {
        data = data_type(height, row_type(width, init_value));
    }

    // copy-ctor
    // missing const in parameter
    matrix(const matrix &m) : data(m.data) {}

    // move-ctor
    matrix(matrix &&m) : data(m.data) {}

    /*
     * Add destructor and redefine operators = copy=
     * */

    // Use size_typea ne 
    size_t width() {
        // Add check that data is not empty or is instantiated
        return data[0].size();
    }

    size_t height() {
        return data.size();
    }

    // missing '&'
    row_type &operator[](size_type height_idx) {
        // Check if the index is within the boundary
        return data[height_idx];
    }

    void clear() {
        for (auto i = 0; i < width(); ++i) {
            for (auto j = 0; j < height(); ++j) {
                // Use value_type default number
                data[i][j] = 0;
            }
        }
    }

    void print() {
        for (auto i = 0; i < width(); ++i) {
            for (auto j = 0; j < height(); ++j) {
                std::cout << std::setw(3) << data[i][j];
            }
            std::cout << '\n'; // Use std::endl instead
        }
    }
};

// Use reference
void fill(matrix &m) {
    // use width() and height() and avoid magic numbers !!!
    for (auto i = 0; i < 10; ++i) {
        for (auto j = 0; j < 10; ++j) {
            // m.data was missing m is class
            m.data[i][j] = i * 10 + j;
        }
    }
}