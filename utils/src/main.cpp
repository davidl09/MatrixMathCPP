#include "rational.hpp"
#include "parsing.hpp"
#include "tests.hpp"

int main(){

    std::string temp;
    LinAlg::Rational num;
    while(true){
        try{
            std::cout << "Type in an expression to evaluate" << std::endl;
            std::cin >> temp;
            std::cin.ignore();
            num = Parsing::str_to_rational(temp);
            std::cout << temp << " = " << num.tostr() << " , or approx. " << num.approx() << std::endl;
        }
        catch(...){
            std::cout << "That was not valid input, please try again" << std::endl;
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

/*
TODO:
    - Change Rational() constructor taking 2 doubles as input
    - Change Shunt class to support parsing as method, not constructor
*/