#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <vector>
#include <string>

#include "rational.hpp"

namespace Parsing{

    class ShuntingYard{
        public:
            ShuntingYard(std::string expr);
            void compute();
            LinAlg::Rational getResult();
            std::string getResult_s();
            double getResult_lf();
            static bool is_operator(char& c);
            static bool is_bracket(char& c);
            static bool is_valid_mstr(std::string& str);
            
        private:
            void toRPN();
            void evaluate();
            std::vector<std::string> input;
            std::vector<std::string> stack;
            std::vector<std::string> out;
            LinAlg::Rational value;
    };

    class ShuntingStack{
        public:
            void push_stack(std::string str); //appends element to last element
            std::vector<std::string> result();
            bool is_empty();
        private:
            std::vector<std::string> stack;
            std::vector<std::string> output;
    };
   
    size_t match_bracket(std::string& str, size_t index);
    std::vector<size_t> open_bracket_groups(std::string& str);
    int op_prec(std::string str);
    int str_charcount(std::string str, char c); 

    LinAlg::Rational str_to_rational(const std::string& str);
    
}

#endif