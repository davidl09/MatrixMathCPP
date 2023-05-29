#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#include "rational.hpp"

namespace LinAlg{
    class Matrix{
        public:
        private:
            std::vector<std::vector<Rational>> matrix;
    };
}

#endif
   