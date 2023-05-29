#include "parsing.hpp"


namespace Algebra{

    const std::string  brackets = "()";
    const std::string  ops = "+-*/";
    const std::string nums = "0123456789.";
    const std::string symbols("0123456789+-*/.()");

    ShuntingYard::ShuntingYard(std::string expr){
        if(expr.length() == 0)
            throw std::invalid_argument("Empty argument to parsing constructor\n");

        for(auto it = expr.begin(); it < expr.end(); ++it){
            if(*it == ' ')
                expr.erase(it);
        }

        if(is_valid_mstr(expr)){
            std::string temp;
            std::string::iterator it = expr.begin();
            while(it < expr.end()){
                if(is_operator(*it) || is_bracket(*it)){ //put operators/brackets into a single token
                    temp.push_back(*it);
                    input.push_back(temp);
                    temp.erase();
                    ++it;
                }else{
                    while(nums.find(*it) != std::string::npos && it < expr.end()){ //put decimal numbers into one token
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


    int op_prec(std::string str){ //numbers: 0, +-: 1,  */: 2, (): 3,
        switch (str.length()) {
            case 1:
                if(str[0] == ops[0] || str[0] == ops[1])
                    return 1;
                if(str[0] == ops[2] || str[0] == ops[3])
                    return 2;
                if(ShuntingYard::is_bracket(str[0]))
                    return 0;
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

    bool ShuntingYard::is_operator(char& c){
        return ops.find(c) != std::string::npos;
    }

    bool ShuntingYard::is_bracket(char& c){
        return c == '(' || c == ')';
    }

    void ShuntingYard::compute(){
        toRPN();
    }

    std::string ShuntingYard::returnRes(){
        std::string temp;
        for(std::string str : out){
            temp.append(str);
        }
        return temp;
    }

    void ShuntingYard::toRPN(){
        ShuntingStack shunt;

        for(std::string& str : input){
            shunt.push_stack(str);
        }
        out = shunt.result();

    }

    //******

    bool ShuntingStack::is_empty(){
        return stack.size() == 0;
    }

    void ShuntingStack::push_stack(std::string str){
        if(str.length() == 0){
            throw std::invalid_argument("Empty string passed to shunting yard algorithm\n");
        }if(ShuntingYard::is_operator(str[0])){
            while(!is_empty() && ShuntingYard::is_operator(stack.back()[0]) && op_prec(stack.back()) >= op_prec(str)){
                output.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(str);
            return;
        }if(ShuntingYard::is_bracket(str[0])){
            switch(str[0]){
                case '(':
                    stack.push_back(str);
                    return;
                case ')':
                    while(stack.back() != "("){
                        if(is_empty())
                            throw std::invalid_argument("Mismatched brackets");
                        output.push_back(stack.back());
                        stack.pop_back();
                    }stack.pop_back(); //discard left bracket
                    return;
            }
        }
        output.push_back(str);
    }

    std::vector<std::string> ShuntingStack::result(){
        while(!is_empty()){
            output.push_back(stack.back());
            stack.pop_back();
        }
        return output;
    }

    //*****

    int str_charcount(std::string str, char c){
        int count = 0;
        for (char& ch : str) {
            if(c == ch){
                count++;
            }
        }
        return count;
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
