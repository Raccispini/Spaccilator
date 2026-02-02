#include "Parser.hpp"
#include "Lexer.hpp"
#include "Utils.hpp"
#include <vector>

Parser::Parser(std::string src): source(src){
    Lexer lex(source);
    tokens = lex.parse();
};

double Parser::parse(){
    
    return 3.0;
}
// Espressioni: VAL | VAL OP ESP 
double Parser::parseExpression(){
    // se left e' op -> errore
    double left =  parseTerm();
    // controlla la prossima OP
    //valuta il prossimo token come parsExpression
    return left;
}

// valuta il termine
double Parser::parseTerm(){
    
}

double Parser::parseFactor(){

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