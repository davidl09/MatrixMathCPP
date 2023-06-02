#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdlib.h>


namespace LinAlg{

    class Rational{
        
        public:
            Rational();
            Rational(int n, int d);
            Rational(double n, double d);
            Rational(double r);
            Rational(std::string str);
            Rational();
            Rational operator+(Rational a);
            Rational operator+(long a);
            Rational operator-(Rational a);
            Rational operator-(long a);
            Rational operator*(Rational a);
            Rational operator*(long a);
            Rational operator/(Rational a);
            Rational operator/(long a);
            Rational& operator+=(Rational a);
            Rational& operator+=(long a);
            Rational& operator -=(Rational a);
            Rational& operator -=(long a);
            Rational& operator*=(Rational a);
            Rational& operator*=(long a);
            Rational& operator/=(Rational a);
            Rational& operator/=(long a);

            Rational inverse();
            long int numer();
            long int denom();
            std::string tostr();
            double approx();
            void invert();

        private:
            void cleanup();
            long int numerator;
            long int denominator;
    };

    bool isprime(long a);
    std::vector<long int> prime_fact(long int a);
    long int gcf(int a, int b);
}

#endif
