#include "Parser.hpp"
#include "Lexer.hpp"
#include "Utils.hpp"
#include <variant>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <stack>
Parser::Parser(std::string src): source(src){
    Lexer lex(source);
    tokens = lex.parse();
};

double Parser::parse() {
    //printTokens();
    // se left e' op -> errore
    Token term =  advance();
    double left;
    switch(term.m_type){
        case (TokenType::NUMBER) :{
            left = std::stod(term.m_value);
            break;
        }
        case (TokenType::OPEN_PARENTHESIS):{
            left = parse();
            break;
        }
        default:{
            throw std::runtime_error("ERROR: Malformed String: parte sinistra");
        }
    }
    
    if (isEnd()) return left;
    while(!isEnd()){
        // controlla la prossima OP
        term = advance();
        char op;
        switch(term.m_type){
            case (TokenType::OPERATOR) :{
                op = term.m_value[0];
                break;
            }
            case (TokenType::CLOSED_PARENTHESIS):{
                return left;
            }
            default:{
                throw std::runtime_error("ERROR: Malformed String: parte centrale");
            }
        }
        term = advance();
        double right;
        switch(term.m_type){
            case (TokenType::NUMBER) :{
                right = std::stod(term.m_value);
                break;
            }
            case (TokenType::OPEN_PARENTHESIS):{
                right = parse();
                break;
            }
            default:{
                throw std::runtime_error("ERROR: Malformed String: parte destra");
            }
        }
        switch (op){
            case '+': {
                left+=right;
                break;
            }
            case '-':{
                left-=right;
                break;
            }
            case '*':{
                left*=right;
                break;
            }
            case '/':{
                left/=right;
                break;
            }

        }   
    }
    return left;
}
// Espressioni: VAL | VAL OP ESP 
double Parser::parseExpression(){
    //printTokens();
    // se left e' op -> errore
    Token term =  advance();
    double left;
    switch(term.m_type){
        case (TokenType::NUMBER) :{
            left = std::stod(term.m_value);
            break;
        }
        case (TokenType::OPEN_PARENTHESIS):{
            left = parseExpression();
            break;
        }
        default:{
            throw std::runtime_error("ERROR: Malformed String: al centro vanno gli operatori");
        }
    }
    if (isEnd()) return left;
    while(!isEnd()){
        // controlla la prossima OP
        term = advance();
        char op;
        switch(term.m_type){
            case (TokenType::OPERATOR) :{
                op = term.m_value[0];
                break;
            }
            case (TokenType::CLOSED_PARENTHESIS):{
                return left;
            }
            default:{
                throw std::runtime_error("ERROR: Malformed String: al centro vanno gli operatori");
            }
        }
        
        term = advance();
        double right;
        switch(term.m_type){
            case (TokenType::NUMBER) :{
                right = std::stod(term.m_value);
                break;
            }
            case (TokenType::OPEN_PARENTHESIS):{
                right = parseExpression();
                break;
            }
            default:{
                throw std::runtime_error("ERROR: Malformed String: al centro vanno gli operatori");
            }
        }
        switch (op){
            case '+': {
                left+=right;
                break;
            }
            case '-':{
                left-=right;
                break;
            }
            case '*':{
                left*=right;
            }
            case '/':{
                left/=right;
            }
        }   
    }
    return left;
}

// valuta il termine
std::variant<double,std::string> Parser::parseTerm(){
    Token token = advance();
    if (token.m_type == TokenType::NUMBER){
        return std::stod(token.m_value);
    }
    return token.m_value;
}

double Parser::parseFactor(){
    return 1.0;
}

bool Parser::match(TokenType type){
    TODO("Cambiare funzione con tipo char e  controllare il tipo di carattere");
    return tokens[cursor].m_type == type;
}

Token Parser::previous(){
    if (cursor == 0) return tokens[cursor];
    return tokens[cursor--];
}
Token Parser::advance(){
    return tokens[cursor++];
}
bool Parser::isEnd(){
    if (tokens[cursor].m_type == TokenType::END_TOKEN){
        return true;
    }
    return false;
}

void Parser::printTokens(){
    for (Token t:tokens){
        std::cout<<"Type: "<< static_cast<int>(t.m_type)<<"\t Value: "<<t.m_value<<std::endl;
    }
}

int opPriority(char op){
    if(op == '+'|| op == '-'){
        return 1;
    }
    if (op == '*'||op == '/'){
        return 2;
    }
    return 0;
}

