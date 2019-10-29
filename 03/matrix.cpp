#include "matrix.h"

Matrix::Row::Row(const size_t row_row, int* row):row_row(row_row),row(row)
{
}


int& Matrix::Row::operator[](size_t j)
{
    if ((j >= row_row) || (j < 0))
        throw std::out_of_range("Index problem with colomns!");
    else
        return row[j];
}


Matrix::Matrix(const size_t rows,const size_t columns):rows(rows),columns(columns)
{
    matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i)
        matrix[i] = new int[columns];
}


size_t Matrix::getRows() const
{
    return rows;
}


size_t Matrix::getColumns() const
{
    return columns;
}


Matrix::Row Matrix::operator[](const size_t i) const
{
    if ((i >= rows) || (i < 0))
        throw std::out_of_range("Index problem with rows!");
    else
        return Row(columns, matrix[i]);
}


Matrix& Matrix::operator*=(const size_t mul)
{
    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < columns; ++j)
            matrix[i][j] *= mul;
    }
    return (*this);
}


bool Matrix::operator==(const Matrix& m1) const
{
    if ((m1.getColumns()!=columns) || (m1.getRows()!=rows))
         return false;
    else
    {
        for(size_t i = 0; i<rows; ++i)
            for(size_t j = 0; j < columns; ++j)
                if (m1[i][j] != matrix[i][j])
                    return false;
        return true;
    }
}


bool Matrix::operator!=(const Matrix& m1) const
{
    return !((*this) == m1);
}


Matrix::~Matrix()
{
    for(size_t i = 0; i < rows; ++i)
        delete [] matrix[i];
    delete [] matrix;
}