project(MatrixMath)
cmake_minimum_required(VERSION 3.22)

set(CXX_STANDARD 20)

add_executable(MatrixMath main.cpp rational.cpp rational.hpp parsing.cpp parsing.hpp)