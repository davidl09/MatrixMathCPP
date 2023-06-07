#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#include "rational.hpp"

namespace LinAlg{
    class Matrix{
        public:
            Matrix(size_t rows, size_t columns);
            Rational at(size_t row, size_t column);
            std::vector<Rational>& operator[](size_t row);
            
        private:
            const size_t num_rows;
            const size_t num_columns;
            std::vector<std::vector<Rational>> matrix;
    };
}

#endif
   