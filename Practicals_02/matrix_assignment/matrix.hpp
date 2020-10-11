//
// Created by mkyjovsky01 on 10/9/2020.
//

#ifndef PRACTICALS_02_MATRIX_HPP
#define PRACTICALS_02_MATRIX_HPP

#include <iostream>
#include <vector>

class Matrix {
    private:
        std::vector<std::vector<int>> table;
        static void copy_row(std::vector<int>& new_row, std::vector<int>& original_row);
        std::vector<std::vector<int>> transpose_matrix();
        void normalize_matrix();
        int get_matrix_width();

    public:
        void set(int x, int y, int value);
        void print();
        std::vector<int>& get_row(int x);
        std::vector<std::vector<int>>& get_rows();
        std::vector<int> get_column(int y);
        std::vector<std::vector<int>> get_columns();
        void clear();
        void fill_with_value(int value);
        void reverse();
        bool is_negative();
        std::vector<int> get_negative();
        std::vector<int> get_positive();
        int zero_count();
};


#endif //PRACTICALS_02_MATRIX_HPP
