#include "rational.hpp"
#include "parsing.hpp"
#include "matrix.hpp"
#include "tests.hpp"

using namespace LinAlg;

int main(){

    std::string temp;
    LinAlg::Rational num;
    while(true){
        try{
            std::cout << "Type in an expression to evaluate\n";
            std::getline(std::cin, temp);
            num = Parsing::str_to_rational(temp);
            std::cout << temp << " = " << num << " , or approx. " << num.approx() << "\n";
        }
        catch(...){
            std::cout << "That was not valid input, please try again" << "\n";
        }
    }
/*
    Tests::Constructors();
    Tests::Parsing();
    Tests::DecimalParsing(); // all tests passed
    std::string temp;
    while(true){
        std::cout << "Enter an expression" << std::endl;
        std::cin >> temp;
        LinAlg::Rational shunt(temp);
        std::cout << "Result: " << shunt.tostr() << "Approximation: " << shunt.approx() << std::endl;
    }*/
}
