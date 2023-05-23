#include "rational.hpp"

std::vector<long int> prime_fact(long int a){
    std::vector<long int> res;
    
    a = (a < 0 ? -a : a);
    
    int i = 2;
    while(i <= a){
        if(a%i == 0){
            res.push_back(i);
            a /= i;
            i = 2;
        }
        else ++i;
    }
    return res;
}

bool isprime(long a){
    if(prime_fact(a).size() == 1)
        return true;
    return false;
}

long int gcf(int a, int b){
    std::vector<long int> pf_a = prime_fact((long) a), pf_b = prime_fact((long) b);
    
    a = (a < 0 ? -a : a);
    b = (b < 0 ? -b : b);
    
    long prime_fact = 1;

    if(pf_a.size() == 1 || pf_b.size() == 1)
        return prime_fact;

    for (int i = 0; i < pf_a.size(); ++i) {
        for (int j = 0; j < pf_b.size(); ++j) {
            if(pf_a[i] == pf_b[j]){
                prime_fact *= pf_b[j];
                pf_b.erase(pf_b.begin() + j);
                pf_a.erase(pf_a.begin() + i);
                break;
            }
        }
    }
    return prime_fact;

}

Rational::Rational(int n, int d){
    numerator = n;
    if(d == 0)
        throw std::invalid_argument("Denominator cannot be set to 0!\n");
    denominator = d;
    cleanup();
}

Rational::Rational(double n, double d){
    
}

Rational::Rational(double r){
    
}

Rational::Rational(std::string str){
    
}


long int Rational::numer(){
    return numerator;
}

long int Rational::denom(){
    return denominator;
}

void Rational::cleanup(){
    if(denominator == 0){
        throw std::invalid_argument("Denominator have value equal to 0!\n");
        return;
    }
    
    if(denominator < 0){
        denominator *= -1;
        numerator *= -1;
    }
    
    long gfact = gcf(numerator, denominator);
    
    numerator /= gfact;
    denominator /= gfact;
    return;
}

std::string Rational::tostr(){
    return std::to_string(numerator) + (denominator == 1 ? "" : ("/" + std::to_string(denominator)));
}

double Rational::approx(){
    return (double)numerator/(double)denominator;
}

double parse_frac(std::string str){ //does not work with brackets yet
    //check validity
    std::string symbols("0123456789+-*/");
    for(char& c : str){
        if(symbols.find(c) == std::string::npos){ //if this char is not in list of valid symbols
            throw std::invalid_argument("String could not be parsed, check input\n"); //then throw exception
        }
    }
    if(str.find('/') != std::string::npos){
        return parse_frac(str.substr(str.begin(), str.find("/"))) / parse_frac(str.substr(str.find("/"), str.length()));
//error here
    }/*
    if(str.contains('*')){
        return parse_frac(str.substr(str.begin(), str.find("*"))) * parse_frac(str.substr(str.find("*"), str.length()));
    }
    if(str.contains('-') || str.contains('+')){
        return parse_frac(str.substr(str.begin(), str.find((str.find('+') < str.find('-') ? '+' : '-')))) * parse_frac(str.substr(str.find((str.find('+') < str.find('-') ? '+' : '-')), str.length()));
        (str.find('+') < str.find('-') ? '+' : '-')
    }*/
    for(char &c : str){
        if(symbols.substr(symbols.begin(), 10).find(c) == std::string::npos){
            throw std::invalid_argument("");
        }
    }
    return (double)std::stod(str);
}

Rational Rational::operator+(Rational a){
    Rational res((int)(this->numerator * a.denominator + a.numerator * this->denominator), (int)(a.denominator * this->denominator));
    return res;
}
