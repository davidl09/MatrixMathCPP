#include "rational.hpp"

/*
class Rational{
    public:
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
};*/

std::vector<long int> prime_fact(long int a){
    std::vector<long int> res;
    
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

long int gcf(int a, int b){
    std::vector<long int> pf_a = prime_fact((long) a), pf_b = prime_fact((long) b);
    
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
    if(denominator == 0)
        throw std::invalid_argument("Denominator cannot be set to 0!\n");
    denominator = d;
}

long int Rational::numer(){
    return numerator;
}

long int Rational::denom(){
    return denominator;
}

Rational Rational::operator+(Rational a){
    Rational res(this->numerator * a.denominator + a.numerator * this->denominator, a.denominator * this->denominator);
    return res;
}