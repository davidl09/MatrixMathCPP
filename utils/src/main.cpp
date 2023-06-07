#include "rational.hpp"
#include "parsing.hpp"
#include "matrix.hpp"
#include "tests.hpp"

using namespace LinAlg;

int main(){

    Rational a;
    a = Parsing::str_to_rational("2^3^2");

    std::cout << a << std::endl;
    
    /*
    std::string temp;
    LinAlg::Rational num;
    while(true){
        try{
            std::cout << "Type in an expression to evaluate\n" << std::endl;
            std::getline(std::cin, temp);
            num = Parsing::str_to_rational(temp);
            std::cout << temp << " = " << num.tostr() << " , or approx. " << num.approx() << std::endl;
        }
        catch(...){
            std::cout << "That was not valid input, please try again" << std::endl;
        }
    }

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
