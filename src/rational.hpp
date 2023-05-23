#include <iostream>
#include <stdexcept>
#include <vector>

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

std::vector<long int> prime_fact(long int a);
long int gcf(int a, int b);

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