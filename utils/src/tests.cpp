#include "rational.hpp"
#include "parsing.hpp"

namespace Tests{
    void Constructors(){
        //std::cout << LinAlg::Rational(4, 3).tostr() << std::endl; //works
        //std::cout << LinAlg::Rational(7).tostr() << std::endl; //works
        //std::cout << LinAlg::Rational(0.56).tostr() << std::endl; //works
        std::cout << LinAlg::Rational((double)3.45, (double)5.2).tostr() << std::endl; //works
        std::cout << LinAlg::Rational(-7.0/5).tostr() << std::endl; //...
        std::cout << LinAlg::Rational("-7/5").tostr() << std::endl;
        std::cout << LinAlg::Rational("8/9 + 2/18").tostr() << std::endl;
        std::cout << LinAlg::Rational("0.2/0.1").tostr() << std::endl;
    }

    void UnaryOps(){
        LinAlg::Rational num(3);
        std::cout << num.tostr() << std::endl;
        num *= 3;
        std::cout << num.tostr() << std::endl;
        num += 2;
        std::cout << num.tostr() << std::endl;
        num /= 7;
        std::cout << num.tostr() << std::endl;
        num += LinAlg::Rational(3, 4);
        std::cout << num.tostr() << std::endl;
    }

    void Parsing(){
        LinAlg::Rational test("(0.2 +0.4) * 5 - 2/7 ");
        std::cout << "Parsing test expected: 19/7, actual: " << test.tostr() << std::endl;
    }

    void DecimalParsing(){
        LinAlg::Rational test("0.3 + 0.3");
        std::cout << "Test: 0.3 + 0.3, result: " << test.tostr() << std::endl;
    }
}