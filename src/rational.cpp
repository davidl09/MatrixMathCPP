#include "rational.hpp"


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

bool is_bracket(char& c){
    return c == '(' || c == ')';
}

bool b_parity(std::string& str){
    int brackets = 0;
    for(char& c : str){
        (c == '(' ? ++brackets : (c == ')' ? --brackets : brackets));
    }
    return brackets == 0;
}

size_t match_bracket(std::string& str, size_t index){ //assumes bracket parity is given
    
    size_t brackets = 1; //first bracket already counted
    if(str[index] == '('){
        for(int i = index + 1; i < str.size(); ++i){
            (str[i] == '(' ? ++brackets : (str[i] == ')' ? --brackets : brackets)); //change bracket count
            if(brackets == 0) //if match found return index
                return i;
        }
        return std::string::npos;
    }
    if(str[index] == ')'){
        for(int i = index - 1; i >= 0; --i){
            (str[i] == ')' ? ++brackets : (str[i] == '(' ? --brackets : brackets)); //change bracket count
            if(brackets == 0) //if match found return index
                return i;
        }
        return std::string::npos;
    }
    return std::string::npos;
}

std::vector<size_t> open_bracket_groups(std::string& str){ //assumes bracket parity is given
    size_t index = 0;
    std::vector<size_t> res;
    while(index < str.size()){
        while(str[index] != '(' && index < str.size()){
            ++index;
        }
        if(index < str.size())
            res.push_back(index);
        index = match_bracket(str, index); //jump to paired closing bracket
    }
    return res;
}

bool is_valid_mstr(std::string& str){
    //check validity
    std::string symbols("0123456789+-*/.()");
    for(char& c : str){
        if(symbols.find(c) == std::string::npos){ //if this char is not in list of valid symbols
            return false;
        }
    }

    if(!b_parity(str))
        return false;

    for(int i = 0; i < str.length(); ++i){
        if(is_operator(str[i])){
            if(i == 0 || i == str.length() - 1){ //check these conditions first to avoid out of bounds array access; checks mismatched operators
                return false;
            }
            if(is_operator(str[i - 1]) || is_operator(str[i + 1])){ //check mismatched operators
                return false;
            }
        }
        if(is_bracket(str[i]) && match_bracket(str, i) == std::string::npos){ //check mismatched brackets
            return false;
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

    //remove whitespaces
    for(std::string::iterator i = str.begin(); i < str.end(); ++i){
        if(*i == ' ')
            str.erase(i);
    }
    if(!is_valid_mstr(str))
        return 0; 
    
    if(str.find('(') != std::string::npos){
        std::vector<size_t> g  = open_bracket_groups(str); //vector containing indices of opening brackets for outermost bracket groups
        std::string nstr;
        int close_bracket;
        if((g.size()) != 0){ //if input contains brackets. no need to check bracket parity since is_valid_mstr does so above
            nstr.append(str.substr(0, g[0]));
            for (int i = 0; i < g.size(); ++i) {
                close_bracket = match_bracket(str, g[i]);
                nstr.append(std::to_string(parse_frac(str.substr(g[i] + 1, close_bracket - g[i] - 1))));
                for (int i = close_bracket + 1; str[i] != '(' && i < str.length(); ++i) {
                    nstr.push_back(str[i]);
                }
            }
            return parse_frac(nstr);
        }
    }

    if(str.find('/') != std::string::npos || str.find('*') != std::string::npos){
        if(str.find('/') < str.find('*')){
            return parse_frac(str.substr(0, str.find("/"))) / parse_frac(str.substr(str.find("/") + 1, str.length()));// */ operators
        }else{
            return parse_frac(str.substr(0, str.find("*"))) * parse_frac(str.substr(str.find("*") + 1, str.length()));
        }
    }

    if(str.find('-') != std::string::npos || str.find('+') != std::string::npos){
        if(str.find('+') < str.find('-')){
            return parse_frac(str.substr(0, str.find("+"))) + parse_frac(str.substr(str.find("+") + 1, str.length()));// +- operators
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
