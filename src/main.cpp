#include "rational.hpp"

int main(){
    double a;
    /*
    Rational a(3, 2);
    Rational b(4, 5);
    Rational c = a + b;

    std::cout << c.numer() << "/" << c.denom() << std::endl;
    std::cout << gcf(24, 18) << std::endl;*/
    //std::string str;
    while(true){
        std::cin >> a;
        if (std::cin.fail()){
            std::cout << "ERROR -- You did not enter an integer";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        Rational c(a);
        std::cout << c.tostr() << std::endl;
    }
    

}