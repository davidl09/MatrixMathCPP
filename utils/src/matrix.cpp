#include "rational.hpp"
#include "matrix.hpp"

namespace LinAlg{

    Matrix::Matrix(const size_t rows, const size_t columns){
        this->num_rows = rows;
        this->num_columns = columns;

        matrix.reserve(num_rows);
        for (int i = 0; i < num_rows; i++)
        {
            matrix.push_back(std::vector<Rational>());
            matrix[i].reserve(num_columns);

            for (int j = 0; j < columns; j++)
            {
                this->matrix[i].push_back(Rational());
            }
        }
        
    }

    std::vector<Rational>& Matrix::operator[](size_t row){
        if(row >= this->num_rows){
            throw std::invalid_argument("Out of bounds access on matrix \n");
        }
        return this->matrix[row];
    }

    Rational Matrix::at(size_t row, size_t column){
        return Rational();
    }

}