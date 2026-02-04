#include "Parser.hpp"
#include "Lexer.hpp"
#include "Utils.hpp"
#include <variant>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

Parser::Parser(std::string src): source(src){
    Lexer lex(source);
    tokens = lex.parse();
};

double Parser::parse() {
    //printTokens();
    // se left e' op -> errore
    std::variant<double,std::string> term =  parseTerm();
    if (std::holds_alternative<std::string>(term)){    // se e' un carattere a sinistra non puo' essere
        //std::cout<<std::get<std::string>(term)<<std::endl;
        throw std::runtime_error("ERROR: Malformed String : a sinistra vanno i numeri");
    }
    double left = std::get<double>(term); //safe
    if (isEnd()) return left;
    while(!isEnd()){
        // controlla la prossima OP
        term = parseTerm();
        if (std::holds_alternative<double>(term)){    // se e' un carattere a sinistra non puo' essere
            throw std::runtime_error("ERROR: Malformed String: al centro vanno gli operatori");
        }
        char op = std::get<std::string>(term)[0];
        term = parseTerm();
        if (std::holds_alternative<std::string>(term)){    // se e' un carattere a sinistra non puo' essere
            //std::cout<<std::get<std::string>(term)<<std::endl;
            throw std::runtime_error("ERROR: Malformed String : a sinistra vanno i numeri");
        }
        double right = std::get<double>(term);
        switch (op){
            case '+': {
                left+=right;
                break;
            }
            case '-':{
                left-=right;
                break;
            }
        }   
    }
    return left;
}
// Espressioni: VAL | VAL OP ESP 
double Parser::parseExpression(){
    // se left e' op -> errore
    std::variant<double,std::string> term =  parseTerm();
    if (std::holds_alternative<std::string>(term)){    // se e' un carattere a sinistra non puo' essere
        //std::cout<<std::get<std::string>(term)<<std::endl;
        throw std::runtime_error("ERROR: Malformed String : a sinistra vanno i numeri");
    }
    double left = std::get<double>(term); //safe
    if (isEnd()){
        return left;
    }
    // controlla la prossima OP
    term = parseTerm();
    if (std::holds_alternative<double>(term)){    // se e' un carattere a sinistra non puo' essere
        throw std::runtime_error("ERROR: Malformed String: al centro vanno gli operatori");
    }
    char op = std::get<std::string>(term)[0];
    double right = parseExpression();
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
        return left;
    }
    //valuta il prossimo token come parsExpression
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
    return tokens[cursor-1];
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