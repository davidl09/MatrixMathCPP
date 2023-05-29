#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdlib.h>


class Rational{
    
    public:
        Rational(int n, int d);
        Rational(double n, double d);
        Rational(double r);
        Rational operator+(Rational a);
        Rational operator+(long a);
        Rational operator-(Rational a);
        Rational operator*(Rational a);
        Rational operator/(Rational a);
        long int numer();
        long int denom();
        std::string tostr();
        double approx();

    private:
        void cleanup();
        long int numerator;
        long int denominator;
};

#endif
