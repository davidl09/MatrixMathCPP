#include "rational.hpp"
#include "parsing.hpp"

int main(){
    std::string temp;
    std::cin >> temp;
    Algebra::ShuntingYard op(temp);
    
}