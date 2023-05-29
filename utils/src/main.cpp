#include "rational.hpp"
#include "parsing.hpp"

int main(){
    
    Rational a(3,4), b(5, 7);
    Rational c = b - a;
    std::cout << c.tostr();
    
}