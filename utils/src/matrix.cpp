#include "rational.hpp"
#include "matrix.hpp"

namespace LinAlg{

    template<typename T>
    Matrix<T>::Matrix(size_t rows, size_t columns){ //constructor
        this->num_rows = rows;
        this->num_columns = columns;

        matrix.reserve(num_rows);
        for (int i = 0; i < num_rows; i++)
        {
            matrix.push_back(std::vector<Rational>());
            matrix[i].reserve(num_columns);
            
            for (int j = 0; j < columns; j++)
            {
                this->matrix[i].push_back((T)0);
            }
        }
        
    }

    template<typename T>
    std::vector<T>& Matrix<T>::operator[](size_t row){
        if(row >= this->num_rows){
            throw std::invalid_argument("Out of bounds access on matrix \n");
        }
        return this->matrix[row];
    }

    template<typename T>
    Rational Matrix<T>::at(size_t row, size_t column){
        return Rational();
    }

    template<typename T>
    void Matrix<T>::set_at(T value, size_t row, size_t column){
        if(row >= num_rows || column >= num_columns){
            throw std::invalid_argument("Out of bounds value set on matrix \n");
        }
        matrix[row][column] = value;
    }

    template<typename T>
    void Matrix<T>::print(){
        for(auto row : matrix){
            for(auto val : row){
                std::cout << val << "  ";
            }

        }
    }

    template<typename T>
    void Matrix<T>::populate(){
        std::string temp;
        for(size_t i = 0; i < num_rows; ++i){
            for (size_t j = 0; j < num_columns; j++)
            {
                std::cout << "Enter a value to set column " << j << ", row " << i << "\n";
                std::cin << matrix[i][j];
            }
            
        }
        std::cout << std::endl;
    }

}