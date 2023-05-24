#include "rational.hpp"
#include <stdexcept>

int str_charcount(std::string str, char c){
    int count = 0;
    for (char& ch : str) {
        if(c == ch){
            count++;
        }
    }
    return count;
}

bool is_operator(char& c){
    std::string symbols("+-*/");
    return symbols.find(c) != std::string::npos;
}

bool is_valid_mstr(std::string& str){
    //check validity
    std::string symbols("0123456789+-*/.");
    for(char& c : str){
        if(symbols.find(c) == std::string::npos){ //if this char is not in list of valid symbols
            throw std::invalid_argument("String could not be parsed, check input\n"); //then throw exception
        }
    }

    for(int i = 0; i < str.length(); ++i){
        if(is_operator(str[i])){
            if(i == 0 || i == str.length() - 1){ //check these first to avoid out of bounds array access
                throw std::invalid_argument("Input operator syntax error\n");
            }
            if(is_operator(str[i - 1]) || is_operator(str[i + 1])){
                throw std::invalid_argument("Input operator syntax error\n");
            }
        }
    }
    return true;
}

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
    Rational(n/d);
}

Rational::Rational(double r){
    long long num, den;
    long gcd;
    num = std::round(r * 1e5);
    den = std::round(1e5);
    while(num%10 == 0){
        num/=10;
        den/=10;
    }
    gcd = gcf(num, den);
    numerator = num/gcd;
    denominator = den/gcd;
}  

Rational::Rational(std::string str){
    Rational(parse_frac(str));
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

    if(!is_valid_mstr(str))
        return 0; //modify later

    if(str.find('/') != std::string::npos || str.find('*') != std::string::npos){
        if(str.find('/') < str.find('*')){
            return parse_frac(str.substr(0, str.find("/"))) / parse_frac(str.substr(str.find("/") + 1, str.length()));
        }else{
            return parse_frac(str.substr(0, str.find("*"))) * parse_frac(str.substr(str.find("*") + 1, str.length()));
        }
    }
    if(str.find('-') != std::string::npos || str.find('+') != std::string::npos){
        if(str.find('+') < str.find('-')){
            return parse_frac(str.substr(0, str.find("+"))) + parse_frac(str.substr(str.find("+") + 1, str.length()));
        }else{
            return parse_frac(str.substr(0, str.find("-"))) - parse_frac(str.substr(str.find("-") + 1, str.length()));
        }
        
    }
    return std::stod(str);
}

Rational Rational::operator+(Rational a){
    Rational res((int)(this->numerator * a.denominator + a.numerator * this->denominator), (int)(a.denominator * this->denominator));
    return res;
}
