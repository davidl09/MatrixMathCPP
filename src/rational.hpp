#include <iostream>
#include <stdexcept>

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

long int gcf();

class Rational{
    public:
        Rational(int n, int d);
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
};

#endif