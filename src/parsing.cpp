#include "parsing.hpp"
#include <float.h>
#include <initializer_list>
#include <stdexcept>

namespace Algebra{

    const std::string  brackets = "()";
    const std::string  ops = "+-*/";
    const std::string nums = "0123456789.";
    const std::string symbols("0123456789+-*/.()");

    ShuntingYard::ShuntingYard(std::string expr){
        if(expr.length() == 0)
            throw std::invalid_argument("Empty argument to parsing constructor\n");

        else if(is_valid_mstr(expr)){
            std::string temp;
            std::string::iterator it = expr.begin();
            while(it < expr.end()){
                if(ops.find(*it) != std::string::npos || brackets.find(*it) != std::string::npos){
                    temp.push_back(*it);
                    input.push_back(temp);
                    temp.erase();
                    ++it;
                }else{
                    while(nums.find(*it) != std::string::npos && it < expr.end()){
                        temp.push_back(*it);
                        ++it;
                    }
                    input.push_back(temp);
                    temp.erase();
                }
            }
        }
        else throw std::invalid_argument("Invalid argument to parsing constructor\n");
    }


    int ShuntingYard::op_prec(std::string str){ //numbers: 0, +-: 1,  */: 2, (): 3,

        switch (str.length()) {
            case 1:
                if(str[0] == ops[0] || str[0] == ops[1])
                    return 1;
                if(str[0] == ops[2] || str[0] == ops[3])
                    return 2;
                if(is_bracket(str[0]))
                    return 3;
            default:
                for(char& c : str){
                    if(nums.find(c) != std::string::npos)
                        return 0;
                }
                return -1; //error
        }
    }

    
    bool ShuntingYard::is_valid_mstr(std::string& str){
        //check validity
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

    void ShuntingYard::compute(){
        //1. convert to rpn

    }

    void ShuntingYard::toRPN(){
        for(std::string& str : input){
            if(is_operator(str[0]) || is_bracket(str[0]))
                op_stack_push(str);
            else out.push_back(str); //if number push straight to output stack
        }
        for(std::vector<std::string>::iterator it = stack.end() - 1; it >= stack.begin(); --it){
            out.push_back(stack.back()); //pop items from operator stack to output
            stack.pop_back();
        }
    }

    void ShuntingYard::op_stack_push(std::string str){ //to be finished
        if(stack.size() == 0){
            stack.push_back(str);
            return;
        }
        if(is_operator(str[0])){
            while(op_prec(stack.back()) >= op_prec(str)){
                out.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(str);
            return;
        }
        if(str[0] == '('){
            stack.push_back(str);
        }
        if(str[0] == ')'){
            while(stack.back()[0] != '('){
                out.push_back(stack.back());
                stack.pop_back();
            }
            return;
        }

    }

    /*    double parse_frac(std::string str){ //broken

        //remove whitespaces
        for(std::string::iterator i = str.begin(); i < str.end(); ++i){
            if(*i == ' ')
                str.erase(i);
        }
        //if(!ShuntingYard::is_valid_mstr(str))
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
                return parse_frac(str.substr(0, str.find("/"))) / parse_frac(str.substr(str.find("/") + 1, next_op(str, str.find('/')) - str.find('/') + 1));// operators
            }else{
                return parse_frac(str.substr(0, str.find("*"))) * parse_frac(str.substr(str.find("*") + 1, next_op(str, str.find('*')) - str.find('*') + 1));
            }
        }

        else if(str.find('-') != std::string::npos || str.find('+') != std::string::npos){
            if(str.find('+') < str.find('-')){
                return parse_frac(str.substr(0, str.find("+"))) + parse_frac(str.substr(str.find("+") + 1, str.length()));// +- operators
            }else{
                return parse_frac(str.substr(0, str.find("-"))) - parse_frac(str.substr(str.find("-") + 1, str.length()));
            }
        
        }
        return std::stod(str);
    }*/

    int str_charcount(std::string str, char c){
        int count = 0;
        for (char& ch : str) {
            if(c == ch){
                count++;
            }
        }
        return count;
    }

    bool ShuntingYard::is_operator(char& c){
        std::string symbols("+-*/");
        return symbols.find(c) != std::string::npos;
    }

    bool ShuntingYard::is_bracket(char& c){
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

    size_t next_op(std::string& str, size_t index){
        std::string operators("+-*/)");
        if(str[index] == '/' || str[index] == '+'){
            do{
                ++index;
            }while(operators.find(str[index]) != std::string::npos);
        }
        return --index;
    }
}
