#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#include "ClassRational_HPP/rational.hpp"

namespace LinAlg{

    template<class T>
    class Matrix{
        public:
            Matrix(const size_t rows, const size_t columns){ //constructor
                this->num_rows = rows;
                this->num_columns = columns;

                matrix.reserve(num_rows);
                for (int i = 0; i < num_rows; i++)
                {
                    matrix.push_back(std::vector<T>());
                    matrix[i].reserve(num_columns);
                    
                    for (int j = 0; j < columns; j++)
                    {
                        this->matrix[i].push_back((T)0);
                    }
                }
                
            }

            T at(size_t row, size_t column){
                if(row >= this->num_rows || column >= num_columns){
                    throw std::invalid_argument("Out of bounds access on matrix \n");
                }
                return this->matrix[row][column];
            }

            std::vector<T>& operator[](size_t row){
                if(row >= this->num_rows){
                    throw std::invalid_argument("Out of bounds access on matrix \n");
                }
                return this->matrix[row];
            }

            void populate(){
                std::string temp;
                for(size_t i = 0; i < num_rows; ++i){
                    for (size_t j = 0; j < num_columns; j++)
                    {
                        std::cout << "Enter a value to set column " << j << ", row " << i << "\n";
                        std::cin >> matrix[i][j];
                    }
                }
                std::cout << std::endl;
            }

            void print(){
                for(auto row : matrix){
                    for(auto val : row){
                        std::cout << val << "  ";
                    }
                    std::cout << "\n";
                }
                std::cout << std::endl;
            }

            void set_at(T value, size_t row, size_t column){
                if(row >= num_rows || column >= num_columns){
                    throw std::invalid_argument("Out of bounds value set on matrix \n");
                }
                matrix[row][column] = value;
            }

            Matrix<T>& operator+(Matrix<T>& newmat){
                
            }

            
        private:
            size_t num_rows;
            size_t num_columns;

            std::vector< std::vector< T > > matrix;

    };

}

#endif