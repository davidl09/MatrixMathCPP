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
            Rational(int a);
            Rational(int n, int d);
            Rational(double n, double d);
            Rational(double r);
            Rational(std::string& str);
            Rational();
            Rational operator+(Rational a);
            Rational operator+(int a);
            Rational operator-(Rational a);
            Rational operator-(int a);
            Rational operator*(Rational a);
            Rational operator*(int a);
            Rational operator/(Rational a);
            Rational operator/(int a);
            Rational& operator+=(Rational a);
            Rational& operator+=(int a);
            Rational& operator -=(Rational a);
            Rational& operator -=(int a);
            Rational& operator*=(Rational a);
            Rational& operator*=(int a);
            Rational& operator/=(Rational a);
            Rational& operator/=(int a);
            Rational operator^(Rational a);
            

            bool operator>(Rational& a);
            bool operator>(int& a);
            bool operator>(int a);
            bool operator<(Rational& a);
            bool operator<(int& a);
            bool operator<(int a);
            bool operator==(Rational& a);
            bool operator==(int& a);
            bool operator==(int a);
            bool operator!=(Rational& a);
            bool operator!=(int& a);
            bool operator!=(int a);


            Rational inverse();
            long int numer();
            long int denom();
            std::string tostr();
            double approx();
            void invert();
            void set_value(int a);
            void set_value(double a);
            void set_value(std::string& expr);

            friend std::istream& operator >> (std::istream& in, Rational& r);// IO functions
            friend std::ostream& operator << (std::ostream& out , Rational& r);

        private:
            void cleanup();
            long long numerator;
            long long denominator;
    };

    bool isprime(int a);
    std::vector<long int> prime_fact(long int a);
    long int gcf(int a, int b);
}

#endif
