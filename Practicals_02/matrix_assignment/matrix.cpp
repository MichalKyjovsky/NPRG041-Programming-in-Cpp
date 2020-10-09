//
// Created by mkyjovsky01 on 10/9/2020.
//

#include "matrix.hpp"


void Matrix::set(int x, int y, int value) {
    /* x determines the row space */

    if (x >= this->table.size()) {
        /* Allocate new row and append it to the table */
        std::vector<int> new_row(y + 1 , 0);
        this->table.push_back(new_row);
    } else if (this->table[x].size() >= y) {
        /* Extend column space */
        std::vector<int> new_row(y + 1, 0);
        copy_row(new_row, this->table[x]);
        auto it = this->table.begin() + x - 1;
        this->table.erase(it + table[x].size());
        it = this->table.begin();
        this->table.insert(it + x, new_row);
    }
        /* Overwrite or append the column to the table*/
        this->table[x][y] = value;
    }



void Matrix::print() {
    for (auto &&  row : this->table) {
        std::cout << "[ ";
        for (auto && column_index : row ) {
            std::cout << column_index << " ";
        }
        std::cout << "]" << std::endl;
    }
}

void Matrix::copy_row(std::vector<int> &new_row, std::vector<int> &original_row) {
    for (int i = 0; i < original_row.size(); i++) {
        new_row[i] = original_row[i];
    }
}


std::vector<int> &Matrix::get_row(int x) {
    int matrix_size = this->table.size();
    if (x <= matrix_size) {
        return this->table[x];
    } else {
        /* TODO: Provide better exception handling.*/
        std::cerr << "Your matrix has only: " << matrix_size
        << " records!" << std::endl;
        exit(1);
    }
}

std::vector<std::vector<int>> &Matrix::get_rows() {
    return this->table;
}

std::vector<int> Matrix::get_column(int y) {
    std::vector<int> output_column;
    for (auto && row : this->table) {
        output_column.push_back(row[y]);
    }
    return output_column;
}

std::vector<std::vector<int>> Matrix::transpose_matrix() {
    std::vector<std::vector<int>> transposed_matrix;
    std::vector<int> column;
    for (auto && row : this->table) {
        for (int & i : row) {
            column.push_back(i);
        }
        transposed_matrix.push_back(column);
    }
    return transposed_matrix;
}

void Matrix::normalize_matrix() {
    /*User might provided new row, which in length
     * does not corresponds to the others. Other
     * cells will be filled by zeros. */
    int matrix_width = this->get_matrix_width();

    for (int i = 0; i < this->table.size(); i++) {
       if (this->table[i].size() < matrix_width) {
           std::vector<int> extended_row(matrix_width, 0);
           this->copy_row(extended_row, this->table[i]);
           auto it = this->table.begin() + i - 1;
           this->table.erase(it + this->table[i].size());
           it = this->table.begin();
           /* Decrease iterator by one, since counting from 0.*/
           this->table.insert(it + matrix_width - 1, extended_row);
       }
    }

}

int Matrix::get_matrix_width() {
    int width = 0;

    for (auto && row : this->table) {
        if (row.size() > width) {
            width = row.size();
        }
    }
    return width;
}

std::vector<std::vector<int>> Matrix::get_columns() {
    return this->transpose_matrix();
}

void Matrix::clear() {
    fill_with_value(0);
}

void Matrix::fill_with_value(int value) {
    for(auto & row : this->table) {
        for (int & col_index : row) {
            col_index = value;
        }
    }
}

void Matrix::reverse() {
    this->table = this->transpose_matrix();
}

bool Matrix::is_negative() {
    for(auto & row : this->table) {
        for (int & col_index : row) {
            if (col_index < 0) {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> Matrix::get_negative() {
    std::vector<int> out_buffer;
    for(auto & row : this->table) {
        for (int & col_index : row) {
            if (col_index < 0) {
                out_buffer.push_back(col_index);
            }
        }
    }
    return out_buffer;
}


std::vector<int> Matrix::get_positive() {
    std::vector<int> out_buffer;
    for(auto & row : this->table) {
        for (int & col_index : row) {
            if (col_index >= 0) {
                out_buffer.push_back(col_index);
            }
        }
    }
    return out_buffer;
}

int Matrix::zero_count() {
    int zero_counter = 0;
    for(auto & row : this->table) {
        for (int & col_index : row) {
            if (col_index == 0) {
                zero_counter++;
            }
        }
    }
    return zero_counter;
}
