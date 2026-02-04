#include "Lexer.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <expected>
#include <cstdlib>

Token::Token(TokenType type,std::string value) :m_type(type),m_value(value){};

Lexer::Lexer(std::string_view src ): source(src){};

bool Lexer::isAtEnd() const {
  return cursor >= source.length();
}
char Lexer::advance() {
  return source[cursor++];
}

char Lexer::peek() const {
  return source[cursor];
}

char Lexer::peekNext() const {
  if (cursor +1 >= source.length()) return '\0';
  return source[cursor+1];
}

bool Lexer::match(char expected) {
  if (isAtEnd() || source[cursor]!=expected) return false;
  cursor++;
  return true;
}
Token Lexer::generate_token(std::string str) {
  std::regex number_pattern(R"(\d+([.,]\d*)?)");
  // controllo se e' un operatore
  if (str.length()==1){
    char c = str[0];
    if (c == '+' || c == '-' || c == '/' || c == '*'){
      Token token(TokenType::OPERATOR,str);
      return token;
    }
  }

  if (std::regex_match(str,number_pattern)){ // e' un numero
    Token token(TokenType::NUMBER,str);
    return token;
  }
  if (str=="("){
    Token token(TokenType::OPEN_PARENTHESIS,str);
    return token;
  }
  if (str==")"){
    Token token(TokenType::CLOSED_PARENTHESIS,str);
    return token;
  }
  Token token(TokenType::INVALID,str);
  return token;
}

std::vector<Token> Lexer::parse(){
 // std::regex check_pattern(R"(\s*[+-]?(\d+([.,]\d*)?|[.,]\d+)\s*)([+\-*/]\s*[+-]?(\d+([.,]\d*)?|[.,]\d+)\s*)");
  //std::regex check_pattern(R"(^[0-9+\-*/.,\s]+$)");

  // if (std::regex_match(source.begin(),source.end(),check_pattern)){
  //   std::cerr <<"Stringa non valida"<<std::endl;
  //   std::exit(EXIT_FAILURE);
  // }
  
  std::string buffer = "";
  std::vector<Token> tokens;
  //regex patterns
  while(!isAtEnd()){
    //char next = peekNext();
    char actual = peek();
    // se e' un numero lo aggiunge al buffer
    if (isdigit(actual)){
      buffer+=actual;
    }
    // se e' un simbolo (+,-,*,/) carica il buffer in token e aggiunge al buffer il simbolo
    if (actual=='+'||actual=='-'||actual=='*'||actual=='/'||actual=='('||actual==')'){
      if (buffer.length()!=0){
        Token token = generate_token(buffer);
        tokens.push_back(token);
        buffer="";
      }
      buffer+=actual;
      Token token = generate_token(buffer);
      tokens.push_back(token);
      buffer="";
    }
    // se e' uno spazio carica il buffer in token
    if (actual==' '){
      if (buffer.length()!=0){
        Token token = generate_token(buffer);
        tokens.push_back(token);
        buffer="";
      }
    }
    if (peekNext()=='\0'){
      if (buffer.length()!=0){
        Token token = generate_token(buffer);
        tokens.push_back(token);
        buffer="";
      }
    }
    advance();
  }
  Token token(TokenType::END_TOKEN,"END");
  tokens.push_back(token);
  return tokens;
}
