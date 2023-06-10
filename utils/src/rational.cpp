#include "rational.hpp"
#include "parsing.hpp"


namespace LinAlg{

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

    bool isprime(int a){
        if(prime_fact(a).size() == 1)
            return true;
        return false;
    }

    long int gcf(int a, int b){
        std::vector<long int> pf_a = prime_fact((long) a), pf_b = prime_fact((long) b);
        
        a = (a < 0 ? -a : a);
        b = (b < 0 ? -b : b);
        
        long prime_fact = 1;

        if(pf_a.size() == 1 && pf_b.size() == 1 && pf_b[0] != pf_a[0])
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

    Rational::Rational(){
        numerator = 0;
        denominator = 1;
    }

    Rational::Rational(int n, int d){
        numerator = n;
        if(d == 0)
            throw std::invalid_argument("Denominator cannot be set to 0!\n");
        denominator = d;
        cleanup();
    }

    Rational::Rational(int a){
        this->numerator = a;
        this->denominator = 1;
    }

    Rational::Rational(double n, double d){ //works, needs more testing
        Rational a(n), b(d);        //--> constructor for Rational from single double retains accuracy (no truncation)

        a /= b; //Rational /= retains accuracy
        *this = a;
        
    }

    Rational::Rational(double r){
        long long num, den;
        long gcd;
        num = std::round(r * 1e5);
        den = std::round(1e5);
        numerator = num;
        denominator = den;
        this->cleanup();
    }  

    Rational::Rational(std::string& str){
        Parsing::ShuntingYard shunt(str);
        shunt.compute();
        *this = shunt.getResult();
    }

    void Rational::set_value(std::string& expr){
        Parsing::ShuntingYard shunt(expr);
        shunt.compute();
        *this = shunt.getResult();
    }

    void Rational::set_value(int a){
        this->denominator = 1;
        this->numerator = a;
    }

    void Rational::set_value(double a){
        this->numerator = std::round(a * 1e5);
        this->denominator = std::round(1e5);
        this->cleanup();
    }

    long int Rational::numer(){
        return numerator;
    }

    long int Rational::denom(){
        return denominator;
    }

    void Rational::cleanup(){
        if(denominator == 0){
            throw std::invalid_argument("Denominator cannot have has value equal to 0!\n");
            return;
        }

        if(numerator == 0){
            denominator = 1;
            return;
        }
        
        if(denominator < 0){
            denominator *= -1;
            numerator *= -1;
        }

        while(numerator % 10 == 0 && denominator % 10 == 0){
            numerator /= 10;
            denominator /= 10;
        }
        
        long gfact = gcf(numerator, denominator);
        
        numerator /= gfact;
        denominator /= gfact;
        return;
    }

    std::istream& operator >> (std::istream& in, Rational& r){
        std::string temp;
        std::cin >> temp;
        r.set_value(temp);
        return in;
    }

    std::ostream& operator << (std::ostream& out , Rational& r){
        std::cout << r.tostr();
        return out;
    }


    std::string Rational::tostr(){
        return std::to_string(numerator) + (denominator == 1 ? "" : ("/" + std::to_string(denominator)));
    }

    double Rational::approx(){
        return (double)numerator/(double)denominator;
    }

    Rational Rational::operator+(Rational a){
        return Rational((int)(this->numerator * a.denominator + a.numerator * this->denominator), (int)(a.denominator * this->denominator));
    }

    Rational Rational::operator+(int a){
        return Rational((int)(this->numerator + a * this->denominator), this->denominator);
    }

    Rational& Rational::operator+=(Rational a){
        long temp = this->denominator;
        this-> numerator *= a.denominator;
        this->denominator *= a.denominator;
        a.denominator *= temp;
        a.numerator *= temp;
        
        this->numerator += a.numerator;
        this->cleanup();
        
        return *this;
    }

    Rational& Rational::operator+=(int a){
        this->numerator += a * this->denominator;
        this->cleanup();
        return *this;
    }

    Rational Rational::operator-(Rational a){
        Rational temp((int)(this->numerator * a.denominator - a.numerator * this->denominator), (int)(a.denominator * this->denominator));
        temp.cleanup();
        return temp;
    }
        
    Rational Rational::operator-(int a){
        return Rational((int)(this->numerator - a * this->denominator), this->denominator);
    }

    Rational& Rational::operator-=(Rational a){
        long temp = this->denominator;
        this-> numerator *= a.denominator;
        this->denominator *= a.denominator;
        a.denominator *= temp;
        a.numerator *= temp;
        
        this->numerator -= a.numerator;
        this->cleanup();
        
        return *this;
    }

    Rational Rational::operator*(Rational a){
        return Rational((int)(this->numerator * a.numer()), (int)(this->denominator * a.denom()));
    }

    Rational Rational::operator*(int a){
        return Rational(int(this->numerator * a), this->denominator);
    }

    Rational& Rational::operator*=(Rational a){
        this->numerator *= a.numerator;
        this->denominator *= a.denominator;
        this->cleanup();
        return *this;
    }

    Rational& Rational::operator*=(int a){
        this->numerator *= a;
        this->cleanup();
        return *this;
    }

    Rational Rational::operator/(Rational a){
        return Rational((int)(this->numerator * a.denominator), this -> denominator * a.numerator);
    }

    Rational Rational::operator/(int a){
        return Rational(this->numerator, (int)(this->numerator * a));
    }

    Rational& Rational::operator/=(Rational a){
        this->numerator *= a.denominator;
        this->denominator *= a.numerator;
        this->cleanup();
        return *this;
    }

    Rational& Rational::operator/=(int a){
        this->denominator *= a;
        this->cleanup();
        return *this;
    }

    Rational Rational::operator^(Rational a){
        Rational temp = *this;

        if(a.denominator == 1){
            for(int i = 0; i < a.numerator; ++i){
                temp.numerator *= a.numerator;
            }
            temp.cleanup();
            return temp;
        }

        temp.set_value(std::pow(this->approx(), a.approx()));
        return temp;
    }

    bool Rational::operator>(Rational& a){
        return (*this - a).numerator > 0;
    }

    bool Rational::operator>(int& a){
        return (*this - a).numerator > 0;
    }

    bool Rational::operator>(int a){
        return(*this - a).numerator > 0;
    }

    bool Rational::operator<(Rational& a){
        return (*this - a).numerator < 0;
    }

    bool Rational::operator<(int& a){
        return (*this - a).numerator < 0;
    }

    bool Rational::operator<(int a){
        return (*this - a).numerator < 0;
    }

    bool Rational::operator==(Rational& a){
        return (*this - a).numerator == 0;
    }

    bool Rational::operator==(int& a){
        return this->numerator == a * this->denominator;
    }

    bool Rational::operator==(int a){
        return this->numerator == a * this->denominator;
    }

    bool Rational::operator!=(Rational& a){
        return !(*this == a);
    }

    bool Rational::operator!=(int& a){
        return !(this->denominator == 1 && this->numerator == a);
    }

    bool Rational::operator!=(int a){
        return !(this->denominator == 1 && this->numerator == a);
    }



    void Rational::invert(){
        if(numerator == 0)
            throw std::invalid_argument("Cannot invert fraction that has value 0\n");
        long temp = numerator;
        numerator = denominator;
        denominator = temp;
    }

    Rational Rational::inverse(){
        if(numerator == 0)
            throw std::invalid_argument("Cannot invert fraction that has value 0\n");

        return Rational((int)this->denominator, this->numerator);
    }
}