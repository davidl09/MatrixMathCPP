#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>


bool isprime(long a);
std::vector<long int> prime_fact(long int a);
long int gcf(int a, int b);
double parse_frac(std::string str);

class Rational{
    public:
        Rational(int n, int d);
        Rational(double n, double d);
        Rational(double r);
        Rational(std::string str);
        Rational operator+(Rational a);
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
