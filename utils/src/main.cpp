#include "rational.hpp"
#include "parsing.hpp"
#include "tests.hpp"

int main(){
    Tests::Constructors();
    Tests::Parsing();
    Tests::DecimalParsing(); // all tests passed
    std::string temp;
    while(true){
        std::cout << "Enter an expression" << std::endl;
        std::cin >> temp;
        LinAlg::Rational shunt(temp);
        std::cout << "Result: " << shunt.tostr() << "Approximation: " << shunt.approx() << std::endl;
    }
}

/*TODO:
    - Change Rational() constructor taking 2 doubles as input
    - Change Shunt class to support parsing as method, not constructor
*/