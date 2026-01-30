#include "Parser.hpp"
#include <iostream>
#include <vector>
#include <regex>
#include <expected>
#include <cstdlib>


Parser::Parser(std::string s) : m_stringa(s) {
  std::cout << "Parser inizializzato con stringa " << m_stringa << " !"
            << std::endl;
}

Token::Token(TokenType type,std::variant<std::string,float> value) :m_type(type),m_value(value){};

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
std::expected<Token,std::string> Lexer::generate_token(std::string str) {
  std::regex number_pattern(R"(\d+([.,]\d*)?)");
  std::regex operation_pattern(R"()");

  if (std::regex_match(str,number_pattern)){ // e' un numero
    Token token(TokenType::Number,str);
    return token;
  }
  // controllo se e' un operatore
  if (str.length()==1){
    char c = str[0];
    if (c == '+' || c == '-' || c == '/' || c == '*'){
      Token token(TokenType::Operator,str);
      return token;
    }
  }
  return std::unexpected("Stringa non valida");
}

std::vector<Token> Lexer::parse(){
 // std::regex check_pattern(R"(\s*[+-]?(\d+([.,]\d*)?|[.,]\d+)\s*)([+\-*/]\s*[+-]?(\d+([.,]\d*)?|[.,]\d+)\s*)");
  std::regex check_pattern(R"(^[0-9+\-*/.,\s]+$)");

  if (std::regex_match(source.begin(),source.end(),check_pattern)){
    std::cerr <<"Stringa non valida"<<std::endl;
    std::exit(EXIT_FAILURE);
  }
  
  std::string buffer = "";
  std::vector<Token> tokens;
  //regex patterns
  
  while(!isAtEnd()){
    buffer+=advance();
    if (peekNext() == ' '){
      auto token = generate_token(buffer);
      if (!token.has_value()){
        std::cerr<<token.error()<<std::endl;
        break;
      }else{
        tokens.push_back(token.value());
        buffer="";
        advance();
      }
    }
    // se e' l'ultimo ciclo
    if (peekNext()!='\0' && buffer.length()!=0){
      auto token = generate_token(buffer);
      if (!token.has_value()){
        std::cerr<<token.error()<<std::endl;
      }else{
        tokens.push_back(token.value());
      }

    }
  }
return tokens;
}
