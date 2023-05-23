#include "rational.hpp"
#include <stdexcept>

/*
class Rational{
    public:
        Rational operator+(Rational a);
        Rational operator-(Rational a);
        Rational operator*(Rational a);
        Rational operator/(Rational a);
        long int data();
        long int numer();
        long int denom();
        void cleanup();
        double dec_est();
    private:
        long int numerator;
        long int denominator;
};*/

Rational::Rational(int n, int d){
    numerator = n;
    if(denominator == 0)
        throw std::invalid_argument("Denominator cannot be set to 0!\n");
    denominator = d;
}

long int Rational::numer(){
    return numerator;
}

long int Rational::denom(){
    return denominator;
}

Rational Rational::operator+(Rational a){
    Rational res(this->numerator + a.numerator, this->denominator + a.denominator);
    return res;
}