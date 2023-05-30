include_directories(${MatrixMath_SOURCE_DIR}/utils/include)

set(EXECUTABLE_OUTPUT_PATH ${MatrixMath_SOURCE_DIR}/bin)

add_executable(MatrixMath main.cpp matrix.cpp rational.cpp parsing.cpp tests.cpp)