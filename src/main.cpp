#include "rational.hpp"

int main(){/*
    Rational a(3, 2);
    Rational b(4, 5);
    Rational c = a + b;

    std::cout << c.numer() << "/" << c.denom() << std::endl;
    std::cout << gcf(24, 18) << std::endl;*/
    std::string str;
    while(true){
        std::cin >> str;    
        std::cout << parse_frac(str) << std::endl;
    }
    

}