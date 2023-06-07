#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#include "rational.hpp"

namespace LinAlg{

    template<typename T>
    class Matrix{
        public:
            Matrix(const size_t rows, const size_t columns); //Constructor initializes all entries to 0
            Rational at(size_t row, size_t column);
            std::vector<T>& operator[](size_t row);
            void populate();
            void print();
            
        private:
            size_t num_rows;
            size_t num_columns;
            void set_at(T value, size_t row, size_t column);
            std::vector< std::vector< T > > matrix;
    };
}

#endif
   