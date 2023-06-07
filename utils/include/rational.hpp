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
            Rational(int n);
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
            void set_value(std::string expr);

            friend std::istream& operator >> (std::istream& in, Rational& r);// IO functions
            friend std::ostream& operator << (std::ostream& out , Rational& r);

        private:
            void cleanup();
            long long numerator;
            long long denominator;
    };

    bool isprime(long a);
    std::vector<long int> prime_fact(long int a);
    long int gcf(int a, int b);
}

#endif
