#pragma once
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>

class Matrix
{
private:
    size_t rows;
    size_t columns;
    int** matrix;
    class Row
    {
        private:
            size_t row_row;
            int* row;
        public:
            Row(size_t row_row, int* row);
            int& operator[](const size_t j);
    };
    
public:
    size_t getRows() const;
    size_t getColumns() const;
    Matrix(const size_t rows, const size_t columns);
    Row operator[](const size_t i) const;
    Matrix& operator*=(const size_t mul);
    bool operator==(const Matrix& m1) const;
    bool operator!=(const Matrix& m1) const;
    ~Matrix();
};