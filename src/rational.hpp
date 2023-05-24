#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

bool is_operator(char& c);
bool b_parity(std::string& str);
bool is_bracket(char& c);
size_t match_bracket(std::string& str, size_t index);
std::vector<size_t> open_bracket_groups(std::string& str);
bool is_valid_mstr(std::string& str);
int str_charcount(std::string str, char c); 
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
